#ifndef RELATION_H_INCLUDED
#define RELATION_H_INCLUDED

#include <string>
#include <iostream>
#include <vector>
#include "notes.h"
#include "timing.h"
using namespace std;

class couple{

	private:
		string label;
		Notes* note1;
		Notes* note2;
		void setLabel(const string& l);
		couple();
		couple(const string& l,Notes& n1,Notes& n2):label(l),note1(&n1),note2(&n2){}
        ~couple();
		friend class relation;

	public:
		string getLabel() const { return label;}
		Notes* getNotes1() { return note1;}
		Notes* getNotes2() { return note2;}
};


class relation{

	private:
		string titre;
		string description;
		vector<couple*> ensemble_couple;

	public:
		string getTitre()const{return titre;}
		string getDescription()const{return description;}
		void setTitre(const string& t) {titre=t;}
		void setDescription(const string d) {description=d;}
		virtual bool existe_relation(Notes& n1,Notes& n2);
		void addCouple(string l, Notes& n1, Notes& n2);
		void removeCouple(Notes& n1, Notes& n2);
		relation();
		~relation();
};

class relationNoOriente : public relation {
	public :
	bool existe_relation(Notes& n1, Notes& n2);
};

#endif // RELATION_H_INCLUDED
