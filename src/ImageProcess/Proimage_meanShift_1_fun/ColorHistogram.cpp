#include "stdafx.h"
#include"ColorHistogram.h"

//���ɫ���ֱ��ͼ
cv::MatND GetHistogram::getHueHistogram(const cv::Mat &image, int minSaturation)
{
	cv::MatND hist;
	cv::Mat hsv;
	cv::cvtColor(image, hsv, CV_BGR2HSV);
	std::vector<cv::Mat> hue;
	cv::split(image, hue);
	cv::Mat mask; 
	//���ͱ��Ͷȵ����ش�������ȥ��
	if (minSaturation > 0)
		cv::threshold(hue[1], mask, minSaturation, 255, cv::THRESH_BINARY);
	cv::calcHist(&hue[0],
		1,
		HueChannels,
		mask,
		hist,
		1,
		HueHistSize,
		HueBinRanges
		);
	return hist;
}