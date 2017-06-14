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


/*! \class Corbeille
   * \brief Classe gérant la Corbeille
*/
class Corbeille
{
private :
    vector<Notes*> corbeille; /*!< Vector de pointeur de Notes*/
    /*!
     *  \brief Constructeur
     */
    Corbeille(); 
    /*!
     *  \brief Constructeur de recopie
     *  \param c : const Corbeille&
     */ 
    Corbeille(const Corbeille& c);
    /*!
     *  \brief Surcharge de l'opérateur =
     *  \param c : const Corbeille&
     *  \return Une référence sur un objet de type \e Corbeille.
     */     
    Corbeille& operator=(const Corbeille& c);
    /*!
     *  \brief Destructeur
     */ 
    ~Corbeille();
    /*! \struct HandlerC
     * \brief Classe permettant d'implémenter le design Pattern Singleton pour la classe \e Corbeille
     */
    struct HandlerC
    {

        Corbeille* instance; /*!<  Pointeur sur \e Corbeille représentant l'instance unique*/
        /*!
         *  \brief Constructeur
         *  Initialize l'instance à un pointeur nul
         */ 
        HandlerC() : instance(nullptr){}
        /*!
         *  \brief Destructeur
         */ 
        ~HandlerC(){
            delete instance;
            instance = nullptr;
        }
    };
    static HandlerC handlerc; /*!< Instance static de type \e HandlerC*/

public :
    /*!
     *  \brief Retourne l'instance unique de Corbeille
     *  \return Une référence sur l'instance unique Corbeille.
     */ 
    static Corbeille& getInstance();
    /*!
     *  \brief Libère l'instance Corbeille
     */ 
    static void libererInstance();
    /*!
     *  \brief Trouve une note avec le titre 
     *  Permet de trouver une note dans la corbeille grâce au titre entré en paramètre.
     *  \param titre : QString
     *  \return Un Pointeur sur la note trouvée.
     */ 
    Notes* getNoteTitre(QString titre);
    /*!
     *  \brief Trouve une note avec la position
     *  Permet de trouver la note à la position entré en paramètre.
     *  \param position : unsigned int
     *  \return Un Pointeur sur la note trouvée.
     */ 
    Notes* getNotePosition(unsigned int position);
    /*!
     *  \brief Nombre de note dans la corbeille 
     *  \return Un Entier correspondantau nombre de note dans la corbeille.
     */ 
    unsigned int getSize() { return corbeille.size(); }
    /*!
     *  \brief Restaure une Note entré en paramètre
     *  \param n : Notes*
     */ 
    void restaurerNote(Notes* n);
    /*!
     *  \brief Supprime une note définitivement 
     *  \param n : Notes*
     */ 
    void supprimerNote(Notes* n);
    /*!
     *  \brief Ajoute une note dans la corbeille
     *  \param n : Notes*
     */ 
    void addNote(Notes* n);
    /*!
     *  \brief Vide la corbeille 
     */ 
    void vider() { corbeille.clear();}
};

#endif // CORBEILLE_H
