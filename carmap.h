#ifndef CARMAP_H
#define CARMAP_H

#include <QWidget>
#include "communicawidget.h"
#include "singlemap.h"

namespace Ui {
class CarMap;
}
class CarMap : public QWidget
{
    Q_OBJECT
public:
    explicit CarMap(QWidget *parent = 0);
    ~CarMap();
protected:
    void    paintEvent(QPaintEvent *);
public slots:
    void parseMsg(QString msg);


private:
    Ui::CarMap* ui;

    CommunicaWidget* singleConnect ;
    singleMap*  map;
};

#endif // CARMAP_H
