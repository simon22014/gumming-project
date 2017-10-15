#include "stdafx.h"
#include "Cbtw_imageDealWith.h"
#include"Cbtw_readThrelodCanny.h"
#include"log.h"
Mat src;
Mat dst;
int thr_value = 0;
int thr_type = 0;
const int max_type = 4;
const int max_value = 255;
const int max_binary_value = 255;
char *windowName = "Demo";

Cbtw_imageDealWith::Cbtw_imageDealWith()
{
	
}

Cbtw_imageDealWith::Cbtw_imageDealWith(int NumPicture, int theTwoNum, int theThreeNum,Mat SourceImage,Mat firstImage)
	:SourceImage(SourceImage), firstImage(firstImage), NumPicture(NumPicture), theTwoNum(theTwoNum), theThreeNum(theThreeNum)
{

	dealWith();
//	ConnectedImage();
}

void  changeImage(Mat& image, int thr_value)//�޸�ĳ�����ص�����ֵ
{
	int cPointR, cPointG, cPointB;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			if (image.at<uchar>(i, j) <= thr_value)
			{
				image.at<uchar>(i, j) = 255;
			}
		}
	}
}

void Image_thred(int, void*)
{
	/* 0: ��������ֵ
	1: ����������ֵ
	2: �ض���ֵ
	3: 0��ֵ
	4: ��0��ֵ
	*/
	threshold(src, dst, thr_value, max_binary_value, thr_type);
	Mat imageSrc = src.clone();
	changeImage(imageSrc, thr_value);
	imshow("imageSrc", imageSrc);
}

void Cbtw_imageDealWith::gammaCheckImage(Mat& src,Mat& dst) //gammaУ��ͼƬ����������
{
	Log("gammaУ��ͼƬ����������", true);
	float fGamma = 0.45;
	CV_Assert(src.data);

	// accept only char type matrices  
	CV_Assert(src.depth() != sizeof(uchar));

	// build look up table  
	unsigned char lut[256];
	for (int i = 0; i < 256; i++)
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), fGamma) * 255.0f);
	}

	dst = src.clone();
	const int channels = dst.channels();
	switch (channels)
	{
	case 1:
	{

		MatIterator_<uchar> it, end;
		for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
			//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;  
			*it = lut[(*it)];

		break;
	}
	case 3:
	{

		MatIterator_<Vec3b> it, end;
		for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++)
		{
			//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;  
			//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;  
			//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;  
			(*it)[0] = lut[((*it)[0])];
			(*it)[1] = lut[((*it)[1])];
			(*it)[2] = lut[((*it)[2])];
		}
		break;
	}
	}
}

void Cbtw_imageDealWith::passThroughDrag()//ͨ������϶��ҵ����ŵ���ֵ��canny
{
	namedWindow(windowName, WINDOW_NORMAL);
	createTrackbar("Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted",
		windowName, &thr_type, max_type, Image_thred);
	createTrackbar("Value",
		windowName, &thr_value, max_value, Image_thred);
	Image_thred(0, 0);

}

