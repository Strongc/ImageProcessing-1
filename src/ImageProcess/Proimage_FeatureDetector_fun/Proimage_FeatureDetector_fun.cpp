// Proimage_FeatureDetector_fun.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
// 	initModule_nonfree();//if use SIFT or SURF  
// 	Ptr<FeatureDetector> detector = FeatureDetector::create( "SIFT" );  
// 	Ptr<DescriptorExtractor> descriptor_extractor = DescriptorExtractor::create( "SIFT" );  
// 	Ptr<DescriptorMatcher> descriptor_matcher = DescriptorMatcher::create( "BruteForce" );  
// 	if( detector.empty() || descriptor_extractor.empty() )  
// 		throw runtime_error("fail to create detector!");  
// 
// 	Mat img1 = imread("E:\\DayBreakZcs\\ImageProcessing\\source\\test3.jpg");  
// 	Mat img2 = imread("E:\\DayBreakZcs\\ImageProcessing\\source\\test2.jpg");  
// 
// 	//detect keypoints;  
// 	vector<KeyPoint> keypoints1,keypoints2;  
// 	detector->detect( img1, keypoints1 );  
// 	detector->detect( img2, keypoints2 );  
// 	cout <<"img1:"<< keypoints1.size() << " points  img2:" <<keypoints2.size()   
// 		<< " points" << endl << ">" << endl;  
// 
// 	//compute descriptors for keypoints;  
// 	cout << "< Computing descriptors for keypoints from images..." << endl;  
// 	Mat descriptors1,descriptors2;  
// 	descriptor_extractor->compute( img1, keypoints1, descriptors1 );  
// 	descriptor_extractor->compute( img2, keypoints2, descriptors2 );  
// 
// 	cout<<endl<<"Descriptors Size: "<<descriptors2.size()<<" >"<<endl;  
// 	cout<<endl<<"Descriptor's Column: "<<descriptors2.cols<<endl  
// 		<<"Descriptor's Row: "<<descriptors2.rows<<endl;  
// 	cout << ">" << endl;  
// 
// 	//Draw And Match img1,img2 keypoints  
// 	Mat img_keypoints1,img_keypoints2;  
// 	drawKeypoints(img1,keypoints1,img_keypoints1,Scalar::all(-1),0);  
// 	drawKeypoints(img2,keypoints2,img_keypoints2,Scalar::all(-1),0);  
// 	imshow("Box_in_scene keyPoints",img_keypoints1);  
// 	imshow("Box keyPoints",img_keypoints2);  
// 
// 	descriptor_extractor->compute( img1, keypoints1, descriptors1 );    
// 	vector<DMatch> matches;  
// 	descriptor_matcher->match( descriptors1, descriptors2, matches );  
// 
// 	Mat img_matches;  
// 	drawMatches(img1,keypoints1,img2,keypoints2,matches,img_matches,Scalar::all(-1),CV_RGB(255,255,255),Mat(),4);  
// 
// 	imshow("Mathc",img_matches);  
// 	waitKey(0);  
// 	return 0;  
// 	return 0;
	Mat image = imread("E:\\DayBreakZcs\\ImageProcessing\\source\\test4.jpg");  
	Mat descriptors;  
	vector<KeyPoint> keypoints;  
	SimpleBlobDetector::Params params;  
	params.minThreshold = 10;  
	params.maxThreshold = 100;  
	params.thresholdStep = 10;  
	params.minArea = 10;   
	params.minConvexity = 0.3;  
	params.minInertiaRatio = 0.01;  
	params.maxArea = 8000;  
	params.maxConvexity = 10;  
	params.filterByColor = false;  
	params.filterByCircularity = false;  
	SimpleBlobDetector blobDetector( params );  
	blobDetector.create("SimpleBlob");  
	blobDetector.detect( image, keypoints );  
	drawKeypoints(image, keypoints, image, Scalar(255,0,0));  
	imshow("Mathc",image);  
	waitKey(0); 
}

