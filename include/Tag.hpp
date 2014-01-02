/************************************************************************
                        Tag.h - By K. Stopa

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

#ifndef TAG_H
#define TAG_H

#include <string>

using namespace std;

class Tag
{
    public:
        Tag();
        Tag(string t);
        virtual ~Tag();
        string GetTag() { return Value; }
        void SetTag(string val) { Value = val; }
        bool operator ==(Tag T);
    protected:
    private:
        string Value;
};

#endif // TAG_H
