#include "postprocwindow.h"

PostProcWindow::PostProcWindow(QVector<QVector<float> > matrixU,QVector<QVector<float> > matrixN, QWidget *parent) :
    QWidget(parent)
{

    layoutG = new QGridLayout();

    tableOfAllCalcs = new QTableWidget(matrixU.size(),3,this);
    QTableWidgetItem* itemParamHor1 = new QTableWidgetItem("Ux стержня");
    tableOfAllCalcs->setHorizontalHeaderItem(0,itemParamHor1);
    QTableWidgetItem* itemParamHor2 = new QTableWidgetItem("Sx стержня");
    tableOfAllCalcs->setHorizontalHeaderItem(1,itemParamHor2);
    QTableWidgetItem* itemParamHor3 = new QTableWidgetItem("Nx стержня");
    tableOfAllCalcs->setHorizontalHeaderItem(2,itemParamHor3);
    (tableOfAllCalcs->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
    (tableOfAllCalcs->horizontalHeader())->setMinimumSectionSize(50);

    layoutG->addWidget(tableOfAllCalcs);

    this->setLayout(layoutG);
}

float PostProcWindow::funcUx(QVector<float> vecU, float x)
{
    float result=0;

    if(vecU.size()==4)
        result=vecU[0]+x*vecU[1]+x*vecU[2]*(1-x*vecU[3]);

    return result;
}

float PostProcWindow::funcNx(QVector<float> vecN, float x)
{
    float result=0;

    if(vecN.size()==3)
        result=vecN[0]+vecN[1]*(1-x*vecN[2]);

    return result;
}
