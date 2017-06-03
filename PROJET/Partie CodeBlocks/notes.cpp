#include "notes.h"
#include <fstream>
using namespace std;

//--------------------NOTES------------------------//
Notes::Notes(const string& i, const string& ti):id(i),titre(ti),ancienneVersion(NULL){



	time_t seconds = time(NULL);
    struct tm * timeinfo = localtime(&seconds);
   	dateCrea=Date((timeinfo->tm_mday),(timeinfo->tm_mon+1),(1900+timeinfo->tm_year));
   	dateModif=Date((timeinfo->tm_mday),(timeinfo->tm_mon+1),(1900+timeinfo->tm_year));
}	//ajouter automatiquement la date créa et date modif

void Notes::setTitre(const string& t){

	titre=t;
}

void Notes::setDateModif(const Date& d){

	dateCrea=d;
}

void Notes::setDateCrea(const Date& d){

	dateModif=d;
}

void Notes::afficher(ostream& f)const{

	f << "ID : "<<getId()<<"\nTitre : "<<getTitre();//<<", Date de creation : "<<getDateCrea()<<", Date de modification : "<<getDateModif();
    f<<"\nDate de creation : ";
    getDateCrea();
    f<<"\nDate de modification : ";
    getDateModif();
}



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

/*Notes& NotesManager::getNotes(const string& id){
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

Article& NotesManager::getNewArticle(const string& id,const string& ti,const string& te){
	Article* n=new Article(id,ti,te);
	addNotes(n);
	return *n;
}

Article& NotesManager::getArticle(const string& id){
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

NoteAvecFichier& NotesManager::getNewNoteAvecFichier(const string& id,const string& ti,const string& de,const string& fi){
	NoteAvecFichier* n=new NoteAvecFichier(id,ti,de,fi);
	addNotes(n);
	return *n;
}

NoteAvecFichier& NotesManager::getNoteAvecFichier(const string& id){
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

Tache& NotesManager::getNewTache(const string& id,const string& ti,const string& ac,const string& pr,const Date& d,statutTache t){
	Tache* n=new Tache(id,ti,ac,pr,d,t);
	addNotes(n);
	return *n;
}

Tache& NotesManager::getTache(const string& id){
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

void NotesManager::load(const string& f) {
	//if (filename!=f) save();
	filename=f;
	ifstream fin(filename); // open file
	if (!fin) throw NotesException("Erreur, le fichier n'existe pas");
	while(!fin.eof()&&fin.good()){
		char tmp[1000];
		fin.getline(tmp,1000); // get id on the first line
		if (fin.bad()) throw NotesException("Erreur de lecture de l'id");
		string id=tmp;
		fin.getline(tmp,1000); // get title on the next line
		if (fin.bad()) throw NotesException("Erreur de lecture du titre");
		string titre=tmp;

		/*fin.getline(tmp,1000); // get text on the next line
		if (fin.bad()) throw NotesException("error reading note text on file");
		Date dateCrea=tmp;
		fin.getline(tmp,1000); // get text on the next line
		if (fin.bad()) throw NotesException("error reading note text on file");
		Date dateModif=tmp;*/
		//		Notes* n=new Notes(id,titre);
		//addNote(n);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
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
Article::Article(const string& i, const string& ti, const string& t):Notes(i,ti),text(t){}

void Article::setText(const string& t){

	text=t;
}

void Article::afficher(ostream& f) const{

	Notes::afficher(f);
	f<<"\nTexte : "<<getText()<<endl<<endl<<endl;
}


Article* Article::editer(){
	return this->clone();
}

//--------------------NOTEAVECFICHIER------------------------//
NoteAvecFichier::NoteAvecFichier(const string& i,const string& ti,const string& d,const string& f):Notes(i,ti),description(d),file(f){}

void NoteAvecFichier::setDescription(const string& t){

	description=t;
}

void NoteAvecFichier::setFile(const string& t){

	file=t;
}

void NoteAvecFichier::afficher(ostream& f)const{

	Notes::afficher(f);
	f<<"\nDescription : "<<getDescription()<<"\nLien du fichier : "<<getFile()<<endl<<endl<<endl;
}


NoteAvecFichier* NoteAvecFichier::editer(){
	return this->clone();
}

//--------------------TACHE------------------------//
Tache::Tache(const string& i, const string& ti,const string& a,const string& pr,const Date& d, statutTache t):Notes(i,ti),action(a),priorite(pr),dateEch(d),statut(t){}

void Tache::setAction(const string& a){

	action=a;
}

void Tache::setPriorite(const string& pr){

	priorite=pr;
}

void Tache::setDateEch(const Date& d){

	dateEch=d;
}

void Tache::setStatutTache(statutTache t){

	statut=t;
}

void Tache::afficher(ostream& f)const{

	Notes::afficher(f);
	f<<"\nAction : "<<getAction()<<"\nPriorite : "<<getPriorite()<<"\nDate d'echeance : ";
    getDateEch();
    f<<"\nStatut de la tache : "<<getStatutTache()<<endl<<endl<<endl;
}

Tache* Tache::editer(){
	return this->clone();
}
