/************************************************************************
                        Image.cpp - By K. Stopa

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
#define _USE_MATH_DEFINES 

#include "Image.hpp"
#include "opencv/cv.hpp"
#include "opencv/highgui.h"
#include <cmath>

#include <iostream>

#include "Vector.h";
#include "Angle.h";
#include "Coordinate.h"
#include "CoordinateSystem.h"


using namespace std;


Image::Image(IplImage* I)
{
    this->Capture = cvCloneImage(I);
}

/*
 *
 */
SomethingCollection* Image::Vectorize()
{
    SomethingCollection* objects = new SomethingCollection();
    IplImage* aux = cvCreateImage(cvGetSize(Capture), IPL_DEPTH_8U, 1 );
    //cvNamedWindow("debug", CV_WINDOW_AUTOSIZE);

    cvThreshold(Capture, aux,110,255,CV_THRESH_BINARY);
    cvCanny(aux, aux, 100.0f, 200.0f, 3);
    //cvShowImage("debug", aux);
    //cvWaitKey();
    //se buscan los bordes y se voctorializa.
    for (int x = 0; x < aux->width; x++)        // A lo ancho.
    {
        for (int y = 0; y < aux->height; y++)   // A lo alto.
        {
            if (GetPixelGrey(aux, x, y) == 255)
            {
                int level = -1;
                Something S = Something();
                Coordinate min_xy = Coordinate(x, y);
                Coordinate max_xy = Coordinate(aux->width, aux->height);
                do
                {
                    VectorCollection* V;
                    V = GetROIContourVectors(aux, min_xy, max_xy, &S);
                    if (V->size() > 2)
                    {
                        level++;
                        if (S.Shapes->size() <= level) S.Shapes->Add(VectorLevel());
                        S.Shapes->at(level).Add(*V);
                        VectorCollection vect_lev = S.SourceShape->at(S.SourceShape->size() - 1);
                        min_xy = vect_lev.GetRectBase()->P0;
                        max_xy = Coordinate(vect_lev.GetRectBase()->P1.X, vect_lev.GetRectBaseY()->P1.Y);
                    }
                    else
                    {
                        if (level - 1 >= 0)
                        {
                            if (S.SourceShape->size() > 0)
                            {
                                level = 0;
                                // Se obtiene la ultima colleccion de vectores added y se saca su bounding box.
                                VectorCollection last_vect_lev = S.SourceShape->at(0);
                                min_xy = last_vect_lev.GetRectBase()->P0;
                                max_xy = Coordinate(last_vect_lev.GetRectBase()->P1.X, last_vect_lev.GetRectBaseY()->P1.Y);
                            }
                            else level = -1;
                        }
                        else level = -1;
                    }
                } while (level >= 0);
                objects->Add(S);
            }
        }
    }
    //cvNamedWindow("debug", CV_WINDOW_AUTOSIZE);
    //cvShowImage("debug", Capture);
    //cvWaitKey();
    cvReleaseImage(&aux);
    return objects;
}



VectorCollection* Image::GetROIContourVectors(IplImage* I, Coordinate roi_min, Coordinate roi_max, Something* s)
{
    // se buscan los bordes y se voctorializa.
    VectorCollection* vectors = new VectorCollection();
    for (int x = roi_min.X; x < roi_max.X; x++)        // A lo ancho.
    {
        for (int y = roi_min.Y; y < roi_max.Y; y++)   // A lo alto.
        {
            if (GetPixelGrey(I, x, y) == 255)
            {
                // Obtenemos el contorno/vectores dentro del bounding box si se encuentran.
                vectors = GetContourVectors(I, x, y);
                // Se converte al sistema de coordendas de objeto del conjunto de vectores encontrado.
                if (vectors != NULL) {
                    if (vectors->size() > 2) {
                        //cout << " Founded " << vectors->size() << endl;
                        // Converto to Object Coordinate System.
                        Vector* dx = vectors->GetRectBase();
                        Vector* dy = vectors->GetRectBaseY();
                        s->SourceShape->Add(*vectors);
                        CoordinateSystem* CS = new CoordinateSystem(dx, dy);
                        vectors = CS->ConvertToSystem(vectors);
                        //this->DrawVectorCollectionMoved(this->Capture, vectors, cvScalar(x*y%255, x/y%255, x%255));
                        return vectors;
                    }
                }
            }
        }
    }
    return vectors;
}



