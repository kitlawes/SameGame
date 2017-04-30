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
}

CSameGameDoc::~CSameGameDoc()
{
}

BOOL CSameGameDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	//  Set (or reset) the game board
	m_board.SetupBoard();

	return TRUE;
}