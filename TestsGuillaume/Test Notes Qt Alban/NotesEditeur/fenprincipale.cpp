#include "FenPrincipale.h"
#include "notes.h"
#include <typeinfo>

FenPrincipale::FenPrincipale(NotesManager& m)
{
    zoneCentrale = new QWidget;

    menuFichier = menuBar()->addMenu("Fichier");

        actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

        /*actionAjouter = new QAction("&Ajouter une note", this);
        menuFichier->addAction(actionAjouter);
        connect(actionAjouter, SIGNAL(triggered()), qApp, SLOT(quit()));*/

    dock = new QDockWidget(tr("Liste de Notes"));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    //Liste de l'ensemble des notes

    listeNote = new QListWidget(dock);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        listeNote->addItem(str);
    }
    dock->setWidget(listeNote);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    //Liste des taches

    dock = new QDockWidget(tr("Todo List"));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    listeTache = new QListWidget(dock);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        if (typeid(it.current()).name()=="tache"){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        listeNote->addItem(str);}
    }
    dock->setWidget(listeTache);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    //Liste des archives

    dock = new QDockWidget(tr("Notes Archivées"));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    listeArchive = new QListWidget(dock);
    dock->setWidget(listeArchive);
    addDockWidget(Qt::LeftDockWidgetArea, dock);

    //Liste des versions

    listeVersion = new QComboBox(this);
    listeVersion->addItem(tr("Afrique"));
    listeVersion->addItem(tr("Amerique du Nord"));


   /* //AJOUTWIDGET VERSIONS
    archive = new QDockWidget(tr("Liste de Notes"));
    archive->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    liste = new QListWidget(archive);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        liste->addItem(str);
    }
    archive->setWidget(liste);
    addDockWidget(Qt::LeftDockWidgetArea, archive);
*/


    /*dock = new QDockWidget();
    bouton1 = new QPushButton("Afficher");
    dock->setWidget(bouton1);
    addDockWidget(Qt::LeftDockWidgetArea, dock);*/

    idlabel=new QLabel("id",this);
    titrelabel=new QLabel("titre",this);
    dateCrealabel=new QLabel("date creation",this);
    dateModiflabel=new QLabel("date modification",this);
    idEdit=new QLineEdit(this);
    titreEdit=new QLineEdit(this);
    dateCreaEdit=new QLineEdit(this);
    dateModifEdit=new QLineEdit(this);
    idEdit->setDisabled(true);
    titreEdit->setDisabled(true);
    dateCreaEdit->setDisabled(true);
    dateModifEdit->setDisabled(true);
    editer=new QPushButton("Editer",this);
    sauver=new QPushButton("Sauver",this);
    restaurer=new QPushButton("Restaurer une ancienne version",this);




    cid = new QHBoxLayout;
    cid->addWidget(idlabel);
    cid->addWidget(idEdit);
    ctitre = new QHBoxLayout;
    ctitre->addWidget(titrelabel);
    ctitre->addWidget(titreEdit);
    cdateCrea = new QHBoxLayout;
    cdateCrea->addWidget(dateCrealabel);
    cdateCrea->addWidget(dateCreaEdit);
    cdateModif = new QHBoxLayout;
    cdateModif->addWidget(dateModiflabel);
    cdateModif->addWidget(dateModifEdit);
    cboutons = new QHBoxLayout;
    cboutons->addWidget(editer);
    cboutons->addWidget(sauver);
    cboutonRestauration = new QVBoxLayout;
    cboutonRestauration->addWidget(restaurer);
    cboutonRestauration->addWidget(listeVersion);
    ccentral = new QVBoxLayout;
    ccentral->addLayout(cid);
    ccentral->addLayout(ctitre);
    ccentral->addLayout(cdateCrea);
    ccentral->addLayout(cdateModif);
    ccentral->addLayout(cboutons);
    ccentral->addLayout(cboutonRestauration);
    zoneCentrale->setLayout(ccentral);
    setCentralWidget(zoneCentrale);

    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
    QObject::connect(listeNote, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(afficheNote(QListWidgetItem*)));
    QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));
    QObject::connect(restaurer, SIGNAL(clicked()),this,SLOT(activerEditer()));

    QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(dateCreaEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(dateModifEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(textEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));

    sauver->setDisabled(true);
    restaurer->setDisabled(true);


}

