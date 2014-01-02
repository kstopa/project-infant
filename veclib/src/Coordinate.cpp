#define _USE_MATH_DEFINES
#include "Coordinate.h"
#include <cmath>


Coordinate::Coordinate()
{
    X = 0.0;
    Y = 0.0;
}


Coordinate::Coordinate(double x, double y)
{
    X = x;
    Y = y;
}


//
// Devuelve el angulo del vector con respecto al origen de coordenadas y la horizontal en radianes.
//
double Coordinate::Angle()
{
    //err!!!
    double dx, dy, dx0, dy0, ang;
    dx = X;
    dy = Y;
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

double Coordinate::Angle(double x, double y)
{
    double dx, dy, dx0, dy0, ang;
    dx = x - X;
    dy = y - Y;
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


double Coordinate::Angle(Coordinate* C)
{
    return Angle(C->X, C->Y);
}

//
// Distancia del punto al origen de coordendas.
//
double Coordinate::Distance()
{
    return sqrt(X*X + Y*Y);
}

double Coordinate::Distance(double x, double y)
{
    return Distance(X, Y, x, y);
}

double Coordinate::Distance(Coordinate* C)
{
    return Distance(X, Y, C->X, C->Y);
}

double Coordinate::Distance(double x0, double y0, double x1, double y1)
{
    return sqrt(((x1 - x0)*(x1 - x0)) + ((y1 - y0)*(y1 - y0)));
}

