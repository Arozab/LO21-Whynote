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


class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
        FenPrincipale(NotesManager& m);
        //void load(QString f);

    public slots:
        //void ouvrirDialogue();
        void afficheNote(QListWidgetItem* item);
        void activerEditer();
        void sauverNote();
    private slots:
        void activerSauver(QString str="");

    private:
        QWidget *zoneCentrale;
        QMenu *menuFichier;
        QAction *actionQuitter;
        QListWidget *liste;
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

        //Article* article;


};

#endif
