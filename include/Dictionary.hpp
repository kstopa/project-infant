/************************************************************************
                        Dictionary.h - By K. Stopa

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

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Something.hpp"
#include "Word.hpp"
#include <string>


/**
 * \class Clase que maneja las jerarquias de tags/palabras que se pueden dar al aprender objetos. Segun el numero de objetos de un determinado tag este subir'a o bajara en la jerarquia.
 * La idea principal es que una vez aprendido un conjunto especializado el sistema por si solo sea capaz de distinguir objetos que pertenezcan a la misma categoria/tag.
 */
class Dictionary
{
    public:
		Dictionary();
        Dictionary(string app_path);
        Word* GetFirstWord();
        /**
         * Generate LUA scripts for all elements in this dictionary.
         * \return A negative value if there are any error generating script.
         */
        //int GenerateScripts();
        /**
         * Adds new element to this dictionary soting it in the dictionary tree by its tags.
         * \param S Object reference to be learnd.
         * \todo Si el objeto se carga de la base de datos no generar nuevamente el script.
         */
        void AddSomething(Something* S);
        /**
         * Compare a object with known objects (calling LUA scripts for compare) in the dictionary
         * \param S something pointer to compare.
         * \return word pointer  from the dictionary that is the most similar or null if there are not any similar objetc.
         */
        Word* Compare(Something* s);
        virtual ~Dictionary();
    protected:

    private:
        Word* main;
        Word* FindWord(Tag t);
        string lua_path;

};

#endif // DICTIONARY_H
