// CELL POSITION

#include "CellPosition.h"
#include "UI_Info.h"

CellPosition::CellPosition()
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;
}

CellPosition::CellPosition(int v, int h)
{
	// (-1) indicating an invalid cell (uninitialized by the user)
	vCell = -1;
	hCell = -1;

	SetVCell(v);
	SetHCell(h);
}

CellPosition::CellPosition(int cellNum)
{
	(*this) = GetCellPositionFromNum(cellNum); // the function call with build a cell position (vCell and hCell)
	// from the passed (cellNum)
	// (*this) = ... --> this will copy the returned (vCell and hCell)
	//                   to the data members (vCell and hCell)
}

bool CellPosition::SetVCell(int v)
{
	{
		if (v >= 0 && v < NumVerticalCells)
		{
			vCell = v;
			return true;  // It returns true, if the parameter is valid and the setting is applied,
		}
		return false;   // Otherwise, return false with no setting
	}

	///TODO: Implement this function as described in the .h file (don't forget the validation)

	 // this line sould be changed with your implementation
}

bool CellPosition::SetHCell(int h)
{

	if (h >= 0 && h < NumHorizontalCells)
	{
		hCell = h;
		return true;  // It returns true, if the parameter is valid and the setting is applied,
	}
	return false;   // Otherwise, return false with no setting

	// this line sould be changed with your implementation
}

int CellPosition::VCell() const
{
	return vCell;
}

int CellPosition::HCell() const
{
	return hCell;
}

bool CellPosition::IsValidCell() const
{
	return(vCell >= 0 && vCell < NumVerticalCells && hCell >= 0 && hCell < NumHorizontalCells);
	///TODO: Implement this function as described in the .h file
}

int CellPosition::GetCellNum() const
{
	return GetCellNumFromPosition(*this); // (*this) is the calling object of GetCellNum
	// which means the object of the current data members (vCell and hCell)
}

int CellPosition::GetCellNumFromPosition(const CellPosition& cellPosition)
{
	// Note:
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)
	// just define an integer that represents cell number and calculate it using the passed cellPosition then return it

	///TODO: Implement this function as described in the .h file
/*/	if (!cellPosition.IsValidCell())
		return -1;

	return ((4 - cellPosition.VCell()) * 11) + cellPosition.HCell() + 1;*/
	// this line should be changed with your implementation
	if (!cellPosition.IsValidCell())
		return -1;
	int v = cellPosition.VCell();
	int h = cellPosition.HCell();

	return (NumVerticalCells - 1 - v) * NumHorizontalCells + h + 1;


}
CellPosition CellPosition::GetCellPositionFromNum(int cellNum)
{
	// this is a static function (do NOT need a calling object so CANNOT use the data members of the calling object, vCell&hCell)

	CellPosition position;

	if (cellNum < 1 || cellNum > NumVerticalCells * NumHorizontalCells)
		return CellPosition(-1, -1);

	int v = NumVerticalCells - 1 - (cellNum - 1) / NumHorizontalCells;
	int h = (cellNum - 1) % NumHorizontalCells;

	position.SetVCell(v);
	position.SetHCell(h);

	return position;


	/// TODO: Implement this function as described in the .h file

	// Note: use the passed cellNum to set the vCell and hCell of the "position" variable declared inside the function
	//       I mean: position.SetVCell(...) and position.SetHCell(...) then return it
}


void CellPosition::AddCellNum(int addedNum, Direction direction)
{
	int cellNum = GetCellNum();

	if (direction == UP)
		cellNum += addedNum * NumHorizontalCells;

	else if (direction == DOWN)
		cellNum -= addedNum * NumHorizontalCells;

	else if (direction == RIGHT)
		cellNum += addedNum;

	else if (direction == LEFT)
		cellNum -= addedNum;

	if (cellNum < 1 || cellNum > NumVerticalCells * NumHorizontalCells)
		return;

	CellPosition newPos = GetCellPositionFromNum(cellNum);

	vCell = newPos.VCell();
	hCell = newPos.HCell();
}