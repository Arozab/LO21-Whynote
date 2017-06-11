#include "notes.h"
#include "notemanager.h"
#include "editeurnote.h"

//EditeurNote::EditeurNote(QString type, QString titre,QWidget* parent) {

//    qDebug()<<"la ça marche\n";
//    NotesManager& m=NotesManager::recupererInstance();
//    NotesManager::Iterator it=m.getIterator();
//    while(!it.isDone() && it.current().getTitre()!=titre){
//        it.next();
//    }
//    qDebug()<<"la aussi\n";

//    if(!it.isDone()){

//        qDebug()<<"et puis la aussi\n";
//        idlabel = new QLabel("ID : ");
//        titrelabel = new QLabel("Titre : ");
//        dateCrealabel = new QLabel("Date Creation  :");
//        dateModiflabel = new QLabel("Date Modification : ");

//        idEdit = new QLineEdit();
//        titreEdit = new QLineEdit();
//        dateCreaEdit = new QLineEdit();
//        dateModifEdit = new QLineEdit();

//        sauver = new QPushButton("Sauver");
//        editer = new QPushButton("Editer");
//        restaurer = new QPushButton("Restaurer");

//        cid = new QHBoxLayout();
//        ctitre = new QHBoxLayout();
//        cdateCrea = new QHBoxLayout();
//        cdateModif = new QHBoxLayout();
//        cboutons = new QHBoxLayout();
//        cboutonRestauration = new QVBoxLayout();
//        zone = new QVBoxLayout();

//        cid->addWidget(idlabel);
//        cid->addWidget(idEdit);
//        ctitre->addWidget(titrelabel);
//        ctitre->addWidget(titreEdit);
//        cdateCrea->addWidget(dateCrealabel);
//        cdateCrea->addWidget(dateCreaEdit);
//        cdateModif->addWidget(dateModiflabel);
//        cdateModif->addWidget(dateModifEdit);
//        cboutons->addWidget(sauver);
//        cboutons->addWidget(editer);
//        cboutons->addWidget(restaurer);

//        zone->addLayout(cid);
//        zone->addLayout(ctitre);
//        zone->addLayout(cdateCrea);
//        zone->addLayout(cdateModif);

//        idEdit->setText(it.current().getId());
//        titreEdit->setText(it.current().getTitre());
//        dateCreaEdit->setText(it.current().getDateCrea());
//        dateModifEdit->setText(it.current().getDateModif());

//        idEdit->setDisabled(true);
//        titreEdit->setDisabled(true);
//        dateCreaEdit->setDisabled(true);
//        dateModifEdit->setDisabled(true);

//        sauver->setDisabled(true);
//        restaurer->setDisabled(true);
//        qDebug()<<"ici ça marche\n";

//        if(type=="7Article"){
//            textlabel = new QLabel("Texte :");
//            textEdit = new QTextEdit();

//            ctext = new QHBoxLayout();

//            ctext->addWidget(textlabel);
//            ctext->addWidget(textEdit);

//            zone->addLayout(ctext);

//            Notes* n=it.current().clone();
//            Article& a1 = dynamic_cast<Article&>(*n);
//            textEdit->setText(a1.getText());
//            textEdit->setDisabled(true);

//            QObject::connect(textEdit,SIGNAL(textChanged()),this,SLOT(activerSauver()));
//        }
//        else if(type=="5Tache"){
//            statutlabel = new QLabel("Statut :");
//            actionlabel = new QLabel("Action :");
//            prioritelabel = new QLabel("Priorite :");
//            dateEchlabel = new QLabel("Date d'echeance' :");

//            statutEdit = new QLineEdit();
//            actionEdit = new QLineEdit();
//            prioriteEdit = new QLineEdit();
//            dateEchEdit = new QLineEdit();

//            cstatut = new QHBoxLayout();
//            caction = new QHBoxLayout();
//            cpriorite = new QHBoxLayout();
//            cdateEch = new QHBoxLayout();

//            cstatut->addWidget(statutlabel);
//            cstatut->addWidget(statutEdit);
//            caction->addWidget(actionlabel);
//            caction->addWidget(actionEdit);
//            cpriorite->addWidget(prioritelabel);
//            cpriorite->addWidget(prioriteEdit);
//            cdateEch->addWidget(dateEchlabel);
//            cdateEch->addWidget(dateEchEdit);

//            zone->addLayout(cstatut);
//            zone->addLayout(caction);
//            zone->addLayout(cpriorite);
//            zone->addLayout(cdateEch);

//            Notes* n=it.current().clone();
//            Tache& a1 = dynamic_cast<Tache&>(*n);

//            actionEdit->setText(a1.getAction());
//            actionEdit->setDisabled(true);
//            prioriteEdit->setText(a1.getPriorite());
//            prioriteEdit->setDisabled(true);
//            dateEchEdit->setText(a1.getDateEch());
//            dateEchEdit->setDisabled(true);
//            statutEdit->setText(a1.getStatut());
//            statutEdit->setDisabled(true);

