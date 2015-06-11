========================================================================
    CONSOLE APPLICATION : Proimage_ZFCompare_fun Project Overview
========================================================================

AppWizard has created this Proimage_ZFCompare_fun application for you.

This file contains a summary of what you will find in each of the files that
make up your Proimage_ZFCompare_fun application.


Proimage_ZFCompare_fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Proimage_ZFCompare_fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Proimage_ZFCompare_fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Proimage_ZFCompare_fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
openCV中提供了cvCompareHist函数用以对比两个直方图的相似度：
cvCompareHist的结果为【0,1】的浮点数，越小表示两幅图匹配度越高，0.0时两幅图精确匹配。（可以试验两幅完全一样的图即为0.0）。
应用
通过对比我们可以设置EMD的阈值来判定皮肤或手的ROI。《Learnning OpenCV》后面有相应的练习题：收集手的肤色直方图，对比室内，室外手的直方图的EMD距离，利用这些测量值设置一个距离阈值。
a.利用该阈值检测第三幅图（如室外阴影），看能能否很好的检测肤色直方图。
b.随机选择不是肤色的背景块直方图，观测EMD变化，试验与真实肤色对比时能否很好的拒绝背景。
如上也即是直方图对比可以应用的场景。