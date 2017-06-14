#ifndef FENETRECORBEILLE_H
#define FENETRECORBEILLE_H

#include "corbeille.h"
#include <QScrollArea>

/*! \class FenetreCorbeille
   * \brief Classe gérant l'affichage de la Corbeille
*/
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
    /*!
     *  \brief Constructeur qui initialise une zone qui affiche les notes supprimées, et les boutons
     *  \param parent : QWidget*
     */
    FenetreCorbeille(QWidget* parent=0);
    /*!
     *  \brief Accéder à l'adresse de la liste de notes supprimées 
     *  \return Un Pointeur sur un \e QListWidget
     */ 
    QListWidget* getList(){ return notesSupp; }
    /*!
     *  \brief Accéder à l'adresse du bouton supprimer 
     *  \return Un Pointeur sur un \e QPushButton
     */ 
    QPushButton* getSupprimer(){ return supprimer; }
    /*!
     *  \brief Accéder à l'adresse du bouton vider 
     *  \return Un Pointeur sur un \e QPushButton
     */
    QPushButton* getVider() { return vider; }
    /*!
     *  \brief Accéder à l'adresse du bouton restaurer 
     *  \return Un Pointeur sur un \e QPushButton
     */
    QPushButton* getRestaurer() { return restaurer; }
    /*!
     *  \brief Actualise la corbeille 
     */
    void actualiserCorbeille();

public slots :
    /*!
     *  \brief Active les boutons de la corbeille 
     */
    void activerBouton();
    /*!
     *  \brief Restaure une note 
     *  \return Un Pointeur sur une \e Notes
     */
    Notes* restaurerNote();
    /*!
     *  \brief Supprime une note 
     */
    void supprimerNote();
    /*!
     *  \brief Vide la corbeille 
     */
    void viderCorbeille();
};

#endif // FENETRECORBEILLE_H
