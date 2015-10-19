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
    heightMy=height()/2;
    if(rods.size()>0)
    {
        float koeffW = width()/(1.08*findUserWidth(rods));
        float koeffH=heightMy/(1.3*findMaxHeight(rods));

        QRect borders(0, 0, width()-1, height()-1);
        QColor gridColor = "#000";
        //gridColor.setAlpha(10);
        p.setPen(gridColor);
    //    for(double k = 10; k <= width(); k += 10)
    //        p.drawLine(k, 0, k, height());
    //    for(double k = 10; k <= height(); k += 10)
    //        p.drawLine(0, k, width(), k);

//        //Отрисовка левой заделки:
//        p.drawLine(20, 3*heightMy/4, 20, heightMy/4);
//        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
//            p.drawLine(10, k-10, 20, k);
        //drawWall(p,20);

        float X=20;
        //Отрисовка стержней:
        for(int k = 0; k <rods.size() ; k++)
        {
            float hRod=rods[k].height*koeffH;
            float wRod=(rods[k].len)*koeffW;
            //qDebug()<<k<<" : "<<width()<<" : "<<height()<<" : "<<hRod<<" : "<<wRod;
            QString str;
            str.setNum(k+1);
            p.drawRect(X, heightMy/2 - hRod/2, wRod,  hRod);
            p.drawText(X, 20,str);
            rods[k].coord=X;
            X+=wRod;
        }

        //Отрисовка правой заделки:
        p.drawText(X, 20,(new QString())->QString::setNum(rods.size()+1));
//        p.drawLine(X, 3*heightMy/4, X, heightMy/4);
//        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
//            p.drawLine(X+10, k-10, X, k);
        //drawWall(p,X);

        //Отрисовка нагрузок
        paintLoads(p,koeffH,koeffW);

        p.drawRect(borders);
    }

}


void Construction::paintLoads(QPainter &p, float koeffH, float koeffW)
{
    for(int k = 0; k <loads.size() ; k++)
    {
        //Отрисовка сосредоточенной нагрузки
        if(loads[k].firstNode==loads[k].secNode)
        {
            float X=0;
            float hRod=0;
            float wRod=0;
            if(loads[k].firstNode-1<rods.size() || rods.size()<2)
            {
                X=rods[loads[k].firstNode-1].coord;
                hRod=rods[loads[k].firstNode-1].height*koeffH;
            }
            else
            {
                X=rods[loads[k].firstNode-2].coord;
                hRod=rods[loads[k].firstNode-2].height*koeffH;
                wRod=rods[loads[k].firstNode-2].len*koeffW;
            }
            if(loads[k].F1>0)
                drawArrow(p,X+wRod,heightMy/2,X+wRod+40,heightMy/2,10);
            if(loads[k].F1<0)
                drawArrow(p,X+wRod,heightMy/2,X+wRod-40,heightMy/2,10);
            if(loads[k].F2<0)
                drawArrow(p,X+wRod,heightMy/2-hRod/2-40,X+wRod,heightMy/2-hRod/2,10);
            if(loads[k].F2>0)
                drawArrow(p,X+wRod,heightMy/2+hRod/2+40,X+wRod,heightMy/2+hRod/2,10);
            //Отрисовка заделки в узле
            if(loads[k].wall!=0)
            {
                if(loads[k].firstNode>rods.size())
                    drawWall(p,X+wRod);
                if(loads[k].firstNode<=rods.size())
                    drawWall(p,X);
            }
        }
        //Отрисовка распределенной нагрузки
        if(loads[k].firstNode!=loads[k].secNode)
        {
            float X=rods[loads[k].firstNode-1].coord;
            float wRod=rods[loads[k].firstNode-1].len*koeffW;
            float hRod=rods[loads[k].firstNode-1].height*koeffH;
            if(loads[k].F1>0)
            {
                for(float i=X;i<X+wRod;i+=wRod/10)
                    drawArrow(p,i,heightMy/2,i+wRod/10,heightMy/2,5);
            }
            if(loads[k].F1<0)
            {
                for(float i=X;i<X+wRod;i+=wRod/10)
                    drawArrow(p,i+wRod/10,heightMy/2,i,heightMy/2,5);
            }
            if(loads[k].F2<0)
            {
                p.drawLine(X, heightMy/2-hRod/2-40, X+wRod, heightMy/2-hRod/2-40);
                for(float i=X;i<X+wRod;i+=wRod/10)
                    drawArrow(p,i,heightMy/2-hRod/2-40,i,heightMy/2-hRod/2,4);
            }
            if(loads[k].F2>0)
            {
                p.drawLine(X, heightMy/2+hRod/2+40, X+wRod, heightMy/2+hRod/2+40);
                for(float i=X;i<X+wRod;i+=wRod/10)
                    drawArrow(p,i,heightMy/2+hRod/2+40,i,heightMy/2+hRod/2,4);
            }
        }
    }
}

void Construction::drawArrow(QPainter &p, float x1, float y1, float x2, float y2,float h)
{
    if(y2==y1)
    {
        QPointF points[7] = {
            QPointF(x1, y1+h/2),
            QPointF(x1+(x2-x1)*2/3, y1+h/2),
            QPointF(x1+(x2-x1)*2/3, y1+h),
            QPointF(x2, y1),
             QPointF(x1+(x2-x1)*2/3, y1-h),
             QPointF(x1+(x2-x1)*2/3, y1-h/2),
             QPointF(x1, y1-h/2),
         };
        p.drawPolygon(points, 7);
    }
    else
        if(x1==x2)
        {
            QPointF points[7] = {
                QPointF(x1-h/2, y1),
                QPointF(x1-h/2, y1+(y2-y1)*2/3),
                QPointF(x1-h, y1+(y2-y1)*2/3),
                QPointF(x1, y2),
                 QPointF(x1+h, y1+(y2-y1)*2/3),
                 QPointF(x1+h/2, y1+(y2-y1)*2/3),
                 QPointF(x1+h/2, y1),
             };
            p.drawPolygon(points, 7);
        }
}

void Construction::drawWall(QPainter &p, float x)
{
    if(x==20)
    {
        p.drawLine(x, 3*heightMy/4, x, heightMy/4);
        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
            p.drawLine(x-10, k-10, x, k);
    }
    if(width()-x<=20)
    {
        p.drawLine(x, 3*heightMy/4, x, heightMy/4);
        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
            p.drawLine(x, k-10, x+10, k);
    }
    if(width()-x>=20 && x>20)
    {
        p.drawLine(x, 3*heightMy/4, x, heightMy/4);
        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
            p.drawLine(x-5, k-10, x+5, k);
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

void Construction::changeMapLoads(QVector<float> set)
{
    Load load(set[0],set[1],set[2],set[3],set[4]);
    loads.push_back(load);
    update();
}


void Construction::clearMapRods()
{
    rods.clear();
}

void Construction::clearMapLoads()
{
    loads.clear();
}


//Находим наибольшую высоту среди стержней
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

//Суммируем все длины стержней, чтобы получить общую пользовательскую ширину
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
