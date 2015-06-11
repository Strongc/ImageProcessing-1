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
特征检测器 FeatureDetector 
OpenCV提供FeatureDetector实现特征检测及匹配

[cpp] view plaincopy在CODE上查看代码片派生到我的代码片

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


FeatureDetetor是虚类，通过定义FeatureDetector的对象可以使用多种特征检测方法。通过create()函数调用：

[cpp] view plaincopy在CODE上查看代码片派生到我的代码片

    Ptr<FeatureDetector> FeatureDetector::create(const string& detectorType);  

OpenCV 2.4.3提供了10种特征检测方法：

    "FAST" – FastFeatureDetector
    "STAR" – StarFeatureDetector
    "SIFT" – SIFT (nonfree module)
    "SURF" – SURF (nonfree module)
    "ORB" – ORB
    "MSER" – MSER
    "GFTT" – GoodFeaturesToTrackDetector
    "HARRIS" – GoodFeaturesToTrackDetector with Harris detector enabled
    "Dense" – DenseFeatureDetector
    "SimpleBlob" – SimpleBlobDetector

图片中的特征大体可分为三种：点特征、线特征、块特征。
FAST算法是Rosten提出的一种快速提取的点特征[1]，Harris与GFTT也是点特征，更具体来说是角点特征（参考这里）。
SimpleBlob是简单块特征，可以通过设置SimpleBlobDetector的参数决定提取图像块的主要性质，提供5种：
颜色 By color、面积 By area、圆形度 By circularity、最大inertia （不知道怎么翻译）与最小inertia的比例 By ratio of the minimum inertia to maximum inertia、以及凸性 By convexity.
最常用的当属SIFT，尺度不变特征匹配算法（参考这里）；以及后来发展起来的SURF，都可以看做较为复杂的块特征。这两个算法在OpenCV nonfree的模块里面，需要在附件引用项中添加opencv_nonfree243.lib，同时在代码中加入：
[cpp] view plaincopy在CODE上查看代码片派生到我的代码片

    initModule_nonfree();  

至于其他几种算法，我就不太了解了 ^_^