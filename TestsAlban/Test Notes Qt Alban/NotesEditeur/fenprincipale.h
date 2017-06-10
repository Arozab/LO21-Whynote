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


class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
        FenPrincipale(NotesManager& m);     
        //void load(QString f);
        void afficherCreerNote();
        void afficherStandard();
        
    public slots:
        //void ouvrirDialogue();
        void afficheNote(QListWidgetItem* item);
        void activerEditer();
        void sauverNote();
        void afficherCreerArticle();
        void afficherCreerTache();
        void afficherCreerNoteFichier();
        void creerArticle();
        void creerTache();
        void creerNoteFichier();

    private slots:
        void activerSauver(QString str="");

    private:
        QWidget *zoneCentrale;
        QMenu *menuFichier;
        QAction *actionQuitter;

        QMenu *menuNouveau;
        QAction *ajouterArticle;
        QAction *ajouterTache;
        QAction *ajouterNoteFichier;

        QListWidget *listeNote;
        QListWidget *listeTache;
        QListWidget *listeArchive;
        QComboBox *listeVersion;
        QPushButton* bouton1;
        QVBoxLayout* pg;
        QLabel* idlabel;
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
        QHBoxLayout* cstatut;
        QVBoxLayout* ccentral;
		QVBoxLayout* cboutonRestauration;
        QDockWidget* dock;
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
        QHBoxLayout* cboutonAjouterTache;

        //Article* article;


};

#endif
