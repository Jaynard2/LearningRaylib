#include "Cell.h"



Cell::Cell() : _State(State::DEAD)
{
}


Cell::~Cell()
{
}

void Cell::Init(State State)
{
	_State = State;
}

void Cell::SetNextState(State State)
{
	_nextState = State;
}

void Cell::GoToNextState()
{
	_State = _nextState;
}
