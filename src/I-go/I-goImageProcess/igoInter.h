  
  /************************************************************************** 
      *  @Copyright (c) 2015, DayBreakZhang, All rights reserved. 
   
      *  @file     : igoInter.h 
      *  @version  : versions 1.0 
   
      *  @author   : DayBreakZhang 
      *  @date     : 2015/04/21 14:03 
      *  @brief    : ��ΪΧ���б�Ľӿ� 
  **************************************************************************/  
#pragma once

#ifdef I_GO_IMAGE_PROCESS_EXPORTS
#define DLL_EXPORT __declspec(dllexport) 
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

typedef struct result
{
	int tGospot;//Χ����Ӹ���
	int tGoAlbino;//Χ����ָ���
	int toutcome;//���

}out_I_GO_Result;
typedef struct param
{

}in_I_GO_ConfigParam;

extern "C" DLL_EXPORT int IGOImagerocessEx(IN char* filename,IN in_I_GO_ConfigParam &config,OUT out_I_GO_Result& result);