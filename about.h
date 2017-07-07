#ifndef ABOUT_H
#define ABOUT_H

namespace Ui {
class About;
}
#include <QDialog>

class About : public QDialog
{
    Q_OBJECT
public:
    explicit About(QWidget *parent = 0);
    ~About();
signals:

public slots:

private:
    Ui::About* ui;

};

#endif // ABOUT_H
