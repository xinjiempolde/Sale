/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: ShowMenu.h
 * Author:   刘小辉
 * Date:     2019年12月05日
 *
 * Description: 显示相关的一系列函数
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
 /*
  * 函数名:SetColor
  * 功  能:改变输出信息的颜色
  * 输  入:颜色值，范围0-16
  * 输  出:无
  * 返回值:无
  */
void SetColor(short x);
 /*
  * 函数名:SetPos
  * 功  能:改变光标位置
  * 输  入:要定位的光标坐标x, y
  * 输  出:无
  * 返回值:无
  */
void SetPos(int x, int y);

 /*
  * 函数名:EchoTime
  * 功  能:在界面显示本地时间
  * 输  入:无
  * 输  出:无
  * 返回值:无
  */
void EchoTime();

 /*
  * 函数名:ShowMainMenu
  * 功  能:显示主界面
  * 输  入:无
  * 输  出:无
  * 返回值:无
  */
void ShowMainMenu();

/*
 * 函数名:ShowProgressBar
 * 功  能:显示登录进度条
 * 输  入:无
 * 输  出:进度条
 * 返回值:无
 */
void ShowProgressBar();

/*
 * 函数名:ShowSysInfo
 * 功  能:显示系统介绍
 * 输  入:无
 * 输  出:系统介绍
 * 返回值:无
 */
void ShowSysInfo();