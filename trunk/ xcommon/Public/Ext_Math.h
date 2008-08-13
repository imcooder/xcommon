
/********************************************************************
Copyright (c) 2002-2003 �����Ƽ����޹�˾. ��Ȩ����.
�ļ�����:   Ext_Math.h          
�ļ�����:  �򵥵�һЩ������ѧ����
�汾��ʷ:  1.0
����:    xuejuntao xuejuntao@hanwang.com.cn 2008/02/26
*********************************************************************/
#ifndef  _HWXUE_Ext_Math_INC
#define _HWXUE_Ext_Math_INC
#include "Ext_Type.h"
#include <XNotesAPI.h>
//��㵽�߶ε���̾��� ����̾����
long Mth_GetMinDist(const HWPoint &tPtA, const HWPoint &tPtB, const HWPoint &tPtC, HWPoint &tNearestPt);
long DivRound(long x, long div);
long MulDivRound(long x, long mul, long div);

#ifdef __cplusplus
extern "C"{
#endif
  DLLXEXPORT long XSqrt(const long& nRoot);//��������������
  DLLXEXPORT void XQsort( void *base, long num, long width, long *pComp);//����������
  DLLXEXPORT void ZB_SwapIdx ( char *a,	char *b, unsigned long nIdxWidth);

#ifdef __cplusplus
}
#endif

#endif // !defined(_HWXUE_Ext_Math_INC)