void Cbtw_imageDealWith::dealWith() //����ͼ��
{
	Cbtw_readThrelodCanny *ReadData = new Cbtw_readThrelodCanny();
	int theThreaold;
	int theCanny;
	theThreaold = ReadData->readThreatoldText(NumPicture, theTwoNum, theThreeNum);
	theCanny = ReadData->readTCannyText(NumPicture, theTwoNum, theThreeNum);

	cout << "theData:" << NumPicture << ":" << theTwoNum << ":" << theThreeNum << endl;
	Log("theData:" + to_string(NumPicture) + ":" + to_string(theTwoNum) + ":" + to_string(theThreeNum), true);
	cout << "theThreaold:" << theThreaold << " theCanny:" << theCanny << endl;
	Log("theThreaold:" + to_string(theThreaold) + " theCanny:" + to_string(theCanny), true);
	
	Mat CannytheSImage;
	Mat firstImage = SourceImage.clone();
//	salt(firstImage, 3000); //���뽷��
	ImageErode(firstImage, 3); //��ʴ
	ImageDilate(firstImage, 3); //����
	cvtColor(firstImage, firstImage, CV_BGR2GRAY);
//	imshow("CV_BGR2GRAY", firstImage);
	Mat BGRtheSImage;
	ImageFiltering(firstImage);//�˲�����
	ImageHisBalance(firstImage); //ֱ��ͼ����
	src = firstImage.clone();

#if 0  //��������gammaУ����ͼƬ
	Mat dst = src.clone();
	gammaCheckImage(src, dst); //����gammaУ��֮���Ч��
	namedWindow("src", WINDOW_AUTOSIZE);
	imshow("src", src);
	imshow("dst", dst);
	waitKey(0);
#endif 

#if 0 //�ֶ�������ֵ
	passThroughDrag();
	firstImage = dst.clone();
	waitKey(0);

//	ReadData->WriteThrelodText(NumPicture, theTwoNum,theThreeNum,thr_value); //����ȡ������ֵд��txt��
	cout << "��ֵ�����" << thr_value << endl;
	Log("��ֵ�����" + to_string(thr_value), true);

#else
	threshold(firstImage, firstImage, theThreaold, 255, THRESH_BINARY); //61
#endif 
//	ImageFindContours(firstImage, firstImage);//Ѱ������
#if 0
//	passThroughDrag();//ͨ������϶��ҵ����ŵ���ֵ��canny
//	imshow("firstImage", firstImage);
//	cv::adaptiveThreshold(firstImage, firstImage, 255, CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 25, 10);
	//	imshow("adaptiveThreshold", firstImage);
	//	waitKey(0);
	//changeImagePx(firstImage);//�޸�ĳ�����ص�����ֵ
//	Sobel(firstImage, CannytheSImage, firstImage.depth(), 1, 1);
//	Laplacian(firstImage, CannytheSImage, firstImage.depth());
//	imshow("CannytheSImage", CannytheSImage);
	//waitKey(0);
//	imshow("CannytheSImage", CannytheSImage);
//	waitKey(0);
//	CannytheSImage = dst.clone();
#endif 

	Canny(firstImage, CannytheSImage, theCanny, theCanny * 3, 3);
	cvtColor(CannytheSImage, BGRtheSImage, CV_GRAY2BGR);//ת����Ե�����ͼΪ�Ҷ�ͼ
	dealWithImage = BGRtheSImage.clone();
}

void Cbtw_imageDealWith::ImageGaussRemoveBackground(Mat& firstImage)//��˹ȥ����
{


}

void Cbtw_imageDealWith::ImageHisBalance(Mat& firstImage) //ֱ��ͼ�����㷨
{
	Log("ֱ��ͼ�����㷨", true);
	Mat mergeImg;//�ϲ����ͼ��  
	vector<Mat> splitBGR(firstImage.channels());
	//�ָ�ͨ�����洢��splitBGR��  
	split(firstImage, splitBGR);
	//�Ը���ͨ���ֱ����ֱ��ͼ���⻯  
	for (int i = 0; i<firstImage.channels(); i++)
		equalizeHist(splitBGR[i], splitBGR[i]);
	//�ϲ�ͨ��  
	merge(splitBGR, mergeImg);

}

void  Cbtw_imageDealWith::ImageFiltering(Mat& image)//�˲�����
{
	Log("blur:�˲�����", true);
	blur(image, image, Size(3, 3), Point(-1, -1));
//	medianBlur(image, image, 5);
}

void Cbtw_imageDealWith::ImageDilate(Mat& image,int num) //�����㷨+ ����
{
	Log("�����㷨+ ����:"+to_string(num), true);
	Mat element = getStructuringElement(0, Size(4 * 1 + 1, 4 * 1 + 1), Point(1, 1));
	for (int i = 0; i < num; i++)
	{
		dilate(image, image, element);
	}
}

void Cbtw_imageDealWith::ImageErode(Mat& image,int num) //��ʴ�㷨 + ����
{
	Log("��ʴ�㷨+ ����:" + to_string(num), true);
	Mat element = getStructuringElement(0, Size(4 * 1 + 1, 4 * 1 + 1), Point(1, 1));
	for (int i = 0; i < num; i++)
	{
		erode(image, image, element);
	}
}

void Cbtw_imageDealWith::changeImagePx(Mat& image)//�޸�ĳ�����ص�����ֵ
{
	Log("�޸�ĳ�����ص�����ֵ,��Ϊ0���޸�Ϊ(255,0,255)", true);
	int cPointR, cPointG, cPointB;
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{

			cPointR = image.at<Vec3b>(i, j)[0];
			cPointG = image.at<Vec3b>(i, j)[1];
			cPointB = image.at<Vec3b>(i, j)[2];
			if (cPointR != 0 || cPointG != 0 || cPointB != 0)
			{
				image.at<Vec3b>(i, j)[0] = 255;
				image.at<Vec3b>(i, j)[1] = 0;
				image.at<Vec3b>(i, j)[2] = 255;
			}
		}
	}
}

