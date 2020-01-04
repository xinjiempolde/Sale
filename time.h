/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: time.h
 * Author:   刘小辉
 * Date:     2019年12月08日
 *
 * Description: 时间处理相关函数
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
#define TIME_OLDER -1
#define TIME_EQUAL 0
#define TIME_NEWER 1
typedef struct {
	int iYear;
	int iMonth;
	int iDay;
	int iHour;			/* 时间结构体 */
	int iMin;
}stTime;

/*
 * 函数名:GetTime
 * 功  能:获取当前本地系统时间
 * 输  入:时间结构体
 * 输  出:当前时间
 * 返回值:无
 */
void GetTime(stTime* time);

/*
 * 函数名:CompareTime
 * 功  能:比较时间先后顺序
 * 输  入:时间结构体
 * 输  出:时间先后
 * 返回值:时间先后
		TIME_NEWER 时间靠前
		TIME_EQUAL 时间相等
		TIME_OLDER 时间靠后
 */
int CompareTime(stTime* time_a, stTime* time_b);

/*
 * 函数名:AddTime
 * 功  能:经过一段时间跨度后的时间
 * 输  入:时间结构体
 * 输  出:当前时间
 * 返回值:无
 */
void AddTime(int span, stTime now_time, stTime* after_time);