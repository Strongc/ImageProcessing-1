/**************************************************************************
   *Copyright(C),2012-2013,zcs
   *GUID:8daa30f5-ccbe-4e11-aa1a-b8b5947ac3f1
   *FileName:VideoOpenCVOperate.h
   *BaseClassName:NULL
   *Author:zhang changsheng
   *Version:V1.0
   *Date:2013/9/5 10:26
   *Description:����opencv�Ľ�����Ƶ
   *Others:
   *Function List:
      1.
      2.
   *History:
      1.Date:
        Author:
        Modification:
 *************************************************************************/
#pragma once

typedef struct VideoAndPictrueInfo
{
	std::string inputVideoPicturePath;
	int width;
	int height;
	int64_t VIDuration;
	int Channels;
	double vfps;
	int fps;
	VideoAndPictrueInfo()
		:width(0)
		,height(0)
		,VIDuration(0)
		,Channels(-1)
		,inputVideoPicturePath("")
		,vfps(0.0)
		,fps(0)
	{

	}
	void cleanData()
	{
		inputVideoPicturePath = "";
		width = -1;
		height = -1;
		VIDuration = -1;
		Channels = -1;
		vfps = 0.0;
		fps = 0;
	}
}VideoAndPictrueInfo_t;

class VideoOpenCVOperate
{
public:
	VideoOpenCVOperate();
	~VideoOpenCVOperate();
public:
		/**********************************************************************
	     *FunGUID:27da40a0-eef5-463d-9674-1761294ab861
		 *Function:VideoOpenCVOperate::initVideoOpenCVOperate
	     *Access:    public 
		 *FunDescription:��ʼ�������������
	     *Qualifier:
		 *@return Face_Result_E
		 *********************************************************************/
	int initVideoOpenCVOperate();
		/**********************************************************************
	     *FunGUID:883f3ac8-7b55-43eb-863a-46891c20e20b
		 *Function:VideoOpenCVOperate::openVideoOpenCVFile
	     *Access:    public 
		 *FunDescription:����Ƶ�ļ��������Ƶ��Ϣ
	     *Qualifier:
		 *@param char * paht IN ��Ƶ·��
		 *@return Face_Result_E
		 *********************************************************************/
	int openVideoOpenCVFile(char* paht);
		/**********************************************************************
	     *FunGUID:809341cc-dbc8-4ed3-96b6-aae7f08b023d
		 *Function:VideoOpenCVOperate::getVideoInfo
	     *Access:    public 
		 *FunDescription:������Ƶ��Ϣ
	     *Qualifier:
		 *@return VideoInfo_t
		 *********************************************************************/
	VideoAndPictrueInfo_t	  getVideoInfo(){return mVideoInfo;}
		/**********************************************************************
	     *FunGUID:30c3dcde-87c7-4a2b-93ab-aed369ce2b40
		 *Function:VideoOpenCVOperate::getVideoOpenCVFrame
	     *Access:    public 
		 *FunDescription:����ָ����֡
	     *Qualifier:
		 *@param int conut
		 *@return IplImage*
		 *********************************************************************/
	IplImage* getVideoOpenCVFrame(int conut);
	void ReleaseOperCV();
	double getVideoFrameTime();
private:

		/**********************************************************************
	     *FunGUID:196a235a-a9a1-4957-a7fb-366be34a4730
		 *Function:VideoOpenCVOperate::FillVideoInfo
	     *Access:    private 
		 *FunDescription:�����Ƶ��Ϣ
	     *Qualifier:
		 *@param double duration IN ��֡��
		 *@param int width IN ���
		 *@param int height
		 *@param int Channels IN ͨ��
		 *@return bool
		 *********************************************************************/
	bool FillVideoInfo(double duration,int width, int height,int Channels);
private:
	VideoAndPictrueInfo_t mVideoInfo;
	CvCapture* mCapture;
	int frame_count;
};
