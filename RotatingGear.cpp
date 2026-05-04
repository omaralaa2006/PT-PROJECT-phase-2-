#include "RotatingGear.h"
#include"Player.h"



RotatingGear::RotatingGear(const CellPosition & gearposition,bool clockwise) : GameObject(gearposition)
{
	isClockWise = clockwise;
}

void RotatingGear::Draw(Output* pOut) const
{
	pOut->DrawRotatingGear(position, isClockWise);
}

void RotatingGear::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	
	if (isClockWise == true)
	{
		pOut->PrintMessage("Rotating clockwise... Click to continue");
	}
	else
	{
		pOut->PrintMessage("Rotating anti-clockwise... Click to continue");
	}

	
	int x, y;
	pIn->GetPointClicked(x, y);

	
	pPlayer->Rotate(isClockWise);

	
	pGrid->UpdateInterface(pState);

	
	pOut->ClearStatusBar();

	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message and change the message according to direction of rotation "You have reached a rotating gear, you will rotate (clockwise/ anti-clockwise) Click to continue ..." and wait mouse click
	//2- Apply the roating gear's effect by rotating the player according to the direction
}
bool RotatingGear::GetisClockWise() const
{
	return isClockWise;
}
GameObject* RotatingGear::Clone() const
{
	return new RotatingGear(*this);
}
void RotatingGear::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << " ";
	OutFile << (isClockWise ? 1 : 0) << endl;
}

void RotatingGear::Load(ifstream& Infile)
{
	int cellNum;
	int dir;
	Infile >> cellNum >> dir;
	this->position = CellPosition::GetCellPositionFromNum(cellNum);
	this->isClockWise = (dir == 1);
}
ActionType RotatingGear::GetType() const
{
	return ADD_ROTATINGGEAR;
}
RotatingGear::~RotatingGear()
{
}
