/************************************************************************
                        Knowleadge.h - By K. Stopa

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

#ifndef KNOWLEADGE_H
#define KNOWLEADGE_H

#include "Something.hpp"
#include "SomethingCollection.hpp"
#include "VectorCollection.h"
#include "TagCollection.hpp"

#include "sqlite3.h"
#include <string>

/*
 * Clase que se encarga del manejo de las bds y los objetos aprendidos por el systema.
 */
class Knowleadge
{
    public:
        Knowleadge(char* source_db);
        // Abre la base de datos de la aplicacion.
        int OpenMemoryDb();
        // Cierra la base de datos de la aplicacion.
        int CloseMemoryDb();
        // Almacena la informacion sobre un determinado objeto.
        int Learn(Something* S);
        // Obtiene todos los elementos aprendidos por el sistema de la bd.
        SomethingCollection* Remember();
        // Destructor
        virtual ~Knowleadge();
    protected:
    private:
        // Ruta a la base de datos.
        char* dbPath;
        // Base de datos de la app.
        sqlite3* MemoryDb;
        // Guarda los datos de un determinado objeto en la tabja things de la bd.
        int LearnThing(Something* S);
        // Guarda los datos de los vectores que componen un determiado objeto.
        int LearnVectors(VectorCollection* V, int id, int level, int vect_pos);
        // Writes on db all tags for thing which ID value it's "id".
        int LearnTags(TagCollection* T, int id);
        // Obtiene todos los elementos (sin vectores)
        SomethingCollection* RememberThings();
        // Obtiene los vectores que definen un determinado objeto segun su id.
        VectorCollection* RememberVectors(int id, int level, int vect_pos);
        // Obtiene los tags que definen el objeto de la bd segun la id del objeto.
        TagCollection* RememberTags(int id);
        // Obtiene el numero de niveles de anidamiento de un determiando objeto.
        int GetCountLevels(int id, int* lev);
        // Obtiene el numero de contornos de un determinado nivel.
        int GetCountVectorsByLeveles(int id, int level, int* vec);


};

#endif // KNOWLEADGE_H
