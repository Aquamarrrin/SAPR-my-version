#include "graphicwindow.h"
#include <QDebug>

GraphicWindow::GraphicWindow(int type, float maxX, QVector<float> vecF, QWidget *parent) :
    QWidget(parent)
{
    layoutG= new QGridLayout();

    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(0,0,this->width()-5,this->height()-5,view);

    QPen pen(Qt::black);
    QColor gridColor = "#000";
    scene->addLine(0,scene->width()/2,scene->width(),scene->width()/2,pen);//x
    scene->addLine(0,0,0,scene->width(),pen);//y

    gridColor.setAlpha(50);
    pen.setColor(gridColor);
    scene->addText("Ux");//setPos(0, height());
    for(double k = 0; k <= scene->width(); k += 20)
        scene->addLine(k, 0, k, scene->width(),pen);
    //scene->addText("x");
    //->setPos(width(), 0);
    for(double k = 0; k <= scene->width(); k += 20)
        scene->addLine(0, k, scene->width(), k,pen);
    gridColor.setAlpha(255);
    pen.setColor(gridColor);

    int countOfCells=scene->width()/20;

    for(double k = 0; k <= scene->width(); k += 40)
    {
        QString str;
        float num=(k/20)*(maxX/countOfCells);
        num*=100;
        num=(int)num;
        num/=100;
        str.setNum(num);
        scene->addText(str)->setPos(k-10,scene->width()/2-5);//x

//        num=funcUx(vecF,((k-scene->width()/2)/20)*((maxX/countOfCells)));

        num=((k-scene->width()/2)/20)*(maxX/countOfCells);
        num*=100;
        num=(int)num;
        num/=100;
        str.setNum(num);
        scene->addText(str)->setPos(0,scene->width()-k-5);//y
    }

    if(type==1)
    {
        scene->addText("Ux")->setPos(0,0);//setPos(0, height());
        scene->addText("X")->setPos(scene->width()-10,scene->width()/2);
        gridColor = "#F00";
        pen.setColor(gridColor);
        for(double k = 20; k <= scene->width(); k += 20)
        {
            float num1=(scene->width()/maxX)*funcUx(vecF,((k-20)/20)*((maxX/countOfCells)));
            qDebug()<<"NUM1"<<funcUx(vecF,((k-20-scene->width()/2)/20)*((maxX/countOfCells)));
            float num2=(scene->width()/maxX)*funcUx(vecF,(k/20)*((maxX/countOfCells)));
            num1=(int)100*num1;
            num1/=100;
            num2=(int)100*num2;
            num2/=100;
            scene->addLine(k-20, scene->width()/2-num1, k, scene->width()/2-num2,pen);
            //qDebug()<<"X1="<<k-20<<"Y1="<<scene->width()/2-funcUx(vecF,(k-20)/200)*kof<<"K="<<(k-20)/200<<"FUNC="<<funcUx(vecF,(k-20)/200);
        }
    }

    if(type==2)
    {
        scene->addText("Nx")->setPos(0,0);//setPos(0, height());
        scene->addText("X")->setPos(scene->width()-10,scene->width()/2);
        gridColor = "#F00";
        pen.setColor(gridColor);
        for(double k = 20; k <= scene->width(); k += 20)
        {
            float num1=(scene->width()/maxX)*funcNx(vecF,((k-20)/20)*((maxX/countOfCells)));
            qDebug()<<"NUM1"<<funcUx(vecF,((k-20-scene->width()/2)/20)*((maxX/countOfCells)));
            float num2=(scene->width()/maxX)*funcNx(vecF,(k/20)*((maxX/countOfCells)));
            num1=(int)100*num1;
            num1/=100;
            num2=(int)100*num2;
            num2/=100;
            scene->addLine(k-20, scene->width()/2-num1, k, scene->width()/2-num2,pen);
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
