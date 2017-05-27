#include "notes.h"
#include <fstream>
using namespace std;

//--------------------NOTES------------------------//
Notes::Notes(const string& i, const string& ti):id(i),titre(ti){



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

	f << "ID : "<<getId()<<", Titre : "<<getTitre();//<<", Date de creation : "<<getDateCrea()<<", Date de modification : "<<getDateModif();
    f<<" Date de creation : ";
    getDateCrea();
    f<<" Date de modification : ";
    getDateModif();
}


//--------------------NOTESMANAGER------------------------//
void NotesManager::addArticles(Article* a){
	for(unsigned int i=0; i<nbArticles; i++){
		if (tabArticles[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
	}
	tabArticles.push_back(a);
	nbArticles++;
}

Article& NotesManager::getNewArticle(const string& id,const string& ti,const string& te){
	Article* n=new Article(id,ti,te);
	addArticles(n);
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
	addNoteAvecFichier(n);
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
	addTaches(n);
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

		Notes* n=new Notes(id,titre);
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


//--------------------ARTICLE------------------------//
Article::Article(const string& i, const string& ti, const string& t):Notes(i,ti),text(t){}

void Article::setText(const string& t){

	text=t;
}

void Article::afficher(ostream& f) const{

	Notes::afficher(f);
	f<<", Texte : "<<getText()<<endl<<endl;
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
	f<<", Description : "<<getDescription()<<", Lien du fichier : "<<getFile()<<endl<<endl;
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
	f<<", Action : "<<getAction()<<", Priorite : "<<getPriorite()<<", Statut de la tache : "<<getStatutTache()<<endl<<endl;//<<", Date d echeance : "<<getDateEch()<<endl;
}
