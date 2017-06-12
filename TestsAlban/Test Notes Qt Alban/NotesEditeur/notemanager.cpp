#include "notes.h"
#include "notemanager.h"
#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
using namespace std;

void NotesManager::addNotes(Notes* n) {
    if (!notes.empty()) {
        for(unsigned int i=0; i<getnbNotes(); i++){
            if (notes[i]->getId()==n->getId()) throw NotesException("Erreur, creation d'une note deja existante");
        }
    }
    else{
        nbNotes=0;
    }
    notes.push_back(n);
    nbNotes++;
}

/*Notes& NotesManager::getNotes(const QString& id){
    for(unsigned int i=0;i<nbNotes;i++){
        if(notes[i]->getId()==id) return *notes[i];
    }
    throw NotesException("Erreur, l'Article n'existe pas");
}*/


void NotesManager::addArticles(Article* a){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
    }
    notes.push_back(a);
    nbNotes++;
}

Article& NotesManager::getNewArticle(const QString& id,const QString& ti,const QString& te){
    Article* n=new Article(id,ti,te);
    addNotes(n);
    return *n;
}


Article& NotesManager::getArticle(const QString& id){
    for(unsigned int i=0;i<nbNotes;i++){
        Article& a=dynamic_cast<Article&>(*notes[i]);
        if(notes[i]->getId()==id) return a ;
    }
    throw NotesException("Erreur, l'Article n'existe pas");
}


void NotesManager::addNoteAvecFichier(NoteAvecFichier* a){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
    }
    notes.push_back(a);
    nbNotes++;
}

NoteAvecFichier& NotesManager::getNewNoteAvecFichier(const QString& id,const QString& ti,const QString& de,const QString& fi){
    NoteAvecFichier* n=new NoteAvecFichier(id,ti,de,fi);
    addNotes(n);
    return *n;
}

NoteAvecFichier& NotesManager::getNoteAvecFichier(const QString& id){
    for(unsigned int i=0;i<nbNotes;i++){
        NoteAvecFichier& a=dynamic_cast<NoteAvecFichier&>(*notes[i]);
        if(notes[i]->getId()==id) return a;
    }
    throw NotesException("Erreur, la note n'existe pas");
}


void NotesManager::addTaches(Tache* a){
    for(unsigned int i=0; i<nbNotes; i++){
        if (notes[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
    }
    notes.push_back(a);
    nbNotes++;
}

Tache& NotesManager::getNewTache(const QString& id,const QString& ti,const QString& ac,const QString& pr,const QString& t){
    Tache* n=new Tache(id,ti,ac,pr,t);
    addNotes(n);
    return *n;
}

Tache& NotesManager::getTache(const QString& id){
    for(unsigned int i=0;i<nbNotes;i++){
        Tache& a=dynamic_cast<Tache&>(*notes[i]);
        if(notes[i]->getId()==id) return a;
    }
    throw NotesException("Erreur, la tache n'existe pas");
}



NotesManager::NotesManager():nbArticles(0),filename(""),nbNoteAvecFichier(0){}

NotesManager::~NotesManager(){
    //save();
    for(auto element : notes) delete element;
    // on vide le tableau
    notes.clear();

}

/*void NotesManager::save()const{
    ofstream fout(filename);
    for(unsigned int i=0; i<nbNotes; i++){
        fout<<*tabNotes[i];
    }
    fout.close();
}*/

void NotesManager::save() const {
    NotesManager& m=recupererInstance();
    QFile newfile(m.getFilename());
    if (!newfile.open(QIODevice::WriteOnly | QIODevice::Text))
        throw NotesException(QString("erreur sauvegarde notes : ouverture fichier xml"));
    QXmlStreamWriter stream(&newfile);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    stream.writeStartElement("notes");
    for(NotesManager::Iterator it=m.getIterator();!it.isDone();it.next()){
        if(it.current().getType()=="7Article"){
            stream.writeStartElement("article");
            stream.writeTextElement("id",it.current().getId());
            stream.writeTextElement("titre",it.current().getTitre());
            stream.writeTextElement("dateCrea",it.current().getDateCrea());
            stream.writeTextElement("dateModif",it.current().getDateModif());
            Notes* n=it.current().clone();
            Article& a1 = dynamic_cast<Article&>(*n);
            stream.writeTextElement("text",a1.getText());
            stream.writeEndElement();
        }
        if(it.current().getType()=="15NoteAvecFichier"){
            stream.writeStartElement("noteAvecFichier");
            stream.writeTextElement("id",it.current().getId());
            stream.writeTextElement("titre",it.current().getTitre());
            stream.writeTextElement("dateCrea",it.current().getDateCrea());
            stream.writeTextElement("dateModif",it.current().getDateModif());
            Notes* n=it.current().clone();
            NoteAvecFichier& a1 = dynamic_cast<NoteAvecFichier&>(*n);
            stream.writeTextElement("description",a1.getDescription());
            stream.writeTextElement("file",a1.getFile());
            stream.writeEndElement();
        }
        if(it.current().getType()=="5Tache"){
            stream.writeStartElement("tache");
            stream.writeTextElement("id",it.current().getId());
            stream.writeTextElement("titre",it.current().getTitre());
            stream.writeTextElement("dateCrea",it.current().getDateCrea());
            stream.writeTextElement("dateModif",it.current().getDateModif());
            Notes* n=it.current().clone();
            Tache& a1 = dynamic_cast<Tache&>(*n);
            stream.writeTextElement("action",a1.getAction());
            stream.writeTextElement("priorite",a1.getPriorite());
            stream.writeTextElement("dateEch",a1.getDateEch());
            stream.writeTextElement("statut",a1.getStatut());
            stream.writeEndElement();
        }

    }
    stream.writeEndElement();
    stream.writeEndDocument();
    newfile.close();
}


void NotesManager::load(const QString& f) {
     filename=f;
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


NotesManager::Handler NotesManager::handler=NotesManager::Handler(); //un objet handler de type Handler initialisé avec le constructeur Handler

NotesManager& NotesManager::getInstance(){
    if(handler.instance==nullptr){
        handler.instance=new NotesManager;
        return *handler.instance;
    }
    else{
        throw NotesException("Erreur, on a deja un note manager");
        return *handler.instance;
    }
}

void NotesManager::libererInstance(){
    delete handler.instance;
    handler.instance=nullptr;
}

NotesManager& NotesManager::recupererInstance(){
    if(handler.instance==nullptr) throw NotesException("Erreur, aucun note manager existant\n");
    else return *handler.instance;
}

void NotesManager::supprimerNote(QString id) {
   for (unsigned int i=0;i<notes.size();i++)
   {
      if (notes[i]->getId()==id) {
          qDebug()<<"on supprime l'id "<<notes[i]->getId()<<"\n";
          notes.erase(notes.begin()+i);
      }

   }
      qDebug("supprime une note");
}

void NotesManager::supprimerNotedefinitivement(Notes* n) {
    delete n;
}

