#pragma once
enum class State {ALIVE, DEAD};

class Cell
{
public:
	Cell();
	~Cell();

	void Init(State State);

	void SetNextState(State State);
	void GoToNextState();

	//Getters
	State getState() { return _State; }

private:
	State _State;
	State _nextState;
};

