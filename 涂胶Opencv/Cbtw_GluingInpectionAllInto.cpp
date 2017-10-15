#include "stdafx.h"
#include "Cbtw_GluingInpectionAllInto.h"
#include "log.h"
Cbtw_GluingInpectionAllInto::Cbtw_GluingInpectionAllInto()
{
}

Cbtw_GluingInpectionAllInto::Cbtw_GluingInpectionAllInto(int NumPicture, Mat dealWithMat, Mat NochangeImage)//NochangeImage���ñ��ֲ������
	:NumPicture(NumPicture), dealWithMat(dealWithMat), NochangeImage(NochangeImage)
{
	vector<float> theEveryTimeLeagth;
	vector<string> theEveryTimeResult;
	resuultDealWithMat = dealWithMat.clone();
	
	vector<Point> theLastFourPoint;
	Mat dealWithImage;
	/*******��ͼƬ���д����ҶԽ�ˮ������*******/
	GetRectTwoPoint *getTwoPoint = new  GetRectTwoPoint(resuultDealWithMat, NumPicture);
  //  getTwoPoint->CornerGetPoint(); //�ֶ���������
	dealWithImage = getTwoPoint->getSourceImageMat().clone();
	theLastFourPoint = getTwoPoint->findFourPoint();
		
	/*********************************************/

	/********************************������ľ��ε㣬����5������ȡ�����վ�����ȡ����������********************************/
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
			theTwoNum++; // �����һ��ͼƬ
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
	//imwrite("C:\\Users\\user\\Desktop\\Ϳ��Opencv\\x64\\Debug\\image\\deal3.jpg", dealWithMat);
//	waitKey(0);
	tm.stop();
	cout << endl;
	cout << "process time=" << tm.getTimeMilli() << "MS" << endl;
	Log("time stop:"+ to_string(tm.getTimeMilli()), true);
	/******************************************/

#if 0
	/*******���Ѿ�ѡ��õ�������н���************/
	//	CImageToRect* getIntRect = new  CImageToRect(dealWithImage, image);
	//	getIntRect->GetRect();


	/******************************************/
	//	namedWindow("������֮���ͼƬ");
	//	imshow("������֮���ͼƬ", dealWithImage);
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
