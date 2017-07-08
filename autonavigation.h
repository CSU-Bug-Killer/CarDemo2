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
protected:
    void    paintEvent(QPaintEvent *);
public slots:
    void parseMsg(QString msg);
    void updateAutomap(QString position);

private:
    Ui::AutoNavigation* ui;
    QTimer timer;
    CommunicaWidget* singleConnect ;
    singleMap*  map;
  //  QPoint  point2;
signals:
 //   void autoMapUpdate(QString);
};

#endif // AUTONAVIGATION_H
