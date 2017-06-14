#include "versions.h"
#include "notes.h"
#include "notemanager.h"
#include "fenetreprincipale.h"
#include "editeurnote.h"

#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
#include <QDomDocument>
#include <QDomNode>
#include <QXmlStreamWriter>
#include <QtWidgets>
#include <QComboBox>

using namespace std;



void VersionsManager::addVersion( Notes* n,QString& id)
	{
    versions.push_back(n);//On ajoute la note au vecteur courant
    nbVersions++;// nbVersions est désormais le numéro de version que l'on va implémenter
    QString	idSearch=vId;
    QDomDocument dom("mon_xml");
    QFile doc_xml("versions.xml");
    if(!doc_xml.open(QIODevice::ReadOnly))
    {
        //QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
        doc_xml.close();
        return;
    }
    if(!dom.setContent(&doc_xml))
    {
       // QMessageBox::critical(this,"Erreur","Impossible d'ouvrir le ficher XML");
        doc_xml.close();
        return;
    }
    doc_xml.close();
    
    QDomElement root = dom.documentElement().firstChildElement("versions");
    QDomElement child = root.firstChildElement();
      while( !child.isNull() ) {
        if (child.attributeNode("key").value()==idSearch){
            child = root.firstChildElement();
            QString type = child.tagName();
            child.appendChild(VersionXMLFactory(type,n,dom));
            break;}
        else{
        child = child.nextSiblingElement();}
      }
      if (child.isNull()){
          QString type="new";
          child.appendChild(VersionXMLFactory(type,n,dom));
          addVersion(n,id);
          loadVersion(id);
      }
      QFile newfile("versions.xml");
      if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
          throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
      QTextStream stream(&newfile);

    QString write_doc = dom.toString();

    stream << write_doc;
	}

void VersionsManager::loadVersion(const QString& idSearch) {
    versions.clear();
    nbVersions=0;//On vide le vecteur du VersionsManager
    QFile fin(VersionsManager::vFile);
    vId=idSearch; //Le chargement met automatiquement la valeur de l'id du VersionsManager à jour

    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) { // Erreur d'ouverture
        throw NotesException("Erreur ouverture fichier versions");
    }

    QXmlStreamReader xml(&fin);//Chargement du XML dans le parser
    while(!xml.atEnd()  && !xml.hasError()) { //On vient parser tout le document versions.xml à la recherche de l'id
        QXmlStreamReader::TokenType token = xml.readNext();
        if(token == QXmlStreamReader::StartDocument) continue;
        if(token == QXmlStreamReader::StartElement) {
            if(xml.name() == "versions") continue;
            QXmlStreamAttributes attributes= xml.attributes();
            if (xml.name()=="id" && attributes.value("key").toString()==idSearch){ //Si on trouve l'id recherché, on récupère les versions quitte la boucle while
                if(xml.name() == "article") {loadArticleFromXML(versions, xml,idSearch);}
                if(xml.name() == "noteAvecFichier") {loadFichierFromXML(versions, xml,idSearch);}
                if(xml.name() == "tache") {loadTacheFromXML(versions, xml,idSearch);}break;}}}

    if(xml.hasError()) {//Erreur d'écriture du fichier
        throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    xml.clear();//Nettoyage du parser
}

void VersionsManager::loadArticleFromXML(vector<Notes*> versions, QXmlStreamReader& xml,const QString& idSearch){
                QString titre;
                QString d1;
                QString d2;
                QString text;
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "version")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

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
                Article* a=new Article(idSearch,titre,text);

                QString strJ=d1.mid(0,2);
                int j=strJ.toInt();
                QString strM=d1.mid(3,2);
                int m=strM.toInt();
                QString strA=d1.mid(6,4);
                int an=strA.toInt();
                Date dateCrea=Date(j,m,an);
                a->setDateCrea(dateCrea);

                QString str2J=d2.mid(0,2);
                int j2=str2J.toInt();
                QString str2M=d2.mid(3,2);
                int m2=str2M.toInt();
                QString str2A=d2.mid(6,4);
                int an2=str2A.toInt();
                Date dateModif=Date(j2,m2,an2);
                a->setDateModif(dateModif);

                versions.push_back(a);
            }