void Cbtw_imageDealWith::salt(Mat& image, int n)//���뽹������
{
	Log("���뽹������", true);
	for (int k = 0; k<n; k++) {
		int i = rand() % image.cols;
		int j = rand() % image.rows;

		if (image.channels() == 1) {   //�ж���һ��ͨ��
			image.at<uchar>(j, i) = 255;
		}
		else {
			image.at<cv::Vec3b>(j, i)[0] = 255;
			image.at<cv::Vec3b>(j, i)[1] = 255;
			image.at<cv::Vec3b>(j, i)[2] = 255;
		}
	}
}

void Cbtw_imageDealWith::ImageFindContours(Mat& firstImage,Mat& image)//��������
{
	Log("��������", true);
	vector<Rect> findRect;
	Mat drawing = Mat::zeros(image.size(), CV_8UC3);
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//��������  
	cv::findContours(image, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);
	//�������ж�������������������ɫ�����Ƴ�ÿ�������������ɫ  
	int index = 0;
	for (; index >= 0; index = hierarchy[index][0]) {
	//	Scalar color(rand() & 255, rand() & 255, rand() & 255);
		Scalar color(0,0, 255);
		double g_dConArea = contourArea(contours[index]);
		if (g_dConArea > 100)
		{
			drawContours(SourceImage, contours, index, color, FILLED, 8, hierarchy);
			Rect rect = boundingRect(contours[index]);//���������  
		//	rectangle(SourceImage, rect, Scalar(0, 255, 0), 3);//���������Ӿ��ο�  
		//	imshow("firstImage", SourceImage);
		//	waitKey(0);
		}
	}

}

void Cbtw_imageDealWith::ConnectedImage()
{
	Mat image = imread("C:\\Users\\user\\Desktop\\Ϳ��Opencv\\x64\\Debug\\image\\Testimage\\4.jpg");  //����Լ�ͼ���·�� 
	Mat firstImage = image.clone();
	Mat changeImage = image.clone();
	Mat CannytheSImage;
	ImageErode(changeImage, 2);
	ImageDilate(changeImage, 2);
	cv::cvtColor(changeImage, changeImage, CV_BGR2GRAY);
	cv::Canny(changeImage, CannytheSImage, 5, 5 * 3, 3);
	cv::threshold(CannytheSImage, CannytheSImage, 20, 200, THRESH_BINARY);
	ImageFindContours(firstImage, CannytheSImage);//��������
	cv::imshow("sourceiMAGE", firstImage);
	cv::waitKey(0);
#if 0

	vector <Rect>::iterator iterRect = findRect.begin();
	vector<Rect> iterFindRect;
	for (; iterRect != findRect.end(); ++iterRect)
	{
		//	cout << "��ɸѡ���ܹ���������Ϊ��" << ((*iterRect).width) * ((*iterRect).height) << endl;
		if (((*iterRect).width)*((*iterRect).height) >	40000)
		{
			iterFindRect.push_back(*iterRect);

			rectangle(theFirstImage, (*iterRect), Scalar(255, 255, 0), 3);//���������Ӿ��ο�  
			circle(theFirstImage, Point((*iterRect).x, (*iterRect).y), 4, Scalar(255, 0, 0));
		}
	}
	vector <Rect>::iterator iterRectFind = iterFindRect.begin();

	for (; iterRectFind != iterFindRect.end(); ++iterRectFind)
	{
		//	if (((*iterRectFind).width) * ((*iterRectFind).height) == 97672)
		{
			cout << "��ɸѡ���ܹ���������Ϊ��" << ((*iterRectFind).width) * ((*iterRectFind).height) << endl;
			imgROI = NotheCImage(Rect(Point((*iterRectFind).x, (*iterRectFind).y), Point((*iterRectFind).x + (*iterRectFind).width, (*iterRectFind).y + (*iterRectFind).height)));
			cv::imshow("P", imgROI);
			cv::waitKey(0);
		}
	}
#endif 
}

Mat Cbtw_imageDealWith::returnDealWithMat()
{
	return dealWithImage;
}

Cbtw_imageDealWith::~Cbtw_imageDealWith()
{
}
