#ifndef NOTES_h
#define NOTES_h

#include <QString>
#include <iostream>
#include <vector>
#include <typeinfo>
#include "timing.h"
using namespace std;
class Article;
class NoteAvecFichier;
class Tache;

typedef enum{en_attente=1,en_cours=2,terminee=3}statutTache;


class NotesException{

	private:
        QString info;

	public:
        NotesException(const QString& message):info(message){}
        QString getInfo()const{return info;}
};


class Notes {

	private:

		Notes& operator=(const Notes& n);
		//~Notes();
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	protected:
        const QString id;
        QString titre;
		Date dateCrea;
		Date dateModif;
        vector<Notes*> ancienneVersion;



		//Empecher la duplication

	public:

        Notes(const QString& i, const QString& ti);
        QString getId() const { return id; }
        QString getTitre() const { return titre; }
        QString getDateCrea() const { return dateCrea.afficher();}
        QString getDateModif() const { return dateModif.afficher();}
		Notes& getOldVersion(unsigned int i)const{return *ancienneVersion[i];}
		virtual Notes* clone()const=0;
        //virtual void afficher(ostream& f=cout) const;
		virtual Notes* editer()=0;	//ajout de l'adresse de n dans le tableau ancienneVersion de n, et on clone n et on l'ouvre

        virtual QString getType(){
            QString t=typeid(*this).name();
            return t;
            //QString string(text);
            //return typeid(*this).name();
        }

        void setTitre(const QString& t);		//Mis à part son identificateur qui ne pourra jamais être édité,
        void setDateModif(const Date& d); 	//tous les éléments d’une note sont modifiables.
        void setDateCrea(const Date& d);
        void setAncienneVersion(Notes* n);
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

        QString filename;	//pour le fichier contenant les notes


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

        QString getFilename()const{return filename;}
        void setFilename(QString f){filename=f;}

        Article& getNewArticle(const QString& id,const QString& ti,const QString& te);
        Article& getArticle(const QString& id);

        NoteAvecFichier& getNewNoteAvecFichier(const QString& id,const QString& ti,const QString& de,const QString& fi);
        NoteAvecFichier& getNoteAvecFichier(const QString& id);

        Tache& getNewTache(const QString& id,const QString& ti,const QString& ac,const QString& pr,const QString& t);
        Tache& getTache(const QString& id);

        void load(const QString& f);
		void save()const;	//on ajoute la note modifiée dans le tableau notes de notesManager (si elle existe deja, remplacer l'ancienne version)
		static NotesManager& getInstance();
        static void libererInstance();
        static NotesManager& recupererInstance();

		unsigned int getnbNotes() const {return nbNotes;}
        Notes& edition(Notes* n);

        Notes* getNotes(unsigned int i)const{return notes[i];}
        //Notes& getNotes(const QString& id);

        class Iterator{
		private:
            vector<Notes*> tab;
			unsigned int nb;
			unsigned int courant;
            Iterator(vector<Notes*> t,unsigned int n):tab(t),nb(n),courant(0){}
			friend class NotesManager;

		public:
            //Iterator():tab(nullptr),nb(0),courant(0) {}
			Notes& current()const{return *tab[courant];}
			void next(){
				if(courant<nb) courant++;
				else throw NotesException("Iterator is done\n");
			}
			bool isDone(){return courant<0 || courant>=nb;}
			void previous(){courant--;}

		};
        Iterator getIterator(){
            return Iterator(notes,nbNotes);
        }

//		Iterator first(){return Iterator(tabNotes,nbNotes,0);}
//        Iterator last(){return Iterator(tabNotes,nbNotes,nbNotes-1);}
};


class Article: public Notes {

	private:

        QString text;
        Article(const QString& i, const QString& ti, const QString& t);
        Article* clone()const{return new Article(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:
        Article* editer();
        QString getText() const {return text;}
		void afficher(ostream& f=cout) const;
        void setText(const QString& t);
        //QString getType(){return typeid(*this).name();}
};


class NoteAvecFichier: public Notes {

	private:

        QString description;
        QString file;
        NoteAvecFichier(const QString& i, const QString& ti, const QString& des, const QString& fi);
	 	NoteAvecFichier* clone()const{return new NoteAvecFichier(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:
		NoteAvecFichier* editer();
        QString getDescription() const {return description;}
        QString getFile() const {return file;}
		void afficher(ostream& f=cout) const;
		//NoteAvecFichier* getType(){return this;}
        void setDescription(const QString& t);
        void setFile(const QString& t);
};


class Tache: public Notes {

	private:
      
        QString action;
        QString priorite;
		Date dateEch;
		QString statut;
        Tache(const QString& i, const QString& ti,const QString& a,const QString& pr, const QString& t);
		Tache* clone()const{return new Tache(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:
		Tache* editer();
        QString getAction() const {return action;}
        QString getPriorite() const {return priorite;}
        QString getDateEch() const {return dateEch.afficher();}
        QString getStatut() const {return statut;}
		void afficher(ostream& f=cout) const;
		//Tache* getType(){return this;}
		void setAction(const QString& a);
        void setPriorite(const QString& pr);
		void setDateEch(const Date& d);
		void setStatut(QString t);
};

#endif
