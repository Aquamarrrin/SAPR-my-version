#include "preprocwindow.h"

PreProcWindow::PreProcWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(900,650);

    layoutV = new QVBoxLayout();
    layoutH = new QHBoxLayout();

    QMenuBar* mnuBar=  new QMenuBar();
    QMenu * menu = new QMenu("Файл");
    menu->addAction("Сохранить");
    menu->addAction("Загрузить");
    menu->addSeparator();
    menu->addAction("Выход");
    mnuBar->addMenu(menu);

    btnDraw = new QPushButton("Draw");
    btnDraw->setMaximumWidth(500);
    btnDraw->setMinimumWidth(350);
    btnDraw->setFixedHeight(30);
    QObject::connect(btnDraw,SIGNAL(clicked()),this,SLOT(showConstruction()));

    QPushButton* btnBack = new QPushButton("Назад");
    btnBack->setFixedHeight(30);
    QObject::connect(btnBack,SIGNAL(clicked()),this,SLOT(backToMenu()));

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
    tableLoad->setColumnCount(3);
    tableLoad->verticalHeader()->hide();
    QTableWidgetItem* itemLoadHor1 = new QTableWidgetItem("№ узла");
    tableLoad->setHorizontalHeaderItem(0,itemLoadHor1);
    QTableWidgetItem* itemLoadHor2 = new QTableWidgetItem("Fx");
    tableLoad->setHorizontalHeaderItem(1,itemLoadHor2);
    QTableWidgetItem* itemLoadHor3 = new QTableWidgetItem("Заделка");
    tableLoad->setHorizontalHeaderItem(2,itemLoadHor3);
    (tableLoad->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
    (tableLoad->horizontalHeader())->setMinimumSectionSize(50);

    //Таблица параметров стержней:
    tableRodSettings = new QTableWidget(this);
    tableRodSettings->setMinimumWidth(350);
    tableRodSettings->setMaximumWidth(500);
    tableRodSettings->setColumnCount(4);
    tableRodSettings->setRowCount(1);
    QTableWidgetItem* itemParamHor1 = new QTableWidgetItem("A стержня");
    tableRodSettings->setHorizontalHeaderItem(0,itemParamHor1);
    QTableWidgetItem* itemParamHor2 = new QTableWidgetItem("L стержня");
    tableRodSettings->setHorizontalHeaderItem(1,itemParamHor2);
    QTableWidgetItem* itemParamHor3 = new QTableWidgetItem("E стержня");
    tableRodSettings->setHorizontalHeaderItem(2,itemParamHor3);
    QTableWidgetItem* itemParamHor4 = new QTableWidgetItem("Fx распр");
    tableRodSettings->setHorizontalHeaderItem(3,itemParamHor4);
    (tableRodSettings->horizontalHeader())->setSectionResizeMode(QHeaderView::Stretch);
    (tableRodSettings->horizontalHeader())->setMinimumSectionSize(50);

    //Отрисовка конструкции:
    constr = new Construction();
    constr->setMinimumWidth(500);
    constr->setFixedHeight(400);

    //Добавляем все элементы на лэйаут
    layoutH->setMenuBar(mnuBar);

    layoutV->addWidget(numNodes);
    layoutV->addWidget(tableRodSettings);
    layoutV->addWidget(numLoads);
    layoutV->addWidget(tableLoad);
    layoutV->addWidget(btnDraw);
    layoutV->addWidget(btnBack);

    layoutH->addLayout(layoutV,1);
    layoutH->addWidget(constr,1);
    this->setLayout(layoutH);
}

void PreProcWindow::createTableRod(int nNodes)
{
    if(nNodes==tableRodSettings->rowCount()+1 || nNodes==tableRodSettings->rowCount()-1)
    {
        if (nNodes>=tableRodSettings->rowCount() || !isNotEmpty(tableRodSettings->rowCount()-1,tableRodSettings))
            tableRodSettings->setRowCount(nNodes);
        else
        {
            QMessageBox* msg = new QMessageBox();
            msg->setText("Невозможно уменьшить колличество стержней: риск потерять данные");
            msg->show();
            numNodes->setValue(nNodes+1);
        }
    }
    else
    {
        numNodes->setValue(tableRodSettings->rowCount());
    }
}


