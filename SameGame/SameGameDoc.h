#pragma once

#include "SameGameBoard.h"

class CSameGameDoc : public CDocument
{
protected: // create from serialization only
	CSameGameDoc();
	virtual ~CSameGameDoc();
	DECLARE_DYNCREATE(CSameGameDoc)

	// Attributes
public:

	// Operations
public:

	/*  Functions for accessing the game board */
	COLORREF GetBoardSpace(int row, int col)
	{
		return m_board.GetBoardSpace(row, col);
	}
	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeight(); }
	int GetColumns(void) { return m_board.GetColumns(); }
	int GetRows(void) { return m_board.GetRows(); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }
	bool IsGameOver() { return m_board.IsGameOver(); }
	int DeleteBlocks(int row, int col)
	{
		return m_board.DeleteBlocks(row, col);
	}
	int GetRemainingCount()
	{
		return m_board.GetRemainingCount();
	}

	// Overrides
public:
	virtual BOOL OnNewDocument();

protected:

	/*  Instance of the game board */
	CSameGameBoard m_board;


	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};