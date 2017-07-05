#include "carmap.h"
#include "ui_carmap.h"

CarMap::CarMap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CarMap)
{
    ui->setupUi(this);
}

CarMap::~CarMap()
{
    delete ui;
}
