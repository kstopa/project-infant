/************************************************************************
                        TagCollection.cpp - By K. Stopa

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

#include "TagCollection.hpp"
#include <iostream> //Brr

TagCollection::TagCollection()
{
    //ctor
}

/*
 * Constructor.
 */
void TagCollection::Add(Tag t)
{
    this->resize(this->size() + 1, t);
}

/*
 * Adds tags to collection from comma formated string.
 */
void TagCollection::Add(string tag_text)
{
    int ini = 0;
    for (int nC = 0; nC < tag_text.size(); nC++) {
        if ((tag_text[nC] == ',') | (nC == tag_text.size() - 1)) {
            if (nC == tag_text.size() - 1) nC++;
            string tag = tag_text.substr(ini, nC - ini);
            this->Add(Tag(tag));
            ini = nC + 1;
        }
    }
}

/*
 * Writes a comma formated string with all tags in collection.
 */
string TagCollection::ToString()
{
    string all_tags = "";
    for (int nT = 0; nT < this->size(); nT++)
    {
        all_tags += this->at(nT).GetTag();
        if (nT < this->size() - 1) all_tags += ",";
    }
    return all_tags;
}




TagCollection::~TagCollection()
{
    //dtor
}
