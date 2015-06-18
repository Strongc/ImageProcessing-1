========================================================================
    CONSOLE APPLICATION : Proimage_Watershed_fun Project Overview
========================================================================

AppWizard has created this Proimage_Watershed_fun application for you.

This file contains a summary of what you will find in each of the files that
make up your Proimage_Watershed_fun application.


Proimage_Watershed_fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Proimage_Watershed_fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Proimage_Watershed_fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Proimage_Watershed_fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
分水岭分割算法
    分水岭分割算法需要您或者先前算法提供标记，该标记用于指定哪些大致区域是目标，哪些大致区域是背景等等；分水岭分割算法的分割效果严重依赖于提供的标记。OpenCv中的函数cvWatershed实现了该算法，函数定义如下：

void cvWatershed(const CvArr * image, CvArr * markers)

其中：image为8为三通道的彩色图像；
      markers是单通道整型图像，它用不同的正整数来标记不同的区域，下面的代码演示了如果响应鼠标事件，并生成标记图像。