void VersionsManager::loadFichierFromXML(vector<Notes*> versions, QXmlStreamReader& xml,const QString& idSearch){


                QString id;
                QString titre;
                QString d1;
                QString d2;
                QString description;
                QString file;
                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "version")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {


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

                NoteAvecFichier* a= new NoteAvecFichier(id,titre,description,file);

                QString strJ=d1.mid(0,2);
                int j=strJ.toInt();
                QString strM=d1.mid(3,2);
                int m=strM.toInt();
                QString strA=d1.mid(6,4);
                int an=strA.toInt();
                Date dateCrea=Date(j,m,an);
                a->setDateCrea(dateCrea);

                QString str2J=d2.mid(0,2);
                int j2=str2J.toInt();
                QString str2M=d2.mid(3,2);
                int m2=str2M.toInt();
                QString str2A=d2.mid(6,4);
                int an2=str2A.toInt();
                Date dateModif=Date(j2,m2,an2);
                a->setDateModif(dateModif);

                versions.push_back(a);
            }

void VersionsManager::loadTacheFromXML(vector<Notes*> versions, QXmlStreamReader& xml, const QString& idSearch){

                QString id;
                QString titre;
                QString d1;
                QString d2;
                QString action;
                QString priorite;
                QString d3;
                QString statut;

                xml.readNext();
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "version")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {

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

                Tache* a= new Tache(idSearch,titre,action,priorite,statut);

                QString strJ=d1.mid(0,2);
                int j=strJ.toInt();
                QString strM=d1.mid(3,2);
                int m=strM.toInt();
                QString strA=d1.mid(6,4);
                int an=strA.toInt();
                Date dateCrea=Date(j,m,an);
                a->setDateCrea(dateCrea);

                QString str2J=d2.mid(0,2);
                int j2=str2J.toInt();
                QString str2M=d2.mid(3,2);
                int m2=str2M.toInt();
                QString str2A=d2.mid(6,4);
                int an2=str2A.toInt();
                Date dateModif=Date(j2,m2,an2);
                a->setDateModif(dateModif);

                QString str3J=d3.mid(0,2);
                int j3=str3J.toInt();
                QString str3M=d3.mid(3,2);
                int m3=str3M.toInt();
                QString str3A=d3.mid(6,4);
                int an3=str3A.toInt();
                Date dateEch=Date(j3,m3,an3);
                a->setDateEch(dateEch);

                versions.push_back(a);
            }

VersionsManager::VersionsManager():nbVersions(0),vId(""),vFile("versions.xml"){}
		
VersionsManager::~VersionsManager(){
    for(auto element : versions) delete element;
    versions.clear();
}

void VersionsManager::restoreVersion(const QString& id, unsigned int numeroVersion){

    NotesManager& m=NotesManager::recupererInstance();
    FenPrincipale& fp = FenPrincipale::getInstance();
    VersionsManager& v=VersionsManager::recupererInstance();

m.supprimerNote(id);
m.addNotes(versions[numeroVersion]);
}



VersionsManager::Handler VersionsManager::handler=VersionsManager::Handler(); //un objet handler de type Handler initialisé avec le constructeur Handler

