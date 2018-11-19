#include "Cell.h"



Cell::Cell() : _state(STATE::DEAD)
{
}


Cell::~Cell()
{
}

void Cell::Init(STATE state)
{
	_state = state;
}

void Cell::SetNextState(STATE state)
{
	_nextState = state;
}

void Cell::GoToNextState()
{
	_state = _nextState;
}
