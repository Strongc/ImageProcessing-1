// Proimage_HoughLines_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp"   
#define PI 3.1415926

class LineFinder{  
private:  
	// 直线对应的点参数向量   
	std::vector<cv::Vec4i> lines;  
	//步长   
	double deltaRho;  
	double deltaTheta;  
	// 判断是直线的最小投票数   
	int minVote;  
	// 判断是直线的最小长度   
	double minLength;  
	// 同一条直线上点之间的距离容忍度   
	double maxGap;  
public:  
	//初始化   
	LineFinder() : deltaRho(1), deltaTheta(PI/180),  
		minVote(10), minLength(0.), maxGap(0.) {}  
	// 设置步长   
	void setAccResolution(double dRho, double dTheta) {  
		deltaRho= dRho;  
		deltaTheta= dTheta;  
	}  
	// 设置最小投票数   
	void setMinVote(int minv) {  
		minVote= minv;  
	}  
	// 设置最小线段长度和线段间距容忍度   
	void setLineLengthAndGap(double length, double gap) {  
		minLength= length;  
		maxGap= gap;  
	}  

	//寻找线段   
	std::vector<cv::Vec4i> findLines(cv::Mat& binary) {  
		lines.clear();  
		cv::HoughLinesP(binary,lines, deltaRho, deltaTheta, minVote,minLength, maxGap);  
		return lines;   
	}  

	// 画线段   
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
	//边缘检测   
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

