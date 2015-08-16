// Table.h: interface for the CTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLE_H__63E4909F_8D21_4D97_B90C_B862320215E1__INCLUDED_)
#define AFX_TABLE_H__63E4909F_8D21_4D97_B90C_B862320215E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTable
{
private:
	BYTE m_Table[64];

public:
	int CountTable(int col,int row,BYTE value);
	BOOL HaveDown(BYTE value);
	BOOL DrawTable(int col,int row,BYTE value);
	BOOL IsDown(int col,int row,BYTE value);
	BYTE GetTable(int pos)	{return *(m_Table+pos);}
	BYTE GetTable(int col,int row)	{return *(m_Table+(row*8+col));}
	void SetTable(int col,int row,BYTE value)	{*(m_Table+(row*8)+col)=value;}
	void SetTable(int pos,BYTE value)	{*(m_Table+pos)=value;}
	CTable();
	virtual ~CTable();

};

#endif // !defined(AFX_TABLE_H__63E4909F_8D21_4D97_B90C_B862320215E1__INCLUDED_)
