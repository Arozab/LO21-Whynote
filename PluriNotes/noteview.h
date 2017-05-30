#ifndef NOTEVIEW_H
#define NOTEVIEW_H

#include <QWidget>

namespace Ui {
class NoteView;
}

class NoteView : public QWidget
{
    Q_OBJECT

public:
    explicit NoteView(QWidget *parent = 0);
    ~NoteView();

private:
    Ui::NoteView *ui;
};

#endif // NOTEVIEW_H
