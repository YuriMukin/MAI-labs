#include <iostream>
#include <cmath>
#include "renderer.h"
#include "ApproximatorPh.h"
#include "ApproximatorFF.h"


int main()
{
    double a = 10, b = 10, c = 10, d = 10;
    int acc=0;
    std::cout << "enter  top cut radius(it could be a number in between 0 and 1)" << std::endl;
    while (a > 1 || a < 0)
        std::cin >> a;
    std::cout << "\nenter  bottom cut radius(it could be a number in between 0 and 1)" << std::endl;
    while (b > 1 || b < 0)
        std::cin >> b;
    std::cout << "\nenter the distance from the center of the circle to the top cut(taking into account the sign)" << std::endl;
    while (c > 1 || c < -1)
        std::cin >> c;
    std::cout << "\nenter the distance from the center of the circle to the bottom cut(taking into account the sign)" << std::endl;
    while (d > 1 || d < -1)
        std::cin >> d;
    int tmp = 0;
    std::cout << "\nchoose a lighting model(1 - Phong 2 - flat fill" << std::endl;
    std::cin >> tmp;
    switch (tmp)
    {
    case 1:
    {
        ApproximatorPh ap(a, b, c, d);
        std::cout << "\n enter accuracy(a number from 5 to 100)" << std::endl;
        std::cin >> acc;
        ap.Approximaze(acc);
        renderer* renderer1 = new renderer(ap.PointSet, ap.weight);
    }
    case 2:
    {
        ApproximatorFF ap(a, b, c, d);
        std::cout << "\n enter accuracy(a number from 5 to 1000)" << std::endl;
        std::cin >> acc;
        ap.Approximaze(acc);
        renderer* renderer1 = new renderer(ap.PointSet, ap.weight);
    }
    default:
    {
        std::cout << "\ninvalid value" << std::endl;
        std::cin >> tmp;
    }
    }
}