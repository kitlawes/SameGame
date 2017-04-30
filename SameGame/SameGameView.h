#pragma once

class CSameGameView : public CView
{
protected: // create from serialization only
	CSameGameView();
	virtual ~CSameGameView();
	DECLARE_DYNCREATE(CSameGameView)

	// Attributes
public:
	CSameGameDoc* GetDocument() const;
	// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

	// Implementation
public:
	void ResizeWindow();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	/*  Functions to change the difficulty level */
	afx_msg void OnLevel3colors();
	afx_msg void OnLevel4colors();
	afx_msg void OnLevel5colors();
	afx_msg void OnLevel6colors();
	afx_msg void OnLevel7colors();
	/*  Functions to update the menu options */
	afx_msg void OnUpdateLevel3colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel4colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel5colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel6colors(CCmdUI *pCmdUI);
	afx_msg void OnUpdateLevel7colors(CCmdUI *pCmdUI);
	afx_msg void OnSetupBlockcount();
	afx_msg void OnSetupBlocksize();
	/*  Functions for undo/redo */
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
	/*  Functions to update the undo/redo menu options */
	afx_msg void OnUpdateEditUndo(CCmdUI *pCmdUI);
	afx_msg void OnUpdateEditRedo(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in SameGameView.cpp
inline CSameGameDoc* CSameGameView::GetDocument() const
{
	return reinterpret_cast<CSameGameDoc*>(m_pDocument);
}
#endif
