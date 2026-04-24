#pragma once
#include "DEFS.h"

class CellPosition
{
	int vCell;
	int hCell;

public:
	CellPosition();
	CellPosition(int v, int h);
	CellPosition(int cellNum);
	bool SetVCell(int v);
	bool SetHCell(int h);
	int VCell() const;
	int HCell() const;
	bool IsValidCell() const;
	int GetCellNum() const;
	static int GetCellNumFromPosition(const CellPosition& cellPosition);
	static CellPosition GetCellPositionFromNum(int cellNum);
	void AddCellNum(int addedNum, Direction direction);
};