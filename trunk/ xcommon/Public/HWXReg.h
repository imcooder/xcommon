#if !defined HWXUE_XREG_H
#define HWXUE_XREG_H

/************************************************************************ 
* �ļ�����    HWXReg.h
* �ļ�������  ע����д 
* �����ˣ�    
************************************************************************/ 
#include "HWXString.h"
class DLLXEXPORT CXReg
{
public:
	CXReg(HKEY hRootKey = HKEY_LOCAL_MACHINE); //���캯������Ĭ�ϲ���
	virtual ~CXReg();

public:
	BOOL VerifyKey (LPCTSTR pszPath); 
	BOOL VerifyValue (LPCTSTR pszValue);
	void SetRootKey(HKEY hRootKey);	
	BOOL CreateKey (LPCTSTR pszPath);
	void Close();

	BOOL DeleteValue (LPCTSTR pszValue);
	BOOL DeleteKey (LPCTSTR pszPath);
	BOOL DeleteKey();

	BOOL Write (LPCTSTR pszKey, DWORD dwVal);
	BOOL Write (LPCTSTR pszKey, LPCTSTR pszVal);
	BOOL Write (LPCTSTR pszKey, const BYTE *pbVal, DWORD dwSize);

	BOOL Read (LPCTSTR pszKey, DWORD& dwVal);
	BOOL Read (LPCTSTR pszKey, CXString& sVal);
	BOOL Read (LPCTSTR pszKey, BYTE *pbVal, DWORD dwSize);

	BOOL IsEqual(LPCTSTR pszValue,int nn);
	BOOL IsEqual(LPCTSTR pszValue,DWORD dw);
	BOOL IsEqual(LPCTSTR pszValue,LPCTSTR lpsz);

	BOOL RestoreKey(LPCTSTR lpFileName);
	BOOL SaveKey(LPCTSTR lpFileName);
private:
	void DeletaKeyTree(HKEY);
protected:	
	HKEY 	  m_hSubKey;    //����򿪵��Ӽ����
	HKEY    m_hRootKey;   //����������
};

#endif
