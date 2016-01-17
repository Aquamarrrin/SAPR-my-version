#include "postprocwindow.h"

PostProcWindow::PostProcWindow(QVector<Rod> rods, QVector<QVector<float> > matrixU, QVector<QVector<float> > matrixN, QWidget *parent) :
    QWidget(parent)
{

    layoutG = new QGridLayout();

    QIcon icoNext(":/icons/next_arrow_white.ico");
    QIcon icoBack(":/icons/back_arrow_white.ico");

    this->rods=rods;
    this->matrixN=matrixN;
    this->matrixU=matrixU;

    QLabel* label1=new QLabel("Введите номер стержня");
    QLabel* label2=new QLabel("Введите тип параметра(1 - Ux, 2 - Nx, 3 - Sx)");
    QLabel* labelRod=new QLabel("Расчитать значения параметров стержня ");
    QLabel* labelX=new QLabel(" в заданной точке:");

    lineEditX = new QLineEdit();

    QPushButton* btnCalc = new QPushButton(icoNext,"Расчитать");
    btnCalc->setMinimumWidth(200);
    btnCalc->setFixedHeight(40);
    btnCalc->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white;}"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    connect(btnCalc,SIGNAL(clicked()),this,SLOT(calcParams()));

    QPushButton* btnEnter = new QPushButton(icoNext,"Добавить Х");
    btnEnter->setMinimumWidth(100);
    btnEnter->setFixedHeight(25);
    btnEnter->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white;}"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    connect(btnEnter,SIGNAL(clicked()),this,SLOT(setX()));

    QPushButton* btn = new QPushButton(icoNext,"График");
    btn->setMinimumWidth(100);
    btn->setFixedHeight(25);
    btn->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                       "QPushButton:hover { background-color: black; color: white;}"
                       "QPushButton:pressed { background-color: black; color: white;}"
                       "QPushButton:disabled { background-color: white; border-radius:5px;}");
    connect(btn,SIGNAL(clicked()),this,SLOT(paintGraph()));

    QPushButton* btnDel = new QPushButton(icoBack,"Удалить X");
    btnDel->setMinimumWidth(100);
    btnDel->setFixedHeight(25);
    btnDel->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                           "QPushButton:hover { background-color: black; color: white;}"
                           "QPushButton:pressed { background-color: black; color: white;}"
                           "QPushButton:disabled { background-color: white; border-radius:5px;}");
    QObject::connect(btnDel,SIGNAL(clicked()),this,SLOT(delX()));

    spinRod = new QSpinBox();
    spinRod->setMinimum(1);
    spinRod->setMaximum(matrixU.size());

    spinRodForCalcs = new QSpinBox();
    spinRodForCalcs->setMinimum(1);
    spinRodForCalcs->setMaximum(matrixU.size());

    spinType= new QSpinBox();
    spinType->setMinimum(1);
    spinType->setMaximum(3);

    spinMaxX= new QSpinBox();
    spinMaxX->setMinimum(1);
    spinMaxX->setMaximum(1000);

    for(int i=0;i<matrixU.size();i++)
    {
        QTableWidget* tableOfAllCalcs = new QTableWidget(2,4,this);
        tableOfAllCalcs->verticalHeader()->hide();
        QTableWidgetItem* itemParamHor0 = new QTableWidgetItem("x");
        tableOfAllCalcs->setHorizontalHeaderItem(0,itemParamHor0);
        QTableWidgetItem* itemParamHor1 = new QTableWidgetItem("Ux стержня");
        tableOfAllCalcs->setHorizontalHeaderItem(1,itemParamHor1);
        QTableWidgetItem* itemParamHor2 = new QTableWidgetItem("σx стержня");
        tableOfAllCalcs->setHorizontalHeaderItem(2,itemParamHor2);
        QTableWidgetItem* itemParamHor3 = new QTableWidgetItem("Nx стержня");
        tableOfAllCalcs->setHorizontalHeaderItem(3,itemParamHor3);

        (tableOfAllCalcs->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
        (tableOfAllCalcs->horizontalHeader())->setMinimumSectionSize(50);

        fillTable(tableOfAllCalcs,i);
        tablesOfAllCalcs.push_back(tableOfAllCalcs);
    }

    layoutG->addWidget(label1,0,0);
    layoutG->addWidget(label2,0,1);
    layoutG->addWidget(btnEnter,0,2);
    layoutG->addWidget(btnDel,0,3);
    layoutG->addWidget(spinRod,1,0);
    layoutG->addWidget(spinType,1,1);
    layoutG->addWidget(btn,1,2,1,2);

    int tmpC = 2;
    for(int i=0;i<tablesOfAllCalcs.size();i++){

        QString tmpStr;
        tmpStr.setNum(i+1);
        QLabel* labelNameOfRod=new QLabel(tmpStr+" стержень");
        layoutG->addWidget(labelNameOfRod,i+tmpC,0,1,1);
        layoutG->addWidget(tablesOfAllCalcs[i],i+tmpC+1,0,1,4);
        tmpC++;
    }

    layoutG->addWidget(labelRod,tablesOfAllCalcs.size()+tmpC+1,0,1,1);
    layoutG->addWidget(spinRodForCalcs,tablesOfAllCalcs.size()+tmpC+1,1,1,1);
    layoutG->addWidget(labelX,tablesOfAllCalcs.size()+tmpC+2,0,1,1);
    layoutG->addWidget(lineEditX,tablesOfAllCalcs.size()+tmpC+2,1,1,1);
    layoutG->addWidget(btnCalc,tablesOfAllCalcs.size()+tmpC+1,2,2,1);

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

void PostProcWindow::fillTable(QTableWidget *tableOfAllCalcs, int matInd)
{
    for(int i=0;i<tableOfAllCalcs->rowCount();i++)
    {
        QString str = "";
        str.setNum((float)i/10);
        QTableWidgetItem *item0 = new QTableWidgetItem();
        item0->setText(str);
        tableOfAllCalcs->setItem(i,0,item0);

        str.setNum(funcUx(matrixU[matInd],(float)i/10));
        QTableWidgetItem *item1 = new QTableWidgetItem();
        item1->setText(str);
        tableOfAllCalcs->setItem(i,1,item1);

        str = "";
        str.setNum(funcNx(matrixN[matInd],(float)i/10)/(rods[matInd].height));
        QTableWidgetItem *item2 = new QTableWidgetItem();
        item2->setText(str);
        if(funcNx(matrixN[matInd],(float)i/10)/(rods[matInd].height)>rods[matInd].sigma)
            item2->setTextColor("red");
        tableOfAllCalcs->setItem(i,2,item2);

        str = "";
        str.setNum(funcNx(matrixN[matInd],(float)i/10));
        QTableWidgetItem *item3 = new QTableWidgetItem();
        item3->setText(str);
        tableOfAllCalcs->setItem(i,3,item3);
    }


}

void PostProcWindow::setX()
{
    float X;
    for(int i=0;i<tablesOfAllCalcs.size();i++)
    {
        if(tablesOfAllCalcs[i]->rowCount()<=rods[i].len*10)
        {
            X=tablesOfAllCalcs[i]->item(tablesOfAllCalcs[i]->rowCount()-1,0)->text().toFloat()+0.1;
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
            str.setNum(funcNx(matrixN[i],X)/(rods[i].height));
            QTableWidgetItem *item2 = new QTableWidgetItem();
            item2->setText(str);
            if(funcNx(matrixN[i],X)/(rods[i].height)>rods[i].sigma)
                item2->setTextColor("red");
            tablesOfAllCalcs[i]->setItem(tablesOfAllCalcs[i]->rowCount()-1,2,item2);

            str = "";
            str.setNum(funcNx(matrixN[i],X));
            QTableWidgetItem *item3 = new QTableWidgetItem();
            item3->setText(str);
            tablesOfAllCalcs[i]->setItem(tablesOfAllCalcs[i]->rowCount()-1,3,item3);
        }
    }
}

void PostProcWindow::delX()
{
        for(int i=0;i<tablesOfAllCalcs.size();i++)
        {
            if(tablesOfAllCalcs[i]->rowCount()>2)
            {
                int row=tablesOfAllCalcs[i]->rowCount()-1;
                for(int j=0;j<tablesOfAllCalcs[i]->columnCount();j++)
                    if(tablesOfAllCalcs[i]->item(row,j)!=0)
                        tablesOfAllCalcs[i]->item(row,j)->setText("");
                tablesOfAllCalcs[i]->removeRow(row);
            }
        }
}

void PostProcWindow::calcParams()
{
    QString str;
    float X = lineEditX->text().toFloat();
    if(X<=rods[spinRodForCalcs->value()].len)
    {
        QString strX = str.setNum(lineEditX->text().toFloat());
        QString U = str.setNum(funcUx(matrixU[spinRodForCalcs->value()],X));
        QString N = str.setNum(funcNx(matrixN[spinRodForCalcs->value()],X));
        QString S = str.setNum(funcNx(matrixN[spinRodForCalcs->value()],X)/rods[spinRodForCalcs->value()].height);
        QMessageBox* msg = new QMessageBox();
        msg->setText("В точке Х =   "+ strX+"   значение Ux =   "+U+",   значение Nx   =   "+ N+",   значение Sx   =   "+S+".");
        msg->show();
    }
    else
    {
        QMessageBox* msg = new QMessageBox();
        msg->setText("X превышает допустимое значение.");
        msg->show();
    }
}

void PostProcWindow::paintGraph()
{
    if(spinType->value()==1){
        GraphicWindow* gw = new GraphicWindow(1,rods[spinRod->value()-1].len,matrixU[spinRod->value()-1]);
        gw->setFixedSize(720,690);
        gw->show();
    }
    else
        if(spinType->value()==2){
            GraphicWindow* gw = new GraphicWindow(2,rods[spinRod->value()-1].len,matrixN[spinRod->value()-1]);
            gw->setFixedSize(720,690);
            gw->show();
        }
        else
            if(spinType->value()==3){
                QVector<float > vec = matrixN[spinRod->value()-1];
                for(int i=0;i<3;i++)
                    vec[i]=vec[i]/(rods[spinRod->value()-1].height);
                GraphicWindow* gw = new GraphicWindow(3,rods[spinRod->value()-1].len,vec);
                gw->setFixedSize(720,690);
                gw->show();
            }
}


void PostProcWindow::backToMenu()
{

}
