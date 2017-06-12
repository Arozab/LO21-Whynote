#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QString>
#include <iostream>
#include <vector>
#include <typeinfo>
#include "timing.h"
#include "notes.h"
//#include "versionsmanager.h"
using namespace std;

class NotesManager{

    private:
        unsigned int nbArticles;
        unsigned int nbNoteAvecFichier;
        unsigned int nbTaches;

        void addNoteAvecFichier(NoteAvecFichier* a);
        void addTaches(Tache* a);
        void addNotes(Notes* n);

        vector<Notes*> notes;
        unsigned int nbNotes;
        QString filename;	//pour le fichier contenant les notes

        friend class QMainWindow;
        friend class VersionsManager;

        NotesManager();
        NotesManager(const NotesManager& m);
        NotesManager& operator=(const NotesManager& m);

        struct Handler
        {
            NotesManager* instance;
            Handler():instance(nullptr){}
            ~Handler(){
                delete instance;
                instance=nullptr;
            }
        };
        static Handler handler;	//le destructeur sera appelé automatiquement à la fin du programme pour cet objet

    public:
        ~NotesManager();
        QString getFilename()const{return filename;}
        void setFilename(QString f){filename=f;}

        void addArticles(Article* a);
        Article& getNewArticle(const QString& id,const QString& ti,const QString& te);
        Article& getArticle(const QString& id);

        NoteAvecFichier& getNewNoteAvecFichier(const QString& id,const QString& ti,const QString& de,const QString& fi);
        NoteAvecFichier& getNoteAvecFichier(const QString& id);

        Tache& getNewTache(const QString& id,const QString& ti,const QString& ac,const QString& pr,const QString& t);
        Tache& getTache(const QString& id);

        void load(const QString& f);
        void save()const;	//on ajoute la note modifiée dans le tableau notes de notesManager (si elle existe deja, remplacer l'ancienne version)
        static NotesManager& getInstance();
        static void libererInstance();
        static NotesManager& recupererInstance();
        void supprimerNote(QString id);
        void supprimerNotedefinitivement(Notes* n);

        unsigned int getnbNotes() const {return nbNotes;}
        Notes& edition(Notes* n);

        Notes* getNotes(unsigned int i)const{return notes[i];}
        //Notes& getNotes(const QString& id);

        class Iterator{
        private:
            vector<Notes*> tab;
            unsigned int nb;
            unsigned int courant;
            Iterator(vector<Notes*> t,unsigned int n):tab(t),nb(n),courant(0){}
            friend class NotesManager;

        public:
            //Iterator():tab(nullptr),nb(0),courant(0) {}
            Notes& current()const{return *tab[courant];}
            void next(){
                if(courant<nb) courant++;
                else throw NotesException("Iterator is done\n");
            }
            bool isDone(){return courant<0 || courant>=nb;}
            void previous(){courant--;}

        };
        Iterator getIterator(){
            return Iterator(notes,nbNotes);
        }

//		Iterator first(){return Iterator(tabNotes,nbNotes,0);}
//        Iterator last(){return Iterator(tabNotes,nbNotes,nbNotes-1);}
};

#endif // NOTEMANAGER_H
