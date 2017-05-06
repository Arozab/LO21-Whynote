#include <string>
#include <iostream>
#include <timing.h>
using namespace std;


class Notes {
	
private:
	void setTitre(const string& t);
	void setDateModif(const date& d);
	Notes(const Notes & n);
	Notes& operator=(const Notes& n);
	Notes(const string& i, const string& ti, const string& te);
	~Notes();
	friend class NotesManager; //permission au NotesManager d'utiliser le constructeur et destructeur

protected:
	string id;
	string titre;
	const date dateCrea;
	date dateModif;
	//Empecher la duplication
	
public:
	string getId() const { return id; }
	string getTitre() const { return titre; }
	string getDateCrea() const { return dateCrea;}
	string getDateModif() const { return dateModif;}
	
};

class Article: protected Notes {


private:
	void setText(const string& t);
	string text;
public:
	string getText() const {return text;}

};

class NoteAvecFichier: protected Notes {


private:
	void setDescription(const string& t);
	void setFile(const string& t);
	string description;
	string file;
public:
	string getDescription() const {return description;}
	string getFile() const {return description;}

};
	
class Tache: protected Notes {

private:
	void setAction(const string& t);
	void setPriorite(const string& t);
	void setDateEch(const string& t);
	void setStatutTache(const string& t);
	string action;
	string priorite;
	date dateEch;
	statut statutTache;
public:
	string getAction() const {return action;}
	string getPriorite() const {return priorite;}
	string getDateEch() const {return dateEch;}
	string getStatutTache() const {return statutTache;}
};	
	
