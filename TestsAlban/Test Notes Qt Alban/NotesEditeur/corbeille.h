#ifndef CORBEILLE_H
#define CORBEILLE_H

#include <iostream>
#include <QSet>
#include <QList>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QHBoxLayout>
#include <QPushButton>
#include <QMessageBox>

#include "notes.h"
#include "notemanager.h"
#include "relation.h"

class Corbeille
{
private :
    vector<Notes*> corbeille;
    Corbeille();
    Corbeille(const Corbeille& c);
    Corbeille& operator=(const Corbeille& c);
    ~Corbeille();
    //singleton
    struct HandlerC
    {
        Corbeille* instance;
        HandlerC() : instance(nullptr){}
        ~HandlerC(){
            delete instance;
            instance = nullptr;
        }
    };
    static HandlerC handlerc;

public :
    static Corbeille& getInstance();
    static void libererInstance();
    void restaurerNote(Notes* n);
    Notes* getNoteTitre(QString titre);
    Notes* getNotePosition(unsigned int position);
    void supprimerNote(Notes* n);
    void addNote(Notes* n);
    void vider() { corbeille.clear();}
    unsigned int getSize() { return corbeille.size(); }
};

#endif // CORBEILLE_H
