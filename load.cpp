#include "load.h"

Load::Load()
{
    firstNode=0;
    secNode=0;
    F1=0;
    F2=0;
    wall=false;
}

Load::Load(int firstNode, int secNode, float F1, float F2, bool wall)
{
    this->firstNode=firstNode;
    this->secNode=secNode;
    this->F1=F1;
    this->F2=F2;
    this->wall=wall;
}
