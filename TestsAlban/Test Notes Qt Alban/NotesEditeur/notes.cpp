#include "notes.h"
#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
using namespace std;

//--------------------NOTES------------------------//
Notes::Notes(const QString& i, const QString& ti):id(i),titre(ti),ancienneVersion(NULL){



    time_t seconds = time(NULL);
    struct tm * timeinfo = localtime(&seconds);
    dateCrea=Date((timeinfo->tm_mday),(timeinfo->tm_mon+1),(1900+timeinfo->tm_year));
    dateModif=Date((timeinfo->tm_mday),(timeinfo->tm_mon+1),(1900+timeinfo->tm_year));
}	//ajouter automatiquement la date créa et date modif


void Notes::setTitre(const QString& t){

    titre=t;
}

void Notes::setDateModif(const Date& d){

    dateCrea=d;
}

void Notes::setDateCrea(const Date& d){

    dateModif=d;
}

void Notes::setAncienneVersion(Notes* n){
    ancienneVersion.push_back(n);
}

/*void Notes::afficher(ostream& f)const{

    f << "ID : "<<getId()<<"\nTitre : "<<getTitre();//<<", Date de creation : "<<getDateCrea()<<", Date de modification : "<<getDateModif();
    f<<"\nDate de creation : ";
    getDateCrea();
    f<<"\nDate de modification : ";
    getDateModif();
}*/



