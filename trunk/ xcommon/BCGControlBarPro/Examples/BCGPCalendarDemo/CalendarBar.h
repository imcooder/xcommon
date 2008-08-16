// CalendarBar.h : interface of the CCalendarBar class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CALENDARBAR_H__27BD293B_AB9D_4F66_AEAF_6DD7F7807E05__INCLUDED_)
#define AFX_CALENDARBAR_H__27BD293B_AB9D_4F66_AEAF_6DD7F7807E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCalendarBar : public CBCGPDockingControlBar
{
	friend class CMainFrame;

public:
	CCalendarBar();

// Attributes
protected:
	CBCGPCalendar m_wndCalendars;

// Operations
public:
	void UpdateCalendar ();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCalendarBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCalendarBar();

// Generated message map functions
protected:
	//{{AFX_MSG(CCalendarBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	afx_msg LRESULT OnSelChanged(WPARAM, LPARAM);
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CALENDARBAR_H__27BD293B_AB9D_4F66_AEAF_6DD7F7807E05__INCLUDED_)
