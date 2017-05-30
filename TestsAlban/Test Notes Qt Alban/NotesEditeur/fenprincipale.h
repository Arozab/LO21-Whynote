#ifndef HEADER_FENPRINCIPALE
#define HEADER_FENPRINCIPALE

#include <QtWidgets>
#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QXmlStreamReader>
#include <QFile>


class FenPrincipale : public QMainWindow
{
    Q_OBJECT

    public:
        FenPrincipale();
        void load(QString f);

    public slots:
        void ouvrirDialogue();

    private:
        QWidget *zoneCentrale;
        QMenu *menuFichier;
        QAction *actionQuitter;
        QComboBox *liste;
        QPushButton* bouton1;
        QGridLayout *layout;

};

#endif
