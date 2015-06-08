// TestIGO.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "igoInter.h"

int _tmain(int argc, _TCHAR* argv[])
{
	out_I_GO_Result _tempresult;
	in_I_GO_ConfigParam _temmpconfig;

	int _tempd = IGOImagerocessEx("a.jpg",_temmpconfig,_tempresult);

	return 0;
}

