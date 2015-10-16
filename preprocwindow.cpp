#include "preprocwindow.h"

PreProcWindow::PreProcWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(650,650);

    layoutV = new QVBoxLayout();
    layoutH = new QHBoxLayout();

    btnDraw = new QPushButton("Draw");
    QObject::connect(btnDraw,SIGNAL(clicked()),this,SLOT(changeNodesRodesAndSettings()));

    //Поля для ввода количества узлов, стержней и нагрузок
    numNodes = new QSpinBox();
    numNodes->setMinimum(1);
    QObject::connect(numNodes,SIGNAL(valueChanged(int)),this,SLOT(createTableRod(int)));

    numLoads = new QSpinBox();
    QObject::connect(numLoads,SIGNAL(valueChanged(int)),this,SLOT(createTableLoad(int)));

    //Таблицы:
//    //Таблица узлов:
//    tableNode = new QTableWidget(this);
//    tableNode->setMaximumWidth(190);
//    tableNode->setColumnCount(1);
//    tableNode->setRowCount(2);
//    QTableWidgetItem* itemNodeHor = new QTableWidgetItem("координата X узла");
//    tableNode->setHorizontalHeaderItem(0,itemNodeHor);
//    (tableNode->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
//    (tableNode->horizontalHeader())->setMinimumSectionSize(50);

//    //Таблица стержней:
//    tableRod = new QTableWidget(this);
//    tableRod->setMaximumWidth(210);
//    tableRod->setColumnCount(2);
//    tableRod->setRowCount(1);
//    QTableWidgetItem* itemRodHor1 = new QTableWidgetItem("N 1го узла");
//    tableRod->setHorizontalHeaderItem(0,itemRodHor1);
//    QTableWidgetItem* itemRodHor2 = new QTableWidgetItem("N 2го узла");
//    tableRod->setHorizontalHeaderItem(1,itemRodHor2);
//    (tableRod->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
//    (tableRod->horizontalHeader())->setMinimumSectionSize(50);

    //Таблица нагрузок:
    tableLoad = new QTableWidget(this);
    tableLoad->setMinimumWidth(350);
    tableLoad->setColumnCount(5);
    tableLoad->verticalHeader()->hide();
    QTableWidgetItem* itemLoadHor1 = new QTableWidgetItem("N 1го узла");
    tableLoad->setHorizontalHeaderItem(0,itemLoadHor1);
    QTableWidgetItem* itemLoadHor2 = new QTableWidgetItem("N 2го узла");
    tableLoad->setHorizontalHeaderItem(1,itemLoadHor2);
    QTableWidgetItem* itemLoadHor3 = new QTableWidgetItem("F1");
    tableLoad->setHorizontalHeaderItem(2,itemLoadHor3);
    QTableWidgetItem* itemLoadHor4 = new QTableWidgetItem("F2");
    tableLoad->setHorizontalHeaderItem(3,itemLoadHor4);
    QTableWidgetItem* itemLoadHor5 = new QTableWidgetItem("Заделка");
    tableLoad->setHorizontalHeaderItem(4,itemLoadHor5);
    (tableLoad->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
    (tableLoad->horizontalHeader())->setMinimumSectionSize(50);

    //Таблица параметров стержней:
    tableRodSettings = new QTableWidget(this);
    tableRodSettings->setColumnCount(5);
    tableRodSettings->setRowCount(1);
    QTableWidgetItem* itemParamHor1 = new QTableWidgetItem("H стержня");
    tableRodSettings->setHorizontalHeaderItem(0,itemParamHor1);
    QTableWidgetItem* itemParamHor2 = new QTableWidgetItem("L стержня");
    tableRodSettings->setHorizontalHeaderItem(1,itemParamHor2);
    QTableWidgetItem* itemParamHor3 = new QTableWidgetItem("A стержня");
    tableRodSettings->setHorizontalHeaderItem(2,itemParamHor3);
    QTableWidgetItem* itemParamHor4 = new QTableWidgetItem("B стержня");
    tableRodSettings->setHorizontalHeaderItem(3,itemParamHor4);
    QTableWidgetItem* itemParamHor5 = new QTableWidgetItem("E стержня");
    tableRodSettings->setHorizontalHeaderItem(4,itemParamHor5);
    (tableRodSettings->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
    (tableRodSettings->horizontalHeader())->setMinimumSectionSize(50);

    //Отрисовка конструкции:
    constr = new Construction();
    constr->setFixedHeight(200);

    //Добавляем все элементы на лэйаут
    layoutV->addWidget(numNodes);
    layoutV->addWidget(numLoads);
    layoutV->addWidget(btnDraw);
    //layoutH->addWidget(tableNode);
    //layoutH->addWidget(tableRod);
    layoutH->addWidget(tableLoad);
    layoutV->addLayout(layoutH);
    layoutV->addWidget(tableRodSettings);
    layoutV->addWidget(constr);

    this->setLayout(layoutV);
}

void PreProcWindow::createTableRod(int nNodes)
{
    tableRodSettings->setRowCount(nNodes);
}


void PreProcWindow::createTableLoad(int nLoads)
{
    tableLoad->setRowCount(nLoads);
}

void PreProcWindow::changeNodesRodesAndSettings()
{/*
    //Меняем или задаем узлы
    constr->clearMapNodes();
    for(int row=0;row<tableNode->rowCount();row++)
        if(isFilled(row, tableNode))
            constr->changeMapNodes(row+1, tableNode->item(row,0)->text().toFloat());
    //Меняем или задаем стержни
    constr->clearMapRods();
    for(int row=0;row<tableRod->rowCount();row++)
        if(isFilled(row, tableRod))
        {
            QPoint point;
            point.setX(tableRod->item(row,0)->text().toInt());
            point.setY(tableRod->item(row,1)->text().toInt());
            constr->changeMapRods(row+1, point);
        }*/

    //Меняем или задаем параметры стержней
    constr->clearMapRods();
    for(int row=0;row<tableRodSettings->rowCount();row++)
        if(isFilled(row, tableRodSettings))
        {
            QVector<float> vec;
            for(int i=0;i<tableRodSettings->columnCount();i++)
                vec.push_back(tableRodSettings->item(row,i)->text().toInt());
            constr->changeMapRods(row+1, vec);
        }
}


bool PreProcWindow::isFilled(int row, QTableWidget* table)
{
    for(int i=0;i<table->columnCount();i++)
        if(table->item(row,i)==0)
            return false;
    return true;
}




//заполнение таблицы из файла
//QString line;
//QFile file(QApplication::applicationDirPath()+"/log.txt");
//if(file.open(QIODevice::ReadOnly | QIODevice::Text))
//{
//    QTextStream textStream(&file);

//    for(int i = 0; !textStream.atEnd(); i++)
//    {
//        line = textStream.readLine();    // Читать лучше из потока, если уже его создали. :)
//        QTableWidgetItem *item = new QTableWidgetItem();
//        item->setText(line);
//        ui->tableWidget->setItem(0,i,item);
//    }
//    file.close();
//}


