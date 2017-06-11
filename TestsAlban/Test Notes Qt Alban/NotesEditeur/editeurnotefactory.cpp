#include "editeurnotefactory.h"
#include "editeurnote.h"

EditeurFactory* EditeurFactory::chooseEditeur(QString type) {
    if(type==(QString) "7Article") {
        ArticleEditeurFactory* factory = new ArticleEditeurFactory();
        return factory;
    }
    else if(type==(QString) "5Tache") {
        TacheEditeurFactory* factory = new TacheEditeurFactory();
        return factory;
    }
    else if(type==(QString) "15NoteAvecFichier") {
        NoteFichierEditeurFactory* factory = new NoteFichierEditeurFactory();
        return factory;
    }
    else
    {
        throw NotesException("Mauvais type..");
    }
}

ArticleEditeur* ArticleEditeurFactory::createEditeur(Notes* n) {
    ArticleEditeur* ae = new ArticleEditeur(dynamic_cast<Article*>(n));
    return ae;
}

TacheEditeur* TacheEditeurFactory::createEditeur(Notes* n) {
    TacheEditeur* te = new TacheEditeur(dynamic_cast<Tache*>(n));
    return te;
}

NoteFichierEditeur* NoteFichierEditeurFactory::createEditeur(Notes* n) {
    NoteFichierEditeur* ae = new NoteFichierEditeur(dynamic_cast<NoteAvecFichier*>(n));
    return ae;
}
