#include <QApplication>
#include <QtWidgets>
#include "fenetrenewnote.h"
#include "fenetreprincipale.h"
#include "notes.h"
#include "notemanager.h"
#include "couplemanager.h"
#include <QFileDialog>



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString fichier = QFileDialog::getOpenFileName();
    NotesManager& m=NotesManager::getInstance();
    m.load(fichier);
    m.setFilename(fichier);

    QString fichier2 = QFileDialog::getOpenFileName();
    CoupleManager& m2=CoupleManager::getInstance();
    m2.load(fichier2);
    //m2.setFilename(fichier2);
    
    FenPrincipale& fenetre=FenPrincipale::getInstance();
    fenetre.show();

    return app.exec();
}
