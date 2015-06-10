========================================================================
    CONSOLE APPLICATION : ProImage_SURF_Fun Project Overview
========================================================================

AppWizard has created this ProImage_SURF_Fun application for you.

This file contains a summary of what you will find in each of the files that
make up your ProImage_SURF_Fun application.


ProImage_SURF_Fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

ProImage_SURF_Fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

ProImage_SURF_Fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ProImage_SURF_Fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
        这个示例程涉及到如下三个方面：

         

            使用 FeatureDetector 接口来发现感兴趣点。
            使用 SurfFeatureDetector 以及其函数 detect 来实现检测过程
            使用函数 drawKeypoints 绘制检测到的关键点。