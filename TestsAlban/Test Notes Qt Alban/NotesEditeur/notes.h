#ifndef NOTES_h
#define NOTES_h

#include <QString>
#include <iostream>
#include <vector>
#include <typeinfo>
#include "timing.h"
using namespace std;

typedef enum{en_attente=1,en_cours=2,terminee=3}statutTache;

/*! \class NotesException
   * \brief Classe gérant les erreurs liées aux notes
*/
class NotesException{

	private:
        QString info;	/*!< Chaine de caractères contenant l'erreur*/

	public:
		/*!
	     *  \brief Constructeur
	     *  \param message : message
	     */
        NotesException(const QString& message):info(message){}
        /*!
	     *  \brief Affiche les exceptions
	     * 	\return Un \e QString représentant l'erreur obtenue.
	     */
        QString getInfo()const{return info;}
};


/*! \class Notes
   * \brief Classe mère abstraite contenant les attributs et méthodes de base d'une note
*/
class Notes {

	private:
		/*!<
	     *  \brief Opérateur d'affectation
	     *	\param n : reference constante vers une Note
	     * 	\return Une reference vers \e Notes qui renvoie la nouvelle note.
	     */
		Notes& operator=(const Notes& n);
		friend class NotesManager; 

	protected:
        const QString id;	/*!< Chaine de caractères représentant la note de façon unique*/
        QString titre;		/*!< Chaine de caractères indiquant le titre de la note*/
		Date dateCrea;		/*!< Date la création de la note*/
		Date dateModif;		/*!< Date la dernière modification de la note*/
        vector<Notes*> ancienneVersion;	/*!< Vecteur de pointeur sur note qui stocke les anciennes versions de la note*/

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
