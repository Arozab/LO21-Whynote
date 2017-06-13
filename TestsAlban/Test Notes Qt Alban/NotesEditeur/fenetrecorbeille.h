#ifndef FENETRECORBEILLE_H
#define FENETRECORBEILLE_H

#include "corbeille.h"
#include <QScrollArea>

class FenetreCorbeille : public QWidget {
    Q_OBJECT
    private:

       QListWidget* notesSupp;
       QPushButton* vider;
       QPushButton* supprimer;
       QPushButton* restaurer;
       QScrollArea* liste;
       QHBoxLayout* cliste;
       QHBoxLayout* cbouton;
       QHBoxLayout* cvider;
       QVBoxLayout* zone;

   public:
       FenetreCorbeille(QWidget* parent=0);
       QListWidget* getList(){ return notesSupp; }
       QPushButton* getSupprimer(){ return supprimer; }
       QPushButton* getVider() { return vider; }
       QPushButton* getRestaurer() { return restaurer; }
       void actualiserCorbeille();

   public slots :
       void supprimerNote();
       void viderCorbeille();
       Notes* restaurerNote();
       void activerBouton();
};

#endif // FENETRECORBEILLE_H
