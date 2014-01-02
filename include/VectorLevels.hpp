/************************************************************************
                        VectorLevels.h - By K. Stopa

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

#ifndef VECTORLEVELS_H
#define VECTORLEVELS_H

#include <vector>
#include "VectorLevel.hpp"



/*
 * Clase que se encarga de almacenar los datos vectoriales de un determinado nivel de externalizacion de un determinado objeto.
 * Los niveles determinan la profundidad en el objeto de un determinado contorno siendo cada uno de los niveles:
 *      0   - Vectores que relacionan los centroides de los deferentes objetos de nivel 1 encontrados.
 *      1   - Vectores que definen los contornos encontrados, es decir, los diferentes objetos que aparecen por separado.
 *      2..N- Partes internas que segun el nivel de anidamiento iran formando niveles superiores.
 */
class  VectorLevels : public std::vector<VectorLevel>
{
    public:
        VectorLevels();
        void Add(VectorLevel vl);
        virtual ~VectorLevels();
    protected:
    private:
};

#endif // VECTORLEVELS_H
