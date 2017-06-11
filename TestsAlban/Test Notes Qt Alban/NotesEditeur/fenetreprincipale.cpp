#include "notes.h"
#include "notemanager.h"
#include "fenetrenewnote.h"
#include "fenetreprincipale.h"
#include "editeurnote.h"
#include "editeurnotefactory.h"

FenPrincipale::FenPHandler FenPrincipale::fenP_handler=FenPHandler();

FenPrincipale& FenPrincipale::getInstance() {
  // Si le pointeur vers l'instance unique pointe vers 0
  if(!fenP_handler.instance) {
    fenP_handler.instance=new FenPrincipale;
  }
  // Retour par ref vers l'instance unique
  return *fenP_handler.instance;
}

void FenPrincipale::libererInstance() {
  // Liberation de la memoire allouee a l'instance unique
  delete fenP_handler.instance;
  // Repasse le pointeur a null/nullptr/0 pour que le prochain appel a getInstance recree bien une instance
  fenP_handler.instance=0;
}


FenPrincipale::FenPrincipale()
{
    NotesManager& m=NotesManager::recupererInstance();
    setWindowTitle("PluriNotes");

// ************ Bar des Taches **********

    menuFichier = menuBar()->addMenu("&Fichier");
    menuNote = menuBar()->addMenu("&Note");
    menuNouveau = menuNote->addMenu("&Nouveau");

    actionQuitter = new QAction("&Quitter", this);
    ajouterArticle = new QAction("&Article",this);
    ajouterTache = new QAction("&Tache",this);
    ajouterNoteFichier = new QAction("&NoteFichier",this);

    menuFichier->addAction(actionQuitter);
    menuNouveau->addAction(ajouterArticle);
    menuNouveau->addAction(ajouterTache);
    menuNouveau->addAction(ajouterNoteFichier);

    QObject::connect(actionQuitter, SIGNAL(triggered()), this, SLOT(quitter()));

    QObject::connect(ajouterArticle, SIGNAL(triggered()), this, SLOT(afficherNewArticle()));
    QObject::connect(ajouterTache, SIGNAL(triggered()), this, SLOT(afficherNewTache()));
    QObject::connect(ajouterNoteFichier, SIGNAL(triggered()), this, SLOT(afficherNewNoteFichier()));


//  ************ Zone Gauche **********

    dockNote = new QDockWidget(tr("Liste de Notes"));
    dockNote->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    // --- Liste de l'ensemble des notes

    listeNote = new QListWidget(dockNote);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        listeNote->addItem(str);
    }
    dockNote->setWidget(listeNote);
    addDockWidget(Qt::LeftDockWidgetArea, dockNote);

    // --- Liste des taches

    dockTache = new QDockWidget(tr("Todo List"));
    dockTache->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    listeTache = new QListWidget(dockTache);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        if (typeid(it.current()).name()=="tache"){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        listeNote->addItem(str);}
    }
    dockTache->setWidget(listeTache);
    addDockWidget(Qt::LeftDockWidgetArea, dockTache);

    // --- Liste des archives

    dockArchive = new QDockWidget(tr("Notes Archivées"));
    dockArchive->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    listeArchive = new QListWidget(dockArchive);
    dockArchive->setWidget(listeArchive);
    addDockWidget(Qt::LeftDockWidgetArea, dockArchive);

    // -- Liste des versions

    listeVersion = new QComboBox();
    listeVersion->addItem(tr("Afrique"));
    listeVersion->addItem(tr("Amerique du Nord"));
    
    QObject::connect(listeNote, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(afficheNote(QListWidgetItem*)));


//  **********  Zone Centrale *********** 

    zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);
    //ccentral = new QGridLayout;
    //zoneCentrale->setLayout(ccentral);



        /*actionAjouter = new QAction("&Ajouter une note", this);
        menuFichier->addAction(actionAjouter);
        connect(actionAjouter, SIGNAL(triggered()), qApp, SLOT(quit()));*/

       /* ajouterArticle = new QAction("&Article",this);
        menuNouveau->addAction(ajouterArticle);
        ajouterTache = new QAction("&Tache",this);
        menuNouveau->addAction(ajouterTache);
        ajouterNoteFichier = new QAction("&NoteFichier",this);
        menuNouveau->addAction(ajouterNoteFichier);
        QObject::connect(ajouterArticle, SIGNAL(triggered()), this, SLOT(afficherCreerArticle()));
        QObject::connect(ajouterTache, SIGNAL(triggered()), this, SLOT(afficherCreerTache()));
        QObject::connect(ajouterNoteFichier, SIGNAL(triggered()), this, SLOT(afficherCreerNoteFichier()));
*/


