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
	//获得imgROI的直方图
	histogram = gh.getHueHistogram(imgROI, 65);
	cv::normalize(histogram,histogram,1.0);
	of.setHistogram(histogram);
	//获取并处理第二幅图像
	cv::Mat hsv; 
	std::vector<cv::Mat> hue;
	img2 = cv::imread("..\\..\\..\\source\\2.jpg");
	cv::cvtColor(img2, hsv, CV_BGR2HSV);
	cv::split(hsv, hue);
	cv::threshold(hue[1], hue[1], 65, 255, cv::THRESH_BINARY);//这个是为了将低饱和度的图像从反向投影结果中剔除
	//对于第二幅图进行反向投影，使用第一幅图ROI的直方图
	backProject = of.finder(img2);
	cv::bitwise_and(backProject, hue[1], backProject);
	cv::namedWindow("backProject");
	cv::imshow("backProject",backProject);
	//均值漂移
	cv::Rect rect(110,260,35,40);
	cv::rectangle(img2, rect, cv::Scalar(0,0,255));
	cv::TermCriteria criteria(cv::TermCriteria::MAX_ITER,10,0.01);//最大迭代次数是10，移动距离阈值是0.01
	cv::meanShift(backProject,rect,criteria);
	cv::rectangle(img2, rect, cv::Scalar(0,255,0));
	cv::namedWindow("img2");
	cv::imshow("img2",img2);

	cv::waitKey(0);
	return 0;
}