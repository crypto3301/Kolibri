/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label_2;
    QSplitter *splitter;
    QPushButton *browseButton;
    QLineEdit *lineEdit;
    QSplitter *splitter_2;
    QPushButton *saveButton;
    QLineEdit *pathLine;
    QSplitter *splitter_3;
    QCheckBox *deleteCheckBox;
    QLabel *key;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QComboBox *conflictComboBox;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QSpinBox *spinBox;
    QComboBox *timerCheckBox;
    QLineEdit *maskLine;
    QLineEdit *keyLine;
    QWidget *widget;
    QGridLayout *gridLayout;
    QPushButton *runButton;
    QPushButton *stopButton;
    QProgressBar *progressBar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(326, 326);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(326, 326));
        MainWindow->setMaximumSize(QSize(326, 326));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(130, 110, 31, 20));
        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setGeometry(QRect(11, 10, 301, 22));
        splitter->setOrientation(Qt::Horizontal);
        browseButton = new QPushButton(splitter);
        browseButton->setObjectName("browseButton");
        splitter->addWidget(browseButton);
        lineEdit = new QLineEdit(splitter);
        lineEdit->setObjectName("lineEdit");
        splitter->addWidget(lineEdit);
        splitter_2 = new QSplitter(centralwidget);
        splitter_2->setObjectName("splitter_2");
        splitter_2->setGeometry(QRect(10, 170, 301, 22));
        splitter_2->setOrientation(Qt::Horizontal);
        saveButton = new QPushButton(splitter_2);
        saveButton->setObjectName("saveButton");
        splitter_2->addWidget(saveButton);
        pathLine = new QLineEdit(splitter_2);
        pathLine->setObjectName("pathLine");
        splitter_2->addWidget(pathLine);
        splitter_3 = new QSplitter(centralwidget);
        splitter_3->setObjectName("splitter_3");
        splitter_3->setGeometry(QRect(20, 140, 141, 18));
        splitter_3->setOrientation(Qt::Horizontal);
        deleteCheckBox = new QCheckBox(splitter_3);
        deleteCheckBox->setObjectName("deleteCheckBox");
        splitter_3->addWidget(deleteCheckBox);
        key = new QLabel(splitter_3);
        key->setObjectName("key");
        splitter_3->addWidget(key);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 70, 91, 51));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        conflictComboBox = new QComboBox(layoutWidget);
        conflictComboBox->addItem(QString());
        conflictComboBox->addItem(QString());
        conflictComboBox->setObjectName("conflictComboBox");

        verticalLayout->addWidget(conflictComboBox);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName("layoutWidget1");
        layoutWidget1->setGeometry(QRect(166, 40, 141, 119));
        verticalLayout_3 = new QVBoxLayout(layoutWidget1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(layoutWidget1);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        spinBox = new QSpinBox(layoutWidget1);
        spinBox->setObjectName("spinBox");

        verticalLayout_2->addWidget(spinBox);

        timerCheckBox = new QComboBox(layoutWidget1);
        timerCheckBox->addItem(QString());
        timerCheckBox->addItem(QString());
        timerCheckBox->setObjectName("timerCheckBox");

        verticalLayout_2->addWidget(timerCheckBox);


        verticalLayout_3->addLayout(verticalLayout_2);

        maskLine = new QLineEdit(layoutWidget1);
        maskLine->setObjectName("maskLine");

        verticalLayout_3->addWidget(maskLine);

        keyLine = new QLineEdit(layoutWidget1);
        keyLine->setObjectName("keyLine");

        verticalLayout_3->addWidget(keyLine);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(30, 220, 261, 81));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        runButton = new QPushButton(widget);
        runButton->setObjectName("runButton");

        gridLayout->addWidget(runButton, 0, 0, 1, 1);

        stopButton = new QPushButton(widget);
        stopButton->setObjectName("stopButton");

        gridLayout->addWidget(stopButton, 0, 1, 1, 1);

        progressBar = new QProgressBar(widget);
        progressBar->setObjectName("progressBar");
        progressBar->setValue(24);

        gridLayout->addWidget(progressBar, 1, 0, 1, 2);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Mask", nullptr));
        browseButton->setText(QCoreApplication::translate("MainWindow", "Input path", nullptr));
        saveButton->setText(QCoreApplication::translate("MainWindow", "Save path", nullptr));
        deleteCheckBox->setText(QCoreApplication::translate("MainWindow", "delete", nullptr));
        key->setText(QCoreApplication::translate("MainWindow", "Key(16-hex)", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "mode", nullptr));
        conflictComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Overwrite", nullptr));
        conflictComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Counter", nullptr));

        label->setText(QCoreApplication::translate("MainWindow", "delay, sec", nullptr));
        timerCheckBox->setItemText(0, QCoreApplication::translate("MainWindow", "timer", nullptr));
        timerCheckBox->setItemText(1, QCoreApplication::translate("MainWindow", "ones", nullptr));

        maskLine->setText(QString());
        runButton->setText(QCoreApplication::translate("MainWindow", "run", nullptr));
        stopButton->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
