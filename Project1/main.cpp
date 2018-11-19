#include <raylib.h>
#include <string>
#include "Cell.h"

#define WIDTH 1920
#define HEIGHT 1080
#define CELL_SIZE 8

int main(int argc, char** arg)
{
	InitWindow(WIDTH, HEIGHT, "Game of Life");

	SetTargetFPS(30);

	Cell cells[WIDTH / CELL_SIZE][HEIGHT / CELL_SIZE];

	for (unsigned int y = 0; y < HEIGHT / CELL_SIZE; ++y)
	{
		for (unsigned int x = 0; x < WIDTH / CELL_SIZE; ++x)
		{
			int rand = GetRandomValue(0, 1);
			if (rand == 0) cells[x][y].Init(STATE::ALIVE);
			else cells[x][y].Init(STATE::DEAD);

		}
	}
	
	while (!WindowShouldClose())
	{
		static unsigned int step = 0;
		unsigned int aliveCellAmount = 0;
		unsigned int deadCellAmount = 0;

		BeginDrawing();

		ClearBackground(BLACK);

		for (unsigned int y = 0; y < HEIGHT / CELL_SIZE; ++y)
		{
			for (unsigned int x = 0; x < WIDTH / CELL_SIZE; ++x)
			{
				if (cells[x][y].getState() == STATE::ALIVE)
				{
					DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);
					++aliveCellAmount;
				}
				else
				{
					DrawRectangle(x * CELL_SIZE, y * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
					++deadCellAmount;
				}
			}
		}

		for (unsigned int x = 0; x < WIDTH; x += CELL_SIZE)
		{
			DrawLineEx({ (float)x, 0 }, { (float)x, HEIGHT }, 1, DARKGRAY);
		}

		for (unsigned int y = 0; y < HEIGHT; y += CELL_SIZE)
		{
			DrawLineEx({ 0, (float)y }, { WIDTH, (float)y }, 1, DARKGRAY);
		}

		std::string aliveString = "Alive Cells: " + std::to_string(aliveCellAmount);
		std::string deadString = "Dead Cells: " + std::to_string(deadCellAmount);
		std::string stepString = "Step: " + std::to_string(step);

		DrawText(aliveString.c_str(), 0, 0, 20, GREEN);
		DrawText(deadString.c_str(), 0, 20, 20, GREEN);
		DrawText(stepString.c_str(), 0, 40, 20, GREEN);

		EndDrawing();

		for (unsigned int y = 0; y < HEIGHT / CELL_SIZE; ++y)
		{
			for (unsigned int x = 0; x < WIDTH / CELL_SIZE; ++x)
			{
				int numAlive = 0;
				
				if (y != 0)
				{
					if(x != 0)
						if (cells[x - 1][y - 1].getState() == STATE::ALIVE) ++numAlive;

					if (cells[x][y - 1].getState() == STATE::ALIVE) ++numAlive;

					if(x != (WIDTH / CELL_SIZE))
						if (cells[x + 1][y - 1].getState() == STATE::ALIVE) ++numAlive;
				}

				if (y != (HEIGHT / CELL_SIZE))
				{
					if(x != 0)
						if (cells[x - 1][y + 1].getState() == STATE::ALIVE) ++numAlive;

					if (cells[x][y + 1].getState() == STATE::ALIVE) ++numAlive;

					if(x != (WIDTH / CELL_SIZE))
						if (cells[x + 1][y + 1].getState() == STATE::ALIVE) ++numAlive;
				}

				if (x != 0)
					if (cells[x - 1][y].getState() == STATE::ALIVE) ++numAlive;

				if(x != (WIDTH / CELL_SIZE))
					if (cells[x + 1][y].getState() == STATE::ALIVE) ++numAlive;

				if (numAlive < 2)
					cells[x][y].SetNextState(STATE::DEAD);

				if (numAlive > 3)
					cells[x][y].SetNextState(STATE::DEAD);

				if (numAlive == 3)
					cells[x][y].SetNextState(STATE::ALIVE);

				if (numAlive == 2)
					cells[x][y].SetNextState(cells[x][y].getState());

			}
		}

		for (unsigned int y = 0; y < HEIGHT / CELL_SIZE; ++y)
		{
			for (unsigned int x = 0; x < WIDTH / CELL_SIZE; ++x)
			{
				cells[x][y].GoToNextState();
			}
		}

		if (IsKeyPressed(KEY_R))
		{
			step = 0;

			for (unsigned int y = 0; y < HEIGHT / CELL_SIZE; ++y)
			{
				for (unsigned int x = 0; x < WIDTH / CELL_SIZE; ++x)
				{
					int rand = GetRandomValue(0, 1);
					if (rand == 0) cells[x][y].Init(STATE::ALIVE);
					else cells[x][y].Init(STATE::DEAD);

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
