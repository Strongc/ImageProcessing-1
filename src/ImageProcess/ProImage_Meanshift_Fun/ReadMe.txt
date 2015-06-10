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
一.ROI介绍

在OpenCV中我们能够非常方便地获取指定ROI区域的子图像。如果你对图像设置了ROI，那么，Opencv的大多数函数只在该ROI区域内运算（只处理该ROI区域），如果没设ROI的话，就会出来整幅图像。
ROI非常有用，例如我们想把图像中的人脸扣出来，进行人脸识别。需要注意的时候，ROI一定在图像内部，而不能超出图像的范围。

对图像设定ROI的函数是：

cvSetImageROI(IplImage* src,CvRect rect);
src表示的是源图像，rect只的是ROI区域。

如果要取消ROI区域，那么使用函数：

cvResetImageROI(IplImage* src);
这个函数，就把src上的ROI区域取消掉。

图像的剪切有多种措施，其中利用ROI的措施

第一步：将必需剪切的图像图像不局部设置为ROI

cvSetImageROI(src , cvRect(x,y,width,height));

第二步：修建一个与必需剪切的图像局部同样大小的新图像

cvCreateImage(cvSize(width,height),IPL_DEPTH,nchannels);

第三步：将源图像复制到修建的图像中

cvCopy(src,dst,0);

第四步：释放ROI区域

cvResetIamgeROI(src);

缩放可用cvResize();
