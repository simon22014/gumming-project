#include "stdafx.h"
#include "Cbtw_readThrelodCanny.h"
#include"log.h"

Cbtw_readThrelodCanny::Cbtw_readThrelodCanny()
{
#if 0
	//string sumS;
	//int sum = 0;
	//int x = 2; int y = 3;
	//MySpecialClass ^a = gcnew MySpecialClass();
	//sum = a->demoAdd(x, y);
	//cout << "sad:" << (a->ReadText()) << endl;;
	//cout << "sum:" << sum << endl;
#endif 
//	readTCannyText();

}
int Cbtw_readThrelodCanny::readTCannyText(int NumPicture, int theTwoNum,int theThreeNum)
{
	int Num = 51;
	MySpecialClass ^a = gcnew MySpecialClass();
	if (a->ReadText() == 0)
	{
		exit(-1);
		cout << "read the text is error" << endl;
		Log("read the text is error", true);
	}
	Num = a->returnCanny(NumPicture, theTwoNum, theThreeNum);
	if (Num == 0)
	{
		cout << "���ļ���ȡCannyʧ�ܣ�ȡ20" << endl;
		Log("���ļ���ȡCannyʧ�ܣ�ȡ2", true);
		Num = 20;
	}
	return Num;
}
int Cbtw_readThrelodCanny::readThreatoldText(int NumPicture,int theTwoNum,int theThreeNum)
{
	int Num = 20;
	MySpecialClass ^a = gcnew MySpecialClass();
	if (a->ReadText() == 0)
	{
	//	exit(-1);
		cout << "read the text is error" << endl;
		Log("read the text is error", true);
	}
	Num = a->returnThrelod(NumPicture, theTwoNum, theThreeNum);
	if (Num == 0)
	{
		if (theTwoNum == 2)
		{
			Num = 34;
			return Num;
		}
		cout<< "���ļ���ȡThreatoldʧ�ܣ�ȡ61" << endl;
		Log("���ļ���ȡThreatoldʧ�ܣ�ȡ61", true);
		Num = 61;

	}
	return Num;
}
void Cbtw_readThrelodCanny::WriteTCannyText()
{
	MySpecialClass ^ab = gcnew MySpecialClass();
	if (ab->ReadText() == 0)
	{
		cout << "read the text is error" << endl;
		Log("read the text is error", true);
	}


}
void Cbtw_readThrelodCanny::WriteThrelodText(int NumPicture,int  theTwoNum,int  theThreeNum,int thr_value)
{
	MySpecialClass ^ab = gcnew MySpecialClass();
	if (ab->ReadText() == 0)
	{
		cout << "read the text is error" << endl;
		Log("read the text is error", true);
	}
	ab->writeTheThrelodTex(NumPicture, theTwoNum, theThreeNum, thr_value); //����ֵд���ļ���ȥ


}

Cbtw_readThrelodCanny::~Cbtw_readThrelodCanny()
{
}
