#include "stdafx.h"
#include "SameGame.h"

#include "SameGameDoc.h"
#include "SameGameView.h"
#include "OptionsDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSameGameView
IMPLEMENT_DYNCREATE(CSameGameView, CView)
BEGIN_MESSAGE_MAP(CSameGameView, CView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_LEVEL_3COLORS, &CSameGameView::OnLevel3colors)
	ON_COMMAND(ID_LEVEL_4COLORS, &CSameGameView::OnLevel4colors)
	ON_COMMAND(ID_LEVEL_5COLORS, &CSameGameView::OnLevel5colors)
	ON_COMMAND(ID_LEVEL_6COLORS, &CSameGameView::OnLevel6colors)
	ON_COMMAND(ID_LEVEL_7COLORS, &CSameGameView::OnLevel7colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3COLORS, &CSameGameView::OnUpdateLevel3colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4COLORS, &CSameGameView::OnUpdateLevel4colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5COLORS, &CSameGameView::OnUpdateLevel5colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6COLORS, &CSameGameView::OnUpdateLevel6colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7COLORS, &CSameGameView::OnUpdateLevel7colors)
	ON_COMMAND(ID_SETUP_BLOCKCOUNT, &CSameGameView::OnSetupBlockcount)
	ON_COMMAND(ID_SETUP_BLOCKSIZE, &CSameGameView::OnSetupBlocksize)
END_MESSAGE_MAP()

// CSameGameView construction/destruction
CSameGameView::CSameGameView()
{
}

CSameGameView::~CSameGameView()
{
}

BOOL CSameGameView::PreCreateWindow(CREATESTRUCT& cs)
{
	return CView::PreCreateWindow(cs);
}

// CSameGameView drawing

void CSameGameView::OnDraw(CDC* pDC) // MFC will comment out the argument name by default; uncomment it
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Save the current state of the device context
	int nDCSave = pDC->SaveDC();
	//  Get the client rectangle
	CRect rcClient;
	GetClientRect(&rcClient);
	//  Get the background color of the board
	COLORREF clr = pDoc->GetBoardSpace(-1, -1);
	//	Draw the background first
	pDC->FillSolidRect(&rcClient, clr);
	//  Create the brush for drawing
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	//	Draw the squares
	for (int row = 0; row < pDoc->GetRows(); row++)
	{
		for (int col = 0; col < pDoc->GetColumns(); col++)
		{
			//  Get the color for this board space
			clr = pDoc->GetBoardSpace(row, col);
			//  Calculate the size and position of this space
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			//  Fill in the block with the correct color
			pDC->FillSolidRect(&rcBlock, clr);
			//  Draw the block outline
			pDC->Rectangle(&rcBlock);
		}
	}
	//  Restore the device context settings
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
}

// CSameGameView diagnostics
#ifdef _DEBUG
void CSameGameView::AssertValid() const
{
	CView::AssertValid();
}

void CSameGameView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//  non-debug version is inline
CSameGameDoc* CSameGameView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSameGameDoc)));
	return (CSameGameDoc*)m_pDocument;
}
#endif //_DEBUG

void CSameGameView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//  Resize the window
	ResizeWindow();

}

void CSameGameView::ResizeWindow()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the size of the client area and the window
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//  Calculate the difference
	int nWidthDiff = rcWindow.Width() - rcClient.Width();
	int nHeightDiff = rcWindow.Height() - rcClient.Height();
	//  Change the window size based on the size of the game board
	rcWindow.right = rcWindow.left +
		pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top +
		pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	//  The MoveWindow function resizes the frame window
	GetParentFrame()->MoveWindow(&rcWindow);
}

void CSameGameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Get the row and column of the block that was clicked on
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//  Delete the blocks from the document
	int count = pDoc->DeleteBlocks(row, col);
	//  Check if there were any blocks deleted
	if (count > 0)
	{
		//  Force the view to redraw
		Invalidate();
		UpdateWindow();
		//  Check if the game is over
		if (pDoc->IsGameOver())
		{
			//  Get the count remaining
			int remaining = pDoc->GetRemainingCount();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"),
				remaining);
			//  Display the results to the user
			MessageBox(message, _T("Game Over"), MB_OK | MB_ICONINFORMATION);
		}
	}
	//  Default OnLButtonDown
	CView::OnLButtonDown(nFlags, point);
}

void CSameGameView::OnLevel3colors()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->SetNumColors(3);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CSameGameView::OnLevel4colors()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->SetNumColors(4);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CSameGameView::OnLevel5colors()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->SetNumColors(5);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CSameGameView::OnLevel6colors()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->SetNumColors(6);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CSameGameView::OnLevel7colors()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the number of colors
	pDoc->SetNumColors(7);
	//  Force the view to redraw
	Invalidate();
	UpdateWindow();
}

void CSameGameView::OnUpdateLevel3colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 3);
}

void CSameGameView::OnUpdateLevel4colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 4);
}

void CSameGameView::OnUpdateLevel5colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 5);
}

void CSameGameView::OnUpdateLevel6colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 6);
}

void CSameGameView::OnUpdateLevel7colors(CCmdUI *pCmdUI)
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Set the check if this is the right level
	pCmdUI->SetCheck(pDoc->GetNumColors() == 7);
}

void CSameGameView::OnSetupBlockcount()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(true, this);
	//  Set the row and column values
	dlg.m_nValue1 = pDoc->GetRows();
	dlg.m_nValue2 = pDoc->GetColumns();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetRows(dlg.m_nValue1);
		pDoc->SetColumns(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}

void CSameGameView::OnSetupBlocksize()
{
	//  First get a pointer to the document
	CSameGameDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//  Create the options dialog
	COptionsDialog dlg(false, this);
	//  Set the width and height values
	dlg.m_nValue1 = pDoc->GetWidth();
	dlg.m_nValue2 = pDoc->GetHeight();
	//  Display the dialog
	if (dlg.DoModal() == IDOK)
	{
		//  First delete the board
		pDoc->DeleteBoard();
		//  Get the user selected values
		pDoc->SetWidth(dlg.m_nValue1);
		pDoc->SetHeight(dlg.m_nValue2);
		//  Update the board
		pDoc->SetupBoard();
		//  Resize the view
		ResizeWindow();
	}
}