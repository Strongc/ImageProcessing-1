// Proimage_ZFcalcBack_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "opencv2/opencv.hpp" 
#include <opencv2/core/core.hpp>  
#include <opencv2/imgproc/imgproc.hpp>  
#include <iostream> 
using namespace cv; 
using namespace std;

class Histogram1D  
{  
private:  

	//直方图的点数  
	int histSize[1];  
	//直方图的范围  
	float hranges[2];  
	//指向该范围的指针  
	const float* ranges[1];  
	//通道  
	int channels[1];  


public:  
	//构造函数  
	Histogram1D()  
	{  
		histSize[0] = 256;  
		hranges[0] = 0.0;  
		hranges[1] = 255.0;  
		ranges[0] = hranges;  
		channels[0] = 0;  

	}  

	Mat getHistogram(const Mat &image)  
	{  
		Mat hist;  
		//计算直方图函数  
		//参数为：源图像（序列）地址，输入图像的个数，通道数，掩码，输出结果，直方图维数，每一维的大小，每一维的取值范围  
		calcHist(&image,1,channels,Mat(),hist,1,histSize,ranges);  
		//这个函数虽然有很多参数，但是大多数时候，只会用于灰度图像或者彩色图像  
		//但是，允许通过指明一个多通道图像使用多幅图像  
		//第6个参数指明了直方图的维数  
		return hist;  
	}  

	Mat getHistogramImage(const Mat &image)  
	{  
		//首先计算直方图  
		Mat hist = getHistogram(image);  

		//获取最大值和最小值  
		double maxVal = 0;  
		double minVal = 0;  
		//minMaxLoc用来获得最大值和最小值,后面两个参数为最小值和最大值的位置，0代表不需要获取  
		minMaxLoc(hist,&minVal,&maxVal,0,0);  
		//展示直方图的画板：底色为白色  
		Mat histImg(histSize[0],histSize[0],CV_8U,Scalar(255));  

		//将最高点设为bin总数的90%  
		//int hpt = static_cast<int>(0.9*histSize[0]);  
		int hpt = static_cast<int>(histSize[0]);  
		//为每一个bin画一条线  
		for(int h = 0; h < histSize[0];h++)  
		{  
			float binVal = hist.at<float>(h);  
			int intensity = static_cast<int>(binVal*hpt/maxVal);  
			//int intensity = static_cast<int>(binVal);  
			line(histImg,Point(h,histSize[0]),Point(h,histSize[0]-intensity),Scalar::all(0));  

		}  
		return histImg;  
	}  

	Mat applyLookUp(const Mat& image,const Mat& lookup)  
	{  
		Mat result;  
		LUT(image,lookup,result);  
		return result;  
	}  


	Mat strech(const Mat &image,int minValue = 0)  
	{  
		//首先计算直方图  
		Mat hist = getHistogram(image);  
		//左边入口  
		int imin = 0;  
		for(;imin< histSize[0];imin++)  
		{  
			cout<<hist.at<float>(imin)<<endl;  
			if(hist.at<float>(imin) > minValue)  
				break;  

		}  
		//右边入口  
		int imax = histSize[0]-1;  
		for(;imax >= 0; imax--)  
		{  
			if(hist.at<float>(imax) > minValue)  
				break;  
		}  

		//创建查找表  
		int dim(256);  
		Mat lookup(1,&dim,CV_8U);  

		for(int i = 0; i < 256; i++)  
		{  
			if(i < imin)  
			{  
				lookup.at<uchar>(i) = 0;  
			}  
			else if(i > imax)  
			{  
				lookup.at<uchar>(i) = 255;  
			}  
			else  
			{  
				lookup.at<uchar>(i) = static_cast<uchar>(255.0*(i-imin)/(imax-imin)+0.5);  
			}  
		}  
		Mat result;  
		result = applyLookUp(image,lookup);  
		return result;  

	}  
	Mat equalize(const Mat &image)  
	{  
		Mat result;  
		equalizeHist(image,result);  
		return result;  
	}  

}; 
class ColorHistogram  
{  
private:  
	int histSize[3];  
	float hranges[2];  
	const float* ranges[3];  
	int channels[3];  
public:  

