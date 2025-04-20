#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QTimer>
#include <QDir>
#include <QFuture>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_browseButton_clicked();
    void on_runButton_clicked();
    void on_saveButton_clicked();
    void checkForFiles();
    void on_stopButton_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool isRunning;
    QByteArray xorKey;
    bool isProcessing;
    QFuture<void> future;
    std::atomic<int> processedFilesCount;
    int totalFilesToProcess;
    QMutex progressMutex;

    void processSingleFile(const QFileInfo& fileInfo);
    void showMessage(const QString& message);
    QFutureWatcher<void> *futureWatcher;
    bool validateSettings();
    QByteArray parseXorKey(const QString &keyValue);
    void processFiles(const QFileInfoList& files);
    void saveSettings();
    void loadSettings();
};

#endif // MAINWINDOW_H
