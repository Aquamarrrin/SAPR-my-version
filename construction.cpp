#include "construction.h"
#include <QDebug>

Construction::Construction(QWidget *parent) :
    QWidget(parent),
    timer(new QTimer(this))
{
    //timer->setInterval(50);
    clearMapRods();
}

void Construction::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintConstruction(p);
}

void Construction::paintConstruction(QPainter &p)
{
    if(rods.size()>0)
    {
        float koeffW = width()/(1.2*findUserWidth(rods));
        float koeffH=height()/(1.2*findMaxHeight(rods));

        QRect borders(0, 0, width()-1, height()-1);
        QColor gridColor = "#000";
        //gridColor.setAlpha(10);
        p.setPen(gridColor);
    //    for(double k = 10; k <= width(); k += 10)
    //        p.drawLine(k, 0, k, height());
    //    for(double k = 10; k <= height(); k += 10)
    //        p.drawLine(0, k, width(), k);

        //Отрисовка левой заделки:
        p.drawLine(20, 3*height()/4, 20, height()/4);
        for(double k = 3*height()/4; k >= height()/4; k -= 10)
            p.drawLine(10, k-10, 20, k);

        //Отрисовка стержней:
//        for(double k = 1; k <nodes.size() ; k++)
//        {
//            QString str;
//            QPoint point;
//            point.setX(k);
//            point.setY(k+1);

//            float hRod=settings[rods.key(point)][0]*koeffH;

//            str.setNum(k);
//            if(k==1)
//            {
//                p.drawRect((nodes[k]-nodes[1])*koeff+20, height()/2 - hRod/2, (nodes[k+1]-nodes[1])*koeff-((nodes[k]-nodes[1])*koeff+20),  hRod);
//                p.drawText((nodes[k]-nodes[1])*koeff+20, height()/2-20 - hRod/2,str);
//            }
//            else
//                if(k==nodes.size()-1)
//                {
//                    p.drawRect((nodes[k]-nodes[1])*koeff, height()/2 - hRod/2, (nodes[k+1]-nodes[1])*koeff-20-((nodes[k]-nodes[1])*koeff), hRod);
//                    p.drawText((nodes[k]-nodes[1])*koeff, height()/2-20 - hRod/2,str);
//                }
//                else
//                {
//                    p.drawText((nodes[k]-nodes[1])*koeff, height()/2-20 - hRod/2,str);
//                    p.drawRect((nodes[k]-nodes[1])*koeff, height()/2-hRod/2, (nodes[k+1]-nodes[1])*koeff-((nodes[k]-nodes[1])*koeff), hRod);
//                }
//        }

        float X=20;
        //Отрисовка стержней:
        for(double k = 0; k <rods.size() ; k++)
        {
            float hRod=rods[k].height*koeffH;
            float wRod=(rods[k].len)*koeffW;
            qDebug()<<k<<" : "<<width()<<" : "<<height()<<" : "<<hRod<<" : "<<wRod;
            QString str;
            str.setNum(k+1);
            p.drawRect(X, height()/2 - hRod/2, wRod,  hRod);
            p.drawText(X, height()/2-20 - hRod/2,str);
            X+=wRod;
        }


        //Отрисовка правой заделки:
        p.drawText(X, height()/4-20,(new QString())->QString::setNum(rods.size()));
        p.drawLine(X, 3*height()/4, X, height()/4);
        for(double k = 3*height()/4; k >= height()/4; k -= 10)
            p.drawLine(X+10, k-10, X, k);

        p.drawRect(borders);
    }

}


void Construction::changeMapRods(int numOfRod, QVector<float> set)
{
    Rod rod;
    rod.firstNod=numOfRod;
    rod.secondNod=numOfRod+1;
    rod.len=set[1];
    rod.height=set[0];
    rod.A=set[2];
    rod.B=set[3];
    rod.E=set[4];
    rods.push_back(rod);
    update();
}


void Construction::clearMapRods()
{
    qDebug()<<rods.size();
    rods.clear();
    qDebug()<<rods.size();
}


float Construction::findMaxHeight(QVector<Rod> set)
{
    float max=0;
    for(int i=0;i<set.size();i++)
    {
        if(set[i].height>max)
            max=set[i].height;
    }
    return max;
}

float Construction::findUserWidth(QVector<Rod> set)
{
    float wid=0;
    for(int i=0;i<set.size();i++)
    {
        wid=wid+set[i].len;
    }
    return wid;
}

Construction::~Construction()
{

}
