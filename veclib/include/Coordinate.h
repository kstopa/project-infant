#ifndef COORDINATE_H
#define COORDINATE_H

#include "Base.h"


/**
 * Class that represents two dimensional coordinate value.
 */
class Coordinate : public Base
{
    public:
		/** x coordinate value. */
        double X;
        /** y coordinate value  */
        double Y;
        /**
         * Default constructor that initialize all coordinates to zero.
         */
        Coordinate();
        /**
         * Constructor that initialize class with given values.
         *
         * @param x New x coordinate.
         * @param y New y coordinate.
         */
        Coordinate(double x, double y);
        /**
         * Gets angle that have formed vector from origin to this coordinate and the horizontal.
         *
         * @return Angle between this coordinate and horizontal.
         */
        double Angle();
        /**
         * Gets angle that have vector formed from given x,y coordinates to this coordinate and the horizontal.
         *
         * @param x Given x coordinate to create vector for angle calculation.
         * @param y Ǵiven y coordinate to create vector for angle calculation.
         * @return Angle between formed vector and the horizontal.
         */
        double Angle(double x, double y);
        /**
         * Gets angle that have vector formed from given coordinate to this coordinate and the horizontal.
         *
         * @param C coordinate to create vector for angle calculation.
         * @return Angle between formed vector and the horizontal.
         */
        double Angle(Coordinate* C);
        /**
         * Get distance from origin to this coordinate.
         *
         * @return Calculated module from zero to this coordinate.
         */
        double Distance();
        /**
         * Get distance from this coordinate to point created by x,y coordinates.
         *
         * @param x Coordinate x that forms new point.
         * @param y Coordinate y that forms new point.
         * @return Calculated module form this coordinate to new coordinate created by x,y.
         */
        double Distance(double x, double y);
        /**
         * Get distance from this coordinate to given one.
         *
         * @param C coordinate for calculate distance with.
         * @return Calculated module form this coordinate to given.
         */
        double Distance(Coordinate* C);
        /**
         * Gets distance between given coordinates.
         *
         * @param x0 Coordinate x for first point.
         * @param y0 Coordiante y for first point.
         * @param x1 Coordiante x for second point.
         * @param y1 Coordiante y for second point.
         * @return Calculated module between created points.
         */
        double Distance(double x0, double y0, double x1, double y1);
    protected:
    private:
};

#endif // COORDINATE_H

