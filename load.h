#ifndef LOAD_H
#define LOAD_H

class Load
{
public:
    Load();
    Load(int firstNode,float F1,bool wall);
    int firstNode;
    float F1;
    bool wall;
};

#endif // LOAD_H
