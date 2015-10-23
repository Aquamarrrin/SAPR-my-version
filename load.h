#ifndef LOAD_H
#define LOAD_H

#include <QDataStream>

class Load //Класс сосредоточенной нагрузки на стержень
{
public:
    Load();
    Load(int firstNode,float F1,bool wall);
    int firstNode;
    float F1;
    bool wall;
};

#endif // LOAD_H
