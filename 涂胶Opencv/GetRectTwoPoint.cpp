#include "stdafx.h"
#include "GetRectTwoPoint.h"
#include"log.h"
Mat GlobalRecImage; //全局变量图像源
Rect roiRect; //所选择的矩形
Point startPoint;
Point endPoint;
bool got_beigin_point = false;
bool got_end_point = false;
vector<Point> foundPoint;
vector<Point> foundPointMouse;
//***************************************
// 函数名称:  WriteFourPoint
// 函数说明:  在进行训练的时候，点击中间滑动保存当前的五个点到内存里中，方便自己进行测试，在正式跑的时候，可以进行屏蔽
// 输入说明： 无
// 权限:      public 
// 返回值:    无
//**************************************
void WriteFourPoint()
{
	
	bool iforNotWrite = false;
	FILE *fp;
	fp = fopen("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\FourPoint.txt", "a+");
	if (fp == NULL)
	{
		//	std::cout << "write Log error" << std::endl;
		//	std::exit(1);
	}
	for (vector <Point>::iterator iter = foundPointMouse.begin(); iter != foundPointMouse.end(); iter++)
	{
		if (iter == foundPointMouse.begin())
		{ 
			fprintf(fp, "%d,%d", (*iter).x, (*iter).y);
		}
		else
		{
			fprintf(fp, ",%d,%d", (*iter).x, (*iter).y);
		}
		iforNotWrite = true;
	//	foundPoint.push_back(*iter);
	}
	if (iforNotWrite)
	{
		fprintf(fp, " OverPoint");
		fprintf(fp, "\n");
	}
	std::fclose(fp);

}

void GetRectTwoPoint::ReadFourPoint()
{
	int NumMap = 0;
	int readJude = 0;
	bool ifisTheY = false;
	Point readPoint;
	string s;
	ifstream fp("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\FourPoint.txt"); 
	if (!fp) 
	{ 
		std::cout << "OPEN ERROR" << endl;
		exit(-1);
	}
	while (getline(fp, s)) 
	{
		if (s == "")
		{
			std::cout << "read the rect is none" << std::endl;
			readJude++;
			if (readJude >= 2)
			{
		//		my_Map.insert(map<int, vector<Point>>::value_type(NumMap, foundPoint));
		//		foundPoint.clear();
				break;
			}
			continue;
		}
		if (s.size() == 3 || s.size() == 4)
		{
			if (NumMap != 0)
			{
				my_Map.insert(map<int, vector<Point>>::value_type(NumMap, foundPoint));
				foundPoint.clear();
			}
			char *TheNum = (char*)s.c_str();
			const char * split = "[";
			char *p;
			p = strtok(TheNum, split);
			const char * splitp = "]";
			char *pp;
			pp = strtok(p, splitp);
			sscanf(pp, "%d", &NumMap);
		//	NumMap = *pp - '0';
			continue;

	//		cout << "NumMap:" << NumMap << endl;
		}
		readJude = 0;
		char *theAllLine = (char*)s.c_str();
		const char * split = "OverPoint";
		char *p;
		p = strtok(theAllLine, split);
		int theNUMdata = 0;
		while (p != NULL)
		{
			theNUMdata++;
			char* Pt;
			Pt = strtok(p, ",");
			int thePointX = 0;
			while (Pt != NULL) {
				//	cout << " Pt" << Pt << endl;
				if (ifisTheY)
				{
					readPoint = Point(thePointX, atoi(Pt));
					foundPoint.push_back(readPoint);
					ifisTheY = false;
					Pt = strtok(NULL, ",");
					continue;
				}
				thePointX = atoi(Pt);
				ifisTheY = true;
				Pt = strtok(NULL, ",");
			}
			p = strtok(NULL, ",");
		} 
	} 
	if (NumMap != 0)
	{
		my_Map.insert(map<int, vector<Point>>::value_type(NumMap, foundPoint));
		foundPoint.clear();
	}
	
	foundPoint = my_Map[NumPicture];

	for (map<int, vector<Point>>::iterator  it= my_Map.begin(); it != my_Map.end(); it++)
	{
		Log("MyPicture:" + to_string((*it).first), false);
	//	std::cout << "MyPicture:" << (*it).first << endl<<"Point: ";
		for (vector<Point>::iterator iter = ((*it).second).begin(); iter != ((*it).second).end(); iter++)
		{
		//	std::cout << "(" << (*iter).x<<","<<(*iter).y<< ")  ";
			Log("(" +to_string((*iter).x) + "," + to_string((*iter).y) + ")  ", false);
		}
		Log("", true);
	//	std::cout << endl;
	}
	std::cout << "当前所处理的图片Point:" << endl << "Point:";
	Log("当前所处理的图片Point:", true);

	for (vector <Point>::iterator iter = foundPoint.begin(); iter != foundPoint.end(); ++iter)
	{
		//std::cout << "(" << (*iter).x << "," << (*iter).y << ") ";
		Log("(" + to_string((*iter).x)+","+to_string((*iter).y)+")", true);
	}
	Log("theImageNum:" + to_string(NumPicture), true);
	//cout << "theImageNum:" << NumPicture << endl;
	fp.close(); 
}

