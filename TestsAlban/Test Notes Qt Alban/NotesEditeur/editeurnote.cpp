#include "notes.h"
#include "notemanager.h"
#include "editeurnote.h"
#include "fenetreprincipale.h"
#include "corbeille.h"
#include "versions.h"

EditeurNote::EditeurNote(Notes *n, QWidget* parent) {
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
            supprimer = new QPushButton("Supprimer");
            annuler = new QPushButton("Annuler");

            // -- Liste des versions

            listeVersion = new QComboBox();


            cid = new QHBoxLayout();
            ctitre = new QHBoxLayout();
            cdateCrea = new QHBoxLayout();
            cdateModif = new QHBoxLayout();
            cboutons = new QHBoxLayout();
            crestaurer = new QVBoxLayout();
            cboutonEdition = new QHBoxLayout();
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
            cboutons->addWidget(annuler);
            cboutons->addWidget(restaurer);
            cboutons->addWidget(listeVersion);


            cboutonEdition->addWidget(editer);
            cboutonEdition->addWidget(supprimer);

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
            annuler->setDisabled(true);
}

void EditeurNote::activerEditer(){
    restaurer->setDisabled(false);
    titreEdit->setDisabled(false);
    annuler->setDisabled(false);
    supprimer->setDisabled(true);



}

void EditeurNote::activerSauver(){
    sauver->setEnabled(true);
}

void EditeurNote::supprimeNote() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Supprimer Note");
    msgBox.setText("Voulez-vous vraiment supprimer cette note ?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
      msgBox.close();
      this->supprime();
    }else {
      msgBox.close();
    }
}

void EditeurNote::restaureNote() {
    QMessageBox msgBox;
    msgBox.setWindowTitle("Supprimer Note");
    msgBox.setText("Voulez-vous vraiment restaurer cette version ?");
    msgBox.setStandardButtons(QMessageBox::Yes);
    msgBox.addButton(QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    if(msgBox.exec() == QMessageBox::Yes){
      msgBox.close();
      this->restaure();
    }else {
      msgBox.close();
    }
}


void EditeurNote::annuleEdition() {
    restaurer->setDisabled(true);
    titreEdit->setDisabled(true);
    annuler->setDisabled(true);
    supprimer->setDisabled(false);
    sauver->setDisabled(true);
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
                QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
                QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
                QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
                QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(restaureNote()));
                QObject::connect(supprimer, SIGNAL(clicked()),this,SLOT(supprimeNote()));
                QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annuleEdition()));


                zone->addLayout(cboutons);
                zone->addLayout(cboutonEdition);
                this->setLayout(zone);
}

void ArticleEditeur::activerEditer() {
    restaurer->setDisabled(false);
    titreEdit->setDisabled(false);
    textEdit->setDisabled(false);
    supprimer->setDisabled(true);
    annuler->setDisabled(false);
}

void ArticleEditeur::annuleEdition() {
    restaurer->setDisabled(true);
    titreEdit->setDisabled(true);
    textEdit->setDisabled(true);
    supprimer->setDisabled(false);
    annuler->setDisabled(true);
    sauver->setDisabled(true);
}

void ArticleEditeur::sauverNote() {
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();

    // on crée un nouveau article et son ancienne version est celle avant la modification
    NotesManager::Iterator it=m.getIterator();
    while(!it.isDone() && it.current().getId()!=article->getId()){
        it.next();
    }
    if(!it.isDone()){
    Article* a=dynamic_cast<Article*>(&it.current());

    a->setAncienneVersion(article);

    a->setTitre(titreEdit->text());

    QString d1=dateCreaEdit->text();
    QString strJ=d1.mid(0,2);
    int j=strJ.toInt();
    QString strM=d1.mid(3,2);
    int mo=strM.toInt();
    QString strA=d1.mid(6,4);
    int an=strA.toInt();
    Date dateCrea=Date(j,mo,an);
    a->setDateCrea(dateCrea);

    QString d2=dateModifEdit->text();
    QString str2J=d2.mid(0,2);
    int j2=str2J.toInt();
    QString str2M=d2.mid(3,2);
    int m2=str2M.toInt();
    QString str2A=d2.mid(6,4);
    int an2=str2A.toInt();
    Date dateModif=Date(j2,m2,an2);

    a->setDateModif(dateModif);

    a->setText(textEdit->toPlainText());
    m.save();

    fp.actualiserNote();

    article=a;

    QMessageBox::information(this,"Sauvegarder","Article sauvegardé !");

    sauver->setDisabled(true);
    }

}

void ArticleEditeur::supprime(){
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();
    Corbeille& c=Corbeille::getInstance();
    qDebug()<<article->getTitre()<<"\n";
    c.addNote(article);
    m.supprimerNote(idEdit->text());
    this->close();
    QWidget* zone= new QWidget;
    fp.setCentralWidget(zone);
    m.save();
    //le placer dans une corbeille
    fp.actualiserNote();
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
    titreEdit->setText(tache->getTitre());
    dateCreaEdit->setText(tache->getDateCrea());
    dateModifEdit->setText(tache->getDateModif());
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
    QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
    QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
    QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(restaureNote()));
    QObject::connect(supprimer, SIGNAL(clicked()),this,SLOT(supprimeNote()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annuleEdition()));

    zone->addLayout(cboutons);
    zone->addLayout(cboutonEdition);
    this->setLayout(zone);
}

void TacheEditeur::activerEditer() {
    restaurer->setDisabled(false);
    titreEdit->setDisabled(false);
    actionEdit->setDisabled(false);
    prioriteEdit->setDisabled(false);
    dateEchEdit->setDisabled(false);
    statutEdit->setDisabled(false);
    supprimer->setDisabled(true);
    annuler->setDisabled(false);
}

