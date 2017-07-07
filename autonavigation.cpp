#include "autonavigation.h"
#include "ui_autonavigation.h"
AutoNavigation::AutoNavigation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AutoNavigation)
{
    ui->setupUi(this);
}

AutoNavigation::~AutoNavigation()
{
    delete ui;
}