/*    idlabel=new QLabel("id",this);
    titrelabel=new QLabel("titre",this);
    dateCrealabel=new QLabel("date creation",this);
    dateModiflabel=new QLabel("date modification",this);
    textlabel=new QLabel("texte",this);
    descriptionlabel=new QLabel("description",this);
    filelabel=new QLabel("file",this);
    actionlabel=new QLabel("action",this);
    prioritelabel=new QLabel("priorite",this);
    dateEchlabel=new QLabel("date echéance",this);
    statutlabel=new QLabel("statut",this);
    idEdit=new QLineEdit(this);
    titreEdit=new QLineEdit(this);
    dateCreaEdit=new QLineEdit(this);
    dateModifEdit=new QLineEdit(this);
    textEdit=new QTextEdit(this);
    descritionEdit=new QTextEdit(this);
    fileEdit=new QLineEdit(this);
    actionEdit=new QLineEdit(this);
    prioriteEdit=new QLineEdit(this);
    dateEchEdit=new QLineEdit(this);
    statutEdit=new QLineEdit(this);
    idEdit->setDisabled(true);
    titreEdit->setDisabled(true);
    dateCreaEdit->setDisabled(true);
    dateModifEdit->setDisabled(true);
    textEdit->setDisabled(true);
    descritionEdit->setDisabled(true);
    fileEdit->setDisabled(true);
    actionEdit->setDisabled(true);
    prioriteEdit->setDisabled(true);
    dateEchEdit->setDisabled(true);
    statutEdit->setDisabled(true);
    textEdit->setHidden(true);
    textlabel->setHidden(true);
    descriptionlabel->setHidden(true);
    descritionEdit->setHidden(true);
    filelabel->setHidden(true);
    fileEdit->setHidden(true);
    actionlabel->setHidden(true);
    actionEdit->setHidden(true);
    prioritelabel->setHidden(true);
    prioriteEdit->setHidden(true);
    dateEchlabel->setHidden(true);
    dateEchEdit->setHidden(true);
    statutlabel->setHidden(true);
    statutEdit->setHidden(true);*/

/*    editer=new QPushButton("Editer",this);
    sauver=new QPushButton("Sauver",this);
    restaurer=new QPushButton("Restaurer une ancienne version",this);
    ajouter= new QPushButton("Ajouter",this);
    ajoutNoteFichier= new QPushButton("Ajouter",this);
    ajoutTache= new QPushButton("Ajouter",this);


    ctext = new QHBoxLayout;
    ctext->addWidget(textlabel);
    ctext->addWidget(textEdit);
    cdescription = new QHBoxLayout;
    cdescription->addWidget(descriptionlabel);
    cdescription->addWidget(descritionEdit);
    cfile = new QHBoxLayout;
    cfile->addWidget(filelabel);
    cfile->addWidget(fileEdit);
    caction = new QHBoxLayout;
    caction->addWidget(actionlabel);
    caction->addWidget(actionEdit);
    cpriorite = new QHBoxLayout;
    cpriorite->addWidget(prioritelabel);
    cpriorite->addWidget(prioriteEdit);
    cdateEch = new QHBoxLayout;
    cdateEch->addWidget(dateEchlabel);
    cdateEch->addWidget(dateEchEdit);
    cstatut = new QHBoxLayout;
    cstatut->addWidget(statutlabel);
    cstatut->addWidget(statutEdit);
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
    cboutonAjouter = new QHBoxLayout;
    cboutonAjouter->addWidget(ajouter);
    cboutonAjouterTache= new QHBoxLayout;
    cboutonAjouterTache->addWidget(ajoutTache);
    cboutonAjouterNoteFichier= new QHBoxLayout;
    cboutonAjouterNoteFichier->addWidget(ajoutNoteFichier);
    ccentral = new QVBoxLayout;
    ccentral->addLayout(cid);
    ccentral->addLayout(ctitre);
    ccentral->addLayout(cdateCrea);
    ccentral->addLayout(cdateModif);
    ccentral->addLayout(cboutons);
    ccentral->addLayout(cboutonRestauration);
    zoneCentrale->setLayout(ccentral);
    setCentralWidget(zoneCentrale);



    QObject::connect(ajouter,SIGNAL(clicked()),this,SLOT(creerArticle()));
    QObject::connect(ajoutTache,SIGNAL(clicked()),this,SLOT(creerTache()));
    QObject::connect(ajoutNoteFichier,SIGNAL(clicked()),this,SLOT(creerNoteFichier()));


    sauver->setDisabled(true);
	restaurer->setDisabled(true);
    ajouter->setDisabled(true);
    ajouter->setHidden(true);
    ajoutTache->setDisabled(true);
    ajoutTache->setHidden(true);
    ajoutNoteFichier->setDisabled(true);
    ajoutNoteFichier->setHidden(true);*/
}