//--------------------NOTESMANAGER------------------------//

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
    for(unsigned int i=0; i<nbArticles; i++){
        if (tabArticles[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
    }
    tabArticles.push_back(a);
    nbArticles++;
}

Article& NotesManager::getNewArticle(const QString& id,const QString& ti,const QString& te){
    Article* n=new Article(id,ti,te);
    addNotes(n);
    return *n;
}


Article& NotesManager::getArticle(const QString& id){
    for(unsigned int i=0;i<nbArticles;i++){
        if(tabArticles[i]->getId()==id) return *tabArticles[i];
    }
    throw NotesException("Erreur, l'Article n'existe pas");
}


void NotesManager::addNoteAvecFichier(NoteAvecFichier* a){
    for(unsigned int i=0; i<nbNoteAvecFichier; i++){
        if (tabNoteAvecFichier[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
    }
    tabNoteAvecFichier.push_back(a);
    nbNoteAvecFichier++;
}

NoteAvecFichier& NotesManager::getNewNoteAvecFichier(const QString& id,const QString& ti,const QString& de,const QString& fi){
    NoteAvecFichier* n=new NoteAvecFichier(id,ti,de,fi);
    addNotes(n);
    return *n;
}

NoteAvecFichier& NotesManager::getNoteAvecFichier(const QString& id){
    for(unsigned int i=0;i<nbNoteAvecFichier;i++){
        if(tabNoteAvecFichier[i]->getId()==id) return *tabNoteAvecFichier[i];
    }
    throw NotesException("Erreur, la note n'existe pas");
}


void NotesManager::addTaches(Tache* a){
    for(unsigned int i=0; i<nbTaches; i++){
        if (tabTaches[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
    }
    tabTaches.push_back(a);
    nbTaches++;
}

Tache& NotesManager::getNewTache(const QString& id,const QString& ti,const QString& ac,const QString& pr,const Date& d,statutTache t){
    Tache* n=new Tache(id,ti,ac,pr,d,t);
    addNotes(n);
    return *n;
}

Tache& NotesManager::getTache(const QString& id){
    for(unsigned int i=0;i<nbTaches;i++){
        if(tabTaches[i]->getId()==id) return *tabTaches[i];
    }
    throw NotesException("Erreur, la tache n'existe pas");
}



NotesManager::NotesManager():nbArticles(0),nbMaxArticles(0),filename(""),nbNoteAvecFichier(0),nbMaxNoteAvecFichier(0){}

NotesManager::~NotesManager(){
    //save();
    for(auto element : tabArticles) delete element;
    // on vide le tableau
    tabArticles.clear();
    for(auto element : tabNoteAvecFichier) delete element;
    tabNoteAvecFichier.clear();
    for(auto element : tabTaches) delete element;
    tabTaches.clear();
}

/*void NotesManager::save()const{
    ofstream fout(filename);
    for(unsigned int i=0; i<nbNotes; i++){
        fout<<*tabNotes[i];
    }
    fout.close();
}*/

/*void NotesManager::load(const QString& f) {
    //if (filename!=f) save();
    filename=f;
    ifstream fin(filename); // open file
    if (!fin) throw NotesException("Erreur, le fichier n'existe pas");
    while(!fin.eof()&&fin.good()){
        char tmp[1000];
        fin.getline(tmp,1000); // get id on the first line
        if (fin.bad()) throw NotesException("Erreur de lecture de l'id");
        QString id=tmp;
        fin.getline(tmp,1000); // get title on the next line
        if (fin.bad()) throw NotesException("Erreur de lecture du titre");
        QString titre=tmp;

        //fin.getline(tmp,1000); // get text on the next line
        //if (fin.bad()) throw NotesException("error reading note text on file");
        //Date dateCrea=tmp;
        //fin.getline(tmp,1000); // get text on the next line
       // if (fin.bad()) throw NotesException("error reading note text on file");
       // Date dateModif=tmp;
        //		Notes* n=new Notes(id,titre);
        //addNote(n);
        if (fin.peek()=='\r') fin.ignore();
        if (fin.peek()=='\n') fin.ignore();
    }
    fin.close(); // close file
}*/

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

Notes& NotesManager::edition(Notes* n){
    unsigned int i=0;
    while(notes[i]->getId()!=n->getId()){
        i++;
    }
    notes[i]=n->editer();
    time_t seconds = time(NULL);
    struct tm * timeinfo = localtime(&seconds);
    notes[i]->setDateModif(Date((timeinfo->tm_mday),(timeinfo->tm_mon+1),(1900+timeinfo->tm_year)));
    notes[i]->setTitre("Grosse BITE");
    notes[i]->ancienneVersion.push_back(n);
    return *notes[i];
}

//--------------------ARTICLE------------------------//
Article::Article(const QString& i, const QString& ti, const QString& t):Notes(i,ti),text(t){}
void Article::setText(const QString& t){

    text=t;
}

/*void Article::afficher(ostream& f) const{

    Notes::afficher(f);
    f<<"\nTexte : "<<getText()<<endl<<endl<<endl;
}*/


Article* Article::editer(){
    return this->clone();
}

//--------------------NOTEAVECFICHIER------------------------//
NoteAvecFichier::NoteAvecFichier(const QString& i,const QString& ti,const QString& d,const QString& f):Notes(i,ti),description(d),file(f){}

void NoteAvecFichier::setDescription(const QString& t){

    description=t;
}

void NoteAvecFichier::setFile(const QString& t){

    file=t;
}

/*void NoteAvecFichier::afficher(ostream& f)const{

    Notes::afficher(f);
    f<<"\nDescription : "<<getDescription()<<"\nLien du fichier : "<<getFile()<<endl<<endl<<endl;
}*/


NoteAvecFichier* NoteAvecFichier::editer(){
    return this->clone();
}

//--------------------TACHE------------------------//
Tache::Tache(const QString& i, const QString& ti,const QString& a,const QString& pr,const Date& d, statutTache t):Notes(i,ti),action(a),priorite(pr),dateEch(d),statut(t){}

void Tache::setAction(const QString& a){

    action=a;
}

void Tache::setPriorite(const QString& pr){

    priorite=pr;
}

void Tache::setDateEch(const Date& d){

    dateEch=d;
}

void Tache::setStatutTache(statutTache t){

    statut=t;
}

/*void Tache::afficher(ostream& f)const{

    Notes::afficher(f);
    f<<"\nAction : "<<getAction()<<"\nPriorite : "<<getPriorite()<<"\nDate d'echeance : ";
    getDateEch();
    f<<"\nStatut de la tache : "<<getStatutTache()<<endl<<endl<<endl;
}*/

Tache* Tache::editer(){
    return this->clone();
}