	//构造函数  
	ColorHistogram()  
	{  
		histSize[0]= histSize[1]= histSize[2]= 256;  
		hranges[0] = 0.0;  
		hranges[1] = 255.0;  
		ranges[0] = hranges;  
		ranges[1] = hranges;  
		ranges[2] = hranges;  
		channels[0] = 0;  
		channels[1] = 1;  
		channels[2] = 2;  
	}  

	//计算彩色图像直方图  
	Mat getHistogram(const Mat& image)  
	{  
		Mat hist;  

		//BGR直方图  
		hranges[0]= 0.0;      
		hranges[1]= 255.0;  
		channels[0]= 0;   
		channels[1]= 1;   
		channels[2]= 2;   

		//计算  
		calcHist(&image,1,channels,Mat(),hist,3,histSize,ranges);  
		return hist;  
	}  

	//计算颜色的直方图  
	Mat getHueHistogram(const Mat &image)  
	{  
		Mat hist;  
		Mat hue;  
		//转换到HSV空间  
		cvtColor(image,hue,CV_BGR2HSV);  

		//设置1维直方图使用的参数  
		hranges[0] = 0.0;  
		hranges[1] = 180.0;  
		channels[0] = 0;  
		//计算直方图  
		calcHist(&hue,1,channels,Mat(),hist,1,histSize,ranges);  
		return hist;  

	}  

	//减少颜色  
	Mat colorReduce(const Mat &image,int div = 64)  
	{  
		int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));  
		uchar mask = 0xFF<<n;  
		Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();  
		Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();  
		//设置输出图像  
		Mat result(image.rows,image.cols,image.type());  
		Mat_<Vec3b>::iterator itr = result.begin<Vec3b>();  
		for(;it != itend;++it,++itr)  
		{  
			(*itr)[0] = ((*it)[0]&mask) + div/2;  
			(*itr)[1] = ((*it)[1]&mask) + div/2;  
			(*itr)[2] = ((*it)[2]&mask) + div/2;  
		}  
		return result;  
	}  

};  
class ContentFinder  
{  
private:  
	float hranges[2];  
	const float* ranges[3];  
	int channels[3];  
	float threshold;  
	Mat histogram;  
public:  
	ContentFinder():threshold(-1.0f)  
	{  
		//所有通道的范围相同  
		ranges[0] = hranges;  
		ranges[1] = hranges;   
		ranges[2] = hranges;  
	}  

	//设置门限参数[0,1]  
	void setThreshold(float t)  
	{  
		threshold = t;  
	}  

	//获取门限参数  
	float getThreshold()  
	{  
		return threshold;  
	}  

	//设置参考的直方图  
	void setHistogram(const Mat& h)  
	{  
		histogram = h;  
		normalize(histogram,histogram,1.0);  
	}  

	//简单的利用反向投影直方图寻找  
	Mat find(const Mat& image)  
	{  
		Mat result;  
		hranges[0] = 0.0;  
		hranges[1] = 255.0;  
		channels[0] = 0;  
		channels[1] = 1;  
		channels[2] = 2;  

		calcBackProject(&image,1,channels,histogram,result,ranges,255.0);  
		if (threshold>0.0)  
		{  
			cv::threshold(result, result, 255*threshold, 255, cv::THRESH_BINARY);  
		}  

		return result;  
	}  

	//复杂的利用反向投影直方图，增加了一些参数  
	Mat find(const Mat &image,float minValue,float maxValue,int *channels,int dim)  
	{  
		Mat result;  
		hranges[0] = minValue;  
		hranges[1] = maxValue;  
		for(int i = 0;i < dim;i++)  
		{  
			this->channels[i] = channels[i];  
		}  
		calcBackProject(&image,1,channels,histogram,result,ranges,255.0);  
		if(threshold >0.0)  
			cv::threshold(result,result, 255*threshold,255,THRESH_BINARY);  
		return result;  

	}  
};  


