#ifndef LIGHTCONTROLLBOARD_H
#define LIGHTCONTROLLBOARD_H

#include <QWidget>

namespace Ui {
class LightControllBoard;
}
class LightControllBoard : public QWidget
{
    Q_OBJECT
public:
    explicit LightControllBoard(QWidget *parent = 0);
    ~LightControllBoard();
signals:

public slots:

private:
    Ui::LightControllBoard* ui;
};

#endif // LIGHTCONTROLLBOARD_H
