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

	//ֱ��ͼ�ĵ���  
	int histSize[1];  
	//ֱ��ͼ�ķ�Χ  
	float hranges[2];  
	//ָ��÷�Χ��ָ��  
	const float* ranges[1];  
	//ͨ��  
	int channels[1];  


public:  
	//���캯��  
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
		//����ֱ��ͼ����  
		//����Ϊ��Դͼ�����У���ַ������ͼ��ĸ�����ͨ���������룬��������ֱ��ͼά����ÿһά�Ĵ�С��ÿһά��ȡֵ��Χ  
		calcHist(&image,1,channels,Mat(),hist,1,histSize,ranges);  
		//���������Ȼ�кܶ���������Ǵ����ʱ��ֻ�����ڻҶ�ͼ����߲�ɫͼ��  
		//���ǣ�����ͨ��ָ��һ����ͨ��ͼ��ʹ�ö��ͼ��  
		//��6������ָ����ֱ��ͼ��ά��  
		return hist;  
	}  

	Mat getHistogramImage(const Mat &image)  
	{  
		//���ȼ���ֱ��ͼ  
		Mat hist = getHistogram(image);  

		//��ȡ���ֵ����Сֵ  
		double maxVal = 0;  
		double minVal = 0;  
		//minMaxLoc����������ֵ����Сֵ,������������Ϊ��Сֵ�����ֵ��λ�ã�0������Ҫ��ȡ  
		minMaxLoc(hist,&minVal,&maxVal,0,0);  
		//չʾֱ��ͼ�Ļ��壺��ɫΪ��ɫ  
		Mat histImg(histSize[0],histSize[0],CV_8U,Scalar(255));  

		//����ߵ���Ϊbin������90%  
		//int hpt = static_cast<int>(0.9*histSize[0]);  
		int hpt = static_cast<int>(histSize[0]);  
		//Ϊÿһ��bin��һ����  
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
		//���ȼ���ֱ��ͼ  
		Mat hist = getHistogram(image);  
		//������  
		int imin = 0;  
		for(;imin< histSize[0];imin++)  
		{  
			cout<<hist.at<float>(imin)<<endl;  
			if(hist.at<float>(imin) > minValue)  
				break;  

		}  
		//�ұ����  
		int imax = histSize[0]-1;  
		for(;imax >= 0; imax--)  
		{  
			if(hist.at<float>(imax) > minValue)  
				break;  
		}  

		//�������ұ�  
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

	//���캯��  
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

	//�����ɫͼ��ֱ��ͼ  
	Mat getHistogram(const Mat& image)  
	{  
		Mat hist;  

		//BGRֱ��ͼ  
		hranges[0]= 0.0;      
		hranges[1]= 255.0;  
		channels[0]= 0;   
		channels[1]= 1;   
		channels[2]= 2;   

		//����  
		calcHist(&image,1,channels,Mat(),hist,3,histSize,ranges);  
		return hist;  
	}  

	//������ɫ��ֱ��ͼ  
	Mat getHueHistogram(const Mat &image)  
	{  
		Mat hist;  
		Mat hue;  
		//ת����HSV�ռ�  
		cvtColor(image,hue,CV_BGR2HSV);  

		//����1άֱ��ͼʹ�õĲ���  
		hranges[0] = 0.0;  
		hranges[1] = 180.0;  
		channels[0] = 0;  
		//����ֱ��ͼ  
		calcHist(&hue,1,channels,Mat(),hist,1,histSize,ranges);  
		return hist;  

	}  

	//������ɫ  
	Mat colorReduce(const Mat &image,int div = 64)  
	{  
		int n = static_cast<int>(log(static_cast<double>(div))/log(2.0));  
		uchar mask = 0xFF<<n;  
		Mat_<Vec3b>::const_iterator it = image.begin<Vec3b>();  
		Mat_<Vec3b>::const_iterator itend = image.end<Vec3b>();  
		//�������ͼ��  
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
		//����ͨ���ķ�Χ��ͬ  
		ranges[0] = hranges;  
		ranges[1] = hranges;   
		ranges[2] = hranges;  
	}  

	//�������޲���[0,1]  
	void setThreshold(float t)  
	{  
		threshold = t;  
	}  

	//��ȡ���޲���  
	float getThreshold()  
	{  
		return threshold;  
	}  

	//���òο���ֱ��ͼ  
	void setHistogram(const Mat& h)  
	{  
		histogram = h;  
		normalize(histogram,histogram,1.0);  
	}  

	//�򵥵����÷���ͶӰֱ��ͼѰ��  
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

	//���ӵ����÷���ͶӰֱ��ͼ��������һЩ����  
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
	//��ȡͼ��  
    Mat image = imread("..\\..\\..\\source\\00_01_48_00.jpg",0);  
    if(!image.data)  
        return -1;  
  
  
    //�������Ȥ����  
    Mat imageROI = image(Rect(360,55,40,50));   
  
    //����ǰ����ƺõ���������Ȥ�����ֱ��ͼ  
    Histogram1D h;  
    Mat hist = h.getHistogram(imageROI);  
  
    //����һ��ContentFinder����  
    ContentFinder finder;  
    finder.setHistogram(hist);  
    finder.setThreshold(-1.0f);  
    //��ȡ����ͶӰ  
    Mat result1;  
    result1 = finder.find(image);  
    Mat tmp;  
    result1.convertTo(tmp,CV_8U,-1.0,255.0);  
    imshow("����ͶӰ���",tmp);  
  
    //��ȡ��ֵ����ͶӰ  
    finder.setThreshold(0.12f);  
    result1 = finder.find(image);  
    imshow("�Ҷ�ͼ��������1��",result1);  
  
    //��Դͼ����Ͼ��ο�  
    rectangle(image,Rect(360,55,40,50),Scalar(0,0,0));  
    imshow("Դͼ��",image);  
  
  
    //��һ��ͼ�����ͼ����Ҳ�д����Ʋ�  
    Mat image2 = imread("..\\..\\..\\source\\00_01_48_00.jpg",0);  
      
    Mat result2 = finder.find(image2);  
    imshow("�Ҷ�ͼ��������2��",result2);  
	
      
//**************���ϼ����Ϊû���õ���ɫ��Ϣ������Ч���ܲ�**************  
  
  
    //��ȡ��ɫֱ��ͼ  
    //��ȡ��ɫͼ��  
    ColorHistogram hc;  
    Mat color = imread("..\\..\\..\\source\\00_01_48_00.jpg");  
    imshow("Դͼ��1��",color);  
    //Ϊ�˼��ټ�������ʹ��colorReduce����  
    color = hc.colorReduce(color,32);  
      
  
    //�������Ȥ����:�Ʋ�  
    imageROI = color(Rect(0,0,165,75));  
  
    //��ȡֱ��ͼ  
    Mat shist = hc.getHistogram(imageROI);  
    finder.setHistogram(shist);  
    finder.setThreshold(0.05f);  
  
    //��ȡ����ͶӰֱ��ͼ  
    result1 = finder.find(color);  
    imshow("��ɫͼ��������1��",result1);  
  
  
    //��ȡ�ڶ���ͼ�񲢼��  
    Mat color2 = imread("..\\..\\..\\source\\00_01_48_00.jpg");  
    imshow("Դͼ��2��",color2);  
    color2 = hc.colorReduce(color2,32);  
    result2 = finder.find(color2);  
    imshow("��ɫͼ��������2��",result2);  
  
//***************���Ͻ����Ϊ��������ɫ��Ϣ������Ч���ȽϺ�*********************  
  
    //������ɫ����Ϣ������ֱ��ͼ�����з���ͶӰ���  
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
    imshow("ʹ��ɫ�ȵĽ����1��",result1);  
  
    //��һ��ͼƬ  
    color2 = imread("..\\..\\..\\source\\00_01_48_00.jpg");  
    cvtColor(color2,hsv,CV_BGR2HSV);  
    result2 = finder.find(hsv,0.0f,180.0f,ch,1);  
    imshow("ʹ��ɫ�ȼ������2��",result2);  
    waitKey(0);  
    return 0;  
	waitKey(0);
	return 0;
}

