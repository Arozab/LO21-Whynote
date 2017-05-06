#include "Notes.h"
#include <fstream>

Article::Article(const string& i, const string& ti, const string& te):
	id(i),title(ti),text(te)
{}

void Article::setTitle(const string& t) {
	title=t;
}

void Article::setText(const string& t) {
	text=t;
}

void NotesManager::addArticle(Article* a){
	for(unsigned int i=0; i<nbArticles; i++){
		if (articles[i]->getId()==a->getId()) throw NotesException("error, creation of an already existent note");
	}
	if (nbArticles==nbMaxArticles){
		Article** newArticles= new Article*[nbMaxArticles+5];
		for(unsigned int i=0; i<nbArticles; i++) newArticles[i]=articles[i];
		Article** oldArticles=articles;
		articles=newArticles;
		nbMaxArticles+=5;
		if (oldArticles) delete[] oldArticles;
	}
	articles[nbArticles++]=a;
}

Article& NotesManager::getArticle(const string& id){
	for(unsigned int i=0; i<nbArticles; i++){
		if (articles[i]->getId()==id) return *articles[i];
	}
	throw NotesException("error, nonexistent note");

}

Article& NotesManager::getNewArticle(const string& id){
	Article* a=new Article(id,"","");
	addArticle(a);
	return *a;
}

NotesManager::NotesManager():articles(nullptr),nbArticles(0),nbMaxArticles(0),filename("tmp.dat"){}

NotesManager::~NotesManager(){
	save();
	for(unsigned int i=0; i<nbArticles; i++) delete articles[i];
	delete[] articles;
}


/*NotesManager::NotesManager(const NotesManager& m):
	articles(new Article*[m.nbMaxArticles]), nbArticles(m.nbArticles),
	nbMaxArticles(m.nbMaxArticles),filename(m.filename) {
	for(unsigned int i=0; i<nbArticles; i++){
		articles[i]=new Article(*m.articles[i]);
	}
}

NotesManager& NotesManager::operator=(const NotesManager& m){
	if (this==&m) return *this;
	Article ** newarticles=new Article * [m.nbArticles];
	for(unsigned int i=0; i<m.nbArticles; i++)
		// construction par recopie d’un nouvel article
		newarticles[i]=new Article(*m.articles[i]);
	Article ** old=articles;
	unsigned int nb=nbArticles;
	articles=newarticles;
	nbArticles=nbMaxArticles=m.nbArticles;
	filename=m.filename;
	// destruction des anciens articles
	for(unsigned int i=0; i<nb; i++) delete old[i];
	delete[] old;
	return *this;
}
*/


void NotesManager::save() const {
	ofstream fout(filename);
	for(unsigned int i=0; i<nbArticles; i++){
		fout<<*articles[i];
	}
	fout.close();
}

ostream& operator<<(ostream& f, const Article& a){
	f<<a.getId()<<"\n";
	f<<a.getTitle()<<"\n";
	f<<a.getText()<<"\n";
	return f;
}

void NotesManager::load(const string& f) {
	if (filename!=f) save();
	filename=f;
	ifstream fin(filename); // open file
	if (!fin) throw NotesException("error, file does not exist");
	while(!fin.eof()&&fin.good()){
		char tmp[1000];
		fin.getline(tmp,1000); // get id on the first line
		if (fin.bad()) throw NotesException("error reading note id on file");
		string id=tmp;
		fin.getline(tmp,1000); // get title on the next line
		if (fin.bad()) throw NotesException("error reading note title on file");
		string title=tmp;
		fin.getline(tmp,1000); // get text on the next line
		if (fin.bad()) throw NotesException("error reading note text on file");
		string text=tmp;
		Article* a=new Article(id,title,text);
		addArticle(a);
		if (fin.peek()=='\r') fin.ignore();
		if (fin.peek()=='\n') fin.ignore();
	}
	fin.close(); // close file
}

/* ************************************************* */
void TagsManager::addTag(Tag* t){
	if (nbTags==nbMaxTags){
		Tag** newTags= new Tag*[nbMaxTags+5];
		for(unsigned int i=0; i<nbTags; i++) newTags[i]=tags[i];
		Tag** oldTags=tags;
		tags=newTags;
		nbMaxTags+=5;
		delete[] oldTags;
	}
	tags[nbTags++]=t;
}


TagsManager::TagsManager():
	tags(0),nbTags(0),nbMaxTags(0)
	{}


TagsManager::~TagsManager(){
	for(unsigned int i=0; i<nbTags; i++) {
		delete tags[i];
	}
	delete[] tags;
}

void TagsManager::addTag(const string& n, const Article& a){
	Tag* t=new Tag(n,a);
	addTag(t);
}

void TagsManager::removeTag(const string& n, const Article& a){
	unsigned int i=0;

	while(i<nbTags && &tags[i]->getArticle()!=&a && tags[i]->getName()!=n) i++;
	if (i==nbTags) throw NotesException("erreur : tag inexistant");

	delete tags[i];
	tags[i]=tags[--nbTags];

}

ostream& operator<<(ostream& f, const Tag& t){
	f<<t.getArticle()<<"\n";
	f<<t.getName()<<"\n";
	return f;
}

//**********************************************	TD		*****************

/*static NotesManager& NotesManager::getInstance(){
	static NotesManager instance;	//creation d'un objet static
	//definition seulement lors du premier appel
	return instance;
}*/

/*NotesManager* NotesManager::instance=nullptr;
NotesManager& NotesManager::getInstance(){
	if(instance==nullptr) instance=new NotesManager;
	return *instance;
}
void NotesManager::libererInstance(){
	delete instance;
	instance=nullptr;
}*/

NotesManager::Handler NotesManager::handler=NotesManager::Handler(); //un objet handler de type Handler initialisé avec le constructeur Handler
NotesManager& NotesManager::getInstance(){
	if(handler.instance==nullptr) handler.instance=new NotesManager;
	return *handler.instance;
}
void NotesManager::libererInstance(){
	delete handler.instance;
	handler.instance=nullptr;
}

