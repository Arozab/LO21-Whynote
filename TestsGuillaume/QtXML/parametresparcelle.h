#ifndef PARAMETRESPARCELLE_H
#define PARAMETRESPARCELLE_H

#include <QString>

class ParametresParcelle
{

public:
    ParametresParcelle();

    void setNom(const QString& nom);
    void setLongueur(const QString& longueur);
    void setLargeur(const QString& largeur);
    void setVolumePulverise(const QString& volumePulverise);
    void setVolumeHectare(const QString& volumeHectare);

    QString getNom() const;

private:

    QString nom;
    QString longueur;
    QString largeur;
    QString volumePulverise;
    QString volumeHectare;
};

#endif // PARAMETRESPARCELLE_H
