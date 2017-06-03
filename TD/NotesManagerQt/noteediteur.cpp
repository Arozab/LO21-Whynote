#include "noteediteur.h"

ArticleEditeur::ArticleEditeur(Article &a, QWidget *parent) : QWidget(parent),article(&a)
{
    //QMainWindow::setCentralWidget(this);
    id=new QLineEdit(this);
    titre=new QLineEdit(this);
    text=new QTextEdit(this);
    idlabel=new QLabel("identificateur",this);
    titrelabel=new QLabel("titre",this);
    textlabel=new QLabel("text",this);
    m_boutonSauver=new QPushButton("Sauver",this);
    m_boutonQuitter=new QPushButton("Quitter",this);
    cid=new QHBoxLayout;
    cid->addWidget(idlabel);
    cid->addWidget(id);
    ctitre=new QHBoxLayout;
    ctitre->addWidget(titrelabel);
    ctitre->addWidget(titre);
    ctext=new QHBoxLayout;
    ctext->addWidget(textlabel);
    ctext->addWidget(text);
    ccouche=new QVBoxLayout;
    ccouche->addLayout(cid);
    ccouche->addLayout(ctitre);
    ccouche->addLayout(ctext);
    ccouche->addWidget(m_boutonSauver);
    ccouche->addWidget(m_boutonQuitter);
    id->setText(article->getId());
    titre->setText(article->getTitle());
    text->setText(article->getText());
    id->setDisabled(true);
    setLayout(ccouche);

    QDockWidget *dock = new QDockWidget(tr("Notes"), this);
    dock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::LeftDockWidgetArea);
    //customerList = new QListWidget(dock);
    //customerList->addItems(QStringList();

 
    QObject::connect(m_boutonSauver,SIGNAL(clicked()),this,SLOT(saveArticle()));
    QObject::connect(m_boutonQuitter,SIGNAL(clicked()),this,SLOT(closeArticle()));
    QObject::connect(titre,SIGNAL(textChanged(QString)),this,SLOT(activerSauver(QString)));
    QObject::connect(text,SIGNAL(textChanged()),this,SLOT(activerSauver()));
    QObject::connect(this, SIGNAL(quitter()), qApp, SLOT(quit()));



    m_boutonSauver->setDisabled(true);
}

void ArticleEditeur::saveArticle(){
    article->setTitle(titre->text());
    article->setText(text->toPlainText());
    QMessageBox::information(this,"Sauvegarder","Article sauvegardé !");
    m_boutonSauver->setDisabled(true);
    m_boutonQuitter->setEnabled(true);
}

void ArticleEditeur::closeArticle(){
   //QMessageBox::information(this,"Qu","Article sauvegardé !");
   emit quitter();
}

void ArticleEditeur::activerSauver(QString){
    m_boutonSauver->setEnabled(true);
    m_boutonQuitter->setDisabled(true);
}
