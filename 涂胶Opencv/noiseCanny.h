#pragma once
#include"IncludeGlobal.h"
class noiseCanny
{
public:
	noiseCanny();
	noiseCanny(Mat);
	~noiseCanny();
private :
	Mat sourceImage;
};

