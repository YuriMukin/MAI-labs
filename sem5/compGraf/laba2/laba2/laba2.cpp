#include <iostream>
#include <cmath>
#include "renderer.h"

int main()
{
    double cs = cos(3.1415926/4);
    double tmp = cs * 0.5;
    double tmp0 = cs * 0.4;
    GLdouble pVerts[] = {
        //bottum
        0,-0.5,0, 0,-0.5,0.5,     tmp,-0.5,tmp,
        0,-0.5,0, tmp,-0.5,tmp,   0.5,-0.5,0,
        0,-0.5,0, 0.5,-0.5,0,     tmp,-0.5,-tmp,
        0,-0.5,0, tmp,-0.5,-tmp,  0,-0.5,-0.5,
        0,-0.5,0, 0,-0.5,-0.5,    -tmp,-0.5,-tmp,
        0,-0.5,0, -tmp,-0.5,-tmp, -0.5,-0.5,0,
        0,-0.5,0, -0.5,-0.5,0,    -tmp,-0.5,tmp,
        0,-0.5,0, -tmp,-0.5,tmp,  0,-0.5,0.5,
        //top
        0,0.5,0.4,       0,0.5,0,  tmp0,0.5,tmp0,
        tmp0,0.5,tmp0,   0,0.5,0,  0.4,0.5,0,
        0.4,0.5,0,       0,0.5,0,  tmp0,0.5,-tmp0,
        tmp0,0.5,-tmp0,  0,0.5,0,  0,0.5,-0.4,
        0,0.5,-0.4,      0,0.5,0,  -tmp0,0.5,-tmp0,
        -tmp0,0.5,-tmp0, 0,0.5,0,  -0.4,0.5,0,
        -0.4,0.5,0,      0,0.5,0,  -tmp0,0.5,tmp0,
        -tmp0,0.5,tmp0,  0,0.5,0,  0,0.5,0.4,
        //further clockwise
        //1
        0,0.5,0.4,  tmp,-0.5,tmp,  0,-0.5,0.5,
        0,0.5,0.4,  tmp0,0.5,tmp0, tmp,-0.5,tmp,
        //2
        tmp0,0.5,tmp0,  0.4,0.5,0,  0.5,-0.5,0,
        tmp0,0.5,tmp0,  0.5,-0.5,0,  tmp,-0.5,tmp,
        //3
        0.4,0.5,0,  tmp0,0.5,-tmp0,  tmp,-0.5,-tmp,
        0.4,0.5,0,  tmp,-0.5,-tmp,  0.5,-0.5,0,
        //4
        tmp0,0.5,-tmp0,  0,0.5,-0.4,   0,-0.5,-0.5,
        tmp0,0.5,-tmp0,  0,-0.5,-0.5,  tmp,-0.5,-tmp,
        //5
        0,0.5,-0.4,  -tmp0,0.5,-tmp0,  -tmp,-0.5,-tmp,
        0,0.5,-0.4,  -tmp,-0.5,-tmp,   0,-0.5,-0.5,
        //6
        -tmp0,0.5,-tmp0,  -0.4,0.5,0,   -0.5,-0.5,0,
        -tmp0,0.5,-tmp0,  -0.5,-0.5,0,  -tmp,-0.5,-tmp,
        //7
        -0.4,0.5,0,  -tmp0,0.5,tmp0,  -tmp,-0.5,tmp,
        -0.4,0.5,0,  -tmp,-0.5,tmp,   -0.5,-0.5,0,
        //8
        -tmp0,0.5,tmp0,  0,0.5,0.4,   0,-0.5,0.5,
        -tmp0,0.5,tmp0,  0,-0.5,0.5,  -tmp,-0.5,tmp
    };
    int count = 0;
    for (int i = 0; i < 288; i++)
    {
        std::cout << pVerts[i] << ' ';
        count++;
        if (count == 4)
        {
            count = 0;
            std::cout << std::endl;
        }
    }
    renderer* renderer1 = new renderer(pVerts, 288);
}

