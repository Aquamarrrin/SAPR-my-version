#ifndef ROD_H
#define ROD_H

class Rod
{
public:
    Rod();
    Rod(int fn,int sn,float len,float height,float A, float B, float E);
    int firstNod;
    int secondNod;
    float len;
    float height;
    float A;
    float B;
    float E;
};

#endif // ROD_H
