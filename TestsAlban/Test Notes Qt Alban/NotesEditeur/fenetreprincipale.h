#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

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
#include "fenetrenewnote.h"
#include "editeurnote.h"

#include <QComboBox>
#include <QGridLayout>


class FenPrincipale : public QMainWindow
{
    Q_OBJECT
public:   
    static FenPrincipale& getInstance();
    static void libererInstance();
    //void load(QString f);
    void afficherCreerNote(FenetreNewNote* fen);
    FenetreNewNote* getFenNewNote() { return fenNewNote;}
    void setFenNewNote(FenetreNewNote* fen) { fenNewNote=fen;}

    //void afficherStandard();

private:
        QWidget *zoneCentrale;
        QGridLayout* ccentral;
        FenetreNewNote* fenNewNote;
        EditeurNote* editnote;
        // ... 
        /// ... puis toutes les autres type de fenetre

        QDockWidget* dockNote;
        QDockWidget* dockTache;
        QDockWidget* dockArchive;
        QListWidget *listeNote;
        QListWidget *listeTache;
        QListWidget *listeArchive;
        QComboBox *listeVersion;

        QMenu *menuFichier;
        QMenu* menuNote;
        QMenu *menuNouveau;

        QAction *actionQuitter;
        QAction* supprimer;
        QAction* restaurer;
        //QAction* editer;
        //QAction* 
        //QAction *ajouterNote;
        QAction *ajouterArticle;
        QAction *ajouterTache;
        QAction *ajouterNoteFichier;

        FenPrincipale();
    ///La structure Handler permet de gérer les appels de l'instance unique du singleton ainsi que sa destruction
    struct FenPHandler{
        FenPrincipale* instance;
        FenPHandler() : instance(0){}
        ~FenPHandler(){if(instance) delete instance; instance = 0;}
    };
    static FenPHandler fenP_handler;

public slots:
        //void ouvrirDialogue();
        void afficheNote(QListWidgetItem* item);
        //void creerNote();
        //void creerArticle();
        //void creerTache();
        //void creerNoteFichier();
        void afficherNewArticle();
        void afficherNewTache();
        void afficherNewNoteFichier();

        //void actualiserNote();
        //void actualiserTache();
        //void actualiserArchive();

        //void supprimerNote();
        //void archiverNote();
        //void viderCorbeille() { NotesManager::recupererInstance().viderCorbeille(); }
        //void quitter(); // demande si vider corbeille puis quitte



/*      QLabel* idlabel;
        QLabel* titrelabel;
        QLabel* dateCrealabel;
        QLabel* dateModiflabel;
        QLabel* textlabel;
        QLabel* descriptionlabel;
        QLabel* filelabel;
        QLabel* actionlabel;
        QLabel* prioritelabel;
        QLabel* dateEchlabel;
        QLabel* statutlabel;

        QHBoxLayout* cid;
        QHBoxLayout* ctitre;
        QHBoxLayout* cdateCrea;
        QHBoxLayout* cdateModif;
        QHBoxLayout* ctext;
        QHBoxLayout* cdescription;
        QHBoxLayout* cfile;
        QHBoxLayout* cboutons;
        QHBoxLayout* caction;
        QHBoxLayout* cpriorite;
        QHBoxLayout* cdateEch;
        QHBoxLayout* cstatut;*/

/*        QVBoxLayout* ccentral;
        QVBoxLayout* cboutonRestauration;

        QLineEdit* idEdit;
        QLineEdit* titreEdit;
        QLineEdit* dateCreaEdit;
        QLineEdit* dateModifEdit;
        QTextEdit* textEdit;
        QTextEdit* descritionEdit;
        QLineEdit* fileEdit;
        QLineEdit* actionEdit;
        QLineEdit* prioriteEdit;
        QLineEdit* dateEchEdit;
        QLineEdit* statutEdit;
        QString titre;

        QPushButton* editer;
        QPushButton* sauver;
		QPushButton* restaurer;
        QPushButton* ajouter;
        QPushButton* ajoutTache;
        QPushButton* ajoutNoteFichier;
        QHBoxLayout* cboutonAjouter;
        QHBoxLayout* cboutonAjouterNoteFichier;
        QHBoxLayout* cboutonAjouterTache;*/

        //Article* article;


};

/*class afficheCreerNote() : public QWidget {
    QLineEdit *id;
    QLineEdit *titre;
    QDateTimeEdit *dateCrea;
public:
    void afficheCreerNote();
    QString getId() { return id->Text(); }
};

class CreerNote() : public QWidget {
private:
    // ---- Label -----
    QLabel* idlabel;
    QLabel* titrelabel;
    QLabel* textlabel;
    QLabel* descriptionlabel;
    QLabel* filelabel;
    QLabel* actionlabel;
    QLabel* prioritelabel;
    QLabel* dateEchlabel;
    QLabel* statutlabel;
    QLabel* typelabel;
    // ---- Edit ---- 
    QLineEdit* idEdit;
    QLineEdit* titreEdit;
    QTextEdit* textEdit;
    QTextEdit* descritionEdit;
    QLineEdit* fileEdit;
    QLineEdit* actionEdit;
    QLineEdit* prioriteEdit;
    QDateTimeEdit* dateEchEdit;
    QLineEdit* statutEdit;    
    QComboBox* typeEdit;
    // ---- Bouton ----
    QPushButton* valider;
    QPushButton* annuler;
    // --- Layout --- 
    QHBoxLayout* cid;
    QHBoxLayout* ctitre;
    QHBoxLayout* ctext;
    QHBoxLayout* cdescription;
    QHBoxLayout* cfile;
    QHBoxLayout* caction;
    QHBoxLayout* cpriorite;
    QHBoxLayout* cdateEch;
    QHBoxLayout* cstatut;
    QHBoxLayout* ctype;
    QHBoxLayout* cboutons;
    QVBoxLayout* zone;

public:
    CreerNote();
    QString getId() { return id->text(); }

public slots:
    QString createNote(QString type);
    void createContenuNote(QString type);

}*/

#endif
