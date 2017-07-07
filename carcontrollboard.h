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

private slots:

    void switchChangeState();

    void on_straightBtn_clicked();
    void on_leftBtn_clicked();
    void on_rightBtn_clicked();
    void on_stopBtn_clicked();
    void on_backBtn_clicked();
    void on_resetBtn_clicked();

private:
    Ui::CarControllBoard* ui;

    bool isOpen=false;
};

#endif // CARCONTROLLBOARD_H
