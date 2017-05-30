/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QWidget *centralWidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *ArticleEditeur;
    QHBoxLayout *Date;
    QVBoxLayout *DateCreation;
    QVBoxLayout *DateLastUpdate;
    QHBoxLayout *Titre;
    QHBoxLayout *Text;
    QMenuBar *menuBar;
    QMenu *menufile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(400, 300);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayoutWidget = new QWidget(centralWidget);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(110, 0, 171, 241));
        ArticleEditeur = new QVBoxLayout(verticalLayoutWidget);
        ArticleEditeur->setSpacing(6);
        ArticleEditeur->setContentsMargins(11, 11, 11, 11);
        ArticleEditeur->setObjectName(QStringLiteral("ArticleEditeur"));
        ArticleEditeur->setContentsMargins(0, 0, 0, 0);
        Date = new QHBoxLayout();
        Date->setSpacing(6);
        Date->setObjectName(QStringLiteral("Date"));
        DateCreation = new QVBoxLayout();
        DateCreation->setSpacing(6);
        DateCreation->setObjectName(QStringLiteral("DateCreation"));

        Date->addLayout(DateCreation);

        DateLastUpdate = new QVBoxLayout();
        DateLastUpdate->setSpacing(6);
        DateLastUpdate->setObjectName(QStringLiteral("DateLastUpdate"));

        Date->addLayout(DateLastUpdate);


        ArticleEditeur->addLayout(Date);

        Titre = new QHBoxLayout();
        Titre->setSpacing(6);
        Titre->setObjectName(QStringLiteral("Titre"));

        ArticleEditeur->addLayout(Titre);

        Text = new QHBoxLayout();
        Text->setSpacing(6);
        Text->setObjectName(QStringLiteral("Text"));

        ArticleEditeur->addLayout(Text);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 21));
        menufile = new QMenu(menuBar);
        menufile->setObjectName(QStringLiteral("menufile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menufile->menuAction());
        menufile->addAction(actionOpen);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        menufile->setTitle(QApplication::translate("MainWindow", "file", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
