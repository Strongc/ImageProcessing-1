#include "stdafx.h"
#include"ObjectFinder.h"

cv::Mat ObjectFinder::finder(const cv::Mat &image)
{
	cv::Mat backProject;
	cv::Mat hsv;
	std::vector<cv::Mat> hue;
	cv::cvtColor(image, hsv, CV_BGR2HSV);
	cv::split(hsv, hue);
	cv::calcBackProject(&hue[1],
		1,
		HueChannels,
		histogram,
		backProject,
		HueBinRanges,
		255.0
		);
	return backProject;
}