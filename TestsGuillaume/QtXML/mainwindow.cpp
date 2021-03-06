#include "mainwindow.h"
//#include "ui_mainwindow.h"

#include <QTextStream>
#include <QDomNode>
#include <QDebug>

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent ),
      ui( new Ui::MainWindow ),
      file("config.xml")
{
    ui->setupUi( this );
    ui->paramsList->addItems(parseXMLFile());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString errorStr;

    int errorLine;
    int errorColumn;

    if( ! file.open( QIODevice::ReadWrite ) )
    {
        QMessageBox::warning(this, "ERREUR", "Une erreur est survenue lors de l'ouverture du fichier de configuration.");
        return;
    }

    // On définit la structure du DOM à partir du contenu du fichier XML
    if( ! domDoc.setContent( &file, true, &errorStr, &errorLine, &errorColumn ) )
    {
        QMessageBox::information(this, "Erreur XML", tr("Erreur à la ligne %1, colonne %2:\n%3").arg( errorLine ).arg( errorColumn ).arg( errorStr ));
        file.close();
        return;
    }

    generateXMLstructure();

    // On vide le fichier
    file.resize(0);

    // On sauvegarde les nouveaux paramètres dans le fichier XML
    if( saveDocument( &file ) )
    {
        QMessageBox::information(this, "INFO", "Les paramètres ont bien été sauvegardés.");
    }

    file.close();
}

// Méthode permettant de générer la structure XML
void MainWindow::generateXMLstructure()
{
    // Noeud racine - <epandage></epandage>
    QDomElement root = domDoc.documentElement();

    // Groupe de paramètre
    QDomElement groupParams = domDoc.createElement("parametres");

    // Paramètres de la parcelle
    QDomElement plotParams = domDoc.createElement("parametres_parcelle");

    // On créé les paramètres de la parcelle
    QDomElement nameElem             = domDoc.createElement("nom");
    QDomElement lengthElem           = domDoc.createElement("longueur");
    QDomElement widthElem            = domDoc.createElement("largeur");
    QDomElement volumeSprayedElem    = domDoc.createElement("volume_pulverise");
    QDomElement volumePerHectareElem = domDoc.createElement("volume_hectare");

    // On définit les valeurs des paramètres de la parcelle
    nameElem.appendChild(domDoc.createTextNode(ui->nomParcelle->text()));
    lengthElem.appendChild(domDoc.createTextNode(QString::number(ui->longueurParcelle->value())));
    widthElem.appendChild(domDoc.createTextNode(QString::number(ui->largeurParcelle->value())));
    volumeSprayedElem.appendChild(domDoc.createTextNode(QString::number(ui->volumeParcelle->value())));
    volumePerHectareElem.appendChild(domDoc.createTextNode(QString::number(ui->volumeHectare->value())));

    // On ajoute les paramètres de la parcelle dans le noeud parent ( parametres_parcelle )
    plotParams.appendChild(nameElem);
    plotParams.appendChild(lengthElem);
    plotParams.appendChild(widthElem);
    plotParams.appendChild(volumeSprayedElem);
    plotParams.appendChild(volumePerHectareElem);

    groupParams.appendChild(plotParams);
    root.appendChild(groupParams);
}

// Méthode permettant de sauvegarder le DOM xml dans un fichier
bool MainWindow::saveDocument( QIODevice* device )
{
    // On définit le niveau d'indentation pour que le fichier soit plus visible
    const int indentSize = 2;

    QTextStream out( device );
    domDoc.save(out, indentSize);

    return true;
}

// Méthode permettant de lire le fichier XML
// Cette méthode renvoie l'historique sous forme d'un QStringList à intégrer via addItems()
QStringList MainWindow::parseXMLFile()
{
    QDomElement root = domDoc.documentElement();
    QDomElement child = root.firstChildElement();

    while( ! child.isNull() )
    {
        QDomElement groupParams = child.firstChildElement();

        while( ! groupParams.isNull() )
        {
            if( groupParams.tagName() == "parametres_parcelle")
            {
                QDomElement param = groupParams.firstChildElement();

                if( param.isNull() ) continue;

                ParametresParcelle parcelle;

                while( ! param.isNull() )
                {
                    if( param.tagName() == "nom" )
                        parcelle.setNom(param.text());
                    else if( param.tagName() == "longueur" )
                        parcelle.setLongueur(param.text());
                    else if( param.tagName() == "largeur" )
                        parcelle.setLargeur(param.text());
                    else if( param.tagName() == "volume_pulverise" )
                        parcelle.setVolumePulverise(param.text());
                    else if( param.tagName() == "volume_hectare" )
                        parcelle.setVolumeHectare(param.text());

                    param = param.nextSiblingElement();
                }

                listParamsParcelle.push_back( parcelle );

                listConfig.push_back(parcelle.getNom());
            }

            groupParams = groupParams.nextSiblingElement();
        }

        child = child.nextSiblingElement();
    }

    return listConfig;

}

// Méthode permettant de créer un nouvel item de type QTree et renvoie un pointeur sur cet item
QTreeWidgetItem* MainWindow::createItem(const QDomElement& element, QTreeWidgetItem* parentItem)
 {
     QTreeWidgetItem* item;

     if( parentItem ) {
         item = new QTreeWidgetItem( parentItem );
     } else {
         item = new QTreeWidgetItem( this );
     }

     domElementForItem.insert(item, element);

     return item;
 }
