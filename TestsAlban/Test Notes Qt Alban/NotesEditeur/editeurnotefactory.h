#ifndef EDITEURNOTEFACTORY_H
#define EDITEURNOTEFACTORY_H

#include "editeurnote.h"

class EditeurFactory{
public:
    virtual EditeurNote* createEditeur(Notes* n) = 0;
    static EditeurFactory* chooseEditeur(QString type);
};

class ArticleEditeurFactory : public EditeurFactory{
public:
    ArticleEditeur* createEditeur(Notes* n);
};


class TacheEditeurFactory : public EditeurFactory{
public:
    TacheEditeur* createEditeur(Notes* n);
};


class NoteFichierEditeurFactory : public EditeurFactory{
public:
    NoteFichierEditeur* createEditeur(Notes* n);
};


#endif // EDITEURNOTEFACTORY_H
