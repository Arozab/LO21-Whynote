#if !defined(_NOTES_H)
#define _NOTES_H

#include <string>
#include <iostream>
using namespace std;

class Article;
class Tag;
class NotesManager;
class TagsManager;

class NotesException{
public:
	NotesException(const string& message):info(message){}
	string getInfo() const { return info; }
private:
	string info;
};

class Article {
	string id;
	string title;
	string text;
	//Empecher la duplication
	Article(const Article& a);
	Article& operator=(const Article& a);
	//Empecher tout le monde à part le NotesManager de construire et de détruire les objets Article
	//on met les constructeurs et destructeurs ici
	//friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

public:
	Article(const string& i, const string& ti, const string& te);
	string getId() const { return id; }
	string getTitle() const { return title; }
	string getText() const { return text; }
	void setTitle(const string& t);
	void setText(const string& t);
};

class NotesManager {
private:
	Article** articles;
	unsigned int nbArticles;
	unsigned int nbMaxArticles;
	void addArticle(Article* a);
	string filename;

	NotesManager();
	~NotesManager();
	NotesManager(const NotesManager& m);
	//static NotesManager* instance; //pointeur sur l'unique instance

	struct Handler
	{
		NotesManager* instance;
		Handler():instance(nullptr){}
		~Handler(){
			delete instance;
			instance=nullptr;
		}
	};
	static Handler handler;	//le destructeur sera appelé automatiquement à la fin du programme pour cet objet

public:

	NotesManager& operator=(const NotesManager& m);
	Article& getNewArticle(const string& id);
	Article& getArticle(const string& id);
	void load(const string& f);
	void save() const;

	//static NotesManager& getInstance();
	static NotesManager& getInstance();
	static void libererInstance();

	class Iterator{
		Article** tab; //adresse du tableau de pointeurs articles
		unsigned int nb;//nombre d'articles
		unsigned int courant; //indice courant
		Iterator(Article** t,unsigned int n):tab(t),nb(n),courant(0){}
		friend class NotesManager;

	public:
		Iterator():tab(nullptr),nb(0),courant(0){}
		Article& current()const{return *tab[courant];}
		void next(){
			if(courant<nb) courant++;
			else throw NotesException("iterator is done");
		}
		bool isDone(){return nb==courant;}
	};
	Iterator getIterator(){
		return Iterator(articles,nbArticles);
	}

	class iterator{	//avec les symboles
		Article** tab; //adresse du tableau de pointeurs articles
		unsigned int nb;//nombre d'articles
		unsigned int courant; //indice courant
		iterator(Article** t,unsigned int n):tab(t),nb(n),courant(0){}
		friend class NotesManager;

	public:
		iterator():tab(nullptr),nb(0),courant(0){}
		Article& operator*()const{return *tab[courant];}
		void operator++(){
			if(courant<nb) courant++;
			else throw NotesException("iterator is done");
		}
		bool operator!=(const iterator it)const
		{return tab!=it.tab||courant != it.courant;}
	};
	iterator begin(){return iterator(articles,nbArticles);}
	iterator end(){return iterator(articles,nbArticles);}


class ConstIterator{	//pour les articles constants
		Article** tab; //adresse du tableau de pointeurs articles
		unsigned int nb;//nombre d'articles
		unsigned int courant; //indice courant
		ConstIterator(Article** t,unsigned int n):tab(t),nb(n),courant(0){}
		friend class NotesManager;

	public:
		ConstIterator():tab(nullptr),nb(0),courant(0){}
		const Article& current()const{return *tab[courant];}
		void next(){
			if(courant<nb) courant++;
			else throw NotesException("iterator is done");
		}
		bool isDone(){return nb==courant;}
	};
	ConstIterator getIterator()const{
		return ConstIterator(articles,nbArticles);
	}

class SearchIterator{
		Article** tab; //adresse du tableau de pointeurs articles
		unsigned int nb;//nombre d'articles
		unsigned int courant; //indice courant
		const string tofind;
		SearchIterator(const string& str, Article** t, unsigned int n):tofind(str),tab(t),nb(n),courant(0){
			//se deplacer sur le premier article qui contient tofind
			while(courant<nb && tab[courant]->getText().find(tofind)==string::npos)
				courant++;
		}
		friend class NotesManager;

	public:
		SearchIterator():tab(nullptr),nb(0),courant(0){}
		Article& current()const{return *tab[courant];}
		void next(){
			if(isDone()) throw NotesException("iterator is done");
            courant++;
			//se deplacer sur le prochain article qui contient tofind
		}
		bool isDone(){return nb==courant;}
	};
	SearchIterator getSearchIterator(const string& str){
		return SearchIterator(str,articles,nbArticles);
	}

};

class Tag {
	string name;
	const Article* article;
public:
	Tag(const string& n, const Article& a):name(n),article(&a){}
	const string& getName() const { return name; }
	const Article& getArticle() const { return *article; }
};

class TagsManager {
private:
	Tag** tags;
	unsigned int nbTags;
	unsigned int nbMaxTags;
	void addTag(Tag* a);
public:
	TagsManager();
	~TagsManager();
	void addTag(const string& t, const Article& a);
	void removeTag(const string& t, const Article& a);
};

ostream& operator<<(ostream& f, const Article& a);
ostream& operator<<(ostream& f, const Tag& t);
#endif
