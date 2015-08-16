// OthelloView.cpp : implementation of the COthelloView class
//

#include "stdafx.h"
#include "Othello.h"

#include "Table.h"
#include "OthelloDoc.h"
#include "OthelloView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COthelloView

IMPLEMENT_DYNCREATE(COthelloView, CView)

BEGIN_MESSAGE_MAP(COthelloView, CView)
	//{{AFX_MSG_MAP(COthelloView)
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_GAME_NEW, OnGameNew)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COthelloView construction/destruction

COthelloView::COthelloView()
{
	m_NormalColor=RGB(255,192,0);
	m_SelectColor=RGB(255,232,162);  // White Color
	m_DownColor=RGB(64,0,255);
	m_Current=-1;
	m_CurPlay=T_BLACK;

	m_InitPosition.x=61;
	m_InitPosition.y=77;

	m_ctlAvi.Open(IDR_TOBLACK);
	m_ctlAvi.Play(0,-1,-1);
	// TODO: add construction code here
}

COthelloView::~COthelloView()
{
}

BOOL COthelloView::PreCreateWindow(CREATESTRUCT& cs)
{
	m_hBackGround=(HBITMAP)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDB_TABLE),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	m_hBlack=(HBITMAP)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDB_BLACK),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	m_hWhite=(HBITMAP)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDB_WHITE),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	m_hMaskerX=(HBITMAP)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDB_X),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);

	m_hcurBlack=(HCURSOR)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDC_BLACK),IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR);
	m_hcurWhite=(HCURSOR)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDC_WHITE),IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR);
	m_hcurDefault=(HCURSOR)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDC_POINTER),IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR);
	//m_hcurDefault=(HCURSOR)::LoadImage(cs.hInstance,MAKEINTRESOURCE(IDC_CURSOR1),IMAGE_CURSOR,32,32,LR_DEFAULTCOLOR);

	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COthelloView drawing

void COthelloView::OnDraw(CDC* pDC)
{
	COthelloDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// COthelloView diagnostics

#ifdef _DEBUG
void COthelloView::AssertValid() const
{
	CView::AssertValid();
}

void COthelloView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COthelloDoc* COthelloView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COthelloDoc)));
	return (COthelloDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COthelloView message handlers

void COthelloView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC dcMem;
	
	int i,j;
	CPoint point;
	COthelloDoc *pDoc=GetDocument();
	dcMem.CreateCompatibleDC(&dc);
	BiltBitmap(0,0,380,400,m_hBackGround);
	
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			if ((pDoc->m_MainTable).GetTable(j,i)==T_BLACK)
			{
				point=GetPosition(j,i);
				BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
			}
			if ((pDoc->m_MainTable).GetTable(j,i)==T_WHITE)
			{
				point=GetPosition(j,i);
				BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
			}
		}

	//GetDC()->BitBlt(0,0,380,400,&dcMem,0,0,SRCCOPY);
	DispDown(pDoc,&dc);
	// TODO: Add your message handler code here
	
	// Do not call CView::OnPaint() for painting messages
}

void COthelloView::BiltBitmap(CRect &rc,HBITMAP hbm)
{
	CClientDC dc(this); // device context for painting
	
	CDC dcMem;
	HBITMAP hbmpOld;
	dcMem.CreateCompatibleDC(&dc);
	hbmpOld=(HBITMAP)::SelectObject(dcMem,hbm);

	GetDC()->BitBlt(rc.left,rc.top,rc.right,rc.bottom,&dcMem,0,0,SRCCOPY);
	::SelectObject(dcMem,hbmpOld);
}

void COthelloView::BiltBitmap(int x1,int y1,int x2,int y2,HBITMAP hbm)
{
	CClientDC dc(this); // device context for painting
	
	CDC dcMem;
	HBITMAP hbmpOld;
	dcMem.CreateCompatibleDC(&dc);
	hbmpOld=(HBITMAP)::SelectObject(dcMem,hbm);

	GetDC()->BitBlt(x1,y1,x2,y2,&dcMem,0,0,SRCCOPY);
	::SelectObject(dcMem,hbmpOld);
}

