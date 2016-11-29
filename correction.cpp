// ---------------------------------//
//File: correction.cpp
//Author:Imed Elhadef imed.elhadef@arcangel.fr
//Date: 22 August 2016
//--------------------------//


#include <iostream>
#include <stdio.h>
#include <math.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <mutex>
#include <thread>

#ifdef _WIN32
#include "stdafx.h"
#include <Windows.h>
#endif

using namespace std;
using namespace cv;

// mutex to lock critical region
mutex mylock;
//CRITICAL_SECTION critSec; --> //For Win32 to work with critical section method is more faster than std::mutex

void distortion_correction (double strength_value)
 {
   // critical section (exclusive access to this part of code):
    mylock.lock();
    //EnterCriticalSection( &critSec );

    cout << " Put the image to load:" << endl;
    Mat_<Vec3b> img;
    img = imread("TestFisheye.jpg", CV_LOAD_IMAGE_COLOR); //read the image data in the file "TestFisheye.jpg" and store it in 'img'
    
    if (img.empty()) //check whether the image is loaded or not
     {
          cout << "Error : Image cannot be loaded..!!" << endl;
     }
    
    namedWindow("Distorted Image", WINDOW_AUTOSIZE);// Create a window for display.
    imshow("Distorted Image", img);                  // Show our image inside it.*/
    
    int halfWidth = img.rows / 2;
    int halfHeight = img.cols / 2;
    double strength = strength_value; // High number of strength leads to stronger correction 
    double correctionRadius = sqrt(pow(img.rows, 2) + pow(img.cols, 2)) / strength;

     Mat_<Vec3b> dstImage = img.clone();

    int newWidth, newHeight;
    double distance; 
    double theta; 
    int correctX; 
    int correctY; 
    double r;

    for (int i = 0; i < dstImage.rows; ++i)
    {
        for (int j = 0; j < dstImage.cols; j++)
        {
            newWidth = i - halfWidth; 
            newHeight = j - halfHeight;
            distance = sqrt(pow(newWidth, 2) + pow(newHeight, 2));
            r = distance / correctionRadius;
            if (r == 0.0)
                theta = 1;
            else
                theta = atan(r) / r;

            correctX = round(halfWidth + theta*newWidth);
            correctY = round(halfHeight + theta * newHeight);

            dstImage(i, j)[0] = img(correctX, correctY)[0];
            dstImage(i, j)[1] = img(correctX, correctY)[1];
            dstImage(i, j)[2] = img(correctX, correctY)[2];
        }
    }

    namedWindow("Final Image ", WINDOW_AUTOSIZE);
    imshow("Final Image ", dstImage);                   // Show our adjusted image inside it.
    waitKey(0);
    mylock.unlock();
    //LeaveCriticalSection( &critSec );
 }

int main() {
  
    thread th1 (distortion_correction,5);
    thread th2 (distortion_correction,1);

    th1.join();
    th2.join();

    return 0;
}
