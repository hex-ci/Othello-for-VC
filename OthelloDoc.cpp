// OthelloDoc.cpp : implementation of the COthelloDoc class
//

#include "stdafx.h"
#include "Othello.h"

#include "Table.h"

#include "OthelloDoc.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COthelloDoc

IMPLEMENT_DYNCREATE(COthelloDoc, CDocument)

BEGIN_MESSAGE_MAP(COthelloDoc, CDocument)
	//{{AFX_MSG_MAP(COthelloDoc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COthelloDoc construction/destruction

COthelloDoc::COthelloDoc()
{
	// TODO: add one-time construction code here

}

COthelloDoc::~COthelloDoc()
{
}

BOOL COthelloDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_MainTable.SetTable(27,T_BLACK);
	m_MainTable.SetTable(28,T_WHITE);
	m_MainTable.SetTable(35,T_WHITE);
	m_MainTable.SetTable(36,T_BLACK);
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}

/*int ComDown(CTable &table,int who,int depth)
{

}
*/

/////////////////////////////////////////////////////////////////////////////
// COthelloDoc serialization

void COthelloDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COthelloDoc diagnostics

#ifdef _DEBUG
void COthelloDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COthelloDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

int COthelloDoc::ComDown(CTable table, BYTE who, BYTE depth)
{
	CTable backup=table;
	if (depth==0) return 0;
	register char i,j;
	int CanDown=0,Num=0;
	tagGoal goal[64],MaxGoal;
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			if (table.IsDown(j,i,who))
			{
				goal[CanDown].Set(j,i,0);
				CanDown++;
			}
		}
	if (CanDown==0) return -5;
	for (i=0;i<CanDown;i++)
	{
		Num=table.CountTable(goal[i].point.x,goal[i].point.y,who);
		goal[i].goal=Num-ComDown(table,who^3,depth-1);
		goal[i].goal+=Optimize(table,who,goal[i]);
		if ((goal[i].point.x==0 && goal[i].point.y==0) ||
				(goal[i].point.x==7 && goal[i].point.y==0) ||
				(goal[i].point.x==0 && goal[i].point.y==7) ||
				(goal[i].point.x==7 && goal[i].point.y==7))
		{
			goal[i].goal+=25;
		}
		else
		{
			if (goal[i].point.x==0 || goal[i].point.y==0 || goal[i].point.x==7 || goal[i].point.y==7)
				goal[i].goal+=5;
			else
			{
				if ((goal[i].point.x==1 && goal[i].point.y==1) ||
						(goal[i].point.x==6 && goal[i].point.y==1) ||
						(goal[i].point.x==1 && goal[i].point.y==6) ||
						(goal[i].point.x==6 && goal[i].point.y==6))
				{
					goal[i].goal-=12;
				}
				else
					if (goal[i].point.x==1 || goal[i].point.y==1 || goal[i].point.x==6 || goal[i].point.y==6)
						goal[i].goal-=10;
			}
		}
		table=backup;
	}
	MaxGoal=goal[0];
	for (i=1;i<CanDown;i++)
	{
		if (MaxGoal.goal<goal[i].goal) MaxGoal=goal[i];
	}
	if (depth==T_DEPTH)
	{
		MaxPoint.x=MaxGoal.point.x;
		MaxPoint.y=MaxGoal.point.y;
	}
	if (CanDown<2)
		MaxGoal.goal-=15;
	else
		MaxGoal.goal+=CanDown;
	return MaxGoal.goal;

}

CPoint COthelloDoc::TryIt(BYTE who, int depth)
{
	ComDown(m_MainTable,who,depth);
	return MaxPoint;
}

void COthelloDoc::GameOver()
{
	int Black=0,White=0,i;
	CString str;
	char temp1[10],temp2[10];
	for (i=0;i<64;i++)
	{
		if (m_MainTable.GetTable(i)==T_BLACK) Black++;
		if (m_MainTable.GetTable(i)==T_WHITE) White++;
	}
	if (Black>White)
	{
		str="黑方胜利！\n";
		_itoa_s(Black,temp1,10);
		_itoa_s(White,temp2,10);
		str+="黑方：";
		str+=temp1;
		str+="\n白方：";
		str+=temp2;
	}
	if (White>Black)
	{
		str="白方胜利！\n";
		_itoa_s(White,temp1,10);
		_itoa_s(Black,temp2,10);
		str+="白方：";
		str+=temp1;
		str+="\n黑方：";
		str+=temp2;
	}
	if (Black==White)
	{
		str="平局！！\n";
		_itoa_s(Black,temp1,10);
		_itoa_s(White,temp2,10);
		str+="黑方：";
		str+=temp1;
		str+="\n白方：";
		str+=temp2;
	}
	MessageBeep(MB_ICONINFORMATION);
	AfxMessageBox(str);
	//AfxMessageBox(str,"游戏结束",MB_ICONINFORMATION|MB_OK);
}

int COthelloDoc::Optimize(CTable &table, BYTE who, tagGoal &goal)
{
	int res=0;
	CPoint point(goal.point.x,goal.point.y);

	// Left
	if (point.x==0 && point.y>1 && point.y<6)
	{
		if (table.GetTable(point.x,point.y-1)==T_NONE && table.GetTable(point.x,point.y-2)==who ||
				table.GetTable(point.x,point.y+1)==T_NONE && table.GetTable(point.x,point.y+2)==who)
		{
			res=-15;
		}
	}

	// Top
	if (point.y==0 && point.x>1 && point.x<6)
	{
		if (table.GetTable(point.x-1,point.y)==T_NONE && table.GetTable(point.x-2,point.y)==who ||
				table.GetTable(point.x+1,point.y)==T_NONE && table.GetTable(point.x+2,point.y)==who)
		{
			res=-15;
		}
	}

	// Right
	if (point.x==7 && point.y>1 && point.y<6)
	{
		if (table.GetTable(point.x,point.y-1)==T_NONE && table.GetTable(point.x,point.y-2)==who ||
				table.GetTable(point.x,point.y+1)==T_NONE && table.GetTable(point.x,point.y+2)==who)
		{
			res=-15;
		}
	}

	// Bottom
	if (point.y==7 && point.x>1 && point.x<6)
	{
		if (table.GetTable(point.x-1,point.y)==T_NONE && table.GetTable(point.x-2,point.y)==who ||
				table.GetTable(point.x+1,point.y)==T_NONE && table.GetTable(point.x+2,point.y)==who)
		{
			res=-15;
		}
	}

	return res;
}
