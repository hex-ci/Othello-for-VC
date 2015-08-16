// Table.cpp: implementation of the CTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Othello.h"
#include "Table.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTable::CTable()
{
	register int i;
	for (i=0;i<64;i++)
	{
		*(m_Table+i)=0;
	}
}

CTable::~CTable()
{

}

BOOL CTable::IsDown(int col, int row, BYTE value)
{
	int c,r;
	BYTE v;
	if (GetTable(col,row)!=T_NONE) return FALSE;
	if (value==T_WHITE)
	{
		// To Left
		for (c=col-1;c>=0;c--)
		{
			v=*(m_Table+(row*8+c));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && col-c>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && col-c>1 && row-r>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+col));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && row-r>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1 && row-r>1)
				{
					return TRUE;
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
			v=*(m_Table+(row*8+c));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1 && r-row>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+col));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && r-row>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				continue;
			}
			else
			{
				if (v==T_WHITE && r-row>1 && col-c>1)
				{
					return TRUE;
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
			v=*(m_Table+(row*8+c));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && col-c>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && col-c>1 && row-r>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+col));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && row-r>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1 && row-r>1)
				{
					return TRUE;
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
			v=*(m_Table+(row*8+c));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1 && r-row>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+col));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && r-row>1)
				{
					return TRUE;
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
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				continue;
			}
			else
			{
				if (v==T_BLACK && r-row>1 && col-c>1)
				{
					return TRUE;
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
	return FALSE;
}

BOOL CTable::HaveDown(BYTE value)
{
	int i,j;
	for (i=0;i<8;i++)
		for (j=0;j<8;j++)
		{
			if (IsDown(j,i,value))
			{
				return TRUE;
			}
		}
	return FALSE;
}

int CTable::CountTable(int col, int row, BYTE value)
{
	*(m_Table+row*8+col)=value;
	int i,j,c,r,temp=0,Number=0;
	BYTE v;
	if (value==T_WHITE)
	{
		// To Left
		for (c=col-1;c>=0;c--)
		{
			v=*(m_Table+(row*8+c));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && col-c>1)
				{
					Number+=temp;
					for (i=col-1;i>c;i--)	SetTable(i,row,T_WHITE);
				}
				break;
			}
		}
		// To Left-Top
		temp=0;
		for (c=col-1,r=row-1;c>=0 && r>=0;c--,r--)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && col-c>1 && row-r>1)
				{
					Number+=temp;
					for (i=col-1,j=row-1;i>c && j>r;i--,j--)	SetTable(i,j,T_WHITE);
				}
				break;
			}
		}
		// To Top
		temp=0;
		for (r=row-1;r>=0;r--)
		{
			v=*(m_Table+(r*8+col));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && row-r>1)
				{
					Number+=temp;
					for (i=row-1;i>r;i--)	SetTable(col,i,T_WHITE);
				}
				break;
			}
		}
		// To Right-Top
		temp=0;
		for (c=col+1,r=row-1;c<8 && r>=0;c++,r--)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1 && row-r>1)
				{
					Number+=temp;
					for (i=col+1,j=row-1;i<c && j>r;i++,j--)	SetTable(i,j,T_WHITE);
				}
				break;
			}
		}
		// To Right
		temp=0;
		for (c=col+1;c<8;c++)
		{
			v=*(m_Table+(row*8+c));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1)
				{
					Number+=temp;
					for (i=col+1;i<c;i++)	SetTable(i,row,T_WHITE);
				}
				break;
			}
		}
		// To Right-Bottom
		temp=0;
		for (c=col+1,r=row+1;c<8 && r<8;c++,r++)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && c-col>1 && r-row>1)
				{
					Number+=temp;
					for (i=col+1,j=row+1;i<c && j<r;i++,j++)	SetTable(i,j,T_WHITE);
				}
				break;
			}
		}
		// To Bottom
		temp=0;
		for (r=row+1;r<8;r++)
		{
			v=*(m_Table+(r*8+col));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && r-row>1)
				{
					Number+=temp;
					for (i=row+1;i<r;i++)	SetTable(col,i,T_WHITE);
				}
				break;
			}
		}
		// To Left-Bottom
		temp=0;
		for (c=col-1,r=row+1;c>=0 && r<8;c--,r++)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_BLACK)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_WHITE && r-row>1 && col-c>1)
				{
					Number+=temp;
					for (i=col-1,j=row+1;i>c && j<r;i--,j++)	SetTable(i,j,T_WHITE);
				}
				break;
			}
		}
		return Number;
	}

	// Black
	if (value==T_BLACK)
	{
		// To Left
		for (c=col-1;c>=0;c--)
		{
			v=*(m_Table+(row*8+c));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && col-c>1)
				{
					Number+=temp;
					for (i=col-1;i>c;i--)	SetTable(i,row,T_BLACK);
				}
				break;
			}
		}
		// To Left-Top
		temp=0;
		for (c=col-1,r=row-1;c>=0 && r>=0;c--,r--)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && col-c>1 && row-r>1)
				{
					Number+=temp;
					for (i=col-1,j=row-1;i>c && j>r;i--,j--)	SetTable(i,j,T_BLACK);
				}
				break;
			}
		}
		// To Top
		temp=0;
		for (r=row-1;r>=0;r--)
		{
			v=*(m_Table+(r*8+col));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && row-r>1)
				{
					Number+=temp;
					for (i=row-1;i>r;i--)	SetTable(col,i,T_BLACK);
				}
				break;
			}
		}
		// To Right-Top
		temp=0;
		for (c=col+1,r=row-1;c<8 && r>=0;c++,r--)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1 && row-r>1)
				{
					Number+=temp;
					for (i=col+1,j=row-1;i<c && j>r;i++,j--)	SetTable(i,j,T_BLACK);
				}
				break;
			}
		}
		// To Right
		temp=0;
		for (c=col+1;c<8;c++)
		{
			v=*(m_Table+(row*8+c));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1)
				{
					Number+=temp;
					for (i=col+1;i<c;i++)	SetTable(i,row,T_BLACK);
				}
				break;
			}
		}
		// To Right-Bottom
		temp=0;
		for (c=col+1,r=row+1;c<8 && r<8;c++,r++)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && c-col>1 && r-row>1)
				{
					Number+=temp;
					for (i=col+1,j=row+1;i<c && j<r;i++,j++)	SetTable(i,j,T_BLACK);
				}
				break;
			}
		}
		// To Bottom
		temp=0;
		for (r=row+1;r<8;r++)
		{
			v=*(m_Table+(r*8+col));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && r-row>1)
				{
					Number+=temp;
					for (i=row+1;i<r;i++)	SetTable(col,i,T_BLACK);
				}
				break;
			}
		}
		// To Left-Bottom
		temp=0;
		for (c=col-1,r=row+1;c>=0 && r<8;c--,r++)
		{
			v=*(m_Table+(r*8+c));
			if (v==T_WHITE)
			{
				temp++;
				continue;
			}
			else
			{
				if (v==T_BLACK && r-row>1 && col-c>1)
				{
					Number+=temp;
					for (i=col-1,j=row+1;i>c && j<r;i--,j++)	SetTable(i,j,T_BLACK);
				}
				break;
			}
		}
	}
	return Number;
}
