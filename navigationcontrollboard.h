#ifndef NAVIGATIONCONTROLLBOARD_H
#define NAVIGATIONCONTROLLBOARD_H

#include <QWidget>

namespace Ui {
class NavigationControllBoard;
}
class NavigationControllBoard : public QWidget
{
    Q_OBJECT
public:
    explicit NavigationControllBoard(QWidget *parent = 0);
    ~NavigationControllBoard();
signals:

public slots:

private slots:
    void AutoModelSwitchBtnClicked();

private:
    Ui::NavigationControllBoard* ui;
    bool isAutoModelOn = false;
};

#endif // NAVIGATIONCONTROLLBOARD_H