void FenPrincipale::afficheNote(QListWidgetItem* item){
    QString titre=item->text();
    if (titre.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText("Il n'y a pas de notes à afficher");
        msgBox.exec();
    }
    else{
        NotesManager& m=NotesManager::recupererInstance();
        NotesManager::Iterator it=m.getIterator();
        while(!it.isDone() && it.current().getTitre()!=titre){
            it.next();
        }
        if(!it.isDone()){
            qDebug()<<titre<<"\n";
            qDebug()<<it.current().getType()<<"\n";
            EditeurFactory* ef = EditeurFactory::chooseEditeur(it.current().getType());
            Notes* n(it.current().clone());
            EditeurNote* en = ef->createEditeur(n);
            //EditeurNote* en= new EditeurNote(it.current().getType(),titre,this);
            editnote=en;
            setCentralWidget(editnote);
            editnote->show();
        }
     }
}

//            idEdit->setText(it.current().getId());
//            titreEdit->setText(it.current().getTitre());
//            dateCreaEdit->setText(it.current().getDateCrea());
//            dateModifEdit->setText(it.current().getDateModif());

//            idEdit->setDisabled(true);
//            titreEdit->setDisabled(true);
//            dateCreaEdit->setDisabled(true);
//            dateModifEdit->setDisabled(true);

//            qDebug()<<"type : "<<it.current().getType()<<"\n";
//            if(it.current().getType()=="7Article"){
//                actionlabel->setHidden(true);
//                actionEdit->setHidden(true);
//                prioritelabel->setHidden(true);
//                prioriteEdit->setHidden(true);
//                dateEchlabel->setHidden(true);
//                dateEchEdit->setHidden(true);
//                statutlabel->setHidden(true);
//                statutEdit->setHidden(true);
//                descriptionlabel->setHidden(true);
//                descritionEdit->setHidden(true);
//                filelabel->setHidden(true);
//                fileEdit->setHidden(true);
//                textEdit->setHidden(false);
//                textlabel->setHidden(false);
//                ccentral->insertLayout(4,ctext);
//                Notes* n=it.current().clone();
//                Article& a1 = dynamic_cast<Article&>(*n);
//                textEdit->setText(a1.getText());
//                textEdit->setDisabled(true);

