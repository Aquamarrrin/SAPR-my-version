#include "postprocwindow.h"

PostProcWindow::PostProcWindow(QVector<Rod> rods, QVector<QVector<float> > matrixU, QVector<QVector<float> > matrixN, QWidget *parent) :
    QWidget(parent)
{

    layoutG = new QGridLayout();

    this->rods=rods;
    this->matrixN=matrixN;
    this->matrixU=matrixU;
    X=0;

    QLabel* labelX=new QLabel("Введите Х");
    lineEditX=new QLineEdit();

    QPushButton* btnEnter = new QPushButton("Есть!");
    connect(btnEnter,SIGNAL(clicked()),this,SLOT(setX()));

    QPushButton* btn = new QPushButton("График");
    connect(btn,SIGNAL(clicked()),this,SLOT(paintGraph()));

    spinRod = new QSpinBox();
    spinRod->setMinimum(1);
    spinRod->setMaximum(matrixU.size());

    spinType= new QSpinBox();
    spinType->setMinimum(1);
    spinType->setMaximum(3);

    for(int i=0;i<matrixU.size();i++)
    {
        QTableWidget* tableOfAllCalcs = new QTableWidget(5,4,this);
        tableOfAllCalcs->verticalHeader()->hide();
        QTableWidgetItem* itemParamHor0 = new QTableWidgetItem("x");
        tableOfAllCalcs->setHorizontalHeaderItem(0,itemParamHor0);
        QTableWidgetItem* itemParamHor1 = new QTableWidgetItem("Ux стержня");
        tableOfAllCalcs->setHorizontalHeaderItem(1,itemParamHor1);
        QTableWidgetItem* itemParamHor2 = new QTableWidgetItem("Sx стержня");
        tableOfAllCalcs->setHorizontalHeaderItem(2,itemParamHor2);
        QTableWidgetItem* itemParamHor3 = new QTableWidgetItem("Nx стержня");
        tableOfAllCalcs->setHorizontalHeaderItem(3,itemParamHor3);

        (tableOfAllCalcs->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
        (tableOfAllCalcs->horizontalHeader())->setMinimumSectionSize(50);

        fillTable(tableOfAllCalcs,i);
        tablesOfAllCalcs.push_back(tableOfAllCalcs);
    }

    layoutG->addWidget(labelX,0,0);
    layoutG->addWidget(lineEditX,0,1);
    layoutG->addWidget(btnEnter,0,2);
    layoutG->addWidget(spinRod,1,0);
    layoutG->addWidget(spinType,1,1);
    layoutG->addWidget(btn,1,2);

    int tmpC = 2;
    for(int i=0;i<tablesOfAllCalcs.size();i++){

        QString tmpStr;
        tmpStr.setNum(i+1);
        QLabel* labelNameOfRod=new QLabel(tmpStr+" стержень");
        layoutG->addWidget(labelNameOfRod,i+tmpC,0,1,1);
        layoutG->addWidget(tablesOfAllCalcs[i],i+tmpC+1,0,1,3);
        tmpC++;
    }

    this->setLayout(layoutG);
}

float PostProcWindow::funcUx(QVector<float> vecU, float x)
{
    float result=0;

    if(vecU.size()==4)
        result=vecU[0]+x*vecU[1]+x*vecU[2]*(1-x*vecU[3]);

    //qDebug()<<vecU[0]<<vecU[1]<<vecU[2]<<vecU[3]<<"RESULT = "<<result;
    return result;
}

float PostProcWindow::funcNx(QVector<float> vecN, float x)
{
    float result=0;

    if(vecN.size()==3)
        result=vecN[0]+vecN[1]*(1-x*vecN[2]);

    return result;
}

void PostProcWindow::fillTable(QTableWidget *tableOfAllCalcs, int matInd)
{
    for(int i=0;i<tableOfAllCalcs->rowCount();i++)
    {
        QString str = "";
        str.setNum((float)i/5);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        item0->setText(str);
        tableOfAllCalcs->setItem(i,0,item0);

        str.setNum(funcUx(matrixU[matInd],(float)i/5));
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(str);
        tableOfAllCalcs->setItem(i,1,item1);

        str = "";
        str.setNum(funcUx(matrixU[matInd],(float)i/5)/(rods[matInd].height));
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(str);
        tableOfAllCalcs->setItem(i,2,item2);

        str = "";
        str.setNum(funcNx(matrixN[matInd],(float)i/5));
        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText(str);
        tableOfAllCalcs->setItem(i,3,item3);
    }


}

void PostProcWindow::setX()
{
    this->X=lineEditX->text().toFloat();
    for(int i=0;i<tablesOfAllCalcs.size();i++)
    {
        tablesOfAllCalcs[i]->setRowCount(tablesOfAllCalcs[i]->rowCount()+1);
        QString str = "";
        str.setNum(X);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        item0->setText(str);
        tablesOfAllCalcs[i]->setItem(tablesOfAllCalcs[i]->rowCount()-1,0,item0);

        str.setNum(funcUx(matrixU[i],X));
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(str);
        tablesOfAllCalcs[i]->setItem(tablesOfAllCalcs[i]->rowCount()-1,1,item1);

        str = "";
        str.setNum(funcUx(matrixU[i],X)/(rods[i].height));
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(str);
        tablesOfAllCalcs[i]->setItem(tablesOfAllCalcs[i]->rowCount()-1,2,item2);

        str = "";
        str.setNum(funcNx(matrixN[i],X));
        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText(str);
        tablesOfAllCalcs[i]->setItem(tablesOfAllCalcs[i]->rowCount()-1,3,item3);
    }
}

void PostProcWindow::paintGraph()
{
    GraphicWindow* gw = new GraphicWindow(spinType->value(),5,matrixU[spinRod->value()-1]);
    qDebug()<<"VECUx = "<<matrixU[spinRod->value()-1];
    gw->show();
}

void PostProcWindow::backToMenu()
{

}
