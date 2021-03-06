/************************************************************************
                        Tag.cpp - By K. Stopa

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

#include "Tag.hpp"

Tag::Tag()
{
    //ctor
}



Tag::Tag(string t)
{
    this->SetTag(t);
}

bool Tag::operator ==(Tag t)
{
    if (this->Value.compare(t.GetTag()) == 0)
        return true;
    else
        return false;
}

Tag::~Tag()
{
    //dtor
}
