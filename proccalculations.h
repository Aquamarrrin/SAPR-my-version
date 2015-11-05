#ifndef PROCCALCULATIONS_H
#define PROCCALCULATIONS_H

#include <QVector>
#include <QDebug>
#include "rod.h"
#include "load.h"
class ProcCalculations
{
public:
    ProcCalculations();
    ProcCalculations(QVector<Rod> rods, QVector<Load> loads);

    QVector<QVector<float> > matrixA; //Матрица [А] данной конструкции
    QVector<float> matrixB; // Вектор {В}
    QVector<float> matrixD; //Искомый вектор дельт

private:
    QVector<QVector<float> > inversion(QVector< QVector<float> > A, QVector< QVector<float> > E); //Нахождение обратной матрицы
    QVector<float> multi(QVector< QVector<float> > A, QVector<float> B, QVector<float> D); // Перемножение матриц
};

#endif // PROCCALCULATIONS_H
