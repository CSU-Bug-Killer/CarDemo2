#ifndef AUTONAVIGATION_H
#define AUTONAVIGATION_H

#include <QWidget>

namespace Ui {
class AutoNavigation;
}
class AutoNavigation : public QWidget
{
    Q_OBJECT
public:
    explicit AutoNavigation(QWidget *parent = 0);
    ~AutoNavigation();
signals:

public slots:

private:
    Ui::AutoNavigation* ui;
};

#endif // AUTONAVIGATION_H
