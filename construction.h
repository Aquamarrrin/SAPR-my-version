#ifndef CONSTRUCTION_H
#define CONSTRUCTION_H

#include <QWidget>
#include <QPainter>
#include <QTimer>
#include <QMap>
#include <QPoint>
#include <QVector>
#include "rod.h"
#include "load.h"

class Construction : public QWidget
{
    Q_OBJECT
public:
    explicit Construction(QWidget *parent = 0);
    ~Construction();

    void changeMapRods(int numOfRod, QVector<float> set);
    void clearMapRods();

    void changeMapLoads(QVector<float> set);
    void clearMapLoads();

private:
    QTimer* timer;

    QVector<Rod> rods;
    QVector<Load> loads;

    float findMaxHeight(QVector<Rod> set);
    float findUserWidth(QVector<Rod> set);

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

private slots:
    void paintConstruction(QPainter &p);
    void paintRods(QPainter &p, float koeffH,float koeffW);
    void paintLoads(QPainter &p);
    void drawArrow(QPainter &p, float x1, float y1, float x2, float y2, float h);

};

#endif // CONSTRUCTION_H
