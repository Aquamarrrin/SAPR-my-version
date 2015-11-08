#ifndef POSTPROCWINDOW_H
#define POSTPROCWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QTableWidget>
#include <QHeaderView>

class PostProcWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PostProcWindow(QVector<QVector<float> > matrixU,QVector<QVector<float> > matrixN, QWidget *parent = 0);

private:
    QGridLayout* layoutG;

    QTableWidget* tableOfAllCalcs;

    float funcUx(QVector<float> vecU, float x);
    float funcNx(QVector<float> vecN, float x);
signals:

public slots:


};

#endif // POSTPROCWINDOW_H
