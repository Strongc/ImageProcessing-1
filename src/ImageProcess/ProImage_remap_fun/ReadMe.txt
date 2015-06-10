========================================================================
    CONSOLE APPLICATION : ProImage_remap_fun Project Overview
========================================================================

AppWizard has created this ProImage_remap_fun application for you.

This file contains a summary of what you will find in each of the files that
make up your ProImage_remap_fun application.


ProImage_remap_fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

ProImage_remap_fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

ProImage_remap_fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ProImage_remap_fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
remap( )函数会根据我们指定的映射形式，将源图像进行重映射几何变换，基于的式子如下：
		DST(X,Y)=SRC(MAPx(X,Y),MAPy(X,Y))	
需要注意，此函数不支持就地（in-place）操作。看看其原型和参数。
    C++: void remap(InputArray src, OutputArraydst, InputArray map1, InputArray map2, int interpolation, intborderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())  
        第一个参数，InputArray类型的src，输入图像，即源图像，填Mat类的对象即可，且需为单通道8位或者浮点型图像。
        第二个参数，OutputArray类型的dst，函数调用后的运算结果存在这里，即这个参数用于存放函数调用后的输出结果，需和源图片有一样的尺寸和类型。
        第三个参数，InputArray类型的map1，它有两种可能的表示对象。

                表示点（x，y）的第一个映射。
                表示CV_16SC2 , CV_32FC1 或CV_32FC2类型的X值。

        第四个参数，InputArray类型的map2，同样，它也有两种可能的表示对象，而且他是根据map1来确定表示那种对象。

                若map1表示点（x，y）时。这个参数不代表任何值。
                表示CV_16UC1 , CV_32FC1类型的Y值（第二个值）。

        第五个参数，int类型的interpolation,插值方式，之前的resize( )函数中有讲到，需要注意，resize( )函数中提到的INTER_AREA插值方式在这里是不支持的，所以可选的插值方式如下：

                INTER_NEAREST - 最近邻插值
                INTER_LINEAR – 双线性插值（默认值）
                INTER_CUBIC – 双三次样条插值（逾4×4像素邻域内的双三次插值）
                INTER_LANCZOS4 -Lanczos插值（逾8×8像素邻域的Lanczos插值）

        第六个参数，int类型的borderMode，边界模式，有默认值BORDER_CONSTANT，表示目标图像中“离群点（outliers）”的像素值不会被此函数修改。
        第七个参数，const Scalar&类型的borderValue，当有常数边界时使用的值，其有默认值Scalar( )，即默认值为0。
