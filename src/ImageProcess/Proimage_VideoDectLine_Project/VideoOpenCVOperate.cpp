#include "stdafx.h"
#include "VideoOpenCVOperate.h"


VideoOpenCVOperate::VideoOpenCVOperate()
:mCapture(NULL)
,frame_count(0)
{

}

VideoOpenCVOperate::~VideoOpenCVOperate()
{
	ReleaseOperCV();
}

int VideoOpenCVOperate::initVideoOpenCVOperate()
{
	mVideoInfo.height = 0;
	mVideoInfo.width = 0;
	mVideoInfo.VIDuration = 0;
	frame_count = 0;
	if(mCapture)
		cvReleaseCapture(&mCapture);
	return 0;
}

int VideoOpenCVOperate::openVideoOpenCVFile( char* paht )
{
	frame_count = 0;
	mCapture = cvCreateFileCapture(paht);  //读取视频
	if(mCapture==NULL) 
	{
		return -1;
	}   

	double frames=cvGetCaptureProperty(mCapture,CV_CAP_PROP_FRAME_COUNT);//读取视频中有多少帧
	IplImage * frame;
	frame = cvQueryFrame(mCapture);//抓取帧
	FillVideoInfo(frames,frame->width,frame->height,frame->nChannels);
	return 0;
}

IplImage* VideoOpenCVOperate::getVideoOpenCVFrame(int conut)
{
	cvSetCaptureProperty(mCapture, CV_CAP_PROP_POS_FRAMES, conut);//设置视频帧的读取位置
	IplImage * frame1;
	frame1 = cvQueryFrame(mCapture);//抓取帧
	if(frame1 == NULL)
		return NULL;
	else
		return frame1;	
}

bool VideoOpenCVOperate::FillVideoInfo(double duration,int width, int height,int Channels)
{
	mVideoInfo.width = width;
	mVideoInfo.height = height;
	mVideoInfo.VIDuration = (int64_t)duration;
	mVideoInfo.Channels = Channels;
	double _fps=cvGetCaptureProperty(mCapture, CV_CAP_PROP_FPS );   //读取视频的帧率
	double _vfps = 1000 / _fps;                                        //计算每帧播放的时间
	mVideoInfo.vfps = _vfps;
	mVideoInfo.fps = (int)_fps;
	return 0;
}

void VideoOpenCVOperate::ReleaseOperCV()
{
	if(mCapture!=NULL)
		cvReleaseCapture(&mCapture);
}

double VideoOpenCVOperate::getVideoFrameTime()
{
	double _tepFrameTime =cvGetCaptureProperty(mCapture, CV_CAP_PROP_POS_MSEC );   //读取视频的帧率
	return _tepFrameTime;
}
