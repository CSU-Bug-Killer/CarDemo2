#ifndef SINGLEMAP_H
#define SINGLEMAP_H

#include <QObject>
#include <QPixmap>
#include <QLine>
#include <QHash>

class singleMap : public QObject
{
    Q_OBJECT
public:
    explicit singleMap(QObject *parent = 0);
    //构建一个hash表保存卡坐标与地图坐标的对应关系
    bool    createHashSet(void);
    //构建地图路线
    bool    createRoads(void);

public:
    //获取地图单例
    static singleMap*   getInstance()
    {
        static  singleMap*  instance = NULL;
        if(NULL == instance)
        {
            instance = new singleMap;
        }
        return instance;
    }
    //获取hash地图数据
    QHash<qlonglong, QPoint>*   getMapHashSet(void);
    //获取路线数据
    QLine*                      getMapRoads(void);
    //获取地图背景图片
    QPixmap                     getBackground(void);

private:
    QPixmap                     mapBackground;
    QHash<qlonglong, QPoint>    mapHashSet;
    QLine                       mapRoads[23];
    int                         scale;

signals:

public slots:
};

#endif // SINGLEMAP_H
