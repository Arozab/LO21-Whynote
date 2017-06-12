#include "relation.h"
#include "couplemanager.h"
#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
using namespace std;

void CoupleManager::addCouple(couple* n) {
    couples.push_back(n);
    nbCouple++;
}


CoupleManager::CoupleManager():nbCouple(0),filename(""){}

CoupleManager::~CoupleManager(){
    //save();
    for(auto element : couples) delete element;
    // on vide le tableau
    couples.clear();

}

CoupleManager::Handler CoupleManager::handler=CoupleManager::Handler(); //un objet handler de type Handler initialisé avec le constructeur Handler

CoupleManager& CoupleManager::getInstance(){
    if(handler.instance==nullptr){
        handler.instance=new CoupleManager;
        return *handler.instance;
    }
    else{
        throw NotesException("Erreur, on a deja un couple manager");
        return *handler.instance;
    }
}

void CoupleManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}

CoupleManager& CoupleManager::recupererInstance(){
    if(handler.instance==nullptr) throw NotesException("Erreur, aucun couple manager existant\n");
    else return *handler.instance;
}

couple& CoupleManager::getNewCouple(const QString& l, int nb1,int nb2){
	couple* c=new couple(l,nb1,nb2);
	addCouple(c);
	return *c;
}


void CoupleManager::load(const QString& f) {
    filename=f;
    QFile fin(filename);
    if (!fin.open(QIODevice::ReadOnly | QIODevice::Text)) {
        //throw NotesException("Erreur ouverture fichier notes");
    }
    QXmlStreamReader xml(&fin);
    while(!xml.atEnd() && !xml.hasError()) {
        // Read next element.
        QXmlStreamReader::TokenType token = xml.readNext();
        // If token is just StartDocument, we'll go to next.
        if(token == QXmlStreamReader::StartDocument) continue;
        // If token is StartElement, we'll see if we can read it.
        if(token == QXmlStreamReader::StartElement) {
            // If it's named taches, we'll go to the next
            if(xml.name() == "couple") {
                qDebug()<<"new couple\n";
                QString label;
                int n1;
                int n2;
                QXmlStreamAttributes attributes = xml.attributes();
                xml.readNext();
                //We're going to loop over the things because the order might change.
                //We'll continue the loop until we hit an EndElement named article.
                while(!(xml.tokenType() == QXmlStreamReader::EndElement && xml.name() == "couple")) {
                    if(xml.tokenType() == QXmlStreamReader::StartElement) {
                        if(xml.name() == "label") {
                            xml.readNext(); label=xml.text().toString();
                            qDebug()<<"label="<<label<<"\n";
                        }
                        if(xml.name() == "note1") {
                            xml.readNext(); n1=xml.text().toInt();
                            qDebug()<<"note1="<<n1<<"\n";
                        }
                        if(xml.name() == "note2") {
                            xml.readNext(); n2=xml.text().toInt();
                            qDebug()<<"note2="<<n2<<"\n";
                        }
                    }
                    // ...and next...
                    xml.readNext();
                }
                qDebug()<<"ajout couple "<<label<<"\n";
                couple& c=getNewCouple(label,n1,n1);
            }
        }
    }
    // Error handling.
    if(xml.hasError()) {
        //throw NotesException("Erreur lecteur fichier notes, parser xml");
    }
    // Removes any device() or data from the reader * and resets its internal state to the initial state.
    xml.clear();
    qDebug()<<"fin load\n";
}
