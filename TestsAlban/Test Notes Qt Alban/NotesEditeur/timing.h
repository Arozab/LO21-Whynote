#if !defined(CTIME)
#define CTIME

#include <iostream>
#include <iomanip>
#include <ctime>
#include <QString>
#include <time.h>

/*! \class TimeException
   * \brief Classe gérant les erreurs liées aux Dates
*/
class TimeException{
public:
    /*!
     *  \brief Constructeur de la classe, on lui oasse une chaine de caractères contenant l'erreur en paramètre
     *	\param m : reference constante vers un QString
    */
    TimeException(const QString & m):info(m){}

    /*!
     *  \brief Retourne l'erreur
     * 	\return Une référence const QString
    */
    const QString& GetInfo() const { return info; }
private:
    QString info;
};


/*! \class Date
        \brief Classe permettant de manipuler des dates standards
        L'utilisation de cette classe nécessite des dates valides au sens commun du terme.
        Déclenchement d'exception dans le cas contraire
*/
class Date {
public:
    /*!
     *	\brief Constructeur à partir d'un jour, mois, année
     *	\param j jour avec 1<=j<=31
     *	\param m mois avec 1<=m<=12
     *	\param a année avec a>=0
    */
    Date(unsigned int short j=1, unsigned int short m=1, unsigned int a=0):jour(1),mois(1),annee(0){ setDate(j,m,a); }
    // méthodes
    unsigned short int  getJour() const { return jour; } //<! Retourne le jour de la date
    unsigned short int  getMois() const { return mois; } //<! Retourne le mois de la date
    unsigned int getAnnee() const { return annee; } //<! Retourne l'année de la date
    void setDate(unsigned short int j, unsigned short int m, unsigned int a); //!< initialisation de la date
    QString afficher() const; //!< affiche le date sous le format JJ/MM/AAAA
    bool operator==(const Date& d) const; //<! d1==d2 retourne vrai si les deux dates sont égales
    bool operator<(const Date& d) const; //<! Compare deux dates dans le temps : d1<d2 retourne true si d1 est avant d2
    int operator-(const Date& d) const; //<! Retourne le nombre de jours séparant les deux dates
    Date demain() const; //<! Retourne la date du lendemain
    Date operator+(unsigned int nb) const; //<!Retourne la date de dans nb jours
private:
    // attributs
    unsigned short int jour; // jour entre 1 et 31
    unsigned short int mois; // mois entre 1 et 12
    unsigned int annee;
};


#endif
