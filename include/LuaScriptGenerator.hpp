/************************************************************************
                        LuaScriptGenerator.h - By K. Stopa

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

#ifndef LUASCRIPTGENERATOR_H
#define LUASCRIPTGENERATOR_H

#include <iostream>
#include <fstream>
#include "SomethingCollection.hpp"

using namespace std;

/**
 * \class Creates LUA script with a serie of (geometric) rules that defines a category
 * of konwn objects and will be used for nonknown objects idetification.
 */
class LuaScriptGenerator
{
    public:
		/**
		 * Class constructor.
		 */
        LuaScriptGenerator();
        /**
         * Open LUA script that will be executed.
         * \param path Path of lua script file.
         * \return A negative integer if there are any problem.
         */
        int Open(string path);
        /**
         * Generate all posible rules that defines objects contained in sc.
         * \param sc
         * \return A negative integer if there are any problem.
         */
        int GenerateScript(SomethingCollection* sc);
        /**
         * Close prewiously opened LUA script file.
         * \return A negative value if there are any error.
         */
        int Close();
        /**
         * Default class destructor.
         */
        virtual ~LuaScriptGenerator();
    protected:
    private:
        /**
         * Stream that writes lua file.
         */
        ofstream lua_script;
        /**
         * Writes rules for similar coordinate comparation. (Rule Generation System: Exist Point)
         * \param sc Collection of objects tath will be analied to generate this rule.
         * \return True if this rule was correctly generated.
         */
        bool GenerateCoordinateRules(SomethingCollection* sc);
        /**
         * Writes rules that will check if any level exists. (Rule Generation System: Exist Level)
         * \todo Not implemented yet!
         */
        bool GenerateLevelRules(SomethingCollection* sc);
        /**
         * Writes rules that check if there are any relation with the Vertex number. (Rule Generation System: Have Min - Max Vertex)
         * \param sc Collection of objects tath will be analied to generate this rule.
         * \return True if this rule was correctly generated.
         */
        bool GenerateMinMaxVertexRules(SomethingCollection* sc);
        /**
         * Writes rules that check if objects have similar vectors.
         * \todo Not implemented yet!
         */
        bool GenerateVectorsLikeRules(SomethingCollection* sc);
        /**
         * Writes rules for check if objects in the collection have vectors vith similar module.
         * \todo Not implemented yet!
         */
        bool GenerateModuleLikeRules(SomethingCollection* sc);
        /**
         * Writes rules for check if any object have angles similar to the coincident angles in the collection.
         * \todo Not implemented yet!
         */
        bool GenerateAngleLikeRules(SomethingCollection* sc);
};

#endif // LUASCRIPTGENERATOR_H
