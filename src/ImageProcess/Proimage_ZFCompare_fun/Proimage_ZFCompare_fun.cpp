// Proimage_ZFCompare_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	//   Mat src_base, hsv_base;
	//   Mat src_test1, hsv_test1;
	//   Mat src_test2, hsv_test2;
	//   Mat hsv_half_down;
	// 
	//   /// װ�����ű���������ͬ��ͼ��
	//   ///if( argc < 4 )
	//   //  { printf("** Error. Usage: ./compareHist_Demo <image_settings0> <image_setting1> <image_settings2>\n");
	//   //    return -1;
	//   //  }
	// 
	//   src_base = imread( "3.jpg", 1 );
	//   src_test1 = imread("4.jpg", 1 );
	//   src_test2 = imread( "5.jpg", 1 );
	// 
	//   /// ת���� HSV
	//   cvtColor( src_base, hsv_base, CV_BGR2HSV );
	//   cvtColor( src_test1, hsv_test1, CV_BGR2HSV );
	//   cvtColor( src_test2, hsv_test2, CV_BGR2HSV );
	// 
	//   hsv_half_down = hsv_base( Range( hsv_base.rows/2, hsv_base.rows - 1 ), Range( 0, hsv_base.cols - 1 ) );
	// 
	//   /// ��hueͨ��ʹ��30��bin,��saturatoinͨ��ʹ��32��bin
	//   int h_bins = 50; int s_bins = 60;
	//   int histSize[] = { h_bins, s_bins };
	// 
	//   // hue��ȡֵ��Χ��0��256, saturationȡֵ��Χ��0��180
	//   float h_ranges[] = { 0, 256 };
	//   float s_ranges[] = { 0, 180 };
	// 
	//   const float* ranges[] = { h_ranges, s_ranges };
	// 
	//   // ʹ�õ�0�͵�1ͨ��
	//   int channels[] = { 0, 1 };
	// 
	//   /// ֱ��ͼ
	//   MatND hist_base;
	//   MatND hist_half_down;
	//   MatND hist_test1;
	//   MatND hist_test2;
	// 
	//   /// ����HSVͼ���ֱ��ͼ
	//   calcHist( &hsv_base, 1, channels, Mat(), hist_base, 2, histSize, ranges, true, false );
	//   normalize( hist_base, hist_base, 0, 1, NORM_MINMAX, -1, Mat() );
	// 
	//   calcHist( &hsv_half_down, 1, channels, Mat(), hist_half_down, 2, histSize, ranges, true, false );
	//   normalize( hist_half_down, hist_half_down, 0, 1, NORM_MINMAX, -1, Mat() );
	// 
	//   calcHist( &hsv_test1, 1, channels, Mat(), hist_test1, 2, histSize, ranges, true, false );
	//   normalize( hist_test1, hist_test1, 0, 1, NORM_MINMAX, -1, Mat() );
	// 
	//   calcHist( &hsv_test2, 1, channels, Mat(), hist_test2, 2, histSize, ranges, true, false );
	//   normalize( hist_test2, hist_test2, 0, 1, NORM_MINMAX, -1, Mat() );
	// 
	//   ///Ӧ�ò�ͬ��ֱ��ͼ�Աȷ���
	//   for( int i = 0; i < 4; i++ )
	//      { int compare_method = i;
	//        double base_base = compareHist( hist_base, hist_base, compare_method );
	//        double base_half = compareHist( hist_base, hist_half_down, compare_method );
	//        double base_test1 = compareHist( hist_base, hist_test1, compare_method );
	//        double base_test2 = compareHist( hist_base, hist_test2, compare_method );
	//        printf( " Method [%d] Perfect, Base-Half, Base-Test(1), Base-Test(2) : %f, %f, %f, %f \n", i, base_base, base_half , base_test1, base_test2 );
	//      }
	// 
	//   printf( "Done \n" );
	//   getchar();
	//   return 0;

	// 	IplImage * image= cvLoadImage("3.jpg");  
	// 	IplImage * image2= cvLoadImage("8.jpg");  
	// 	int hist_size=256;  
	// 	float range[] = {0,255};  
	// 	float* ranges[]={range};  
	// 
	// 	IplImage* gray_plane = cvCreateImage(cvGetSize(image),8,1);  
	// 	cvCvtColor(image,gray_plane,CV_BGR2GRAY);  
	// 	CvHistogram* gray_hist = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
	// 	cvCalcHist(&gray_plane,gray_hist,0,0);  
	// 
	// 
	// 	IplImage* gray_plane2 = cvCreateImage(cvGetSize(image2),8,1);  
	// 	cvCvtColor(image2,gray_plane2,CV_BGR2GRAY);  
	// 	CvHistogram* gray_hist2 = cvCreateHist(1,&hist_size,CV_HIST_ARRAY,ranges,1);  
	// 	cvCalcHist(&gray_plane2,gray_hist2,0,0);  
	// 
	// 	//��أ�CV_COMP_CORREL      
	// 	//������CV_COMP_CHISQR  
	// 	//ֱ��ͼ�ཻ��CV_COMP_INTERSECT  
	// 	//Bhattacharyya���룺CV_COMP_BHATTACHARYYA  
	// 	double  com=cvCompareHist(gray_hist,gray_hist2,CV_COMP_BHATTACHARYYA);  
	// 
	// 	cout<<com<<endl;  
	// 	return 0;

	int hist_size = 64;
	float range_0[]={0,256};
	float* ranges[] = { range_0 };

	IplImage *src_image  = cvLoadImage( "3.jpg", 0 );
	IplImage *src_image1 = cvLoadImage( "4.jpg", 0 );

	if( !src_image )
	{
		return -1;
	}

	CvHistogram *hist    = cvCreateHist( 1, &hist_size, CV_HIST_ARRAY, ranges, 1);
	CvHistogram *newHist = cvCreateHist( 1, &hist_size, CV_HIST_ARRAY, ranges, 1);
	CvHistogram *temp    = cvCreateHist( 1, &hist_size, CV_HIST_ARRAY, ranges, 1);

	cvCalcHist( &src_image, hist, 0, NULL );
	cvCalcHist( &src_image1,newHist, 0, NULL);

	cvSave("x.xml", hist->bins);

	CvArr *bins = cvLoad("x.xml");
	cvReleaseData(temp->bins);
	temp->mat  = *(CvMatND *) bins;
	temp->bins = &temp->mat;
	//��أ�CV_COMP_CORREL      
	//������CV_COMP_CHISQR  
	//ֱ��ͼ�ཻ��CV_COMP_INTERSECT  
	//Bhattacharyya���룺CV_COMP_BHATTACHARYYA
	double dc = cvCompareHist(hist, newHist, CV_COMP_BHATTACHARYYA);
	double dc1 = cvCompareHist(newHist, temp, CV_COMP_BHATTACHARYYA);

	printf("Original compare: %f \nChanged bins com: %f \n",dc, dc1);

	return 0;
}

