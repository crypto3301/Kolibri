#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QTimer>
#include <QMessageBox>
#include <QSettings>
#include <QtConcurrent/QtConcurrentRun>
#include <QDebug>
#include <QFile>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isRunning(false)
    , isProcessing(false)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::checkForFiles);

    futureWatcher = new QFutureWatcher<void>(this);
    connect(futureWatcher, &QFutureWatcher<void>::finished, this, [this]() {
        ui->runButton->setEnabled(true);
        if (!isRunning) {
            ui->progressBar->setValue(100);
        }
    });

    ui->progressBar->setRange(0, 100);
    ui->progressBar->setValue(0);

    ui->spinBox->setMinimum(1);
    ui->spinBox->setSuffix(" сек.");

    loadSettings();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::on_browseButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Input Directory", QDir::currentPath());
    if (!dir.isEmpty()) {
        ui->lineEdit->setText(dir);
    }
}

void MainWindow::on_runButton_clicked()
{
    if (!validateSettings()) {
        return;
    }

    if (ui->timerCheckBox->currentIndex() == 1) {
        isRunning = false;
        checkForFiles();
    } else {
        isRunning = true;
        int interval = ui->spinBox->value() * 1000;
        timer->start(interval);
        ui->runButton->setEnabled(false);
    }
}


void MainWindow::checkForFiles()
{
    if (isProcessing) {
        qDebug() << "Processing already in progress, skipping check";
        return;
    }

    QDir dir(ui->lineEdit->text());
    if (!dir.exists()) {
        showMessage("Input directory does not exist");
        return;
    }

    QString maskText = ui->maskLine->text();
    if (maskText.isEmpty()) {
        showMessage("File mask is empty");
        return;
    }

    // Разбиваем строку масок по точке с запятой
    QStringList masks = maskText.split(";", Qt::SkipEmptyParts);

    // Удаляем возможные пробелы вокруг масок
    for (QString& mask : masks) {
        mask = mask.trimmed();
    }

    if (masks.isEmpty()) {
        showMessage("No valid file masks found");
        return;
    }

    QFileInfoList files = dir.entryInfoList(masks, QDir::Files);
    if (files.isEmpty()) {
        showMessage("No files found matching the masks");
        return;
    }

    isProcessing = true;
    ui->progressBar->setValue(0);

    QFuture<void> future = QtConcurrent::run([this, files]() {
        this->processFiles(files);
    });
    futureWatcher->setFuture(future);
}
void MainWindow::processFiles(const QFileInfoList& files)
{
    QByteArray key = QByteArray::fromHex(ui->keyLine->text().toUtf8());
    if (key.size() != 8) {
        emit showMessage("Key must be 8 bytes (16 hex characters)");
        isProcessing = false;
        return;
    }

    QString savePath = ui->pathLine->text();
    QDir saveDir(savePath);
    if (!saveDir.exists()) {
        if (!saveDir.mkpath(".")) {
            emit showMessage("Cannot create save directory");
            isProcessing = false;
            return;
        }
    }

    bool deleteSource = ui->deleteCheckBox->isChecked();
    bool overwrite = (ui->conflictComboBox->currentText() == "Overwrite");

    for (int i = 0; i < files.size(); ++i) {
        if (!isRunning && ui->timerCheckBox->currentIndex() == 0) {
            break;
        }

        QFileInfo fi = files[i];
        QFile file(fi.filePath());
        if (!file.open(QIODevice::ReadOnly)) {
            emit showMessage("Cannot open file: " + fi.fileName());
            continue;
        }

        QByteArray data;
        qint64 totalBytes = 0;
        qint64 fileSize = file.size();
        const qint64 bufferSize = 1024 * 1024;

        while (!file.atEnd()) {
            QByteArray chunk = file.read(bufferSize);
            if (chunk.isEmpty()) {
                break;
            }

            for (int j = 0; j < chunk.size(); ++j) {
                chunk[j] ^= key[j % 8];
            }

            data.append(chunk);
            totalBytes += chunk.size();

            int progress = ((i * 100) + (totalBytes * 100 / fileSize)) / files.size();
            QMetaObject::invokeMethod(ui->progressBar, "setValue",
                                      Qt::QueuedConnection,
                                      Q_ARG(int, progress));
        }
        file.close();

        QString outName = fi.fileName();
        if (!overwrite) {
            int counter = 1;
            QString baseName = fi.completeBaseName();
            QString suffix = fi.suffix();

            while (QFile::exists(savePath + QDir::separator() + outName)) {
                outName = QString("%1_%2.%3").arg(baseName)
                              .arg(counter++)
                              .arg(suffix);
            }
        }

        QFile outFile(savePath + QDir::separator() + outName);
        if (!outFile.open(QIODevice::WriteOnly)) {
            emit showMessage("Cannot create output file: " + outName);
            continue;
        }

        if (outFile.write(data) != data.size()) {
            emit showMessage("Error writing to file: " + outName);
            outFile.close();
            continue;
        }
        outFile.close();

        if (deleteSource) {
            if (!file.remove()) {
                emit showMessage("Cannot delete source file: " + fi.fileName());
            }
        }

        int progress = ((i + 1) * 100) / files.size();
        QMetaObject::invokeMethod(ui->progressBar, "setValue",
                                  Qt::QueuedConnection,
                                  Q_ARG(int, progress));
    }

    isProcessing = false;
    if (ui->timerCheckBox->currentIndex() == 1) {
        emit showMessage("Processing completed");
    }
}

