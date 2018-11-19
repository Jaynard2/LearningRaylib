#pragma once
enum class STATE {ALIVE, DEAD};

class Cell
{
public:
	Cell();
	~Cell();

	void Init(STATE state);

	void SetNextState(STATE state);
	void GoToNextState();

	//Getters
	STATE getState() { return _state; }

private:
	STATE _state;
	STATE _nextState;
};

