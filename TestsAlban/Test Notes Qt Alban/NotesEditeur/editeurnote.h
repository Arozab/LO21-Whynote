#ifndef EDITEURNOTE_H
#define EDITEURNOTE_H

#include <QtWidgets>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include <QXmlStreamReader>
#include <QFile>
#include <QLabel>
#include <QListWidget>
#include <QDockWidget>
#include <QMenu>
#include <QLineEdit>
#include <QListWidgetItem>
#include "notes.h"
#include "notemanager.h"


class EditeurNote : public QWidget {
    Q_OBJECT
    friend class NotesManager;
protected :
    // ---- Label -----
    QLabel* idlabel;
    QLabel* titrelabel;
    QLabel* dateCrealabel;
    QLabel* dateModiflabel;
    // ---- Edit ----
    QLineEdit* idEdit;
    QLineEdit* titreEdit;
    QLineEdit* dateCreaEdit;
    QLineEdit* dateModifEdit;
    // ---- Bouton ----
    QPushButton* editer;
    QPushButton* sauver;
    QPushButton* restaurer;
    QComboBox* listeVersion;
    QPushButton* supprimer;
    QPushButton* annuler;
    // --- Layout ---
    QHBoxLayout* ctype;
    QHBoxLayout* cid;
    QHBoxLayout* cdateCrea;
    QHBoxLayout* cdateModif;
    QHBoxLayout* ctitre;
    QHBoxLayout* cboutons;
    QVBoxLayout* crestaurer;
    QHBoxLayout* cboutonEdition;
    QVBoxLayout* zone;

    //OldVersionsWindow* ovw;
    //QHBoxLayout* versionLayout;
    //QLabel* versionLabel;
    //QLineEdit* version;

public:
    EditeurNote(Notes* n, QWidget* parent=0);
    //EditeurNote(QString type,QString titre,QWidget* parent=0);
    virtual ~EditeurNote(){}

signals :

public slots :
//    virtual void toDustbin() = 0;
//    virtual void showOldVersionsWindow() = 0;
//    void updateNotesManager();
//    void updateArchivesManager();
//    void updateTaskManager();
//    void setEmptyCentralWidget();
    virtual void activerEditer();
    virtual void annuleEdition();
    virtual void supprime()=0;
    virtual void supprimeNote();
    virtual void restaureNote();
    virtual void sauverNote()=0;
    //void editerNote();
    void restaure();
    //virtual void actualiserNote() = 0;
    //virtual void actualiserTache()=0;
    //virtual void actualiserArchive()=0;
private slots :
    void activerSauver();
};

class ArticleEditeur : public EditeurNote {
Q_OBJECT
private:
    Article* article;
    // ---- Label -----
    QLabel* textlabel;
    // ---- Edit ----
    QTextEdit* textEdit;
    // --- Layout ---
    QHBoxLayout* ctext;
public:
    explicit ArticleEditeur(Article* a,QWidget* parent=0);
    ~ArticleEditeur(){};
    void supprime();
public slots:
    void sauverNote();
    void activerEditer();
    void annuleEdition();

};

class TacheEditeur : public EditeurNote {
Q_OBJECT
private:
    Tache* tache;
    // ---- Label -----
    QLabel* actionlabel;
    QLabel* prioritelabel;
    QLabel* dateEchlabel;
    QLabel* statutlabel;
    // ---- Edit ----
    QLineEdit* actionEdit;
    QLineEdit* prioriteEdit;
    QLineEdit* dateEchEdit;
    QLineEdit* statutEdit;
    // --- Layout ---
    QHBoxLayout* caction;
    QHBoxLayout* cpriorite;
    QHBoxLayout* cdateEch;
    QHBoxLayout* cstatut;
public:
    explicit TacheEditeur(Tache* a,QWidget* parent=0);
    ~TacheEditeur(){};
    void supprime();
public slots:
    void sauverNote();
    void activerEditer();
    void annuleEdition();
};

class NoteFichierEditeur : public EditeurNote {
Q_OBJECT
private:
    NoteAvecFichier* noteFichier;
    // ---- Label -----
    QLabel* descriptionlabel;
    QLabel* filelabel;
    // ---- Edit ----
    QTextEdit* descriptionEdit;
    QLineEdit* fileEdit;
    // --- Layout ---
    QHBoxLayout* cdescription;
    QHBoxLayout* cfile;
public:
    explicit NoteFichierEditeur(NoteAvecFichier* a,QWidget* parent=0);
    ~NoteFichierEditeur(){};
    void supprime();
public slots:
    void sauverNote();
    void activerEditer();
    void annuleEdition();

};

#endif // EDITEURNOTE_H
