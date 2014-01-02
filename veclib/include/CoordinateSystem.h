#ifndef COORDINATESYSTEM_H
#define COORDINATESYSTEM_H

#include "Vector.h"
#include "VectorCollection.h"

/**
 * Defines a object coordinate system that it is used to compare objects.
 */
class CoordinateSystem : public Base
{
    public:
		/**
		 * Constructor that defines a basic coordinate system from two uniter perpendicular vectors.
		 */
        CoordinateSystem();
        /*
         * Constructor that defines a coordinate system from one vector and other equal
         * perpendicular vector.
         *
         * @param base Vector that defines new coordinate system.
         */
        CoordinateSystem(Vector* base);
        /**
         * Constructor that defines a coordinate system from two vectors for definition of
         * x and y axis.
         *
         * @param base_x Vector that defines X axis of new coordinate system.
         * @param base_y Vector that defines Y axis of new coordinate system.
         */
        CoordinateSystem(Vector* base_x, Vector* base_y);
        /**
         * Convert a vector from basic unary perpendicular coordinate system to defined.
         *
         * @param v Vector that will be converted.
         * @return Converted vector.
         */
        Vector* ConvertToSystem(Vector* v);
        /**
         * Converts all passed vector from basic unary perpendicular system to defined.
         *
         * @param V Collection of vectors that will be converted to definde coordinate system.
         * @return Converted collection of vectors passed to new coordiante system.
         */
        VectorCollection* ConvertToSystem(VectorCollection* V);
        /**
         * Default class destructor.
         */
        virtual ~CoordinateSystem();
    protected:
    private:
        /**
         *  Origin of coordinates point.
         *  @todo Change to coordinate class.
         */
        double dx, dy;
        /**
         * Rotation angle of X axis.
         * @todo Change to Angle class.
         */
        double alfa;
        /**
         * Unary scale factor to pass vectors from basic perpendicular unary system to defined one.
         */
        double scale_x, scale_y;

};

#endif // COORDINATESYSTEM_H
