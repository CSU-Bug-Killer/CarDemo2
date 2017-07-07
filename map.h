#ifndef MAP_H
#define MAP_H

#include <QWidget>
#include "singlemap.h"

namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = 0);
    ~Map();

protected:
    void    paintEvent(QPaintEvent *);
public slots:

private:
    Ui::Map* ui;
    singleMap*  map;
};

#endif // MAP_H
