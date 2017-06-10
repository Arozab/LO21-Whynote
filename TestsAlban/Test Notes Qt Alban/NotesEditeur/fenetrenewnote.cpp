#include "notes.h"
#include "fenetrenewnote.h"

FenetreNewArticle::FenetreNewArticle(QWidget* parent): QWidget(parent) {
    pere=parent;
    titrelabel=new QLabel("titre",this);
    textlabel=new QLabel("texte",this);
    titreEdit=new QLineEdit(this);
    textEdit=new QTextEdit(this);

    ctext = new QHBoxLayout;
    ctext->addWidget(textlabel);
    ctext->addWidget(textEdit);
    ctitre = new QHBoxLayout;
    ctitre->addWidget(titrelabel);
    ctitre->addWidget(titreEdit);

    ajouter=new QPushButton("Ajouter",this);
    cboutons = new QHBoxLayout;
    cboutons->addWidget(ajouter);

    ccentral= new QVBoxLayout;
    ccentral->addLayout(ctitre);
    ccentral->addLayout(ctext);
    ccentral->addLayout(cboutons);
    setLayout(ccentral);

    QObject::connect(ajouter,SIGNAL(clicked()),pere,SLOT(creerArticle()));
}
FenetreNewTask::FenetreNewTask(QWidget* parent): QWidget(parent) {

}
FenetreNewNoteFichier::FenetreNewNoteFichier(QWidget* parent): QWidget(parent) {

}