VectorCollection* Image::GetContourVectors(IplImage* I, int ini_x, int ini_y)
{
    CvScalar black = {0, 0, 0};
    VectorCollection* vectors = new VectorCollection();
    bool founded = true;
    int x, y;
    x = ini_x; y = ini_y;
    while (founded)
    {
        founded = false;
        if (GetPixelGrey(I, x + 1, y - 1) == 255) { founded = true; x++; y--; } else
        if (GetPixelGrey(I, x + 1, y + 1) == 255) { founded = true; x++; y++; } else
        if (GetPixelGrey(I, x - 1, y + 1) == 255) { founded = true; x--; y++; } else
        if (GetPixelGrey(I, x - 1, y - 1) == 255) { founded = true; x--; y--; } else
        if (GetPixelGrey(I, x + 1, y) == 255) { founded = true; x++; } else
        if (GetPixelGrey(I, x, y + 1)== 255) { founded = true; y++;} else
        if (GetPixelGrey(I, x - 1, y) == 255) { founded = true; x--;} else
        if (GetPixelGrey(I, x, y - 1) == 255) { founded = true; y--; }
        if (!founded)
        {
            // Segundo nivel (fila suerior)
            if (GetPixelGrey(I, x - 2, y - 2) == 255) { founded = true; x=x-2; y=y-2;} else
            if (GetPixelGrey(I, x - 1, y - 2) == 255) { founded = true; x=x-1; y=y-2; } else
            if (GetPixelGrey(I, x, y - 2) == 255) { founded = true; y=y-2;} else
            if (GetPixelGrey(I, x + 1, y - 2) == 255) { founded = true; x=x+1; y=y-2; } else
            if (GetPixelGrey(I, x + 2, y - 2) == 255) { founded = true; x=x+2; y=y-2; } else
            // segundo nivel (fila ingerior).
            if (GetPixelGrey(I, x - 2, y + 2) == 255) { founded = true; x=x-2; y=y+2; } else
            if (GetPixelGrey(I, x - 1, y + 2) == 255) { founded = true; x=x-1; y=y+2; } else
            if (GetPixelGrey(I, x, y + 2) == 255) { founded = true; y=y+2;} else
            if (GetPixelGrey(I, x + 1, y + 2) == 255) { founded = true; x=x+1; y=y+2; } else
            if (GetPixelGrey(I, x + 2, y + 2) == 255) { founded = true; x=x+2; y=y+2; } else
            // segundo nivel (laterales)
            if (GetPixelGrey(I, x - 2, y - 1) == 255) { founded = true; x=x-2; y=y-1; } else
            if (GetPixelGrey(I, x - 2, y) == 255) { founded = true; x=x-2; } else
            if (GetPixelGrey(I, x - 2, y + 1) == 255) { founded = true; x=x-2; y=y+1; } else
            if (GetPixelGrey(I, x + 2, y - 1) == 255) { founded = true; x=x+2; y=y-1; } else
            if (GetPixelGrey(I, x + 2, y) == 255) { founded = true; x=x+2; } else
            if (GetPixelGrey(I, x + 2, y + 1) == 255) { founded = true; x=x+2; y=y+1; }   // ToDo: Establecer prioridad de seleccion
            if (founded) SetPixelLevelValue(I, ini_x, ini_y, 2, black);                   // Se borran todos los posibles vecinos de nivel 2.
        }
        if (founded)
        {
            SetPixelLevelValue(I, ini_x, ini_y, 1, black);
            Vector* V = new Vector(ini_x, ini_y, x, y);
            vectors->Add(*V);
            ini_x = x; ini_y = y;
        }
    }
    // Se simplifica los vectores.
    if (vectors->size() > 15)   // Si el borde encontrado tiene 15 pixeles o menos -> ruido.
    {
        vectors = Simplifi(vectors);
        return vectors;
    }
    else
    {
        vectors = new VectorCollection();   // si no es una mancha y pasando.. :P
        return vectors;
    }
}


