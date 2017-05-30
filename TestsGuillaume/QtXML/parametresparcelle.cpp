#include "parametresparcelle.h"

ParametresParcelle::ParametresParcelle()
    : nom(""),
      longueur(""),
      largeur(""),
      volumePulverise(""),
      volumeHectare("")
{}

void ParametresParcelle::setNom(const QString& nom)
{
    this->nom = nom;
}

void ParametresParcelle::setLongueur(const QString& longueur)
{
    this->longueur = longueur;
}

void ParametresParcelle::setLargeur(const QString& largeur)
{
    this->largeur = largeur;
}

void ParametresParcelle::setVolumePulverise(const QString& volumePulverise)
{
    this->volumePulverise = volumePulverise;
}

void ParametresParcelle::setVolumeHectare(const QString& volumeHectare)
{
    this->volumeHectare = volumeHectare;
}

QString ParametresParcelle::getNom() const
{
    return ( this->nom );
}
