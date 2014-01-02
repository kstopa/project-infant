#ifndef VECTOR_H
#define VECTOR_H

#include "Coordinate.h"

/**
 * Class that represents a vector defined by initial and end point.
 */
class Vector : public Base
{
    public:
        Coordinate P0, P1;
        /**
         * Contructor that create empty vector.
         */
        Vector();
        /**
         * Constructor that create vector from two coordinates.
         *
         * @param p0 initial coordinate of defined vector.
         * @param p1 end coordinate of defined vector.
         */
        Vector(Coordinate p0, Coordinate p1);
        /**
         * Constructor that create vector from x and y values of two coordinates.
         *
         * @param
         */
        Vector(double x0, double y0, double x1, double y1);
        double Module();
        double Angle();
        virtual ~Vector();
    protected:
    private:
};

#endif // VECTOR_H
