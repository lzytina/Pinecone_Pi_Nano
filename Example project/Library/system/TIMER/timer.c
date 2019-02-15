/**
  ******************************************************************************
  * @file    timer.c
  * @author  PineconePi
  * @version V1.0.0
  * @date    20-December-2018
  * @brief  This document is used for timer configuration 
  * @License:GNU General Public License v3.0         
  ******************************************************************************
  * @attention
  *
  *Timer Interrupt Processing Function in timer.c
  *  
  * 
  * 
  * 
  * 
  *
  * 
  ******************************************************************************
	**/

#include	"timer.h"

/********************* Timer0�жϺ���************************/
void timer0_int (void) interrupt 1
{

}

/********************* Timer1�жϺ���************************/
void timer1_int (void) interrupt 3
{

}

/********************* Timer2�жϺ���************************/
void timer2_int (void) interrupt 12
{

}


//========================================================================
// ����: unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)
// ����: ��ʱ����ʼ������.
// ����:  ��ο�timer.c����Ľṹ�嶨��
//       
//       
// ����: 
// �汾: VER1.0.0
// ����: 2018-12-20
// ����: PineconePi
// ��ע:
//	
//	
//	
//	
//	
//========================================================================
unsigned char	Timer_Inilize(unsigned char TIM, TIM_InitTypeDef *TIMx)
{
	if(TIM > Timer2)	return 1;	//�ղ���

	if(TIM == Timer0)
	{
		TR0 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET0 = 1;	//�����ж�
		else									ET0 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT0 = 1;	//�����ȼ��ж�
		else									PT0 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >  TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x03) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ, 3: 16λ�Զ���װ, ���������ж�
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x80;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x80;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x04;	//����������Ƶ
		else										TMOD &= ~0x04;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x01;	//���ʱ��
		else							INTCLKO &= ~0x01;	//�����ʱ��
		
		TH0 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL0 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR0 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer1)
	{
		TR1 = 0;		//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)		ET1 = 1;	//�����ж�
		else									ET1 = 0;	//��ֹ�ж�
		if(TIMx->TIM_Polity == PolityHigh)		PT1 = 1;	//�����ȼ��ж�
		else									PT1 = 0;	//�����ȼ��ж�
		if(TIMx->TIM_Mode >= TIM_16BitAutoReloadNoMask)	return 2;	//����
		TMOD = (TMOD & ~0x30) | TIMx->TIM_Mode;	//����ģʽ,0: 16λ�Զ���װ, 1: 16λ��ʱ/����, 2: 8λ�Զ���װ
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~0x40;	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  0x40;	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	TMOD |=  0x40;	//����������Ƶ
		else										TMOD &= ~0x40;	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x02;	//���ʱ��
		else							INTCLKO &= ~0x02;	//�����ʱ��
		
		TH1 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL1 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	TR1 = 1;	//��ʼ����
		return	0;		//�ɹ�
	}

	if(TIM == Timer2)		//Timer2,�̶�Ϊ16λ�Զ���װ, �ж������ȼ�
	{
		AUXR &= ~(1<<4);	//ֹͣ����
		if(TIMx->TIM_Interrupt == ENABLE)			IE2  |=  (1<<2);	//�����ж�
		else										IE2  &= ~(1<<2);	//��ֹ�ж�
		if(TIMx->TIM_ClkSource >  TIM_CLOCK_Ext)	return 2;
		if(TIMx->TIM_ClkSource == TIM_CLOCK_12T)	AUXR &= ~(1<<2);	//12T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_1T)		AUXR |=  (1<<2);	//1T
		if(TIMx->TIM_ClkSource == TIM_CLOCK_Ext)	AUXR |=  (1<<3);	//����������Ƶ
		else										AUXR &= ~(1<<3);	//��ʱ
		if(TIMx->TIM_ClkOut == ENABLE)	INTCLKO |=  0x04;	//���ʱ��
		else							INTCLKO &= ~0x04;	//�����ʱ��

		TH2 = (unsigned char)(TIMx->TIM_Value >> 8);
		TL2 = (unsigned char)TIMx->TIM_Value;
		if(TIMx->TIM_Run == ENABLE)	AUXR |=  (1<<4);	//��ʼ����
		return	0;		//�ɹ�
	}
	return 2;	//����
}