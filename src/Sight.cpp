/************************************************************************
                        Sight.cpp - By K. Stopa

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

#include "Sight.hpp"
#include "Image.hpp"

#include <iostream>

Sight::Sight() {
	// TODO Auto-generated constructor stub
	//camera = cvCaptureFromCAM(0);
	capture = NULL;
	back = NULL;
}

int Sight::OpenEyes(){
	capture = cvCreateImage(cvSize(400,300), IPL_DEPTH_8U, 1 );
	camera = cvCaptureFromCAM(0);
	if (camera != NULL) {
		std::cout << "Setting back\n";
		this->RealizeCapture();
		this->UpdateBackground();
		this->imgsize = cvGetSize(this->capture);
		return 0;
	} else {
		return -1;
	}
}

SomethingCollection* Sight::GetViewObjects() {
	if ((back != NULL) & (capture != NULL)) {

		IplImage* front = GetFrontImage();
		Image* Iproc = new Image(front);
		return Iproc->Vectorize();
		cvReleaseImage(&front);	// ERRR
	} else {
		return NULL;
	}
}

IplImage* Sight::GetCaptureImage(){
	return this->capture;
}

int Sight::RealizeCapture() {
	if (camera != NULL) {
		IplImage* temp = cvQueryFrame(camera);
		cvFillImage(capture, 0.0);
		IplImage* noscale = cvCreateImage(cvGetSize(temp), IPL_DEPTH_8U, 1 );
		//cvWaitKey(100);
		if (temp != NULL) {
			cvCvtColor(temp, noscale, CV_BGR2GRAY);
			//use cvResize to resize source to a destination image
			cvResize(noscale, capture);
			cvReleaseImage(&noscale);
			return 0;
		} else {
			return -1;	// Problems with camera.
		}
	} else {
		return -1; // Camera not initialized.
	}
}



/*
 * Updates image that is used as background for filter information to process.
 */
void Sight::UpdateBackground() {
	// ToDo: Cambiar por calculos estadisticos de los cambios producidos en una imagen temporal.
	int nF = 0;
	while (nF < 100)
	{
		if (this->RealizeCapture() >= 0)
			nF++;
	}
	this->back = cvCloneImage(this->capture);
	cvErode(this->back, this->back, NULL, 1);
}

/*
 * Get image that results from delete background data from last captured image.
 */
IplImage* Sight::GetFrontImage() {
	IplImage* out = cvCreateImage( cvGetSize(this->capture), IPL_DEPTH_8U, 1 );
	cvErode(this->capture, this->capture, NULL, 1);
	CvScalar  white = {255, 0, 0, 0};
	CvScalar C0 = {0, 0, 0, 0};
	CvScalar C1 = {20, 0, 0, 0};
	CvScalar C2 = {40, 0, 0, 0};
	CvScalar C3 = {60, 0, 0, 0};
	CvScalar C4 = {80, 0, 0, 0};
	CvScalar C5 = {100, 0, 0, 0};
	int pix_ctrl1 = GetImagePixelAvergueColor(this->back, 4, 4);
	int pix_ctrl2 = GetImagePixelAvergueColor(this->capture, 4, 4);
	for (int x = 0; x < imgsize.width; x++)
	{
		for (int y = 0; y < imgsize.height; y++)
		{
			int bn_org, bn_dif;
			//bn_org = cvGet2D(this->back, y, x).val[0];
			//bn_dif = cvGet2D(this->capture, y, x).val[0];
			bn_org = GetImagePixelAvergueColor(this->back, x, y) - (pix_ctrl1 - pix_ctrl2);
			bn_dif = GetImagePixelAvergueColor(this->capture, x, y);
			// Si el color es parecido se pone blanco si no, no es fondo y se establece el color original.
			if ((bn_dif >= bn_org - 25)  & (bn_dif <= bn_org + 25))	{
				cvSet2D(out, y, x, white);
			} else {
				//cvSet2D(out, y, x, cvGet2D(this->capture, y, x));
				if (bn_dif < 40)
					cvSet2D(out, y, x, C0);//cvGet2D(this->capture, y, x));
				else if (bn_dif < 80)
					cvSet2D(out, y, x, C0);
				else if (bn_dif < 120)
					cvSet2D(out, y, x, C3);
				else if (bn_dif < 160)
					cvSet2D(out, y, x, C3);
				else if (bn_dif < 200)
					cvSet2D(out, y, x, C5);
				else
					cvSet2D(out, y, x, C5);
			}
		}
	}

	return out;
}

int Sight::GetImagePixelAvergueColor(IplImage* I, int x, int y) {
	int tot = 5;
	int pix_base = cvGet2D(I, y, x).val[0];
	int u,d,l,r;
	//left
	if (x > 0) { l = cvGet2D(I, y, x - 1).val[0]; }
	else { l = 0; tot--; }
	//right
	if (x < imgsize.width - 1) { r = cvGet2D(I, y, x + 1).val[0]; }
	else { r = 0; tot--; };
	// up
	if (y > 0) { u = cvGet2D(I, y - 1, x).val[0]; }
	else { u = 0; tot--; };
	// down
	if (y < imgsize.height - 1) { u = cvGet2D(I, y + 1, x).val[0]; }
	else { d = 0; tot--; }
	return (u + d + l + r + pix_base) / tot;
	/*int pix_base = cvGet2D(I, y, x).val[0];
	int pix_ctrl1 = cvGet2D(I, 4, 4).val[0];
	int pix_ctrl2 = cvGet2D(I, imgsize.height - 4, imgsize.width - 4).val[0];
	pix_ctrl1 = (pix_ctrl1 + pix_ctrl2) / 2;

	int pix_00, pix_01, pix_02, pix_10, pix_12, pix_20, pix_21, pix_22;

	if (y > 0) pix_10 = cvGet2D(I, y - 1, x).val[0];
	else pix_10 = 0;
	if (y < imgsize.height - 1) pix_12 = cvGet2D(I, y + 1, x).val[0];
	else pix_12 = 0;
	return (pix_base + pix_10 + pix_12) / 3;*/
}

Sight::~Sight() {
	// TODO Auto-generated destructor stub
	cvReleaseCapture(&camera);
	cvReleaseImage(&capture);
	cvReleaseImage(&back);
}
