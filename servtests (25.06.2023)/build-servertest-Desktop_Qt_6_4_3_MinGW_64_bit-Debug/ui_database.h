/********************************************************************************
** Form generated from reading UI file 'database.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATABASE_H
#define UI_DATABASE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_DataBase
{
public:

    void setupUi(QDialog *DataBase)
    {
        if (DataBase->objectName().isEmpty())
            DataBase->setObjectName("DataBase");
        DataBase->resize(400, 300);

        retranslateUi(DataBase);

        QMetaObject::connectSlotsByName(DataBase);
    } // setupUi

    void retranslateUi(QDialog *DataBase)
    {
        DataBase->setWindowTitle(QCoreApplication::translate("DataBase", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataBase: public Ui_DataBase {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATABASE_H
