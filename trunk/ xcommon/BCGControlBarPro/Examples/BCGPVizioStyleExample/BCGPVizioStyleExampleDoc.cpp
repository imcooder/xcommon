// BCGPVizioStyleExampleDoc.cpp : implementation of the CBCGPVizioStyleExampleDoc class
//

#include "stdafx.h"
#include "BCGPVizioStyleExample.h"

#include "BCGPVizioStyleExampleDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBCGPVizioStyleExampleDoc

IMPLEMENT_DYNCREATE(CBCGPVizioStyleExampleDoc, CDocument)

BEGIN_MESSAGE_MAP(CBCGPVizioStyleExampleDoc, CDocument)
	//{{AFX_MSG_MAP(CBCGPVizioStyleExampleDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBCGPVizioStyleExampleDoc construction/destruction

CBCGPVizioStyleExampleDoc::CBCGPVizioStyleExampleDoc()
{
	// TODO: add one-time construction code here

}

CBCGPVizioStyleExampleDoc::~CBCGPVizioStyleExampleDoc()
{
}

BOOL CBCGPVizioStyleExampleDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBCGPVizioStyleExampleDoc serialization

void CBCGPVizioStyleExampleDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBCGPVizioStyleExampleDoc diagnostics

#ifdef _DEBUG
void CBCGPVizioStyleExampleDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBCGPVizioStyleExampleDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBCGPVizioStyleExampleDoc commands
