/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: ShowMenu.h
 * Author:   ��С��
 * Date:     2019��12��05��
 *
 * Description: ��ʾ��ص�һϵ�к���
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#pragma once
 /*
  * ������:SetColor
  * ��  ��:�ı������Ϣ����ɫ
  * ��  ��:��ɫֵ����Χ0-16
  * ��  ��:��
  * ����ֵ:��
  */
void SetColor(short x);
 /*
  * ������:SetPos
  * ��  ��:�ı���λ��
  * ��  ��:Ҫ��λ�Ĺ������x, y
  * ��  ��:��
  * ����ֵ:��
  */
void SetPos(int x, int y);

 /*
  * ������:EchoTime
  * ��  ��:�ڽ�����ʾ����ʱ��
  * ��  ��:��
  * ��  ��:��
  * ����ֵ:��
  */
void EchoTime();

 /*
  * ������:ShowMainMenu
  * ��  ��:��ʾ������
  * ��  ��:��
  * ��  ��:��
  * ����ֵ:��
  */
void ShowMainMenu();

/*
 * ������:ShowProgressBar
 * ��  ��:��ʾ��¼������
 * ��  ��:��
 * ��  ��:������
 * ����ֵ:��
 */
void ShowProgressBar();

/*
 * ������:ShowSysInfo
 * ��  ��:��ʾϵͳ����
 * ��  ��:��
 * ��  ��:ϵͳ����
 * ����ֵ:��
 */
void ShowSysInfo();