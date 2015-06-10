// ProImage_Meanshift_Fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//¼ôÇÐÍ¼Æ¬Îªm * n ¿é  
void Cut_img(Mat src_img,int m,int n,Vector<Mat> ceil_img){  

	int t = m * n;  
	int height = src_img.rows;  
	int width  = src_img.cols;  

	int ceil_height = height/m;  
	int ceil_width  = width/n;   

	Mat roi_img,tmp_img;  

	Point p1,p2;  
	for(int i = 0;i<m;i++)  
		for(int j = 0;j<n;j++){  
			//p1 =   
			Rect rect(i+j*ceil_width,j+i*ceil_height,ceil_width,ceil_height);  

			src_img(rect).copyTo(roi_img);  

			ceil_img.push_back(roi_img);  
			imshow("roi_img",roi_img);  
			//getchar();  
			waitKey(0);  
			//rectangle(i+j*ceil_width,j+i*ceil_height,);  
		}     
}  

void show_images(Vector<Mat> imgs,int n){  

	//do something  
}  

int _tmain(int argc, _TCHAR* argv[])  
{  
	Mat img = imread("a.png",1);  
	imshow("src img",img);  
	int m = 3;  
	int n = 3;  
	Vector<Mat> ceil_img = m*n;  

	Cut_img(img,m,n,ceil_img);  

	waitKey();  
	return 0;  
}  