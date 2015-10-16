#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMap>
#include <QPoint>
#include <QVector>
#include "rod.h"

class Construction : public QWidget
{
    Q_OBJECT
public:
    explicit Construction(QWidget *parent = 0);
    ~Construction();

    void changeMapRods(int numOfRod, QVector<float> set);
    void clearMapRods();

private:
    QTimer* timer;

    QVector<Rod> rods;

    float findMaxHeight(QVector<Rod> set);
    float findUserWidth(QVector<Rod> set);

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

private slots:
    void paintConstruction(QPainter &p);

};

#endif // CONSTRUCTION_H
