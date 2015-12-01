#include "graphicwindow.h"
#include <QDebug>

GraphicWindow::GraphicWindow(int type, float maxX, QVector<float> vecF, QWidget *parent) :
    QWidget(parent)
{
    layoutG= new QGridLayout();

    QGraphicsView *view = new QGraphicsView();
    QGraphicsScene *scene = new QGraphicsScene(view);

    QPen pen(Qt::black);
    QColor gridColor = "#000";
    scene->addLine(0,view->width()/2,view->width(),view->width()/2,pen);//x
    scene->addLine(0,0,0,view->width(),pen);//y

    gridColor.setAlpha(50);
    pen.setColor(gridColor);
    scene->addText("Ux");//setPos(0, height());
    for(double k = 20; k <= view->width(); k += 20)
        scene->addLine(k, 0, k, view->width(),pen);
    //scene->addText("x");
    //->setPos(width(), 0);
    for(double k = 10; k <= view->width(); k += 10)
        scene->addLine(0, k, view->width(), k,pen);
    gridColor.setAlpha(255);
    pen.setColor(gridColor);

    if(type==1)
    {
        scene->addText("Ux")->setPos(0,0);//setPos(0, height());
        float kof =(view->width()/funcUx(vecF,view->width()))*100;
        for(double k = 20; k <= view->width(); k += 20)
        {
            QString str;
            str.setNum((k)/200);
            scene->addText(str)->setPos(k-10,view->width()/2-5);//setPos(0, height());
            if((int)k%40==0)
            {
                str.setNum(funcUx(vecF,(k-20)/200));
                scene->addText(str)->setPos(0,view->width()/2-funcUx(vecF,(k-20)/200)*kof-5);//setPos(0, height());
            }
            scene->addLine(k-20, view->width()/2-funcUx(vecF,(k-20)/200)*kof, k, view->width()/2-funcUx(vecF,k/200)*kof,pen);
            qDebug()<<"X1="<<k-20<<"Y1="<<view->width()/2-funcUx(vecF,(k-20)/200)*kof<<"K="<<(k-20)/200<<"FUNC="<<funcUx(vecF,(k-20)/200);
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
