// Proimge_PrySegmentation_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/legacy/legacy.hpp>

using namespace std;
using namespace cv;

void f( IplImage* src, IplImage* dst )
{
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* comp = NULL;
	cvPyrSegmentation( src, dst, storage, &comp, 4, 100, 10 );
	cvReleaseMemStorage( &storage );
}
int main(int argc, char** argv)
{
	// Load the image from the given file name.
	char *filename="..\\..\\..\\source\\00_01_30_00.jpg";
	IplImage *dst,*src = cvLoadImage(filename,1);
	if(!src)
	{
		printf("Couldn't seem to Open %s, sorry/n",filename);
		return -1;
	}

	dst = cvCreateImage( cvGetSize(src), src->depth, src->nChannels);
	f( src, dst);
	cv::Mat result,image(dst);  
	cv::cvtColor (image,result,CV_BGRA2GRAY);  
	cv::Mat contours; 
	cv::Canny (result,contours,50,150);
	cv::imshow("Bian",contours);
	// Create a named window with a the name of the file.
	cvNamedWindow( filename, 1 );
	// Show the image in the named window
	cvShowImage( filename, dst );
	// Press any key to exit.
	cvWaitKey(0);
	// Clean up and don¡¯t be piggies
	cvDestroyWindow( filename );
	cvReleaseImage( &src );
	cvReleaseImage( &dst );
	return 0;
}

