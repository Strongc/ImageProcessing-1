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
// 	//��Ե���   
// 	cv::Canny (result,contours,50,150);
// 	cv::imshow("Bian",contours);
// 
// #ifdef _Line
// 	vector<Vec2f> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
// 	HoughLines(contours, lines, 1, CV_PI/2, 100, 0, 0 );
// 
// 	//��4��������ͼ�л��Ƴ�ÿ���߶�
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
// 	//��3�����л����߱任
// 	vector<Vec4i> lines;//����һ��ʸ���ṹlines���ڴ�ŵõ����߶�ʸ������
// 	HoughLinesP(contours, lines, 1, CV_PI/2, 30, 50, 10 );
// 
// 	//��4��������ͼ�л��Ƴ�ÿ���߶�
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


Mat g_srcImage, g_dstImage,g_midImage;//ԭʼͼ���м�ͼ��Ч��ͼ
vector<Vec4i> g_lines;//����һ��ʸ���ṹg_lines���ڴ�ŵõ����߶�ʸ������
//�������յ�TrackBarλ�ò���
int g_nthreshold=100;

static void on_HoughLines(int, void*);//�ص�����
static void ShowHelpText();

int main( )
{
	//�ı�console������ɫ
	system("color 3F");  

	ShowHelpText();

	//����ԭʼͼ��Mat��������   
	Mat g_srcImage = imread("..\\..\\..\\source\\00_00_01_00.jpg");  //����Ŀ¼��Ӧ����һ����Ϊ1.jpg���ز�ͼ

	//��ʾԭʼͼ  
	imshow("��ԭʼͼ��", g_srcImage);  

	//����������
	namedWindow("��Ч��ͼ��",1);
	createTrackbar("ֵ", "��Ч��ͼ��",&g_nthreshold,200,on_HoughLines);

	//���б�Ե����ת��Ϊ�Ҷ�ͼ
	Canny(g_srcImage, g_midImage, 50, 200, 3);//����һ��canny��Ե���
	cvtColor(g_midImage,g_dstImage, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ

	//����һ�λص�����������һ��HoughLinesP����
	on_HoughLines(g_nthreshold,0);
	HoughLinesP(g_midImage, g_lines, 1, CV_PI/2, 80, 50, 10 );

	//��ʾЧ��ͼ  
	imshow("��Ч��ͼ��", g_dstImage);  


	waitKey(0);  

	return 0;  

}


//-----------------------------------��on_HoughLines( )������--------------------------------
//		����������ñ����/��ñ���㡿���ڵĻص�����
//----------------------------------------------------------------------------------------------
static void on_HoughLines(int, void*)
{
	//����ֲ���������ȫ�ֱ���
	Mat dstImage=g_dstImage.clone();
	Mat midImage=g_midImage.clone();

	//����HoughLinesP����
	vector<Vec4i> mylines;
	HoughLinesP(midImage, mylines, 1, CV_PI/2, g_nthreshold+1, 10, 80 );

	//ѭ����������ÿһ���߶�
	for( size_t i = 0; i < mylines.size(); i++ )
	{
		Vec4i l = mylines[i];
		line( dstImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(23,180,55), 1, CV_AA);
	}
	//��ʾͼ��
	imshow("��Ч��ͼ��",dstImage);
}

//-----------------------------------��ShowHelpText( )������----------------------------------
//		���������һЩ������Ϣ
//----------------------------------------------------------------------------------------------
static void ShowHelpText()
{
	//���һЩ������Ϣ
	printf("\n\n\n\t������������۲�ͼ��Ч��~\n\n");
	printf("\n\n\t\t\t\t\t\t\t\t byǳī"
		);
}