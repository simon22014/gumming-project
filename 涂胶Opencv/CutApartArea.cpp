#include "stdafx.h"
#include "CutApartArea.h"
#include"CImageToRect.h"
#include"DealWithGetLine.h"
#include "log.h"
CutApartArea::CutApartArea()
{
}
CutApartArea::CutApartArea(int NumPicture, int theTwoNum,Mat theFirstImage,Mat sourceImage, Cbtw_Singleton* Singleton, Cbtw_GetInAllResult*getInAllResult,Mat NochangeImage)
	:theFirstImage(theFirstImage),sourceImage(sourceImage),Singleton(Singleton), getInAllResult(getInAllResult), NumPicture(NumPicture), theTwoNum(theTwoNum), NochangeImage(NochangeImage)
{

	CutALitterArea();

}
void CutApartArea::CutALitterArea()
{
	CutLeath = 20; //人为检测多少个宽度
	cout << "cols" << theFirstImage.cols << "rows" << theFirstImage.rows << endl;//257 65
	Log("cols:" + to_string(theFirstImage.cols) +"rows" + to_string(theFirstImage.rows), true);
	for (int i = 0; i < theFirstImage.cols;)
	{
		if (i != 0)
		{
			Mat ROIImage = theFirstImage(Rect(i - CutLeath, 0, CutLeath, theFirstImage.rows));
			theLitterArea.push_back(ROIImage);
		}
	//	line(theFirstImage, Point(i, 0),Point(i,theFirstImage.rows), Scalar(0, 255, 255), 2, 4, 0);
		i = i + CutLeath;
	}
//	imshow("thefirstImAGE", theFirstImage);
//	waitKey(0);
	cout << "cols" << theLitterArea.size()<< endl;//257 65
	Log("cols:" + to_string(theLitterArea.size()), true);
	vector <Mat>::iterator Lastiter = theLitterArea.begin();
	for (; Lastiter != theLitterArea.end(); Lastiter++)
	{
//		imshow("AlitterArea", *Lastiter);
	//	waitKey(0);
	}
	GetTheLine();
}
void CutApartArea::GetTheLine()
{
	/*
	Mat element = getStructuringElement(0, Size(4 * 1 + 1, 4 * 1 + 1), Point(1, 1));
	vector <Mat>::iterator Lastiter = theLitterArea.begin();
	for (; Lastiter != theLitterArea.end(); Lastiter++)
	{
		imshow("AlitterArea", *Lastiter);
	   waitKey(0);
	}*/
	DealWithGetLine* getLine = new DealWithGetLine(NumPicture, theTwoNum,theLitterArea, theFirstImage,sourceImage, Singleton, getInAllResult, CutLeath, NochangeImage);
}
CutApartArea::~CutApartArea()
{
}
