#include "postprocwindow.h"

PostProcWindow::PostProcWindow(QVector<Rod> rods, QVector<QVector<float> > matrixU, QVector<QVector<float> > matrixN, QWidget *parent) :
    QWidget(parent)
{

    layoutG = new QGridLayout();

    this->rods=rods;
    this->matrixN=matrixN;
    this->matrixU=matrixU;

    tableOfAllCalcs = new QTableWidget(matrixU.size(),3,this);
    QTableWidgetItem* itemParamHor1 = new QTableWidgetItem("Ux стержня");
    tableOfAllCalcs->setHorizontalHeaderItem(0,itemParamHor1);
    QTableWidgetItem* itemParamHor2 = new QTableWidgetItem("Sx стержня");
    tableOfAllCalcs->setHorizontalHeaderItem(1,itemParamHor2);
    QTableWidgetItem* itemParamHor3 = new QTableWidgetItem("Nx стержня");
    tableOfAllCalcs->setHorizontalHeaderItem(2,itemParamHor3);
    (tableOfAllCalcs->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
    (tableOfAllCalcs->horizontalHeader())->setMinimumSectionSize(50);

    fillTable();

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

void PostProcWindow::fillTable()
{
    for(int i=0;i<tableOfAllCalcs->rowCount();i++)
    {
        QString str = "";
        str.setNum(funcUx(matrixU[i],0));
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(str);
        tableOfAllCalcs->setItem(i,0,item1);

        str = "";
        str.setNum(funcUx(matrixU[i],0)/(rods[i].height));
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(str);
        tableOfAllCalcs->setItem(i,1,item2);

        str = "";
        str.setNum(funcNx(matrixN[i],0));
        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText(str);
        tableOfAllCalcs->setItem(i,2,item3);
    }
}

void PostProcWindow::backToMenu()
{

}
