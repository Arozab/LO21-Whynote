#ifndef COUPLEMANAGER_H_INCLUDED
#define COUPLEMANAGER_H_INCLUDED

#include <QString>
#include <iostream>
#include <vector>
#include "relation.h"
using namespace std;

/*! \class CoupleManager
   * \brief Classe gérant toutes les opérations liées aux couples
*/
class CoupleManager
{
private:
	unsigned int nbCouple;
    void addCouple(couple* c);
    vector<couple*> couples;
    QString filename;
    friend class QMainWindow;

    CoupleManager();
    CoupleManager(const CoupleManager& m);
    CoupleManager& operator=(const CoupleManager& m);

	struct Handler
    {
        CoupleManager* instance;
        Handler():instance(nullptr){}
        ~Handler(){
            delete instance;
            instance=nullptr;
        }
    };
    static Handler handler;	//le destructeur sera appelé automatiquement à la fin du programme pour cet objet


public:
    /*!
     *  \brief Destructeur de la classe
    */
	~CoupleManager();

    /*!
     *  \brief Créé une unique instance du couple manager
     *  \return Une reference vers couple manager
     */
	static CoupleManager& getInstance();

    /*!
     *  \brief Libère l'unique instance de couple manager
     *  \return void
    */
    static void libererInstance();

    /*!
     *  \brief Renvoie l'instance en cours sur le couple manager
     *  \return Une reference vers couple manager
     */
    static CoupleManager& recupererInstance();

    /*!
     *  \brief Renvoie le nombre de couple du tableau de couples
     *  \return unsigned int
    */
    unsigned int getnbCouple() const {return nbCouple;}

    /*!
     *  \brief Créé un nouveau couple
     *  \param l : const QString& (label)
     *  \param nb1 : int (id de la note1)
     *  \param nb2 : int (id de la note2)
     *  \return Une référence vers le couple créé
     */
    couple& getNewCouple(const QString& l, int nb1,int nb2);

    /*!
     *  \brief Charge le fichier contenant les couples
     *  \param f : référence const vers un QString qui contient le chemin vers le fichier en question
     *  \return void
     */
    void load(const QString& f);

    /*! \class Iterator
       * \brief Classe qui permet de parcourir séquentiellement les éléments du tableau de couple
    */
    class Iterator{
    private:
        vector<couple*> tab;
        unsigned int nb;
        unsigned int courant;
        Iterator(vector<couple*> t,unsigned int n):tab(t),nb(n),courant(0){}
        friend class CoupleManager;

    public:
        /*!
         *  \brief Renvoie une référence vers le couple courant
         *  \return Référence vers le couple actuel
        */
        couple& current()const{return *tab[courant];}

        /*!
         *  \brief Passe au couple suivant
         *  \return void
        */
        void next(){
            if(courant<nb) courant++;
            else throw NotesException("Iterator is done\n");
        }

        /*!
         *  \brief Renvoie un booléen pour savoir si on a parcouru tous les couples ou non
         *  \return void
        */
        bool isDone(){return courant<0 || courant>=nb;}

        /*!
         *  \brief Passe au couple précédent
         *  \return void
        */
        void previous(){courant--;}

    };

    /*!
         *  \brief Créé un itérator
         *  \return Iterator créé
        */
    Iterator getIterator(){
        return Iterator(couples,nbCouple);
    }
};


#endif // COUPLEMANAGER_H_INCLUDED
