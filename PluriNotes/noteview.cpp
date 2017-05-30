#include "noteview.h"
#include "ui_noteview.h"

NoteView::NoteView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NoteView)
{
    ui->setupUi(this);
}

NoteView::~NoteView()
{
    delete ui;
}
