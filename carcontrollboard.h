#ifndef CARCONTROLLBOARD_H
#define CARCONTROLLBOARD_H

#include <QWidget>

namespace Ui {
class CarControllBoard;
}
class CarControllBoard : public QWidget
{
    Q_OBJECT
public:
    explicit CarControllBoard(QWidget *parent = 0);
    ~CarControllBoard();
signals:

public slots:

private:
    Ui::CarControllBoard* ui;
};

#endif // CARCONTROLLBOARD_H
