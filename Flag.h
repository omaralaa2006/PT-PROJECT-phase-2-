#pragma once
#include "GameObject.h"
class Flag :public GameObject
{
public:
	Flag(const CellPosition & flagposition); // A constructor for initialization
	virtual void Draw(Output* pOut) const; // Draws a flag in a selected cell

	virtual GameObject* Clone() const;
	virtual void Apply(Grid* pGrid, GameState* pState, Player* pPlayer); // Applies the effect of the flag
	virtual void Save(ofstream& OutFile, ActionType type);
	virtual void Load(ifstream& Infile);
	virtual ActionType GetType() const;
	virtual ~Flag(); // Virtual destructor
};