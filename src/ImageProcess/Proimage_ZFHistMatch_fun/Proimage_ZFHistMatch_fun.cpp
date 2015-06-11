// Proimage_ZFHistMatch_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

// the defination is designed for histgram 
#define  BINWIDTH 5
#define  HistSize 256

// the heigth and width of the histgram and the interval stand for the hist image interval
int height = 440;  
int interval = cvRound(BINWIDTH * 2 / 5);  
int width = HistSize * BINWIDTH + (HistSize - 1)*interval; 

// function in order to show many image in one named window
void cvShowManyImages(char* title, int nArgs, ...) {

	// img - Used for getting the arguments 
	IplImage *img;

	// DispImage - the image in which input images are to be copied
	IplImage *DispImage;

	int size;
	int i;
	int m, n;
	int x, y;

	// w - Maximum number of images in a row 
	// h - Maximum number of images in a column 
	int w, h;

	// scale - How much we have to resize the image
	float scale;
	int max;

	// If the number of arguments is lesser than 0 or greater than 12
	// return without displaying 
	if(nArgs <= 0) {
		printf("Number of arguments too small....\n");
		return;
	}
	else if(nArgs > 12) {
		printf("Number of arguments too large....\n");
		return;
	}
	// Determine the size of the image, 
	// and the number of rows/cols 
	// from number of arguments 
	else if (nArgs == 1) {
		w = h = 1;
		size = 300;
	}
	else if (nArgs == 2) {
		w = 2; h = 1;
		size = 300;
	}
	else if (nArgs == 3 || nArgs == 4) {
		w = 2; h = 2;
		size = 300;
	}
	else if (nArgs == 5 || nArgs == 6) {
		w = 3; h = 2;
		size = 200;
	}
	else if (nArgs == 7 || nArgs == 8) {
		w = 4; h = 2;
		size = 200;
	}
	else {
		w = 4; h = 3;
		size = 150;
	}

	// Create a new 3 channel image
	DispImage = cvCreateImage( cvSize(100 + size*w, 60 + size*h), 8, 1 );

	// Used to get the arguments passed
	va_list args;
	va_start(args, nArgs);

	// Loop for nArgs number of arguments
	for (i = 0, m = 20, n = 20; i < nArgs; i++, m += (20 + size)) {

		// Get the Pointer to the IplImage
		img = va_arg(args, IplImage*);

		// Check whether it is NULL or not
		// If it is NULL, release the image, and return
		if(img == 0) {
			printf("Invalid arguments");
			cvReleaseImage(&DispImage);
			return;
		}

		// Find the width and height of the image
		x = img->width;
		y = img->height;

		// Find whether height or width is greater in order to resize the image
		max = (x > y)? x: y;

		// Find the scaling factor to resize the image
		scale = (float) ( (float) max / size );

		// Used to Align the images
		if( i % w == 0 && m!= 20) {
			m = 20;
			n+= 20 + size;
		}

		// Set the image ROI to display the current image
		cvSetImageROI(DispImage, cvRect(m, n, (int)( x/scale ), (int)( y/scale )));

		// Resize the input image and copy the it to the Single Big Image
		cvResize(img, DispImage);

		// Reset the ROI in order to display the next image
		cvResetImageROI(DispImage);
	}

	// Create a new window, and show the Single Big Image
	cvNamedWindow( title, 1 );
	cvShowImage( title, DispImage);

	cvWaitKey(0);
	cvDestroyWindow(title);

	// End the number of arguments
	va_end(args);

	// Release the Image Memory
	cvReleaseImage(&DispImage);
}

// plot histgram :img is the source image  and the dst is the hist image  and scalar is the color
void PlotHist1D(IplImage *img,IplImage *dst,CvScalar scalar) // plot the hist graph
{
	IplImage *histimg = cvCloneImage(img);

	int bins = HistSize; // the bins of the hist image
	int sizes[] = {bins};
	CvHistogram *hist = cvCreateHist(1,sizes,CV_HIST_ARRAY);
	cvCalcHist(&histimg,hist);
	float max_val;
	cvGetMinMaxHistValue(hist,0,&max_val,0,0); 

	IplImage* pHistImg = cvCreateImage(cvSize(width,height),IPL_DEPTH_8U,1); 
	cvZero(pHistImg);  // create the hist image and set it to zero

	for (int i = 0;i < bins;i++) // draw the hist image 
	{  

		float fBinValue = cvQueryHistValue_1D(hist,i);  

		int BinHeight = cvRound(fBinValue / max_val * height);  

		CvScalar color = scalar;  

		CvPoint point1 = cvPoint(i*(BINWIDTH + interval),height);  

		CvPoint point2 = cvPoint(point1.x + BINWIDTH,height - BinHeight);  

		cvRectangle(pHistImg,point1,point2,color,-1,8,0);  
	}  

	cvReleaseHist(&hist); 
	cvCopy(pHistImg,dst);

}

