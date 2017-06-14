#ifndef EDITEURNOTEFACTORY_H
#define EDITEURNOTEFACTORY_H

#include "editeurnote.h"

/*! \class EditeurFactory
   * \brief Classe abstraite de la création d'un éditeur de Notes
*/
class EditeurFactory{
public:
    /*!
     *  \brief  Créer un editeur de Notes
     *  \param n : Notes*
     *  \return Un Pointeur vers un \e EditeurNote.
     */ 
    virtual EditeurNote* createEditeur(Notes* n) = 0;
    /*!
     *  \brief Choisit le type de Factory d'editeur de note à utiliser
     *  \param type : QString
     *  \return Un Pointeur vers un \e EditeurFactory.
     */ 
    static EditeurFactory* chooseEditeur(QString type);
};

/*! \class ArticleEditeurFactory
   * \brief Classe de la création d'un éditeur d'Article
*/
class ArticleEditeurFactory : public EditeurFactory{
public:
    /*!
     *  \brief Créer un editeur d'Article 
     *  \param n : Notes*
     *  \return Un Pointeur vers un \e ArticleEditeur.
     */ 
    ArticleEditeur* createEditeur(Notes* n);
};

/*! \class TacheEditeurFactory
   * \brief Classe de la création d'éditeur de Tache
*/
class TacheEditeurFactory : public EditeurFactory{
public:
    /*!
     *  \brief Créer un editeur de Tache 
     *  \param n : Notes*
     *  \return Un Pointeur vers un \e TacheEditeur.
     */ 
    TacheEditeur* createEditeur(Notes* n);
};

/*! \class NoteFichierEditeurFactory
   * \brief Classe de la création d'un éditeur de NoteAvecFichier
*/
class NoteFichierEditeurFactory : public EditeurFactory{
public:
    /*!
     *  \brief Créer un editeur de NoteAvecFichier 
     *  \param n : Notes*
     *  \return Un Pointeur vers un \e NoteFichierEditeur.
     */ 
    NoteFichierEditeur* createEditeur(Notes* n);
};


#endif // EDITEURNOTEFACTORY_H
