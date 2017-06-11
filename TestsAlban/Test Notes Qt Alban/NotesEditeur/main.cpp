#include <QApplication>
#include <QtWidgets>
#include "fenetrenewnote.h"
#include "fenetreprincipale.h"
#include "notes.h"
#include "notemanager.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString fichier = QFileDialog::getOpenFileName();
    NotesManager& m=NotesManager::getInstance();
    m.load(fichier);
    m.setFilename(fichier);
    FenPrincipale& fenetre=FenPrincipale::getInstance();
    fenetre.show();

    return app.exec();
}
