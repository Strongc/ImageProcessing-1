// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

string pHashValue(Mat &src)
{
	Mat img ,dst;
	string rst(64,'\0');
	double dIdex[64];
	double mean = 0.0;
	int k = 0;
	if(src.channels()==3)
	{
		cvtColor(src,src,CV_BGR2GRAY);
		img = Mat_<double>(src);
	}	 
	else
	{
		img = Mat_<double>(src);
	}     

	/* ��һ�������ųߴ磬����ΪSize(32,32)��Size(8,8)��Ҳ���Ը��ߣ���Ҫ��Ϊ����߼���Ч��*/
	resize(img, img, Size(32,32));

	/* �ڶ�������ɢ���ұ任��DCTϵ����ȡ*/
	dct(img, dst);	

	/* ����������ȡDCTϵ����ֵ�����Ͻ�8*8�����DCTϵ����*/
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) 
		{
			dIdex[k] = dst.at<double>(i, j);
			mean += dst.at<double>(i, j)/64;
			++k;
		}
	}

	/* ���Ĳ��������ϣֵ��*/
	for (int i =0;i<64;++i)
	{
		if (dIdex[i]>=mean)
		{
			rst[i]='1';
		}
		else
		{
			rst[i]='0';
		}
	}
	return rst;
}
//�����������
int HanmingDistance(string &str1,string &str2)
{
	if((str1.size()!=64)||(str2.size()!=64))
		return -1;
	int difference = 0;
	for(int i=0;i<64;i++)
	{
		if(str1[i]!=str2[i])
			difference++;
	}
	return difference;
}

template<typename T>
class MyTemp
{
public:
	T addFun(T a,T b)
	{
		T _b = a+b;
		return _b;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
// 	Mat src_image  =imread("3.jpg"); 
// 	Mat src_image1 = imread("2.jpg"); 
// 
// 	std::string _imagesrc = pHashValue(src_image);
// 	std::string _imagesrc2 = pHashValue(src_image1);
// 
// 	int s = HanmingDistance(_imagesrc,_imagesrc2);
// 	cout<< s<<endl;
// 	MyTemp<std::string> _sd;
// 	std::string _s = _sd.addFun("10.0","12.0");


	time_t t = time(0); 
	char tmp[1024]={'\0'}; 
	strftime( tmp, sizeof(tmp), "%Y/%m/%d %X %A �����%j�� �����%m�µ�%d�� �����%U��ÿ%w�� %z",localtime(&t) ); 
	puts( tmp ); 
	return 0; 

	return 0;
}

