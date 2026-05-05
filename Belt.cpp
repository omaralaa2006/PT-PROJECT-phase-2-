#include "Belt.h"


Belt::Belt(const CellPosition & startCellPos, const CellPosition & endCellPos) : GameObject(startCellPos)
{
	this->endCellPos = endCellPos;

	///TODO: Do the needed validation
}
void Belt::Draw(Output* pOut) const
{
	pOut->DrawBelt(position, endCellPos);
}

void Belt::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{


	//TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "You have reached a belt. Click to continue ..." and wait mouse click

	// 2- Apply the belt's effect by moving the player to the endCellPos
	//    Review the "pGrid" functions and decide which function can be used for that
	
	// 1- Get Output and Input pointers to interact with the user
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	// 2- Print a message and wait for a mouse click to keep the user informed
	pOut->PrintMessage("You have reached a belt. Click to continue ...");
	int x, y;
	pIn->GetPointClicked(x, y);

	// 3- Move the player to the endCellPos using UpdatePlayerCell
	// This function handles removing the player from the current cell and placing them in the new one
	pGrid->UpdatePlayerCell(pPlayer, endCellPos);

	// 4- Clear the status bar
	pOut->ClearStatusBar();

}
CellPosition Belt::GetEndPosition() const
{
	return endCellPos;
}
GameObject* Belt::Clone() const
{
	return new Belt(*this);
}

void Belt::Save(ofstream& OutFile, ActionType type) {
	if (type == ADD_BELT) {
		// Calculate length (difference in cells)
		int lengthV = endCellPos.VCell() - position.VCell();
		int lengthH = endCellPos.HCell() - position.HCell();

		// Save: StartCellNum, LengthV, LengthH
		OutFile << position.GetCellNum() << " " << lengthV << " " << lengthH << endl;
	}
}
void Belt::Load(ifstream& InFile) {
	int startCellNum, lengthV, lengthH;
	InFile >> startCellNum >> lengthV >> lengthH;

	this->position = CellPosition(startCellNum);

	// Reconstruct endCellPos based on saved lengths
	this->endCellPos = CellPosition(position.VCell() + lengthV, position.HCell() + lengthH);
}
//void Belt::Load(ifstream& Infile)
//{
	//int start,end;
	//Infile >> start >> end;;
	//this->position = CellPosition(start);
	//this->endCellPos = CellPosition(end);
//}
GameObject* Belt::GetCopy(CellPosition pos) const {
	// 1. Calculate current length/displacement
	int dV = this->endCellPos.VCell() - this->position.VCell();
	int dH = this->endCellPos.HCell() - this->position.HCell();

	// 2. Create new end position relative to the NEW 'pos'
	CellPosition newEnd(pos.VCell() + dV, pos.HCell() + dH);

	// 3. Return the new Belt
	return new Belt(pos, newEnd);
}
ActionType Belt::GetType() const
{
	return ADD_BELT;
}
Belt::~Belt()
{
}
