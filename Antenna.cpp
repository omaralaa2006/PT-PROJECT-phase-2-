#include "Antenna.h"
#include "GameState.h"
#include "Player.h"    


Antenna::Antenna(const CellPosition & antennaPosition):GameObject(antennaPosition)
{
}

void Antenna::Draw(Output * pOut) const
{
	pOut->DrawAntenna(position);
}

void Antenna::Apply(Grid* pGrid, GameState* pState, Player* pPlayer)
{

 
	


	///TODO: Implement this function as mentioned in the guideline steps (numbered below) below


	// == Here are some guideline steps (numbered below) to implement this function ==

	// 1- Print a message "the antenna will decide the turn of players. Click to continue ..." and wait mouse click

	// 2- Determine turn order based on each player's distance from the antenna.
	//    Hint: distance = |dV| + |dH|
	//    The player closest to the antenna plays first. Ties are broken by player number.
	//    Use pState to update the turn order accordingly.
	// 3- Print a message indicating which player will play first

	
		// MASHY delw2ty gebna el tools ely interact m3 el user mashy ehna mehtagen hagten men pGrid 
	// el output aalshan tekteb el message fe Status Bar ely taht
	// el input aalshan ye2of w yestany el user yeclick 3la mouse
		Output* pOut = pGrid->GetOutput();
		Input* pIn = pGrid->GetInput();

		// hena 3amlna print ll message aady 
		pOut->PrintMessage("The antenna will decide the turn of players. Click to continue ...");

		
		int x, y;
		pIn->GetPointClicked(x, y);

		//  Get pointers for both players from the GameState to calculate their positions
		//  we have 2 players: Player 1 (index 0) and Player 2 (index 1)
		Player* p1 = pState->GetPlayerPointer(0);
		Player* p2 = pState->GetPlayerPointer(1);

		//  Get the Antenna's current coordinates (V and H)
		int antV = position.VCell();
		int antH = position.HCell();

		//  Calculate Manhattan Distance for Player 1: |dV| + |dH|
		int distP1 = abs(p1->GetCell()->GetCellPosition().VCell() - antV) +
			abs(p1->GetCell()->GetCellPosition().HCell() - antH);

		//  Calculate Manhattan Distance for Player 2: |dV| + |dH|[cite: 1]
		int distP2 = abs(p2->GetCell()->GetCellPosition().VCell() - antV) +
			abs(p2->GetCell()->GetCellPosition().HCell() - antH);

		int firstPlayerNum;

		//  Comparison logic to decide the turn order[cite: 1]
		if (distP1 < distP2) {
			// Player 1 is closer[cite: 1]
			firstPlayerNum = 0;
		}
		else if (distP2 < distP1) {
			// Player 2 is closer[cite: 1]
			firstPlayerNum = 1;
		}
		else {
			// If there is a tie, player number breaks it (Player 1 has priority)[cite: 1]
			firstPlayerNum = 0;
		}

		//  Update the current turn in GameState so the system knows who starts the round[cite: 2]
		pState->SetCurrentPlayer(firstPlayerNum);

		//  Inform the users about the decision via the status bar[cite: 1]
		string finalMsg = "Player " + to_string(firstPlayerNum + 1) + " will play first! Click to start.";
		pOut->PrintMessage(finalMsg);
	}

void Antenna::Save(ofstream& OutFile, ActionType type) {
	if (type == ADD_ANTENNA) {
		OutFile << position.GetCellNum() <<  endl;
	}
}

void Antenna::Load(ifstream& Infile)
{
	int cellNum;
	Infile >> cellNum;
	position = CellPosition::GetCellPositionFromNum(cellNum);
}

GameObject* Antenna::Clone() const
{
	return new Antenna(*this);
}

ActionType Antenna::GetType() const
{
	return ADD_ANTENNA;
}


Antenna::~Antenna()
{
}