//            }
//            if(it.current().getType()=="15NoteAvecFichier"){
//                actionlabel->setHidden(true);
//                actionEdit->setHidden(true);
//                prioritelabel->setHidden(true);
//                prioriteEdit->setHidden(true);
//                dateEchlabel->setHidden(true);
//                dateEchEdit->setHidden(true);
//                statutlabel->setHidden(true);
//                statutEdit->setHidden(true);
//                textEdit->setHidden(true);
//                textlabel->setHidden(true);
//                descritionEdit->setHidden(false);
//                descriptionlabel->setHidden(false);
//                fileEdit->setHidden(false);
//                filelabel->setHidden(false);
//                ccentral->insertLayout(4,cdescription);
//                ccentral->insertLayout(5,cfile);
//                Notes* n=it.current().clone();
//                NoteAvecFichier& a1 = dynamic_cast<NoteAvecFichier&>(*n);
//                descritionEdit->setText(a1.getDescription());
//                descritionEdit->setDisabled(true);
//                fileEdit->setText(a1.getFile());
//                fileEdit->setDisabled(true);
//            }
//            if(it.current().getType()=="5Tache"){
//                textEdit->setHidden(true);
//                textlabel->setHidden(true);
//                descritionEdit->setHidden(true);
//                descriptionlabel->setHidden(true);
//                fileEdit->setHidden(true);
//                filelabel->setHidden(true);
//                actionlabel->setHidden(false);
//                actionEdit->setHidden(false);
//                prioritelabel->setHidden(false);
//                prioriteEdit->setHidden(false);
//                dateEchlabel->setHidden(false);
//                dateEchEdit->setHidden(false);
//                statutlabel->setHidden(false);
//                statutEdit->setHidden(false);
//                ccentral->insertLayout(4,caction);
//                ccentral->insertLayout(5,cpriorite);
//                ccentral->insertLayout(6,cdateEch);
//                ccentral->insertLayout(7,cstatut);
//                Notes* n=it.current().clone();
//                Tache& a1 = dynamic_cast<Tache&>(*n);
//                actionEdit->setText(a1.getAction());
//                actionEdit->setDisabled(true);
//                prioriteEdit->setText(a1.getPriorite());
//                prioriteEdit->setDisabled(true);
//                dateEchEdit->setText(a1.getDateEch());
//                dateEchEdit->setDisabled(true);
//                statutEdit->setText(a1.getStatut());
//                statutEdit->setDisabled(true);
//            }
//        }
//    }
//    sauver->setDisabled(true);
//}

// void FenPrincipale::activerEditer(){
//	 restaurer->setDisabled(false);
//     titreEdit->setDisabled(false);
//     dateCreaEdit->setDisabled(false);
//     dateModifEdit->setDisabled(false);
//     textEdit->setDisabled(false);
//     descritionEdit->setDisabled(false);
//     fileEdit->setDisabled(false);
//     actionEdit->setDisabled(false);
//     prioriteEdit->setDisabled(false);
//     dateEchEdit->setDisabled(false);
//     statutEdit->setDisabled(false);
// }

//  void FenPrincipale::activerSauver(QString str){
//      sauver->setEnabled(true);
//  }

//  void FenPrincipale::sauverNote(){
//      NotesManager& m=NotesManager::recupererInstance();
//      NotesManager::Iterator it=m.getIterator();
//      while(!it.isDone() && it.current().getId()!=idEdit->text()){
//          it.next();
//      }
//      if(!it.isDone()){
//          Notes* n=it.current().clone();
//          if(it.current().getType()=="7Article"){
//              Article* a2 = dynamic_cast<Article*>(&it.current());
//              a2->setAncienneVersion(n);
//              a2->setTitre(titreEdit->text());
//              QString d1=dateCreaEdit->text();
//              QString strJ=d1.mid(0,2);
//              int j=strJ.toInt();
//              QString strM=d1.mid(3,2);
//              int m=strM.toInt();
//              QString strA=d1.mid(6,4);
//              int an=strA.toInt();
//              Date dateCrea=Date(j,m,an);
//              a2->setDateCrea(dateCrea);

//              QString d2=dateModifEdit->text();
//              QString str2J=d2.mid(0,2);
//              int j2=str2J.toInt();
//              QString str2M=d2.mid(3,2);
//              int m2=str2M.toInt();
//              QString str2A=d2.mid(6,4);
//              int an2=str2A.toInt();
//              Date dateModif=Date(j2,m2,an2);
//              a2->setDateModif(dateModif);

//              a2->setText(textEdit->toPlainText());
//              QMessageBox::information(this,"Sauvegarder","Article sauvegardé !");
//          }

