// Proimage_GMM_1_alg.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <stdio.h>
#include <cv.h>
#include <cxcore.h>
#include <highgui.h>
#include <cvaux.h>//必须引此头文件
int main( int argc, char** argv )
{ 

 	//IplImage* pFrame = NULL;   
 	//IplImage* pFrImg = NULL; 
 	//IplImage* pBkImg = NULL;   
 	//CvCapture* pCapture = NULL;   
 	//int nFrmNum = 0;
 
 	//cvNamedWindow("video", 1); 
 	//cvNamedWindow("background",1); 
 	//cvNamedWindow("foreground",1);   
 	//cvMoveWindow("video", 30, 0); 
 	//cvMoveWindow("background", 360, 0); 
 	//cvMoveWindow("foreground", 690, 0);
 	//if( argc > 2 )   
 	//{     
 	//	fprintf(stderr, "Usage: bkgrd [video_file_name]\n");     
 	//	return -1;   
 	//}
 
 
 	//打开视频文件 
 	//if(argc == 2)   
 	//	if( !(pCapture = cvCaptureFromFile(argv[1])))     
 	//	{   
 	//		fprintf(stderr, "Can not open video file %s\n", argv[1]);   
 	//		return -2;     
 	//	}
 	//	打开摄像头 
 	//	if (argc == 1)   
 	//		if( !(pCapture = cvCaptureFromCAM(1)))     
 	//		{   
 	//			fprintf(stderr, "Can not open camera.\n");   
 	//			return -2;     
 	//		}   
 	//		Sleep(5000);
 	//		初始化高斯混合模型参数
 	//		CvGaussBGModel* bg_model=NULL;
 
 	//		while(pFrame = cvQueryFrame( pCapture ))   
 	//		{     
 	//			nFrmNum++;           
 	//			if(nFrmNum == 1)   
 	//			{    
 	//				pBkImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,3);   
 	//				pFrImg = cvCreateImage(cvSize(pFrame->width, pFrame->height),  IPL_DEPTH_8U,1);     
 
 
 	//				高斯背景建模，pFrame可以是多通道图像也可以是单通道图像
 	//				cvCreateGaussianBGModel函数返回值为CvBGStatModel*，
 	//				需要强制转换成CvGaussBGModel*
 	//				bg_model = (CvGaussBGModel*)cvCreateGaussianBGModel(pFrame, 0);
 	//			}     
 	//			else
 	//			{    
 	//				更新高斯模型
 	//				cvUpdateBGStatModel(pFrame, (CvBGStatModel *)bg_model );
 
 	//				pFrImg为前景图像，只能为单通道
 	//				pBkImg为背景图像，可以为单通道或与pFrame通道数相同
 	//				cvCopy(bg_model->foreground,pFrImg,0);
 	//				cvCopy(bg_model->background,pBkImg,0);
 
 	//				把图像正过来
 	//				pBkImg->origin=1;
 	//				pFrImg->origin=1;  // 这个不需要翻转（实验结果得知）
 
 	//				cvShowImage("video", pFrame);    
 	//				cvShowImage("background", pBkImg);    
 	//				cvShowImage("foreground", pFrImg);       
 	//				if( cvWaitKey(2) >= 0 )      
 	//					break;     
 	//			}     
 
 	//		}
 
 	//		释放高斯模型参数占用内存   
 	//		cvReleaseBGStatModel((CvBGStatModel**)&bg_model);
 	//		cvDestroyWindow("video"); 
 	//		cvDestroyWindow("background"); 
 	//		cvDestroyWindow("foreground");   
 	//		cvReleaseImage(&pFrImg); 
 	//		cvReleaseImage(&pBkImg);   
 	//		cvReleaseCapture(&pCapture);   
 	//		return 0;

 	std::string videoFile ="e:\\201501230819_1.mp4";  
 	CvCapture* pCapture = NULL;
 	if(argc == 2)
 	{
 	 	if( !(pCapture = cvCaptureFromFile(argv[1])))     
 	 	{   
 	 		fprintf(stderr, "Can not open video file %s\n", argv[1]);   
 	 		return -2;     
 	 	}
 	}
 	if (argc == 1)
 	{
 		if( !(pCapture = cvCaptureFromCAM(1)))     
 		{   
 			fprintf(stderr, "Can not open camera.\n");   
 			return -2;     
 		} 
 	}
 	Sleep(2000);
 	cv::BackgroundSubtractorMOG2 mog(20,16,false);  
 	cv::Mat foreground;  
 	cv::Mat background; 
 	IplImage* pFrame = NULL;
 	long frameNo = 0;
 	while (pFrame =cvQueryFrame(pCapture))  
 	{ 
 		++frameNo;  
 		cv::Mat frame(pFrame,0);
 		std::cout<<frameNo<<std::endl;  
 		mog(frame, foreground, 0.001);         
 		cv::erode(foreground, foreground, cv::Mat());  
 		cv::dilate(foreground, foreground, cv::Mat());  
  		mog.getBackgroundImage(background);
 		cv::imshow("video", foreground);  
 		cv::imshow("background", background);  
 		if (cv::waitKey(25) > 0)  
 		{ 
 			break; 
 		}
 	}
 	return 0;  
}