void COthelloView::OnMouseMove(UINT nFlags, CPoint point) 
{
	int i,j,have=0;
	CClientDC dc(this);
	CPoint p;
	COthelloDoc *pDoc=GetDocument();
	
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			p=GetPosition(j,i);
			if (point.x>p.x && point.x<p.x+35 && point.y>p.y && point.y<p.y+35)
			{
				if (m_Current!=i*8+j)
				{
					if (m_Current>=0 && (pDoc->m_MainTable).GetTable(m_Current)<1)
					{
						if ((pDoc->m_MainTable).IsDown(m_CurCol,m_CurRow,m_CurPlay))
						{
							BiltBitmap(m_CurX,m_CurY,m_CurX+34,m_CurY+34,m_hMaskerX);
						}
						else
						{
							dc.FillSolidRect(m_CurX,m_CurY,34,34,m_NormalColor);
						}
						::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
						SetCursor(m_hcurDefault);
					}
					if ((pDoc->m_MainTable).GetTable(j,i)<1 && (pDoc->m_MainTable).IsDown(j,i,m_CurPlay))
					{
						dc.FillSolidRect(p.x,p.y,34,34,m_SelectColor);
						::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
						if (m_CurPlay==T_WHITE)
						{
							SetCursor(m_hcurWhite);
						}
						else
						{
							SetCursor(m_hcurBlack);
						}
					}
					m_Current=i*8+j;
					m_CurX=p.x;
					m_CurY=p.y;
					m_CurCol=j;
					m_CurRow=i;
				}
				have=1;
			}
		}
	if (!have)
	{
		if (m_Current>=0 && (pDoc->m_MainTable).GetTable(m_Current)<1)
		{
			if ((pDoc->m_MainTable).IsDown(m_CurCol,m_CurRow,m_CurPlay))
			{
				BiltBitmap(m_CurX,m_CurY,m_CurX+34,m_CurY+34,m_hMaskerX);
			}
			else
			{
				dc.FillSolidRect(m_CurX,m_CurY,34,34,m_NormalColor);
			}
			::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
			SetCursor(m_hcurDefault);
		}
		m_Current=-1;
	}

	// TODO: Add your message handler code here and/or call default
	
	CView::OnMouseMove(nFlags, point);
}

void COthelloView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CClientDC dc(this);
	COthelloDoc *pDoc=GetDocument();
	if (m_Current>=0 && (pDoc->m_MainTable).GetTable(m_Current)<1)
	{
		if (m_CurPlay==T_BLACK && (pDoc->m_MainTable).IsDown(m_CurCol,m_CurRow,T_BLACK))
		{
			BiltBitmap(m_CurX,m_CurY,m_CurX+33,m_CurY+33,m_hBlack);
			(pDoc->m_MainTable).SetTable(m_Current,T_BLACK);
			DrawTable(m_CurCol,m_CurRow,T_BLACK);
			if (!(pDoc->m_MainTable).HaveDown(T_WHITE))
			{
				if (!(pDoc->m_MainTable).HaveDown(T_BLACK))
				{
					pDoc->GameOver();
				}
				else
				{
					MessageBox("White Pass!!!");
					m_CurPlay=T_BLACK;
				}
			}
			else
			{
				::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
				SetCursor(m_hcurWhite);
cont:
				CPoint point,pos;
				point=pDoc->TryIt(T_WHITE,T_DEPTH);
				(pDoc->m_MainTable).SetTable(point.x,point.y,T_WHITE);
				pos=GetPosition(point.x,point.y);
				//MessageBeep(MB_ICONINFORMATION);
				BiltBitmap(pos.x,pos.y,pos.x+33,pos.y+33,m_hWhite);
				Sleep(100);
				dc.FillSolidRect(pos.x,pos.y,34,34,m_NormalColor);
				Sleep(100);
				BiltBitmap(pos.x,pos.y,pos.x+33,pos.y+33,m_hWhite);
				Sleep(100);
				dc.FillSolidRect(pos.x,pos.y,34,34,m_NormalColor);
				Sleep(100);
				BiltBitmap(pos.x,pos.y,pos.x+33,pos.y+33,m_hWhite);
				DrawTable(point.x,point.y,T_WHITE);
				m_CurPlay=T_BLACK;
				if (!(pDoc->m_MainTable).HaveDown(T_BLACK))
				{
					if (!(pDoc->m_MainTable).HaveDown(T_WHITE))
					{
						pDoc->GameOver();
					}
					else
					{
						MessageBox("Black Pass!!!");
						m_CurPlay=T_WHITE;
						goto cont;
					}
				}
			}
			::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
			SetCursor(m_hcurDefault);
			DispDown(pDoc,&dc);
		}
		else
		{
			if (m_CurPlay==T_WHITE && (pDoc->m_MainTable).IsDown(m_CurCol,m_CurRow,T_WHITE))
			{
				BiltBitmap(m_CurX,m_CurY,m_CurX+33,m_CurY+33,m_hWhite);
				(pDoc->m_MainTable).SetTable(m_Current,T_WHITE);
				DrawTable(m_CurCol,m_CurRow,T_WHITE);
				if (!(pDoc->m_MainTable).HaveDown(T_BLACK))
				{
					if (!(pDoc->m_MainTable).HaveDown(T_WHITE))
					{
						MessageBox("Game Over!!!");
					}
					else
					{
						MessageBox("No!!!");
						m_CurPlay=T_WHITE;
					}
				}
				else
				{
					m_CurPlay=T_BLACK;
				}
				::SetClassLong(GetSafeHwnd(),GCL_HCURSOR,NULL);
				SetCursor(m_hcurDefault);
			}
		}
	}
	// TODO: Add your message handler code here and/or call default
	
	CView::OnLButtonDown(nFlags, point);
}

