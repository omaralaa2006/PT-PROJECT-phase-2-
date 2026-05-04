#include "Flag.h"
Flag::Flag(const CellPosition & flagposition) : GameObject(flagposition)
{

}

void Flag::Draw(Output* pOut) const
{
	pOut->DrawFlag(position);
}

void Flag::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	
	pOut->PrintMessage("You have reached a flag. CONGRATULATIONS! Click to continue ...");
	int x, y;
	pIn->GetPointClicked(x, y);

	
	pGrid->SetEndGame(true);

	
	pOut->ClearStatusBar();
	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below
	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a flag. Click to continue ..." and wait mouse click

	// 2- Apply the flag's effect by ending the game
	//    Review the "pGrid" functions and decide which function can be used for that
}
GameObject* Flag::Clone() const
{
	return new Flag(*this);
}

void Flag::Save(ofstream& OutFile, ActionType type) {
	if (type == SET_FLAG_CELL) {
		OutFile << position.GetCellNum() << endl;
	}
}

void Flag::Load(ifstream& Infile)
{
	int cellNum;
	Infile >> cellNum;
	position = CellPosition::GetCellPositionFromNum(cellNum);
}
ActionType Flag::GetType() const
{
	return SET_FLAG_CELL;
}
Flag::~Flag()
{

}