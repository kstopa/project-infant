#include "VectorCollection.h"

VectorCollection::VectorCollection()
{
    //ctor
}

void VectorCollection::Add(Vector v)
{
    this->resize(this->size() + 1, v);
}

int VectorCollection::GetBase()
{
    double max_lenght = 0.0;
    int v_pos = -1;
    for (unsigned int nV = 0; nV < this->size(); nV++)
    {
        if (this->at(nV).Module() > max_lenght)
        {
            max_lenght = this->at(nV).Module();
            v_pos = nV;
        }
    }
    return v_pos;
}

Vector* VectorCollection::GetRectBase()
{
    // Se busca el minimo i maximo X asi como el mini Y.
    double min_y = 999999999.0; double min_x = 999999999.0; double max_x = 0.0;
    for (unsigned int nV = 0; nV < this->size(); nV++)
    {
        // Min y max X.
        if (this->at(nV).P0.X < min_x) min_x = this->at(nV).P0.X;
        else if (this->at(nV).P0.X > max_x) max_x = this->at(nV).P0.X;
        if (this->at(nV).P1.X < min_x) min_x = this->at(nV).P1.X;
        else if (this->at(nV).P1.X > max_x) max_x = this->at(nV).P1.X;
        // Min Y.
        if (this->at(nV).P0.Y < min_y) min_y = this->at(nV).P0.Y;
        if (this->at(nV).P1.Y < min_y) min_y = this->at(nV).P1.Y;
    }
    Vector* v = new Vector(min_x, min_y, max_x, min_y);
    return v;
}

Vector* VectorCollection::GetRectBaseY()
{
    // Se busca el minimo i maximo X asi como el mini Y.
    double min_x = 999999999.0; double min_y = 999999999.0; double max_y = 0.0;
    for (unsigned int nV = 0; nV < this->size(); nV++)
    {
        // Min y max X.
        if (this->at(nV).P0.Y < min_y) min_y = this->at(nV).P0.Y;
        else if (this->at(nV).P0.Y > max_y) max_y = this->at(nV).P0.Y;
        if (this->at(nV).P1.Y < min_y) min_y = this->at(nV).P1.Y;
        else if (this->at(nV).P1.Y > max_y) max_y = this->at(nV).P1.Y;
        // Min Y.
        if (this->at(nV).P0.X < min_x) min_x = this->at(nV).P0.X;
        if (this->at(nV).P1.X < min_x) min_x = this->at(nV).P1.X;
    }
    Vector* v = new Vector(min_x, min_y, min_x, max_y);
    return v;
}

// Obtiene el centroide de los vertices que forman el vector.
Coordinate VectorCollection::GetCentroid()
{
    // El centroide sera coordenda media de entre todos los vertices.
    double sumX = 0.0;
    double sumY = 0.0;
    for (int nV = 0; nV < this->size(); nV++)
    {
        sumX += this->at(nV).P0.X;
        sumY += this->at(nV).P0.Y;
    }
    return Coordinate(sumX/this->size(), sumY/this->size());
}

VectorCollection::~VectorCollection()
{
    //dtor
}
