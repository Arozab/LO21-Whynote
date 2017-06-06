#include "FenPrincipale.h"
#include "notes.h"

FenPrincipale::FenPrincipale(NotesManager& m)
{
    zoneCentrale = new QWidget;

    menuFichier = menuBar()->addMenu("Fichier");
        actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    dock = new QDockWidget(tr("Liste de Notes"));
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    liste = new QListWidget(dock);
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        QString str=it.current().getTitre();
        //str.append(" ");
        //str.append(it.current().getTitre());
        //liste->addItem(it.current().getTitre());
        liste->addItem(str);
    }
    dock->setWidget(liste);
    addDockWidget(Qt::LeftDockWidgetArea, dock);




    /*dock = new QDockWidget();
    bouton1 = new QPushButton("Afficher");
    dock->setWidget(bouton1);
    addDockWidget(Qt::LeftDockWidgetArea, dock);*/

    idlabel=new QLabel("id",this);
    titrelabel=new QLabel("titre",this);
    dateCrealabel=new QLabel("date creation",this);
    dateModiflabel=new QLabel("date modification",this);
    textlabel=new QLabel("texte",this);
    descriptionlabel=new QLabel("description",this);
    filelabel=new QLabel("file",this);
    idEdit=new QLineEdit(this);
    titreEdit=new QLineEdit(this);
    dateCreaEdit=new QLineEdit(this);
    dateModifEdit=new QLineEdit(this);
    textEdit=new QTextEdit(this);
    descritionEdit=new QTextEdit(this);
    fileEdit=new QLineEdit(this);
    idEdit->setDisabled(true);
    titreEdit->setDisabled(true);
    dateCreaEdit->setDisabled(true);
    dateModifEdit->setDisabled(true);
    textEdit->setDisabled(true);
    descritionEdit->setDisabled(true);
    fileEdit->setDisabled(true);
    textEdit->setHidden(true);
    textlabel->setHidden(true);
    descriptionlabel->setHidden(true);
    descritionEdit->setHidden(true);
    filelabel->setHidden(true);
    fileEdit->setHidden(true);
    editer=new QPushButton("Editer",this);
    sauver=new QPushButton("Sauver",this);


    ctext = new QHBoxLayout;
    ctext->addWidget(textlabel);
    ctext->addWidget(textEdit);
    cdescription = new QHBoxLayout;
    cdescription->addWidget(descriptionlabel);
    cdescription->addWidget(descritionEdit);
    cfile = new QHBoxLayout;
    cfile->addWidget(filelabel);
    cfile->addWidget(fileEdit);
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
    ccentral = new QVBoxLayout;
    ccentral->addLayout(cid);
    ccentral->addLayout(ctitre);
    ccentral->addLayout(cdateCrea);
    ccentral->addLayout(cdateModif);
    ccentral->addLayout(cboutons);
    zoneCentrale->setLayout(ccentral);
    setCentralWidget(zoneCentrale);

    QObject::connect(sauver,SIGNAL(clicked()),this,SLOT(sauverNote()));
    QObject::connect(liste, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(afficheNote(QListWidgetItem*)));
    QObject::connect(editer, SIGNAL(clicked()),this,SLOT(activerEditer()));

    QObject::connect(titreEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(dateCreaEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(dateModifEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(textEdit,SIGNAL(textChanged()),this,SLOT(activerSauver()));
    QObject::connect(descritionEdit,SIGNAL(textChanged()),this,SLOT(activerSauver()));
    QObject::connect(fileEdit,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));

    sauver->setDisabled(true);


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

            idEdit->setDisabled(true);
            titreEdit->setDisabled(true);
            dateCreaEdit->setDisabled(true);
            dateModifEdit->setDisabled(true);

            qDebug()<<"type : "<<it.current().getType()<<"\n";
            if(it.current().getType()=="7Article"){
                descriptionlabel->setHidden(true);
                descritionEdit->setHidden(true);
                filelabel->setHidden(true);
                fileEdit->setHidden(true);
                textEdit->setHidden(false);
                textlabel->setHidden(false);
                ccentral->insertLayout(4,ctext);
                Notes* n=it.current().clone();
                Article& a1 = dynamic_cast<Article&>(*n);
                textEdit->setText(a1.getText());
                textEdit->setDisabled(true);

            }
            if(it.current().getType()=="15NoteAvecFichier"){
                textEdit->setHidden(true);
                textlabel->setHidden(true);
                descritionEdit->setHidden(false);
                descriptionlabel->setHidden(false);
                fileEdit->setHidden(false);
                filelabel->setHidden(false);
                ccentral->insertLayout(4,cdescription);
                ccentral->insertLayout(5,cfile);
                Notes* n=it.current().clone();
                NoteAvecFichier& a1 = dynamic_cast<NoteAvecFichier&>(*n);
                descritionEdit->setText(a1.getDescription());
                descritionEdit->setDisabled(true);
                fileEdit->setText(a1.getFile());
                fileEdit->setDisabled(true);
            }
        }
    }
    sauver->setDisabled(true);
}

 void FenPrincipale::activerEditer(){
     titreEdit->setDisabled(false);
     dateCreaEdit->setDisabled(false);
     dateModifEdit->setDisabled(false);
     textEdit->setDisabled(false);
     descritionEdit->setDisabled(false);
     fileEdit->setDisabled(false);
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
          if(it.current().getType()=="7Article"){
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
          }

          if(it.current().getType()=="15NoteAvecFichier"){
              NoteAvecFichier* a2 = dynamic_cast<NoteAvecFichier*>(&it.current());
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

              a2->setDescription(descritionEdit->toPlainText());
              a2->setFile(fileEdit->text());
              QMessageBox::information(this,"Sauvegarder","Note avec fichier sauvegardée !");
          }

          sauver->setDisabled(true);
          textEdit->setDisabled(true);
          idEdit->setDisabled(true);
          titreEdit->setDisabled(true);
          dateCreaEdit->setDisabled(true);
          dateModifEdit->setDisabled(true);
          descritionEdit->setDisabled(true);
          fileEdit->setDisabled(true);
          qDebug()<<it.current().getOldVersion(0).getTitre()<<"\n";
        }
      m.save();
      liste = new QListWidget(dock);
      for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
          QString str=it.current().getTitre();
          liste->addItem(str);
      }
      dock->setWidget(liste);
      QObject::connect(liste, SIGNAL(itemDoubleClicked(QListWidgetItem*)),this, SLOT(afficheNote(QListWidgetItem*)));

  }

/*void FenPrincipale::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "(*.xml)");
    //load(fichier);
}*/
