========================================================================
    CONSOLE APPLICATION : Proimge_PrySegmentation_fun Project Overview
========================================================================

AppWizard has created this Proimge_PrySegmentation_fun application for you.

This file contains a summary of what you will find in each of the files that
make up your Proimge_PrySegmentation_fun application.


Proimge_PrySegmentation_fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Proimge_PrySegmentation_fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Proimge_PrySegmentation_fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Proimge_PrySegmentation_fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
PyrSegmentation
�ý�����ʵ��ͼ��ָ�

void cvPyrSegmentation( IplImage* src, IplImage* dst,
CvMemStorage* storage, CvSeq** comp,
int level, double threshold1, double threshold2 );
src
����ͼ��.
dst
���ͼ��.
storage
Storage: �洢��ͨ���������н��
comp
�ָ�����������ָ�� components.
level
������������������
threshold1
�������ӵĴ�����ֵ
threshold2
�ָ�صĴ�����ֵ
���� cvPyrSegmentation ʵ���˽�����������ͼ��ָ������������ level ָ��������������� p(c(a),c(b))<threshold1,���ڲ� i �����ص� a ���������ڲ�ĸ������� b ֮������ӱ�����������

��������Ӳ��������Ǳ����뵽ĳЩ���С����p(c(A),c(B))<threshold2�����κ������ָ� A �� B ����ͬһ�ء�

�������ͼ��ֻ��һ��ͨ������ô

p(c1,c2)=|c1-c2|.
�������ͼ���е���ͨ�����졢�̡�����������

p(c1,c2)=0,3��(c1r-c2r)+0,59��(c1g-c2g)+0,11��(c1b-c2b) .
ÿһ���ؿ����ж�����Ӳ�����ͼ�� src �� dst Ӧ���� 8-���ء���ͨ�� �� 3-ͨ��ͼ���Ҵ�Сһ��

 