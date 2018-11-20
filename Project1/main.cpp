#include <raylib.h>
#include <string>
#include <iostream>
#include "Cell.h"

constexpr unsigned int width = 3000;
constexpr unsigned int height = 2000;
constexpr unsigned int cellSize = 8;

int main(int argc, char** arg)
{
	InitWindow(width, height, "Game of Life");

	SetTargetFPS(60);

	Cell cells[width / cellSize][height / cellSize];

	for (unsigned int y = 0; y < height / cellSize; ++y)
	{
		for (unsigned int x = 0; x < width / cellSize; ++x)
		{
			int rand = GetRandomValue(0, 1);
			if (rand == 0) cells[x][y].Init(State::ALIVE);
			else cells[x][y].Init(State::DEAD);

		}
	}
	
	while (!WindowShouldClose())
	{
		static unsigned int step = 0;

		unsigned int aliveCellAmount = 0;
		unsigned int deadCellAmount = 0;

		BeginDrawing();
		{

			ClearBackground(BLACK);

			for (unsigned int y = 0; y < height / cellSize; ++y)
			{
				for (unsigned int x = 0; x < width / cellSize; ++x)
				{
					if (cells[x][y].getState() == State::ALIVE)
					{
						DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, WHITE);
						++aliveCellAmount;
					}
					else ++deadCellAmount;
					//Coloring dead cells is not necessary; they are already black
				}
			}

			for (unsigned int x = 0; x < width; x += cellSize)
			{
				DrawLineEx({ (float)x, 0 }, { (float)x, height }, 1, DARKGRAY);
			}

			for (unsigned int y = 0; y < height; y += cellSize)
			{
				DrawLineEx({ 0, (float)y }, { width, (float)y }, 1, DARKGRAY);
			}

			std::string aliveString = "Alive Cells: " + std::to_string(aliveCellAmount);
			std::string deadString = "Dead Cells: " + std::to_string(deadCellAmount);
			std::string stepString = "Step: " + std::to_string(step);

			DrawText(aliveString.c_str(), 0, 0, 40, GREEN);
			DrawText(deadString.c_str(), 0, 40, 40, GREEN);
			DrawText(stepString.c_str(), 0, 80, 40, GREEN);
			DrawText("Any cell with fewer than 2 live neighbors dies", 0, 120, 40, GREEN);
			DrawText("Any cell with 4 or more live neighbors dies", 0, 160, 40, GREEN);
			DrawText("A dead cell with 3 live neighbors becomes a live one", 0, 200, 40, GREEN);
			DrawText("Press R to reset", 0, 240, 40, GREEN);

		}
		EndDrawing();

		for (unsigned int y = 0; y < height / cellSize; ++y)
		{
			for (unsigned int x = 0; x < width / cellSize; ++x)
			{
				int numAlive = 0;

				if (y != 0)
				{
					if (x != 0)
						if (cells[x - 1][y - 1].getState() == State::ALIVE) ++numAlive;

					if (cells[x][y - 1].getState() == State::ALIVE) ++numAlive;

					if (x != (width / cellSize))
						if (cells[x + 1][y - 1].getState() == State::ALIVE) ++numAlive;
				}

				if (y != (height / cellSize))
				{
					if (x != 0)
						if (cells[x - 1][y + 1].getState() == State::ALIVE) ++numAlive;

					if (cells[x][y + 1].getState() == State::ALIVE) ++numAlive;

					if (x != (width / cellSize))
						if (cells[x + 1][y + 1].getState() == State::ALIVE) ++numAlive;
				}

				if (x != 0)
					if (cells[x - 1][y].getState() == State::ALIVE) ++numAlive;

				if (x != (width / cellSize))
					if (cells[x + 1][y].getState() == State::ALIVE) ++numAlive;

				if (numAlive < 2)
					cells[x][y].SetNextState(State::DEAD);

				if (numAlive > 3)
					cells[x][y].SetNextState(State::DEAD);

				if (numAlive == 3)
					cells[x][y].SetNextState(State::ALIVE);

				if (numAlive == 2)
					cells[x][y].SetNextState(cells[x][y].getState());

			}
		}

		for (unsigned int y = 0; y < height / cellSize; ++y)
		{
			for (unsigned int x = 0; x < width / cellSize; ++x)
			{
				cells[x][y].GoToNextState();
			}
		}

		if (IsKeyPressed(KEY_R))
		{
			step = 0;

			for (unsigned int y = 0; y < height / cellSize; ++y)
			{
				for (unsigned int x = 0; x < width / cellSize; ++x)
				{
					int rand = GetRandomValue(0, 1);
					if (rand == 0) cells[x][y].Init(State::ALIVE);
					else cells[x][y].Init(State::DEAD);

				}
			}
		}

		if (IsKeyPressed(KEY_F))
		{
			ToggleFullscreen();
		}


		++step;

	}
}
