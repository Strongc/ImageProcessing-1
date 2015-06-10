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
remap( )�������������ָ����ӳ����ʽ����Դͼ�������ӳ�伸�α任�����ڵ�ʽ�����£�
		DST(X,Y)=SRC(MAPx(X,Y),MAPy(X,Y))	
��Ҫע�⣬�˺�����֧�־͵أ�in-place��������������ԭ�ͺͲ�����
    C++: void remap(InputArray src, OutputArraydst, InputArray map1, InputArray map2, int interpolation, intborderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())  
        ��һ��������InputArray���͵�src������ͼ�񣬼�Դͼ����Mat��Ķ��󼴿ɣ�����Ϊ��ͨ��8λ���߸�����ͼ��
        �ڶ���������OutputArray���͵�dst���������ú���������������������������ڴ�ź������ú�������������ԴͼƬ��һ���ĳߴ�����͡�
        ������������InputArray���͵�map1���������ֿ��ܵı�ʾ����

                ��ʾ�㣨x��y���ĵ�һ��ӳ�䡣
                ��ʾCV_16SC2 , CV_32FC1 ��CV_32FC2���͵�Xֵ��

        ���ĸ�������InputArray���͵�map2��ͬ������Ҳ�����ֿ��ܵı�ʾ���󣬶������Ǹ���map1��ȷ����ʾ���ֶ���

                ��map1��ʾ�㣨x��y��ʱ����������������κ�ֵ��
                ��ʾCV_16UC1 , CV_32FC1���͵�Yֵ���ڶ���ֵ����

        �����������int���͵�interpolation,��ֵ��ʽ��֮ǰ��resize( )�������н�������Ҫע�⣬resize( )�������ᵽ��INTER_AREA��ֵ��ʽ�������ǲ�֧�ֵģ����Կ�ѡ�Ĳ�ֵ��ʽ���£�

                INTER_NEAREST - ����ڲ�ֵ
                INTER_LINEAR �C ˫���Բ�ֵ��Ĭ��ֵ��
                INTER_CUBIC �C ˫����������ֵ����4��4���������ڵ�˫���β�ֵ��
                INTER_LANCZOS4 -Lanczos��ֵ����8��8���������Lanczos��ֵ��

        ������������int���͵�borderMode���߽�ģʽ����Ĭ��ֵBORDER_CONSTANT����ʾĿ��ͼ���С���Ⱥ�㣨outliers����������ֵ���ᱻ�˺����޸ġ�
        ���߸�������const Scalar&���͵�borderValue�����г����߽�ʱʹ�õ�ֵ������Ĭ��ֵScalar( )����Ĭ��ֵΪ0��
