#ifndef NOTEMANAGER_H
#define NOTEMANAGER_H

#include <QString>
#include <iostream>
#include <vector>
#include <typeinfo>
#include "timing.h"
#include "notes.h"

using namespace std;

/*! \class NotesManager
   * \brief Classe gérant toutes les opérations liées aux notes
*/
class NotesManager{

    private:
        unsigned int nbArticles;
        unsigned int nbNoteAvecFichier;
        unsigned int nbTaches;

        void addNoteAvecFichier(NoteAvecFichier* a);
        void addTaches(Tache* a);

        vector<Notes*> notes;
        unsigned int nbNotes;
        QString filename;	

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
        static Handler handler;	

    public:

        /*!
         *  \brief Destructeur de la classe
         */
        ~NotesManager();

        /*!
         *  \brief Retourne le chemin vers le fichier contenant toutes les notes    
         *  \return QString
         */
        QString getFilename()const{return filename;}

        /*!
         *  \brief Permet de modifier le chemin vers le fichier contenant toutes les notes
         *  \param f : QString
         *  \return void
         */
        void setFilename(QString f){filename=f;}

        /*!
         *  \brief Créé un nouvel article
         *  \param id : const QString&
         *  \param ti : const QString&
         *  \param te : const QString&
         *  \return Une référence vers l'article créé
         */
        Article& getNewArticle(const QString& id,const QString& ti,const QString& te);

        /*!
         *  \brief Renvoie une référence sur l'article avec l'id correspondant
         *  \param id : const QString&
         *  \return Une reference l'article en question.
         */
        Article& getArticle(const QString& id);

        /*!
         *  \brief Créé une nouvelle note avec fichier
         *  \param id : const QString&
         *  \param ti : const QString&
         *  \param de : const QString&
         *  \param fi : const QString&
         *  \return Une référence vers la nouvelle note avec fichier créée
         */
        NoteAvecFichier& getNewNoteAvecFichier(const QString& id,const QString& ti,const QString& de,const QString& fi);

        /*!
         *  \brief Renvoie une référence sur la note avec fichier avec l'id correspondant
         *  \param id : const QString&
         *  \return Une référence vers la note avec fichier créée
         */
        NoteAvecFichier& getNoteAvecFichier(const QString& id);

        /*!
         *  \brief Créé une nouvelle Tache
         *  \param id : const QString&
         *  \param ti : const QString&
         *  \param ac : const QString&
         *  \param pr : const QString&
         *  \param t : const QString&
         *  \return Une référence vers la nouvelle tache avec fichier créée
         */
        Tache& getNewTache(const QString& id,const QString& ti,const QString& ac,const QString& pr,const QString& t);

        /*!
         *  \brief Opérateur d'affectation
         *  \param n : reference constante vers une Note
         *  \return Une référence vers la tache 
         */
        Tache& getTache(const QString& id);

        /*!
         *  \brief Ajoute une note au tableau de notes
         *  \param n : pointeur vers une Note
         *  \return void
         */
        void addNotes(Notes* n);

        /*!
         *  \brief Charge le fichier contenant les notes
         *  \param f : référence const vers un QString qui contient le chemin vers le fichier en question
         *  \return void
         */
        void load(const QString& f);

        /*!
         *  \brief Sauvergarde dans le fichier contenant les notes
         *  \return void
         */
        void save()const;	

        /*!
         *  \brief Créé une unique instance du notes manager
         *  \return Une reference vers notes manager
         */
        static NotesManager& getInstance();

        /*!
         *  \brief Libère l'unique instance de notes manager
         *  \return void
        */
        static void libererInstance();

        /*!
         *  \brief Renvoie l'instance en cours sur le notes manager
         *  \return Une reference vers notes manager
         */
        static NotesManager& recupererInstance();

        /*!
         *  \brief Supprime la notes avec l'id correspondant et la place dans la corbeille
         *  \param id : QString
         *  \return void
         */
        void supprimerNote(QString id);

        /*!
         *  \brief Supprime la note définitivement
         *  \param n : pointeur vers la Note en question
         *  \return void
         */
        void supprimerNotedefinitivement(Notes* n);

        /*!
         *  \brief Renvoie le nombre de notes du tableau de notes
         *  \return unsigned int
        */
        unsigned int getnbNotes() const {return nbNotes;}


        /*! \class Iterator
           * \brief Classe qui permet de parcourir séquentiellement les éléments du tableau de notes
        */
        class Iterator{
        private:
            vector<Notes*> tab;
            unsigned int nb;
            unsigned int courant;
            Iterator(vector<Notes*> t,unsigned int n):tab(t),nb(n),courant(0){}
            friend class NotesManager;

        public:
            /*!
             *  \brief Renvoie une référence vers la note courante
             *  \return Référence vers la note actuelle
            */
            Notes& current()const{return *tab[courant];}

            /*!
             *  \brief Passe à la note suivante
             *  \return void
            */
            void next(){
                if(courant<nb) courant++;
                else throw NotesException("Iterator is done\n");
            }

            /*!
             *  \brief Renvoie un booléen pour savoir si on a parcouru toutes les notes ou non
             *  \return void
            */
            bool isDone(){return courant<0 || courant>=nb;}

            /*!
             *  \brief Passe à la note précédente
             *  \return void
            */
            void previous(){courant--;}

        };

        /*!
         *  \brief Créé un itérator
         *  \return Iterator créé
        */
        Iterator getIterator(){
            return Iterator(notes,nbNotes);
        }
     
};

#endif // NOTEMANAGER_H
