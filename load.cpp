#include "load.h"

Load::Load()
{
    firstNode=0;
    F1=0;
    wall=false;
}

Load::Load(int firstNode,float F1,bool wall)
{
    this->firstNode=firstNode;
    this->F1=F1;
    this->wall=wall;
}
