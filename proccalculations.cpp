#include "proccalculations.h"

ProcCalculations::ProcCalculations()
{
}


ProcCalculations::ProcCalculations(QVector<Rod> rods,QVector<Load> loads)
{
    if(rods.size()!=0 && loads.size()!=0)
    {
        matrixA.resize(rods.size()+1);
        for(int i=0;i<rods.size()+1;i++)
        {
            matrixA[i].resize(rods.size()+1);
            for(int j=0;j<rods.size()+1;j++)
            {
                matrixA[i][j]=0;
            }
        }
        matrixA[0][0]=(rods[0].height * rods[0].E)/(rods[0].len);
        for(int mI=1;mI<rods.size();mI++)
        {
            matrixA[mI][mI-1]=-(rods[mI-1].height * rods[mI-1].E)/(rods[mI-1].len);
            matrixA[mI][mI]=(rods[mI-1].height * rods[mI-1].E)/(rods[mI-1].len)+ (rods[mI].height * rods[mI].E)/(rods[mI].len);
            matrixA[mI-1][mI]=-(rods[mI-1].height * rods[mI-1].E)/(rods[mI-1].len);
        }
        matrixA[rods.size()][rods.size()-1]=-(rods[rods.size()-1].height * rods[rods.size()-1].E)/(rods[rods.size()-1].len);
        matrixA[rods.size()][rods.size()]=(rods[rods.size()-1].height * rods[rods.size()-1].E)/(rods[rods.size()-1].len);
        matrixA[rods.size()-1][rods.size()]=-(rods[rods.size()-1].height * rods[rods.size()-1].E)/(rods[rods.size()-1].len);

        qDebug()<<matrixA;

        QVector<Load> tmpLoads;
        tmpLoads.resize(rods.size()+1);
        for(int i=0;i<tmpLoads.size();i++)
        {
            Load l(i+1,0,0);
            tmpLoads[i]=l;
        }
        for(int i=0;i<loads.size();i++)
        {
            tmpLoads[loads[i].firstNode-1].firstNode=loads[i].firstNode;
            tmpLoads[loads[i].firstNode-1].wall=loads[i].wall;
            tmpLoads[loads[i].firstNode-1].F1=loads[i].F1;
        }

        matrixB.resize(rods.size()+1);
        for(int i=0;i<rods.size()+1;i++)
        {
            matrixB[i]=0;
        }
        matrixB[0]=(rods[0].Fx * rods[0].len)/2 + tmpLoads[rods[0].firstNod-1].F1;
        for(int i=1;i<rods.size();i++)
        {
            matrixB[i]=(rods[i-1].Fx * rods[i-1].len)/2 +(rods[i].Fx * rods[i].len)/2 + tmpLoads[rods[i].firstNod-1].F1;
        }
        matrixB[rods.size()]=(rods[rods.size()-1].Fx * rods[rods.size()-1].len)/2 + tmpLoads[rods[rods.size()-1].secondNod-1].F1;

        qDebug()<<matrixB;

        matrixD.resize(rods.size()+1);
        for(int i=0;i<tmpLoads.size();i++)
        {
            if(tmpLoads[i].wall!=0)
            {
                matrixD[i]=0;
                for(int j=0;j<matrixA[i].size();j++)
                    matrixA[i][j]=0;
                matrixA[i][i]=1;
                matrixB[i]=0;
                if(i==0)
                {
                    matrixA[i+1][i]=0;
                    matrixA[i][i+1]=0;
                }
                else
                    if(i==tmpLoads.size()-1)
                    {
                        matrixA[i-1][i]=0;
                        matrixA[i][i-1]=0;
                    }
                    else
                    {
                        matrixA[i-1][i]=0;
                        matrixA[i][i-1]=0;
                        matrixA[i+1][i]=0;
                        matrixA[i][i+1]=0;
                    }
            }
        }



        qDebug()<<matrixA;
        QVector< QVector<float> > matrixE;
        matrixE.resize(rods.size()+1);
        for(int i=0;i<rods.size()+1;i++)
        {
            matrixE[i].resize(rods.size()+1);
            for(int j=0;j<rods.size()+1;j++)
            {
                matrixE[i][j]=0;
            }
            matrixE[i][i]=1;
        }

        matrixE=inversion(matrixA,matrixE);
        matrixD=multi(matrixE,matrixB,matrixD);

        qDebug()<<matrixD;

        //Заполняем коэффициенты Ux для каждого стержня конструкции
        for(int i=0;i<rods.size();i++)
        {
            QVector<float> vec;
            vec.push_back(matrixD[i]);
//            qDebug()<<matrixD[i+1]<<" - "<<matrixD[i]<<" = "<<matrixD[i+1]-matrixD[i];
            vec.push_back((matrixD[i+1]-matrixD[i])/rods[i].len);
            vec.push_back((rods[i].Fx*rods[i].len)/(2*rods[i].E*rods[i].height));
            vec.push_back(1/rods[i].len);

            matrixU.push_back(vec);
        }

        //Заполняем коэффициенты Nx для каждого стержня конструкции
        for(int i=0;i<rods.size();i++)
        {
            QVector<float> vec;
            vec.push_back((rods[i].E*rods[i].height)*(matrixD[i+1]-matrixD[i])/rods[i].len);
            vec.push_back((rods[i].Fx*rods[i].len)/2);
            vec.push_back(2/rods[i].len);

            matrixN.push_back(vec);
        }

        //qDebug()<<matrixU;
        //qDebug()<<matrixN;
    }
}

QVector<QVector<float> > ProcCalculations::inversion(QVector<QVector<float> > A, QVector<QVector<float> > E)
{
    float temp;

    for (int k = 0; k < A.size(); k++)
    {
        temp = A[k][k];

        for (int j = 0; j < A.size(); j++)
        {
            A[k][j] /= temp;
            E[k][j] /= temp;
        }

        for (int i = k + 1; i < A.size(); i++)
        {
            temp = A[i][k];

            for (int j = 0; j < A.size(); j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    for (int k = A.size() - 1; k > 0; k--)
    {
        for (int i = k - 1; i >= 0; i--)
        {
            temp = A[i][k];

            for (int j = 0; j < A.size(); j++)
            {
                A[i][j] -= A[k][j] * temp;
                E[i][j] -= E[k][j] * temp;
            }
        }
    }

    return E;
}

QVector<float> ProcCalculations::multi(QVector<QVector<float> > A, QVector<float> B, QVector<float> D)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            D[i] += A[i][j] * B[j];
        }
        D[i]*=10000;
        D[i]=round(D[i]);
        D[i]/=10000;/*
        qDebug()<<D[i];
        qDebug()<<" ------ ";*/
    }

    return D;
}

