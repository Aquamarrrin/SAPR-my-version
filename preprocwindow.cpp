#include "preprocwindow.h"

//При создании нового файла
PreProcWindow::PreProcWindow(QString filePath , QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(900,650);

    layoutV = new QVBoxLayout();
    layoutH = new QHBoxLayout();

    QMenuBar* mnuBar=  new QMenuBar();
    QMenu * menu = new QMenu("Файл");
    QIcon icoExit(":/icons/exit.ico");
    QIcon icoSave(":/icons/save.ico");
    menu->addAction(icoSave,"Сохранить",this,SLOT(saveFile()));
    menu->addAction("Загрузить",this,SLOT(openFile()));
    menu->addSeparator();
    menu->addAction(icoExit,"Выход",this,SLOT(close()));
    mnuBar->addMenu(menu);

    QIcon icoNext(":/icons/next_arrow_white.ico");
    btnDraw = new QPushButton(icoNext,"Рисовать");
    btnDraw->setMaximumWidth(500);
    btnDraw->setMinimumWidth(350);
    btnDraw->setFixedHeight(30);
    btnDraw->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                           "QPushButton:hover { background-color: black; color: white;}"
                           "QPushButton:pressed { background-color: black; color: white;}"
                           "QPushButton:disabled { background-color: white; border-radius:5px;}");
    QObject::connect(btnDraw,SIGNAL(clicked()),this,SLOT(showConstruction()));

    QIcon icoBack(":/icons/back_arrow_white.ico");
    QPushButton* btnBack = new QPushButton(icoBack,"Назад");
    btnBack->setFixedHeight(30);
    btnBack->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                           "QPushButton:hover { background-color: black; color: white;}"
                           "QPushButton:pressed { background-color: black; color: white;}"
                           "QPushButton:disabled { background-color: white; border-radius:5px;}");
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

    if(filePath!="")
    {
        fileOfTablesText.clear();
        QFile file(filePath);
        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,tr("Error"),tr("Открытие файла невозможно"));
            return;
        }
        QTextStream stream(&file);
        while (stream.atEnd() == false)
        {
            QString strTxt=stream.readLine();
            fileOfTablesText.push_back(strTxt);
        }
        file.close();

        parseFileOfTablesText();

    }
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

Construction* PreProcWindow::getConstr()
{
    return constr;
}

//Изменяем колличество строк в таблице стержней
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

//Изменяем колличество строк в таблице нагрузок
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

//Передаём параметры стержней и нагрузок в класс конструкции
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
                if((isNumber(tableRodSettings->item(row,i)->text())) && (i==tableRodSettings->columnCount()-1 || tableRodSettings->item(row,i)->text().toFloat()>0))
                {
                    vec.push_back(tableRodSettings->item(row,i)->text().toFloat());
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
                bool ok2=true;

                if(isNumber(tableLoad->item(row,0)->text()) && tableLoad->item(row,0)->text().toFloat()>0 && tableLoad->item(row,0)->text().toFloat()<=tableRodSettings->rowCount()+1)
                    for(int i=0;i<tableLoad->columnCount();i++)
                    {
                        if(isNumber(tableLoad->item(row,i)->text()))
                        {
                            vec.push_back(tableLoad->item(row,i)->text().toFloat());
                            ok=true;
                        }
                        else
                        {
                            ok=false;
                            ok2=false;
                            tableLoad->setCurrentCell(row,i);
                            QMessageBox* msg = new QMessageBox();
                            msg->setText("В таблице нагрузок нельзя вводить буквы и другие нечисловые символы!");
                            msg->show();
                            constr->clearMapLoads();
                            break;
                        }
                    }
                else
                {
                    ok=false;
                }

                if(ok)
                    constr->changeMapLoads(vec);
                else
                {
                    if(ok2)
                    {
                        tableLoad->setCurrentCell(row,0);
                        QMessageBox* msg = new QMessageBox();
                        msg->setText("В таблице нагрузок неправильно введен номер узла");
                        msg->show();
                        constr->clearMapLoads();
                    }
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

//Назад в меню
void PreProcWindow::backToMenu()
{
    MainWindow* mw = new MainWindow();
    mw->takeValues(constr->getVecRod(),constr->getVecLoad());
    mw->startMenu();
    mw->show();
    this->close();
}


//Проверяем заполнена ли строчка в таблице
bool PreProcWindow::isFilled(int row, QTableWidget* table)
{
    for(int i=0;i<table->columnCount();i++)
        if(table->item(row,i)->text().isEmpty())
            return false;
    return true;
}

//Проверяем пуста ли строчка в таблице
bool PreProcWindow::isNotEmpty(int row, QTableWidget* table)
{
    for(int i=0;i<table->columnCount();i++)
        if(table->item(row,i)!=0 && !table->item(row,i)->text().isEmpty())
            return true;
    return false;
}

//Проверяем пуста ли определенная ячейка в таблице
bool PreProcWindow::isExist(int row, int column, QTableWidget *table)
{
    for(int i=0;i<table->rowCount();i++)
        if(i!=row && table->item(row,column)->text().toFloat()==table->item(i,column)->text().toFloat())
            return true;
    return false;
}

bool PreProcWindow::isNumber(const QString &str)
{
    QRegExp reg("[0-9]+");
    return reg.indexIn(str) != -1;
}

//Сохранем в текстовый файл данные таблиц
void PreProcWindow::saveFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
                                                    tr("Text Files (*.txt)"));

    if (fileName != "")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::critical(this,tr("Error"),tr("Сохранение файла невозможно"));
            return;
        } else {
            QTextStream stream(&file);
            stream<<"Rods:\n";
            for (int i=0;i<tableRodSettings->rowCount();i++)
            {
                for (int j=0;j<tableRodSettings->columnCount();j++)
                    stream<<tableRodSettings->item(i,j)->text()<<";";
                stream<<"\n";
            }
            stream<<"\n";
            stream<<"Loads:\n";
            for (int i=0;i<tableLoad->rowCount();i++)
            {
                for (int j=0;j<tableLoad->columnCount();j++)
                    stream<<tableLoad->item(i,j)->text()<<";";
                stream<<"\n";
            }
            stream.flush();

            file.close();
        }
    }
}

