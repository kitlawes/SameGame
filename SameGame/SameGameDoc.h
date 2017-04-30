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
	void SetWidth(int nWidth) { m_board.SetWidth(nWidth); }
	int GetHeight(void) { return m_board.GetHeight(); }
	void SetHeight(int nHeight) { m_board.SetHeight(nHeight); }
	int GetColumns(void) { return m_board.GetColumns(); }
	void SetColumns(int nColumns) { m_board.SetColumns(nColumns); }
	int GetRows(void) { return m_board.GetRows(); }
	void SetRows(int nRows) { m_board.SetRows(nRows); }
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
	int GetNumColors() { return m_board.GetNumColors(); }
	void SetNumColors(int nColors);

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