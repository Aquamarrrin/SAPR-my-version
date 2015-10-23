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

QDataStream & operator << ( QDataStream & stream, const Load & load )
{
    return stream
            <<load.firstNode
            <<load.F1
            <<load.wall;
}

QDataStream & operator >> ( QDataStream & stream, Load & load )
{
    return stream
            >>load.firstNode
            >>load.F1
            >>load.wall;
}
