#include "stdafx.h"
#include "CImageToRect.h"

CImageToRect::CImageToRect()
{
}

CImageToRect::CImageToRect(Mat image,Mat firstImage)
{
	NotheCImage = image.clone();
	theFirstImage = image.clone();
	sourceImage = image.clone();
	changeImage = image.clone();

}

void CImageToRect::thresholdMat()
{
	int cPointR, cPointG, cPointB, cPoint;//currentPoint;
	for (int i = 1; i < sourceImage.rows; i++)
	{
		for (int j = 1; j < sourceImage.cols; j++)
		{
			cPointB = sourceImage.at<Vec3b>(i, j)[0];
			cPointG = sourceImage.at<Vec3b>(i, j)[1];
			cPointR = sourceImage.at<Vec3b>(i, j)[2];
			if ((cPointB == 0) && (cPointG == 0) && (cPointR = 255))
			{
				changeImage.at<Vec3b>(i, j)[0] = 0;
				changeImage.at<Vec3b>(i, j)[1] = 0;
				changeImage.at<Vec3b>(i, j)[2] = 0;
			}
			else
			{
				changeImage.at<Vec3b>(i, j)[0] = 255;
				changeImage.at<Vec3b>(i, j)[1] = 255;
				changeImage.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
//	cv::imshow("display", changeImage);
//	cv::waitKey(0);

}

void CImageToRect::GetContoursPic()
{
	Mat srcImg = imgROI.clone();
//	imshow("原始图", srcImg);
//	waitKey(0);
	Mat gray, binImg;
	//灰度化
	cvtColor(srcImg, gray, COLOR_RGB2GRAY);
//	imshow("灰度图", gray);
//	waitKey(0);
	//二值化
	threshold(gray, binImg, 150, 260, CV_THRESH_BINARY);
//	imshow("二值化", binImg);
//	waitKey(0);

	vector<vector<Point> > contours;
	vector<Rect> boundRect(contours.size());
	//注意第5个参数为CV_RETR_EXTERNAL，只检索外框  
	findContours(binImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE); //找轮廓
	cout << contours.size() << endl;
	for (int i = 0; i < contours.size(); i++)
	{
		{

			//需要获取的坐标  
			CvPoint2D32f rectpoint[4];
			CvBox2D rect = minAreaRect(Mat(contours[i]));

			cvBoxPoints(rect, rectpoint); //获取4个顶点坐标  
										  //与水平线的角度  
			float angle = rect.angle;
			cout << angle << endl;

			int line1 = sqrt((rectpoint[1].y - rectpoint[0].y)*(rectpoint[1].y - rectpoint[0].y) + (rectpoint[1].x - rectpoint[0].x)*(rectpoint[1].x - rectpoint[0].x));
			int line2 = sqrt((rectpoint[3].y - rectpoint[0].y)*(rectpoint[3].y - rectpoint[0].y) + (rectpoint[3].x - rectpoint[0].x)*(rectpoint[3].x - rectpoint[0].x));
			//rectangle(binImg, rectpoint[0], rectpoint[3], Scalar(255), 2);
			//面积太小的直接pass
			if (line1 * line2 < 600)
			{
				continue;
			}
			//为了让正方形横着放，所以旋转角度是不一样的。竖放的，给他加90度，翻过来  
			if (line1 > line2)
			{
				angle = 90 + angle;
			}

			//新建一个感兴趣的区域图，大小跟原图一样大  
			Mat RoiSrcImg(srcImg.rows, srcImg.cols, CV_8UC3); //注意这里必须选CV_8UC3
			RoiSrcImg.setTo(0); //颜色都设置为黑色  
								//imshow("新建的ROI", RoiSrcImg);
								//对得到的轮廓填充一下  
			drawContours(binImg, contours, -1, Scalar(255), CV_FILLED);

			//抠图到RoiSrcImg
			srcImg.copyTo(RoiSrcImg, binImg);
			//再显示一下看看，除了感兴趣的区域，其他部分都是黑色的了  
	//		namedWindow("RoiSrcImg", 1);
	//		imshow("RoiSrcImg", RoiSrcImg);
	//		waitKey(0);

			//创建一个旋转后的图像  
			Mat RatationedImg(RoiSrcImg.rows, RoiSrcImg.cols, CV_8UC1);
			RatationedImg.setTo(0);
			//对RoiSrcImg进行旋转  
			Point2f center = rect.center;  //中心点  
			Mat M2 = getRotationMatrix2D(center, angle, 1);//计算旋转加缩放的变换矩阵 
			warpAffine(RoiSrcImg, RatationedImg, M2, RoiSrcImg.size(), 1, 0, Scalar(0));//仿射变换 
			cout << "【i：" << i << endl;
			imwrite("C:\\Users\\user\\Desktop\\涂胶Opencv\\x64\\Debug\\image\\5.jpg", RatationedImg);
		//	imshow("旋转之后", RatationedImg);
		//	waitKey(0);
		}
	
	}

#if 1
	//对ROI区域进行抠图

	//对旋转后的图片进行轮廓提取  
	vector<vector<Point> > contours2;
//	Mat raw = imread("r.jpg");
	Mat raw = imgROI.clone();
	Mat SecondFindImg;
	//SecondFindImg.setTo(0);
	cvtColor(raw, SecondFindImg, COLOR_BGR2GRAY);  //灰度化  
	threshold(SecondFindImg, SecondFindImg, 80, 200, CV_THRESH_BINARY);
	findContours(SecondFindImg, contours2, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);
	//cout << "sec contour:" << contours2.size() << endl;

	for (int j = 0; j < contours2.size(); j++)
	{
		//这时候其实就是一个长方形了，所以获取rect  
		Rect rect = boundingRect(Mat(contours2[j]));
		//面积太小的轮廓直接pass,通过设置过滤面积大小，可以保证只拿到外框
		if (rect.area() < 600)
		{
			continue;
		}
	Mat dstImg = raw(rect);
//		imshow("dst", dstImg);
	}
#endif
}

void CImageToRect::erodeImage()
{
	Mat srcGray;
	cvtColor(changeImage, srcGray, CV_BGR2GRAY);
	Mat element = getStructuringElement(0, Size(8 * 1 + 1, 8 * 1 + 1), Point(1, 1));

	/// 腐蚀操作
	erode(srcGray, changeImage, element);
	cv::Canny(changeImage, changeImage, 1, 1 * 3, 3);
//	cv::imshow("getPoint", changeImage);
//	cv::waitKey(0);

}

void CImageToRect::FindIntCorner()
{
	vector<Rect> findRect;
	Mat drawing = Mat::zeros(changeImage.size(), CV_8UC3);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//查找轮廓  
	cv::findContours(changeImage, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	//遍历所有顶层的轮廓，随机绘制颜色，绘制出每个连接组件的颜色  
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0]) {
		Scalar color(rand() & 255, rand() & 255, rand() & 255);
		double g_dConArea = contourArea(contours[index]);
			if (g_dConArea > 10)
			{
				drawContours(theFirstImage, contours, index, color, FILLED, 8, hierarchy);

				Rect rect = boundingRect(contours[index]);//检测外轮廓  
				rectangle(theFirstImage, rect, Scalar(0, 255, 0), 3);//对外轮廓加矩形框  
				findRect.push_back(rect);
			}
	}
	vector <Rect>::iterator iterRect = findRect.begin();
	vector<Rect> iterFindRect;
	for (; iterRect != findRect.end(); ++iterRect)
	{
	//	cout << "【筛选后总共轮廓个数为：" << ((*iterRect).width) * ((*iterRect).height) << endl;
		if (((*iterRect).width)*((*iterRect).height) >	40000)
		{
			iterFindRect.push_back(*iterRect);

			rectangle(theFirstImage, (*iterRect), Scalar(255, 255, 0), 3);//对外轮廓加矩形框  
			circle(theFirstImage, Point((*iterRect).x,(*iterRect).y), 4, Scalar(255, 0, 0));
		}
	}
	vector <Rect>::iterator iterRectFind = iterFindRect.begin();

	for (; iterRectFind != iterFindRect.end(); ++iterRectFind)
	{
//	if (((*iterRectFind).width) * ((*iterRectFind).height) == 97672)
		{
			cout << "【筛选后总共轮廓个数为：" << ((*iterRectFind).width) * ((*iterRectFind).height) << endl;
		   imgROI = NotheCImage(Rect(Point((*iterRectFind).x, (*iterRectFind).y), Point((*iterRectFind).x + (*iterRectFind).width, (*iterRectFind).y + (*iterRectFind).height)));
			cv::imshow("P", imgROI);
			cv::waitKey(0);
		}
	}
	//	cout << "【筛选前总共轮廓个数为】：" << (int)contours.size() << endl;
	for (int i = 0; i < (int)contours.size(); i++)
	{
		double g_dConArea = contourArea(contours[i], true);
		//	cout << "【用轮廓面积计算函数计算出来的第" << i << "个轮廓的面积为：】" << g_dConArea << endl;
	}
	vector <vector<Point>>::iterator iter = contours.begin();
	for (; iter != contours.end();)
	{
		double g_dConArea = contourArea(*iter);
		if (g_dConArea < 100)
		{
			iter = contours.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//	cout << "【筛选后总共轮廓个数为：" << (int)contours.size() << endl;
	for (int i = 0; i < (int)contours.size(); i++)
	{
		double g_dConArea = contourArea(contours[i], true);
			//	cout << "【用轮廓面积计算函数计算出来的第" << i << "个轮廓的面积为：】" << g_dConArea << endl;
	}
//	drawContours(theFirstImage, contours, -1, Scalar(255), 1);   // -1 表示所有轮廓  



//	Mat srcGray;
//	cvtColor(theFirstImage, srcGray, CV_BGR2GRAY);
//	Mat element = getStructuringElement(0, Size(4 * 1 + 1, 4 * 1 + 1), Point(1, 1));

	/// 腐蚀操作
//	erode(theFirstImage, changeImage, element);
	//sourceImage = changeImage.clone();
//	thresholdMat();

//	cv::imshow("geP", theFirstImage);
//	cv::waitKey(0);




}

Mat CImageToRect::GetRect()
{
thresholdMat();
erodeImage();
FindIntCorner();
GetContoursPic();
NOCanny = new noiseCanny(imgROI);




#if 0

	//dilate(srcGray, edges, element);
//	threshold(edges, edges, 80, 255, THRESH_BINARY);
///	Mat edge;
	Canny(edges, canny_output, 1, 1 * 3, 3);

	vector<Vec4i> lines;
	HoughLinesP(canny_output, lines, 1, CV_PI / 180, 40, 20, 5);
	for (size_t i = 0; i < lines.size(); i++)
	{
		line(canny_output, Point(lines[i][0], lines[i][1]),
			Point(lines[i][2], lines[i][3]), Scalar(0, 0, 255), 3, 8);
	}


	//Mat result(canny_output.size(), CV_8U, Scalar(0));
//	drawContours(result, contours, -1, Scalar(255), 1);   // -1 表示所有轮廓  
//	namedWindow("result");
//	imshow("result", result);

	//namedWindow("getPoint");
//	imshow("getPoint", canny_output);
	//waitKey(0);
	return sourceImage;
#endif 
	return sourceImage;
}

CImageToRect::~CImageToRect()
{
}
