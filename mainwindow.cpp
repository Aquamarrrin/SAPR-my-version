#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(350,350);
    layoutV=new QVBoxLayout;

    QIcon icoRightArr(":/icons/next_arrow_white.ico");
    btnStart = new QPushButton(icoRightArr,"Начать");
    btnStart->setFixedHeight(30);
    //QPushButton{selection-background-color:qlineargradient(x1:0, y1:0, x2:0.5, y2:0.5, stop: 0 blue, stop: 1 black);}
    //background:qlineargradient(x1:0, y1:0, x2:0.5, y2:0.5, stop: 0 #f0f, stop: 1 black);
    btnStart->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white; }"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnStart);
    QObject::connect(btnStart,SIGNAL(clicked()),this,SLOT(startMenu()));

    btnLoad = new QPushButton(icoRightArr,"Загрузить");
    btnLoad->setFixedHeight(30);
    btnLoad->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white;}"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnLoad);
    QObject::connect(btnLoad,SIGNAL(clicked()),this,SLOT(openFile()));

    QIcon icoExit(":/icons/exit.ico");
    QPushButton* btnBack = new QPushButton(icoExit,"Выход");
    btnBack->setFixedHeight(30);
    btnBack->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                           "QPushButton:hover { background-color: black; color: white;}"
                           "QPushButton:pressed { background-color: black; color: white;}"
                           "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnBack);
    QObject::connect(btnBack,SIGNAL(clicked()),this,SLOT(close()));

    this->setLayout(layoutV);
}

void MainWindow::startMenu()
{
    clean();
    QIcon icoRightArr(":/icons/next_arrow_white.ico");
    QIcon icoLeftArr(":/icons/back_arrow_white.ico");

    btnPreProc = new QPushButton(icoRightArr,"Препроцессор");
    btnPreProc->setFixedHeight(30);
    btnPreProc->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white; }"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnPreProc);
    QObject::connect(btnPreProc,SIGNAL(clicked()),this,SLOT(loadPreProc()));

    btnProc = new QPushButton(icoRightArr,"Процессор");
    btnProc->setFixedHeight(30);
    btnProc->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white; }"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnProc);
    QObject::connect(btnProc,SIGNAL(clicked()),this,SLOT(loadProc()));

    btnPostProc = new QPushButton(icoRightArr,"Построцессор");
    btnPostProc->setFixedHeight(30);
    btnPostProc->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white; }"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnPostProc);
    QObject::connect(btnPostProc,SIGNAL(clicked()),this,SLOT(loadPostProc()));

    QPushButton* btnBack = new QPushButton(icoLeftArr,"Назад");
    btnBack->setFixedHeight(30);
    btnBack->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white; }"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnBack);
    QObject::connect(btnBack,SIGNAL(clicked()),this,SLOT(backToMainMenu()));

    this->setLayout(layoutV);

}

void MainWindow::backToMainMenu()
{
    clean();

    QIcon icoRightArr(":/icons/next_arrow_white.ico");
    btnStart = new QPushButton(icoRightArr,"Начать");
    btnStart->setFixedHeight(30);
    btnStart->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white; }"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnStart);
    QObject::connect(btnStart,SIGNAL(clicked()),this,SLOT(startMenu()));

    btnLoad = new QPushButton(icoRightArr,"Загрузить");
    btnLoad->setFixedHeight(30);
    btnLoad->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white;}"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnLoad);
    QObject::connect(btnLoad,SIGNAL(clicked()),this,SLOT(openFile()));

    QIcon icoExit(":/icons/exit.ico");
    QPushButton* btnBack = new QPushButton(icoExit,"Выход");
    btnBack->setFixedHeight(30);
    btnBack->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                           "QPushButton:hover { background-color: black; color: white;}"
                           "QPushButton:pressed { background-color: black; color: white;}"
                           "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnBack);
    QObject::connect(btnBack,SIGNAL(clicked()),this,SLOT(close()));

    this->setLayout(layoutV);
}

void MainWindow::loadPreProc()
{
    PreProcWindow* pw = new PreProcWindow();
    pw->openTmpFile();
    pw->show();
    this->close();
}

void MainWindow::loadProc()
{
    if(rods.size()!=0)
    {
        ProcCalculations* calc = new ProcCalculations(rods,loads);
        QMessageBox* msg = new QMessageBox();
        msg->setText("Все расчёты успешно произведены! Сохранить?");
        this->matrixU.clear();
        this->matrixN.clear();
        this->matrixD.clear();
        this->matrixU=calc->matrixU;
        this->matrixN=calc->matrixN;
        this->matrixD=calc->matrixD;
        QPushButton* btnSave = msg->addButton("Да",QMessageBox::YesRole);
        connect(btnSave,SIGNAL(clicked()),this,SLOT(saveFile()));
        msg->addButton("Нет",QMessageBox::NoRole);
        msg->show();
    }
}

void MainWindow::loadPostProc()
{
    if(rods.size()!=0 && matrixD.size()!=0)
    {
        PostProcWindow* postPW= new PostProcWindow(rods,matrixU,matrixN);
        postPW->setMinimumSize(800,700);
        postPW->show();
    }
}


void MainWindow::showThisMenu()
{
    this->show();
}

void MainWindow::openFile()
{
    QString fileName=QFileDialog::getOpenFileName(this,tr("OpenFile"),"",tr("Text Files (*.txt)"));
    PreProcWindow* pw = new PreProcWindow(fileName);
    pw->show();
    this->close();
}

void MainWindow::saveFile()
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
        }
        else
        {
            QTextStream stream(&file);
            stream<<"Matrix [U]:\n";
            for (int i=0;i<matrixU.size();i++)
            {
                for (int j=0;j<matrixU[i].size();j++)
                    stream<<(new QString())->QString::setNum(matrixU[i][j])<<";";
                            stream<<"\n";
            }
            stream<<"\n";
            stream<<"Matrix [N]:\n";
            for (int i=0;i<matrixN.size();i++)
            {
                for (int j=0;j<matrixN[i].size();j++)
                    stream<<(new QString())->QString::setNum(matrixN[i][j])<<";";
                            stream<<"\n";
            }
            stream<<"\n";
            stream<<"Vector {D}:\n";
            for (int i=0;i<matrixD.size();i++)
            {
                stream<<(new QString())->QString::setNum(matrixD[i])<<";";
                stream<<"\n";
            }
            stream.flush();

            file.close();

        }
    }
}

void MainWindow::takeValues(QVector<Rod> rods, QVector<Load> loads)
{
    this->rods=rods;
    this->loads=loads;
}

void MainWindow::clean( )
{
    QLayoutItem *child;
     while ((child = this->layout()->takeAt(0)) != 0)
     {
         delete child->widget();
         delete child;
     }
}

MainWindow::~MainWindow()
{
    QFile file("tmpFileOfTables.txt");
    file.remove();
}
