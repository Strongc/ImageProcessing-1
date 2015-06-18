// Proimage_HW2_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp" 
#include <iostream>
using namespace cv;
using namespace std;

//Set element in Matrix
void SetMatElem(CvMat *mat, int row, int col, int channel, int val)
{
	((float*)(mat->data.ptr+mat->step*row))[col*mat->step+channel]= val;

}

class Color
{
	int num;
public:
	int b, g, r;
	Color(){ b= 0; g= 0; r=0;num=0;}
	Color(int x, int y, int z) { b=x; g= y; r =z; num=0;}
	void Add( int x, int y, int z)//Calcuate average color
	{
		b=( b*num+x)/(num+1);
		g=( g*num+y)/(num+1);
		r= (r*num+z)/(num+1);
		++num;
	}
};

int main( int argc, char** argv )
{
	IplImage *src,*dst;
	int cluster_num;	

	//Load image
	if (argc==2){
		src= cvLoadImage(argv[1]);
	}
	else{
		src= cvLoadImage("..\\..\\..\\source\\00_01_30_00.jpg");
	}

	if( src == 0) { cout<<"Cannot open the file!"; exit(1000);}

	//Read input, get the number of clusters
	cout<<"Please input cluster number:";
	cin>>cluster_num;



	Color *color_tab= new Color[cluster_num]();
	CvMat *sample = cvCreateMat(src->height*src->width, 1, CV_32FC(5));
	CvMat *cluster = cvCreateMat(src->height*src->width, 1, CV_32SC1);

	//Initalize Matrix for 5-D vector to store each pixel info.in image	
	for( int i=0; i<src->height ;i++){	//row
		for( int j=0; j<src->width; j++){		//col
			long int index= i*src->width+j;
			SetMatElem(sample,index,0,0,i);
			SetMatElem(sample,index,0,1,j);
			SetMatElem(sample,index,0,2,CV_IMAGE_ELEM(src,uchar,i,j*3));
			SetMatElem(sample,index,0,3,CV_IMAGE_ELEM(src,uchar,i,j*3+1));
			SetMatElem(sample,index,0,4,CV_IMAGE_ELEM(src,uchar,i,j*3+2));
		}
	}

	//Do KMeans to Matrix sample, and store result in Matrix cluster
	cvKMeans2(sample, cluster_num, cluster,
		cvTermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 10, 10 ));

	dst = cvCreateImage(cvGetSize(src),8,3);
	cvZero(dst);

	//Visit each pixel in original image, calculate average color in each clusters
	//and store result in Table color_tab
	for(int i=0; i<dst->height; i++){
		for( int j=0; j<dst->width; j++){
			long int index= i* dst->width+j;
			int cluster_idx= cluster->data.i[index];
			int x= CV_IMAGE_ELEM(src,uchar, i, j*3);
			int y=  CV_IMAGE_ELEM(src,uchar, i, j*3+1);
			int z= CV_IMAGE_ELEM(src,uchar, i, j*3+2);
			color_tab[cluster_idx].Add(x,y,z);

		}
	}
	//Assign average color in cluster to destination image
	for(int i=0; i<dst->height; i++){
		for( int j=0; j<dst->width; j++){
			long int index= i* dst->width+j;
			int cluster_idx= cluster->data.i[index];
			CV_IMAGE_ELEM(dst,uchar, i, j*3) = color_tab[cluster_idx].b;
			CV_IMAGE_ELEM(dst,uchar, i, j*3+1) = color_tab[cluster_idx].g;
			CV_IMAGE_ELEM(dst,uchar, i, j*3+2) = color_tab[cluster_idx].r;
		}
	}

	//Show image
	cvNamedWindow("K-means Segmentation Result");
	cvShowImage("K-means Segmentation Result", dst);

	cvWaitKey(-1);

	cvReleaseMat(&sample);
	cvReleaseMat(&cluster);

	cvReleaseImage(&src);
	cvReleaseImage(&dst);


}
