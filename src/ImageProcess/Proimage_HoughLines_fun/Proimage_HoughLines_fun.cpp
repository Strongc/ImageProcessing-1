// Proimage_HoughLines_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"   
#define PI 3.1415926

class LineFinder{  
private:  
	// ֱ�߶�Ӧ�ĵ��������   
	std::vector<cv::Vec4i> lines;  
	//����   
	double deltaRho;  
	double deltaTheta;  
	// �ж���ֱ�ߵ���СͶƱ��   
	int minVote;  
	// �ж���ֱ�ߵ���С����   
	double minLength;  
	// ͬһ��ֱ���ϵ�֮��ľ������̶�   
	double maxGap;  
public:  
	//��ʼ��   
	LineFinder() : deltaRho(1), deltaTheta(PI/180),  
		minVote(10), minLength(0.), maxGap(0.) {}  
	// ���ò���   
	void setAccResolution(double dRho, double dTheta) {  
		deltaRho= dRho;  
		deltaTheta= dTheta;  
	}  
	// ������СͶƱ��   
	void setMinVote(int minv) {  
		minVote= minv;  
	}  
	// ������С�߶γ��Ⱥ��߶μ�����̶�   
	void setLineLengthAndGap(double length, double gap) {  
		minLength= length;  
		maxGap= gap;  
	}  

	//Ѱ���߶�   
	std::vector<cv::Vec4i> findLines(cv::Mat& binary) {  
		lines.clear();  
		cv::HoughLinesP(binary,lines, deltaRho, deltaTheta, minVote,minLength, maxGap);  
		return lines;   
	}  

	// ���߶�   
	void drawDetectedLines(cv::Mat &image, cv::Scalar color=cv::Scalar(0,255,0)) {  
		std::vector<cv::Vec4i>::const_iterator it2=lines.begin();  
		while (it2!=lines.end()) {  
			cv::Point pt1((*it2)[0],(*it2)[1]);  
			cv::Point pt2((*it2)[2],(*it2)[3]);  
			cv::line( image, pt1, pt2, color);  
			++it2;  
		}  
	}  
};  
int _tmain(int argc, _TCHAR* argv[])
{
	cv::Mat image = cv::imread ("..\\..\\..\\source\\00_01_48_00.jpg");    
	cv::Mat result;  
	cv::cvtColor (image,result,CV_BGRA2GRAY);  
	cv::Mat contours;  
	//��Ե���   
	cv::Canny (result,contours,50,150);
	//cv::Sobel(result,contours,result.depth(),1,0);
	//cv::Laplacian(result,contours,result.depth());
	cv::imshow("Bian",contours);
	LineFinder finder;  
	finder.setMinVote (80);  
	finder.setLineLengthAndGap (100,20);  
	finder.findLines (contours);  
	finder.drawDetectedLines (image);  

	cv::namedWindow ("hough");  
	cv::imshow("hough",image);  
	cv::waitKey (0);  
}

