========================================================================
    CONSOLE APPLICATION : Proimage_GMM_1_alg Project Overview
========================================================================

AppWizard has created this Proimage_GMM_1_alg application for you.

This file contains a summary of what you will find in each of the files that
make up your Proimage_GMM_1_alg application.


Proimage_GMM_1_alg.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

Proimage_GMM_1_alg.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

Proimage_GMM_1_alg.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named Proimage_GMM_1_alg.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////
高斯混合模型概述

高斯密度函数估计是一种参数化模型。有单高斯模型（Single Gaussian Model, SGM）和高斯混合模型（Gaussian mixture model，GMM）两类。类似于聚类，根据高斯概率密度函数（PDF，见公式1）参数的不同，每一个高斯模型可以看作一种类别，输入一个样本 ，即可通过PDF计算其值，然后通过一个阈值来判断该样本是否属于高斯模型。很明显，SGM适合于仅有两类别问题的划分，而GMM由于具有多个模型，划分更为精细，适用于多类别的划分，可以应用于复杂对象建模。

下面以视频前景分割应用场景为例，说明SGM与GMM在应用上的优劣比较：

l        SGM需要进行初始化，如在进行视频背景分割时，这意味着如果人体在前几帧就出现在摄像头前，人体将会被初始化为背景，而使模型无法使用；

l        SGM只能进行微小性渐变，而不可突变。如户外亮度随时间的渐变是可以适应的，如果在明亮的室内突然关灯，单高斯模型就会将整个室内全部判断为前景。又如，若在监控范围内开了一辆车，并在摄像头下开始停留。由于与模型无法匹配，车会一直被视为前景。当车过很长时间离去时，由于车停留点的亮度发生了很大的变化，因此已经无法与先前的背景模型相匹配；

l        SGM无法适应背景有多个状态，如窗帘，风吹的树叶。单高斯模型无法表示这种情况，而使得前背景检测混乱，而GMM能够很好地描述不同状态；

l        相对于单高斯模型的自适应变化，混合高斯模型的自适应变化要健壮的多。它能解决单高斯模型很多不能解决的问题。如无法解决同一样本点的多种状态，无法进行模型状态转化等。