void TacheEditeur::annuleEdition() {
    restaurer->setDisabled(true);
    titreEdit->setDisabled(true);
    actionEdit->setDisabled(true);
    prioriteEdit->setDisabled(true);
    dateEchEdit->setDisabled(true);
    statutEdit->setDisabled(true);
    supprimer->setDisabled(false);
    annuler->setDisabled(true);
    sauver->setDisabled(true);
}


void TacheEditeur::sauverNote() {
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();

    // on crée une nouvelle tache et son ancienne version est celle avant la modification
    NotesManager::Iterator it=m.getIterator();
    while(!it.isDone() && it.current().getId()!=tache->getId()){
        it.next();
    }
    if(!it.isDone()){
    Tache* a=dynamic_cast<Tache*>(&it.current());

    a->setAncienneVersion(tache);

    a->setTitre(titreEdit->text());

    QString d1=dateCreaEdit->text();
    QString strJ=d1.mid(0,2);
    int j=strJ.toInt();
    QString strM=d1.mid(3,2);
    int mo=strM.toInt();
    QString strA=d1.mid(6,4);
    int an=strA.toInt();
    Date dateCrea=Date(j,mo,an);
    a->setDateCrea(dateCrea);

    QString d2=dateModifEdit->text();
    QString str2J=d2.mid(0,2);
    int j2=str2J.toInt();
    QString str2M=d2.mid(3,2);
    int m2=str2M.toInt();
    QString str2A=d2.mid(6,4);
    int an2=str2A.toInt();
    Date dateModif=Date(j2,m2,an2);
    a->setDateModif(dateModif);

    a->setAction(actionEdit->text());

    a->setPriorite(prioriteEdit->text());

    QString d3=dateEchEdit->text();
    QString str3J=d3.mid(0,2);
    int j3=str3J.toInt();
    QString str3M=d3.mid(3,2);
    int m3=str3M.toInt();
    QString str3A=d3.mid(6,4);
    int an3=str3A.toInt();
    Date dateEch=Date(j3,m3,an3);
    a->setDateEch(dateEch);

    a->setAction(actionEdit->text());

    a->setStatut(statutEdit->text());

    m.save();

    fp.actualiserNote();

    tache=a;

    QMessageBox::information(this,"Sauvegarder","Tache sauvegardée !");

    sauver->setDisabled(true);
    }
}

void TacheEditeur::supprime(){
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();
    Corbeille::getInstance().addNote(tache);
    m.supprimerNote(idEdit->text());
    this->close();
    QWidget* zone= new QWidget;
    fp.setCentralWidget(zone);
    m.save();
    //le placer dans une corbeille
    fp.actualiserNote();
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
    QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver()));
    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
    QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
    QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(restaureNote()));
    QObject::connect(supprimer, SIGNAL(clicked()),this,SLOT(supprimeNote()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(annuleEdition()));

    zone->addLayout(cboutons);
    zone->addLayout(cboutonEdition);
    this->setLayout(zone);
}

    void NoteFichierEditeur::activerEditer() {
    restaurer->setDisabled(false);
    titreEdit->setDisabled(false);
    descriptionEdit->setDisabled(false);
    fileEdit->setDisabled(false);
    supprimer->setDisabled(true);
    annuler->setDisabled(false);
}

void NoteFichierEditeur::annuleEdition() {
    restaurer->setDisabled(true);
    titreEdit->setDisabled(true);
    descriptionEdit->setDisabled(true);
    fileEdit->setDisabled(true);
    supprimer->setDisabled(false);
    annuler->setDisabled(true);
    sauver->setDisabled(true);
}

void NoteFichierEditeur::sauverNote() {
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();

    // on crée un nouveau NoteAvecFichier et son ancienne version est celle avant la modification
    NotesManager::Iterator it=m.getIterator();
    while(!it.isDone() && it.current().getId()!=noteFichier->getId()){
        it.next();
    }
    if(!it.isDone()){
    NoteAvecFichier* a=dynamic_cast<NoteAvecFichier*>(&it.current());

    a->setAncienneVersion(noteFichier);

    a->setTitre(titreEdit->text());

    QString d1=dateCreaEdit->text();
    QString strJ=d1.mid(0,2);
    int j=strJ.toInt();
    QString strM=d1.mid(3,2);
    int mo=strM.toInt();
    QString strA=d1.mid(6,4);
    int an=strA.toInt();
    Date dateCrea=Date(j,mo,an);
    a->setDateCrea(dateCrea);

    QString d2=dateModifEdit->text();
    QString str2J=d2.mid(0,2);
    int j2=str2J.toInt();
    QString str2M=d2.mid(3,2);
    int m2=str2M.toInt();
    QString str2A=d2.mid(6,4);
    int an2=str2A.toInt();
    Date dateModif=Date(j2,m2,an2);
    a->setDateModif(dateModif);

    a->setDescription(descriptionEdit->toPlainText());

    a->setFile(fileEdit->text());
    m.save();

    fp.actualiserNote();

    noteFichier=a;

    QMessageBox::information(this,"Sauvegarder","Note avec fichier sauvegardée !");

    sauver->setDisabled(true);
    }
}

void NoteFichierEditeur::supprime(){
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();
    Corbeille::getInstance().addNote(noteFichier);
    m.supprimerNote(idEdit->text());
    this->close();
    QWidget* zone= new QWidget;
    fp.setCentralWidget(zone);
    m.save();
    //le placer dans une corbeille
    fp.actualiserNote();
}

void EditeurNote::restaure() {
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();

    VersionsManager& v= VersionsManager::recupererInstance();

    v.updateComboBox(listeVersion);
    fp.actualiserNote();
    QMessageBox::information(this,"Restaurer","Article restauré !");

    }
