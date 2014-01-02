#define _USE_MATH_DEFINES
#include "Vector.h"
#include <cmath>

Vector::Vector()
{
    //ctor
    P0 = Coordinate(0.0, 0.0);
    P1 = Coordinate(0.0, 0.0);

}

Vector::Vector(Coordinate p0, Coordinate p1)
{
    P0 = p0;
    P1 = p1;
}


Vector::Vector(double x0, double y0, double x1, double y1)
{
    P0 = Coordinate(x0, y0);
    P1 = Coordinate(x1, y1);
}

//
// Devuelve el modulo del vector.
//
double Vector::Module()
{
    return sqrt(pow(P1.X - P0.X, 2.0) + pow(P1.Y - P0.Y, 2.0));
}


/*

*/

//
// Devuelve el angulo del vector con respecto a la horizontal en radianes.
//
double Vector::Angle()
{
    double dx, dy, dx0, dy0, ang;
    dx = P1.X - P0.X;
    dy = P1.Y - P0.Y;
    dy0 = dy;
    dx0 = dx;
    if (dx < 0.0) dx0 = -dx;
    if (dy < 0.0) dy0 = -dy;
    ang = atan2(dy0, dx0);
    if (dx < 0.0 & dy > 0.0) ang = M_PI - ang;
    else if ((dx < 0.0) & (dy <= 0.0)) ang = M_PI + ang;
    else if ((dx >= 0.0) & (dy < 0.0)) ang = 2.0 * M_PI - ang;
    return ang;
}

//
//
//
Vector::~Vector()
{
    //dtor
}
