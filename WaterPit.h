#pragma once
#include "GameObject.h"
class WaterPit:public GameObject
{
public:
	WaterPit(const CellPosition & waterPitPosition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a water pit in the cell

	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the water pit
	virtual GameObject* Clone() const;
	virtual void Save(ofstream& OutFile, ActionType type);
	virtual void Load(ifstream& Infile);
	virtual ActionType GetType() const;
	virtual ~WaterPit();
};