//Открываем уже сохраненный файл
void PreProcWindow::openFile()
{
    fileOfTablesText.clear();
    QString fileName=QFileDialog::getOpenFileName(this,tr("OpenFile"),"",tr("Text Files (*.txt)"));
    if (fileName !="")
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,tr("Error"),tr("Открытие файла невозможно"));
            return;
        }
        //textEdt->setText(in.readAll());
        QTextStream stream(&file);
        while (stream.atEnd() == false)
        {
            QString strTxt=stream.readLine();
            fileOfTablesText.push_back(strTxt);
        }
        file.close();

        parseFileOfTablesText();
    }
}

void PreProcWindow::parseFileOfTablesText()
{
    tableRodSettings->clear();
    tableLoad->clear();
    //Таблица нагрузок:
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

    int i=0;
    int numOfRows=0;
    while (numLoads->value()!=0)
    {
        numLoads->setValue(numLoads->value()-1);
    }
    while (numNodes->value()!=1)
    {
        numNodes->setValue(numNodes->value()-1);
    }

    while(i!=fileOfTablesText.size() && fileOfTablesText[i]!="Loads:")
    {
        if(fileOfTablesText[i]!="" && fileOfTablesText[i]!="Rods:")
        {
            numNodes->setValue(numOfRows+1);
            int j=0;
            int numOfCol=0;
            while(j<fileOfTablesText[i].size())
            {
                QString tmpValueItem="";
                while(fileOfTablesText[i][j]!=';')
                {
                    tmpValueItem+=fileOfTablesText[i][j];
                    j++;
                }
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(tmpValueItem);
                tableRodSettings->setItem(numOfRows,numOfCol,item);
                j++;
                numOfCol++;
            }
            numOfRows++;
        }
        i++;
    }

    i++;
    numOfRows=0;
    while(i!=fileOfTablesText.size())
    {
        if(fileOfTablesText[i]!="" && fileOfTablesText[i]!="Loads:")
        {
            createTableLoad(numOfRows+1);
            int j=0;
            int numOfCol=0;
            while(j<fileOfTablesText[i].size())
            {
                QString tmpValueItem="";
                while(fileOfTablesText[i][j]!=';' && fileOfTablesText[i][j]!=' ')
                {
                    tmpValueItem+=fileOfTablesText[i][j];
                    j++;
                }
                QTableWidgetItem *item = new QTableWidgetItem();
                item->setText(tmpValueItem);
                tableLoad->setItem(numOfRows,numOfCol,item);
                j++;
                numOfCol++;
            }
            numOfRows++;
        }
        i++;
    }
    numLoads->setValue(numOfRows);
}

PreProcWindow::~PreProcWindow()
{}

