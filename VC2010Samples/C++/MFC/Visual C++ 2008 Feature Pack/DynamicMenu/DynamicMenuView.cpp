// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#include "stdafx.h"
#include "DynamicMenu.h"

#include "DynamicMenuDoc.h"
#include "DynamicMenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const CString strInfo = 
	_T("This sample illustrates how a popup menu and a menu bar can be changed on the fly.\r\n\r\n")
	_T("The following features are available:\r\n")
	_T("* Insert two dynamic menu items under the 'Edit' menu (see CMainFrame::OnShowPopupMenu)\r\n")
	_T("* Insert a dynamic popup menu 'DynamicMenu' into the top-level menu bar\r\n")
	_T("* Draw an image on a dynamic menu item\r\n\r\n")
	_T("The project was generated by Application Wizard\r\n")
	_T("Please note //----Example----// comments in the example source code\r\n")
	_T("CMyMenuBar class was added in order to demonstrate how to change the top-level menu bar");


/////////////////////////////////////////////////////////////////////////////
// CDynamicMenuView

IMPLEMENT_DYNCREATE(CDynamicMenuView, CView)

BEGIN_MESSAGE_MAP(CDynamicMenuView, CView)
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynamicMenuView construction/destruction

CDynamicMenuView::CDynamicMenuView()
{
	// TODO: add construction code here

}

CDynamicMenuView::~CDynamicMenuView()
{
}

BOOL CDynamicMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDynamicMenuView drawing

void CDynamicMenuView::OnDraw(CDC* pDC)
{
//	CDynamicMenuDoc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);

	const int iOffset = 20;

	CFont* pFontOld = (CFont*) pDC->SelectStockObject (DEFAULT_GUI_FONT);
	ASSERT (pFontOld != NULL);

	CRect rectClient;
	GetClientRect (&rectClient);

	CRect rectText = rectClient;
	rectText.DeflateRect (iOffset, iOffset);
	pDC->DrawText (strInfo, rectText, DT_CALCRECT | DT_WORDBREAK);

	rectText.OffsetRect (	(rectClient.Width () - rectText.Width () - 2 * iOffset) / 2,
							(rectClient.Height () - rectText.Height () - 2 * iOffset) / 2);

	CRect rectFrame = rectText;
	rectFrame.InflateRect (iOffset, iOffset);

	pDC->FillSolidRect (rectFrame, ::GetSysColor (COLOR_INFOBK));
	
	rectFrame.DeflateRect (1, 1);
	pDC->Draw3dRect (rectFrame, ::GetSysColor (COLOR_3DSHADOW), 
					::GetSysColor (COLOR_3DLIGHT));

	rectFrame.DeflateRect (2, 2);
	pDC->Draw3dRect (rectFrame, ::GetSysColor (COLOR_3DSHADOW), 
					::GetSysColor (COLOR_3DLIGHT));

	pDC->SetTextColor (::GetSysColor (COLOR_INFOTEXT));
	pDC->SetBkMode (TRANSPARENT);

	pDC->DrawText (strInfo, rectText, DT_WORDBREAK);

	pDC->SelectObject (pFontOld);
	
}

/////////////////////////////////////////////////////////////////////////////
// CDynamicMenuView printing

void CDynamicMenuView::OnFilePrintPreview() 
{
	AFXPrintPreview (this);
}

BOOL CDynamicMenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDynamicMenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDynamicMenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDynamicMenuView diagnostics

#ifdef _DEBUG
void CDynamicMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CDynamicMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDynamicMenuDoc* CDynamicMenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDynamicMenuDoc)));
	return (CDynamicMenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynamicMenuView message handlers

void CDynamicMenuView::OnContextMenu(CWnd*, CPoint point)
{
	theApp.ShowPopupMenu (IDR_CONTEXT_MENU, point, this);
}
