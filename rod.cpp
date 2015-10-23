#include "rod.h"

Rod::Rod()
{
    firstNod=0;
    secondNod=0;
    len=0;
    height=0;
    E=0;
    coord=-1;
}

Rod::Rod(int fn, int sn, float len, float height, float E,float coord)
{
    firstNod=fn;
    secondNod=sn;
    this->len=len;
    this->height=height;
    this->E=E;
    this->coord=coord;
}

QDataStream & operator << ( QDataStream & stream, const Rod & rod )
{
    return stream
            <<rod.firstNod
            <<rod.secondNod
            <<rod.len
            <<rod.height
            <<rod.E
            <<rod.coord;
}

QDataStream & operator >> ( QDataStream & stream, Rod & rod )
{
    return stream
            >>rod.firstNod
            >>rod.secondNod
            >>rod.len
            >>rod.height
            >>rod.E
            >>rod.coord;
}
