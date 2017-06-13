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
	     *  \param message : const QString&
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
		/*!
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
		/*!
	     *  \brief Constructeur
	     *  \param i : const QString&
	     *  \param ti : const QString&
	     */
        Notes(const QString& i, const QString& ti);

       	/*!
	     *  \brief Retourne l'ID de la note
	     * 	\return QString
	     */
        QString getId() const { return id; }

        /*!
	     *  \brief Retourne le titre de la note
	     * 	\return QString
	     */
        QString getTitre() const { return titre; }

        /*!
	     *  \brief Retourne la date de création de la note
	     * 	\return QString
	     */
        QString getDateCrea() const { return dateCrea.afficher();}

        /*!
	     *  \brief Retourne la date de derniere modification de la note
	     * 	\return QString
	     */
        QString getDateModif() const { return dateModif.afficher();}

        /*!
	     *  \brief Retourne l'ancienne version d'indice i de la note
	     *  \param i : unsigned int	     
	     * 	\return \e Notes&
	     */
		Notes& getOldVersion(unsigned int i)const{return *ancienneVersion[i];}

		/*!
	     *  \brief Retourne un pointeur vers une copie de la note    
	     * 	\return \e Notes*
	     */
		virtual Notes* clone()const=0;

		/*!
	     *  \brief Retourne le type de la note    
	     * 	\return QString
	     */
        virtual QString getType(){
            QString t=typeid(*this).name();
            return t;
        }

        /*!
	     *  \brief Permet de modifier le titre de la note
	     *  \param t : const QString&     
	     * 	\return void
	     */
        void setTitre(const QString& t);

        /*!
	     *  \brief Permet de modifier la date de modification de la note
	     *  \param d : const Date&     
	     * 	\return void
	     */
        void setDateModif(const Date& d);

        /*!
	     *  \brief Permet de modifier la date de création de la note
	     *  \param d : const Date&  
	     * 	\return void
	     */ 	
        void setDateCrea(const Date& d);

        /*!
	     *  \brief Permet de modifier le vector d'ancienne version de la note
	     *  \param n : Notes*   
	     * 	\return void
	     */
        void setAncienneVersion(Notes* n);
};

/*! \class Article
   * \brief Classe fille de Notes  contenant des attributs et méthodes supplémentaires
*/
class Article: public Notes {

	private:

        QString text;	/*!< Chaine de caractères représentant le texte de l'article*/
        Article(const QString& i, const QString& ti, const QString& t);
        Article* clone()const{return new Article(*this);}
		friend class NotesManager;

	public:
        /*!
	     *  \brief Retourne le texte de l'article
	     * 	\return QString
	     */
        QString getText() const {return text;}

		/*!
	     *  \brief Permet de modifier le texte d'un article
	     *  \param t : const QString&  
	     * 	\return void
	     */
        void setText(const QString& t);
};

/*! \class NoteAvecFichier
   * \brief Classe fille de Notes  contenant des attributs et méthodes supplémentaires
*/
class NoteAvecFichier: public Notes {

	private:

        QString description;	/*!< Chaine de caractères représentant la description de la noteAvecFichier*/
        QString file;			/*!< Chaine de caractères représentant le chemin vers le fichier relié à la noteAvecFichier*/
        NoteAvecFichier(const QString& i, const QString& ti, const QString& des, const QString& fi);
	 	NoteAvecFichier* clone()const{return new NoteAvecFichier(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:
		/*!
	     *  \brief Retourne la description d'une note avec fichier
	     * 	\return QString
	     */		
        QString getDescription() const {return description;}

        /*!
	     *  \brief Retourne le chemin vers le fichier relié à la noteAvecFichier
	     * 	\return QString
	     */
        QString getFile() const {return file;}

        /*!
	     *  \brief Permet de modifier la description d'une note avec fichier
	     *  \param t : const QString&  
	     * 	\return void
	     */
        void setDescription(const QString& t);

        /*!
	     *  \brief Permet de modifier le chemin vers le fichier relié à la noteAvecFichier
	     *  \param t : const QString&  
	     * 	\return void
	     */
        void setFile(const QString& t);
};

/*! \class Tache
   * \brief Classe fille de Notes contenant des attributs et méthodes supplémentaires
*/
class Tache: public Notes {

	private:
      
        QString action;		/*!< Chaine de caractères représentant l'action de la tache*/
        QString priorite;	/*!< Chaine de caractères représentant la priorité de la tache*/
		Date dateEch;		/*!< Chaine de caractères représentant la date d'échéance de la tache*/
		QString statut;		/*!< Chaine de caractères représentant le statut de la tache*/
        Tache(const QString& i, const QString& ti,const QString& a,const QString& pr, const QString& t);
		Tache* clone()const{return new Tache(*this);}
		friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

	public:
		/*!
	     *  \brief Retourne l'action de la Tache
	     * 	\return QString
	     */
        QString getAction() const {return action;}

        /*!
	     *  \brief Retourne la priorité de la Tache
	     * 	\return QString
	     */
        QString getPriorite() const {return priorite;}

        /*!
	     *  \brief Retourne la date d'échéance de la Tache
	     * 	\return QString
	     */
        QString getDateEch() const {return dateEch.afficher();}

        /*!
	     *  \brief Retourne le statut de la Tache
	     * 	\return QString
	     */
        QString getStatut() const {return statut;}

        /*!
	     *  \brief Permet de modifier l'action de la Tache
	     *  \param a : const QString&  
	     * 	\return void
	     */
		void setAction(const QString& a);

		/*!
	     *  \brief Permet de modifier la priorité de la Tache
	     *  \param pr : const QString&  
	     * 	\return void
	     */
        void setPriorite(const QString& pr);

        /*!
	     *  \brief Permet de modifier la date d'échéance de la Tache
	     *  \param d : const Date& d 
	     * 	\return void
	     */
		void setDateEch(const Date& d);

		/*!
	     *  \brief Permet de modifier le statut de la Tache
	     *  \param t : QString
	     * 	\return void
	     */
		void setStatut(QString t);
};

#endif
