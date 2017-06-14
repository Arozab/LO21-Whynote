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
         *
         *  Constructeur de la classe NotesException
         *
         *  \param message : message
         */

        NotesException(const QString& message):info(message){}

        /*!

         *  \brief Affiche les exceptions
         *
         *  Methode qui permet d'afficher l'exception
         *
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
         *
         *  Methode qui permet d'affecter les valeurs d'un objet à un autre objet
         *
         *	\param n : reference constante vers une Note
         *
         * 	\return Une reference vers \e Notes qui renvoie la nouvelle note.
         */
        Notes& operator=(const Notes& n);
        friend class NotesManager;
        friend class VersionsManager;

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

        Notes& getOldVersion(unsigned int i)const{return *ancienneVersion[i];}
        virtual Notes* clone()const=0;
        //virtual void afficher(ostream& f=cout) const;
        virtual Notes* editer()=0;	//ajout de l'adresse de n dans le tableau ancienneVersion de n, et on clone n et on l'ouvre


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

        friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur
        friend class VersionsManager; //permission au VersionsManager d'utiliser le constructeur et destructeur

    public:
        Article* editer();
        QString getText() const {return text;}
        void afficher(ostream& f=cout) const;

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
        friend class VersionsManager; //permission au VersionsManager d'utiliser le constructeur et destructeur


    public:
        NoteAvecFichier* editer();

        QString getDescription() const {return description;}

        /*!
	     *  \brief Retourne le chemin vers le fichier relié à la noteAvecFichier
	     * 	\return QString
	     */
        QString getFile() const {return file;}

        void afficher(ostream& f=cout) const;
        //NoteAvecFichier* getType(){return this;}

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
        friend class VersionsManager; //permission au VersionsManager d'utiliser le constructeur et destructeur


    public:
        Tache* editer();

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

        void afficher(ostream& f=cout) const;
        //Tache* getType(){return this;}
        void setAction(const QString& a);
        void setPriorite(const QString& pr);
        void setDateEch(const Date& d);
        void setStatut(QString t);

};

#endif
