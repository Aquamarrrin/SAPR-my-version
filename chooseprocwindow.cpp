#include "chooseprocwindow.h"

ChooseProcWindow::ChooseProcWindow(QWidget *parent) :
    QWidget(parent)
{

    this->setMinimumSize(350,350);
    this->resize(500,500);

    QVBoxLayout* layoutV = new QVBoxLayout;

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


    this->setLayout(layoutV);
}


void ChooseProcWindow::loadPreProc()
{
    PreProcWindow* pw = new PreProcWindow();
    pw->show();
    this->close();
}


ChooseProcWindow::~ChooseProcWindow()
{}