void FenPrincipale::afficheNote(QListWidgetItem* item){
    QString titre=item->text();
    if (titre.isEmpty()){
        qDebug()<<"titre : "<<titre<<"\n";
        return;
    }
    else{
        NotesManager& m=NotesManager::recupererInstance();
        NotesManager::Iterator it=m.getIterator();
        while(!it.isDone() && it.current().getTitre()!=titre){
            it.next();
        }
        if(!it.isDone()){
            idEdit->setText(it.current().getId());
            titreEdit->setText(it.current().getTitre());
            dateCreaEdit->setText(it.current().getDateCrea());
            dateModifEdit->setText(it.current().getDateModif());
            if(textEdit == NULL && textlabel == NULL && ctext == NULL){
                textEdit=new QTextEdit(this);
                ctext = new QHBoxLayout;
                textlabel=new QLabel("texte",this);
                ccentral->insertLayout(4,ctext);
            }
            textEdit->setDisabled(true);
            idEdit->setDisabled(true);
            titreEdit->setDisabled(true);
            dateCreaEdit->setDisabled(true);
            dateModifEdit->setDisabled(true);
            ctext->addWidget(textlabel);
            ctext->addWidget(textEdit);

            Notes* n=it.current().clone();
            Article& a1 = dynamic_cast<Article&>(*n);
            textEdit->setText(a1.getText());
            //article=&a1;
        }
    }
    sauver->setDisabled(true);
}

 void FenPrincipale::activerEditer(){
     titreEdit->setDisabled(false);
     dateCreaEdit->setDisabled(false);
     dateModifEdit->setDisabled(false);
     textEdit->setDisabled(false);
     restaurer->setDisabled(false);
 }

  void FenPrincipale::activerSauver(QString str){
      sauver->setEnabled(true);
  }

  void FenPrincipale::sauverNote(){
      NotesManager& m=NotesManager::recupererInstance();
      NotesManager::Iterator it=m.getIterator();
      while(!it.isDone() && it.current().getId()!=idEdit->text()){
          it.next();
      }
      if(!it.isDone()){
          Notes* n=it.current().clone();
          Article* a2 = dynamic_cast<Article*>(&it.current());
          a2->setAncienneVersion(n);
          a2->setTitre(titreEdit->text());
          QString d1=dateCreaEdit->text();
          QString strJ=d1.mid(0,2);
          int j=strJ.toInt();
          QString strM=d1.mid(3,2);
          int m=strM.toInt();
          QString strA=d1.mid(6,4);
          int an=strA.toInt();
          Date dateCrea=Date(j,m,an);
          a2->setDateCrea(dateCrea);

          QString d2=dateModifEdit->text();
          QString str2J=d2.mid(0,2);
          int j2=str2J.toInt();
          QString str2M=d2.mid(3,2);
          int m2=str2M.toInt();
          QString str2A=d2.mid(6,4);
          int an2=str2A.toInt();
          Date dateModif=Date(j2,m2,an2);
          a2->setDateModif(dateModif);

          a2->setText(textEdit->toPlainText());
          QMessageBox::information(this,"Sauvegarder","Article sauvegardé !");
          sauver->setDisabled(true);
          textEdit->setDisabled(true);
          idEdit->setDisabled(true);
          titreEdit->setDisabled(true);
          dateCreaEdit->setDisabled(true);
          dateModifEdit->setDisabled(true);
          qDebug()<<it.current().getOldVersion(0).getTitre()<<"\n";
        }

      //addDockWidget(Qt::LeftDockWidgetArea, dock);
  }

/*void FenPrincipale::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "(*.xml)");
    //load(fichier);
}*/
