#ifndef COUPLEMANAGER_H_INCLUDED
#define COUPLEMANAGER_H_INCLUDED

#include <QString>
#include <iostream>
#include <vector>
#include "relation.h"
using namespace std;

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
	~CoupleManager();
	static CoupleManager& getInstance();
    static void libererInstance();
    static CoupleManager& recupererInstance();
    unsigned int getnbCouple() const {return nbCouple;}

    couple& getNewCouple(const QString& l, int nb1,int nb2);
    void load(const QString& f);


    class Iterator{
    private:
        vector<couple*> tab;
        unsigned int nb;
        unsigned int courant;
        Iterator(vector<couple*> t,unsigned int n):tab(t),nb(n),courant(0){}
        friend class CoupleManager;

    public:
        //Iterator():tab(nullptr),nb(0),courant(0) {}
        couple& current()const{return *tab[courant];}
        void next(){
            if(courant<nb) courant++;
            else throw NotesException("Iterator is done\n");
        }
        bool isDone(){return courant<0 || courant>=nb;}
        void previous(){courant--;}

    };
    Iterator getIterator(){
        return Iterator(couples,nbCouple);
    }
};


#endif // COUPLEMANAGER_H_INCLUDED
