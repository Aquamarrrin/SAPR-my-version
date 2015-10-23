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

    void changeMapRods(int numOfRod, QVector<float> set);  //Добавляем параметры стержней в вектор
    void clearMapRods(); //Очищаем вектор стержней

    void changeMapLoads(QVector<float> set);  //Добавляем параметры нагрузок в вектор
    void clearMapLoads();  //Очищаем вектор нагрузок

private:
    QTimer* timer;

    QVector<Rod> rods;
    QVector<Load> loads;

    float findMaxHeight(QVector<Rod> set); //Находим максимальную высоту в векторе стержней
    float findUserWidth(QVector<Rod> set); //Суммируем пользовательскую ширину для получения правильных коэффициентов

    float heightMy;

protected:
    void paintEvent(QPaintEvent *);
signals:

public slots:

private slots:
    void paintConstruction(QPainter &p);  //Собственно отрисовка конструкции
    void paintLoads(QPainter &p, float koeffH, float koeffW);  //Отрисовка нагрузок на стержни
    void drawArrow(QPainter &p, float x1, float y1, float x2, float y2, float h); //Отрисовка стрелок
    void drawWall(QPainter &p, float x); //Отрисовка заделок

};

#endif // CONSTRUCTION_H
