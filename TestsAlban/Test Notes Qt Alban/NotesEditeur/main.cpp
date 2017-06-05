#include <QApplication>
#include <QtWidgets>
#include "FenPrincipale.h"
#include "notes.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString fichier = QFileDialog::getOpenFileName();
    NotesManager& m=NotesManager::getInstance();
    m.load(fichier);
    FenPrincipale fenetre(m);
    fenetre.show();

    return app.exec();
}
