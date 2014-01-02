/************************************************************************
                        Image.h - By K. Stopa

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

#ifndef IMAGE_H
#define IMAGE_H


#include "opencv/cv.hpp" // include standard OpenCV headers, same as before
#include "opencv/highgui.h"


#include "Coordinate.h"
#include "VectorCollection.h"
#include "VectorLevel.hpp"
#include "VectorLevels.hpp"
#include "Something.hpp"
#include "SomethingCollection.hpp"

/*
 * Clase que se encarga de manejar y procesar las imagenes obtenidas para su comprension.
 */
class Image
{
    public:
        IplImage* Capture;
        Image(IplImage* I);
        // Vectoriza la imagen transofrandola al sistema de coordendas de la imagen.
        // VectorCollection* Vectorize();
        SomethingCollection* Vectorize();
        // Vectorializa todos los objetos de la imagen que contiene la clase transformandolos al sistema de coordendas de la imagen.
        VectorLevels* VectorizeByLeveles();
        // Quitar de aqui..
        void DrawVectorCollection(IplImage* I, VectorCollection* V, CvScalar Color);
        // Quitar o cmbiar.
        void DrawVectorCollectionMoved(IplImage* I, VectorCollection* V, CvScalar Color);
        virtual ~Image();
    protected:
    private:
        // Simplifica los vectores obtenidos en la vecotirzacion.
        VectorCollection* Simplifi(VectorCollection* V);
        // Obtiene el contorno vectorizado desde un punto inicial x, y hasta que no encuentra mas vecions.
        // I, imagen preconvertida pro Canny.
        // ini_x : coordendada x inicial de la busqueda.
        // ini_y : coordendada y inicial de la busqueda.
        VectorCollection* GetContourVectors(IplImage* I, int ini_x, int ini_y);

        VectorCollection* GetROIContourVectors(IplImage* I, Coordinate roi_min, Coordinate roi_max, Something* s);
        // Obtiene el angulo medio que tienen con respecto a la horizontal los vectores que se forman entre el punto P0 del vector V[ini] y
        // cada punto final entre V[ini] y V[fin].
        // V: colleccion de vectores con la que se trabaja.
        // ini: vector de inicio a partir de cual se cualcula el angulo medio.
        // fin: vector final hasta el cual se tiene en cuenta a la hora de calcular el
        double GetAvergueAngule(VectorCollection* V, int ini, int end);
        //
        void SetPixelLevelValue(IplImage* I, int x, int y, int level, CvScalar pix_val);
        // Obtiene el valor del priemr canal en una imagen en b/n.
        int GetPixelGrey(IplImage* I, int x, int y);

};

#endif // IMAGE_H
