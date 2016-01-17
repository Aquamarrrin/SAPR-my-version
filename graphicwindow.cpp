#include "graphicwindow.h"
#include <QDebug>

GraphicWindow::GraphicWindow(int type, float maxX, QVector<float> vecF, QWidget *parent) :
    QWidget(parent)
{
    layoutG= new QGridLayout();

    QGraphicsView *view = new QGraphicsView();
    view->setFixedSize(700,690);
    QGraphicsScene *scene = new QGraphicsScene(0,0,680,680,view);

    QPen pen(Qt::black);
    QColor gridColor = "#000";
    scene->addLine(0,scene->width()/2,scene->width(),scene->width()/2,pen);//x
    scene->addLine(0,0,0,scene->width(),pen);//y

    gridColor.setAlpha(50);
    pen.setColor(gridColor);
    //scene->addText("Ux");//setPos(0, height());
    for(double k = 0; k <= scene->width(); k += 20)
        scene->addLine(k, 0, k, scene->height(),pen);
    //scene->addText("x");
    //->setPos(width(), 0);
    for(double k = 0; k <= scene->height(); k += 20)
        scene->addLine(0, k, scene->width(), k,pen);
    gridColor.setAlpha(255);
    pen.setColor(gridColor);

    int countOfCellsX=scene->width()/5;
    int countOfCellsY=scene->height()/5;


    if(type==1)
    {
        float maxF=0;
        for(double k = 0; k <= scene->width(); k += 40)
        {
            QString str;
            float num=(k/5)*(maxX/countOfCellsX);
            num*=100;
            num=(int)num;
            num/=100;
            str.setNum(num);
            scene->addText(str)->setPos(k-10,scene->height()/2-5);//x

            if(fabs(funcUx(vecF,(k/5)*((maxX/countOfCellsX))))>maxF)
                    maxF=fabs(funcUx(vecF,(k/5)*((maxX/countOfCellsX))));
            //qDebug()<<"FABS::"<<fabs(funcUx(vecF,((k)/20)*((maxX/countOfCellsX))))<<"MAX::  "<<maxF;

        }
        maxF*=2;
        maxF=maxF+maxF*0.1;
        for(double k = 0; k <= scene->width(); k += 40)
        {
            QString str;
            float num;

            num=((k-scene->height()/2)/5)*(maxF/countOfCellsY);
            str.setNum(num);
            scene->addText(str)->setPos(0,scene->height()-k-5);//y
        }
        scene->addText("Ux")->setPos(20,0);//setPos(0, height());
        scene->addText("X")->setPos(scene->width()-10,scene->width()/2-20);
        gridColor = "#F00";
        pen.setColor(gridColor);
        for(double k = 5; k <= scene->width(); k += 5)
        {
            float num1=(scene->height()/maxF)*funcUx(vecF,((k-5)/5)*((maxX/countOfCellsX)));
            //qDebug()<<"NUM1"<<funcUx(vecF,((k-20-scene->width()/2)/20)*((maxX/countOfCellsX)));
            float num2=(scene->height()/maxF)*funcUx(vecF,(k/5)*((maxX/countOfCellsX)));
            scene->addLine(k-5, scene->height()/2-num1, k, scene->height()/2-num2,pen);
            //qDebug()<<"X1="<<k-20<<"Y1="<<scene->width()/2-funcUx(vecF,(k-20)/200)*kof<<"K="<<(k-20)/200<<"FUNC="<<funcUx(vecF,(k-20)/200);
        }
    }

    if(type==2)
    {
        float maxF=0;
        for(double k = 0; k <= scene->width(); k += 40)
        {
            QString str;
            float num=(k/5)*(maxX/countOfCellsX);
            num*=100;
            num=(int)num;
            num/=100;
            str.setNum(num);
            scene->addText(str)->setPos(k-10,scene->height()/2-5);//x

            if(fabs(funcNx(vecF,(k/5)*((maxX/countOfCellsX))))>maxF)
                    maxF=fabs(funcNx(vecF,(k/5)*((maxX/countOfCellsX))));
            //qDebug()<<"FABS::"<<fabs(funcNx(vecF,((k)/20)*((maxX/countOfCellsX))))<<"MAX::  "<<maxF;

        }
        maxF*=2;
        maxF=maxF+maxF*0.1;
        for(double k = 0; k <= scene->width(); k += 40)
        {
            QString str;
            float num;

            num=((k-scene->height()/2)/5)*(maxF/countOfCellsY);
            str.setNum(num);
            scene->addText(str)->setPos(0,scene->height()-k-5);//y
        }

        scene->addText("Nx")->setPos(20,0);//setPos(0, height());
        scene->addText("X")->setPos(scene->width()-10,scene->width()/2-20);
        gridColor = "#F00";
        pen.setColor(gridColor);
        for(double k = 5; k <= scene->width(); k += 5)
        {
            float num1=(scene->height()/maxF)*funcNx(vecF,((k-5)/5)*((maxX/countOfCellsX)));
            //qDebug()<<"NUM1"<<funcUx(vecF,((k-20-scene->width()/2)/20)*((maxX/countOfCellsX)));
            float num2=(scene->height()/maxF)*funcNx(vecF,(k/5)*((maxX/countOfCellsX)));
            scene->addLine(k-5, scene->height()/2-num1, k, scene->height()/2-num2,pen);
            //qDebug()<<"X1="<<k-20<<"Y1="<<scene->width()/2-funcUx(vecF,(k-20)/200)*kof<<"K="<<(k-20)/200<<"FUNC="<<funcUx(vecF,(k-20)/200);
        }
    }

    if(type==3)
    {
        float maxF=0;
        for(double k = 0; k <= scene->width(); k += 40)
        {
            QString str;
            float num=(k/5)*(maxX/countOfCellsX);
            num*=100;
            num=(int)num;
            num/=100;
            str.setNum(num);
            scene->addText(str)->setPos(k-10,scene->height()/2-5);//x

            if(fabs(funcNx(vecF,(k/5)*((maxX/countOfCellsX))))>maxF)
                    maxF=fabs(funcNx(vecF,(k/5)*((maxX/countOfCellsX))));
            //qDebug()<<"FABS::"<<fabs(funcUx(vecF,((k)/20)*((maxX/countOfCellsX))))<<"MAX::  "<<maxF;

        }
        maxF*=2;
        maxF=maxF+maxF*0.1;
        for(double k = 0; k <= scene->width(); k += 40)
        {
            QString str;
            float num;

            num=((k-scene->height()/2)/5)*(maxF/countOfCellsY);
            str.setNum(num);
            scene->addText(str)->setPos(0,scene->height()-k-5);//y
        }
        scene->addText("σx")->setPos(20,0);//setPos(0, height());
        scene->addText("X")->setPos(scene->width()-10,scene->width()/2-20);
        gridColor = "#F00";
        pen.setColor(gridColor);
        for(double k = 5; k <= scene->width(); k += 5)
        {
            float num1=(scene->height()/maxF)*funcNx(vecF,((k-5)/5)*((maxX/countOfCellsX)));
            float num2=(scene->height()/maxF)*funcNx(vecF,(k/5)*((maxX/countOfCellsX)));
            scene->addLine(k-5, scene->height()/2-num1, k, scene->height()/2-num2,pen);
            //qDebug()<<"X1="<<k-20<<"Y1="<<scene->width()/2-funcUx(vecF,(k-20)/200)*kof<<"K="<<(k-20)/200<<"FUNC="<<funcUx(vecF,(k-20)/200);
        }
    }

    view->setScene(scene);

    layoutG->addWidget(view);
    this->setLayout(layoutG);
}

float GraphicWindow::funcUx(QVector<float> vecU, float x)
{
    float result=0;

    if(vecU.size()==4)
        result=vecU[0]+x*vecU[1]+x*vecU[2]*(1-x*vecU[3]);

    //qDebug()<<vecU[0]<<vecU[1]<<vecU[2]<<vecU[3]<<"RESULT = "<<result;
    return result;
}

float GraphicWindow::funcNx(QVector<float> vecN, float x)
{
    float result=0;

    if(vecN.size()==3)
        result=vecN[0]+vecN[1]*(1-x*vecN[2]);

    return result;
}
