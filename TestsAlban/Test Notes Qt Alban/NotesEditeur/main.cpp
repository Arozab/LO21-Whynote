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
    QString fichier = QFileDialog::getOpenFileName(nullptr,"Selectionner le fichier de Notes");
    NotesManager& m=NotesManager::getInstance();
    m.load(fichier);
    m.setFilename(fichier);

    QString fichier2 = QFileDialog::getOpenFileName(nullptr,"Selectionner le fichier de Couples");
    CoupleManager& m2=CoupleManager::getInstance();
    m2.load(fichier2);
    //m2.setFilename(fichier2);
    
    FenPrincipale& fenetre=FenPrincipale::getInstance();
   // fenetre.setMinimumSize(1000,650);
    fenetre.setWindowState(Qt::WindowMaximized);
    fenetre.show();

    return app.exec();
}
