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
        float koeffW = width()/(1.07*findUserWidth(rods));
        float koeffH=heightMy/(1.5*findMaxHeight(rods));

        QRect borders(0, 0, width()-1, height()-1);
        QColor gridColor = "#000";

        //Отрисовка сетки поля
        gridColor.setAlpha(10);
        p.setPen(gridColor);
        for(double k = 20; k <= width(); k += 20)
            p.drawLine(k, 0, k, height());
        for(double k = 20; k <= height(); k += 20)
            p.drawLine(0, k, width(), k);
        gridColor.setAlpha(255);
        p.setPen(gridColor);


        float X=20;
        //Отрисовка стержней:
        for(int k = 0; k <rods.size() ; k++)
        {
            float hRod=rods[k].height*koeffH;
            float wRod=(rods[k].len)*koeffW;
            QString str;
            QString str1;

            //Отрисовка стержня
            str.setNum(k+1);
            p.drawRect(X, heightMy/2 - hRod/2, wRod,  hRod);
            p.drawText(X, 20,str);

            //Отрисовка пунктирных прямых
            p.setPen(Qt::DashLine);
            p.drawLine(X, heightMy/2 + hRod/2,X,height());
            p.setPen(Qt::SolidLine);

            //Отрисовка надписей под стержнем
            str=str.setNum(rods[k].E);
            str="E="+str;
            p.drawText(X+5, heightMy/2 + hRod/2+30,str);
            str1=str1.setNum(rods[k].height);
            str1="A="+str1;
            p.drawText(X+5, heightMy/2 + hRod/2+45,str1);


            //Отрисовка надписей над стержнем
            str=str.setNum(rods[k].len);
            str="L="+str;
            p.drawText(X+wRod/3, heightMy/2 - hRod/2-10,str);

            rods[k].coord=X;
            X+=wRod;
        }

        p.drawText(X, 20,(new QString())->QString::setNum(rods.size()+1));
        p.setPen(Qt::DashLine);
        p.drawLine(X, heightMy/2,X,height());
        p.setPen(Qt::SolidLine);

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
        if(loads[k].firstNode>0 && loads[k].firstNode<=rods.size()+1)
        {
            float X=0;
            float hRod=0;
            float wRod=0;
            if(loads[k].firstNode-1<rods.size() || rods.size()<2)
            {
                if(rods.size()<=1 && loads[k].firstNode>1)
                {
                    X=rods[0].coord;
                    hRod=rods[0].height*koeffH;
                    wRod=rods[0].len*koeffW;
                }
                else
                {
                    X=rods[loads[k].firstNode-1].coord;
                    hRod=rods[loads[k].firstNode-1].height*koeffH;
                    wRod=rods[loads[k].firstNode-1].len*koeffW;
                }
            }
            else
            {
                X=rods[loads[k].firstNode-2].coord;
                hRod=rods[loads[k].firstNode-2].height*koeffH;
                wRod=rods[loads[k].firstNode-2].len*koeffW;
            }

            p.setBrush(Qt::SolidPattern);

            QString str;
            if(loads[k].firstNode-1<rods.size())
            {
                if(loads[k].F1>0)
                {
                    drawArrow(p,X,heightMy/2,X+20,heightMy/2,10);
                    p.drawText(X, heightMy/2 +15,"F="+str.setNum(loads[k].F1));
                }
                if(loads[k].F1<0)
                {
                    drawArrow(p,X,heightMy/2,X-20,heightMy/2,10);
                    p.drawText(X-20, heightMy/2 +15,"F="+str.setNum(loads[k].F1));
                }
            }
            else
            {
                if(loads[k].F1>0)
                {
                    drawArrow(p,X+wRod,heightMy/2,X+wRod+20,heightMy/2,10);
                    p.drawText(X+wRod, heightMy/2 +15,"F="+str.setNum(loads[k].F1));
                }
                if(loads[k].F1<0)
                {
                    drawArrow(p,X+wRod,heightMy/2,X+wRod-20,heightMy/2,10);
                    p.drawText(X+wRod-20, heightMy/2 +15,"F="+str.setNum(loads[k].F1));
                }
            }
            p.setBrush(Qt::NoBrush);

            //Отрисовка заделки в узле
            if(loads[k].wall!=0)
            {
                if(loads[k].firstNode>rods.size() || (rods.size()<=1 && loads[k].firstNode>1))
                    drawWall(p,X+wRod);
                if(loads[k].firstNode<=rods.size())
                    drawWall(p,X);
            }
        }

    }
    //Отрисовка распределенной нагрузки
    for(int k=0;k<rods.size();k++)
    {
        if(rods[k].Fx!=0)
        {
            QString str;
            float X=rods[k].coord;
            float wRod=rods[k].len*koeffW;
            if(rods[k].Fx>0)
            {
                for(float i=X;i<X+wRod-wRod/10;i+=wRod/10)
                    drawArrow(p,i,heightMy/2,i+wRod/10,heightMy/2,5);
                drawArrow(p,X+wRod-wRod/10,heightMy/2,X+wRod,heightMy/2,5);
                p.drawText(X+wRod/3, heightMy/2 -15,"q="+str.setNum(rods[k].Fx));
            }
            if(rods[k].Fx<0)
            {
                for(float i=X;i<X+wRod-wRod/10;i+=wRod/10)
                    drawArrow(p,i+wRod/10,heightMy/2,i,heightMy/2,5);
                drawArrow(p,X+wRod,heightMy/2,X+wRod-wRod/10,heightMy/2,5);
                p.drawText(X+wRod/3, heightMy/2 -15,"q="+str.setNum(rods[k].Fx));
            }
        }
    }
}

//Отрисовка стрелок:
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
        p.drawPolygon(points, 7,Qt::OddEvenFill);
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
            p.drawPolygon(points, 7,Qt::OddEvenFill);
        }
}

//Отрисовка заделок:
void Construction::drawWall(QPainter &p, float x)
{
    p.drawLine(x, 3*heightMy/4, x, heightMy/4);
    if(x==20)
    {
        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
            p.drawLine(x-10, k-10, x, k);
    }
    else
    if(width()-x<=40)
    {
        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
            p.drawLine(x, k, x+10, k+10);
    }
    else
    {
        for(double k = 3*heightMy/4; k >= heightMy/4; k -= 10)
            p.drawLine(x-5, k-10, x+5, k);
    }
}

void Construction::changeMapRods(int numOfRod, QVector<float> set)
{
    //Заполняем вектор стержней:
    Rod rod;
    rod.firstNod=numOfRod;
    rod.secondNod=numOfRod+1;
    rod.len=set[1];
    rod.height=set[0];
    rod.E=set[2];
    rod.Fx=set[3];
    rods.push_back(rod);
    update();
}

void Construction::changeMapLoads(QVector<float> set)
{
    //Заполняем вектор нагрузок:
    Load load(set[0],set[1],set[2]);
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
