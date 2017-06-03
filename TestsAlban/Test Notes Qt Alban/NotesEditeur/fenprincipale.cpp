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
    connect(liste, SIGNAL(currentTextChanged(QString)),this, SLOT(afficheNote(QString)));

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
    ccentral = new QVBoxLayout;
    ccentral->addLayout(cid);
    ccentral->addLayout(ctitre);
    ccentral->addLayout(cdateCrea);
    ccentral->addLayout(cdateModif);
    zoneCentrale->setLayout(ccentral);
    setCentralWidget(zoneCentrale);

}

void FenPrincipale::afficheNote(const QString& titre){
    if (titre.isEmpty()){
        qDebug()<<"titre : "<<titre<<"\n";
        return;
    }
    else{
        qDebug()<<"titre : "<<titre<<"\n";
       // Notes& n=trouverNote(titre,m);
        //idEdit->setText(n.getId());
        idEdit->setText(titre);

    }
       /* for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
            liste->addItem(it.current().getTitre());
        }*/
}

/*Notes& FenPrincipale::trouverNote(const QString& titre,NotesManager& m){
    NotesManager::Iterator it=m.getIterator();
    while(!it.isDone() && it.current().getTitre()!=titre){
        it.next();
    }
    if(!it.isDone())
        return it.current();
}*/

/*void FenPrincipale::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "(*.xml)");
    //load(fichier);
}*/


/*void FenPrincipale::load(QString f) {
    QFile fin(f);
    // If we can't open it, let's show an error message.
   if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Erreur d'ouverture du fichier", "Le fichier n'as pas réussi à s'ouvrir correctement !");
   }
    // QXmlStreamReader takes any QIODevice.
    QXmlStreamReader xml(&fin);
    //qDebug()<<"debut fichier\n";
    // We'll parse the XML until we reach end of it.
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next.
            if(xml.name() == "notes") continue;
            // If it's named tache, we'll dig the information from there.
            if(xml.name() == "article") {
                qDebug()<<"new article\n";
                QString identificateur;
                QString titre;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); identificateur=xml.text().toString();
                            qDebug()<<"id="<<identificateur<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "title") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "text") {
                            xml.readNext();
                            text=xml.text().toString();
                            qDebug()<<"text="<<text<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<identificateur<<"\n";
                //addArticle(identificateur,titre,text);
                liste->addItem(titre);
            }
        }
    }
    // Error handling.
//    if(xml.hasError()) {
//        throw NotesException("Erreur lecteur fichier notes, parser xml");
//    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
*/
