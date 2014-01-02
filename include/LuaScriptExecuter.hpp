/************************************************************************
                        LuaScriptExecuter.h - By K. Stopa

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

#ifndef LUASCRIPTEXECUTER_H
#define LUASCRIPTEXECUTER_H



#include <string>
#include "Something.hpp"

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

/*
 * Class that execute generated lua scripts that check if any object is or not
 * similar to its that script defines.
 *
 * Es decir esta es la clase encargada de comparar nuevos objetos por medio del
 * script LUA asociado a cada categoria.
 */
class LuaScriptExecuter
{
    public:
        LuaScriptExecuter(string path);
        // Set s levels and coordinates on Lua interpreter defined by lua_state ls.
        void SetParameters(Something* s);
        // Execute a script and returns % of similarity beetween s and script defined category.
        int Execute();
        virtual ~LuaScriptExecuter();
    protected:
    private:
        // Script path.
        string s_path;
        // Lua script state
        lua_State* ls;

};

#endif // LUASCRIPTEXECUTER_H
