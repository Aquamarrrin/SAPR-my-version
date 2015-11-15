#ifndef POSTPROCWINDOW_H
#define POSTPROCWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
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

    QTableWidget* tableOfAllCalcs;

    float funcUx(QVector<float> vecU, float x);
    float funcNx(QVector<float> vecN, float x);

    void fillTable();
signals:

private slots:
    void backToMenu();

};

#endif // POSTPROCWINDOW_H
