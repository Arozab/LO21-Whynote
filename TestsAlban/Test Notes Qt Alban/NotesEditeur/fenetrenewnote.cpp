#include "notes.h"
#include "notemanager.h"
#include "fenetrenewnote.h"
#include "fenetreprincipale.h"


FenetreNewNote::FenetreNewNote(QString type, QWidget* parent) : QWidget(parent) {
    typeEdit = new QLineEdit();
    typeEdit->setText(type);
    typeEdit->setDisabled(true);

    idlabel = new QLabel("ID : ");
    titrelabel = new QLabel("Titre : ");

    idEdit = new QLineEdit();
    titreEdit = new QLineEdit();

    valider = new QPushButton("Ajouter");
    annuler = new QPushButton("Annuler");

    ctype = new QHBoxLayout();
    cid = new QHBoxLayout();
    ctitre = new QHBoxLayout();
    cboutons = new QHBoxLayout();
    zone = new QVBoxLayout();

    ctype->addWidget(typeEdit);
    cid->addWidget(idlabel);
    cid->addWidget(idEdit);
    ctitre->addWidget(titrelabel);
    ctitre->addWidget(titreEdit);
    cboutons->addWidget(valider);
    cboutons->addWidget(annuler);

    zone->addLayout(cid);
    zone->addLayout(ctitre);

    if (type == "article")
    {
        textlabel = new QLabel("Texte :");
        textEdit = new QTextEdit();

        ctext = new QHBoxLayout();

        ctext->addWidget(textlabel);
        ctext->addWidget(textEdit);

        zone->addLayout(ctext);
    }
    else
        if (type == "tache")
        {
            statutlabel = new QLabel("Statut :");
            actionlabel = new QLabel("Action :");
            prioritelabel = new QLabel("Priorite :");
            dateEchlabel = new QLabel("Date d'echeance' :");

            statutEdit = new QLineEdit();
            actionEdit = new QLineEdit();
            prioriteEdit = new QLineEdit();
            dateEchEdit = new QDateTimeEdit();

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
        }
        else
            if (type == "noteFichier")
            {
                descriptionlabel = new QLabel("Description :");
                filelabel = new QLabel("Fichier :");

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
            }

    zone->addLayout(cboutons);
    this->setLayout(zone);

    QObject::connect(valider,SIGNAL(clicked()),this,SLOT(creerNote()));
    QObject::connect(annuler,SIGNAL(clicked()),this,SLOT(close()));

    this->setWindowModality(Qt::ApplicationModal);
}


void FenetreNewNote::creerNote() {
    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp=FenPrincipale::getInstance();
    NotesManager::Iterator it=m.getIterator();
    while(!it.isDone() && it.current().getId()!=idEdit->text()){
        it.next();
    }
    if (!it.isDone()) { // si on trouve un id deja existant
        QMessageBox::information(this, "Erreur", "Id deja existant");
    }
    else if(idEdit->text()!="") {
        try
        {
            if (typeEdit->text() == "article")
            {
                Article a=m.getNewArticle(idEdit->text(),titreEdit->text(),textEdit->toPlainText());
                QMessageBox::information(this,"Ajouter","Article ajouté !");
                m.save();
                fp.actualiserNote();
                close();
            }
            else
                if (typeEdit->text() == "tache")
                {
                    Tache a=m.getNewTache(idEdit->text(),titreEdit->text(),statutEdit->text(),actionEdit->text(),prioriteEdit->text()/*,DateEch*/);
                    QMessageBox::information(this,"Ajouter","Tache ajoutée !");
                    m.save();
                    fp.actualiserNote();
                    close();
                }
                else  
                    if(typeEdit->text() == "noteFichier")
                    {
                        NoteAvecFichier a=m.getNewNoteAvecFichier(idEdit->text(),titreEdit->text(),descriptionEdit->toPlainText(),fileEdit->text());
                        QMessageBox::information(this,"Ajouter","NoteFichier ajoutée !");
                        m.save();
                        fp.actualiserNote();
                        close();
                    }
        }
        catch (NotesException& e)
        {
            QMessageBox::information(this,"Erreur",e.getInfo());
        }
    }
    else
        QMessageBox::information(this, "Erreur", "Vous devez entrer un id !");
}





//FenetreNewArticle::FenetreNewArticle(QWidget* parent): QWidget(parent) {
//    titrelabel=new QLabel("titre",this);
//    textlabel=new QLabel("texte",this);
//    titreEdit=new QLineEdit(this);
//    textEdit=new QTextEdit(this);

//    ctext = new QHBoxLayout;
//    ctext->addWidget(textlabel);
//    ctext->addWidget(textEdit);
//    ctitre = new QHBoxLayout;
//    ctitre->addWidget(titrelabel);
//    ctitre->addWidget(titreEdit);

//    ajouter=new QPushButton("Ajouter",this);
//    cboutons = new QHBoxLayout;
//    cboutons->addWidget(ajouter);

//    ccentral= new QVBoxLayout;
//    ccentral->addLayout(ctitre);
//    ccentral->addLayout(ctext);
//    ccentral->addLayout(cboutons);
//    setLayout(ccentral);

//    QObject::connect(ajouter,SIGNAL(clicked()),pere,SLOT(creerArticle()));
//}


