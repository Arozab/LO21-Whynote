/********************************************************************************
** Form generated from reading UI file 'noteview.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTEVIEW_H
#define UI_NOTEVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NoteView
{
public:
    QVBoxLayout *verticalLayout;
    QLineEdit *lineEdit;
    QTextEdit *textEdit;

    void setupUi(QWidget *NoteView)
    {
        if (NoteView->objectName().isEmpty())
            NoteView->setObjectName(QStringLiteral("NoteView"));
        NoteView->resize(400, 300);
        verticalLayout = new QVBoxLayout(NoteView);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        lineEdit = new QLineEdit(NoteView);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        textEdit = new QTextEdit(NoteView);
        textEdit->setObjectName(QStringLiteral("textEdit"));

        verticalLayout->addWidget(textEdit);


        retranslateUi(NoteView);

        QMetaObject::connectSlotsByName(NoteView);
    } // setupUi

    void retranslateUi(QWidget *NoteView)
    {
        NoteView->setWindowTitle(QApplication::translate("NoteView", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NoteView: public Ui_NoteView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTEVIEW_H
