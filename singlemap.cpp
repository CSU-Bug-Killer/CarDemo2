#include "singlemap.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

singleMap::singleMap(QObject *parent) : QObject(parent)
{
    this->mapBackground.load(":/image/map.png");
    this->scale = 1;
    this->createRoads();
    this->createHashSet();
//    for(int i=0;i<71;i++){
//        qDebug()<<this->getMapHashSet()->value(i).x();
//        qDebug()<<this->getMapHashSet()->value(i).y();

  //  }
   // qDebug()<<this->getMapHashSet()->value(1);

}


bool singleMap::createHashSet()
{
    QTextStream     in;
        int             currRoadNo = 0;
        int             lastRoadNo = -1;
        int             scale = 1;
        QString         readBuf;
        QList<QString>  currRoad;

        //打开地图信息文件
        QFile  cardInfo(":/resource/cardNumber.txt");

    //        if(!cardInfo.open(QFile::ReadOnly|QFile::Text))
    //        {
    //            qDebug()<<"打开文件失败";
    //        }else {
    //            qDebug()<<"打开文件success";
    //        }

       cardInfo.open(QIODevice::ReadOnly);
       in.setDevice(&cardInfo);

    while(!in.atEnd())
    {
        //清空缓冲区
        readBuf.clear();
        readBuf = in.readLine();//读取一行记录
        if(readBuf.contains("Road")){//读到路号

            readBuf.remove("Road");
            currRoadNo = readBuf.toInt(0, 10);
            if(currRoadNo>0) currRoadNo -= 1;

            if(lastRoadNo == -1)
            {//第一条路
                lastRoadNo = currRoadNo;
            }
            else if(currRoadNo!=lastRoadNo)
            {//读到新的路号，保存上一条路
                double     inc = 0.0;
                QPoint  point(0, 0);
                //qDebug()<<currRoadNo;
                //qDebug()<<currRoad;
                if(lastRoadNo<12){//水平路线
                    point.setY(this->mapRoads[lastRoadNo].y1());
                    inc = (mapRoads[lastRoadNo].x2()-mapRoads[lastRoadNo].x1())/(currRoad.length()-1);
                    if(0 == lastRoadNo){
                        for(int i=0; i<currRoad.length(); i++){
                            point.setX(150+30*i);
                            point.setY(150-30*i);
                            // qDebug()<<point;
                            //qDebug()<<readBuf;
                            mapHashSet.insert(currRoad[i].toLongLong(0, 0), point);

                        }

                    }else if(1 == lastRoadNo){
                     //   qDebug()<<lastRoadNo;
                        for(int i=0; i<currRoad.length(); i++){
                            point.setX(180+30*i);
                            point.setY(180-30*i);
                           // qDebug()<<point;

                            mapHashSet.insert(currRoad[i].toLongLong(0, 0), point);
                        }

                    }else if(0 == (lastRoadNo+1)%2){//L-->R
                        for(int i=0; i<currRoad.length(); i++){
                            point.setX(mapRoads[lastRoadNo].x1()+i*inc);
                            mapHashSet.insert(currRoad[i].toLongLong(0, 0), point);

                      //      qDebug()<<point;
                        }
                    } else if(1 == (lastRoadNo+1)%2){//R-->L
                        for(int i=0; i<currRoad.length(); i++){
                            point.setX(mapRoads[lastRoadNo].x1()+i*inc);
                            mapHashSet.insert(currRoad[i].toLongLong(0, 0), point);
                       //      qDebug()<<point;
                        }
                    }
                } else {//垂直路线

                    if(20 == lastRoadNo ){
                    //    qDebug()<<lastRoadNo;
                        for(int i=0; i<currRoad.length(); i++){
                            point.setX(130-30*i);
                            point.setY(180+30*i);

                            mapHashSet.insert(currRoad[i].toLongLong(0, 0), point);
                         //   qDebug()<<point;
                            }

                    }else if(21 == lastRoadNo){
                      //  qDebug()<<lastRoadNo;
                        for(int i=0; i<currRoad.length(); i++){
                            point.setX(170-30*i);
                            point.setY(150+30*i);

                            mapHashSet.insert(currRoad[i].toLongLong(0, 0), point);
                        //    qDebug()<<point;

                        }


                    }else {
                      // qDebug()<<lastRoadNo;
                        point.setX(this->mapRoads[lastRoadNo].x1());
                        inc = (mapRoads[lastRoadNo].y2()-mapRoads[lastRoadNo].y1())/(currRoad.length()-1);

                        if(0 == (lastRoadNo+1)%2){//DOWN-->UP
                            for(int i=0; i<currRoad.length(); i++){
                                point.setY(mapRoads[lastRoadNo].y1()+i*inc);
                                mapHashSet.insert(currRoad[i].toLongLong(0, 0), point);
                                if (24 == lastRoadNo+1 ){
                                    qDebug()<<point;
                                }

                            }
                        } else if(1 == (lastRoadNo+1)%2){//UP-->DOWN
                            for(int i=0; i<currRoad.length(); i++){
                                point.setY(mapRoads[lastRoadNo].y1()+i*inc);
                                mapHashSet.insert(currRoad[i].toLongLong(0,0), point);
                              //  qDebug()<<point;
                            }
                        }

                    }
                }

                lastRoadNo = currRoadNo;
                currRoad.clear();

            }

        }

            else {//读到卡号，添加到当前路
            if(currRoadNo==lastRoadNo){
                currRoad.append(readBuf);
            }

        }
    }

    cardInfo.close();

    return  true;
}


