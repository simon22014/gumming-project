#pragma once
#include"IncludeGlobal.h"
#include"noiseCanny.h"
class CImageToRect
{
public:
	CImageToRect();
	CImageToRect(Mat image,Mat firstImage);
	~CImageToRect();
	Mat GetRect();
	void thresholdMat();
	void erodeImage();
	void FindIntCorner();
	void GetContoursPic();
private:
	Mat NotheCImage;
	Mat theFirstImage;
	Mat sourceImage;
	Mat changeImage;
	Mat imgROI;
	noiseCanny* NOCanny;
};

