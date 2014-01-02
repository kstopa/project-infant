#ifndef BASE_H
#define BASE_H


/**
 * Superclass class for vector class definition.
 */
class Base
{
    public:
		/**
		 * Constructor base.
		 */
        Base();
        /**
         * Calculates the distance of vector formed by points created
         * by defined coordinates.
         *
         * @param x0 First point X coordinate.
         * @param y0 First point Y coordinate.
         * @param x1 End point X coordinate.
         * @param y1 End point Y coordinate.
         */
        double Distance(double x0, double y0, double x1, double y1);
        /**
         * Default destructor.
         */
        virtual ~Base();
    protected:
    private:
};

#endif // BASE_H
