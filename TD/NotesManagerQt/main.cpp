/*#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include "Notes.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QWidget fenetre;
    QLabel idlabel("Identificateur",&fenetre);
    QLabel titrelabel("Titre",&fenetre);
    QLabel textlabel("Texte",&fenetre);
    QLineEdit id(&fenetre);
    QLineEdit titre(&fenetre);
    QTextEdit text(&fenetre);
    QPushButton sauver("Sauver",&fenetre);

    QHBoxLayout cid;
    cid.addWidget(&idlabel);
    cid.addWidget(&id);

    QHBoxLayout ctitre;
    ctitre.addWidget(&titrelabel);
    ctitre.addWidget(&titre);

    QHBoxLayout ctext;
    ctext.addWidget(&textlabel);
    ctext.addWidget(&text);

    QVBoxLayout couche;
    couche.addLayout(&cid);
    couche.addLayout(&ctitre);
    couche.addLayout(&ctext);
    couche.addWidget(&sauver);
    fenetre.setLayout(&couche);
    fenetre.show();

    QString filename = QFileDialog::getOpenFileName();
    NotesManager& m=NotesManager::getManager();
    m.setFilename(filename);
    m.load();
    Article& a=m.getArticle("id:citation_babage");
    id.setText(a.getId());
    titre.setText(a.getTitle());
    text.setText(a.getText());
    id.setDisabled(true);


    return app.exec();
}
*/
#include <QApplication>
#include <QString>
#include <QtWidgets>
#include "noteediteur.h"
#include "fenprincipale.h"
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QString fichier = QFileDialog::getOpenFileName();
    NotesManager& m=NotesManager::getManager();
    m.setFilename(fichier);
    m.load();
    Article& a=m.getArticle("id:to_read");
    ArticleEditeur fenetre(a);


    fenetre.show();
    return app.exec();
}

