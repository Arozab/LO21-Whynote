#ifndef ZONECENTRALE_H
#define ZONECENTRALE_H

#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>

class ZoneCentral : public QMdiarea {
    Q_OBJECT
private:
public :
    ZoneCentral(QWidget *parent=0);
};


#endif // ZONECENTRALE_H
