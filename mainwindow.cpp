#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setMinimumSize(350,350);
    this->resize(500,500);
    QVBoxLayout* layoutV=new QVBoxLayout;

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

void MainWindow::startMenu()
{
    ChooseProcWindow* chw=new ChooseProcWindow();
    chw->show();
    this->close();
}

MainWindow::~MainWindow()
{

}
