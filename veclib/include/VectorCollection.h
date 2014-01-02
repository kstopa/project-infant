#ifndef VECTORCOLLECTION_H
#define VECTORCOLLECTION_H

#include <vector>
#include "Vector.h"
#include "Coordinate.h"

class VectorCollection : public std::vector<Vector>
{
    public:
        // Vectors();
        VectorCollection();
        void Add(Vector v);
        // Obtiene el vector mas largo del objeto que se utilizara para definir el sistema de coordendas del objeto.
        int GetBase();
        // Obtiene el vector que forma la base del bounding box que contiene todos los vectores de la coleccion.
        Vector* GetRectBase();
        Vector* GetRectBaseY();
        // Obtiene el centroide del poligono que forman los vectores que componen la coleccion tratandola como un poligono cerrado cuyos vertices son todos los P0;
        Coordinate GetCentroid();
        // ToDo... investigar la obtencion del vector base con el convex hull.
        virtual ~VectorCollection();
    protected:
    private:
};

#endif // VECTORCOLLECTION_H
