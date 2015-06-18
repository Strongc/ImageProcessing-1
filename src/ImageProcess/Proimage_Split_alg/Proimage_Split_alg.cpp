// Proimage_Split_alg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"
#include <iostream>
#include<cmath>
#include<stdio.h>
#include<iostream>
#include <fstream>
using namespace std;
using namespace cv;

#define _LineP

// int _tmain(int argc, _TCHAR* argv[])
// {
// 	cv::Mat image = cv::imread ("..\\..\\..\\source\\00_00_01_00.jpg");    
// 	cv::Mat result; 
// 	cv::imshow("src",image);
// 	cv::cvtColor (image,result,CV_BGRA2GRAY);  
// 	cv::Mat contours;  
// 	//边缘检测   
// 	cv::Canny (result,contours,50,150);
// 	cv::imshow("Bian",contours);
// 
// #ifdef _Line
// 	vector<Vec2f> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
// 	HoughLines(contours, lines, 1, CV_PI/2, 100, 0, 0 );
// 
// 	//【4】依次在图中绘制出每条线段
// 	for( size_t i = 0; i < lines.size(); i++ )
// 	{
// 		float rho = lines[i][0], theta = lines[i][1];
// 
// 		//if(theta == 0 )
// 		{
// 			Point pt1, pt2;
// 			double a = cos(theta), b = sin(theta);
// 			double x0 = a*rho, y0 = b*rho;
// 			pt1.x = cvRound(x0 + 1000*(-b));
// 			pt1.y = cvRound(y0 + 1000*(a));
// 			pt2.x = cvRound(x0 - 1000*(-b));
// 			pt2.y = cvRound(y0 - 1000*(a));
// 			line( image, pt1, pt2, Scalar(0,0,255), 1, CV_AA);
// 		}	
// // 		if(((theta <= 1.58)&&theta>=1.56))
// // 		{
// // 			Point pt1, pt2;
// // 			double a = cos(theta), b = sin(theta);
// // 			double x0 = a*rho, y0 = b*rho;
// // 			pt1.x = cvRound(x0 + 1000*(-b));
// // 			pt1.y = cvRound(y0 + 1000*(a));
// // 			pt2.x = cvRound(x0 - 1000*(-b));
// // 			pt2.y = cvRound(y0 - 1000*(a));
// // 			line( image, pt1, pt2, Scalar(0,255,0), 1, CV_AA);
// // 		}
// 	}
// #endif
// #ifdef _LineP
// 	//【3】进行霍夫线变换
// 	vector<Vec4i> lines;//定义一个矢量结构lines用于存放得到的线段矢量集合
// 	HoughLinesP(contours, lines, 1, CV_PI/2, 30, 50, 10 );
// 
// 	//【4】依次在图中绘制出每条线段
// 	for( size_t i = 0; i < lines.size(); i++ )
// 	{
// 		Vec4i l = lines[i];
// 		line( image, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186,88,255), 1, CV_AA);
// 	}
// #endif
// 	
// 
// 	cv::imshow("Bian1",image);
// 	cv::waitKey (0);  
// 	return 0;
// }


Mat g_srcImage, g_dstImage,g_midImage;//原始图、中间图和效果图
vector<Vec4i> g_lines;//定义一个矢量结构g_lines用于存放得到的线段矢量集合
//变量接收的TrackBar位置参数
int g_nthreshold=100;

static void on_HoughLines(int, void*);//回调函数
static void ShowHelpText();

int main( )
{
	//改变console字体颜色
	system("color 3F");  

	ShowHelpText();

	//载入原始图和Mat变量定义   
	Mat g_srcImage = imread("..\\..\\..\\source\\00_00_01_00.jpg");  //工程目录下应该有一张名为1.jpg的素材图

	//显示原始图  
	imshow("【原始图】", g_srcImage);  

	//创建滚动条
	namedWindow("【效果图】",1);
	createTrackbar("值", "【效果图】",&g_nthreshold,200,on_HoughLines);

	//进行边缘检测和转化为灰度图
	Canny(g_srcImage, g_midImage, 50, 200, 3);//进行一次canny边缘检测
	cvtColor(g_midImage,g_dstImage, CV_GRAY2BGR);//转化边缘检测后的图为灰度图

	//调用一次回调函数，调用一次HoughLinesP函数
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/2, 80, 50, 10 );

	//显示效果图  
	imshow("【效果图】", g_dstImage);  


	waitKey(0);  

	return 0;  

}


//-----------------------------------【on_HoughLines( )函数】--------------------------------
//		描述：【顶帽运算/黑帽运算】窗口的回调函数
//----------------------------------------------------------------------------------------------
static void on_HoughLines(int, void*)
{
	//定义局部变量储存全局变量
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//调用HoughLinesP函数
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/2, g_nthreshold+1, 10, 80 );

	//循环遍历绘制每一条线段
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, CV_AA);
	}
	//显示图像
	imshow("【效果图】",dstImage);
}

//-----------------------------------【ShowHelpText( )函数】----------------------------------
//		描述：输出一些帮助信息
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//输出一些帮助信息
	printf("\n\n\n\t请调整滚动条观察图像效果~\n\n");
	printf("\n\n\t\t\t\t\t\t\t\t by浅墨"
		);
}