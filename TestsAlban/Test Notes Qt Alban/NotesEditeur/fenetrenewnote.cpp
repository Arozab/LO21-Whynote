#include "notes.h"
#include "notemanager.h"
#include "fenetrenewnote.h"
#include "fenetreprincipale.h"
#include "editeurnote.h"
#include "editeurnotefactory.h"
#include "versions.h"


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
            dateEchlabel = new QLabel("Date d'echeance :");

            statutEdit = new QLineEdit();
            actionEdit = new QLineEdit();
            prioriteEdit = new QLineEdit();
            dateEchEdit = new QLineEdit();
            dateEchEdit->setText("jj/mm/aaaa");

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
    VersionsManager& v=VersionsManager::recupererInstance();

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
                Article* pta=&a;
                QMessageBox::information(this,"Ajouter","Article ajouté !");
                m.save();
                fp.actualiserNote();

                idEdit->setDisabled(true);
                titreEdit->setDisabled(true);
                textEdit->setDisabled(true);
                valider->setDisabled(true);
                annuler->setDisabled(true);

                v.addVersion(pta);
            }
            else
                if (typeEdit->text() == "tache")
                {
                    QString d5=dateEchEdit->text();
                    QString strJ=d5.mid(0,2);
                    int j=strJ.toInt();
                    QString strM=d5.mid(3,2);
                    int mo=strM.toInt();
                    QString strA=d5.mid(6,4);
                    int an=strA.toInt();
                    Date dateEch=Date(j,mo,an);

                    Tache a=m.getNewTache(idEdit->text(),titreEdit->text(),statutEdit->text(),actionEdit->text(),prioriteEdit->text());
                    Tache* pta=&a;

                    a.setDateEch(dateEch);
                    QMessageBox::information(this,"Ajouter","Tache ajoutée !");
                    m.save();
                    fp.actualiserNote();

                    idEdit->setDisabled(true);
                    titreEdit->setDisabled(true);
                    statutEdit->setDisabled(true);
                    actionEdit->setDisabled(true);
                    prioriteEdit->setDisabled(true);
                    dateEchEdit->setDisabled(true);
                    valider->setDisabled(true);
                    annuler->setDisabled(true);

                    //v.addVersion(&ref);
                }
                else  
                    if(typeEdit->text() == "noteFichier")
                    {
                        NoteAvecFichier a=m.getNewNoteAvecFichier(idEdit->text(),titreEdit->text(),descriptionEdit->toPlainText(),fileEdit->text());
                        NoteAvecFichier* pta=&a;


                        QMessageBox::information(this,"Ajouter","NoteFichier ajoutée !");
                        m.save();
                        fp.actualiserNote();

                        idEdit->setDisabled(true);
                        titreEdit->setDisabled(true);
                        descriptionEdit->setDisabled(true);
                        fileEdit->setDisabled(true);
                        valider->setDisabled(true);
                        annuler->setDisabled(true);

                        v.initVersion("noteAvecFichier",pta->getId());

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


