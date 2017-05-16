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
/*void NotesManager::addNote(Notes* n){
	for(unsigned int i=0; i<nbNotes; i++){
		if (tabNotes[i]->getId()==n->getId()) throw NotesException("Erreur, creation d'une note deja existante");
	}
	if(nbNotes==nbMaxNotes){
		Notes** newTabNotes=new Notes*[nbMaxNotes+10];
		for(unsigned int i=0;i<nbNotes;i++) newTabNotes[i]=tabNotes[i];
		Notes** oldNotes=tabNotes;
		tabNotes=newTabNotes;
		nbMaxNotes+=10;
		if(oldNotes) delete[] oldNotes;
	}
	tabNotes[nbNotes++]=n;
}*/

/*Notes& NotesManager::getNote(const string& id){
	for(unsigned int i=0;i<nbNotes;i++){
		if(tabNotes[i]->getId()==id) return *tabNotes[i];
	}
	throw NotesException("Erreur, la note n'existe pas");
}*/

/*Notes& NotesManager::getNewNote(const string& id){
	Notes* n=new Article(id,"","");
	addNote(n);
	return *n;
}*/


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



NotesManager::NotesManager():tabArticles(nullptr),nbArticles(0),nbMaxArticles(0),filename(""){}

NotesManager::~NotesManager(){
	//save();
	for(unsigned int i=0; i<nbArticles; i++) delete tabArticles[i];
	delete[] tabArticles;
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
Tache::Tache(const string& i, const string& ti,const string& a,const string& pr, Date d, statutTache t):Notes(i,ti),action(a),priorite(pr),dateEch(d),statut(t){}

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
