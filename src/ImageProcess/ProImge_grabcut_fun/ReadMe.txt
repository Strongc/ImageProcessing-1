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
��grabcut����graph cut�����ϸĽ���һ��ͼ��ָ��㷨����ͬ���ǻ���ͼ�����۵ģ�����ͼ��ļ򵥽��ܿ��Բο�����ǰ��Ĳ��ģ�һЩ֪ʶ��ĳ������_8(Graph Cuts,ing...) ����΢������grabcut��������ģ�������һ�㶼����graph cut�����Ľ�������˵������GMMģ�͵ȡ�ͬgraph cutһ������ʹ��grabcut��Ҳ����Ҫ�˻������ģ����˹��ȸ���һ�������Ŀ����߱�����Ȼ���͸�grabcut�㷨���ָͨ��ʵ�鷢�֣���ָ�Ч��һ��㣬�ҷָ��ٶȱȽ�����һ����ͨ��С��ͼƬ�����Ҫ1s���ҵ�ʱ�䣬

 

����ʵ��˵��

������Ϊ��ʹ�ø��㷨�Ĺ�������Ҫ�˻�������������Ҫ�õ��ܶ������̵Ĳ����������ЩGUI�������߼���ϵһ��Ҫ����á���������Ҫ��GUI��ƾ�����������Ӧ�����У������ù���ͼƬ����������Ӧ����ʱ���亯���Ĳ�����������һ�������ͣ�������ʾ��

����mouseClick (int event, int x, int y, int flags, void* param); 

��������event�� CV_EVENT_*����֮һ�� x��y�����ָ����ͼ������ϵ�����꣬�������������ڵ����ꣻ  flags��CV_EVENT_FLAG����ϣ�  ����ʾ���еİ�����һ��������ǹ̶��ģ�  param���û�����Ĵ��ݵ�cvSetMouseCallback�������õĲ�������ͨ���ڻص������ж����������ֹ��ܵĵĲ�����

��  Grabcut��opencv�к����㷨����Ϊ��
     void cv::grabCut( const Mat& img, Mat& mask, Rect rect, Mat& bgdModel, Mat& fgdModel, int iterCount, int mode )
���������������ѵĲ���ѧϰOpenCV����grabcut�����͸ú������÷���
����img�������ָ��Դͼ�񣬱�����8λ3ͨ����CV_8UC3��ͼ���ڴ���Ĺ����в��ᱻ�޸ģ�
����mask��������ͼ�����ʹ��������г�ʼ������ômask�����ʼ��������Ϣ����ִ�зָ��ʱ��Ҳ���Խ��û��������趨��ǰ���뱳�����浽mask�У�Ȼ���ٴ���grabCut�������ڴ������֮��mask�лᱣ������maskֻ��ȡ��������ֵ��
����GCD_BGD��=0����������
����GCD_FGD��=1����ǰ����
����GCD_PR_BGD��=2�������ܵı�����
����GCD_PR_FGD��=3�������ܵ�ǰ����
�������û���ֹ����GCD_BGD����GCD_FGD����ô���ֻ����GCD_PR_BGD��GCD_PR_FGD��
����rect���������޶���Ҫ���зָ��ͼ��Χ��ֻ�иþ��δ����ڵ�ͼ�񲿷ֲű�����
����bgdModel��������ģ�ͣ����Ϊnull�������ڲ����Զ�����һ��bgdModel��bgdModel�����ǵ�ͨ�������ͣ�CV_32FC1��ͼ��������ֻ��Ϊ1������ֻ��Ϊ13x5��
����fgdModel����ǰ��ģ�ͣ����Ϊnull�������ڲ����Զ�����һ��fgdModel��fgdModel�����ǵ�ͨ�������ͣ�CV_32FC1��ͼ��������ֻ��Ϊ1������ֻ��Ϊ13x5��
����iterCount���������������������0��
����mode��������ָʾgrabCut��������ʲô��������ѡ��ֵ�У�
����GC_INIT_WITH_RECT��=0�����þ��δ���ʼ��GrabCut��
����GC_INIT_WITH_MASK��=1����������ͼ���ʼ��GrabCut��
����GC_EVAL��=2����ִ�зָ