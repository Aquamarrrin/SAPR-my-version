#ifndef ROD_H
#define ROD_H

#include <QDataStream>

class Rod //Класс стержня, содержащий его параметры
{
public:
    Rod();
    Rod(int fn, int sn, float len, float height, float E, float coord);
    int firstNod;
    int secondNod;
    float len;
    float height;
    float Fx;
    float E;
    float coord;
    float sigma;
};

#endif // ROD_H
