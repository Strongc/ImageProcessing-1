#if !defined OBJECTFINDER_H
#define OBJECTFINDER_H

#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>

class ObjectFinder
{
private:
	//calcBackProject�Ĳ���
	int HueChannels[1];
	cv::MatND histogram;
	float HueValueRanges[2];
	const float *HueBinRanges[1];


public:
	ObjectFinder()
	{
		HueChannels[0] = 0;
		HueValueRanges[0] = 0.0;
		HueValueRanges[1] = 180.0;
		HueBinRanges[0] = HueValueRanges;
	}
	//�õ�calcHist��ֱ��ͼ
	void setHistogram(cv::MatND hist)
	{
		histogram = hist;
	}
	//����ֱ��ͼ��ͼ����ͶӰ
	cv::Mat finder(const cv::Mat &image);
};

#endif