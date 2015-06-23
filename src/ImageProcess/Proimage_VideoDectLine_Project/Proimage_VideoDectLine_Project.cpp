// Proimage_VideoDectLine_Project.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, char* argv[])
{
	CvCapture* pCapture = NULL;
	if(argc == 2)
	{
		char* _tempname = "e:\\201505280048_22.mp4";
		if( !(pCapture = cvCaptureFromFile(_tempname)))     
		{   
			fprintf(stderr, "Can not open video file %s\n", argv[1]);   
			return -2;     
		}
	}
	if (argc == 1)
	{
		if( !(pCapture = cvCaptureFromCAM(1)))     
		{   
			fprintf(stderr, "Can not open camera.\n");   
			return -2;     
		} 
	}

	IplImage* pFrame = NULL;
	int countx=0;
	while (pFrame =cvQueryFrame(pCapture))  
	{ 
		countx++;
		cv::Mat image(pFrame);
		cv::Mat result;  
		cv::cvtColor (image,result,CV_BGRA2GRAY); 
		cv::Mat contours;  
		//±ßÔµ¼ì²â   
		cv::Canny (result,contours,50,150);
		char a[128]={'\0'};
		sprintf(a,".\\Result\\%d.jpg",countx);
		imwrite(a,contours);
		imshow("video",image);
	}
	return 0;
}

