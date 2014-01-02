/************************************************************************
                        main.cpp - By K. Stopa

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

/* TODO:
 * - Revisar ordenación estructura arbol!!!!.
 * - Revisar obtencion puntos similares!!!
 * - Revisar el Word que devuelve la funcion de comparación al ejecutar su script LUA.
 * - Probar reconocimiento de objetos con camara.
 */

#include <iostream>
#include <string>
#include "opencv/cv.h"
#include "opencv/highgui.h"

#include "Image.hpp"
#include "VectorCollection.h"
#include "SomethingCollection.hpp"
#include "Something.hpp"
#include "Knowleadge.hpp"
#include "Dictionary.hpp"
#include "Sight.hpp"


using namespace std;

/*VectorCollection* ProcessImage(string imgpath)
{
    cvNamedWindow(imgpath.c_str(), CV_WINDOW_AUTOSIZE);
    IplImage* img  = cvLoadImage(imgpath.c_str(), 1);
    Image* Iproc = new Image(img);
    return Iproc->Vectorize();
    cvShowImage(imgpath.c_str(), img);

    return 0;
}*/

SomethingCollection* ProcessImage(string imgpath)
{
    cvNamedWindow(imgpath.c_str(), CV_WINDOW_AUTOSIZE);
    IplImage* img  = cvLoadImage(imgpath.c_str());
    IplImage* img_bn = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 1 );
    cvCvtColor(img,img_bn,CV_BGR2GRAY);
    Image* Iproc = new Image(img_bn);
    cvShowImage(imgpath.c_str(), img_bn);
    cvWaitKey();
    cvDestroyWindow(imgpath.c_str());
    //cvReleaseImage(img);
    //cvReleaseImage(imb_bn);
    return Iproc->Vectorize();
}


// Muestra un formulario para la indentificacion de un determinado objeto.
int ShowIdentifyWindow(Something* S)
{
    if (S->ShowOriginalShape() != 0)
    {
        string txtin;
        cout << "Do you want identify this object? (y/n):";
        cin >> txtin;
        if (txtin.compare("y") == 0)
        {
            txtin = "";
            cout << "Please enter tags for object identification separated by ,(comma) without spaces: ";
            cin >> txtin;
            S->Tags->Add(txtin);
            return 0;
        }
        else
        {
            return -1; // Obj not has been indentified.
        }
    }
    else
    {
        cout << "Error showing id window." << endl;
        return -1;
    }
}

//
int ShowCamManager(Dictionary* Dict)
{
	cout << "Starting camera";
	Sight* vista = new Sight();
	if (vista->OpenEyes() >= 0)
	{
		cout << "OK" << endl;
		char key = ' ';
		cvNamedWindow("debug front", CV_WINDOW_AUTOSIZE);
		IplImage* aux = cvCreateImage( cvGetSize(vista->GetCaptureImage()), IPL_DEPTH_8U, 1 );
		cvShowImage("debug front", aux);
		CvFont font;
		cvInitFont(&font,CV_FONT_VECTOR0,0.5f,0.5f,0,1);
		string prev = "";
		do
		{
			vista->RealizeCapture();
			aux = vista->GetFrontImage();
			//cvCanny(aux, aux, 100.0f, 200.0f, 3);
			cvWaitKey(100);
			//IplImage* front = vista->GetFrontImage();
			Image* Iproc = new Image(aux);
			SomethingCollection* S = Iproc->Vectorize();
			string things = "";
			for (unsigned int nS = 0;nS < S->size() ; nS++) {
				Word* w;
				w = Dict->Compare(&S->at(nS));
				if (w != NULL)
				{
					things += " " + w->ToString();
				}
			}
			cvPutText(aux,things.c_str(),cvPoint(20,20), &font, cvScalar(150,0,0));
			cvShowImage("debug front", aux);
			//}
			Iproc = NULL;
			S = NULL;
			cvReleaseImage(&aux);
		} while(key != 'q');

	} else {
		cout << "ERR";
	}
	return 0;
}


int main(int argc, char **argv)
{

    string app_path = string(argv[0]);
    app_path.replace(app_path.length() - 6, 6, "");
    string db_path = app_path + "infant.db";
    // ruta a la base de datos en forma de puntor a
    char* db_path_chr;
    db_path_chr = new char[db_path.size() + 1];
    strcpy(db_path_chr, db_path.c_str());
    string txtIn;
    Dictionary Dict = Dictionary(app_path);
    SomethingCollection* Cosas = new SomethingCollection();
    // Loads things from database.
    Knowleadge* db = new Knowleadge(db_path_chr);
    cout << "Db opened....";
    if (db->OpenMemoryDb() >= 0)
    {
        cout << "Loading....";
        Cosas = db->Remember();
        for (int nC = 0; nC < Cosas->size(); nC++)
        	Dict.AddSomething(&Cosas->at(nC));
        db->CloseMemoryDb();
        cout << "\nWelcome to Infant Demo 0.0.2 - 2010 - 2011 - 2014 - Krzysztof Stopa - V CUSL\n";
        cout << "----------------------------------------------------------\n\n";
        cout << "Loaded " << Cosas->size() << " objects from " << db_path << endl;
    }
    while (txtIn.compare("q") != 0 )
    {
        cout << "\nType template image file name or 'cam' to work with web cam: ";
        cin >> txtIn;

        if (txtIn.compare("q") != 0)
        {
            if (txtIn.compare("cam") == 0)
            {
                ShowCamManager(&Dict);
            }
            else
            {
                // Compara todos los objetos obtenidos con la bd.
                SomethingCollection* objs = new SomethingCollection();
                objs = ProcessImage(txtIn);
                cout << "Located " << objs->size() << " things." << endl;
                if (objs != NULL)
                {
                    string answ;
                    cout<< "Object has been detected. Compare with data base? (y/n)";
                    cin >> answ;
                    if (answ.compare("y") == 0)
                    {
                        for (int nO = 0; nO < objs->size(); nO++)
                        {
                        	Dict.Compare(&objs->at(nO));
                            /*for (int nS = 0; nS < Cosas->size(); nS++)
                            {
                                cout << objs->at(nO).Compare(&Cosas->at(nS)) << " % similar to " << Cosas->at(nS).Tags->ToString() << endl;
                            }*/
                        }

                        // Identification process.
                        Knowleadge* DB = new Knowleadge(db_path_chr);
                        if (DB->OpenMemoryDb() >= 0)
                        {
                            for (int nO = 0; nO < objs->size(); nO++)
                            {
                                if (ShowIdentifyWindow(&objs->at(nO)) >= 0)
                                {
                                    // Learn this object if it has been identified.
                                    DB->Learn(&objs->at(nO));
                                    Cosas->Add(objs->at(nO));
                                }
                            }
                            DB->CloseMemoryDb();
                        } else {
                            cout << " Error al abrir la bd." << endl;
                        }

                    }
                }
                else
                {
                    cout << " There are problems to process image " << txtIn << endl;
                }
            }
        }
    }
    return 0;
}
