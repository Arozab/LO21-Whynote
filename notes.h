#ifndef NOTES_h
#define NOTES_h

#include <string>
#include <iostream>
#include <timing.h>
using namespace std;

enum statutTache{
	"en attente",
	"en cours",
	"terminee"
};

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
		Notes(const string& i, const string& ti);
		~Notes();
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	protected:
		const string id;
		string titre;
		Date dateCrea;
		Date dateModif;
		//Empecher la duplication
		
	public:
		string getId() const { return id; }
		string getTitre() const { return titre; }
		string getDateCrea() const { return dateCrea;}
		string getDateModif() const { return dateModif;}	
};


class NotesManager{

	private: 
		Notes** tabNotes;
		unsigned int nbNotes;
		unsigned int nbMaxNotes;
		void addNote(Notes* n);
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
		Notes& getNewNote(const string& n);
		Notes& getNote(const string& n);
		void load(const string& f);
		void save()const;
		static NotesManager& getInstance();
		static void libererInstance();

		class Iterator{
		private:
			Notes** tab;
			unsigned int nb;
			unsigned int courant;
			Iterator(Notes** n,unsigned int n):tab(t),nb(n),courant(0){}
			friend class NotesManager;

		public:
			Notes& current()const{return *tab[courant];}
			void next(){
				if(courant<nb) courant++;
				else throw NotesException("Iterator is done\n");
			}
			bool isDone(){return nb==courant;}
			
		};
		Iterator getIterator(){return Iterator(tab,nbNotes);}	
};


class Article: protected Notes {

	private:
		void setText(const string& t);
		string text;
		Article(const string& i, const string& ti, const string& t);

	public:
		string getText() const {return text;}
};


class NoteAvecFichier: protected Notes {

	private:
		void setDescription(const string& t);
		void setFile(const string& t);
		string description;
		string file;
		NoteAvecFichier(const string& i, const string& ti, const string& des, const string& fi);

	public:
		string getDescription() const {return description;}
		string getFile() const {return file;}
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
		Tache(const string& i, const string& ti,const string& a,const string& pr, Date d, statutTache t);

	public:
		string getAction() const {return action;}
		string getPriorite() const {return priorite;}
		string getDateEch() const {return dateEch;}
		string getStatutTache() const {return statutTache;}
};	
	

class couple{

	private:
		string label;
		Notes& note1;
		Notes& note2;
		void setLabel(const string& l);
		couple();
		couple(const string& l,Notes& n1,Notes& n2):label(l),note1(n1),Note2(n2){}
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
