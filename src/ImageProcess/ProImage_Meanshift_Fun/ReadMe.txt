========================================================================
    CONSOLE APPLICATION : ProImage_Meanshift_Fun Project Overview
========================================================================

AppWizard has created this ProImage_Meanshift_Fun application for you.

This file contains a summary of what you will find in each of the files that
make up your ProImage_Meanshift_Fun application.


ProImage_Meanshift_Fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

ProImage_Meanshift_Fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

ProImage_Meanshift_Fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ProImage_Meanshift_Fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
һ.ROI����

��OpenCV�������ܹ��ǳ�����ػ�ȡָ��ROI�������ͼ��������ͼ��������ROI����ô��Opencv�Ĵ��������ֻ�ڸ�ROI���������㣨ֻ�����ROI���򣩣����û��ROI�Ļ����ͻ��������ͼ��
ROI�ǳ����ã������������ͼ���е������۳�������������ʶ����Ҫע���ʱ��ROIһ����ͼ���ڲ��������ܳ���ͼ��ķ�Χ��

��ͼ���趨ROI�ĺ����ǣ�

cvSetImageROI(IplImage* src,CvRect rect);
src��ʾ����Դͼ��rectֻ����ROI����

���Ҫȡ��ROI������ôʹ�ú�����

cvResetImageROI(IplImage* src);
����������Ͱ�src�ϵ�ROI����ȡ������

ͼ��ļ����ж��ִ�ʩ����������ROI�Ĵ�ʩ

��һ������������е�ͼ��ͼ�񲻾ֲ�����ΪROI

cvSetImageROI(src , cvRect(x,y,width,height));

�ڶ������޽�һ���������е�ͼ��ֲ�ͬ����С����ͼ��

cvCreateImage(cvSize(width,height),IPL_DEPTH,nchannels);

����������Դͼ���Ƶ��޽���ͼ����

cvCopy(src,dst,0);

���Ĳ����ͷ�ROI����

cvResetIamgeROI(src);

���ſ���cvResize();