int Image::GetPixelGrey(IplImage* I, int x, int y)
{
    if ((x < I->width) & (x >= 0) & (y < I->height) & (y >= 0))
    {
        return cvGet2D(I, y, x).val[0];
    }
    else return 0;
}


VectorCollection* Image::Simplifi(VectorCollection* V)
{
    if (V->size() > 2)
    {
    Angle ang_prev = Angle(V->at(0).Angle());
    const double M_PI_4_ERR = M_PI_4 + 0.1;
    VectorCollection* simple = new VectorCollection();
    Coordinate p_ini = V->at(0).P0;
    double coef_k = 1.0;
    for (int nV = 1; nV < V->size(); nV++)
    {
        //double ang_act = V->at(nV).Angle();
        Angle ang_act = Angle(V->at(nV).Angle());
        if (!ang_act.IsBetween(ang_prev - M_PI_4_ERR/coef_k, ang_prev + M_PI_4_ERR/coef_k))
        {
            Vector* v = new Vector(p_ini, V->at(nV).P0);
            simple->Add(*v);
            p_ini = V->at(nV).P0;
            ang_prev = ang_act;
            coef_k += 0.05 ;
        } else {
            Vector* v = new Vector(p_ini, V->at(nV).P1);
            ang_prev = v->Angle();
            coef_k = 1.0;
        }
    }

    // Se cierra el contorno.
    if (simple->size() > 1) {
        Vector* vclose = new Vector(simple->at(simple->size() - 1).P1, simple->at(0).P0);
        simple->Add(*vclose);
    }
        return simple;
    }
    else
    {
        return V;
    }
}

double Image::GetAvergueAngule(VectorCollection* V, int ini, int end)
{
    int v_count = 0;
    double sum_ang = 0.0;
    double exp_ang = 0.0;
    double ang = 0.0;
    for (int i = ini; i <= end; i++)
    {
        Vector* v = new Vector(V->at(ini).P0, V->at(i).P1);
        if (i != ini)
            exp_ang = (ang + v->Angle()) / 2.0;
        ang = v->Angle();
        sum_ang += ang;
        v_count++;
    }
    return sum_ang/v_count;
}


void Image::SetPixelLevelValue(IplImage* I, int x, int y, int level, CvScalar pix_val)
{
    for (int i = x - level; i <= x + level; i++)
    {
        for (int j = y - level; j <= y + level; j++)
        {
            if ((i >= 0 & i < I->width) & (j >= 0 & j < I->height))
                cvSet2D(I, j, i, pix_val);
        }

    }
}

/*
void Image::DrawVectorCollection(IplImage* I, VectorCollection* V, CvScalar Color)
{
    for (unsigned int i = 0; i < V->size(); i++)
        cvLine(I, cvPoint(V->at(i).P0.Y,V->at(i).P0.X), cvPoint(V->at(i).P1.Y, V->at(i).P1.X), Color, 1);
}


void Image::DrawVectorCollectionMoved(IplImage* I, VectorCollection* V, CvScalar Color)
{
    for (unsigned int i = 0; i < V->size(); i++)
            cvLine(I, cvPoint(V->at(i).P0.X+50, V->at(i).P0.Y+50), cvPoint(V->at(i).P1.X+50, V->at(i).P1.Y+50), Color, 1);
}*/

Image::~Image()
{
    //dtor
	cvReleaseImage(&Capture);

}
