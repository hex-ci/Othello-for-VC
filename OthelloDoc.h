// OthelloDoc.h : interface of the COthelloDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OTHELLODOC_H__DE215BAB_F465_11D5_8C06_40644EC11002__INCLUDED_)
#define AFX_OTHELLODOC_H__DE215BAB_F465_11D5_8C06_40644EC11002__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class COthelloDoc : public CDocument
{
protected: // create from serialization only
	COthelloDoc();
	struct tagGoal
	{
		CPoint point;
		int goal;
		void Set(int col,int row,int num)
		{
			point.x=col;
			point.y=row;
			goal=num;
		}
		int GetPos(void)
		{
			return (point.y*8+point.x);
		}
	};
	CPoint MaxPoint;

	DECLARE_DYNCREATE(COthelloDoc)

// Attributes
public:
	CTable m_MainTable;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COthelloDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void GameOver(void);
	CPoint TryIt(BYTE who,int depth);
	virtual ~COthelloDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COthelloDoc)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int Optimize(CTable &table,BYTE who,tagGoal &goal);
	int ComDown(CTable table,BYTE who,BYTE depth);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OTHELLODOC_H__DE215BAB_F465_11D5_8C06_40644EC11002__INCLUDED_)
