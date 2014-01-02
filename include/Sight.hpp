/************************************************************************
                        Sight.h - By K. Stopa

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

#include "SomethingCollection.hpp"
#include "opencv/cv.h"
#include "opencv/highgui.h"


#ifndef SIGHT_H_
#define SIGHT_H_



class Sight {
public:
	Sight();
	// Initialize cameras for image capture (by now only one)
	// ToDo: Capability to read and compare data from stereo cameras.
	int OpenEyes();
	// Read frame image from camera.
	int RealizeCapture();
	// Get last readed frame from camera.
	// Get image that is the difference between background image and last camera capture.
	IplImage* GetFrontImage();
	IplImage* GetCaptureImage();
	// Read processed (vectorized and separated objects) from a capture if it was ready.
	// First this may by check ussing IsReady function.
	SomethingCollection* GetViewObjects();
	// Check if something was processed
	bool IsReady();
	// Destructor
	virtual ~Sight();
private:
	// Device for image capture.
	CvCapture* camera; //= cvCaptureFromCAM(0);
	// Last image captured by camera.
	IplImage* capture;
	// Last updated background image.
	IplImage* back;


	// Update image used as background for filter capture content.
	void UpdateBackground();
	// Captured image size.
	CvSize imgsize;
	int GetImagePixelAvergueColor(IplImage* I, int x, int y);

};

#endif /* SIGHT_H_ */
