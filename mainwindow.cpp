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

    QPushButton* btnBack = new QPushButton(icoLeftArr,"Назад");
    btnBack->setFixedHeight(30);
    btnBack->setStyleSheet("QPushButton:enabled { background-color: white; border-radius:5px;}"
                            "QPushButton:hover { background-color: black; color: white; }"
                            "QPushButton:pressed { background-color: black; color: white;}"
                            "QPushButton:disabled { background-color: white; border-radius:5px;}");
    layoutV->addWidget(btnBack);
    QObject::connect(btnBack,SIGNAL(clicked()),this,SLOT(backToMainMenu()));

    this->setLayout(layoutV);
    qDebug()<<rods.size();

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
    pw->show();
    this->close();
}

void MainWindow::loadProc()
{
    if(rods.size()!=0)
    {
        ProcCalculations* calc = new ProcCalculations(rods,loads);
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

}
