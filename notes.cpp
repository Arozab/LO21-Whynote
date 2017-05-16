#include "notes.h"
#include <fstream>
using namespace std;

//--------------------NOTES------------------------//
Notes::Notes(const string& i, const string& ti):id(i),titre(ti){}	//ajouter automatiquement la date créa et date modif

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
}


//--------------------NOTESMANAGER------------------------//
void NotesManager::addArticles(Article* a){
	for(unsigned int i=0; i<nbArticles; i++){
		if (tabArticles[i]->getId()==a->getId()) throw NotesException("Erreur, creation d'une note deja existante");
	}
	if(nbArticles==nbMaxArticles){
		Article** newTabArticles=new Article*[nbMaxArticles+10];
		for(unsigned int i=0;i<nbArticles;i++) newTabArticles[i]=tabArticles[i];
		Article** oldArticles=tabArticles;
		tabArticles=newTabArticles;
		nbMaxArticles+=10;
		if(oldArticles) delete[] oldArticles;
	}
	tabArticles[nbArticles++]=a;
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
	if(nbNoteAvecFichier==nbMaxNoteAvecFichier){
		NoteAvecFichier** newTabNoteAvecFichier=new NoteAvecFichier*[nbMaxNoteAvecFichier+10];
		for(unsigned int i=0;i<nbNoteAvecFichier;i++) newTabNoteAvecFichier[i]=tabNoteAvecFichier[i];
		NoteAvecFichier** oldNoteAvecFichier=tabNoteAvecFichier;
		tabNoteAvecFichier=newTabNoteAvecFichier;
		nbMaxNoteAvecFichier+=10;
		if(oldNoteAvecFichier) delete[] oldNoteAvecFichier;
	}
	tabNoteAvecFichier[nbNoteAvecFichier++]=a;
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
	if(nbTaches==nbMaxTaches){
		Tache** newTabTaches=new Tache*[nbMaxTaches+10];
		for(unsigned int i=0;i<nbTaches;i++) newTabTaches[i]=tabTaches[i];
		Tache** oldTaches=tabTaches;
		tabTaches=newTabTaches;
		nbMaxTaches+=10;
		if(oldTaches) delete[] oldTaches;
	}
	tabTaches[nbTaches++]=a;
}

Tache& NotesManager::getNewTache(const string& id,const string& ti,const string& ac,const string& pr,statutTache t){
	Tache* n=new Tache(id,ti,ac,pr,t);
	addTaches(n);
	return *n;
}

Tache& NotesManager::getTache(const string& id){
	for(unsigned int i=0;i<nbTaches;i++){
		if(tabTaches[i]->getId()==id) return *tabTaches[i];
	}
	throw NotesException("Erreur, la tache n'existe pas");
}



NotesManager::NotesManager():tabArticles(nullptr),nbArticles(0),nbMaxArticles(0),filename(""),tabNoteAvecFichier(nullptr),nbNoteAvecFichier(0),nbMaxNoteAvecFichier(0){}

NotesManager::~NotesManager(){
	//save();
	for(unsigned int i=0; i<nbArticles; i++) delete tabArticles[i];
	delete[] tabArticles;
	for(unsigned int i=0; i<nbNoteAvecFichier; i++) delete tabNoteAvecFichier[i];
	delete[] tabNoteAvecFichier;
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
	f<<", Texte : "<<getText()<<endl;
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
	f<<", Description : "<<getDescription()<<", Lien du fichier : "<<getFile()<<endl;
}


//--------------------TACHE------------------------//
Tache::Tache(const string& i, const string& ti,const string& a,const string& pr, statutTache t):Notes(i,ti),action(a),priorite(pr),statut(t){}

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
	f<<", Action : "<<getAction()<<", Priorite : "<<getPriorite()<<", Statut de la tache : "<<getStatutTache();//<<", Date d echeance : "<<getDateEch()<<endl;
}