VersionsManager& VersionsManager::getInstance(){
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

QDomElement VersionsManager::VersionXMLFactory(QString& type, Notes* n,QDomDocument doc){
    QDomElement newNodeTag = doc.createElement(QString("version"));
    newNodeTag.setAttribute("num", this->nbVersions); // L'attribut id vaudra 2.
    if (type=="article"){
        Article& a1 = dynamic_cast<Article&>(*n);
        QDomNode newNodeTitre = doc.createTextNode(QString("titre"));
        newNodeTitre.setNodeValue(a1.getTitre());
        QDomNode newNodeDateCrea = doc.createTextNode(QString("dateCrea"));
        newNodeDateCrea.setNodeValue(a1.getDateCrea());
        QDomNode newNodeDateModif = doc.createTextNode(QString("dateModif"));
        newNodeDateModif.setNodeValue(a1.getDateModif());
        QDomNode newNodeText = doc.createTextNode(QString("text"));
        newNodeText.setNodeValue(a1.getText());
        newNodeTag.appendChild(newNodeTitre);
        newNodeTag.appendChild(newNodeDateCrea);
        newNodeTag.appendChild(newNodeDateModif);
        newNodeTag.appendChild(newNodeText);}
    if (type=="tache"){
        Tache& t1 = dynamic_cast<Tache&>(*n);
        QDomNode newNodeTitre = doc.createTextNode(QString("titre"));
        newNodeTitre.setNodeValue(t1.getTitre());
        QDomNode newNodeDateCrea = doc.createTextNode(QString("dateCrea"));
        newNodeDateCrea.setNodeValue(t1.getDateCrea());
        QDomNode newNodeDateModif = doc.createTextNode(QString("dateModif"));
        newNodeDateModif.setNodeValue(t1.getDateModif());
        QDomNode newNodeAction = doc.createTextNode(QString("action"));
        newNodeAction.setNodeValue(t1.getAction());
        QDomNode newNodePriorite = doc.createTextNode(QString("priorite"));
        newNodePriorite.setNodeValue(t1.getPriorite());
        QDomNode newNodeDateEch = doc.createTextNode(QString("dateEch"));
        newNodeDateEch.setNodeValue(t1.getDateEch());
        QDomNode newNodeStatut = doc.createTextNode(QString("statut"));
        newNodeStatut.setNodeValue(t1.getStatut());
        
        newNodeTag.appendChild(newNodeTitre);
        newNodeTag.appendChild(newNodeDateCrea);
        newNodeTag.appendChild(newNodeDateModif);

        newNodeTag.appendChild(newNodeAction);
        newNodeTag.appendChild(newNodePriorite);
        newNodeTag.appendChild(newNodeDateEch);
        newNodeTag.appendChild(newNodeStatut);
    }
    if (type=="noteAvecFichier"){
        NoteAvecFichier& f1 = dynamic_cast<NoteAvecFichier&>(*n);
        QDomNode newNodeTitre = doc.createTextNode(QString("titre"));

        newNodeTitre.setNodeValue(f1.getTitre());
        QDomNode newNodeDateCrea = doc.createTextNode(QString("dateCrea"));
        newNodeDateCrea.setNodeValue(f1.getDateCrea());
        QDomNode newNodeDateModif = doc.createTextNode(QString("dateModif"));
        newNodeDateModif.setNodeValue(f1.getDateModif());
        QDomNode newNodeDescription = doc.createTextNode(QString("description"));
        newNodeDescription.setNodeValue(f1.getDescription());
        QDomNode newNodeFile = doc.createTextNode(QString("file"));
        newNodeFile.setNodeValue(f1.getFile());
                
        newNodeTag.appendChild(newNodeTitre);
        newNodeTag.appendChild(newNodeDateCrea);
        newNodeTag.appendChild(newNodeDateModif);
        newNodeTag.appendChild(newNodeDescription);
        newNodeTag.appendChild(newNodeFile);}
    if (type=="new"){

        QDomElement newNodeTag = doc.createElement(QString("id"));
        QDomElement newType;
        newNodeTag.setAttribute("key", this->vId); // L'attribut id vaudra 2.
        if(n->getType()=="7Article"){newType = doc.createElement(QString("article"));}
        if(n->getType()=="15NoteAvecFichier"){newType = doc.createElement(QString("noteAvecFichier"));}
        if(n->getType()=="5Tache"){ newType = doc.createElement(QString("tache"));}
        newNodeTag.appendChild(newType);
    }
    return newNodeTag;
}

void VersionsManager::updateComboBox(QComboBox* combobox){
    loadVersion(vId);
    combobox->clear();
    for(unsigned int i=0; i<versions.size();i++)
    {

       combobox->addItem("Version ",vId);
}
}
//+i+" du "+versions[i]->getDateModif()
