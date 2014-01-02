/************************************************************************
                        Something.h - By K. Stopa

	Infant (c) K. Stopa
	V CUSL 2010 - 2011.

	This program is free software; you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation; either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program. If not, see <http://www.gnu.org/licenses/>.

**************************************************************************/

#ifndef SOMETHING_H
#define SOMETHING_H

#include "VectorCollection.h"
#include "VectorLevels.hpp"
#include "TagCollection.hpp"
#include <string>
#include "Angle.h"

using namespace std;

class Something
{
    public:
        // Id en la db del objeto, si no ha sido guardado en la bd tendra un valor negativo.
        int ID;
        // Vectores que componen la forma del objeto.
        VectorCollection* Shape;    // v 0.0.1 obsoleto
        VectorLevels* Shapes;       // v 0.0.2
        // Original simplified vectors got when original image is prcessed. It is used for identify object by user.
        VectorLevel* SourceShape;
        // Nombre del objeto.
        string Name;
        // Angulo medio original del objeto.
        Angle AvAng;
        // Tags that define an object.
        TagCollection* Tags;

        // TODO (70065#1#): Add informacion sobre el color del objeto.
        // TODO (70065#1#): Add informaci'on contexto... es decir, en una escena observar que elementos aparecen siempre con otros objetos juntos... p.e. si se ven cubiertos es siempre tenedor + cochillo, etc.

        Something();
        Something(VectorCollection* V, string name);
        int ShowOriginalShape();
        // Compra el objeto actual y devuelve el porcentaje (0-100) de similitud.
        int Compare(Something* O);
        virtual ~Something();
    protected:
    private:
        // Compara el vector comp a org y devuelve el porcentaje de parecido.
        int CompareVectors(VectorCollection* org, VectorCollection* comp);

};

#endif // SOMETHING_H
