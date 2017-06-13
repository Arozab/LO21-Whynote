#include "corbeille.h"
#include "fenetrecorbeille.h"

#include <QDebug>

FenetreCorbeille::FenetreCorbeille(QWidget* parent){
    notesSupp = new QListWidget();
    for(unsigned int i=0;i<Corbeille::getInstance().getSize();i++){
        Notes* n = Corbeille::getInstance().getNotePosition(i);
        QString titre = n->getTitre();
        qDebug()<<"titre supprime : "<<titre<<"\n";
        notesSupp->addItem(titre);
    }

    supprimer = new QPushButton("Supprimer");
    vider = new QPushButton("Vider");
    restaurer = new QPushButton("Restaurer");

    supprimer->setEnabled(false);
    restaurer->setEnabled(false);

    QObject::connect(vider, SIGNAL(clicked()), this, SLOT(viderCorbeille()));
    QObject::connect(supprimer, SIGNAL(clicked()), this, SLOT(supprimerNote()));
    QObject::connect(notesSupp, SIGNAL(itemSelectionChanged()), this, SLOT(activerBouton()));
    QObject::connect(restaurer, SIGNAL(clicked()), this, SLOT (restaurerNote()));

    cbouton =new QHBoxLayout();
    cvider = new QHBoxLayout();
    zone = new QVBoxLayout();
    liste = new QScrollArea();
    cliste = new QHBoxLayout();

    liste->setWidget(notesSupp);
    cliste->addWidget(liste);
    cbouton->addWidget(supprimer);
    cbouton->addWidget(restaurer);
    cvider->addWidget(vider);

    zone->addLayout(cliste);
    zone->addLayout(cbouton);
    zone->addLayout(cvider);
    setLayout(zone);
}

void FenetreCorbeille::supprimerNote(){
    if(!notesSupp->currentItem() == 0){
        Corbeille& c =Corbeille::getInstance();
        QListWidgetItem* selectedItem = notesSupp->currentItem() ;
        Notes* n = c.getNoteTitre(selectedItem->text());
        c.supprimerNote(n);
        this->actualiserCorbeille();
    }
    else {
        QMessageBox::information(this,"Erreur","Pas de notes à supprimer");
    }
}

void FenetreCorbeille::viderCorbeille(){
    Corbeille::getInstance().vider();
    notesSupp->clear();
}

void FenetreCorbeille::activerBouton(){
    supprimer->setEnabled(true);
    restaurer->setEnabled(true);
}


Notes* FenetreCorbeille::restaurerNote(){
    if(!notesSupp->currentItem() == 0){
        Corbeille& c =Corbeille::getInstance();
        QListWidgetItem* selectedItem = notesSupp->currentItem() ;
        Notes* n = c.getNoteTitre(selectedItem->text());
        c.restaurerNote(n);
        this->actualiserCorbeille();
        return n;
    }
    else {
        QMessageBox::information(this,"Erreur","Pas de notes");
    }
}

void FenetreCorbeille::actualiserCorbeille() {
    Corbeille& c = Corbeille::getInstance();
    notesSupp->clear();
    for(unsigned int i=0;i<c.getSize();i++){
        Notes* n = c.getNotePosition(i);
        QString titre = n->getTitre();
        notesSupp->addItem(titre);
    }
}