#if 0

	bool ifisTheY = false;
	char theAllLine[1024] = { 0 };
	char c;
	FILE *fp;
	fp = fopen("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\FourPoint.txt", "r+");
	if (fp == NULL)
	{
		//	std::cout << "write Log error" << std::endl;
		//	std::exit(1);
	}
	Point readPoint;
	if (NULL == fp)
	{
		std::exit(1);//要返回错误代码
	}
	int i = 0;
	while (fscanf(fp, "%c", &c) != EOF)
	{
		theAllLine[i] = c;
		i++;
	}//从文本中读入并在控制台打印出来

	cout << "theAllLine" << theAllLine << endl;
	const char * split = "OverPoint";
	char *p;
	p = strtok(theAllLine, split);
	cout << "theAllLine" << theAllLine << "p:" << p << endl;
	int theNUMdata  = 0;
	while (p != NULL)
	{
		theNUMdata++;
	
		char* Pt;
		Pt = strtok(p, ",");
		int thePointX = 0;
		while (Pt != NULL) {
			//	cout << " Pt" << Pt << endl;
			if (ifisTheY)
			{
				readPoint = Point(thePointX, atoi(Pt));
					
				foundPoint.push_back(readPoint);
				ifisTheY = false;
				Pt = strtok(NULL, ",");
				continue;
			}
			thePointX = atoi(Pt);
			ifisTheY = true;
			Pt = strtok(NULL, ",");
		}
		p = strtok(NULL, ",");
	}
	
	cout <<"ReadLine" <<theAllLine << endl;
	fclose(fp);

}
#endif 
//***************************************
// 函数名称:  FindCornerMouseEvent
// 函数说明:  鼠标操作响应
// 输入说明： 无
// 权限:      public 
// 返回值:    无
//**************************************
void FindCornerMouseEvent(int event, int x, int y, int flags, void* data)
{
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		startPoint = Point(x, y);

		if (!got_beigin_point)
		{
			foundPoint.push_back(startPoint);
			foundPointMouse.push_back(startPoint);
			got_beigin_point = true;
		}
		
		break;
	case   CV_EVENT_MOUSEMOVE:
	//	if (got_beigin_point)
	//	{
		//	endPoint = Point(x, y);
	//	}	
		break;
	case CV_EVENT_RBUTTONDOWN:
		got_end_point = true;
		endPoint = Point(x, y);
		foundPoint.push_back(endPoint);
		foundPointMouse.push_back(endPoint);
		break;
	case CV_EVENT_MBUTTONDOWN:
		
		imwrite("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\image\\1.jpg", GlobalRecImage);
		WriteFourPoint();
		break;
	default:
		break;
	}
	if (got_end_point)
	{
		line(GlobalRecImage, startPoint, endPoint, Scalar(0, 0, 255), 5);

		got_end_point = false;
		imshow("findCornerImage", GlobalRecImage);
		waitKey(0);
	}

}

GetRectTwoPoint::GetRectTwoPoint()
{
}

 GetRectTwoPoint::GetRectTwoPoint(Mat image, int NumPicture)
	 :NumPicture(NumPicture)
{
	ReadFourPoint();
	 sourceImage = image.clone();
	 firstImage = sourceImage.clone();
}

 void GetRectTwoPoint::ItChangeImage()
 {
 sourceImage = imread("C:\\Users\\user\\Desktop\\simon涂胶项目\\涂胶Opencv\\x64\\Debug\\image\\1.jpg");//存放自己图像的路径 

 }

 Mat GetRectTwoPoint::getSourceImageMat()
 {
	 return firstImage;
 
 }

 vector<Point> GetRectTwoPoint::findFourPoint()
 {

	 return foundPoint;
 }

GetRectTwoPoint::~GetRectTwoPoint()
{
}

void GetRectTwoPoint::CornerGetPoint()
{
		namedWindow("findCornerImage");
		imshow("findCornerImage", sourceImage);
	
		GlobalRecImage = sourceImage.clone();
	setMouseCallback("findCornerImage", FindCornerMouseEvent, 0); //根据鼠标获取感兴趣的区域 
	waitKey(0);

}
