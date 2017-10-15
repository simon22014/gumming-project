#pragma once
#include"IncludeGlobal.h"
#include "Cbtw_Singleton.h"
#include"Cbtw_GetInAllResult.h"
class Cbtw_AlgImageRestore
{
public:
	Cbtw_AlgImageRestore();
	Cbtw_AlgImageRestore(Mat,Mat, Cbtw_Singleton*,string, Cbtw_GetInAllResult*,Mat);
	~Cbtw_AlgImageRestore();
private:
	Mat NochangeImage;
	Cbtw_Singleton* Singleton;
	Mat firstImage;
	Mat sourceImage;
	string TheLastResult;
	Cbtw_GetInAllResult*getInAllResult;
};

