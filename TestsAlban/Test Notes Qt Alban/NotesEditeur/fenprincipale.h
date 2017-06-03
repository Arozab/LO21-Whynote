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
#include "notes.h"


class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
        FenPrincipale(NotesManager& m);
        //void load(QString f);

    public slots:
        //void ouvrirDialogue();
        void afficheNote(const QString& titre);
        //Notes& trouverNote(const QString& titre,NotesManager& m);

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
        QHBoxLayout* cid;
        QHBoxLayout* ctitre;
        QHBoxLayout* cdateCrea;
        QHBoxLayout* cdateModif;
        QVBoxLayout* ccentral;
        QDockWidget* dock;
        QLineEdit* idEdit;
        QLineEdit* titreEdit;
        QLineEdit* dateCreaEdit;
        QLineEdit* dateModifEdit;
        QString titre;


};

#endif