// do the hist match histv[] is the vector that you need match
void HistMatch(IplImage *histimg,double histv[])
{
	int bins = 256;
	int sizes[] = {bins};
	CvHistogram *hist = cvCreateHist(1,sizes,CV_HIST_ARRAY);
	cvCalcHist(&histimg,hist);

	cvNormalizeHist(hist,1);

	double val_1 = 0.0;
	double val_2 = 0.0;
	uchar T[256] = {0};
	double S[256] = {0};
	double G[256] = {0};

	for (int index = 0; index<256; ++index)
	{
		val_1 += cvQueryHistValue_1D(hist,index);
		val_2 += histv[index];

		G[index] = val_2;
		S[index] = val_1;
	}

	double min_val = 0.0;
	int PG = 0;

	for ( int i = 0; i<256; ++i)
	{
		min_val = 1.0;
		for(int j = 0;j<256; ++j)
		{
			if( (G[j] - S[i]) < min_val && (G[j] - S[i]) >= 0)
			{
				min_val = (G[j] - S[i]);
				PG = j;
			}

		}
		T[i] = (uchar)PG;
	}

	uchar *p = NULL;
	for (int x = 0; x<histimg->height;++x)
	{ 
		p = (uchar*)(histimg->imageData + histimg->widthStep*x);
		for (int y = 0; y<histimg->width;++y)
		{
			p[y] = T[p[y]];
		}

	}


}

// generate a bimodal gausssian-like function in the interval[0,1] see p62 in Gonzalaz
void GenerateGaussModel(double model[])
{
	double m1,m2,sigma1,sigma2,A1,A2,K;
	m1 = 0.15;
	m2 = 0.75;
	sigma1 = 0.05;
	sigma2 = 0.05;
	A1 = 1;
	A2 = 0.07;
	K = 0.002;

	double c1 = A1*(1.0/(sqrt(2*CV_PI))*sigma1);
	double k1 = 2*sigma1*sigma1;
	double c2 = A2*(1.0/(sqrt(2*CV_PI))*sigma2);
	double k2 = 2*sigma2*sigma2;

	double p = 0.0,val= 0.0,z = 0.0;

	for (int zt = 0;zt < 256;++zt)
	{

		val = K + c1*exp(-(z-m1)*(z-m1)/k1) + c2*exp(-(z-m2)*(z-m2)/k2);
		model[zt] = val;
		p = p +val;
		z = z + 1.0/256;

	}

	for (int i = 0;i<256; ++i)
	{
		model[i] = model[i]/p;
	}

} 

int main()
{
// 	IplImage *img = cvLoadImage("E:\\DayBreakZcs\\ImageProcessing\\source\\test.jpg",CV_LOAD_IMAGE_GRAYSCALE);	   
// 	IplImage *histimg = cvCreateImage(cvGetSize(img),8,1);
// 	cvCopy(img,histimg);
// 
// 	double model[256] = {0};
// 
// 	GenerateGaussModel(model);
// 	HistMatch(histimg,model);
// 
// 	IplImage *histdst = cvCreateImage(cvSize(width,height),8,1);
// 	IplImage *histmatchdst = cvCreateImage(cvSize(width,height),8,1);
// 
// 	PlotHist1D(img,histdst,CV_RGB(100,100,100));
// 	PlotHist1D(histimg,histmatchdst,CV_RGB(200,100,100));
// 
// 	cvShowManyImages("image",4,img,histimg,histdst,histmatchdst);

	IplImage * image= cvLoadImage("E:\\DayBreakZcs\\ImageProcessing\\source\\test.jpg");  
	//显示原图及直方图  
	cvShowImage("Source",image);  

	IplImage* eqlimage=cvCreateImage(cvGetSize(image),image->depth,3);  
	//分别均衡化每个信道  
	IplImage* redImage=cvCreateImage(cvGetSize(image),image->depth,1);  
	IplImage* greenImage=cvCreateImage(cvGetSize(image),image->depth,1);  
	IplImage* blueImage=cvCreateImage(cvGetSize(image),image->depth,1);  
	cvSplit(image,blueImage,greenImage,redImage,NULL);  

	cvEqualizeHist(redImage,redImage);  
	cvEqualizeHist(greenImage,greenImage);   
	cvEqualizeHist(blueImage,blueImage);   
	//均衡化后的图像  
	cvMerge(blueImage,greenImage,redImage,NULL,eqlimage);  
	cvShowImage("Equalized",eqlimage);  
	cvWaitKey(0);

	return 0;
}

