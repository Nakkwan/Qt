/********************************************************************************
** Form generated from reading UI file 'secwin.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SECWIN_H
#define UI_SECWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_SecWin
{
public:

    void setupUi(QDialog *SecWin)
    {
        if (SecWin->objectName().isEmpty())
            SecWin->setObjectName(QString::fromUtf8("SecWin"));
        SecWin->resize(400, 300);

        retranslateUi(SecWin);

        QMetaObject::connectSlotsByName(SecWin);
    } // setupUi

    void retranslateUi(QDialog *SecWin)
    {
        SecWin->setWindowTitle(QCoreApplication::translate("SecWin", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SecWin: public Ui_SecWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SECWIN_H
