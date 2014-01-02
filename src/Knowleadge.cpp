/************************************************************************
                        Knowleadge.cpp - By K. Stopa

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

#include "Knowleadge.hpp"
#include <iostream>
#include <sstream>


Knowleadge::Knowleadge(char* source_db)
{
    //ctor
    this->dbPath = source_db;
}


int Knowleadge::Learn(Something* S)
{
    int id_s = LearnThing(S);
    if (id_s > 0)
    {
        S->ID = id_s;
        int err = 0;
        err += this->LearnTags(S->Tags, S->ID);
        for (int nL = 0; nL < S->Shapes->size(); nL++)
        {
            for (int nV = 0; nV < S->Shapes->at(nL).size(); nV++)
                err += this->LearnVectors(&S->Shapes->at(nL).at(nV), id_s, nL, nV);
        }
        return err;
    }
    return id_s;
}


int Knowleadge::LearnThing(Something* S)
{
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(this->MemoryDb,"INSERT INTO things VALUES (?,?,?);",-1,&stmt,NULL) == SQLITE_OK)
    {
        sqlite3_bind_null(stmt,1);
        sqlite3_bind_text(stmt,2,S->Name.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_double(stmt,3, S->AvAng.Value);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);
        return sqlite3_last_insert_rowid(this->MemoryDb);   //Devuelve el id del objeto insertado.
    } else {
        return -1;
    }
}


int Knowleadge::LearnVectors(VectorCollection* V, int id, int level, int vect_pos)
{
    sqlite3_stmt* stmt;
    int err = 0; //numero de elementos insertados correctamente.
    for (int nV = 0; nV < V->size(); nV++)
    {
        if (sqlite3_prepare_v2(this->MemoryDb,"INSERT INTO vectors VALUES (?,?,?,?,?,?,?,?);",-1,&stmt,NULL) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_int(stmt, 2, level);
            sqlite3_bind_int(stmt, 3, vect_pos);
            sqlite3_bind_int(stmt, 4, nV);
            sqlite3_bind_double(stmt, 5, V->at(nV).P0.X);
            sqlite3_bind_double(stmt, 6, V->at(nV).P0.Y);
            sqlite3_bind_double(stmt, 7, V->at(nV).P1.X);
            sqlite3_bind_double(stmt, 8, V->at(nV).P1.Y);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        } else err = -1;
    }
    return err;
}

// Load tags from db.
int Knowleadge::LearnTags(TagCollection* T, int id) {
    sqlite3_stmt* stmt;
    int err = 0;
    for (int nT = 0; nT < T->size(); nT++)
    {
        if (sqlite3_prepare_v2(this->MemoryDb, "INSERT INTO tags VALUES (?, ?);", -1,&stmt,NULL) == SQLITE_OK)
        {
            sqlite3_bind_int(stmt, 1, id);
            sqlite3_bind_text(stmt,2, T->at(nT).GetTag().c_str(),-1,SQLITE_STATIC);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
        else err = -1;
    }
    return err;
}

// Carga de la bd todos los objetos conocidos.
SomethingCollection* Knowleadge::Remember()
{
    SomethingCollection* sc = new SomethingCollection();
    sc = RememberThings();
    if (sc != NULL)
    {
        for (int nS = 0; nS < sc->size(); nS++)
        {
            sc->at(nS).Tags = RememberTags(sc->at(nS).ID);
            int levels;
            GetCountLevels(sc->at(nS).ID, &levels); // Error raro no devolvia bien el entero la funcion por eso esta la referencia a entero en la cabecera...
            for (int nL = 0; nL < levels ; nL++)
            {
                int vectors;
                GetCountVectorsByLeveles(sc->at(nS).ID, nL, &vectors); // Error raro no devolvia bien el entero la funcion por eso esta la referencia a entero en la cabecera..
                VectorLevel L = VectorLevel();
                for (int nV = 0; nV < vectors ; nV++)
                {
                    VectorCollection* V = new VectorCollection();
                    V = RememberVectors(sc->at(nS).ID, nL, nV);
                    L.Add(*V);
                }
                sc->at(nS).Shapes->Add(L);
            }
        }
        return sc;
    } else {
        return NULL;
    }
}


//
SomethingCollection* Knowleadge::RememberThings()
{
    SomethingCollection* Things = new SomethingCollection();
    sqlite3_stmt * stmt;
    if (sqlite3_prepare_v2(this->MemoryDb,"SELECT * FROM things;",-1,&stmt,NULL) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            Something S = Something();
            S.ID = sqlite3_column_int(stmt, 0);
            S.Name = std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)));  // cast from unsigned const char* to string.
            S.AvAng = sqlite3_column_double(stmt, 2);
            Things->Add(S);
        }
        sqlite3_finalize(stmt);
        return Things;
    } else {
        return NULL;
    }
}

//
TagCollection* Knowleadge::RememberTags(int id)
{
    TagCollection* tags = new TagCollection();
    sqlite3_stmt* stmt;
    ostringstream id_string; id_string << id;
    string cmd = "SELECT * FROM tags WHERE id=" + id_string.str() + ";";
    if (sqlite3_prepare_v2(this->MemoryDb, cmd.c_str(),-1,&stmt,NULL) == SQLITE_OK)
    {
        while (sqlite3_step(stmt) == SQLITE_ROW)
        {
            tags->Add(Tag(std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)))));
        }
        sqlite3_finalize(stmt);
        return tags;
    }
    else
        return NULL;
}

// Carga la informacion de todos los vectores almacenados para definir un determinado objeto.
VectorCollection* Knowleadge::RememberVectors(int id, int level, int vect_pos)
{
    sqlite3_stmt * stmt;
    ostringstream id_string; id_string << id;
    ostringstream lev_string; lev_string << level;
    ostringstream vct_string; vct_string << vect_pos;
    // Numero de elementos para escalar el vector de vectores.
    string cmd = "SELECT COUNT(*) FROM vectors WHERE id=" + id_string.str() + " AND level=" + lev_string.str() + " AND vct=" + vct_string.str() + ";";
    if (sqlite3_prepare_v2(this->MemoryDb, cmd.c_str(),-1,&stmt,NULL) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            int n_elem = sqlite3_column_int(stmt, 0);
            VectorCollection* Shape = new VectorCollection();
            Shape->resize(n_elem, Vector());
            sqlite3_finalize(stmt);
            string cmd2 = "SELECT * FROM vectors WHERE id=" + id_string.str() +  " AND level=" + lev_string.str() + " AND vct=" + vct_string.str() + ";";
            if (sqlite3_prepare_v2(this->MemoryDb, cmd2.c_str(), -1, &stmt, NULL) == SQLITE_OK)
            {
                while (sqlite3_step(stmt) == SQLITE_ROW)
                {
                    Vector v = Vector();
                    int pos = sqlite3_column_int(stmt, 3);
                    v.P0.X = sqlite3_column_double(stmt, 4);
                    v.P0.Y = sqlite3_column_double(stmt, 5);
                    v.P1.X = sqlite3_column_double(stmt, 6);
                    v.P1.Y = sqlite3_column_double(stmt, 7);
                    Shape->at(pos) = v;
                }
                return Shape;
            } else {
                return NULL;
            }
        } else {
            return NULL;
        }
    } else {
        return NULL;
    }
}

int Knowleadge::GetCountLevels(int id, int* lev)
{
    sqlite3_stmt * stmt;
    ostringstream id_string; id_string << id;
    string cmd = "SELECT COUNT(DISTINCT level) FROM vectors WHERE id=" + id_string.str() + ";";
    if (sqlite3_prepare_v2(this->MemoryDb, cmd.c_str(), -1, &stmt, NULL) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            *lev = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return *lev;
        }
        else return -1;
    }
}

int Knowleadge::GetCountVectorsByLeveles(int id, int level, int* vec)
{
    sqlite3_stmt * stmt;
    ostringstream id_string; id_string << id;
    ostringstream lev_string; lev_string << level;
    string cmd = "SELECT COUNT(DISTINCT vct) FROM vectors WHERE id=" + id_string.str() + " AND level=" + lev_string.str() + ";"; //+ " GROUP BY level, vct ;";
    if (sqlite3_prepare_v2(this->MemoryDb, cmd.c_str(), -1, &stmt, NULL) == SQLITE_OK)
    {
        if (sqlite3_step(stmt) == SQLITE_ROW)
        {
            *vec = sqlite3_column_int(stmt, 0);
            sqlite3_finalize(stmt);
            return *vec;
        }
        else return -1;
    }
}



// Abre la conexion la db.
int Knowleadge::OpenMemoryDb()
{
    int rc;
    rc = sqlite3_open(dbPath, &this->MemoryDb);
    if( rc ){
        sqlite3_close(this->MemoryDb);
        return -1;
    } else {
        return 0;
    }
}

// Cierra la bd.
int Knowleadge::CloseMemoryDb()
{
    if (sqlite3_close(this->MemoryDb) == SQLITE_OK)
        return 0;
    else
        return -1;
}



Knowleadge::~Knowleadge()
{
    //dtor
}