//          if(it.current().getType()=="15NoteAvecFichier"){
//              NoteAvecFichier* a2 = dynamic_cast<NoteAvecFichier*>(&it.current());
//              a2->setAncienneVersion(n);
//              a2->setTitre(titreEdit->text());
//              QString d1=dateCreaEdit->text();
//              QString strJ=d1.mid(0,2);
//              int j=strJ.toInt();
//              QString strM=d1.mid(3,2);
//              int m=strM.toInt();
//              QString strA=d1.mid(6,4);
//              int an=strA.toInt();
//              Date dateCrea=Date(j,m,an);
//              a2->setDateCrea(dateCrea);

//              QString d2=dateModifEdit->text();
//              QString str2J=d2.mid(0,2);
//              int j2=str2J.toInt();
//              QString str2M=d2.mid(3,2);
//              int m2=str2M.toInt();
//              QString str2A=d2.mid(6,4);
//              int an2=str2A.toInt();
//              Date dateModif=Date(j2,m2,an2);
//              a2->setDateModif(dateModif);

//              a2->setDescription(descritionEdit->toPlainText());
//              a2->setFile(fileEdit->text());
//              QMessageBox::information(this,"Sauvegarder","Note avec fichier sauvegardée !");
//          }

//          if(it.current().getType()=="5Tache"){
//              Tache* a3 = dynamic_cast<Tache*>(&it.current());
//              a3->setAncienneVersion(n);
//              a3->setTitre(titreEdit->text());
//              QString d1=dateCreaEdit->text();
//              QString strJ=d1.mid(0,2);
//              int j=strJ.toInt();
//              QString strM=d1.mid(3,2);
//              int m=strM.toInt();
//              QString strA=d1.mid(6,4);
//              int an=strA.toInt();
//              Date dateCrea=Date(j,m,an);
//              a3->setDateCrea(dateCrea);

//              QString d2=dateModifEdit->text();
//              QString str2J=d2.mid(0,2);
//              int j2=str2J.toInt();
//              QString str2M=d2.mid(3,2);
//              int m2=str2M.toInt();
//              QString str2A=d2.mid(6,4);
//              int an2=str2A.toInt();
//              Date dateModif=Date(j2,m2,an2);
//              a3->setDateModif(dateModif);

//              a3->setAction(actionEdit->text());
//              a3->setPriorite(prioriteEdit->text());

//              QString d3=dateEchEdit->text();
//              QString str3J=d3.mid(0,2);
//              int j3=str3J.toInt();
//              QString str3M=d3.mid(3,2);
//              int m3=str3M.toInt();
//              QString str3A=d3.mid(6,4);
//              int an3=str3A.toInt();
//              Date dateEch=Date(j3,m3,an3);
//              a3->setAction(actionEdit->text());
//              a3->setStatut(statutEdit->text());
//              QMessageBox::information(this,"Sauvegarder","Tache sauvegardée !");
//          }


//          sauver->setDisabled(true);
//          textEdit->setDisabled(true);
//          idEdit->setDisabled(true);
//          titreEdit->setDisabled(true);
//          dateCreaEdit->setDisabled(true);
//          dateModifEdit->setDisabled(true);
//          descritionEdit->setDisabled(true);
//          fileEdit->setDisabled(true);
//          actionEdit->setDisabled(true);
//          prioriteEdit->setDisabled(true);
//          dateEchEdit->setDisabled(true);
//          statutEdit->setDisabled(true);
//          qDebug()<<it.current().getOldVersion(0).getTitre()<<"\n";
//        }
//      m.save();
////      listeNote = new QListWidget(dock);
////      for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
////          QString str=it.current().getTitre();
////          listeNote->addItem(str);
////      }
////      dock->setWidget(listeNote);
////      QObject::connect(listeNote, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(afficheNote(QListWidgetItem*)));

//  }

void FenPrincipale::afficherNewArticle() {
      FenetreNewNote* fe = new FenetreNewNote("article",this);
      fenNewNote = fe;
      setCentralWidget(fenNewNote);
      fenNewNote->show();
}

void FenPrincipale::afficherNewTache() {
      FenetreNewNote* fe = new FenetreNewNote("tache",this);
      fenNewNote = fe;
      setCentralWidget(fenNewNote);
      fenNewNote->show();
}

