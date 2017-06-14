#include "notes.h"
#include <fstream>
#include <QFile>
#include <QTextCodec>
#include <QtXml>
#include <QMessageBox>
using namespace std;

//--------------------NOTES------------------------//
Notes::Notes(const QString& i, const QString& ti):id(i),titre(ti),ancienneVersion(NULL){

    time_t seconds = time(NULL);
    struct tm * timeinfo = localtime(&seconds);
    dateCrea=Date((timeinfo->tm_mday),(timeinfo->tm_mon+1),(1900+timeinfo->tm_year));
    dateModif=Date((timeinfo->tm_mday),(timeinfo->tm_mon+1),(1900+timeinfo->tm_year));
}


void Notes::setTitre(const QString& t){

    titre=t;
}

void Notes::setDateModif(const Date& d){

    dateCrea=d;
}

void Notes::setDateCrea(const Date& d){

    dateModif=d;
}

void Notes::setAncienneVersion(Notes* n){
    ancienneVersion.push_back(n);
}




//--------------------ARTICLE------------------------//
Article::Article(const QString& i, const QString& ti, const QString& t):Notes(i,ti),text(t){}
void Article::setText(const QString& t){

    text=t;
}


/*void Article::afficher(ostream& f) const{
    Notes::afficher(f);
    f<<"\nTexte : "<<getText()<<endl<<endl<<endl;
}*/


Article* Article::editer(){
    return this->clone();
}


//--------------------NOTEAVECFICHIER------------------------//
NoteAvecFichier::NoteAvecFichier(const QString& i,const QString& ti,const QString& d,const QString& f):Notes(i,ti),description(d),file(f){}

void NoteAvecFichier::setDescription(const QString& t){

    description=t;
}

void NoteAvecFichier::setFile(const QString& t){

    file=t;
}


/*void NoteAvecFichier::afficher(ostream& f)const{
    Notes::afficher(f);
    f<<"\nDescription : "<<getDescription()<<"\nLien du fichier : "<<getFile()<<endl<<endl<<endl;
}*/


NoteAvecFichier* NoteAvecFichier::editer(){
    return this->clone();
}


//--------------------TACHE------------------------//
Tache::Tache(const QString& i, const QString& ti,const QString& a,const QString& pr, const QString& t):Notes(i,ti),action(a),priorite(pr),statut(t){}

void Tache::setAction(const QString& a){

    action=a;
}

void Tache::setPriorite(const QString& pr){

    priorite=pr;
}

void Tache::setDateEch(const Date& d){

    dateEch=d;
}

void Tache::setStatut(QString t){

    statut=t;
}


/*void Tache::afficher(ostream& f)const{
    Notes::afficher(f);
    f<<"\nAction : "<<getAction()<<"\nPriorite : "<<getPriorite()<<"\nDate d'echeance : ";
    getDateEch();
    f<<"\nStatut de la tache : "<<getStatutTache()<<endl<<endl<<endl;
}*/

Tache* Tache::editer(){
    return this->clone();
}

