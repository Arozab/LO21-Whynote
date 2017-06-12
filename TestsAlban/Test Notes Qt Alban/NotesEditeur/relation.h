#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED

#include <QString>
#include <iostream>
#include <vector>
#include "notes.h"
//#include "couplemanager.h"
using namespace std;

class couple{

	private:
		QString label;
		int note1;
		int note2;
		void setLabel(const QString& l);
		couple(const QString& l,int n1,int n2):label(l),note1(n1),note2(n2){}
       
		friend class CoupleManager;

	public:
		//~couple();
		QString getLabel() const { return label;}
        int getNotes1() { return note1;}
        int getNotes2() { return note2;}
};


/*class relation{

	private:
		QString titre;
		QString description;
		vector<couple*> ensemble_couple;
		int orientation; // 0 pour non orientée, 1 pour orienter dans le sens de note1 vers note2, 2 dans l'autre sens, erreur sinon

	public:
		QString getTitre()const{return titre;}
		QString getDescription()const{return description;}
		void setTitre(const QString& t) {titre=t;}
		void setDescription(const QString d) {description=d;}
		bool existe_relation(Notes& n1,Notes& n2);
        void addCouple(QString l, int n1, int n2);
		void removeCouple(Notes& n1, Notes& n2);
		relation();
		~relation();
		int getOrientation()const{return orientation;}
};*/



#endif // RELATION_H_INCLUDED
