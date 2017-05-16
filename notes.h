#ifndef NOTES_h
#define NOTES_h

#include <string>
#include <iostream>
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
		Notes(const Notes& n);
		Notes& operator=(const Notes& n);
		//~Notes();		
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	protected:
		const string id;
		string titre;
		Date dateCrea;
		Date dateModif;
		//Empecher la duplication

	public:

		Notes(const string& i, const string& ti);
		string getId() const { return id; }
		string getTitre() const { return titre; }
		void getDateCrea() const { return dateCrea.afficher();}
		void getDateModif() const { return dateModif.afficher();}
		virtual void afficher(ostream& f=cout) const;
};


class NotesManager{

	private:
		Article** tabArticles;
		unsigned int nbArticles;
		unsigned int nbMaxArticles;
		void addArticles(Article* a);

		NoteAvecFichier** tabNoteAvecFichier;
		unsigned int nbNoteAvecFichier;
		unsigned int nbMaxNoteAvecFichier;
		void addNoteAvecFichier(NoteAvecFichier* a);

		Tache** tabTaches;
		unsigned int nbTaches;
		unsigned int nbMaxTaches;
		void addTaches(Tache* a);

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

		Tache& getNewTache(const string& id,const string& ti,const string& ac,const string& pr,statutTache t);
		Tache& getTache(const string& id);

		void load(const string& f);
		void save()const;
		static NotesManager& getInstance();
		static void libererInstance();

		/*class Iterator{
		private:
			Notes** tab;
			unsigned int nb;
			unsigned int courant;
			Iterator(Notes** t,unsigned int n):tab(t),nb(n),courant(0){}
			friend class NotesManager;

		public:
			Notes& current()const{return *tab[courant];}
			void next(){
				if(courant<nb) courant++;
				else throw NotesException("Iterator is done\n");
			}
			bool isDone(){return nb==courant;}

		};
		Iterator getIterator(){return Iterator(tabNotes,nbNotes);}*/
};


class Article: protected Notes {

	private:
		void setText(const string& t);
		string text;
		Article(const string& i, const string& ti, const string& t);
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
		Tache(const string& i, const string& ti,const string& a,const string& pr, statutTache t);
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:
		string getAction() const {return action;}
		string getPriorite() const {return priorite;}
		void getDateEch() const {return dateEch.afficher();}
		statutTache getStatutTache() const {return statut;}
		void afficher(ostream& f=cout) const;
};


class couple{

	private:
		string label;
		Notes& note1;
		Notes& note2;
		void setLabel(const string& l);
		couple();
		couple(const string& l,Notes& n1,Notes& n2):label(l),note1(n1),note2(n2){}
		~couple();

	public:
		string getLabel()const{return label;}
};


class relation{

	private:
		string titre;
		string description;
		couple* ensemble_couple;

	public:
		string getTitre()const{return titre;}
		string getDescription()const{return description;}
		relation();
		~relation();
};



#endif
