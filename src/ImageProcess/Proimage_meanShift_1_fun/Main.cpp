#include "stdafx.h"
#include <opencv2\core\core.hpp>
#include<opencv2\highgui\highgui.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <opencv2\video\video.hpp>

#include "ColorHistogram.h"
#include "ObjectFinder.h"

int main(void)
{
	GetHistogram gh;
	ObjectFinder of;
	cv::Mat img1, img2;
	cv::Mat imgROI;
	cv::Mat histogram;
	cv::Mat backProject;

	img1 = cv::imread("..\\..\\..\\source\\1.jpg");
	if(!img1.data)
		return 0;

	imgROI = img1(cv::Rect(80,300,35,40));
	cv::rectangle(img1,cv::Rect(110,260,35,40),cv::Scalar(0,0,255));
	cv::namedWindow("img1");
	cv::imshow("img1", img1);
	//���imgROI��ֱ��ͼ
	histogram = gh.getHueHistogram(imgROI, 65);
	cv::normalize(histogram,histogram,1.0);
	of.setHistogram(histogram);
	//��ȡ������ڶ���ͼ��
	cv::Mat hsv; 
	std::vector<cv::Mat> hue;
	img2 = cv::imread("..\\..\\..\\source\\2.jpg");
	cv::cvtColor(img2, hsv, CV_BGR2HSV);
	cv::split(hsv, hue);
	cv::threshold(hue[1], hue[1], 65, 255, cv::THRESH_BINARY);//�����Ϊ�˽��ͱ��Ͷȵ�ͼ��ӷ���ͶӰ������޳�
	//���ڵڶ���ͼ���з���ͶӰ��ʹ�õ�һ��ͼROI��ֱ��ͼ
	backProject = of.finder(img2);
	cv::bitwise_and(backProject, hue[1], backProject);
	cv::namedWindow("backProject");
	cv::imshow("backProject",backProject);
	//��ֵƯ��
	cv::Rect rect(110,260,35,40);
	cv::rectangle(img2, rect, cv::Scalar(0,0,255));
	cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,10,0.01);//������������10���ƶ�������ֵ��0.01
	cv::meanShift(backProject,rect,criteria);
	cv::rectangle(img2, rect, cv::Scalar(0,255,0));
	cv::namedWindow("img2");
	cv::imshow("img2",img2);

	cv::waitKey(0);
	return 0;
}