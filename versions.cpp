/*void VersionsManager::addVersion(constNotes* n) 
	{
    versions.push_back(n);//On ajoute la note au vecteur courant
    nbVersions++;// nbVersions est désormais le numéro de version que l'on va implémenter
	
	
	
	QDomElement dom_element = new QDomDocument();//Ouverture du DOM
	QFile xml_doc(vFile);//Nom de fichier fixe
	if(!xml_doc.open(QIODevice::ReadOnly))
		{
		QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert. Vérifiez que le nom est le bon et que le document est bien placé");
		return;
		}
	if (!dom.setContent(&xml_doc)) 
		{
		xml_doc.close();
		QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
		return;
		}
	
	QDomNode noeud = dom_element.firstChild();
	while(noeud.attribute["id"]!=id)
		{
		if(!dom_element.isNull())
			QMessageBox::information(this, "Nom de la balise", "Le nom de la balise est " + dom_element.tagName());
                noeud = noeud.nextSibling();
		}

	QDomElement add = dom.createElement(nbVersions);
	add.setAttribute("titre", n.getId()); 
	noeud.appendChild(add)

	}
*/
VersionsManager::VersionsManager():nbVersions(0),filename(""),vId(0)
		
VersionsManager::~VersionsManager(){
    for(auto element : versions) delete element;
    versions.clear();
}
/*
VersionsManager::restoreVersion(const QString& id, const unsigned int numeroVersion){

//APPEL A NOTES MANAGER delete(id)
//APPEL A NOTE MANAGER add (n)  
}
  
void NotesManager::loadVersion(const QString& id) {
	vId=id;
    QFile fin(filename);
    // If we can't open it, let's show an error message.
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw NotesException("Erreur ouverture fichier notes");
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
                QString id;
                QString titre;
                QString d1;
                QString d2;
                QString text;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "article")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); id=xml.text().toString();
                            qDebug()<<"id="<<id<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "dateCrea") {
                            xml.readNext();
                            d1=xml.text().toString();
                            qDebug()<<"dateCrea="<<d1<<"\n";
                        }
                        if(xml.name() == "dateModif") {
                            xml.readNext();
                            d2=xml.text().toString();
                            qDebug()<<"dateModif="<<d2<<"\n";
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
                qDebug()<<"ajout note "<<id<<"\n";
                Article& a=getNewArticle(id,titre,text);

                QString strJ=d1.mid(0,2);
                int j=strJ.toInt();
                QString strM=d1.mid(3,2);
                int m=strM.toInt();
                QString strA=d1.mid(6,4);
                int an=strA.toInt();
                Date dateCrea=Date(j,m,an);
                a.setDateCrea(dateCrea);

                QString str2J=d2.mid(0,2);
                int j2=str2J.toInt();
                QString str2M=d2.mid(3,2);
                int m2=str2M.toInt();
                QString str2A=d2.mid(6,4);
                int an2=str2A.toInt();
                Date dateModif=Date(j2,m2,an2);
                a.setDateModif(dateModif);

               //FenPricipale.liste->addItem(titre);
            }

            if(xml.name() == "noteAvecFichier") {
                qDebug()<<"new NoteAvecFichier\n";
                QString id;
                QString titre;
                QString d1;
                QString d2;
                QString description;
                QString file;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "noteAvecFichier")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); id=xml.text().toString();
                            qDebug()<<"id="<<id<<"\n";
                        }

                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "dateCrea") {
                            xml.readNext();
                            d1=xml.text().toString();
                            qDebug()<<"dateCrea="<<d1<<"\n";
                        }
                        if(xml.name() == "dateModif") {
                            xml.readNext();
                            d2=xml.text().toString();
                            qDebug()<<"dateModif="<<d2<<"\n";
                        }
                        // We've found text
                        if(xml.name() == "description") {
                            xml.readNext();
                            description=xml.text().toString();
                            qDebug()<<"description="<<description<<"\n";
                        }
                        if(xml.name() == "file") {
                            xml.readNext();
                            file=xml.text().toString();
                            qDebug()<<"file="<<file<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout note "<<id<<"\n";
                NoteAvecFichier& a=getNewNoteAvecFichier(id,titre,description,file);

                QString strJ=d1.mid(0,2);
                int j=strJ.toInt();
                QString strM=d1.mid(3,2);
                int m=strM.toInt();
                QString strA=d1.mid(6,4);
                int an=strA.toInt();
                Date dateCrea=Date(j,m,an);
                a.setDateCrea(dateCrea);

                QString str2J=d2.mid(0,2);
                int j2=str2J.toInt();
                QString str2M=d2.mid(3,2);
                int m2=str2M.toInt();
                QString str2A=d2.mid(6,4);
                int an2=str2A.toInt();
                Date dateModif=Date(j2,m2,an2);
                a.setDateModif(dateModif);

               //FenPricipale.liste->addItem(titre);
            }

            if(xml.name() == "tache") {
                qDebug()<<"new tache\n";
                QString id;
                QString titre;
                QString d1;
                QString d2;
                QString action;
                QString priorite;
                QString d3;
                QString statut;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "tache")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        // We've found identificteur.
                        if(xml.name() == "id") {
                            xml.readNext(); id=xml.text().toString();
                            qDebug()<<"id="<<id<<"\n";
                        }
                        // We've found titre.
                        if(xml.name() == "titre") {
                            xml.readNext(); titre=xml.text().toString();
                            qDebug()<<"titre="<<titre<<"\n";
                        }
                        if(xml.name() == "dateCrea") {
                            xml.readNext();
                            d1=xml.text().toString();
                            qDebug()<<"dateCrea="<<d1<<"\n";
                        }
                        if(xml.name() == "dateModif") {
                            xml.readNext();
                            d2=xml.text().toString();
                            qDebug()<<"dateModif="<<d2<<"\n";
                        }                        
                        if(xml.name() == "action") {
                            xml.readNext();
                            action=xml.text().toString();
                            qDebug()<<"action="<<action<<"\n";
                        }
                        if(xml.name() == "priorite") {
                            xml.readNext();
                            priorite=xml.text().toString();
                            qDebug()<<"priorite="<<priorite<<"\n";
                        }
                        if(xml.name() == "dateEch") {
                            xml.readNext();
                            d3=xml.text().toString();
                            qDebug()<<"dateEch="<<d3<<"\n";
                        }
                        if(xml.name() == "statut") {
                            xml.readNext();
                            statut=xml.text().toString();
                            qDebug()<<"statut="<<statut<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout tache "<<id<<"\n";
                Tache& a=getNewTache(id,titre,action,priorite,statut);

                QString strJ=d1.mid(0,2);
                int j=strJ.toInt();
                QString strM=d1.mid(3,2);
                int m=strM.toInt();
                QString strA=d1.mid(6,4);
                int an=strA.toInt();
                Date dateCrea=Date(j,m,an);
                a.setDateCrea(dateCrea);

                QString str2J=d2.mid(0,2);
                int j2=str2J.toInt();
                QString str2M=d2.mid(3,2);
                int m2=str2M.toInt();
                QString str2A=d2.mid(6,4);
                int an2=str2A.toInt();
                Date dateModif=Date(j2,m2,an2);
                a.setDateModif(dateModif);

                QString str3J=d3.mid(0,2);
                int j3=str3J.toInt();
                QString str3M=d3.mid(3,2);
                int m3=str3M.toInt();
                QString str3A=d3.mid(6,4);
                int an3=str3A.toInt();
                Date dateEch=Date(j3,m3,an3);
                a.setDateEch(dateEch);

               //FenPricipale.liste->addItem(titre);
            }


        }
    }
    // Error handling.
    if(xml.hasError()) {
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
*/
VersionsManager::Handler NotesManager::handler=VersionsManager::Handler(); //un objet handler de type Handler initialisé avec le constructeur Handler

VersionsManager& NotesManager::getInstance(){
    if(handler.instance==nullptr){
        handler.instance=new VersionsManager;
        return *handler.instance;
    }
    else{
        throw NotesException("Erreur, on a deja un note manager");
        return *handler.instance;
    }
}

void VersionsManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}

VersionsManager& VersionsManager::recupererInstance(){
    if(handler.instance==nullptr) throw NotesException("Erreur, aucun note manager existant\n");
    else return *handler.instance;
}
