/************************************************************************
                        VectorLevel.cpp - By K. Stopa

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

#include "VectorLevel.hpp"

VectorLevel::VectorLevel()
{
    //ctor
}

// Ad vector en este nivel de anidamiento.
void VectorLevel::Add(VectorCollection v)
{
    this->resize(this->size() + 1, v);
}

VectorLevel::~VectorLevel()
{
    //dtor
}
