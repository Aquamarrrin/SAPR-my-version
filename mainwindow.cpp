#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(350,350);
    layoutV=new QVBoxLayout;

    btnStart = new QPushButton("Начать");
    btnStart->setFixedHeight(70);
    //btnStart->setStyleSheet(" QPushButton{ background-color: #fff800; border-color: red; border-style: solid} QPushButton:pressed { background-color: red; border-style: solid}");
    layoutV->addWidget(btnStart);
    QObject::connect(btnStart,SIGNAL(clicked()),this,SLOT(startMenu()));

    btnSave = new QPushButton("Сохранить");
    btnSave->setFixedHeight(70);
    layoutV->addWidget(btnSave);

    btnLoad = new QPushButton("Загрузить");
    btnLoad->setFixedHeight(70);
    layoutV->addWidget(btnLoad);

    this->setLayout(layoutV);
}

void MainWindow::startMenu()
{
    clean();

    btnPreProc = new QPushButton("Препроцессор");
    btnPreProc->setFixedHeight(70);
    layoutV->addWidget(btnPreProc);
    QObject::connect(btnPreProc,SIGNAL(clicked()),this,SLOT(loadPreProc()));

    btnProc = new QPushButton("Процессор");
    btnProc->setFixedHeight(70);
    layoutV->addWidget(btnProc);

    btnPostProc = new QPushButton("Построцессор");
    btnPostProc->setFixedHeight(70);
    layoutV->addWidget(btnPostProc);

    QPushButton* btnBack = new QPushButton("Назад");
    btnBack->setFixedHeight(70);
    layoutV->addWidget(btnBack);
    QObject::connect(btnBack,SIGNAL(clicked()),this,SLOT(backToMainMenu()));

    this->setLayout(layoutV);
}

void MainWindow::backToMainMenu()
{
    clean();

    btnStart = new QPushButton("Начать");
    btnStart->setFixedHeight(70);
    layoutV->addWidget(btnStart);
    QObject::connect(btnStart,SIGNAL(clicked()),this,SLOT(startMenu()));

    btnSave = new QPushButton("Сохранить");
    btnSave->setFixedHeight(70);
    layoutV->addWidget(btnSave);

    btnLoad = new QPushButton("Загрузить");
    btnLoad->setFixedHeight(70);
    layoutV->addWidget(btnLoad);

    this->setLayout(layoutV);
}

void MainWindow::loadPreProc()
{
    PreProcWindow* pw = new PreProcWindow();
    pw->show();
    this->close();
}

void MainWindow::showThisMenu()
{
    this->show();
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
