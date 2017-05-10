#include "notes.h"
#include <fstream>
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


//--------------------NOTESMANAGER------------------------//
void NotesManager::addNote(Notes* n){
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
	tabNotes[nbNotes++]=a;
}

Notes& NotesManager::getNote(const string& id){
	for(unsigned int i=0;i<nbNotes;i++){
		if(tabNotes[i]->getId()==id) return *tabNotes[i];
	}
	throw NotesException("Erreur, la note n'existe pas");
}

Notes& NotesManager::getNewNote(const Notes& id){
	Notes* n=new Notes(id,"");
	addNote(n);
	return *n;
}

NotesManager::NotesManager():tabNotes(nullptr),nbNotes(0),nbMaxNotes(0),filename(""){}

NotesManager::~NotesManager(){
	save();
	for(unsigned int i=0; i<nbNotes; i++) delete tabNotes[i];
	delete[] tabNotes;
}

void NotesManager::save()const{
	ofstream fout(filename);
	for(unsigned int i=0; i<nbNotes; i++){
		fout<<*tabNotes[i];
	}
	fout.close();
}

void NotesManager::load(const string& f) {
	if (filename!=f) save();
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
		addNote(n);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}

NotesManager::Handler NotesManager::handler=NotesManager::Handler(); //un objet handler de type Handler initialisé avec le constructeur Handler

NotesManager& NotesManager::getInstance(){
	if(handler.instance==nullptr) handler.instance=new NotesManager;
	return *handler.instance;
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


//--------------------NOTEAVECFICHIER------------------------//
NoteAvecFichier::NoteAvecFichier(const string& i,const string& ti,const string& d,const string& f):Notes(i,ti),description(d),file(f){}

void NoteAvecFichier::setDescription(const string& t){

	description=t;
}

void NoteAvecFichier::setFile(const string& t){

	file=t;
}


//--------------------TACHE------------------------//
Tache::Tache(const string& i, const string& ti,const string& a,const string& pr, Date d, statutTache t):Notes(i,ti),action(a),priorite(pr),dateEch(d),statut(t){}

void Tache::setAction(const string& a){

	action=a;
}

void Tache::setPriorite(const string& pr){

	priorite=p;
}

void Tache::setDateEch(const Date& d){

	dateEch=t;
}

void Tache::setStatut(statutTache t){

	statut=t;
}
