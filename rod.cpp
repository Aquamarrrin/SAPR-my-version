#include "rod.h"

Rod::Rod()
{
    firstNod=0;
    secondNod=0;
    len=0;
    height=0;
    A=0;
    B=0;
    E=0;
}

Rod::Rod(int fn, int sn, float len, float height, float A, float B, float E)
{
    firstNod=fn;
    secondNod=sn;
    this->len=len;
    this->height=height;
    this->A=A;
    this->B=B;
    this->E=E;
}
