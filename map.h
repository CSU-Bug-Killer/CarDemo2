#ifndef MAP_H
#define MAP_H
#include <QTimer>
#include <QWidget>
#include "singlemap.h"
#include "communicawidget.h"

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
        void parseMsg(QString msg);
        void updateMap(QString s1,QString s2);

private:
    Ui::Map* ui;
    singleMap*  map;
    QString  light1;
    QString  light2;
    QTimer timer;
    CommunicaWidget* singleConnect ;
signals:
    void MapUpdate(QString light1,QString light2);
};

#endif // MAP_H
