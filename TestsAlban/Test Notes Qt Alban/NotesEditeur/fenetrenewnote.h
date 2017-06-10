#ifndef FENETRENEWNOTE_H
#define FENETRENEWNOTE_H

#include <QtWidgets>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QFile>
#include <QLabel>
#include <QListWidget>
#include <QDockWidget>
#include <QMenu>
#include <QLineEdit>
#include <QListWidgetItem>
#include "notes.h"

class FenetreNewArticle : public QWidget {

    Q_OBJECT
    public:
    explicit FenetreNewArticle(QWidget* parent=0);
    QPushButton* getBouton() { return ajouter;}
private:
    QWidget* pere;
    QVBoxLayout* ccentral;
    QPushButton* ajouter;
    QHBoxLayout* cboutons;
    QLabel* titrelabel;
    QLabel* textlabel;
    QHBoxLayout* ctitre;
    QHBoxLayout* ctext;
    QLineEdit* titreEdit;
    QTextEdit* textEdit;
public slots:
};

class FenetreNewTask : public QWidget {

    Q_OBJECT
    public:
    explicit FenetreNewTask(QWidget* parent=0);
private:
    QPushButton* ajouter;

};

class FenetreNewNoteFichier : public QWidget {

    Q_OBJECT
    public:
    explicit FenetreNewNoteFichier(QWidget* parent=0);

};
#endif // FENETRENEWNOTE_H
