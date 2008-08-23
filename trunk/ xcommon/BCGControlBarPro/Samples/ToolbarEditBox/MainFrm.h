// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__07DBBC5C_7B4E_422F_8AAC_90146B1C675A__INCLUDED_)
#define AFX_MAINFRM_H__07DBBC5C_7B4E_422F_8AAC_90146B1C675A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define CFrameWnd CBCGPFrameWnd

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CBCGPMenuBar		m_wndMenuBar;
	CBCGPStatusBar		m_wndStatusBar;
	CBCGPToolBar		m_wndToolBar;

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnEdit1();
	afx_msg void OnEdit2();
	afx_msg void OnEdit3();
	//}}AFX_MSG
	afx_msg void OnViewCustomize();
	afx_msg LRESULT OnToolbarReset(WPARAM,LPARAM);
	afx_msg LRESULT OnToolbarContextMenu(WPARAM,LPARAM);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup);

//----Exmaple----//
	void OnEdit (UINT uiCmd);
//----Exmaple----//
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__07DBBC5C_7B4E_422F_8AAC_90146B1C675A__INCLUDED_)