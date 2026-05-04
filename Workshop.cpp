#include "Workshop.h"
#include"Player.h"


Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
	Output* pOut = pGrid->GetOutput();
	Input* pIn = pGrid->GetInput();

	
	pOut->PrintMessage("Welcome to the Workshop! Your health will be restored. Click to continue...");
	int x, y;
	pIn->GetPointClicked(x, y);

	
	int maxHealth = 10;
	pPlayer->SetHealth(maxHealth);
	///TODO: Implement this function
	// Apply the workshop's effect on the player
	// [OPTIONAL BONUS] Consumables can be given to the player here
}
GameObject* Workshop::Clone() const
{
	return new Workshop(*this);
}
void Workshop::Save(ofstream& OutFile)
{
	OutFile << position.GetCellNum() << endl;
}

void Workshop::Load(ifstream& Infile)
{
	int cellNum;
	Infile >> cellNum;
	position = CellPosition::GetCellPositionFromNum(cellNum);
}
ActionType Workshop::GetType() const
{
	return ADD_WORKSHOP;
}
Workshop::~Workshop()
{
}
