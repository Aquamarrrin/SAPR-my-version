#ifndef GRAPHICWINDOW_H
#define GRAPHICWINDOW_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QGraphicsTextItem>
#include <math.h>

class GraphicWindow : public QWidget
{
    Q_OBJECT
public:
    explicit GraphicWindow(int type, float maxX, QVector<float > vecF, QWidget *parent = 0);
private:
    QGridLayout* layoutG;
    float funcUx(QVector<float> vecU, float x);
    float funcNx(QVector<float> vecN, float x);

signals:

public slots:

};

#endif // GRAPHICWINDOW_H
