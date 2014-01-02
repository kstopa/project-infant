#ifndef ANGLE_H
#define ANGLE_H

/**
 * @class Defines and manages radiant angle values.
 *
 * @version 24.04.2011
 * @author K. Stopa
 *
 * @todo Set public double Value as a private variable.
 */
class Angle
{
	public:		
		/** Angle value */
        double Value;
        /**
         * Contructor that initialize angle to zero.
         */
        Angle();
        /**
         *  Contructor that initialize angle to determined value.
         *
         *  @param ang Value to set for angle.
         */
        Angle(double ang);
        /**
         * Gets actual angle value.
         */
        double getValue();
        /**
         * Set new angle value adjusting always in interval [0, 2PI).
         *
         * @param ang New angle value to be set.
         */
        void setValue(double ang);
        /**
         * Gets sum value of this angle value and any other angle adjusting the result to values
         * in interval [0, 2PI).
         *
         * @param ang Angle value to be added.
         * @return Angle with added value.
         */
        Angle operator + (double ang);
        /**
         * Gets sum value of this angle and any other angle adjusting the result to values
         * in interval [0, 2PI).
         *
         * @param ang Angle to be added.
         * @return Angle with added value.
         */
        Angle operator + (Angle ang);
        /**
         * Gets difference between this and any angle value adjusting the result to values
         * in interval [0, 2PI).
         *
         * @param ang Angle that will be restado from this.
         * @return Calculated angle with the diference.
         */
        Angle operator - (double ang);
        /**
         * Gets difference between this and an angle adjusting the result to values
         * in interval [0, 2PI).
         *
         * @param ang Angle that will be restado from this.
         * @return Calculated angle with the diference.
         */
        Angle operator - (Angle ang);
        /**
         * Check if any angle value is greater than this angle.
         *
         * @param ang Angle value to be compared.
         * @return True if compared angle is greater than this.
         */
        bool operator< (double ang);
        /**
         * Check if any angle is greater than this angle.
         *
         * @param ang Angle value to be compared.
         * @return True if compared angle is greater than this.
         */
        bool operator< (Angle ang);
        /**
         * Check if any angle value is lower than this angle.
         *
         * @param ang Angle value to be compared.
         * @return True if compared angle value is lower.
         */
        bool operator> (double ang);
        /**
         * Check if any angle is lower than this angle.
         *
         * @param ang Angle to be compared.
         * @return True if compared angle is lower.
         */
        bool operator> (Angle ang);
        /**
         * Check if angle is between two limit angle values that creates an sentido contrario a las agujas del reloj.
         *
         * @param lin_inf Start angle value of created arc angle.
         * @param lim_sum End angle value of created arc angle.
         *
         * @return true is this angle is created arc.
         */
        bool IsBetween(double lim_inf, double lim_sup);
        /**
         * Check if angle is between two limit angles that creates an sentido contrario a las agujas del reloj.
         *
         * @param lin_inf Start angle of created arc angle.
         * @param lim_sum End angle of created arc angle.
         *
         * @return true is this angle is created arc.
         */
        bool IsBetween(Angle lim_inf, Angle lim_sum);
        /**
         * Default class destructor.
         */
        virtual ~Angle();
    protected:
    private:
        /**
         * Gets corrected value for given angle between 0 and 2PI.
         *
         * @param ang Anlge to correct.
         * @return Normalized anlge.
         */

        double Normalize(double ang);

		

};

#endif // ANGLE_H
