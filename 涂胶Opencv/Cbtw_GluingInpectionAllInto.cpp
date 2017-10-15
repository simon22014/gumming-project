#include "stdafx.h"
#include "Cbtw_GluingInpectionAllInto.h"
#include "log.h"
Cbtw_GluingInpectionAllInto::Cbtw_GluingInpectionAllInto()
{
}

Cbtw_GluingInpectionAllInto::Cbtw_GluingInpectionAllInto(int NumPicture, Mat dealWithMat, Mat NochangeImage)//NochangeImage永久保持不变的量
	:NumPicture(NumPicture), dealWithMat(dealWithMat), NochangeImage(NochangeImage)
{
	vector<float> theEveryTimeLeagth;
	vector<string> theEveryTimeResult;
	resuultDealWithMat = dealWithMat.clone();
	
	vector<Point> theLastFourPoint;
	Mat dealWithImage;
	/*******对图片进行处理找对胶水的区域*******/
	GetRectTwoPoint *getTwoPoint = new  GetRectTwoPoint(resuultDealWithMat, NumPicture);
  //  getTwoPoint->CornerGetPoint(); //手动画出矩形
	dealWithImage = getTwoPoint->getSourceImageMat().clone();
	theLastFourPoint = getTwoPoint->findFourPoint();
		
	/*********************************************/

	/********************************将保存的矩形点，按照5个点提取（按照矩形提取出来分析）********************************/
	Log("time start:", true);
	TickMeter tm;
	tm.start();
	//imshow("image", image);
	vector<Point>theNumRect;
	int theNUM = 0;
	int theTwoNum = 0;
	for (vector <Point>::iterator iter = theLastFourPoint.begin(); iter != theLastFourPoint.end(); iter++)
	{
		theNumRect.push_back(*iter);
		if (theNUM == 4)
		{
			theTwoNum++; // 代表第一个图片
			resuultDealWithMat = dealWithMat.clone();
			dealWithFourPoint* DWFpoint = new dealWithFourPoint(NumPicture, theTwoNum,theNumRect, resuultDealWithMat, NochangeImage);
			DWFpoint->SetRightFourPoint();
			DWFpoint->SetRightRect();
			theEveryTimeResult.push_back(DWFpoint->getOneResult());
			theEveryTimeLeagth = DWFpoint->getOneLeagth();
			for (vector <float>::iterator iterLeagth = theEveryTimeLeagth.begin(); iterLeagth != theEveryTimeLeagth.end(); iterLeagth++)
			{
				dealWithLeagth.push_back(*(iterLeagth));
			}
			theEveryTimeLeagth.clear();
			theNUM = 0;
			theNumRect.clear();
			continue;
		}
		theNUM++;
	}
	/*************************************************************end**********************************************************/
	for (vector <string>::iterator iter = theEveryTimeResult.begin(); iter != theEveryTimeResult.end(); iter++)
	{
		if ((*iter) == "NG")
		{
			result = "NG";
			break;
		}
		result = "OK";
	}
//	imshow("Image", dealWithMat);
	//imwrite("C:\\Users\\user\\Desktop\\涂胶Opencv\\x64\\Debug\\image\\deal3.jpg", dealWithMat);
//	waitKey(0);
	tm.stop();
	cout << endl;
	cout << "process time=" << tm.getTimeMilli() << "MS" << endl;
	Log("time stop:"+ to_string(tm.getTimeMilli()), true);
	/******************************************/

#if 0
	/*******对已经选择好的区域进行矫正************/
	//	CImageToRect* getIntRect = new  CImageToRect(dealWithImage, image);
	//	getIntRect->GetRect();


	/******************************************/
	//	namedWindow("处理完之后的图片");
	//	imshow("处理完之后的图片", dealWithImage);
	//	waitKey(0);
#endif 
}
Mat Cbtw_GluingInpectionAllInto::returnResultDealWithMat()
{

	return resuultDealWithMat;
	
}
vector<float> Cbtw_GluingInpectionAllInto::returnDealWithLeagth()
{
	return dealWithLeagth;
}
string  Cbtw_GluingInpectionAllInto::returnResult()
{
	return result;
}
Cbtw_GluingInpectionAllInto::~Cbtw_GluingInpectionAllInto()
{

}
