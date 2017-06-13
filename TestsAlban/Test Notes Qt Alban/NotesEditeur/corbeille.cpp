#include "corbeille.h"
#include "fenetreprincipale.h"

Corbeille::Corbeille(){}

Corbeille::~Corbeille() {
    for(unsigned int i=0; i<corbeille.size(); i++)
    {
        delete corbeille[i];
    }
    corbeille.clear();
}

Corbeille::HandlerC Corbeille::handlerc=Corbeille::HandlerC();

Corbeille& Corbeille::getInstance() {
    if(handlerc.instance==nullptr) {
        handlerc.instance = new Corbeille;
        return *handlerc.instance;
    }
    else {
        //throw NotesException("Erreur, on a déjà une corbeille");
        return *handlerc.instance;
    }
}

void Corbeille::libererInstance() {
    delete handlerc.instance;
    handlerc.instance=nullptr;
}

Notes* Corbeille::getNoteTitre(QString titre){
    for(unsigned int i=0; i<corbeille.size();i++){
        if(corbeille[i]->getTitre() == titre) { return corbeille[i]; }
        else {
            throw NotesException("Il n'y a pas de note avec cet id.");
        }
    }
}

Notes* Corbeille::getNotePosition(unsigned int position){
    if(position<corbeille.size()) {
        return corbeille[position];
    }
    else {
        throw NotesException("Note pas trouvé");
    }
}


void Corbeille::addNote(Notes* n){
  corbeille.push_back(n);
}

void Corbeille::restaurerNote(Notes* n){
    for (unsigned int i=0;corbeille.size();i++) {
        if (corbeille[i]==n) {
            NotesManager& m=NotesManager::recupererInstance();
            FenPrincipale& fp = FenPrincipale::getInstance();
            m.addNotes(n);
            m.save();
            fp.actualiserNote();
            corbeille.erase(corbeille.begin()+i);
            return;
        }
    }
}

void Corbeille::supprimerNote(Notes* n){
    for (unsigned int i=0;corbeille.size();i++) {
        if (corbeille[i]==n) {
            // le supprimer des couples et relation aussi
            NotesManager& m = NotesManager::getInstance();
            corbeille.erase(corbeille.begin()+i);
            m.supprimerNotedefinitivement(n);
            return;
        }
    }
}
