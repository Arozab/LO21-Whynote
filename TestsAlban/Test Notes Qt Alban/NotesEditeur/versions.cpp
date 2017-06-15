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
    qDebug()<<"ON EN EST LA !";
    versions.clear();
    qDebug()<<"ON EN EST LA !";
    nbVersions=0;//On vide le vecteur du VersionsManager
    qDebug()<<"ON EN EST LA !";
    vId=idSearch; //Le chargement met automatiquement la valeur de l'id du VersionsManager à jour

    QDomDocument doc;
        QFile file(VersionsManager::vFile);
        if (!file.open(QIODevice::ReadOnly) || !doc.setContent(&file))
            throw NotesException("Erreur ouverture fichier versions");
    qDebug()<<"ON EN EST LA !";


    qDebug()<<"CHARGEMENTDANSLEPARSER";
    QDomElement node=doc.elementById("versions");
    QDomNodeList ids = doc.elementsByTagName("id");
    for (int i = 0; i < ids.size(); i++) {
            QDomNode domnode = ids.item(i);
            QDomElement note=domnode.toElement();
            if (note.attributeNode("key").value()==idSearch){ qDebug()<<"JE T'AI TROUVE ENCULE";//Si on trouve l'id recherché, on récupère les versions quitte la boucle while
                QDomElement type=domnode.firstChild().toElement();
                if(type.tagName() == "article") {loadArticleFromXML( type,idSearch);}
                if(type.tagName() == "noteAvecFichier") {loadFichierFromXML(type,idSearch);}
                if(type.tagName() == "tache") {loadTacheFromXML( type,idSearch);}}}


    qDebug()<<"ON A FINI !";
}

void VersionsManager::loadArticleFromXML( QDomElement& xml,const QString& idSearch){
                }

void VersionsManager::loadFichierFromXML(QDomElement& xml,const QString& idSearch) {


                QString id;
                QString titre;
                QString d1;
                QString d2;
                QString description;
                QString file;
                QDomElement xmlelement=xml.toElement();
                QDomNodeList versions = xmlelement.elementsByTagName("version");
                    for (int i = 0; i < versions.size(); i++) {
                        QDomNode n = versions.item(i);
                        QString titre = n.firstChildElement("titre").text();
                        QString d1 = n.firstChildElement("dateCrea").text();
                        QString d2 = n.firstChildElement("dateModif").text();
                        QString description = n.firstChildElement("description").text();
                        QString file = n.firstChildElement("file").text();


                NoteAvecFichier* a= new NoteAvecFichier(idSearch,titre,description,file);
                qDebug()<<a->getId();
                qDebug()<<a->getTitre();
                qDebug()<<a->getDescription();
                qDebug()<<a->getFile();

                QString strJ=d1.mid(0,2);
                int j=strJ.toInt();
                QString strM=d1.mid(3,2);
                int m=strM.toInt();
                QString strA=d1.mid(6,4);
                int an=strA.toInt();
                Date dateCrea=Date(j,m,an);

                a->Notes::setDateCrea(dateCrea);
                qDebug()<<"REMPLISSAGE";
                QString str2J=d2.mid(0,2);
                int j2=str2J.toInt();
                QString str2M=d2.mid(3,2);
                int m2=str2M.toInt();
                QString str2A=d2.mid(6,4);
                int an2=str2A.toInt();
                Date dateModif=Date(j2,m2,an2);
                qDebug()<<"ON CREE CETTE NOTE";
                a->Notes::setDateModif(dateModif);
                qDebug()<<"JUSTE APRES CA PLANTE";
                this->versions.push_back(a);


}


}

void VersionsManager::loadTacheFromXML(QDomElement& xml, const QString& idSearch){
}

VersionsManager::VersionsManager():nbVersions(0),vId(""),vFile("versions.xml"){}
		
VersionsManager::~VersionsManager(){
    for(auto element : versions) delete element;
    versions.clear();
}

void VersionsManager::restoreVersion(int numeroVersion){

    NotesManager& m=NotesManager::recupererInstance();

    VersionsManager& v=VersionsManager::recupererInstance();

    QString type=typeid(versions[numeroVersion]).name();
    Notes& n=m.getNote(vId,type);
    Notes* note=&n;
qDebug()<<"TEST";
m.supprimerNote( vId);
qDebug()<<"TEST";
Notes* rest=versions[numeroVersion];
rest->getTitre();
m.addNotes(rest);
qDebug()<<"POUR LA RESTO HIP HIP HIP";
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

void VersionsManager::updateComboBox(QComboBox*& combobox, QString id){
    qDebug()<<"ET ON SE FAIT UN PETIT UPDATE AVEC L'ID "<<id;
    loadVersion(id);
    qDebug()<<"ON A DES VERSIONS ! "<<versions.size();
    combobox->clear();
    QString label;
    for(int i=0; i<versions.size();i++)
    {
        qDebug()<<"CA RAJOUTE";
       label="Version du "+versions[i]->getDateCrea()+ " modifiée le "+ versions[i]->getDateModif();
       combobox->addItem(label,i);
}
}
//+i+" du "+versions[i]->getDateModif()
