#ifndef CARMAP_H
#define CARMAP_H
#include <QTimer>
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
    QPoint  point;
    explicit CarMap(QWidget *parent = 0);
    ~CarMap();
protected:
    void    paintEvent(QPaintEvent *);
public slots:
    void parseMsg(QString msg);
    void updateCarmap(QString position);

private:
    Ui::CarMap* ui;

    QTimer timer;
    CommunicaWidget* singleConnect ;
    singleMap*  map;
signals:
    void carMapUpdate(QString);
};

#endif // CARMAP_H
