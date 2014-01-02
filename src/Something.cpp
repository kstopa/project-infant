/************************************************************************
                        Something.cpp - By K. Stopa

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

#include "Something.hpp"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "opencv/cv.hpp" // include standard OpenCV headers, same as before
#include "opencv/highgui.h"

#include "Angle.h"
#include "CoordinateSystem.h"

using namespace std;


Something::Something()
{
    Shapes = new VectorLevels();
    Shape = new VectorCollection();
    SourceShape = new VectorLevel();
    Name = "";
    Tags = new TagCollection();
}

/* Curiosidades descbuiertas:
    - El angulo medio de los angulos que componen el contorno de un objeto es similar en objetos parecidos (lo cual es logico).
    - Objetos del mismo tipo son parecidos entre ellos en p.e. letras con letras y numeros con numeros.
    */


Something::Something(VectorCollection* V, string name)
{
    this->Shape = V;
    this->Name = name;
    Shapes = new VectorLevels();
    SourceShape = new VectorLevel();
    Tags = new TagCollection();
}


int Something::Compare(Something* S)
{
    // se compara por niveles:
    int porc_pare_elem = 0;
    int n_elem = 0;
    for (int nL = 0; nL < this->Shapes->size(); nL++)
    {
        int porc_pare_level = 0;
        int n_elem_level = 0;
        if (S->Shapes->size() > nL) // Se comparan todos los niveles iguales.
        {
            for (int nV = 0; nV < this->Shapes->at(nL).size(); nV++)
            {
                for (int nW = 0; nW < S->Shapes->at(nL).size(); nW++)
                {
                    int porc_temp = CompareVectors(&this->Shapes->at(nL).at(nV), &S->Shapes->at(nL).at(nW));
                    porc_pare_level += porc_temp;
                    n_elem_level++;
                }
            }
            if (n_elem_level > 0)
                porc_pare_elem += porc_pare_level / n_elem_level;
            n_elem++;
        }
    }
    if (n_elem > 0)
        return porc_pare_elem/n_elem;
    else
        return 0;
}


int Something::CompareVectors(VectorCollection* org, VectorCollection* comp)
{
    int v_ok_count = 0;
    for (int nV = 0; nV < org->size(); nV++)
    {
        for (int nW = 0; nW < comp->size(); nW++)
        {
            if (((org->at(nV).P0.Distance(&comp->at(nW).P0) < 10.0) | (org->at(nV).P0.Distance(&comp->at(nW).P1) < 10.0)) &
                ((org->at(nV).P1.Distance(&comp->at(nW).P0) < 10.0) | (org->at(nV).P1.Distance(&comp->at(nW).P1) < 10.0)))
            {
                v_ok_count++;
                break;
            }
        }
    }
    return v_ok_count * 100 / org->size();
}

///
int Something::ShowOriginalShape()
{
    if (this->SourceShape != NULL)
    {
        if (this->SourceShape->size() >0)
        {
            /// ToDo: optimizar.
            Coordinate pmin = this->SourceShape->at(0).GetRectBase()->P0;
            Coordinate pmax = Coordinate(this->SourceShape->at(0).GetRectBase()->P1.X, this->SourceShape->at(0).GetRectBaseY()->P1.Y);
            IplImage* I =  cvCreateImage(cvSize( pmax.X - pmin.X + 50, pmax.Y - pmin.Y + 50), IPL_DEPTH_32F, 3);
            for (int i = 0; i < SourceShape->size(); i++)
            {
                for (int nV = 0; nV < SourceShape->at(i).size(); nV++)
                    cvLine(I, cvPoint(SourceShape->at(i).at(nV).P0.X - pmin.X + 25, SourceShape->at(i).at(nV).P0.Y - pmin.Y + 25), cvPoint(SourceShape->at(i).at(nV).P1.X - pmin.X + 25, SourceShape->at(i).at(nV).P1.Y - pmin.Y + 25), cvScalar(0, 100, 200), 1);
            }

            cvNamedWindow("Original Shape", CV_WINDOW_AUTOSIZE);
            cvShowImage("Original Shape", I);
            cvWaitKey();
        }
        else
        {
            return -1;
        }

    }
    else return -1;
}





Something::~Something()
{
    //dtor
}
