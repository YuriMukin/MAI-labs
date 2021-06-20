#include <fstream>
#include <iostream>
#include "renderer.h"

int main()
{
    std::ifstream in("params.txt");
    if (in.is_open())
    {
        bool r = false, p = false;
        int count = 0;
        char temp;
        while (!in.eof())
        {
            in >> temp;
            if (temp == 'r')
                r = true;
            if (temp == 'p')
                p = true;
            if (temp == ';')
                count++;
        }
        if (r)
            count--;
        if (p)
            count--;

        Dot* inArr = new Dot[count];
        in.close();
        int paream[5];
        if (!r)
        {
            std::cout << "Entre rools" << std::endl;
            for (int i = 0; i < 5; i++)
                std::cin >> paream[i];
        }
        std::ifstream in2("params.txt");
        in2.is_open();
        int count2 = 0;
        while (!in2.eof())
        {
            if (r) {
                int count1 = 0;
                char tmp;
                in2.get(tmp);
                while (tmp != ';')
                {
                    if (tmp != 'r')
                    {
                        in2 >> paream[count1];
                        count1++;
                    }
                    in2.get(tmp);
                }
                r = false;
            }
            if (p)
            {
                char tmp;
                in2.get(tmp);
                while (tmp != ';')
                {
                    in2 >> tmp;
                }
                p = false;
            }
            char tmp2;
            in2.get(tmp2);
            if (tmp2 == '.') break;

            in2 >> inArr[count2].X;
            in2 >> inArr[count2].Y;
            in2 >> inArr[count2].Z;
            count2++;
        }
        renderer* renderer1 = new renderer(paream[0], paream[1], paream[2], paream[3], paream[4], inArr, count);
    }
    else
    {
        int paream[5];
        std::cout << "File not found. Entre rools" << std::endl;
        for (int i = 0; i < 5; i++)
            std::cin >> paream[i];
        Dot* inArr = new Dot[0];
        renderer* renderer1 = new renderer(paream[0], paream[1], paream[2], paream[3], paream[4], inArr, 0);
    }
}
