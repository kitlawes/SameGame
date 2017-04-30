#pragma once

#include "SameGameBoard.h"
#include <stack>

class CSameGameDoc : public CDocument
{
protected: // create from serialization only
	CSameGameDoc();
	virtual ~CSameGameDoc();
	DECLARE_DYNCREATE(CSameGameDoc)

	// Operations
public:
	/*  Functions for accessing the game board */
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board->GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board->SetupBoard(); }
	int GetWidth(void) { return m_board->GetWidth(); }
	void SetWidth(int nWidth) { m_board->SetWidth(nWidth); }
	int GetHeight(void) { return m_board->GetHeight(); }
	void SetHeight(int nHeight) { m_board->SetHeight(nHeight); }
	int GetColumns(void) { return m_board->GetColumns(); }
	void SetColumns(int nColumns) { m_board->SetColumns(nColumns); }
	int GetRows(void) { return m_board->GetRows(); }
	void SetRows(int nRows) { m_board->SetRows(nRows); }
	void DeleteBoard(void) { m_board->DeleteBoard(); }
	bool IsGameOver() { return m_board->IsGameOver(); }
	/*  Notice we removed the implementation of this function */
	int DeleteBlocks(int row, int col);
	int GetRemainingCount()
	{
		return m_board->GetRemainingCount();
	}
	int GetNumColors() { return m_board->GetNumColors(); }
	void SetNumColors(int nColors);
	/*  Undo/redo functions */
	void UndoLast();
	bool CanUndo();
	void RedoLast();
	bool CanRedo();
	// Overrides
public:
	virtual BOOL OnNewDocument();

protected:
	/*  Functions to clear undo/redo stacks */
	void ClearUndo();
	void ClearRedo();
	/*  Instance of the game board--notice that we made it a pointer */
	CSameGameBoard* m_board;
	/*  Undo stack */
	std::stack<CSameGameBoard*> m_undo;
	/*  Redo stack */
	std::stack<CSameGameBoard*> m_redo;


	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};