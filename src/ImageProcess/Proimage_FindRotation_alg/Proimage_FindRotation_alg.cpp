// Proimage_FindRotation_alg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define PI 3.1415926
int main()  
{  
	// Read input binary image  

	char *image_name = "..\\..\\..\\source\\00_01_30_001.jpg";  
	IplImage *src = cvLoadImage(image_name,CV_LOAD_IMAGE_GRAYSCALE);  
	cvSaveImage("a.jpg",src);
	CvMemStorage *storage = cvCreateMemStorage();  
	CvSeq *seq = NULL;  
	int cnt = cvFindContours(src,storage,&seq);  
	seq = seq->h_next;  
	double length = cvArcLength(seq);  
	double area = cvContourArea(seq);  
	CvRect rect = cvBoundingRect(seq,1);  
	CvBox2D box = cvMinAreaRect2(seq,NULL);  

	cout<<"Length = "<<length<<endl;  
	cout<<"Area = "<<area<<endl;  

	IplImage *dst = cvCreateImage(cvGetSize(src),8,3); cvZero(dst);  
	cvDrawContours(dst,seq,CV_RGB(255,0,0),CV_RGB(255,0,0),0);  
	cvRectangleR(dst,rect,CV_RGB(0,255,0));  
	cvShowImage("dst",dst);  
	cvWaitKey();  

	CvPoint2D32f center;  
	float radius;  
	cvMinEnclosingCircle(seq,&center,&radius);  
	cvCircle(dst,cvPointFrom32f(center),cvRound(radius),CV_RGB(100,100,100));  
	cvShowImage("dst",dst);  
	cvWaitKey();  

	CvBox2D ellipse = cvFitEllipse2(seq);  
	cvEllipseBox(dst,ellipse,CV_RGB(255,255,0));  
	cvShowImage("dst",dst);  
	cvWaitKey();  

	//���������С����  
	CvPoint2D32f pt[4];  
	cvBoxPoints(box,pt);  
	for(int i = 0;i<4;++i){  
		cvLine(dst,cvPointFrom32f(pt[i]),cvPointFrom32f(pt[((i+1)%4)?(i+1):0]),CV_RGB(0,0,255));  
	}  
	cvShowImage("dst",dst);  
	cvWaitKey();  

	cvReleaseImage(&src);  
	cvReleaseImage(&dst);  
	cvReleaseMemStorage(&storage);    


}  

