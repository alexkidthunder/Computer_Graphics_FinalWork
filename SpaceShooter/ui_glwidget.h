/********************************************************************************
** Form generated from reading UI file 'glwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GLWIDGET_H
#define UI_GLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_glwidget
{
public:

    void setupUi(QWidget *glwidget)
    {
        if (glwidget->objectName().isEmpty())
            glwidget->setObjectName(QString::fromUtf8("glwidget"));
        glwidget->resize(243, 400);
        glwidget->setMinimumSize(QSize(200, 400));

        retranslateUi(glwidget);

        QMetaObject::connectSlotsByName(glwidget);
    } // setupUi

    void retranslateUi(QWidget *glwidget)
    {
        glwidget->setWindowTitle(QCoreApplication::translate("glwidget", "glwidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class glwidget: public Ui_glwidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GLWIDGET_H
