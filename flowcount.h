#ifndef FLOWCOUNT_H
#define FLOWCOUNT_H

#include <QWidget>
#include "communicawidget.h"

namespace Ui {
class FlowCount;
}
class FlowCount : public QWidget
{
    Q_OBJECT
public:
    explicit FlowCount(QWidget *parent = 0);
    ~FlowCount();
signals:

public slots:

    void onReadMessageSave(QString msg);
private:
    Ui::FlowCount* ui;

    CommunicaWidget* conServer;
};

#endif // FLOWCOUNT_H
