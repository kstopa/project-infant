/************************************************************************
                        LuaScriptExecuter.cpp - By K. Stopa

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

#include "LuaScriptExecuter.hpp"
#include "Vector.h"
#include <iostream> // Borrar!

#define lua_open()  luaL_newstate()

LuaScriptExecuter::LuaScriptExecuter(string path)
{
	ls = lua_open();
	this->s_path = path;
	luaL_openlibs(ls);
}

// Establece los parametros para compara con el script a ejecutar un determinado objeto.
void LuaScriptExecuter::SetParameters(Something* s)
{
	int elem_count = 0;
	int pnum = 0;
    lua_newtable(ls);
    for (int nL = 0; nL < s->Shapes->size(); nL++)    {
        lua_pushnumber(ls, elem_count++);
        lua_pushnumber(ls, 1000 + nL); // level code (allways >= 1000)
        lua_rawset(ls, -3);
        // Write all level coordiante data.
        for (unsigned int nC = 0; nC < s->Shapes->at(nL).size(); nC++) {
            for (unsigned  int nV = 0; nV < s->Shapes->at(nL).at(nC).size(); nV++) {
                Vector v = s->Shapes->at(nL).at(nC).at(nV);
                // X coordinate
                lua_pushnumber(ls, elem_count++); // vector cod. ending in 1 means x in 2 its y coordinate.
                lua_pushnumber(ls, v.P0.X);
                lua_rawset(ls, -3);
                // Y coordinate
                lua_pushnumber(ls, elem_count++);
                lua_pushnumber(ls, v.P0.Y);
                lua_rawset(ls, -3);
                pnum++;
            }
        }
        lua_pushnumber(ls, elem_count++);
        lua_pushnumber(ls, 9999); // end of table
        lua_rawset(ls, -3);
        lua_pushnumber(ls, 0);
        lua_pushnumber(ls,10000 + pnum); // end of table
        lua_rawset(ls, -3);
    }
    // Se añade a las variable global a nueva tabla llamada "infant"
    lua_setglobal( ls, "obj_table" );
}


int LuaScriptExecuter::Execute()
{
	int resault = 0;
    // Ejecutamos el script cargado
	luaL_dofile(ls, s_path.c_str());
	// Se obtienen los resultados almacenados en la variable "is_it" dentro del script ejecutado
	lua_getglobal(ls, "is_it");
	resault = lua_tointeger(ls, -1);
	return resault;
}



LuaScriptExecuter::~LuaScriptExecuter()
{
	lua_close(ls);
}
