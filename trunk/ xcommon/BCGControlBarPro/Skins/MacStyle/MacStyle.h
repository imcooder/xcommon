// MacStyle.h : main header file for the MACSTYLE DLL
//

#if !defined(AFX_SKIN2_H__19EB3018_265B_4B7E_8A74_24470D922F92__INCLUDED_)
#define AFX_SKIN2_H__19EB3018_265B_4B7E_8A74_24470D922F92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMacStyleApp
// See MacStyle.cpp for the implementation of this class
//

class CMacStyleApp : public CWinApp
{
public:
	CMacStyleApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMacStyleApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CMacStyleApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SKIN2_H__19EB3018_265B_4B7E_8A74_24470D922F92__INCLUDED_)
