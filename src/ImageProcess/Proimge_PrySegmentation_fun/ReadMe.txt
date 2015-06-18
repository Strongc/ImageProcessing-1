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
用金字塔实现图像分割

void cvPyrSegmentation( IplImage* src, IplImage* dst,
CvMemStorage* storage, CvSeq** comp,
int level, double threshold1, double threshold2 );
src
输入图像.
dst
输出图像.
storage
Storage: 存储连通部件的序列结果
comp
分割部件的输出序列指针 components.
level
建立金字塔的最大层数
threshold1
建立连接的错误阈值
threshold2
分割簇的错误阈值
函数 cvPyrSegmentation 实现了金字塔方法的图像分割。金字塔建立到 level 指定的最大层数。如果 p(c(a),c(b))<threshold1,则在层 i 的象素点 a 和它的相邻层的父亲象素 b 之间的连接被建立起来，

定义好连接部件后，它们被加入到某些簇中。如果p(c(A),c(B))<threshold2，则任何两个分割 A 和 B 属于同一簇。

如果输入图像只有一个通道，那么

p(c1,c2)=|c1-c2|.
如果输入图像有单个通道（红、绿、兰），那幺

p(c1,c2)=0,3·(c1r-c2r)+0,59·(c1g-c2g)+0,11·(c1b-c2b) .
每一个簇可以有多个连接部件。图像 src 和 dst 应该是 8-比特、单通道 或 3-通道图像，且大小一样

 