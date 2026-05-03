#include "Workshop.h"



Workshop::Workshop(const CellPosition & workshopPosition):GameObject( workshopPosition)
{

}


void Workshop::Draw(Output * pOut) const
{
	pOut->DrawWorkshop(position);
}

void Workshop::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{
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
