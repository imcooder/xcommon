#include "stdafx.h"
#include "HWXReg.h"
#include <tchar.h>
#include <assert.h>
#define REG_BufferMaxLen		(256)
/*================================================================ 
* ��������    CXReg
* ������      (HKEY hRootKey) 
* ˵����      ������캯��������������ʹ��Ĭ�ϵĲ�����m_hRootKey����ʼ��
			  ΪHKEY_LOCAL_MACHINE, ������в����� m_hRootKeyΪָ����ֵ
================================================================*/ 
CXReg::CXReg(HKEY hRootKey) :m_hSubKey(NULL)
{
	m_hRootKey = hRootKey; 
}
 /************************************************************************
 ����:	SetRootKey
 ȫ��:	void CXReg::SetRootKey( HKEY hRootKey )
 ����:	public 
 ����ֵ:	void: 
 ����:	 ���ø���ֵ
 ����:	HKEY hRootKey: 
 ************************************************************************/
void CXReg::SetRootKey( HKEY hRootKey )
{
	assert(NULL != hRootKey);
	m_hRootKey = hRootKey;
}

CXReg::~CXReg() //�����������йرմ�ע�����
{
	Close();
}

/*================================================================ 
* ��������    VerifyKey
* ������      (HKEY hRootKey, LPCTSTR pszPath) 
* ��������:   �жϸ�����·���Ƿ���� (���д򿪵Ĺ���)
			  �����һ������ΪNULL����ʹ��Ĭ�ϵĸ�����
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::VerifyKey (LPCTSTR pszPath)
{
 	BOOL blRet = TRUE;
	if (NULL != m_hSubKey)
	{
		RegCloseKey(m_hSubKey);
		m_hSubKey = NULL;
	}
	if(ERROR_SUCCESS != RegOpenKeyEx (m_hRootKey, pszPath, 0L,
										KEY_ALL_ACCESS, &m_hSubKey))
	{	
		blRet = FALSE;
		goto Err;
	}
Err:
	return blRet;
}


/*================================================================ 
* ��������    VerifyValue
* ������      (LPCTSTR pszValue)
* ��������:   �жϸ�����ֵ�Ƿ���� �����ȵ���VerifyKey��Ȼ����ʹ�øú�����
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::VerifyValue (LPCTSTR pszValue)
{
	BOOL blRet = FALSE;
	if(ERROR_SUCCESS == RegQueryValueEx(m_hSubKey, pszValue, NULL,
		NULL, NULL, NULL))
	{
		blRet = TRUE;
		goto Err;
	}
Err:
	return blRet;
}

/*================================================================ 
* ��������    VerifyValue
* ������      (LPCTSTR pszValue)
* ��������:   �ж�ָ���ļ����Ƿ����ĳ��ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::IsEqual(LPCTSTR pszValue,DWORD dwValue)
{
	DWORD dwTemp;
	Read(pszValue, dwTemp);
	if(dwTemp == dwValue)
		return TRUE;
	return FALSE;
}
BOOL CXReg::IsEqual(LPCTSTR pszValue,LPCTSTR lpszString)
{
	CXStringT str;
	Read(pszValue, str);
	if(0 == str.CompareNoCase(lpszString))
		return TRUE;
	return FALSE;
}


/*================================================================ 
* ��������    CreateKey
* ������      (HKEY hRootKey, LPCTSTR pszPath)
* ��������:   ����·��
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::CreateKey (LPCTSTR pszPath)
{
	DWORD dwTmp;	
	if (m_hSubKey)
	{
		RegCloseKey(m_hSubKey);
		m_hSubKey = NULL;
	}
	if(ERROR_SUCCESS == RegCreateKeyEx (m_hRootKey, pszPath, 0L, NULL,
		REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &m_hSubKey, &dwTmp))
		return TRUE;

	return FALSE;
}


/*================================================================ 
* ��������    Write
* ������      (LPCTSTR lpszKeyName, DWORD dwVal)
* ��������:   д��DWORDֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Write (LPCTSTR lpszKeyName, DWORD dwVal)
{
	return ::RegSetValueEx (m_hSubKey, lpszKeyName, 0L, REG_DWORD,
		(CONST BYTE*) &dwVal, sizeof(DWORD));
}


/*================================================================ 
* ��������    Write
* ������      (LPCTSTR lpszKeyName, LPCTSTR pszData)
* ��������:   д���ַ���ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Write (LPCTSTR lpszKeyName, LPCTSTR pszData)
{
	if(ERROR_SUCCESS == RegSetValueEx (m_hSubKey, lpszKeyName, 0L, REG_SZ,
		(const BYTE*) pszData, (LONG)(_tcslen(pszData) + 1) * sizeof(TCHAR)))
	{
		return TRUE;
	}	
	return FALSE;
}
/*================================================================ 
* ��������    Write
* ������      (LPCTSTR lpszKeyName, BYTE *pbData, long nSiz)
* ��������:   д�������
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Write (LPCTSTR lpszKeyName, const BYTE *pbData, DWORD dwSize)
{
	assert(NULL != pbData && dwSize > 0);	
	if(ERROR_SUCCESS == RegSetValueEx (m_hSubKey, lpszKeyName, 0L, REG_BINARY,
		(const BYTE*)pbData, dwSize))
	{
		return TRUE;
	}	
	return FALSE;
}
/*================================================================ 
* ��������    Read
* ������      (LPCTSTR lpszKeyName, DWORD& dwVal) ��2������ͨ�����ô��ݣ������ں������޸�ʵ��
* ��������:   ��ȡDWORDֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Read (LPCTSTR lpszKeyName, DWORD& dwVal)
{
	DWORD dwType;
	DWORD dwSize = sizeof (DWORD);
	DWORD dwDest;	

	if(ERROR_SUCCESS == RegQueryValueEx (m_hSubKey, (LPCTSTR) lpszKeyName, NULL, 
		&dwType, (BYTE *) &dwDest, &dwSize))
	{
		dwVal = dwDest;
		return TRUE;
	}

	return FALSE;
}


/*================================================================ 
* ��������    Read
* ������      (LPCTSTR lpszKeyName, CString& sVal) ��2������ͨ�����ô��ݣ������ں������޸�ʵ��
* ��������:   ��ȡ�ַ���ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Read (LPCTSTR lpszKeyName, CXString& sVal)
{

	DWORD dwType;
	DWORD dwSize = REG_BufferMaxLen;
	TCHAR szString[REG_BufferMaxLen];

	if(ERROR_SUCCESS == RegQueryValueEx (m_hSubKey, lpszKeyName, NULL,
		&dwType, (BYTE *)szString, &dwSize))
	{
		sVal = szString;
		return TRUE;
	}
	return FALSE;
}

/*================================================================ 
* ��������    Read
* ������      (LPCTSTR lpszKeyName, BYTE *pbVal, long nBufferSize) ��2������ͨ��ָ�봫�ݣ������ں������޸�ʵ��
* ��������:   ��ȡ�ַ���ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::Read (LPCTSTR lpszKeyName, BYTE *pbData, DWORD dwSize)
{	
	assert(NULL != pbData && dwSize > 0);
	DWORD dwType;
	if(ERROR_SUCCESS == RegQueryValueEx (m_hSubKey, lpszKeyName, NULL,
		&dwType, pbData, &dwSize))
	{		
		return TRUE;
	}
	return FALSE;
}

/*================================================================ 
* ��������    DeleteValue
* ������      (LPCTSTR pszValue) 
* ��������:   ɾ��ֵ
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::DeleteValue (LPCTSTR pszValue)
{
	if(ERROR_SUCCESS == ::RegDeleteValue(m_hSubKey, pszValue))		
		return TRUE;
	else
		return FALSE;
}

/*================================================================ 
* ��������    DeleteKey
* ������      (HKEY hRootKey, LPCTSTR pszPath) 
* ��������:   ɾ��·��
* ����ֵ��    BOOL
* �� �ߣ�     
================================================================*/ 
BOOL CXReg::DeleteKey (LPCTSTR pszPath)
{	
	assert(NULL != pszPath);
	BOOL blRet = TRUE;
	HKEY hOldSubKey;
	if (!pszPath)
	{
		blRet = FALSE;
		goto Exit_;
	}
	hOldSubKey = m_hSubKey;
	if(FALSE == VerifyKey(pszPath))
	{		
		blRet = FALSE;
		goto Exit_;
	}
	DeletaKeyTree(m_hSubKey);
	m_hSubKey = hOldSubKey;		
	if (ERROR_SUCCESS == RegDeleteKey(m_hRootKey, pszPath))
	{
		blRet = TRUE;		
	}
Exit_:
	return blRet;
}
BOOL CXReg::DeleteKey()
{	
	assert(NULL != m_hSubKey);
	BOOL blRet = FALSE;
	TCHAR szKeyPath[REG_BufferMaxLen];
	DWORD dwBufferLen = REG_BufferMaxLen;
	if (ERROR_SUCCESS != (blRet = RegQueryInfoKey(m_hSubKey, szKeyPath, &dwBufferLen, 
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL)))
	{
		goto Exit_;
	}
	DeletaKeyTree(m_hSubKey);		
	if (ERROR_SUCCESS != RegDeleteKey(m_hRootKey, szKeyPath))
	{
		goto Exit_;	
	}
	blRet = TRUE;
	m_hSubKey = NULL;
Exit_:
	return blRet;
}

