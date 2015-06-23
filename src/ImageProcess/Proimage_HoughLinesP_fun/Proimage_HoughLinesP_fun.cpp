// Proimage_HoughLinesP_fun.cpp : Defines the entry point for the console application.
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
	cv::Mat image = cv::imread ("..\\..\\..\\source\\00_01_30_001.jpg");    
	cv::Mat result;  
	cv::cvtColor (image,result,CV_BGRA2GRAY);  
	cv::Mat contours;  
	//��Ե���   
	cv::Canny (result,contours,50,150);
	//cv::Sobel(result,contours,result.depth(),1,0);
	//cv::Laplacian(result,contours,result.depth());
	cv::imshow("Bian",contours);
	imwrite("122.jpg",contours);
	LineFinder finder;  
	finder.setMinVote (80);  
	finder.setLineLengthAndGap (100,20);
	std::vector<cv::Vec4i> li;
	li = finder.findLines (contours); 
	//ѡ���һ��ֱ�� 
	//��ɫ��ͼ��  
	
	for(int i = 0; i < li.size();i++)
	{
		int n= i;
		cv::Mat oneLine(image.size(),CV_8U,cv::Scalar(0));  
		cv::Mat oneLineInv;  
		//����  
		line(oneLine,cv::Point(li[n][0],li[n][1]),cv::Point(li[n][2],li[n][3]),cv::Scalar(255),5);  
		//����������߰�λ��  
		bitwise_and(contours,oneLine,oneLine); 		
		threshold(oneLine,oneLineInv,128,255,cv::THRESH_BINARY_INV);  
		imwrite("12.jpg",oneLine);
		//�ѵ㼯�еĵ���뵽������  
		std::vector<cv::Point> points;  
		//����ÿ������  
		for(int y = 0; y < oneLine.rows;y++)  
		{  
			uchar* rowPtr = oneLine.ptr<uchar>(y);  
			for(int x = 0;x < oneLine.cols;x++)  
			{  
				if(rowPtr[x])  
				{  
					points.push_back(cv::Point(x,y));  
				}  
			}  
		}  
		//�������ֱ�ߵ�����  
		cv::Vec4f line;  
		//ֱ����Ϻ���  
		fitLine(cv::Mat(points),line,CV_DIST_L12,0,0.01,0.01);  
		//��һ���߶�  
		int x0= line[2];  
		int y0= line[3];  
		int x1= x0-line[0];  
		int y1= y0-line[1]; 
		if(y0 == y1 /*|| x0 == x1*/)
		{
			cv::line(image,cv::Point(x0,y0),cv::Point(x1,y1),cv::Scalar(0,255,0),1); 	
			imwrite("123.jpg",image);
		}
	}
	imshow("���Ƶ�ֱ��",image); 
	//finder.drawDetectedLines (image);  

// 	cv::namedWindow ("hough");  
// 	cv::imshow("hough",image);  
	cv::waitKey (0);
	return 0;
}

