========================================================================
    CONSOLE APPLICATION : ProImge_grabcut_fun Project Overview
========================================================================

AppWizard has created this ProImge_grabcut_fun application for you.

This file contains a summary of what you will find in each of the files that
make up your ProImge_grabcut_fun application.


ProImge_grabcut_fun.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

ProImge_grabcut_fun.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

ProImge_grabcut_fun.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named ProImge_grabcut_fun.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
　grabcut是在graph cut基础上改进的一种图像分割算法，它同样是基于图割理论的，关于图割的简单介绍可以参考本人前面的博文：一些知识点的初步理解_8(Graph Cuts,ing...) 。稍微看了下grabcut方面的论文，论文中一般都是在graph cut上作改进，比如说引入了GMM模型等。同graph cut一样，在使用grabcut是也是需要人机交互的，即人工先给定一定区域的目标或者背景，然后送给grabcut算法来分割。通过实验发现，其分割效果一般般，且分割速度比较慢，一张普通大小的图片差不多需要1s左右的时间，

 

　　实验说明

　　因为在使用该算法的过程中需要人机交互，所以需要用到很多鼠标键盘的操作，因此这些GUI操作的逻辑关系一定要处理好。其中最主要的GUI设计就在鼠标键盘响应函数中，在设置关于图片的鼠标键盘响应函数时，其函数的参数必须满足一定的类型，如下所示：

　　mouseClick (int event, int x, int y, int flags, void* param); 

　　其中event是 CV_EVENT_*变量之一； x和y是鼠标指针在图像坐标系的坐标，并不是整个窗口的坐标；  flags是CV_EVENT_FLAG的组合，  即表示所有的按键，一般情况下是固定的；  param是用户定义的传递到cvSetMouseCallback函数调用的参数，这通常在回调函数中都有类似这种功能的的参数。

　  Grabcut在opencv中核心算法函数为：
     void cv::grabCut( const Mat& img, Mat& mask, Rect rect, Mat& bgdModel, Mat& fgdModel, int iterCount, int mode )
　　这里引用网友的博文学习OpenCV——grabcut来解释该函数的用法：
　　img——待分割的源图像，必须是8位3通道（CV_8UC3）图像，在处理的过程中不会被修改；
　　mask——掩码图像，如果使用掩码进行初始化，那么mask保存初始化掩码信息；在执行分割的时候，也可以将用户交互所设定的前景与背景保存到mask中，然后再传入grabCut函数；在处理结束之后，mask中会保存结果。mask只能取以下四种值：
　　GCD_BGD（=0），背景；
　　GCD_FGD（=1），前景；
　　GCD_PR_BGD（=2），可能的背景；
　　GCD_PR_FGD（=3），可能的前景。
　　如果没有手工标记GCD_BGD或者GCD_FGD，那么结果只会有GCD_PR_BGD或GCD_PR_FGD；
　　rect——用于限定需要进行分割的图像范围，只有该矩形窗口内的图像部分才被处理；
　　bgdModel——背景模型，如果为null，函数内部会自动创建一个bgdModel；bgdModel必须是单通道浮点型（CV_32FC1）图像，且行数只能为1，列数只能为13x5；
　　fgdModel——前景模型，如果为null，函数内部会自动创建一个fgdModel；fgdModel必须是单通道浮点型（CV_32FC1）图像，且行数只能为1，列数只能为13x5；
　　iterCount——迭代次数，必须大于0；
　　mode——用于指示grabCut函数进行什么操作，可选的值有：
　　GC_INIT_WITH_RECT（=0），用矩形窗初始化GrabCut；
　　GC_INIT_WITH_MASK（=1），用掩码图像初始化GrabCut；
　　GC_EVAL（=2），执行分割。