int _tmain(int argc, _TCHAR* argv[])
{
	//读取图像  
    Mat image = imread("..\\..\\..\\source\\00_01_48_00.jpg",0);  
    if(!image.data)  
        return -1;  
  
  
    //定义感兴趣区域  
    Mat imageROI = image(Rect(360,55,40,50));   
  
    //利用前面设计好的类计算感兴趣区域的直方图  
    Histogram1D h;  
    Mat hist = h.getHistogram(imageROI);  
  
    //创建一个ContentFinder对象  
    ContentFinder finder;  
    finder.setHistogram(hist);  
    finder.setThreshold(-1.0f);  
    //获取反向投影  
    Mat result1;  
    result1 = finder.find(image);  
    Mat tmp;  
    result1.convertTo(tmp,CV_8U,-1.0,255.0);  
    imshow("反向投影结果",tmp);  
  
    //获取二值反向投影  
    finder.setThreshold(0.12f);  
    result1 = finder.find(image);  
    imshow("灰度图像检测结果（1）",result1);  
  
    //给源图像加上矩形框  
    rectangle(image,Rect(360,55,40,50),Scalar(0,0,0));  
    imshow("源图像",image);  
  
  
    //换一幅图像：这幅图像中也有大量云彩  
    Mat image2 = imread("..\\..\\..\\source\\00_01_48_00.jpg",0);  
      
    Mat result2 = finder.find(image2);  
    imshow("灰度图像检测结果（2）",result2);  
	
      
//**************以上检测因为没有用到颜色信息，所以效果很差**************  
  
  
    //获取彩色直方图  
    //读取彩色图像  
    ColorHistogram hc;  
    Mat color = imread("..\\..\\..\\source\\00_01_48_00.jpg");  
    imshow("源图像（1）",color);  
    //为了减少计算量，使用colorReduce函数  
    color = hc.colorReduce(color,32);  
      
  
    //定义感兴趣区域:云彩  
    imageROI = color(Rect(0,0,165,75));  
  
    //获取直方图  
    Mat shist = hc.getHistogram(imageROI);  
    finder.setHistogram(shist);  
    finder.setThreshold(0.05f);  
  
    //获取反向投影直方图  
    result1 = finder.find(color);  
    imshow("彩色图像检测结果（1）",result1);  
  
  
    //读取第二幅图像并检测  
    Mat color2 = imread("..\\..\\..\\source\\00_01_48_00.jpg");  
    imshow("源图像（2）",color2);  
    color2 = hc.colorReduce(color2,32);  
    result2 = finder.find(color2);  
    imshow("彩色图像检测结果（2）",result2);  
  
//***************以上结果因为考虑了颜色信息，所以效果比较好*********************  
  
    //仅考虑色度信息，构成直方图，进行反向投影检测  
    color = imread("..\\..\\..\\source\\00_01_48_00.jpg");  
    imageROI = color(Rect(0,0,165,75));  
    Mat colorhist = hc.getHueHistogram(imageROI);  
    finder.setHistogram(colorhist);  
    finder.setThreshold(0.3f);  
    Mat hsv;  
    cvtColor(color,hsv,CV_BGR2HSV);  
    int ch[2]={1,2};  
    ch[0] = 0;  
    result1 = finder.find(hsv,0.0f,180.0f,ch,1);  
    imshow("使用色度的结果（1）",result1);  
  
    //换一幅图片  
    color2 = imread("..\\..\\..\\source\\00_01_48_00.jpg");  
    cvtColor(color2,hsv,CV_BGR2HSV);  
    result2 = finder.find(hsv,0.0f,180.0f,ch,1);  
    imshow("使用色度检测结果（2）",result2);  
    waitKey(0);  
    return 0;  
	waitKey(0);
	return 0;
}

