#ifndef POSTPROCWINDOW_H
#define POSTPROCWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include "graphicwindow.h"
#include "mainwindow.h"
#include "rod.h"

class PostProcWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PostProcWindow(QVector<Rod> rods, QVector<QVector<float> > matrixU, QVector<QVector<float> >matrixN, QWidget *parent = 0);

private:
    QVector<Rod> rods;
    QVector<QVector<float> > matrixU;
    QVector<QVector<float> >matrixN;

    QGridLayout* layoutG;

    QLineEdit* lineEditX;
    QSpinBox* spinRod;
    QSpinBox* spinType;

    QVector<QTableWidget*> tablesOfAllCalcs;

    float funcUx(QVector<float> vecU, float x);
    float funcNx(QVector<float> vecN, float x);

    void fillTable(QTableWidget* tableOfAllCalcs, int matInd);

    float X;
    int indexOFButton;
signals:


private slots:
    void backToMenu();
    void setX();
    void paintGraph();

};

#endif // POSTPROCWINDOW_H
