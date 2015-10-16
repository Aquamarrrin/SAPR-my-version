#ifndef LOAD_H
#define LOAD_H

class Load
{
public:
    Load();
    Load(int firstNode,int secNode, float F1,float F2,bool wall);
    int firstNode;
    int secNode;
    float F1;
    float F2;
    bool wall;
};

#endif // LOAD_H
