#ifndef ARTICLEEDITEUR_H
#define ARTICLEEDITEUR_H
#include <QObject>
#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "Notes.h"
class ArticleEditeur : public QWidget
{
    Article* article;
    QLabel* idlabel;
    QLabel* titrelabel;
    QLabel* textlabel;
    QLineEdit* id;
    QLineEdit* titre;
    QTextEdit* text;
    QHBoxLayout* cid;
    QHBoxLayout* ctitre;
    QHBoxLayout* ctext;
    QVBoxLayout* ccouche;
    QPushButton* sauver;


    Q_OBJECT
public:
    explicit ArticleEditeur(Article& a,QWidget *parent = 0);

signals:

public slots:
    void saveArticle();
private slots:
    void activerSauver(QString str="");
};

#endif // ARTICLEEDITEUR_H
