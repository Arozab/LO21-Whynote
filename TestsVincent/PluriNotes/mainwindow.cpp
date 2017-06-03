#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->label_note->setText("jgj");
    QObject::connect(ui->actionSave, SIGNAL(triggered(bool)), this, SLOT(reactSave()));
}

void MainWindow::reactSave(){
    qDebug() << "clicked !";
    ui->centralLayout->addWidget(new NoteView);
}

MainWindow::~MainWindow()
{
    delete ui;
}
