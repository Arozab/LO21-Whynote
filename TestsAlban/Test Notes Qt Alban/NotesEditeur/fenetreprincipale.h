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
    EditeurNote* getEditeurNote() { return editnote;}
    void setEditeurNote(EditeurNote* fen) { editnote=fen;}

    void actualiserNote();
    //void actualiserTache();
    //void actualiserArchive();

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
        QDockWidget* dockCouple;
        QListWidget *listeNote;
        QListWidget *listeCouple;
        QListWidget *listeTache;
        QListWidget *listeArchive;
        QComboBox *listeVersion;

        QMenu *menuFichier;
        QMenu* menuNote;
        QMenu *menuNouveau;

        QAction *actionQuitter;
        QAction* supprimer;
        QAction* restaurer;
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
        void afficherNewArticle();
        void afficherNewTache();
        void afficherNewNoteFichier();

        //void supprimerNote();
        //void archiverNote();
        //void viderCorbeille() { NotesManager::recupererInstance().viderCorbeille(); }
        //void quitter(); // demande si vider corbeille puis quitte
};

#endif