BOOL COthelloView::DrawTable(int col, int row, BYTE value)
{
	int c,r,yes=0,i,j;
	BYTE v;
	CPoint point;
	COthelloDoc *pDoc=GetDocument();
	if (value==T_WHITE)
	{
		// To Left
		for (c=col-1;c>=0;c--)
		{
			v=(pDoc->m_MainTable).GetTable(c,row);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && col-c>1)
				{
					for (i=col-1;i>c;i--)
					{
						(pDoc->m_MainTable).SetTable(i,row,v);
						point=GetPosition(i,row);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Left-Top
		for (c=col-1,r=row-1;c>=0 && r>=0;c--,r--)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && col-c>1 && row-r>1)
				{
					for (i=col-1,j=row-1;i>c && j>r;i--,j--)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Top
		for (r=row-1;r>=0;r--)
		{
			v=(pDoc->m_MainTable).GetTable(col,r);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && row-r>1)
				{
					for (i=row-1;i>r;i--)
					{
						(pDoc->m_MainTable).SetTable(col,i,v);
						point=GetPosition(col,i);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Right-Top
		for (c=col+1,r=row-1;c<8 && r>=0;c++,r--)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1 && row-r>1)
				{
					for (i=col+1,j=row-1;i<c && j>r;i++,j--)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Right
		for (c=col+1;c<8;c++)
		{
			v=(pDoc->m_MainTable).GetTable(c,row);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1)
				{
					for (i=col+1;i<c;i++)
					{
						(pDoc->m_MainTable).SetTable(i,row,v);
						point=GetPosition(i,row);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Right-Bottom
		for (c=col+1,r=row+1;c<8 && r<8;c++,r++)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1 && r-row>1)
				{
					for (i=col+1,j=row+1;i<c && j<r;i++,j++)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Bottom
		for (r=row+1;r<8;r++)
		{
			v=(pDoc->m_MainTable).GetTable(col,r);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && r-row>1)
				{
					for (i=row+1;i<r;i++)
					{
						(pDoc->m_MainTable).SetTable(col,i,v);
						point=GetPosition(col,i);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Left-Bottom
		for (c=col-1,r=row+1;c>=0 && r<8;c--,r++)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && r-row>1 && col-c>1)
				{
					for (i=col-1,j=row+1;i>c && j<r;i--,j++)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// No Space!!!
		return FALSE;
	}

	// Black
	if (value==T_BLACK)
	{
		// To Left
		for (c=col-1;c>=0;c--)
		{
			v=(pDoc->m_MainTable).GetTable(c,row);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && col-c>1)
				{
					for (i=col-1;i>c;i--)
					{
						(pDoc->m_MainTable).SetTable(i,row,v);
						point=GetPosition(i,row);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Left-Top
		for (c=col-1,r=row-1;c>=0 && r>=0;c--,r--)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && col-c>1 && row-r>1)
				{
					for (i=col-1,j=row-1;i>c && j>r;i--,j--)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Top
		for (r=row-1;r>=0;r--)
		{
			v=(pDoc->m_MainTable).GetTable(col,r);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && row-r>1)
				{
					for (i=row-1;i>r;i--)
					{
						(pDoc->m_MainTable).SetTable(col,i,v);
						point=GetPosition(col,i);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Right-Top
		for (c=col+1,r=row-1;c<8 && r>=0;c++,r--)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1 && row-r>1)
				{
					for (i=col+1,j=row-1;i<c && j>r;i++,j--)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);				}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Right
		for (c=col+1;c<8;c++)
		{
			v=(pDoc->m_MainTable).GetTable(c,row);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1)
				{
					for (i=col+1;i<c;i++)
					{
						(pDoc->m_MainTable).SetTable(i,row,v);
						point=GetPosition(i,row);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Right-Bottom
		for (c=col+1,r=row+1;c<8 && r<8;c++,r++)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1 && r-row>1)
				{
					for (i=col+1,j=row+1;i<c && j<r;i++,j++)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Bottom
		for (r=row+1;r<8;r++)
		{
			v=(pDoc->m_MainTable).GetTable(col,r);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && r-row>1)
				{
					for (i=row+1;i<r;i++)
					{
						(pDoc->m_MainTable).SetTable(col,i,v);
						point=GetPosition(col,i);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// To Left-Bottom
		for (c=col-1,r=row+1;c>=0 && r<8;c--,r++)
		{
			v=(pDoc->m_MainTable).GetTable(c,r);
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && r-row>1 && col-c>1)
				{
					for (i=col-1,j=row+1;i>c && j<r;i--,j++)
					{
						(pDoc->m_MainTable).SetTable(i,j,v);
						point=GetPosition(i,j);
						BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
					}
					break;
				}
				else
				{
					break;
				}
			}
		}
		// No Space!!!
		return FALSE;
	}
	return TRUE;
}

CPoint COthelloView::GetPosition(int col, int row)
{
	CPoint res;
	res.x=m_InitPosition.x+col*35;
	res.y=m_InitPosition.y+row*35;

	return res;
}

void COthelloView::OnGameNew() 
{
	CPaintDC dc(this); // device context for painting
	
	int i,j;
	CPoint point;
	COthelloDoc *pDoc=GetDocument();
	for (i=0;i<64;i++)
	{
		(pDoc->m_MainTable).SetTable(i,T_NONE);
	}
	(pDoc->m_MainTable).SetTable(27,T_BLACK);
	(pDoc->m_MainTable).SetTable(28,T_WHITE);
	(pDoc->m_MainTable).SetTable(35,T_WHITE);
	(pDoc->m_MainTable).SetTable(36,T_BLACK);

	BiltBitmap(0,0,380,400,m_hBackGround);
	
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			if ((pDoc->m_MainTable).GetTable(j,i)==T_BLACK)
			{
				point=GetPosition(j,i);
				BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hBlack);
			}
			if ((pDoc->m_MainTable).GetTable(j,i)==T_WHITE)
			{
				point=GetPosition(j,i);
				BiltBitmap(point.x,point.y,point.x+33,point.y+33,m_hWhite);
			}
		}
		DispDown(pDoc,&dc);
// TODO: Add your command handler code here
	
}

void COthelloView::DispDown(COthelloDoc *pDoc, CDC *pDC)
{
	int i,j;
	CPoint point;
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			if ((pDoc->m_MainTable).GetTable(j,i)>0) continue;
			if ((pDoc->m_MainTable).IsDown(j,i,m_CurPlay))
			{
				point=GetPosition(j,i);
				BiltBitmap(point.x,point.y,point.x+34,point.y+34,m_hMaskerX);
			}
			else
			{
				point=GetPosition(j,i);
				pDC->FillSolidRect(point.x,point.y,34,34,m_NormalColor);
			}

		}
}

void COthelloView::BiltBitmap(CDC &dc, CRect &rc, HBITMAP hbm)
{
	CDC dcMem;
	HBITMAP hbmpOld;
	dcMem.CreateCompatibleDC(&dc);
	hbmpOld=(HBITMAP)::SelectObject(dcMem,hbm);

	dc.BitBlt(rc.left,rc.top,rc.right,rc.bottom,&dcMem,0,0,SRCCOPY);
	::SelectObject(dcMem,hbmpOld);
}

void COthelloView::BiltBitmap(CDC &dc, int x1, int y1, int x2, int y2, HBITMAP hbm)
{
	CDC dcMem;
	HBITMAP hbmpOld;
	dcMem.CreateCompatibleDC(&dc);
	hbmpOld=(HBITMAP)::SelectObject(dcMem,hbm);

	dc.BitBlt(x1,y1,x2,y2,&dcMem,0,0,SRCCOPY);
	::SelectObject(dcMem,hbmpOld);
}
