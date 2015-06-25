#if !defined GETHISTOGRAM_H
#define GETHISTOGRAM_H

#include<opencv2\core\core.hpp>
#include<opencv2\imgproc\imgproc.hpp>

class GetHistogram
{
private:
	//calchist中的参数
	int HueChannels[1];

	int HueHistSize[1] ;

	float HueValueRanges[2];

	const float *HueBinRanges[1] ;

public:
	GetHistogram()
	{
		HueChannels[0] = 0;

		HueHistSize[0] = 180;

		HueValueRanges[0] = 0.0;
		HueValueRanges[1] = 180.0;

		HueBinRanges[0] = HueValueRanges;
	}
	//获得色相的直方图
	cv::MatND getHueHistogram(const cv::Mat &image, int minSaturation);
};

#endif