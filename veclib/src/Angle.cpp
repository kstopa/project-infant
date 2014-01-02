#define _USE_MATH_DEFINES
#include "Angle.h"
#include <cmath>

Angle::Angle()
{
    //ctor
    Value = 0.0;
}

Angle::Angle(double ang)
{
	Value = ang;
}

Angle::~Angle()
{
    Value = 0.0;
}

double Angle::getValue() {
	return this->Value;
}

void Angle::setValue(double ang) {
	this->Value = Normalize(ang);
}

Angle Angle::operator +(double ang)
{
    return Angle(Normalize(Value + ang));
}

Angle Angle::operator +(Angle ang)
{
    return Angle(Normalize(Value + ang.getValue()));
}

Angle Angle::operator -(double ang)
{
    return Angle(Normalize(Value - ang));
}

Angle Angle::operator -(Angle ang)
{
    return Angle(Normalize(Value - ang.getValue()));
}

bool Angle::operator < (double ang)
{
    if (this->Value < Normalize(ang)) return true;
    else return false;
}

bool Angle::operator <(Angle ang)
{
    if (this->Value < ang.getValue()) return true;
    else return false;
}

bool Angle::operator >(double ang)
{
    if (this->Value > Normalize(ang)) return true;
    else return false;
}

bool Angle::operator >(Angle ang)
{
    if (this->Value > ang.Value) return true;
    else return false;
}

double Angle::Normalize(double ang)
{
    while (ang >= M_PI * 2.0)
        ang -= (M_PI * 2.0);
    while (ang < 0.0)
        ang += (M_PI * 2.0);
    return ang;
}


bool Angle::IsBetween(double lim_inf, double lim_sup)
{
    if (lim_inf > lim_sup)
    {
        if (((this->Value >= lim_inf) & (this->Value <= 2 * M_PI)) |
            ((this->Value >= 0.0) & (this->Value <= lim_sup)))
            return true;
        else
            return false;
    }
    else
    {
        if ((this->Value >= lim_inf) & (this->Value <= lim_sup))
            return true;
        else
            return false;
    }
}


bool Angle::IsBetween(Angle lim_inf, Angle lim_sup)
{
    return this->IsBetween(lim_inf.getValue(), lim_sup.getValue());
}