//            QObject::connect(actionEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//            QObject::connect(prioriteEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//            QObject::connect(dateEchEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//            QObject::connect(statutEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//    }
//    else if(type=="15NoteAvecFichier")
//        {
//            descriptionlabel = new QLabel("Description :");
//            filelabel = new QLabel("Fichier :");

//            descriptionEdit = new QTextEdit();
//            fileEdit = new QLineEdit();

//            cdescription = new QHBoxLayout();
//            cfile = new QHBoxLayout();

//            cdescription->addWidget(descriptionlabel);
//            cdescription->addWidget(descriptionEdit);
//            cfile->addWidget(filelabel);
//            cfile->addWidget(fileEdit);

//            zone->addLayout(cdescription);
//            zone->addLayout(cfile);

//            Notes* n=it.current().clone();
//            NoteAvecFichier& a1 = dynamic_cast<NoteAvecFichier&>(*n);

//            descriptionEdit->setText(a1.getDescription());
//            descriptionEdit->setDisabled(true);
//            fileEdit->setText(a1.getFile());
//            fileEdit->setDisabled(true);

//            QObject::connect(descriptionEdit,SIGNAL(textChanged()),this,SLOT(activerSauver()));
//            QObject::connect(fileEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//     }

//     zone->addLayout(cboutons);
//     this->setLayout(zone);

//     QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
//     QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
//     QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(activerEditer()));

//     QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//     QObject::connect(dateCreaEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//     QObject::connect(dateModifEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
//    }
//}

EditeurNote::EditeurNote(Notes *n, QWidget* parent) {
    qDebug()<<"et puis la aussi\n";
            idlabel = new QLabel("ID : ");
            titrelabel = new QLabel("Titre : ");
            dateCrealabel = new QLabel("Date Creation  :");
            dateModiflabel = new QLabel("Date Modification : ");

            idEdit = new QLineEdit();
            titreEdit = new QLineEdit();
            dateCreaEdit = new QLineEdit();
            dateModifEdit = new QLineEdit();

            sauver = new QPushButton("Sauver");
            editer = new QPushButton("Editer");
            restaurer = new QPushButton("Restaurer");

            cid = new QHBoxLayout();
            ctitre = new QHBoxLayout();
            cdateCrea = new QHBoxLayout();
            cdateModif = new QHBoxLayout();
            cboutons = new QHBoxLayout();
            cboutonRestauration = new QVBoxLayout();
            zone = new QVBoxLayout();

            cid->addWidget(idlabel);
            cid->addWidget(idEdit);
            ctitre->addWidget(titrelabel);
            ctitre->addWidget(titreEdit);
            cdateCrea->addWidget(dateCrealabel);
            cdateCrea->addWidget(dateCreaEdit);
            cdateModif->addWidget(dateModiflabel);
            cdateModif->addWidget(dateModifEdit);
            cboutons->addWidget(sauver);
            cboutons->addWidget(editer);
            cboutons->addWidget(restaurer);

            zone->addLayout(cid);
            zone->addLayout(ctitre);
            zone->addLayout(cdateCrea);
            zone->addLayout(cdateModif);

            idEdit->setText(n->getId());
            titreEdit->setText(n->getTitre());
            dateCreaEdit->setText(n->getDateCrea());
            dateModifEdit->setText(n->getDateModif());

            idEdit->setDisabled(true);
            titreEdit->setDisabled(true);
            dateCreaEdit->setDisabled(true);
            dateModifEdit->setDisabled(true);

            sauver->setDisabled(true);
            restaurer->setDisabled(true);
            qDebug()<<"ici ça marche\n";
}

void EditeurNote::activerEditer(){
    restaurer->setDisabled(false);
    titreEdit->setDisabled(false);
    dateCreaEdit->setDisabled(false);
    dateModifEdit->setDisabled(false);



}

void EditeurNote::activerSauver(){
    sauver->setEnabled(true);
}

