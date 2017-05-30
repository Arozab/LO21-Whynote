#ifndef NOTESACTIVES_H
#define NOTESACTIVES_H

#include <QWidget>

namespace Ui {
class NotesActives;
}

class NotesActives : public QWidget
{
    Q_OBJECT

public:
    explicit NotesActives(QWidget *parent = 0);
    ~NotesActives();

private:
    Ui::NotesActives *ui;
};

#endif // NOTESACTIVES_H
