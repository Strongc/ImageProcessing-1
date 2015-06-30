// Proimage_findREC_alg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
char* filename = "E:\\DayBreakZcs\\ImageProcessing\\source\\00_01_30_001.jpg";
//char* filenamemode = "face.bmp"; 
int ithreshold = 0;
IplImage *Image1,*Image2;
CvMemStorage *stroage;
IplImage *contourimage;
CvSeq *seq = NULL;
int ivalue = 0; 
int ku=-1;

void changebar(int)
{
	ithreshold = ivalue;
	cvThreshold(Image1,Image2,150,255,CV_THRESH_BINARY);

	int numcontours = cvFindContours(Image2,stroage,&seq,sizeof(CvContour),CV_RETR_LIST);

	if (ku != numcontours)
	{
		ku = numcontours;
		printf("contournum:::: %d \n",numcontours);
	}
	CvSeq *c = 0;
	int zz = 0;

	int totl = 0;
	cvSet(contourimage,cvScalar(255,255,255));
	cvSet(contourimage,cvScalar(125,125,125));
	CvPoint2D32f center;  
	float radius;  

	CvPoint2D32f rectpoint[4];

	CvContour *testcontour = 0;
	for (c = seq;c !=NULL;c = c->h_next)
	{
		double testdbArea = fabs(cvContourArea(c,CV_WHOLE_SEQ));
		double testdbLength = cvArcLength(c);

		c->block_max;
		if (testdbArea>=1000 && testdbLength<=1000)
		{
			CvRect testrect = cvBoundingRect(c);
			CvBox2D testbox = cvMinAreaRect2(c);
			cvDrawContours(contourimage,c,cvScalar(0,0,255),cvScalar(0,0,0),0,2);
			cvRectangle(contourimage,cvPoint(testrect.x,testrect.y+testrect.height),cvPoint(testrect.x+testrect.width,testrect.y),cvScalar(0,0,0),2);

			cvMinEnclosingCircle(c,&center,&radius); 
			cvCircle(contourimage,cvPointFrom32f(center),(int)radius,cvScalar(0,0,0),2);

			cvBoxPoints(testbox,rectpoint);
			cvRectangle(contourimage,cvPoint(testrect.x,testrect.y+testrect.height),cvPoint(testrect.x+testrect.width,testrect.y),cvScalar(0,0,0),2);

			for(int i = 0;i<4;i++)
			{
				cvLine(contourimage,cvPointFrom32f(rectpoint[i]),cvPointFrom32f(rectpoint[(i+1)%4]),CV_RGB(0,0,255),2);
			}  

			cvShowImage("grotto" ,contourimage);
			totl++;
			printf("contournum:::: %d   testdbArea::::  %f   testdbLength::::  %f\n",zz,testdbArea,testdbLength);

			cvWaitKey(0);	
		}
		zz++;
		//			cvWaitKey(0);	

	}
	printf("totl:::: %d     \n",totl);
	cvSaveImage("zzzz.jpg",contourimage);	

};

int main()
{
	//	filename = "D:\\kkk.bmp";
	//	filename = "D:\\zfruits512.JPG";
	//	filename = "D:\\alp.bmp";
	Image1=cvLoadImage(filename ,0);
	Image2 = cvCreateImage(cvGetSize(Image1),8,1);
	cvNamedWindow("grotto" ,1 );

	contourimage = cvCreateImage(cvGetSize(Image1),8,3);
	stroage = cvCreateMemStorage();

	ivalue = 1;
	changebar(1);
	int iexit = 0;
	while (iexit != 32 )
	{
		iexit = cvWaitKey(0 );
	}
	cvDestroyWindow("grotto");
	exit(1);

	return 0;
}