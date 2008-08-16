// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BCGPCalendarDemo.h"

#include "MainFrm.h"

#include "BCGPCalendarDemoDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)


BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_TIMECHANGE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_VIEW_CUSTOMIZE, OnViewCustomize)
	ON_REGISTERED_MESSAGE(BCGM_RESETTOOLBAR, OnToolbarReset)
	ON_REGISTERED_MESSAGE(BCGM_TOOLBARMENU, OnToolbarContextMenu)
	ON_COMMAND(ID_VIEW_CALENDARBAR, OnViewCalendarBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CALENDARBAR, OnUpdateViewCalendarBar)
	ON_COMMAND(ID_VIEW_PROPBAR, OnViewPropBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPBAR, OnUpdateViewPropBar)
	ON_COMMAND(ID_VIEW_CAPTIONBAR, OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTIONBAR, OnUpdateViewCaptionBar)
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_2007_4, OnAppLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_2000, ID_VIEW_APPLOOK_2007_4, OnUpdateAppLook)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	m_nAppLook = theApp.GetInt (_T("ApplicationLook"), ID_VIEW_APPLOOK_2003);
	CBCGPPopupMenu::SetForceMenuFocus (FALSE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	OnAppLook (m_nAppLook);

	CBCGPToolBar::EnableQuickCustomization ();

	if (!m_wndMenuBar.Create (this))
	{
		TRACE0("Failed to create menubar\n");
		return -1;      // fail to create
	}

	m_wndMenuBar.SetBarStyle(m_wndMenuBar.GetBarStyle() | CBRS_SIZE_DYNAMIC);

	// Detect color depth. 256 color toolbars can be used in the
	// high or true color modes only (bits per pixel is > 8):
	CClientDC dc (this);
	BOOL bIsHighColor = dc.GetDeviceCaps (BITSPIXEL) > 8;

	UINT uiToolbarHotID = bIsHighColor ? IDB_TOOLBAR256 : 0;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	uiToolbarHotID = bIsHighColor ? IDB_PLANNER_TB256 : 0;

	if (!m_wndPlannerToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, 
		CRect(1, 1, 1, 1), AFX_IDW_TOOLBAR + 1) ||
		!m_wndPlannerToolBar.LoadToolBar(IDR_PLANNER, 0, 0, FALSE, 0, 0, uiToolbarHotID))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	CBCGPToolBar::AddToolBarForImageCollection (IDR_PLANNER_DUMMY, 
		bIsHighColor ? IDB_PLANNER_DUMMY_TB256 : 0);

	CImageList imagesWorkspace;
	imagesWorkspace.Create (IDB_WORKSPACE, 16, 0, RGB (255, 0, 255));

	if (!m_wndCalendarBar.Create (_T("Calendar"), this, CRect (0, 0, 200, 300),
		TRUE, ID_VIEW_CALENDARBAR,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_LEFT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create calendar bar\n");
		return FALSE;      // fail to create
	}

	m_wndCalendarBar.SetIcon (imagesWorkspace.ExtractIcon (0), FALSE);

	if (!m_wndPropBar.Create (_T("Properties"), this, CRect (0, 0, 150, 200),
		TRUE, ID_VIEW_PROPBAR,
		WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN | CBRS_RIGHT | CBRS_FLOAT_MULTI))
	{
		TRACE0("Failed to create calendar bar\n");
		return FALSE;      // fail to create
	}

	m_wndPropBar.SetIcon (imagesWorkspace.ExtractIcon (1), FALSE);

	m_wndToolBar.SetWindowText (_T("Standard"));
	m_wndPlannerToolBar.SetWindowText (_T("Planner"));

	m_wndMenuBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPlannerToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndCalendarBar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndPropBar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	EnableAutoHideBars(CBRS_ALIGN_ANY);

	if (!m_wndCaptionBar.Create (WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this,
		ID_VIEW_CAPTIONBAR, -1))
	{
		TRACE0("Failed to create caption bar\n");
		return -1;      // fail to create
	}

	m_wndCaptionBar.SetFlatBorder ();
	m_wndCaptionBar.SetText (_T("<Put your caption here>"));
	m_bmpCaption.LoadBitmap (IDB_CAPTION);
	m_wndCaptionBar.SetBitmap (m_bmpCaption, RGB (255, 0, 255));

	DockControlBar (&m_wndMenuBar);
	DockControlBar (&m_wndPlannerToolBar);
	DockControlBarLeftOf (&m_wndToolBar, &m_wndPlannerToolBar);

	DockControlBar (&m_wndCalendarBar);
	DockControlBar (&m_wndPropBar);

	m_wndToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	m_wndPlannerToolBar.EnableCustomizeButton (TRUE, ID_VIEW_CUSTOMIZE, _T("Customize..."));
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


void CMainFrame::OnViewCustomize()
{
	//------------------------------------
	// Create a customize toolbars dialog:
	//------------------------------------
	CBCGPToolbarCustomize* pDlgCust = new CBCGPToolbarCustomize (this,
		TRUE /* Automatic menus scaning */
		);

	pDlgCust->Create ();
}

LRESULT CMainFrame::OnToolbarContextMenu(WPARAM,LPARAM lp)
{
	CPoint point (BCG_GET_X_LPARAM(lp), BCG_GET_Y_LPARAM(lp));

	CMenu menu;
	VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

	CMenu* pPopup = menu.GetSubMenu(0);
	ASSERT(pPopup != NULL);

	CBCGPPopupMenu* pPopupMenu = new CBCGPPopupMenu;
	pPopupMenu->Create (this, point.x, point.y, pPopup->Detach ());

	return 0;
}

afx_msg LRESULT CMainFrame::OnToolbarReset (WPARAM wp, LPARAM)
{
	UINT uiToolBarId = (UINT) wp;
	if (uiToolBarId == IDR_PLANNER)
	{
		// Replace "Back" and "Forward" buttons by the menu buttons
		// with the history lists:

		CMenu menu;
		menu.LoadMenu (IDR_PLANNER_NEW);

		m_wndPlannerToolBar.ReplaceButton (ID_PLANNER_NEW, 
			CBCGPToolbarMenuButton (ID_PLANNER_NEW, menu, 
						CImageHash::GetImageOfCommand (ID_PLANNER_NEW), NULL));
	}

	return 0;
}

BOOL CMainFrame::OnShowPopupMenu (CBCGPPopupMenu* pMenuPopup)
{
	//---------------------------------------------------------
	// Replace ID_VIEW_TOOLBARS menu item to the toolbars list:
	//---------------------------------------------------------
    CFrameWnd::OnShowPopupMenu (pMenuPopup);

/*
	CBCGPFrameWnd::OnShowPopupMenu (pMenuPopup);

	CBCGPPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT_VALID (pMenuBar);

	CBCGPToolbarMenuButton* pParentButton = pMenuPopup->GetParentButton ();
	if (pParentButton == NULL)
	{
		return TRUE;
	}

	switch (pParentButton->m_nID)
	{
	case ID_GO_BACK:
	case ID_GO_FORWARD:
		{
			if (CBCGPToolBar::IsCustomizeMode ())
			{
				return FALSE;
			}
		}
	}

	return TRUE;
*/

	if (pMenuPopup == NULL)
	{
		return TRUE;
	}

	CBCGPPopupMenuBar* pMenuBar = pMenuPopup->GetMenuBar ();
	ASSERT_VALID (pMenuBar);

    if (pMenuBar->CommandToIndex (ID_VIEW_TOOLBARS) >= 0)
    {
		if (CBCGPToolBar::IsCustomizeMode ())
		{
			//----------------------------------------------------
			// Don't show toolbars list in the cuztomization mode!
			//----------------------------------------------------
			return FALSE;
		}

		pMenuPopup->RemoveAllItems ();

		CMenu menu;
		VERIFY(menu.LoadMenu (IDR_POPUP_TOOLBAR));

		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pMenuBar->ImportFromMenu (*pPopup, TRUE);
    }
	else
	{
		CBCGPToolbarMenuButton* pParentButton = pMenuPopup->GetParentButton ();
		if (pParentButton == NULL)
		{
			return TRUE;
		}

		switch (pParentButton->m_nID)
		{
		case ID_PLANNER_NEW:
			{
				if (CBCGPToolBar::IsCustomizeMode ())
				{
					return FALSE;
				}
			}
		}
	}

	return TRUE;
}

void CMainFrame::OnViewCalendarBar() 
{
	ShowControlBar (&m_wndCalendarBar,
					!(m_wndCalendarBar.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewCalendarBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndCalendarBar.IsVisible ());
}

void CMainFrame::OnViewPropBar() 
{
	ShowControlBar (&m_wndPropBar,
					!(m_wndPropBar.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewPropBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndPropBar.IsVisible ());
}

void CMainFrame::OnAppLook(UINT id)
{
	CBCGPDockManager::SetDockMode (DT_SMART);

	m_nAppLook = id;

	CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D;

	switch (m_nAppLook)
	{
	case ID_VIEW_APPLOOK_2000:
		// enable Office 2000 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager));
		break;

	case ID_VIEW_APPLOOK_XP:
		// enable Office XP look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerXP));
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		// enable Windows XP look (in other OS Office XP look will be used):
		CBCGPWinXPVisualManager::m_b3DTabsXPTheme = TRUE;
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPWinXPVisualManager));
		break;

	case ID_VIEW_APPLOOK_2003:
		// enable Office 2003 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2003));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	case ID_VIEW_APPLOOK_VS2005:
		// enable VS.NET 2005 look:
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManagerVS2005));
		CBCGPTabbedControlBar::m_StyleTabWnd = CBCGPTabWnd::STYLE_3D_ROUNDED;
		CBCGPVisualManager::GetInstance ();
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_1:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_LunaBlue);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_2:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_ObsidianBlack);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_3:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Aqua);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	case ID_VIEW_APPLOOK_2007_4:
		// enable Office 2007 look:
		CBCGPVisualManager2007::SetStyle (CBCGPVisualManager2007::VS2007_Silver);
		CBCGPVisualManager::SetDefaultManager (RUNTIME_CLASS (CBCGPVisualManager2007));
		CBCGPDockManager::SetDockMode (DT_SMART);
		break;

	default:
		ASSERT (FALSE);
	}

	CBCGPDockManager* pDockManager = GetDockManager ();
	if (pDockManager != NULL)
	{
		ASSERT_VALID (pDockManager);
		pDockManager->AdjustBarFrames ();
	}

	CBCGPTabbedControlBar::ResetTabs ();

	RecalcLayout ();
	RedrawWindow ();

	theApp.WriteInt (_T("ApplicationLook"), m_nAppLook);
}

void CMainFrame::OnUpdateAppLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio (m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::SetDateInterval (const COleDateTime& date1, const COleDateTime& date2)
{
	CBCGPCalendarDemoDoc* pDoc = (CBCGPCalendarDemoDoc*) GetActiveDocument ();
	if (pDoc != NULL)
	{
		ASSERT_VALID (pDoc);
		pDoc->SetDateInterval (date1, date2);
	}
}

void CMainFrame::OnViewCaptionBar() 
{
	ShowControlBar (&m_wndCaptionBar,
					!(m_wndCaptionBar.IsVisible ()),
					FALSE, TRUE);
	RecalcLayout ();
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck (m_wndCaptionBar.IsVisible ());
}

void CMainFrame::OnTimeChange() 
{
	CFrameWnd::OnTimeChange();
	
	CView* pView = GetActiveView ();
	if (pView != NULL)
	{
		pView->SendMessage (WM_TIMECHANGE, 0, 0);
	}
}

void CMainFrame::SetCaptionText (const CString& strText)
{
	ASSERT (!strText.IsEmpty ());

	m_wndCaptionBar.SetText (strText);
}