ArticleEditeur::ArticleEditeur(Article *a,QWidget* parent) : EditeurNote(a,parent), article(a) {
                textlabel = new QLabel("Texte :");
                textEdit = new QTextEdit();

                ctext = new QHBoxLayout();

                ctext->addWidget(textlabel);
                ctext->addWidget(textEdit);

                zone->addLayout(ctext);

                idEdit->setText(article->getId());
                titreEdit->setText(article->getTitre());
                dateCreaEdit->setText(article->getDateCrea());
                dateModifEdit->setText(article->getDateModif());
                textEdit->setText(article->getText());
                textEdit->setDisabled(true);

                QObject::connect(textEdit,SIGNAL(textChanged()),this,SLOT(activerSauver()));
                QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
                QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
                QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(activerEditer()));

                zone->addLayout(cboutons);
                this->setLayout(zone);

                QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
                QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
                QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(activerEditer()));

                QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(dateCreaEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(dateModifEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
}

void ArticleEditeur::activerEditer() {
    textEdit->setDisabled(false);
}

void ArticleEditeur::sauverNote() {
    qDebug()<<"fonction sauver article";
}

TacheEditeur::TacheEditeur(Tache *a,QWidget* parent) : EditeurNote(a,parent), tache(a) {
                statutlabel = new QLabel("Statut :");
                actionlabel = new QLabel("Action :");
                prioritelabel = new QLabel("Priorite :");
                dateEchlabel = new QLabel("Date d'echeance' :");

                statutEdit = new QLineEdit();
                actionEdit = new QLineEdit();
                prioriteEdit = new QLineEdit();
                dateEchEdit = new QLineEdit();

                cstatut = new QHBoxLayout();
                caction = new QHBoxLayout();
                cpriorite = new QHBoxLayout();
                cdateEch = new QHBoxLayout();

                cstatut->addWidget(statutlabel);
                cstatut->addWidget(statutEdit);
                caction->addWidget(actionlabel);
                caction->addWidget(actionEdit);
                cpriorite->addWidget(prioritelabel);
                cpriorite->addWidget(prioriteEdit);
                cdateEch->addWidget(dateEchlabel);
                cdateEch->addWidget(dateEchEdit);

                zone->addLayout(cstatut);
                zone->addLayout(caction);
                zone->addLayout(cpriorite);
                zone->addLayout(cdateEch);

                idEdit->setText(tache->getId());
                idEdit->setDisabled(true);
                titreEdit->setText(tache->getTitre());
                titreEdit->setDisabled(true);
                dateCreaEdit->setText(tache->getDateCrea());
                dateCreaEdit->setDisabled(true);
                dateModifEdit->setText(tache->getDateModif());
                dateModifEdit->setDisabled(true);
                actionEdit->setText(tache->getAction());
                actionEdit->setDisabled(true);
                prioriteEdit->setText(tache->getPriorite());
                prioriteEdit->setDisabled(true);
                dateEchEdit->setText(tache->getDateEch());
                dateEchEdit->setDisabled(true);
                statutEdit->setText(tache->getStatut());
                statutEdit->setDisabled(true);

                QObject::connect(actionEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(prioriteEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(dateEchEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(statutEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));

                zone->addLayout(cboutons);
                this->setLayout(zone);

                QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
                QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
                QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(activerEditer()));

                QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(dateCreaEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(dateModifEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
}

void TacheEditeur::activerEditer() {
    actionEdit->setDisabled(false);
    prioriteEdit->setDisabled(false);
    dateEchEdit->setDisabled(false);
    statutEdit->setDisabled(false);
}

void TacheEditeur::sauverNote() {
    qDebug()<<"fonction sauver tache";
}

NoteFichierEditeur::NoteFichierEditeur(NoteAvecFichier *a,QWidget* parent) : EditeurNote(a,parent), noteFichier(a) {
                descriptionlabel = new QLabel("descrption :");
                filelabel= new QLabel("file : ");
                descriptionEdit = new QTextEdit();
                fileEdit = new QLineEdit();

                cdescription = new QHBoxLayout();
                cfile = new QHBoxLayout();

                cdescription->addWidget(descriptionlabel);
                cdescription->addWidget(descriptionEdit);
                cfile->addWidget(filelabel);
                cfile->addWidget(fileEdit);

                zone->addLayout(cdescription);
                zone->addLayout(cfile);
                idEdit->setText(noteFichier->getId());
                titreEdit->setText(noteFichier->getTitre());
                dateCreaEdit->setText(noteFichier->getDateCrea());
                dateModifEdit->setText(noteFichier->getDateModif());
                descriptionEdit->setText(noteFichier->getDescription());
                descriptionEdit->setDisabled(true);
                fileEdit->setText(noteFichier->getFile());
                fileEdit->setDisabled(true);

                QObject::connect(descriptionEdit,SIGNAL(textChanged()),this,SLOT(activerSauver()));
                QObject::connect(fileEdit,SIGNAL(textChanged()),this,SLOT(activerSauver()));
                QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
                QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
                QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(activerEditer()));

                zone->addLayout(cboutons);
                this->setLayout(zone);

                QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
                QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
                QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(activerEditer()));

                QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(dateCreaEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(dateModifEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
}

void NoteFichierEditeur::activerEditer() {
    descriptionEdit->setDisabled(false);
    fileEdit->setDisabled(false);
}

void NoteFichierEditeur::sauverNote() {
    qDebug()<<"fonction sauver notefichier";
}