bool singleMap::createRoads()
{
    if(0 == scale){
          return false;
      }
      //初始化路线
     // this->mapRoads[0].setLine(158*scale, 8*scale, 174*scale, 8*scale);
      //this->mapRoads[1].setLine(88*scale, 8*scale, 128*scale, 8*scale);

      this->mapRoads[2].setLine(370*scale, 70*scale, 590*scale, 70*scale);
      this->mapRoads[3].setLine(370*scale, 100*scale, 590*scale, 100*scale);

      this->mapRoads[4].setLine(105*scale, 335*scale, 315*scale, 335*scale);
      this->mapRoads[5].setLine(105*scale, 365*scale, 315*scale, 365*scale);

      this->mapRoads[6].setLine(370*scale, 335*scale, 590*scale, 335*scale);
      this->mapRoads[7].setLine(370*scale, 365*scale, 590*scale, 365*scale);

      this->mapRoads[8].setLine(105*scale, 610*scale, 315*scale, 610*scale);
      this->mapRoads[9].setLine(105*scale, 640*scale, 315*scale, 640*scale);

      this->mapRoads[10].setLine(370*scale, 610*scale, 590*scale, 610*scale);
      this->mapRoads[11].setLine(370*scale, 640*scale, 590*scale, 640*scale);

      this->mapRoads[12].setLine(635*scale, 110*scale, 635*scale, 320*scale);
      this->mapRoads[13].setLine(605*scale, 110*scale, 605*scale, 320*scale);

      this->mapRoads[14].setLine(635*scale, 380*scale, 635*scale, 600*scale);
      this->mapRoads[15].setLine(605*scale, 380*scale, 605*scale, 600*scale);

      this->mapRoads[16].setLine(360*scale, 110*scale, 360*scale, 325*scale);
      this->mapRoads[17].setLine(330*scale, 110*scale, 330*scale, 325*scale);

      this->mapRoads[18].setLine(360*scale, 380*scale, 360*scale, 600*scale);
      this->mapRoads[19].setLine(330*scale, 380*scale, 330*scale, 600*scale);

     // this->mapRoads[21].setLine(16*scale, 30*scale, 16*scale, 50*scale);
    //  this->mapRoads[20].setLine(16*scale, 85*scale, 16*scale, 171*scale);

      this->mapRoads[22].setLine(90*scale, 380*scale, 90*scale, 600*scale);
      this->mapRoads[23].setLine(60*scale, 380*scale, 60*scale, 600*scale);

      return true;

}

QHash<qlonglong, QPoint>*   singleMap::getMapHashSet()
{
    if(!mapHashSet.isEmpty())
        return &mapHashSet;
    else
        return  NULL;

}

QLine*  singleMap::getMapRoads()
{
    return mapRoads;
}

QPixmap singleMap::getBackground()
{
    return this->mapBackground;
}