void PreProcWindow::createTableLoad(int nLoads)
{
    if(nLoads==tableLoad->rowCount()+1 || nLoads==tableLoad->rowCount()-1)
    {
        if(nLoads<=numNodes->value()+1)
        {
            if (nLoads>=tableLoad->rowCount() || !isNotEmpty(tableLoad->rowCount()-1,tableLoad))
                tableLoad->setRowCount(nLoads);
            else
            {
                QMessageBox* msg = new QMessageBox();
                msg->setText("Невозможно уменьшить колличество стержней: риск потерять данные");
                msg->show();
                numLoads->setValue(nLoads+1);
            }
        }
        else
        {
            QMessageBox* msg = new QMessageBox();
            msg->setText("Колличество узлов не может превышать колличество стержней + 1");
            msg->show();
            numLoads->setValue(nLoads-1);
        }
    }
    else
    {
        numLoads->setValue(tableLoad->rowCount());
    }
}

void PreProcWindow::showConstruction()
{
    //Меняем или задаем параметры стержней
    constr->clearMapRods();
    for(int row=0;row<tableRodSettings->rowCount();row++)
        if(isFilled(row, tableRodSettings))
        {
            QVector<float> vec;
            bool ok=false;
            for(int i=0;i<tableRodSettings->columnCount();i++)
            {
                if(i==tableRodSettings->columnCount()-1 || tableRodSettings->item(row,i)->text().toInt()>=0)
                {
                    vec.push_back(tableRodSettings->item(row,i)->text().toInt());
                    ok=true;
                }
                else
                {
                    tableRodSettings->setCurrentCell(row,i);
                    QMessageBox* msg = new QMessageBox();
                    msg->setText("У стержня № "+(new QString())->QString::setNum(row+1)+" неправильно введены входные данные");
                    msg->show();
                    ok=false;
                    break;
                }
            }
            if (ok)
                constr->changeMapRods(row+1, vec);
            else
            {
                constr->clearMapRods();
                break;
            }
        }
    constr->update();

    //Меняем или задаем параметры нагрузок
    constr->clearMapLoads();
    for(int row=0;row<tableLoad->rowCount();row++)
    {
        if(!isExist(row,0,tableLoad))
        {
            if(isFilled(row, tableLoad))
            {
                QVector<float> vec;
                bool ok=false;
                for(int i=0;i<tableLoad->columnCount();i++)
                {
                    if(tableLoad->item(row,0)->text().toInt()>0)
                    {
                        vec.push_back(tableLoad->item(row,i)->text().toInt());
                        ok=true;
                    }
                    else
                    {
                        ok=false;
                        break;
                    }
                }
                if(ok)
                    constr->changeMapLoads(vec);
                else
                {
                    tableLoad->setCurrentCell(row,0);
                    QMessageBox* msg = new QMessageBox();
                    msg->setText("В таблице нагрузок неправильно введен номер узла");
                    msg->show();
                    constr->clearMapLoads();
                    break;
                }
            }
        }
        else
        {
            tableLoad->setCurrentCell(row,0);
            QMessageBox* msg = new QMessageBox();
            msg->setText("В таблице нагрузок нельзя указывать 2 раза один и тот же узел");
            msg->show();
            break;
        }
    }
    constr->update();
}

void PreProcWindow::backToMenu()
{
    MainWindow* mw = new MainWindow();
    mw->startMenu();
    mw->show();
    this->close();
}



bool PreProcWindow::isFilled(int row, QTableWidget* table)
{
    for(int i=0;i<table->columnCount();i++)
        if(table->item(row,i)->text().isEmpty())
            return false;
    return true;
}

bool PreProcWindow::isNotEmpty(int row, QTableWidget* table)
{
    for(int i=0;i<table->columnCount();i++)
        if(table->item(row,i)!=0 && !table->item(row,i)->text().isEmpty())
            return true;
    return false;
}

bool PreProcWindow::isExist(int row, int column, QTableWidget *table)
{
    for(int i=0;i<table->rowCount();i++)
        if(i!=row && table->item(row,column)->text().toInt()==table->item(i,column)->text().toInt())
            return true;
    return false;
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


