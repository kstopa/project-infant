/************************************************************************
                        SomethingCollection.cpp - By K. Stopa

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

#include "SomethingCollection.hpp"

SomethingCollection::SomethingCollection()
{
    //ctor
}


void SomethingCollection::Add(Something s)
{
    this->resize(this->size() + 1, s);
}

vector<Coordinate> SomethingCollection::GetSimilarPoints()
{
    // ToDo: Se toma como base el objeto con mas vectores.
    vector<Coordinate> sim_coor = vector<Coordinate>();
    const int base_t = 0;
    for (int nL0 = 0; nL0 < this->at(base_t).Shapes->size(); nL0++)
    {
        for (int nVC0 = 0; nVC0 < this->at(base_t).Shapes->at(nL0).size(); nVC0++)
        {

            for (int nV0 = 0; nV0 < this->at(base_t).Shapes->at(nL0).at(nVC0).size(); nV0++)
            {
                bool addedP0 = false;
                bool addedP1 = false;
                // Compare with the rest of vector and itself.
                for (int nS = 0; nS < this->size(); nS++)   // objetos
                {
                    for (int nL = 0; nL < this->at(nS).Shapes->size(); nL++)    // niveles
                    {
                        for (int nVC = 0; nVC < this->at(nS).Shapes->at(nL).size(); nVC++)  // vectores de coordendas
                        {
                            for (int nV = 0; nV < this->at(nS).Shapes->at(nL).at(nVC).size(); nV++) //coordendas.
                            {
                                /// ToDo: en vez de add el primero mejor calcular el punto medio entre todos los putnos parecidos encontrados.
                                if (!addedP0){
                                    if ((this->at(base_t).Shapes->at(nL0).at(nVC0).at(nV0).P0.Distance(&this->at(nS).Shapes->at(nL).at(nVC).at(nV).P0) < 10.0) |
                                        (this->at(base_t).Shapes->at(nL0).at(nVC0).at(nV0).P0.Distance(&this->at(nS).Shapes->at(nL).at(nVC).at(nV).P1) < 10.0))
                                    {
                                        sim_coor.resize(sim_coor.size() + 1, this->at(base_t).Shapes->at(nL0).at(nVC0).at(nV0).P0);
                                        addedP0 = true;
                                    }
                                }
                            }
                            if  ((addedP1) | (addedP0)) break;
                        }
                        if  ((addedP1) | (addedP0)) break;
                    }
                    if  ((addedP1) | (addedP0)) break;
                }
            }
        }
    }
    /// ToDo: Eliminar duplicados parecidos o no anadir si ya existe parecido.
    return sim_coor;
}

/*
 * Genera niveles a partir de puntos similares en los diferentes objetos de la colecion.
 *
 */
VectorLevels SomethingCollection::GetSimilarLevels()
{
    for (int nO = 0; nO < this->size(); nO++)
    {
        return VectorLevels();
    }

}


SomethingCollection::~SomethingCollection()
{
    //dtor
}
