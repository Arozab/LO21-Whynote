#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "parametresparcelle.h"

#include <QMainWindow>
#include <QFile>
#include <QDomDocument>
#include <QDomElement>
#include <QMessageBox>
#include <QStringList>
#include <QTreeWidget>
#include <QHash>

#include <vector>

using namespace std;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = 0 );
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow* ui;

    QFile file;
    QDomDocument domDoc;
    QStringList listConfig;
    vector<ParametresParcelle> listParamsParcelle;
    QHash<QTreeWidgetItem*, QDomElement> domElementForItem;

    void generateXMLstructure();
    bool saveDocument( QIODevice* device );

    QTreeWidgetItem* createItem(const QDomElement& element, QTreeWidgetItem* parentItem = 0);

    QStringList parseXMLFile();

};

#endif // MAINWINDOW_H
