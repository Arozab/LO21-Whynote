#include "FenPrincipale.h"

FenPrincipale::FenPrincipale()
{
    zoneCentrale = new QWidget;

    menuFichier = menuBar()->addMenu("Fichier");
        actionQuitter = new QAction("&Quitter", this);
        menuFichier->addAction(actionQuitter);
        connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));

    liste = new QComboBox();
    liste->setMinimumContentsLength(30);

    bouton1 = new QPushButton("Ouvrir");

    layout = new QGridLayout;
    layout->addWidget(bouton1,0,1);
    layout->addWidget(liste,0,0);

    zoneCentrale->setLayout(layout);

    setCentralWidget(zoneCentrale);
    QObject::connect(bouton1,SIGNAL(clicked()),this,SLOT(ouvrirDialogue()));

}

void FenPrincipale::ouvrirDialogue()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "(*.xml)");
    load(fichier);
}


void FenPrincipale::load(QString f) {
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
