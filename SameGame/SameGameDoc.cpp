#include "stdafx.h"
#include "SameGame.h"

#include "SameGameDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSameGameDoc
IMPLEMENT_DYNCREATE(CSameGameDoc, CDocument)
BEGIN_MESSAGE_MAP(CSameGameDoc, CDocument)
END_MESSAGE_MAP()

// CSameGameDoc construction/destruction
CSameGameDoc::CSameGameDoc()
{

	//  There should always be a game board
	m_board = new CSameGameBoard();

}

CSameGameDoc::~CSameGameDoc()
{

	//  Delete the current game board
	delete m_board;
	//  Delete everything from the undo stack
	ClearUndo();
	//  Delete everything from the redo stack
	ClearRedo();

}

BOOL CSameGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//  Set (or reset) the game board
	m_board->SetupBoard();
	//  Clear the undo/redo stacks
	ClearUndo();
	ClearRedo();


	return TRUE;
}

void CSameGameDoc::SetNumColors(int nColors)
{
	//  Set the number of colors first
	m_board->SetNumColors(nColors);
	//  Then reset the game board
	m_board->SetupBoard();
}


int CSameGameDoc::DeleteBlocks(int row, int col)
{
	//  Save the current board in the undo stack
	m_undo.push(new CSameGameBoard(*m_board));
	//  Empty out the redo stack
	ClearRedo();
	//  Then delete the blocks
	int blocks = m_board->DeleteBlocks(row, col);
	//  Clear the undo stack at the end of a game
	if (m_board->IsGameOver())
		ClearUndo();
	//  Return the number of blocks
	return blocks;
}

void CSameGameDoc::UndoLast()
{
	//  First make sure that there is a move to undo
	if (m_undo.empty())
		return;
	//  Take the current board and put it on the redo
	m_redo.push(m_board);
	//  Take the top undo and make it the current
	m_board = m_undo.top();
	m_undo.pop();
}

bool CSameGameDoc::CanUndo()
{
	//  Can undo if the undo stack isn't empty
	return !m_undo.empty();
}

void CSameGameDoc::RedoLast()
{
	//  First make sure that there is a move to redo
	if (m_redo.empty())
		return;
	//  Take the current board and put it on the undo
	m_undo.push(m_board);
	//  Take the top redo and make it the current
	m_board = m_redo.top();
	m_redo.pop();
}

bool CSameGameDoc::CanRedo()
{
	//  Can redo if the redo stack isn't empty
	return !m_redo.empty();
}

void CSameGameDoc::ClearUndo()
{
	//  Delete everything from the undo stack
	while (!m_undo.empty())
	{
		delete m_undo.top();
		m_undo.pop();
	}
}

void CSameGameDoc::ClearRedo()
{
	//  Delete everything from the redo stack
	while (!m_redo.empty())
	{
		delete m_redo.top();
		m_redo.pop();
	}
}