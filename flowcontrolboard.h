#ifndef FLOWCONTROLBOARD_H
#define FLOWCONTROLBOARD_H

#include <QWidget>

namespace Ui {
class FlowControlBoard;
}
class FlowControlBoard : public QWidget
{
    Q_OBJECT
public:
    explicit FlowControlBoard(QWidget *parent = 0);
    ~FlowControlBoard();

signals:

public slots:

private:
    Ui::FlowControlBoard* ui;
};

#endif // FLOWCONTROLBOARD_H
