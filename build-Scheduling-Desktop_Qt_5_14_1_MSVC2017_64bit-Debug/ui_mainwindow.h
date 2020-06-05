/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPlainTextEdit *PeriodicTextEdit;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QPlainTextEdit *AperiodicTextEdit;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_7;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QPlainTextEdit *capacityText;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_6;
    QPlainTextEdit *periodText;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *BackgroundButton;
    QPushButton *PollingButton;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_8;
    QLabel *label_10;
    QLabel *label_11;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *GanttChart;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_9;
    QLineEdit *DelayTime;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1236, 539);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_5 = new QHBoxLayout(centralwidget);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(-1, -1, -1, 18);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        PeriodicTextEdit = new QPlainTextEdit(centralwidget);
        PeriodicTextEdit->setObjectName(QString::fromUtf8("PeriodicTextEdit"));

        verticalLayout->addWidget(PeriodicTextEdit);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);


        horizontalLayout_2->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        AperiodicTextEdit = new QPlainTextEdit(centralwidget);
        AperiodicTextEdit->setObjectName(QString::fromUtf8("AperiodicTextEdit"));
        AperiodicTextEdit->setLayoutDirection(Qt::LeftToRight);
        AperiodicTextEdit->setFrameShape(QFrame::StyledPanel);
        AperiodicTextEdit->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(AperiodicTextEdit);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout_6->addLayout(horizontalLayout_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(-1, 12, -1, -1);
        label_7 = new QLabel(centralwidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_5);

        capacityText = new QPlainTextEdit(centralwidget);
        capacityText->setObjectName(QString::fromUtf8("capacityText"));
        capacityText->setMaximumSize(QSize(500, 30));
        capacityText->setInputMethodHints(Qt::ImhDigitsOnly);

        verticalLayout_3->addWidget(capacityText);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_6 = new QLabel(centralwidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setFrameShape(QFrame::NoFrame);
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_6);

        periodText = new QPlainTextEdit(centralwidget);
        periodText->setObjectName(QString::fromUtf8("periodText"));
        periodText->setMaximumSize(QSize(500, 30));
        periodText->setInputMethodHints(Qt::ImhDigitsOnly);

        verticalLayout_4->addWidget(periodText);


        horizontalLayout->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        BackgroundButton = new QPushButton(centralwidget);
        BackgroundButton->setObjectName(QString::fromUtf8("BackgroundButton"));

        horizontalLayout_3->addWidget(BackgroundButton);

        PollingButton = new QPushButton(centralwidget);
        PollingButton->setObjectName(QString::fromUtf8("PollingButton"));

        horizontalLayout_3->addWidget(PollingButton);


        verticalLayout_6->addLayout(horizontalLayout_3);


        verticalLayout_9->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_8 = new QLabel(centralwidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_7->addWidget(label_8);

        label_10 = new QLabel(centralwidget);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        verticalLayout_7->addWidget(label_10);

        label_11 = new QLabel(centralwidget);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        verticalLayout_7->addWidget(label_11);


        verticalLayout_9->addLayout(verticalLayout_7);


        horizontalLayout_5->addLayout(verticalLayout_9);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(18, -1, -1, -1);
        GanttChart = new QTableWidget(centralwidget);
        GanttChart->setObjectName(QString::fromUtf8("GanttChart"));
        GanttChart->setMinimumSize(QSize(650, 380));
        GanttChart->setTextElideMode(Qt::ElideRight);
        GanttChart->horizontalHeader()->setVisible(false);
        GanttChart->horizontalHeader()->setHighlightSections(false);
        GanttChart->verticalHeader()->setVisible(false);
        GanttChart->verticalHeader()->setHighlightSections(false);

        verticalLayout_8->addWidget(GanttChart);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_9 = new QLabel(centralwidget);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_4->addWidget(label_9);

        DelayTime = new QLineEdit(centralwidget);
        DelayTime->setObjectName(QString::fromUtf8("DelayTime"));

        horizontalLayout_4->addWidget(DelayTime);


        verticalLayout_8->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_8);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1236, 26));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Periodic Tasks", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\354\210\230\355\226\211\354\213\234\352\260\204 \354\243\274\352\270\260\n"
"\354\210\230\355\226\211\354\213\234\352\260\204 \354\243\274\352\270\260 \354\235\230 \355\230\225\355\203\234\353\241\234 \354\236\205\353\240\245", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Aperiodic Tasks", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\354\210\230\355\226\211\354\213\234\352\260\204 \353\217\204\354\260\251\354\213\234\352\260\204\n"
"\354\210\230\355\226\211\354\213\234\352\260\204 \353\217\204\354\260\251\354\213\234\352\260\204 \354\235\230 \355\230\225\355\203\234\353\241\234 \354\236\205\353\240\245", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Polling Server Tasks", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "capacity", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Period", nullptr));
        BackgroundButton->setText(QCoreApplication::translate("MainWindow", "Background APS", nullptr));
        PollingButton->setText(QCoreApplication::translate("MainWindow", "Polling server APS", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\354\210\230\355\226\211\354\213\234\352\260\204\352\263\274 \354\243\274\352\270\260, \354\210\230\355\226\211\354\213\234\352\260\204\352\263\274 \353\217\204\354\260\251\354\213\234\352\260\204\354\235\200 \355\225\230\353\202\230\354\235\230 \352\263\265\353\260\261\354\234\274\353\241\234\353\247\214 \352\265\254\353\266\204\353\220\230\354\226\264\354\225\274 \355\225\234\353\213\244.", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\352\260\201 Task\353\212\224 \355\225\230\353\202\230\354\235\230 \352\260\234\355\226\211\353\254\270\354\236\220\353\241\234\353\247\214 \352\265\254\353\266\204\353\220\230\354\226\264\354\225\274 \355\225\234\353\213\244.", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\352\260\201 Task\353\212\224 \354\236\205\353\240\245 \354\210\234\354\234\274\353\241\234 1\353\266\200\355\204\260 \354\235\264\353\246\204\354\235\264 \353\247\244\352\262\250\354\247\204\353\213\244.(Periodic: Pn, Aperiodic:APn)", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\355\217\211\352\267\240 \354\247\200\354\227\260\354\213\234\352\260\204", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
