/* * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Filename: time.h
 * Author:   ��С��
 * Date:     2019��12��08��
 *
 * Description: ʱ�䴦����غ���
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
	int iHour;			/* ʱ��ṹ�� */
	int iMin;
}stTime;

/*
 * ������:GetTime
 * ��  ��:��ȡ��ǰ����ϵͳʱ��
 * ��  ��:ʱ��ṹ��
 * ��  ��:��ǰʱ��
 * ����ֵ:��
 */
void GetTime(stTime* time);

/*
 * ������:CompareTime
 * ��  ��:�Ƚ�ʱ���Ⱥ�˳��
 * ��  ��:ʱ��ṹ��
 * ��  ��:ʱ���Ⱥ�
 * ����ֵ:ʱ���Ⱥ�
		TIME_NEWER ʱ�俿ǰ
		TIME_EQUAL ʱ�����
		TIME_OLDER ʱ�俿��
 */
int CompareTime(stTime* time_a, stTime* time_b);

/*
 * ������:AddTime
 * ��  ��:����һ��ʱ���Ⱥ��ʱ��
 * ��  ��:ʱ��ṹ��
 * ��  ��:��ǰʱ��
 * ����ֵ:��
 */
void AddTime(int span, stTime now_time, stTime* after_time);