// FindComboBox.cpp : implementation file
//

#include "stdafx.h"
#include "BCGCBDotNetExample.h"
#include "BCGCBDotNetExampleView.h"
#include "FindComboBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFindComboButton

IMPLEMENT_SERIAL(CFindComboButton, CBCGPToolbarComboBoxButton, 1)

BOOL CFindComboButton::m_bHasFocus = FALSE;

BOOL CFindComboButton::NotifyCommand (int iNotifyCode)
{
	BOOL bRes = CBCGPToolbarComboBoxButton::NotifyCommand (iNotifyCode);
	
	switch (iNotifyCode)
	{
	case CBN_KILLFOCUS:
		m_bHasFocus = FALSE;
		bRes = TRUE;
		break;

	case CBN_SETFOCUS:
		m_bHasFocus = TRUE;
		bRes = TRUE;
		break;
	}

	return bRes;
}