/*================================================================ 
* ��������    Close
* ������      
* ��������:   �ر�ע���
* ����ֵ��    void
* �� �ߣ�     
================================================================*/ 
void CXReg::Close()
{
	if (m_hSubKey)
	{
		::RegCloseKey (m_hSubKey);
		m_hSubKey = NULL;
	}
}
BOOL CXReg::RestoreKey(LPCTSTR lpFileName)
{
	assert(m_hSubKey);
	assert(lpFileName);
	BOOL blRet = TRUE;
	
	if(ERROR_SUCCESS != RegRestoreKey(m_hSubKey, lpFileName, REG_WHOLE_HIVE_VOLATILE))
	{
		blRet = FALSE;
		goto Err;
	}
Err:
	return blRet;
}

BOOL CXReg::SaveKey(LPCTSTR lpFileName)
{
	assert(m_hSubKey);
	assert(lpFileName);
	BOOL blRet = TRUE;
	if(ERROR_SUCCESS != (blRet = RegSaveKey(m_hSubKey, lpFileName, NULL)))
	{
		blRet = FALSE;
		goto Err;
	}
Err:	
	return blRet;
}
void  CXReg::DeletaKeyTree(HKEY hKey) 
{   
	DWORD   dwCount = 0;   
	TCHAR	szSubkeyName[128];   
	HKEY   hKeySub; 
    
	if(ERROR_SUCCESS != RegQueryInfoKey(hKey, 0, 0, 0, &dwCount, 0, 0, 0, 0, 0, 0, 0))   
	{   		
		return;   
	}   
	else if(dwCount)   
	{
		for(DWORD i = 0; i < dwCount; i ++)   
		{   		 
			if(ERROR_SUCCESS != RegEnumKey(hKey, 0, szSubkeyName, 128))   
			{   
				assert(0);  					
				return;   
			}   			
			if(ERROR_SUCCESS != RegOpenKey(hKey, szSubkeyName, &hKeySub))   
			{   
				assert(0);   					
				return;   
			}   
			DeletaKeyTree(hKeySub);//���õݹ�   			 
			if(ERROR_SUCCESS != RegDeleteKey(hKey, szSubkeyName))   
			{   
				assert(0);   					  
				return;   
			}   
			RegCloseKey(hKeySub);   
		}  
	}		
} 