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
��ˮ��ָ��㷨
    ��ˮ��ָ��㷨��Ҫ��������ǰ�㷨�ṩ��ǣ��ñ������ָ����Щ����������Ŀ�꣬��Щ���������Ǳ����ȵȣ���ˮ��ָ��㷨�ķָ�Ч�������������ṩ�ı�ǡ�OpenCv�еĺ���cvWatershedʵ���˸��㷨�������������£�

void cvWatershed(const CvArr * image, CvArr * markers)

���У�imageΪ8Ϊ��ͨ���Ĳ�ɫͼ��
      markers�ǵ�ͨ������ͼ�����ò�ͬ������������ǲ�ͬ����������Ĵ�����ʾ�������Ӧ����¼��������ɱ��ͼ��