void MainWindow::showMessage(const QString& message)
{
    QMetaObject::invokeMethod(ui->statusbar, "showMessage", Qt::QueuedConnection,
                              Q_ARG(QString, message));
}

bool MainWindow::validateSettings()
{

    if (ui->maskLine->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "File mask cannot be empty");
        return false;
    }

    if (ui->pathLine->text().isEmpty()) {
        QMessageBox::warning(this, "Error", "Save path cannot be empty");
        return false;
    }

    xorKey = parseXorKey(ui->keyLine->text());

    if (xorKey.isEmpty()) {
        QMessageBox::warning(this, "Error",
                             "Invalid XOR key (must be 16 hex characters)");
        return false;
    }

    return true;
}

QByteArray MainWindow::parseXorKey(const QString &keyText)
{
    QString cleanText = keyText.trimmed();
    if (cleanText.length() != 16) return QByteArray();
    return QByteArray::fromHex(cleanText.toLatin1());
}

void MainWindow::on_saveButton_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, "Select Directory to Save Files",
                                                    QDir::currentPath());
    if (!dir.isEmpty()) {
        ui->pathLine->setText(dir);
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("Kolibri", "xor2file");
    settings.setValue("fileMask", ui->maskLine->text());
    settings.setValue("savePath", ui->pathLine->text());
    settings.setValue("inputPath", ui->lineEdit->text());
    settings.setValue("xorKey", ui->keyLine->text());
    settings.setValue("timerMode", ui->timerCheckBox->currentIndex());
    settings.setValue("interval", ui->spinBox->value());
    settings.setValue("conflictMode", ui->conflictComboBox->currentIndex());
    settings.setValue("deleteFiles", ui->deleteCheckBox->isChecked());
}

void MainWindow::loadSettings()
{
    QSettings settings("Kolibri", "xor2file");
    ui->maskLine->setText(settings.value("fileMask", "*.txt;*.bin").toString());
    ui->pathLine->setText(settings.value("savePath", QDir::currentPath()).toString());
    ui->lineEdit->setText(settings.value("inputPath", QDir::currentPath()).toString());
    ui->keyLine->setText(settings.value("xorKey", "0123456789ABCDEF").toString());
    ui->timerCheckBox->setCurrentIndex(settings.value("timerMode", 0).toInt());
    ui->spinBox->setValue(settings.value("interval", 1000).toInt());
    ui->conflictComboBox->setCurrentIndex(settings.value("conflictMode", 0).toInt());
    ui->deleteCheckBox->setChecked(settings.value("deleteFiles", false).toBool());
}
