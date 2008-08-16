#if !defined(AFX_BCGPPLANNERCLOCKICONSDEMO_H__B8C60AAF_318B_462A_A4E4_B8697060C209__INCLUDED_)
#define AFX_BCGPPLANNERCLOCKICONSDEMO_H__B8C60AAF_318B_462A_A4E4_B8697060C209__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BCGPPlannerClockIconsDemo.h : header file
//

#include "BCGPPlannerClockIcons.h"

/////////////////////////////////////////////////////////////////////////////
// CBCGPPlannerClockIconsDemo

class CBCGPPlannerClockIconsDemo : public CBCGPPlannerClockIcons
{
	DECLARE_DYNCREATE(CBCGPPlannerClockIconsDemo)

public:
	virtual ~CBCGPPlannerClockIconsDemo();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

// Overrides
public:
	
protected:

	CBCGPPlannerClockIconsDemo();

protected:
	virtual BOOL Initialize ();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BCGPPLANNERCLOCKICONSDEMO_H__B8C60AAF_318B_462A_A4E4_B8697060C209__INCLUDED_)
