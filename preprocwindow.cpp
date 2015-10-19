#include "preprocwindow.h"

PreProcWindow::PreProcWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(900,650);

    layoutV = new QVBoxLayout();
    layoutH = new QHBoxLayout();

    btnDraw = new QPushButton("Draw");
    btnDraw->setMaximumWidth(500);
    btnDraw->setMinimumWidth(350);
    QObject::connect(btnDraw,SIGNAL(clicked()),this,SLOT(showConstruction()));

    //Поля для ввода количества узлов, стержней и нагрузок
    numNodes = new QSlider();
    numNodes->setMaximumWidth(500);
    numNodes->setMinimum(1);
    numNodes->setMaximum(50);
    numNodes->setTickPosition(QSlider::TicksBelow);
    numNodes->setTickInterval(2);
    numNodes->setOrientation(Qt::Horizontal);
    connect(numNodes,SIGNAL(valueChanged(int)),this,SLOT(createTableRod(int)));

    numLoads = new QSlider();
    numLoads->setMaximumWidth(500);
    numLoads->setOrientation(Qt::Horizontal);
    numLoads->setMinimum(0);
    numLoads->setMaximum(50);
    numLoads->setTickPosition(QSlider::TicksBelow);
    numLoads->setTickInterval(2);
    connect(numLoads,SIGNAL(valueChanged(int)),this,SLOT(createTableLoad(int)));

    //Таблицы:

    //Таблица нагрузок:
    tableLoad = new QTableWidget(this);
    tableLoad->setMinimumWidth(350);
    tableLoad->setMaximumWidth(500);
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
    tableRodSettings->setMinimumWidth(350);
    tableRodSettings->setMaximumWidth(500);
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
    constr->setMinimumWidth(500);
    constr->setFixedHeight(400);

    //Добавляем все элементы на лэйаут

    layoutV->addWidget(numLoads);
    layoutV->addWidget(tableLoad);
    layoutV->addWidget(numNodes);
    layoutV->addWidget(tableRodSettings);
    layoutV->addWidget(btnDraw);

    layoutH->addLayout(layoutV,1);
    layoutH->addWidget(constr,1);
    this->setLayout(layoutH);
}

void PreProcWindow::createTableRod(int nNodes)
{
    tableRodSettings->setRowCount(nNodes);
}


void PreProcWindow::createTableLoad(int nLoads)
{
    tableLoad->setRowCount(nLoads);
}

void PreProcWindow::showConstruction()
{
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

    //Меняем или задаем параметры нагрузок
    constr->clearMapLoads();
    for(int row=0;row<tableLoad->rowCount();row++)
        if(isFilled(row, tableLoad))
        {
            QVector<float> vec;
            for(int i=0;i<tableLoad->columnCount();i++)
                vec.push_back(tableLoad->item(row,i)->text().toInt());
            constr->changeMapLoads(vec);
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


