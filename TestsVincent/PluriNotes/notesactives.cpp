#include "notesactives.h"
#include "ui_notesactives.h"

NotesActives::NotesActives(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotesActives)
{
    ui->setupUi(this);
    //QObject::connect(ui->listWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(updatecurrentNote))
    //ui->listWidget->addItem();
}

NotesActives::~NotesActives()
{
    delete ui;
}
