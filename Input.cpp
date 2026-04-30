#include "Input.h"

#include "Output.h"
//======================================================================================//
//								General Functions									    //
//======================================================================================//

Input::Input(window* pW)
{
	pWind = pW; // point to the passed window
}

////////////////////////////////////////////////////////////////////////////////////////// 

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y); // Note: x and y of WaitMouseClick are sent by reference
}

////////////////////////////////////////////////////////////////////////////////////////// 

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	// ESCAPE key is pressed
			return "";	// returns nothing as user has cancelled label
		if (Key == 13)	// ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	// BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

////////////////////////////////////////////////////////////////////////////////////////// 

int Input::GetInteger(Output* pO) const
{


	///TODO: implement the GetInteger function as described in Input.h file 
	//       using function GetString() defined above and function stoi()
	string s = GetSrting(pO);

	if (s == "") return 0;

	bool valid = true;

	for (int i = 0; i < s.size(); i++)
	{
		if (i == 0 && (s[i] == '+' || s[i] == '-'))
			continue;
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
			valid = false;
			break;
		}
	}
	if (valid)
	{
		return stoi(s);
	}
	else
	{
		if (pO)
			pO->PrintMessage("wrong number , try again");
		return GetInteger(pO);
	}
	// Note: stoi(s) converts string s into its equivalent integer (for example, "55" is converted to 55)

	
}

//======================================================================================//
//								Game  Functions									        //
//======================================================================================//

ActionType Input::GetUserAction() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	//  ============ GUI in the Design mode ============
	if (UI.InterfaceMode == MODE_DESIGN)
	{
		// [1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			// Check which Menu item was clicked
			// ==> This assumes that menu items are lined up horizontally <==

			int clickedItemOrder = (x / UI.MenuItemWidth);

			// Divide x coord of the point clicked by the menu item width (integer division)
			// If division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (clickedItemOrder)
			{
			case ITM_SET_FLAG_CELL: return SET_FLAG_CELL;
			case ITM_EXIT: return EXIT;
			case ITM_SWITCH_TO_PLAY_MODE: return TO_PLAY_MODE;

				///TODO: Add cases for the other items of Design Mode
			case ITM_ADD_ANTENNA: return ADD_ANTENNA;
			case ITM_ADD_BELT: return ADD_BELT;
			case ITM_ADD_WATER_PITS: return ADD_WATER_PIT;
			case ITM_ADD_DANGER_ZONE: return ADD_DANGER_ZONE;
			case ITM_ADD_WORK_SHOP: return ADD_WORKSHOP;
			case ITM_ROTATING_GEAR: return ADD_ROTATINGGEAR;
			case ITM_COPY: return COPY_OBJECT;
			case ITM_CUT: return CUT_OBJECT;
			case ITM_PASTE: return PASTE_OBJECT;
			case ITM_DELETE: return DELETE_OBJECT;
			case ITM_SAVE: return SAVE_GRID;
			case ITM_LOAD: return LOAD_GRID;
			default: return EMPTY;	// A click on empty place in toolbar
			}
		}

		// [2] User clicks on the grid area
		if ((y >= UI.ToolBarHeight) && (y < UI.height - UI.StatusBarHeight))
		{
			return GRID_AREA;
		}

		// [3] User clicks on the status bar
		return STATUS;
	}

	// ============ GUI in the Play mode ============
	else
	{
		///TODO:
		// perform checks similar to Design mode checks above for the Play Mode
		// and return the corresponding ActionType
		// Inside GetUserAction() -> else block (Play Mode)
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int clickedItemOrder = x / UI.MenuItemWidth;
			switch (clickedItemOrder)
			{
			case ITM_EXECUTE_COMMANDS: return EXECUTE_COMMANDS;      // 0
			case ITM_SELECT_COMMAND: return SELECT_COMMAND;          // 1
			case ITM_SWITCH_TO_DESIGN_MODE: return TO_DESIGN_MODE;   // 2
			case ITM_ROBOT: return REBOOT_REPAIR;                        // 3
			case ITM_EXIT_Play: return EXIT_Play;                    // 4
			case ITM_MOVE_FORWARD: return MOVE_FORWARD;              // 5
			case ITM_MOVE_BAKWARD: return MOVE_BACKWARD;             // 6
			case ITM_ROTATE_LEFT: return ROTATE_LEFT;                // 7
			case ITM_ROTATE_RIGHT: return ROTATE_RIGHT;              // 8
			default: return EMPTY;
			}
		}
		if ((y >= UI.height - UI.StatusBarHeight - UI.CommandsBarHeight) &&
			(y < UI.height - UI.StatusBarHeight))
		{
			return COMMAND_BAR;
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return GRID_AREA;
		}
		return STATUS;
		//return TO_DESIGN_MODE;	// just for now ==> This should be updated
	}

}

////////////////////////////////////////////////////////////////////////////////////////// 

CellPosition Input::GetCellClicked() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);
	CellPosition cellPos(-1, -1); // Initialize as invalid
	// The grid area is between the ToolBar and the CommandBar/StatusBar
	if (y >= UI.ToolBarHeight && y < (UI.height - UI.StatusBarHeight - (UI.InterfaceMode == MODE_PLAY ? UI.CommandsBarHeight : 0)))
	{
		int vCell = (y - UI.ToolBarHeight) / UI.CellHeight;
		int hCell = x / UI.CellWidth;
		cellPos.SetVCell(vCell);
		cellPos.SetHCell(hCell);
	}
	return cellPos;
}

//////////////////////////////////////////////////////////////////////////////////////////

int Input::GetSelectedCommandIndex() const
{
	int x = -1, y = -1;
	GetPointClicked(x, y);

	if ((y >= UI.height - UI.StatusBarHeight - UI.CommandsBarHeight - UI.AvailableCommandsYOffset) && (y < UI.height - UI.StatusBarHeight))
	{
		if (x < UI.AvailableCommandsXOffset || x > UI.AvailableCommandsXOffset + (UI.CommandItemWidth / 2) * MaxAvailableCommands)
			return -1;

		return (x - UI.AvailableCommandsXOffset) / (UI.CommandItemWidth / 2);;
	}

	return -1;
}

//////////////////////////////////////////////////////////////////////////////////////////