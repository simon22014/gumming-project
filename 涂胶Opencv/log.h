/*******************************************************************
*  Copyright(c) 2017-2020 上海贝特威自动化科技有限公司
*  All rights reserved.
*
*  文件名称:  log.h
*  简要描述: 抓取log的集合
*
*  创建日期:  2017/10/11
*  说明:
*
*  修改日期:
*  作者:     simon.li
*  说明:
******************************************************************/
#ifndef _LOG_H
#define _LOG_H
#pragma once
#include "stdafx.h"
#include "stdafx.h"
#include <opencv2/opencv.hpp>
#include <iostream>
void WriteLog(int B, int G, int R);
void Log(std::string  a,bool ifNewLine);
#endif