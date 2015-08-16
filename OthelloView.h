// OthelloView.h : interface of the COthelloView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTHELLOVIEW_H__DE215BAD_F465_11D5_8C06_40644EC11002__INCLUDED_)
#define AFX_OTHELLOVIEW_H__DE215BAD_F465_11D5_8C06_40644EC11002__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COthelloView : public CView
{
private:
	void BiltBitmap(CDC &dc, int x1, int y1, int x2, int y2, HBITMAP hbm);
	void BiltBitmap(CDC &dc,CRect &rc,HBITMAP hbm);
	void DispDown(COthelloDoc *pDoc,CDC *pDC);
	unsigned long m_NormalColor;
	unsigned long m_SelectColor;
	unsigned long m_DownColor;
	int m_Current;
	int m_CurX,m_CurY;
	int m_CurCol,m_CurRow;
	CPoint m_InitPosition;
	BYTE m_CurPlay;

	CPoint GetPosition(int col,int row);

protected: // create from serialization only
	COthelloView();

	HBITMAP m_hBackGround;
	HBITMAP m_hBlack;
	HBITMAP m_hWhite;
	HBITMAP m_hMaskerX;
	HCURSOR m_hcurBlack;
	HCURSOR m_hcurWhite;
	HCURSOR m_hcurDefault;
	CAnimateCtrl m_ctlAvi;

	void BiltBitmap(CRect &rc,HBITMAP hbm);
	void BiltBitmap(int x1,int y1,int x2,int y2,HBITMAP hbm);
	DECLARE_DYNCREATE(COthelloView)

// Attributes
public:
	COthelloDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COthelloView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL DrawTable(int col,int row,BYTE value);
	virtual ~COthelloView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COthelloView)
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnGameNew();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OthelloView.cpp
inline COthelloDoc* COthelloView::GetDocument()
   { return (COthelloDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHELLOVIEW_H__DE215BAD_F465_11D5_8C06_40644EC11002__INCLUDED_)
