#include "stdafx.h"
#include"log.h"

void WriteLog(int B, int G, int R)
{
	FILE *fp;
	fp = fopen("C:\\Users\\user\\Desktop\\simonÍ¿½ºÏîÄ¿\\Í¿½ºOpencv\\x64\\Debug\\log\\log.txt", "a+");
	if (fp == NULL)
	{
		std::cout << "write Log error" << std::endl;
		std::exit(1);
	}
	fprintf(fp, "buf:%d %d %d ", B,G,R);
	fclose(fp);

}

void Log(std::string  theWriteData,bool ifNewLine)
{
   std:: string theData;
   time_t rawtime;
   struct tm* timeinfo;

   time(&rawtime);
   timeinfo = localtime(&rawtime);
	FILE *fp;
	fp = fopen("C:\\Users\\user\\Desktop\\simonÍ¿½ºÏîÄ¿\\Í¿½ºOpencv\\x64\\Debug\\log\\log.txt", "a+");
	if (fp == NULL)
	{
			std::cout << "write Log error" << std::endl;
			std::exit(1);
	}
	theData = std::to_string(((timeinfo->tm_year) + 1900)) + ":" + std::to_string(timeinfo->tm_mon + 1) + ":" + std::to_string(timeinfo->tm_mday) + ": " + std::to_string(timeinfo->tm_hour) + ":";
	theData = theData + std::to_string(timeinfo->tm_min) + ":" + std::to_string(timeinfo->tm_sec);

//	theData =  theData +" "+ theWriteData;
	if (ifNewLine)
	{
		if (theWriteData != "")
		{
			theData = theData +"***************" + theWriteData;
			fprintf(fp, "%s\n", theData.c_str());
		}
		else
		{
			fprintf(fp, "\n");
		}
	}
	else
	{

		fprintf(fp, "%s", (theWriteData + " ").c_str());
	}
	fclose(fp);

}