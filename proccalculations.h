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

    QVector<QVector<float> > matrixA;
    QVector<float> matrixB;
    QVector<float> matrixD;

private:
    QVector<QVector<float> > inversion(QVector< QVector<float> > A, QVector< QVector<float> > E);
    QVector<float> multi(QVector< QVector<float> > A, QVector<float> B, QVector<float> D);
};

#endif // PROCCALCULATIONS_H
