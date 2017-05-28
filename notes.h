#ifndef NOTES_h
#define NOTES_h

#include <string>
#include <iostream>
#include <vector>
#include "timing.h"
using namespace std;
class Article;
class NoteAvecFichier;
class Tache;

typedef enum{en_attente=1,en_cours=2,terminee=3}statutTache;


class NotesException{

	private:
		string info;

	public:
		NotesException(const string& message):info(message){}
		string getInfo()const{return info;}
};


class Notes {

	private:
		void setTitre(const string& t);		//Mis à part son identificateur qui ne pourra jamais être édité,
		void setDateModif(const Date& d); 	//tous les éléments d’une note sont modifiables.
		void setDateCrea(const Date& d);
		Notes& operator=(const Notes& n);
		//~Notes();
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	protected:
		const string id;
		string titre;
		Date dateCrea;
		Date dateModif;
		vector<Notes*> ancienneVersion;
		//Empecher la duplication

	public:

		Notes(const string& i, const string& ti);
		string getId() const { return id; }
		string getTitre() const { return titre; }
		void getDateCrea() const { return dateCrea.afficher();}
		void getDateModif() const { return dateModif.afficher();}
		virtual Notes* clone()const=0;
		virtual void afficher(ostream& f=cout) const;
};


class NotesManager{

	private:
		vector<Article*> tabArticles;
		unsigned int nbArticles;
		unsigned int nbMaxArticles;
		void addArticles(Article* a);

		vector<NoteAvecFichier*> tabNoteAvecFichier;
		unsigned int nbNoteAvecFichier;
		unsigned int nbMaxNoteAvecFichier;
		void addNoteAvecFichier(NoteAvecFichier* a);

		vector<Tache*> tabTaches;
		unsigned int nbTaches;
		unsigned int nbMaxTaches;
		void addTaches(Tache* a);

		vector<Notes*> notes;
		void addNotes(Notes* n);
		unsigned int nbNotes;

		string filename;	//pour le fichier contenant les notes

		NotesManager();
		~NotesManager();
		NotesManager(const NotesManager& m);
		NotesManager& operator=(const NotesManager& m);

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

		Article& getNewArticle(const string& id,const string& ti,const string& te);
		Article& getArticle(const string& id);

		NoteAvecFichier& getNewNoteAvecFichier(const string& id,const string& ti,const string& de,const string& fi);
		NoteAvecFichier& getNoteAvecFichier(const string& id);

		Tache& getNewTache(const string& id,const string& ti,const string& ac,const string& pr,const Date& d,statutTache t);
		Tache& getTache(const string& id);

		void load(const string& f);
		void save()const;	//on ajoute la note modifiée dans le tableau notes de notesManager (si elle existe deja, remplacer l'ancienne version)
		static NotesManager& getInstance();
		static void libererInstance();

		void editer(const Notes& n);	//ajout de l'adresse de n dans le tableau ancienneVersion de n, et on clone n et on l'ouvre
		//Notes& getNotes(const string& id);

		/*class Iterator{
		private:
			Notes** tab;
			unsigned int nb;
			unsigned int courant;
			Iterator(Notes** t,unsigned int n,unsigned int c):tab(t),nb(n),courant(c){}
			friend class NotesManager;

		public:
			Notes& current()const{return *tab[courant];}
			void next(){
				if(courant<nb) courant++;
				else throw NotesException("Iterator is done\n");
			}
			bool isDone(){return courant<0 || courant>=nb;}
			void previous(){courant--;}

		};
		Iterator first(){return Iterator(tabNotes,nbNotes,0);}
		Iterator last(){return Iterator(tabNotes,nbNotes,nbNotes-1);}*/
};


class Article: protected Notes {

	private:
		void setText(const string& t);
		string text;
		Article(const string& i, const string& ti, const string& t);
		Article* clone()const{return new Article(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:

		string getText() const {return text;}
		void afficher(ostream& f=cout) const;
};


class NoteAvecFichier: protected Notes {

	private:
		void setDescription(const string& t);
		void setFile(const string& t);
		string description;
		string file;
	 	NoteAvecFichier(const string& i, const string& ti, const string& des, const string& fi);
	 	NoteAvecFichier* clone()const{return new NoteAvecFichier(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:

		string getDescription() const {return description;}
		string getFile() const {return file;}
		void afficher(ostream& f=cout) const;
};


class Tache: protected Notes {

	private:
		void setAction(const string& a);
		void setPriorite(const string& pr);
		void setDateEch(const Date& d);
		void setStatutTache(statutTache t);
		string action;
		string priorite;
		Date dateEch;
		statutTache statut;
		Tache(const string& i, const string& ti,const string& a,const string& pr,const Date&, statutTache t);
		Tache* clone()const{return new Tache(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:
		string getAction() const {return action;}
		string getPriorite() const {return priorite;}
		void getDateEch() const {return dateEch.afficher();}
		statutTache getStatutTache() const {return statut;}
		void afficher(ostream& f=cout) const;
};

#endif
