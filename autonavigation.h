#ifndef AUTONAVIGATION_H
#define AUTONAVIGATION_H

#include <QWidget>
#include <QTimer>
#include "communicawidget.h"
#include "singlemap.h"

namespace Ui {
class AutoNavigation;
}
class AutoNavigation : public QWidget
{
    Q_OBJECT
public:

    explicit AutoNavigation(QWidget *parent = 0);
    ~AutoNavigation();
    QPoint point2;
protected:
    void    paintEvent(QPaintEvent *);

public slots:
    void parseMsg(QString msg);
    void updateMap(QString position);

private:
    Ui::AutoNavigation* ui;
    QTimer timer;
    CommunicaWidget* singleConnect ;
    singleMap*  map;

signals:
    void MapUpdate(QString);

};

#endif // AUTONAVIGATION_H