void FenPrincipale::afficherNewNoteFichier() {
      FenetreNewNote* fe = new FenetreNewNote("noteFichier",this);
      fenNewNote = fe;
      setCentralWidget(fenNewNote);
      fenNewNote->show();
  }

  // --- Interface Commune ---

  /*void FenPrincipale::afficherCreerNote() {
      idEdit->setDisabled(true);
      dateCreaEdit->setDisabled(true);
      dateModifEdit->setDisabled(true);
      idEdit->setHidden(true);
      idlabel->setHidden(true);
      titreEdit->setDisabled(false);

      titrelabel->setHidden(false);
      titreEdit->setHidden(false);
      dateCrealabel->setHidden(true);
      dateCreaEdit->setHidden(true);
      dateModiflabel->setHidden(true);
      dateModifEdit->setHidden(true);
      descriptionlabel->setHidden(true);
      descritionEdit->setHidden(true);
      filelabel->setHidden(true);
      fileEdit->setHidden(true);
      actionlabel->setHidden(true);
      actionEdit->setHidden(true);
      prioritelabel->setHidden(true);
      prioriteEdit->setHidden(true);
      dateEchlabel->setHidden(true);
      dateEchEdit->setHidden(true);
      statutlabel->setHidden(true);
      statutEdit->setHidden(true);
      textEdit->setHidden(true);
      textlabel->setHidden(true);

      editer->setHidden(true);
      sauver->setHidden(true);
      restaurer->setHidden(true);
      listeVersion->setHidden(true);
      titreEdit->clear();
  }

  void FenPrincipale::afficherStandard() {
      idEdit->setDisabled(true);
      titreEdit->setDisabled(true);
      dateCreaEdit->setDisabled(true);
      dateModifEdit->setDisabled(true);
      textEdit->setDisabled(true);
      descritionEdit->setDisabled(true);
      fileEdit->setDisabled(true);
      actionEdit->setDisabled(true);
      prioriteEdit->setDisabled(true);
      dateEchEdit->setDisabled(true);
      statutEdit->setDisabled(true);
      sauver->setDisabled(true);
      editer->setDisabled(true);
      restaurer->setDisabled(true);
      ajouter->setDisabled(true);
      ajoutTache->setDisabled(true);
      ajoutNoteFichier->setDisabled(true);

      idEdit->setHidden(false);
      idlabel->setHidden(false);
      titrelabel->setHidden(false);
      titreEdit->setHidden(false);
      dateCrealabel->setHidden(false);
      dateCreaEdit->setHidden(false);
      dateModiflabel->setHidden(false);
      dateModifEdit->setHidden(false);
      textEdit->setHidden(true);
      textlabel->setHidden(true);
      descriptionlabel->setHidden(true);
      descritionEdit->setHidden(true);
      filelabel->setHidden(true);
      fileEdit->setHidden(true);
      actionlabel->setHidden(true);
      actionEdit->setHidden(true);
      prioritelabel->setHidden(true);
      prioriteEdit->setHidden(true);
      dateEchlabel->setHidden(true);
      dateEchEdit->setHidden(true);
      statutlabel->setHidden(true);
      statutEdit->setHidden(true);
      editer->setHidden(false);
      sauver->setHidden(false);
      restaurer->setHidden(false);
      ajouter->setHidden(true);
      ajoutTache->setHidden(true);
      ajoutNoteFichier->setHidden(true);
      listeVersion->setHidden(false);
  }

  // --  Interface Nouvel Article -----
  void FenPrincipale::afficherCreerArticle() {
      this->afficherCreerNote();
      textEdit->setDisabled(false);

      textEdit->setHidden(false);
      textlabel->setHidden(false);
      ccentral->insertLayout(4,ctext);
      ccentral->insertLayout(9,cboutonAjouter);
      ajouter->setHidden(false);
      ajouter->setDisabled(false);
      textEdit->clear();
  }


  void FenPrincipale::creerArticle() {
      const QString ti=titreEdit->text();
      const QString te= textEdit->toPlainText();
      NotesManager& m=NotesManager::recupererInstance();
      NotesManager::Iterator it=m.getIterator();
      QString id;
      int intid;
      if (m.getnbNotes()==0) id="1";
      else {
          while(!it.isDone()){
             it.next();
          }
          it.previous();
          intid=it.current().getId().toInt();
          intid++;
          id=QString::number(intid);
      }
      //id=m.genereId();
      qDebug()<<id<<"\n";
      Article a=m.getNewArticle(id,ti,te);
      QMessageBox::information(this,"Ajouter","Article ajouté !");
      m.save();

      this->afficherStandard();

      QString titre=a.getTitre();
      listeNote->addItem(titre);
  }

  // --- Interface Tache --- 

  void FenPrincipale::afficherCreerTache() {
    afficherCreerNote();
    actionEdit->setDisabled(false);
    prioriteEdit->setDisabled(false);
    dateEchEdit->setDisabled(false);
    statutEdit->setDisabled(false);

    actionlabel->setHidden(false);
    actionEdit->setHidden(false);
    prioritelabel->setHidden(false);
    prioriteEdit->setHidden(false);
    dateEchlabel->setHidden(false);
    dateEchEdit->setHidden(false);
    statutlabel->setHidden(false);
    statutEdit->setHidden(false);
    ccentral->insertLayout(4,caction);
    ccentral->insertLayout(5,cpriorite);
    ccentral->insertLayout(6,cdateEch);
    ccentral->insertLayout(7,cstatut);
    ccentral->insertLayout(9,cboutonAjouterTache);
    ajoutTache->setHidden(false);
    ajoutTache->setDisabled(false);

    actionEdit->clear();
    prioriteEdit->clear();
    dateEchEdit->clear();
    statutEdit->clear();    

  }

  void FenPrincipale::creerTache() {
      const QString ti=titreEdit->text();
      const QString ac= actionEdit->text();
      const QString pr=prioriteEdit->text();
      const QString st= statutEdit->text();
      const QString d= dateEchEdit->text();
      NotesManager& m=NotesManager::recupererInstance();
      NotesManager::Iterator it=m.getIterator();
      QString id;
      int intid;
      if (m.getnbNotes()==0) id="1";
      else {
          while(!it.isDone()){
             it.next();
          }
          it.previous();
          intid=it.current().getId().toInt();
          intid++;
          id=QString::number(intid);
      }
      Tache a=m.getNewTache(id,ti,ac,pr,st);
      QMessageBox::information(this,"Ajouter","Tache ajoutée !");
      m.save();

      this->afficherStandard();

      QString titre=a.getTitre();
      listeNote->addItem(titre);
  }

  // --- Interface NoteFichier ---- 

  void FenPrincipale::afficherCreerNoteFichier() {
    this->afficherCreerNote();
    descritionEdit->setDisabled(false);
    fileEdit->setDisabled(false);

    descriptionlabel->setHidden(false);
    descritionEdit->setHidden(false);
    filelabel->setHidden(false);
    fileEdit->setHidden(false);
    ccentral->insertLayout(4,cdescription);
    ccentral->insertLayout(5,cfile);
    ccentral->insertLayout(9,cboutonAjouterNoteFichier);
    ajoutNoteFichier->setHidden(false);
    ajoutNoteFichier->setDisabled(false);

    descritionEdit->clear();
    fileEdit->clear();
  }

  void FenPrincipale::creerNoteFichier() {
      const QString ti=titreEdit->text();
      const QString de=descritionEdit->toPlainText();
      const QString f=fileEdit->text();
      NotesManager& m=NotesManager::recupererInstance();
      NotesManager::Iterator it=m.getIterator();
      QString id;
      int intid;
      if (m.getnbNotes()==0) id="1";
      else {
          while(!it.isDone()){
             it.next();
          }
          it.previous();
          intid=it.current().getId().toInt();
          intid++;
          id=QString::number(intid);
      }
      qDebug()<<id<<"\n";
      NoteAvecFichier a=m.getNewNoteAvecFichier(id,ti,de,f);
      QMessageBox::information(this,"Ajouter","NoteFichier ajouté !");
      m.save();

      this->afficherStandard();

      QString titre=a.getTitre();
      listeNote->addItem(titre);
  }*/

/*void FenPrincipale::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "(*.xml)");
    //load(fichier);
}*/
