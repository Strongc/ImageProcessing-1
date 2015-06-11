========================================================================
    CONSOLE APPLICATION : Proimage_FeatureDetector_fun Project Overview
========================================================================

AppWizard has created this Proimage_FeatureDetector_fun application for you.

This file contains a summary of what you will find in each of the files that
make up your Proimage_FeatureDetector_fun application.


Proimage_FeatureDetector_fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Proimage_FeatureDetector_fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Proimage_FeatureDetector_fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Proimage_FeatureDetector_fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
��������� FeatureDetector 
OpenCV�ṩFeatureDetectorʵ��������⼰ƥ��

[cpp] view plaincopy��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ

    class CV_EXPORTS FeatureDetector  
    {  
    public:  
        virtual ~FeatureDetector();  
        void detect( const Mat& image, vector<KeyPoint>& keypoints,  
            const Mat& mask=Mat() ) const;  
        void detect( const vector<Mat>& images,  
            vector<vector<KeyPoint> >& keypoints,  
            const vector<Mat>& masks=vector<Mat>() ) const;  
        virtual void read(const FileNode&);  
        virtual void write(FileStorage&) const;  
        static Ptr<FeatureDetector> create( const string& detectorType );  
    protected:  
        ...  
    };  


FeatureDetetor�����࣬ͨ������FeatureDetector�Ķ������ʹ�ö���������ⷽ����ͨ��create()�������ã�

[cpp] view plaincopy��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ

    Ptr<FeatureDetector> FeatureDetector::create(const string& detectorType);  

OpenCV 2.4.3�ṩ��10��������ⷽ����

    "FAST" �C FastFeatureDetector
    "STAR" �C StarFeatureDetector
    "SIFT" �C SIFT (nonfree module)
    "SURF" �C SURF (nonfree module)
    "ORB" �C ORB
    "MSER" �C MSER
    "GFTT" �C GoodFeaturesToTrackDetector
    "HARRIS" �C GoodFeaturesToTrackDetector with Harris detector enabled
    "Dense" �C DenseFeatureDetector
    "SimpleBlob" �C SimpleBlobDetector

ͼƬ�е���������ɷ�Ϊ���֣�������������������������
FAST�㷨��Rosten�����һ�ֿ�����ȡ�ĵ�����[1]��Harris��GFTTҲ�ǵ���������������˵�ǽǵ��������ο������
SimpleBlob�Ǽ򵥿�����������ͨ������SimpleBlobDetector�Ĳ���������ȡͼ������Ҫ���ʣ��ṩ5�֣�
��ɫ By color����� By area��Բ�ζ� By circularity�����inertia ����֪����ô���룩����Сinertia�ı��� By ratio of the minimum inertia to maximum inertia���Լ�͹�� By convexity.
��õĵ���SIFT���߶Ȳ�������ƥ���㷨���ο�������Լ�������չ������SURF�������Կ�����Ϊ���ӵĿ��������������㷨��OpenCV nonfree��ģ�����棬��Ҫ�ڸ��������������opencv_nonfree243.lib��ͬʱ�ڴ����м��룺
[cpp] view plaincopy��CODE�ϲ鿴����Ƭ�������ҵĴ���Ƭ

    initModule_nonfree();  

�������������㷨���ҾͲ�̫�˽��� ^_^