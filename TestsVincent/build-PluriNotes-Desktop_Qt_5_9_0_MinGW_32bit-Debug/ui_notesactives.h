/********************************************************************************
** Form generated from reading UI file 'notesactives.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOTESACTIVES_H
#define UI_NOTESACTIVES_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NotesActives
{
public:
    QVBoxLayout *verticalLayout_2;
    QListWidget *listWidget;
    QPushButton *actualiser;

    void setupUi(QWidget *NotesActives)
    {
        if (NotesActives->objectName().isEmpty())
            NotesActives->setObjectName(QStringLiteral("NotesActives"));
        NotesActives->resize(400, 300);
        verticalLayout_2 = new QVBoxLayout(NotesActives);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        listWidget = new QListWidget(NotesActives);
        listWidget->setObjectName(QStringLiteral("listWidget"));

        verticalLayout_2->addWidget(listWidget);

        actualiser = new QPushButton(NotesActives);
        actualiser->setObjectName(QStringLiteral("actualiser"));

        verticalLayout_2->addWidget(actualiser);


        retranslateUi(NotesActives);

        QMetaObject::connectSlotsByName(NotesActives);
    } // setupUi

    void retranslateUi(QWidget *NotesActives)
    {
        NotesActives->setWindowTitle(QApplication::translate("NotesActives", "Form", Q_NULLPTR));
        actualiser->setText(QApplication::translate("NotesActives", "Actualiser", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class NotesActives: public Ui_NotesActives {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOTESACTIVES_H
