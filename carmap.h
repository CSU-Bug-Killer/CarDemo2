#ifndef CARMAP_H
#define CARMAP_H

#include <QWidget>

namespace Ui {
class CarMap;
}
class CarMap : public QWidget
{
    Q_OBJECT
public:
    explicit CarMap(QWidget *parent = 0);
    ~CarMap();

signals:

public slots:

private:
    Ui::CarMap* ui;
};

#endif // CARMAP_H
