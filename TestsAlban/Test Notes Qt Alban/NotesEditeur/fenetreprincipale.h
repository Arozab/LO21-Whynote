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
#include "fenetrecorbeille.h"

#include <QComboBox>
#include <QGridLayout>

/*! \class FenPrincipale
   * \brief Classe qui gère tous les éléments de l'affichage principal
*/
class FenPrincipale : public QMainWindow
{
    Q_OBJECT


public: 

    /*!
         *  \brief On récupère l'unique instance de fenêtre principale
         *  \return Une reference vers FenPrincpale
         */  

    static FenPrincipale& getInstance();

    /*!
     *  \brief Libère l'unique instance de la fenêtre principale
     *  \return void
    */
    static void libererInstance();
    /*!
     *  \brief On construit la fenêtre de création d'une nouvelle note
     *  \param fen : pointeur vers FenetreNewNote
     *  \return void
     */
    void afficherCreerNote(FenetreNewNote* fen);

    /*!
     *  \brief On récupère la fenêtre de création d'une nouvelle note
     *  \return FenetreNewNote*
     */
    FenetreNewNote* getFenNewNote() { return fenNewNote;}

    /*!
     *  \brief Permet la modification de la fenêtre de création d'une nouvelle note
     *  \param fen : pointeur vers FenetreNewNote
     *  \return void
     */
    void setFenNewNote(FenetreNewNote* fen) { fenNewNote=fen;}

    /*!
     *  \brief Permet de récupérer l'éditeur de notes
     *  \return EditeurNote*
     */
    EditeurNote* getEditeurNote() { return editnote;}

    /*!
     *  \brief Permet de modifier l'éditeur de notes
     *  \param fen : EditeurNote*
     *  \return void
     */
    void setEditeurNote(EditeurNote* fen) { editnote=fen;}

    /*!
     *  \brief Actualise la note
     *  \return void
     */
    void actualiserNote();
    //void actualiserTache();
    //void actualiserArchive();

    //void afficherStandard();

private:
        QWidget *zoneCentrale;
        QGridLayout* ccentral;
        FenetreNewNote* fenNewNote;
        EditeurNote* editnote;
        FenetreCorbeille* corbeil;
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
        QMenu* menuCorbeille;

        QAction *actionQuitter;
        QAction* restaurer;
        QAction *ajouterArticle;
        QAction *ajouterTache;
        QAction *ajouterNoteFichier;
        QAction* montrerCorbeille;

        FenPrincipale();
    ///La structure Handler permet de gérer les appels de l'instance unique du singleton ainsi que sa destruction
    struct FenPHandler{
        FenPrincipale* instance;
        FenPHandler() : instance(0){}
        ~FenPHandler(){if(instance) delete instance; instance = 0;}
    };
    static FenPHandler fenP_handler;

public slots:
        
    /*!
     *  \brief Met en place l'affichage pour une note
     *  \param item : QListWidgetItem* (widget à modifier)
     *  \return void
     */
    void afficheNote(QListWidgetItem* item);

    /*!
     *  \brief Met en place l'affichage pour un nouvel article
     *  \return void
     */
    void afficherNewArticle();

    /*!
     *  \brief Met en place l'affichage pour une nouvelle tache
     *  \return void
     */
    void afficherNewTache();

    /*!
     *  \brief Met en place l'affichage pour une nouvelle note avec fichier
     *  \return void
     */
    void afficherNewNoteFichier();

    /*!
     *  \brief Met en place l'affichage pour la corbeille
     *  \return void
     */
    void afficherCorbeille();

    //void supprimerNote();
    //void archiverNote();
    //void viderCorbeille() { NotesManager::recupererInstance().viderCorbeille(); }
    //void quitter(); // demande si vider corbeille puis quitte
};

#endif
