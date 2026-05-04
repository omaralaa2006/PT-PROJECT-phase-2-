#include "Grid.h"

#include "Cell.h"
#include "GameObject.h"
#include "Belt.h"
#include "Player.h"
#include "GameState.h"

Grid::Grid(Input* pIn, Output* pOut) : pIn(pIn), pOut(pOut)
{
	for (int i = NumVerticalCells - 1; i >= 0; i--)
		for (int j = 0; j < NumHorizontalCells; j++)
			CellList[i][j] = new Cell(i, j);

	Clipboard = NULL;
}


// ========== Board Operations ==========


bool Grid::AddObjectToCell(GameObject* pNewObject)
{
	CellPosition pos = pNewObject->GetPosition();
	if (pos.IsValidCell())
	{
		GameObject* pPrevObject = CellList[pos.VCell()][pos.HCell()]->GetGameObject();
		if (pPrevObject)
			return false;

		CellList[pos.VCell()][pos.HCell()]->SetGameObject(pNewObject);
		return true;
	}
	return false;
}
// ana salma zwedt hagat hna
bool Grid::RemoveObjectFromCell(const CellPosition& pos)
{
	if (pos.IsValidCell())
	{
		// Note: deallocate the object here before NULLing if ownership requires it
		CellList[pos.VCell()][pos.HCell()]->SetGameObject(NULL);
		return true;
	}
	return false;
}

void Grid::UpdatePlayerCell(Player* player, const CellPosition& newPosition)
{
	player->ClearDrawing(pOut);
	Cell* newCell = CellList[newPosition.VCell()][newPosition.HCell()];
	player->SetCell(newCell);
	player->Draw(pOut);
}

Belt* Grid::GetNextBelt(const CellPosition& position)
{
	int startH = position.HCell();
	for (int i = position.VCell(); i >= 0; i--)
	{
		for (int j = startH; j < NumHorizontalCells; j++)
		{
			///TODO: Check if CellList[i][j] has a belt, if yes return it
		}
		startH = 0;
	}
	return NULL;
}


// ========== Setters / Getters ==========


Input* Grid::GetInput() const { return pIn; }
Output* Grid::GetOutput() const { return pOut; }

void Grid::SetClipboard(GameObject* gameObject) { Clipboard = gameObject; }
GameObject* Grid::GetClipboard() const { return Clipboard; }

Cell* Grid::GetStartCell() const
{
	return CellList[NumVerticalCells - 1][0];
}

Cell* Grid::GetCell(const CellPosition& pos) const
{
	if (pos.IsValidCell())
	{
		return CellList[pos.VCell()][pos.HCell()];
	}

	return NULL;
}

// ========== User Interface ==========


void Grid::UpdateInterface(const GameState* pState) const
{
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				CellList[i][j]->DrawCellOrWaterPitOrDangerZone(pOut);

		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				CellList[i][j]->DrawGameObject(pOut);

		pState->DrawAllPlayers(pOut);
	}
	else // Play mode
	{
		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				CellList[i][j]->DrawCellOrWaterPitOrDangerZone(pOut);

		for (int i = NumVerticalCells - 1; i >= 0; i--)
			for (int j = 0; j < NumHorizontalCells; j++)
				CellList[i][j]->DrawGameObject(pOut);

		pState->DrawAllPlayers(pOut);

		string playersInfo = "";
		pState->AppendPlayersInfo(playersInfo);
		pOut->PrintPlayersInfo(playersInfo);

		Player* pPlayer = pState->GetCurrentPlayer();

		Command saved[MaxSavedCommands];
		int savedCount = pPlayer->GetSavedCommandCount();

		for (int i = 0; i < MaxSavedCommands; i++)
		{
			if (i < savedCount)
				saved[i] = pPlayer->GetSavedCommand(i);
			else
				saved[i] = NO_COMMAND;
		}

		int availableCount = pState->GetAvailableCommandsCount();

		Command available[MaxAvailableCommands];

		for (int i = 0; i < availableCount; i++)
			available[i] = pState->GetAvailableCommand(i);

		pOut->CreateCommandsBar(saved, MaxSavedCommands, available, availableCount);
	}
}

void Grid::PrintErrorMessage(string msg)
{
	pOut->PrintMessage(msg);
	int x, y;
	pIn->GetPointClicked(x, y);
	pOut->ClearStatusBar();
}

void Grid::SaveAll(ofstream& OutFile, ActionType type)
{
	int count = 0;
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			GameObject* pobj = CellList[i][j]->GetGameObject();
			if (pobj != NULL && pobj->GetType() == type)
			{
				count++;
			}
		}
	}

	OutFile << count << endl;

	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			GameObject* pobj = CellList[i][j]->GetGameObject();
			if (pobj != NULL && pobj->GetType() == type)
			{
				pobj->Save(OutFile);
			}
		}
	}
}

void Grid::ClearGrid()
{
	for (int i = 0; i < NumVerticalCells; i++)
	{
		for (int j = 0; j < NumHorizontalCells; j++)
		{
			RemoveObjectFromCell(CellPosition(i, j));
		}
	}
}

void Grid::SetEndGame(bool end)
{
	endGame = end;
}

bool Grid::GetEndGame() const
{
	return endGame;
}

Grid::~Grid()
{
	delete pIn;
	delete pOut;

	for (int i = NumVerticalCells - 1; i >= 0; i--)
		for (int j = 0; j < NumHorizontalCells; j++)
			delete CellList[i][j];
}