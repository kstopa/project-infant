/************************************************************************
                        Dictionary.cpp - By K. Stopa

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

#include "Dictionary.hpp"
#include <iostream>

Dictionary::Dictionary()
{
    this->main = new Word();
    this->main->tag = Tag("_infant_");
}

Dictionary::Dictionary(string app_path)
{
	this->lua_path = app_path;
    this->main = new Word();
    this->main->tag = Tag("_infant_");
}

Word* Dictionary::GetFirstWord() {
	return this->main;
}

Word* Dictionary::Compare(Something* S){
	Word* aux = new Word();
	int perc = this->main->Compare(this->lua_path, S, *aux);
	if (perc > 80)
	{
		std::cout << "Parecido en un " << perc << "% a " << aux->ToString() << std::endl;
		return aux;
	}
	else
	{
		return NULL;
	}
}

void Dictionary::AddSomething(Something* S)
{
	// El objeto principal "conoce" todos los elementos.
    main->AddThing(S);
    // Se buscan si alguno de los tags ya existe y se anade el objeto al tag.
    for (int nT = 0; nT < S->Tags->size(); nT++)
    {
        Word* w = main->FindWord(S->Tags->at(nT));
        if (w != NULL){
            w->AddThing(S);
            w->GetLuaScript(lua_path);
        }
        else{
        	Word* w = new Word(S->Tags->at(nT));
        	w->AddThing(S);
        	std::cout << " Add " << S->Tags->at(nT).GetTag();
        	main->AddLowerWord(w);
        	w->GetLuaScript(lua_path);
        }

    }
    // Se reordena segun el numero de elementos de cada palabra.....
    main->Resort();
}


Dictionary::~Dictionary()
{
    //dtor
}
