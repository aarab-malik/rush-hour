//24i-2552 Aarab Malik DS-B OOP Project

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include<string>
#include<cmath> 
using namespace std;

int currentScreen = 0;

class Player
{
	int score;
	int fuel;
	bool isTaxi;
	int posX;
	int posY;
	int wallet;

public:
	Player()
	{
		score = 10;
		fuel = 200;
		isTaxi = false;
		posX = 0;
		posY = 29;
		wallet = 0;
	}

    Player(bool initialIsTaxi)
    {
        score = 10;
        fuel = 200;
        isTaxi = initialIsTaxi;
        posX = 0;
        posY = 29;
        wallet = 0;
    }

	int& getScore()
	{
		return score;
	}

	int getScore() const
	{
		return score;
	}

	int& getFuel()
	{
		return fuel;
	}
	
	int getFuel() const
	{
		return fuel;
	}

	int& getX()
	{
		return posX;
	}

	int getX() const
	{
		return posX;
	}

	int& getY()
	{
		return posY;
	}

	int getY() const
	{
		return posY;
	}

	int& getWallet()
	{
		return wallet;
	}

	int getWallet() const
	{
		return wallet;
	}

	bool& getIsTaxi()
	{
		return isTaxi;
	}

	bool getIsTaxi() const
	{
		return isTaxi;
	}
};

class Vehicle
{
protected:
	int posX;
	int posY;
	int colorNum;
	static bool taken[39];
	static int takenCount;

public:
	Vehicle()
	{
		posX = 0;
		posY = 0;
		
		int randNum;

		if (takenCount < 40)
		{
			do
			{
				randNum = rand() % 40;
			} while (taken[randNum]);

			taken[randNum] = true;
			colorNum = randNum;
			takenCount++;
		}
	}

	int& getX()
	{
		return posX;
	}

	int getX() const
	{
		return posX;
	}

	int& getY()
	{
		return posY;
	}

	int getY() const
	{
		return posY;
	}

	virtual void drawCar() = 0;

	static void resetVehicleStats() 
	{
        takenCount = 0;
        for (int i = 0; i < 39; i++) 
            taken[i] = false;

    }
};

bool Vehicle::taken[39] = {false};
int Vehicle::takenCount = 0;

class Board
{
	int width;
    int height;
	int gridSize;
	int cellSize;
	int **grid;
	int numPassengers;
	int numDeliveryBoxes; 
	int gameSeconds;
	bool gameOver;
	Player player;
	int garageX, garageY;
	int npcCount;
	static const int maxNPCs = 15;
	static const int initialNPCs = 5;

public:
	Board(): player(false)
	{
		width = 0;
		height = 0;
		gridSize = 0;
		cellSize = 0;
		grid = nullptr;
		numPassengers = 0;
		numDeliveryBoxes = 5;
		gameSeconds = 0;
		npcCount = initialNPCs;

		for (int i = 0; i < maxNPCs; i++) 
            npcs[i] = nullptr;

		taxi = nullptr;
		deliveryDriver = nullptr;
		garageX = -1;
		garageY = -1;
	}

	Board(int passedGridSize, int passedCellSize, int passedNumPassengers, int passedDeliveryBoxes, int passedGameSeconds): player(false)
	{
		width = 1920;
		height = 1080;
		gridSize = passedGridSize;
		grid = new int*[gridSize];

		for (int i = 0; i < gridSize; i++)
			grid[i] = new int[gridSize];

		cellSize = passedCellSize;
		numPassengers = passedNumPassengers;
		numDeliveryBoxes = passedDeliveryBoxes; 
		gameSeconds = passedGameSeconds;
		npcCount = initialNPCs;

		for (int i = 0; i < maxNPCs; i++)
			npcs[i] = nullptr;

		for (int i = 0; i < npcCount; i++) 
            npcs[i] = new NPC(*this);

		taxi = new Taxi(*this);
		deliveryDriver = new DeliveryDriver(*this);
		garageX = -1;
		garageY = -1;
	}

	~Board()
	{
		for (int i = 0; i < gridSize; i++)
			delete[] grid[i];

		delete[] grid;
		width = 0;
		height = 0;
		gridSize = 0;
		cellSize = 0;
		grid = nullptr;
		numPassengers = 0;
		gameSeconds = 0;

		for (int i = 0; i < npcCount; i++)
            delete npcs[i]; 
		
		delete taxi;
		delete deliveryDriver;
	}

	int getWidth()
	{
		return width;
	}

	int getHeight()
	{
		return height;
	}

	int getSize()
	{
		return gridSize;
	}

	int** getGrid()
	{
		return grid; 
	}

	int getGridSize()
	{
		return gridSize;
	}

	int getCellSize()
	{
		return cellSize;
	}

	int& getGameSeconds() 
	{
	    return gameSeconds;
	}

	int getGameSeconds() const
	{
	    return gameSeconds;
	}

	bool& getGameOverStatus()
	{
	    return gameOver;
	}

	bool getGameOverStatus() const
	{
	    return gameOver;
	}

	Player& getPlayer() 
	{
		return player;
	}

	Player getPlayer() const
	{
		return player;
	}

	void initializePassengers() 
	{
		int randX, randY, placed = 0;
	
    	while (placed < numPassengers)
		{
    	    randX = rand() % gridSize;
    	    randY = rand() % gridSize;
	
    	    if (grid[randX][randY] == 0 && !(randX == player.getX() && randY == player.getY()))
			{
    	        grid[randX][randY] = 3;
    	        placed++;
    	    }
    	}
	}

	void drawPassenger()
	{
		int passX, passY;
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (grid[i][j] == 3)
				{
					DrawCircle(435 + i * cellSize + cellSize / 2, 15 + j * cellSize + cellSize / 2, cellSize / 4, colors[BLACK]);
					DrawLine(435 + i * cellSize + cellSize / 2, 15 + j * cellSize + cellSize / 2, 435 + i * cellSize + cellSize / 2, 15 + j * cellSize + cellSize / 2 - cellSize / 3, 2, colors[BLACK]);
					DrawLine(435 + i * cellSize + cellSize / 2, 15 + j * cellSize + cellSize / 2 - cellSize / 3, 435 + i * cellSize + cellSize / 2 + 5, 15 + j * cellSize + cellSize / 2 - cellSize / 2, 2, colors[BLACK]);
					DrawLine(435 + i * cellSize + cellSize / 2, 15 + j * cellSize + cellSize / 2 - cellSize / 3, 435 + i * cellSize + cellSize / 2 - 5, 15 + j * cellSize + cellSize / 2 - cellSize / 2, 2, colors[BLACK]);
				}
			}
		}
	}

	void initializeDeliveryBoxes()
	{
		int randX, randY, placed = 0;

		while (placed < numDeliveryBoxes)
		{
			randX = rand() % gridSize;
			randY = rand() % gridSize;

			if (grid[randX][randY] == 0 && !(randX == getPlayer().getX() && randY == getPlayer().getY()))
			{
				grid[randX][randY] = 4;
				placed++;
			}
		}
	}

	void drawDeliveryBoxes()
	{
		for (int i = 0; i < gridSize; i++)
		{
			for (int j = 0; j < gridSize; j++)
			{
				if (grid[i][j] == 4)
				{
					DrawSquare(435 + i * cellSize + 5, 15 + j * cellSize + 5, cellSize - 10, colors[BROWN]);

					DrawLine(435 + i * cellSize + 5, 15 + j * cellSize + 5 + (cellSize - 10) / 2, 435 + i * cellSize + cellSize - 5, 15 + j * cellSize + 5 + (cellSize - 10) / 2, 6, colors[WHITE]);
				}
			}
		}
	}

	void initializeBuildings()
	{
	    int totalCells = gridSize * gridSize, numBuildings = totalCells * 0.25, placedBuildings = 0;

	    while (placedBuildings < numBuildings)
		{
	        int randX = rand() % gridSize;
	        int randY = rand() % gridSize;
	
	        if (grid[randX][randY] == 0 && !(randX == player.getX() && randY == player.getY()))
			{
	            grid[randX][randY] = 1;
	            placedBuildings++;
	        }
	    }
	}

	void drawBuildings()
	{
		for (int i = 0; i < gridSize; i++) 
		{
    	    for (int j = 0; j < gridSize; j++)
			{
    	        if (grid[i][j] == 1) 
    	            DrawSquare(435 + i * cellSize, 15 + j * cellSize, cellSize + 2, colors[BLACK]);
    	    }
    	}
	}

	void initializeObstacles()
	{
	    int totalCells = gridSize * gridSize, numObstacles = totalCells * 0.01, placedObstacles = 0;

	    while (placedObstacles < numObstacles)
		{
	        int randX = rand() % gridSize;
	        int randY = rand() % gridSize;
	
	        if (grid[randX][randY] == 0 && !(randX == player.getX() && randY == player.getY()))
			{
	            grid[randX][randY] = 2;
	            placedObstacles++;
	        }
	    }
	}

	void drawObstacles()
	{
		for (int i = 0; i < gridSize; i++) 
		{
    	    for (int j = 0; j < gridSize; j++)
			{
    	        if (grid[i][j] == 2) 
				{
    	            DrawSquare(435 + i * cellSize + cellSize / 4, 15 + j * cellSize, cellSize / 2, colors[BROWN]);
					
					DrawTriangle(435 + i * cellSize, 15 + j * cellSize + cellSize / 2, 435 + i * cellSize + cellSize, 15 + j * cellSize + cellSize / 2, 435 + i * cellSize + cellSize / 2,  15 + j * cellSize + cellSize, colors[GREEN]);
    	        }
    	    }
    	}
	}

	void initializeFuelStations()
	{
		int placed = 0;

		while (placed < 2) 
		{
			int fuelX = rand() % gridSize;
			int fuelY = rand() % gridSize;

			if (grid[fuelX][fuelY] == 0 && !(fuelX == player.getX() && fuelY == player.getY())) 
			{
				grid[fuelX][fuelY] = 5;
				placed++;
			}
		}
	}

	void drawFuelStation()
	{
		for (int i = 0; i < gridSize; i++) 
		{
			for (int j = 0; j < gridSize; j++) 
			{
				if (grid[i][j] == 5) 
				{
                	DrawSquare(435 + i * cellSize + 2, 15 + j * cellSize + 2, cellSize - 4, colors[RED]);

					DrawRectangle(435 + i * cellSize + cellSize * 0.2 + 3, 20 + j * cellSize + cellSize * 0.375, cellSize * 0.4, cellSize * 0.25, colors[WHITE]);

				}
			}
		}
	}

	void initializeGarage()
	{
		int corner = rand() % 3;

		if (corner == 0)
		{
			garageX = gridSize - 1;
			garageY = gridSize - 1;
		}
		else if (corner == 1)
		{
			garageX = 0;
			garageY = 0;
		}
		else
		{
			garageX = gridSize - 1;
			garageY = 0;
		}

		grid[garageX][garageY] = 6;
	}

	void drawGarage()
	{
		DrawSquare(435 + garageX * cellSize + cellSize / 4, 15 + garageY * cellSize, cellSize / 2, colors[NAVY]);
		DrawTriangle(435 + garageX * cellSize, 15 + garageY * cellSize + cellSize / 2, 435 + garageX * cellSize + cellSize, 15 + garageY * cellSize + cellSize / 2, 435 + garageX * cellSize + cellSize / 2, 15 + garageY * cellSize + cellSize, colors[NAVY]);
	}

	void resetGame()
	{
	    player.getX() = 0;
	    player.getY() = 29;
	    player.getFuel() = 200;
		player.getScore() = 0;
		player.getWallet() = 0;
		gameSeconds = 180;
        gameOver = false;
		garageX = -1;
		garageY = -1;
		npcCount = initialNPCs;
	
	    for(int i = 0; i < gridSize; i++)
		{
	        for(int j = 0; j < gridSize; j++)
	            grid[i][j] = 0;
	    }

        for (int i = 0; i < maxNPCs; i++)
        {
            delete npcs[i];
            npcs[i] = nullptr;
        }
		delete taxi;
		taxi = nullptr;
		delete deliveryDriver;
		deliveryDriver = nullptr;

        Vehicle::resetVehicleStats();

        initializeBuildings();
        initializeObstacles();
        initializePassengers();
        initializeDeliveryBoxes();
        initializeFuelStations();
        initializeGarage();

        for (int i = 0; i < npcCount; i++)
            npcs[i] = new NPC(*this);
			
		taxi = new Taxi(*this);
		deliveryDriver = new DeliveryDriver(*this);
	}

	void buyFuel() 
	{
		int posX = player.getX();
		int posY = player.getY();

		bool adjacentFuel = false;

		if (posY + 1 < gridSize && grid[posX][posY + 1] == 5)
			adjacentFuel = true;

		else if (posY - 1 >= 0 && grid[posX][posY - 1] == 5)
			adjacentFuel = true;

		else if (posX + 1 < gridSize && grid[posX + 1][posY] == 5)
			adjacentFuel = true;
			
		else if (posX - 1 >= 0 && grid[posX - 1][posY] == 5)
			adjacentFuel = true;

		if (adjacentFuel && player.getWallet() > 0)
		{
			player.getFuel() += player.getWallet();
			player.getWallet() = 0;
		}
	}

	class NPC: public Vehicle 
	{
		Board& board; 
		int speed;
		int direction; 
	public:

		NPC(Board& b): board(b)
		{
			int randX, randY;

			do
			{
				randX = rand() % board.gridSize;
				randY = rand() % board.gridSize;
			} while (board.grid[randX][randY] != 0 || (randX == board.player.getX() && randY == board.player.getY()));

			posX = randX;
			posY = randY;
			direction = rand() % 4;
		}

		void drawCar() 
		{
		    DrawSquare(435 + posX * board.cellSize + 8, 15 + posY * board.cellSize + 8, board.cellSize - 16, colors[colorNum]);

		    DrawCircle(435 + posX * board.cellSize + 5 + (board.cellSize - 10) / 6 + 4, 15 + posY * board.cellSize + 5 + (board.cellSize - 10) / 6, (board.cellSize - 10) / 6, colors[BLACK]);
			
		    DrawCircle(435 + posX * board.cellSize + 5 + (board.cellSize - 10) - (board.cellSize - 10) / 6 - 4, 15 + posY * board.cellSize + 5 + (board.cellSize - 10) / 6, (board.cellSize - 10) / 6, colors[BLACK]);
		}

		void moveCar()
		{
			int prevX = posX;
			int prevY = posY;

			switch (direction)
			{
				case 0:
					if (posY < board.gridSize - 1 && board.grid[posX][posY + 1] == 0)
						posY++;
					else
					{
						if (posY > 0 && posX >= 0 && posX < board.gridSize && board.grid[posX][posY - 1] == 0)
							direction = 1;
						else
						{
							if (rand() % 2)
								direction = 2;
							else
								direction = 3;
						}
					}
					break;

				case 1:
					if (posY > 0 && posX >= 0 && posX < board.gridSize && board.grid[posX][posY - 1] == 0)
						posY--;
					else
					{
						if (posY + 1 < board.gridSize && posX >= 0 && posY < board.gridSize && board.grid[posX][posY + 1] == 0)
							direction = 0;
						else
						{
							if (rand() % 2)
								direction = 2;
							else
								direction = 3;
						}
					}
					break;

				case 2: 
					if (posX > 0 && posY >= 0 && posY < board.gridSize && board.grid[posX - 1][posY] == 0)
						posX--;
					else
					{
						if (posX + 1 < board.gridSize && posY >= 0 && posY < board.gridSize && board.grid[posX + 1][posY] == 0)
							direction = 3;
						else
						{
							if (rand() % 2)
								direction = 0;
							else
								direction = 1;
						}
					}
					break;

				case 3: 
					if (posX + 1 < board.gridSize && posY >= 0 && posY < board.gridSize && board.grid[posX + 1][posY] == 0)
						posX++;
					else
					{
						if (posX > 0 && posY >= 0 && posY < board.gridSize && board.grid[posX - 1][posY] == 0)
							direction = 2;
						else
						{
							if (rand() % 2)
								direction = 0;
							else
								direction = 1;
						}
					}
					break;
			}

			if (posX < 0 || posX >= board.gridSize || posY < 0 || posY >= board.gridSize)
			{
				posX = prevX;
				posY = prevY;
				direction = rand() % 4;
			}
		}
	};

	void moveNPCs() 
	{
        if (!gameOver) 
		{
            for (int i = 0; i < npcCount; i++) 
                if (npcs[i]) npcs[i]->moveCar(); 
        }
    }

    void drawNPCs() 
	{
        for (int i = 0; i < npcCount; i++) 
            if (npcs[i]) npcs[i]->drawCar(); 
    }

	NPC** getNPCs() 
	{
		return npcs;
	}

	int getNPCCount() const 
	{ 
		return npcCount; 
	}

	void addNPC()
	{
		if (npcCount < maxNPCs)
		{
			npcs[npcCount] = new NPC(*this);
			npcCount++;
		}
	}

private:
	NPC* npcs[maxNPCs];
public:

	class Taxi: public Vehicle
	{
		Board& board;
		bool hasPassenger;
		int destX;
		int destY;
		bool hasDestination;
		int passengersDropped; 

	public:
		Taxi(Board& b): board(b)
		{
			hasPassenger = false;
			hasDestination = false;
			destX = -1;
			destY = -1;
			passengersDropped = 0;
		}

		void drawCar() override
		{
			DrawSquare(435 + board.getPlayer().getX() * board.getCellSize() + 8, 15 + board.getPlayer().getY() * board.getCellSize() + 8, board.getCellSize() - 16, colors[ORANGE]);

			DrawCircle(435 + board.getPlayer().getX() * board.getCellSize() + 5 + (board.getCellSize() - 10) / 6 + 4, 15 + board.getPlayer().getY() * board.getCellSize() + 5 + (board.getCellSize() - 10) / 6, (board.getCellSize() - 10) / 6, colors[BLACK]);

			DrawCircle(435 + board.getPlayer().getX() * board.getCellSize() + 5 + (board.getCellSize() - 10) - (board.getCellSize() - 10) / 6 - 4, 15 + board.getPlayer().getY() * board.getCellSize() + 5 + (board.getCellSize() - 10) / 6, (board.getCellSize() - 10) / 6, colors[BLACK]);
			
			DrawLine(435 + board.getPlayer().getX() * board.getCellSize() + 8, 15 + board.getPlayer().getY() * board.getCellSize() + 5 + (board.getCellSize() - 10) / 2, 435 + board.getPlayer().getX() * board.getCellSize() + 8 + (board.getCellSize() - 16), 15 + board.getPlayer().getY() * board.getCellSize() + 5 + (board.getCellSize() - 10) / 2, 4, colors[BLACK]);
		}

		void pickPassenger() 
		{
			if (hasPassenger) 
				return;

			int posX = board.getPlayer().getX();
			int posY = board.getPlayer().getY();
			int** grid = board.getGrid();

			bool found = false;

			if (posY + 1 < board.getGridSize()) 
			{
				if (grid[posX][posY + 1] == 3)
				{
					grid[posX][posY + 1] = 0;
					found = true;
				}
			}
			
			if (!found && posY - 1 >= 0)
			{
				if (grid[posX][posY - 1] == 3)
				{
					grid[posX][posY - 1] = 0;
					found = true;
				}
			}

			if (!found && posX - 1 >= 0) 
			{
				if (grid[posX - 1][posY] == 3)
				{
					grid[posX - 1][posY] = 0;
					found = true;
				}	
			}
			
			if (!found && posX + 1 < board.getGridSize())
			{
				if (grid[posX + 1][posY] == 3) 
				{
					grid[posX + 1][posY] = 0;
					found = true;
				}
			}

			if (found) 
			{
				hasPassenger = true;
				hasDestination = false;
				return;
			}
		}

		void drawDestination() 
		{
			if (hasPassenger) 
			{
				if (!hasDestination) 
				{
					int** grid = board.getGrid();
					int size = board.getGridSize();
					int randX, randY;

					do 
					{
						randX = rand() % size;
						randY = rand() % size;
					} while (grid[randX][randY] != 0 || (randX == board.getPlayer().getX() && randY == board.getPlayer().getY()));

					destX = randX;
					destY = randY;
					hasDestination = true;
				}

				DrawSquare(437 + destX * board.getCellSize(), 15 + destY * board.getCellSize(), board.getCellSize() - 2, colors[LIGHT_GREEN]);
			}
		}

		void dropPassenger() 
		{
			if (!hasPassenger || !hasDestination) 
				return;

			int posX = board.getPlayer().getX();
			int posY = board.getPlayer().getY();

			if ((posY + 1 < board.getGridSize() && posX == destX && posY + 1 == destY) || (posY - 1 >= 0 && posX == destX && posY - 1 == destY) || (posX - 1 >= 0 && posY == destY && posX - 1 == destX) || (posX + 1 < board.getGridSize() && posY == destY && posX + 1 == destX)) 
			{
				hasPassenger = false;
				hasDestination = false;
				destX = -1;
				destY = -1;
				board.getPlayer().getScore() += 10;

				board.getPlayer().getWallet() += 40 + rand() % 31;

				int** grid = board.getGrid();
				int size = board.getGridSize();
				int randX, randY;

				do 
				{
					randX = rand() % size;
					randY = rand() % size;
				} while (grid[randX][randY] != 0 || (randX == board.getPlayer().getX() && randY == board.getPlayer().getY()));

				grid[randX][randY] = 3;

				passengersDropped++;

				if (passengersDropped % 2 == 0)
					board.addNPC();
			}
		}

		int getPassengersDropped()
		{
			return passengersDropped;
		}

	};


	class DeliveryDriver: public Vehicle
	{
		Board& board;
		bool hasPackage;
		int destX;
		int destY;
		bool hasDestination;
		int packagesDropped;

	public:
		DeliveryDriver(Board& b): board(b)
		{
			hasPackage = false;
			hasDestination = false;
			destX = -1;
			destY = -1;
			packagesDropped = 0;
		}

		void drawCar() override
		{
			DrawSquare(435 + board.getPlayer().getX() * board.getCellSize() + 8, 15 + board.getPlayer().getY() * board.getCellSize() + 8, board.getCellSize() - 16, colors[RED]);

			DrawCircle(435 + board.getPlayer().getX() * board.getCellSize() + 9 + (board.getCellSize() - 10) / 6, 20 + board.getPlayer().getY() * board.getCellSize() + (board.getCellSize() - 10) / 6, (board.getCellSize() - 10) / 6, colors[BLACK]);

			DrawCircle(435 + board.getPlayer().getX() * board.getCellSize() + 1 + (board.getCellSize() - 10) * 5.0 / 6, 20 + board.getPlayer().getY() * board.getCellSize() + (board.getCellSize() - 10) / 6, (board.getCellSize() - 10) / 6, colors[BLACK]);

			DrawLine(435 + board.getPlayer().getX() * board.getCellSize() + 8, 15 + board.getPlayer().getY() * board.getCellSize() + 5 + (board.getCellSize() - 10) / 2, 435 + board.getPlayer().getX() * board.getCellSize() + board.getCellSize() - 8, 15 + board.getPlayer().getY() * board.getCellSize() + 5 + (board.getCellSize() - 10) / 2, 4, colors[ORANGE]);

			glutPostRedisplay();
		}

		void pickPackage()
		{
			if (hasPackage)
				return;

			int posX = board.getPlayer().getX();
			int posY = board.getPlayer().getY();
			int** grid = board.getGrid();

			bool found = false;

			if (posY + 1 < board.getGridSize())
			{
				if (grid[posX][posY + 1] == 4)
				{
					grid[posX][posY + 1] = 0;
					found = true;
				}
			}

			if (!found && posY - 1 >= 0)
			{
				if (grid[posX][posY - 1] == 4)
				{
					grid[posX][posY - 1] = 0;
					found = true;
				}
			}

			if (!found && posX - 1 >= 0)
			{
				if (grid[posX - 1][posY] == 4)
				{
					grid[posX - 1][posY] = 0;
					found = true;
				}
			}

			if (!found && posX + 1 < board.getGridSize())
			{
				if (grid[posX + 1][posY] == 4)
				{
					grid[posX + 1][posY] = 0;
					found = true;
				}
			}

			if (found)
			{
				hasPackage = true;
				hasDestination = false;
				return;
			}
		}

		void drawDestination()
		{
			if (hasPackage)
			{
				if (!hasDestination)
				{
					int** grid = board.getGrid();
					int size = board.getGridSize();
					int randX, randY;

					do
					{
						randX = rand() % size;
						randY = rand() % size;
					} while (grid[randX][randY] != 0 || (randX == board.getPlayer().getX() && randY == board.getPlayer().getY()));

					destX = randX;
					destY = randY;
					hasDestination = true;
				}

				DrawSquare(437 + destX * board.getCellSize(), 15 + destY * board.getCellSize(), board.getCellSize() - 2, colors[LIGHT_BLUE]);
			}
		}

		void dropPackage()
		{
			if (!hasPackage || !hasDestination)
				return;

			int posX = board.getPlayer().getX();
			int posY = board.getPlayer().getY();

			if ((posY + 1 < board.getGridSize() && posX == destX && posY + 1 == destY) || (posY - 1 >= 0 && posX == destX && posY - 1 == destY) || (posX - 1 >= 0 && posY == destY && posX - 1 == destX) || (posX + 1 < board.getGridSize() && posY == destY && posX + 1 == destX))
			{
				hasPackage = false;
				hasDestination = false;
				destX = -1;
				destY = -1;
				board.getPlayer().getScore() += 20;
				board.getPlayer().getWallet() += 20 + rand() % 31;

				int** grid = board.getGrid();
				int size = board.getGridSize();
				int randX, randY;

				do
				{
					randX = rand() % size;
					randY = rand() % size;
				} while (grid[randX][randY] != 0 || (randX == board.getPlayer().getX() && randY == board.getPlayer().getY()));

				grid[randX][randY] = 4;

				packagesDropped++;

				if (packagesDropped % 2 == 0)
					board.addNPC();
			}
		}

		int getPackagesDropped()
		{
			return packagesDropped;
		}
		
	};

private:
	Taxi* taxi;
	DeliveryDriver* deliveryDriver;

public:

	Taxi* getTaxi() 
	{ 
		return taxi;
	}

	DeliveryDriver* getDeliveryDriver()
	{
		return deliveryDriver;
	}

	void switchRole()
	{
		int posX = player.getX();
		int posY = player.getY();
		bool adjacentGarage = false;

		if (posY + 1 < gridSize && grid[posX][posY + 1] == 6)
			adjacentGarage = true;
		else if (posY - 1 >= 0 && grid[posX][posY - 1] == 6)
			adjacentGarage = true;
		else if (posX + 1 < gridSize && grid[posX + 1][posY] == 6)
			adjacentGarage = true;
		else if (posX - 1 >= 0 && grid[posX - 1][posY] == 6)
			adjacentGarage = true;

		if (adjacentGarage)
			player.getIsTaxi() = !player.getIsTaxi();
	}
};

Board board(30, 35, 4, 2, 180); 

void SetCanvasSize(int width, int height) 
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}

void GameDisplay()
{
	glClearColor(0.8, 0.8, 0.8, 0); 
	glClear (GL_COLOR_BUFFER_BIT);

    if (currentScreen == 0)
	{
        DrawRectangle(0, 0, 1925, 1085, colors[BLACK]);
		
        DrawString(825, 875, "Welcome to Rush Hour!", colors[WHITE]);

        DrawRectangle(600, 600, 245, 50, colors[YELLOW]);
        DrawString(625, 620, "Play as Taxi Driver", colors[WHITE]);

        DrawRectangle(600, 520, 245, 50, colors[BLUE]);
        DrawString(610, 540, "Play as Delivery Driver", colors[WHITE]);

        glutSwapBuffers();
        return;
    }

    if (currentScreen != 2)
		return;

	if (board.getGameOverStatus())
	{
		DrawRectangle(0, 0, 1925, 1085, colors[BLACK]);

		DrawString(875, 875, "GAME OVER!", colors[WHITE]);
		
		if (board.getPlayer().getScore() >= 100) 
			DrawString(600, 750, "YOU WIN!", colors[GREEN]);
		else
			DrawString(600, 750, "YOU LOSE!", colors[RED]);

		DrawString(600, 700, "Score: " + to_string(board.getPlayer().getScore()), colors[BLUE]);
		DrawString(600, 650, "Passengers dropped: " + to_string(board.getTaxi()->getPassengersDropped()), colors[YELLOW]);
		DrawString(600, 600, "Packages dropped: " + to_string(board.getDeliveryDriver()->getPackagesDropped()), colors[BROWN]);
		DrawString(600, 550, "Leftover money: $" + to_string(board.getPlayer().getWallet()), colors[GREEN]);
		
    }
	else
	{
		DrawString(50, 800, "Score: " + to_string(board.getPlayer().getScore()), colors[BLACK]);

		DrawString(50, 775, "Wallet: $" + to_string(board.getPlayer().getWallet()), colors[GREEN]);

		string fuelStr = "Fuel: " + to_string(board.getPlayer().getFuel());
		DrawString(50, 750, fuelStr, colors[RED]);

		int** grid = board.getGrid();

		int minutes = board.getGameSeconds() / 60;
		int seconds = board.getGameSeconds() % 60;

		string timeStr = "Time: " + to_string(minutes) + ":";
		if (seconds < 10)
			 timeStr += "0";
		else
			timeStr += "";
		timeStr += to_string(seconds);
    	DrawString(50, 700, timeStr, colors[BLUE_VIOLET]);

    	for (int i = 0; i <= board.getGridSize(); i++)
		{
    	    DrawLine(435 + i * board.getCellSize(), 15, 435 + i * board.getCellSize(), 1065, 2, colors[BLACK]);
    	    //DrawLine(435, 15 + i * board.getCellSize(), 1485, 15 + i * board.getCellSize(), 2, colors[BLACK]);
    	}

		board.drawBuildings();
		board.drawObstacles();
		board.drawPassenger();
		board.drawDeliveryBoxes(); 
		board.drawNPCs();
		board.drawFuelStation();
		board.drawGarage();

		if (board.getPlayer().getIsTaxi()) 
		{
			board.getTaxi()->drawDestination();
			board.getTaxi()->drawCar();
		}

		else 
		{
			board.getDeliveryDriver()->drawDestination();
			board.getDeliveryDriver()->drawCar();
		}

		DrawLine(435, 15, 1485, 15, 5, colors[RED]);
    	DrawLine(435, 1065, 1485, 1065, 5, colors[RED]);
    	DrawLine(435, 15, 435, 1065, 5, colors[RED]);
    	DrawLine(1485, 15, 1485, 1065, 5, colors[RED]);
	}

	glutSwapBuffers();
	
}

void NonPrintableKeys(int key, int x, int y) 
{
	if (!board.getGameOverStatus() && board.getPlayer().getFuel() > 0) 
	{
		int** grid = board.getGrid();
		int posX = board.getPlayer().getX();
		int posY = board.getPlayer().getY();

		if (key == GLUT_KEY_LEFT) 
		{
			if (posX > 0 && grid[posX - 1][posY] != 1 && grid[posX - 1][posY] != 5)
			{
				board.getPlayer().getX()--;
				board.getPlayer().getFuel()--;
			}
		} 
		else if (key == GLUT_KEY_RIGHT) 
		{
			if (posX < board.getGridSize() - 1 && grid[posX + 1][posY] != 1 && grid[posX + 1][posY] != 5)
			{
				board.getPlayer().getX()++;
				board.getPlayer().getFuel()--;
			}
		} 
		else if (key == GLUT_KEY_UP) 
		{
			if (posY < board.getGridSize() - 1 && grid[posX][posY + 1] != 1 && grid[posX][posY + 1] != 5)
			{
				board.getPlayer().getY()++;
				board.getPlayer().getFuel()--;
			}
		}
		else if (key == GLUT_KEY_DOWN)
		{
			if (posY > 0 && grid[posX][posY - 1] != 1 && grid[posX][posY - 1] != 5)
			{
				board.getPlayer().getY()--;
				board.getPlayer().getFuel()--;
			}
		}

		posX = board.getPlayer().getX();
		posY = board.getPlayer().getY();

		bool carHit = false;

		if (grid[posX][posY] == 3)
		{
			if (board.getPlayer().getIsTaxi()) 
				board.getPlayer().getScore() -= 5;
			else 
				board.getPlayer().getScore() -= 8;

		} 
		else if (grid[posX][posY] == 2 || grid[posX][posY] == 4) 
		{
			if (board.getPlayer().getIsTaxi()) 
				board.getPlayer().getScore() -= 2;
			else
				board.getPlayer().getScore() -= 4;
		} 
		else 
		{
			carHit = false;
			for (int i = 0; i < 10; i++)
				if (board.getNPCs()[i] && board.getNPCs()[i]->getX() == posX && board.getNPCs()[i]->getY() == posY)
					carHit = true;
			if (carHit) 
			{
				if (board.getPlayer().getIsTaxi())
					board.getPlayer().getScore() -= 3;
				else 
					board.getPlayer().getScore() -= 5;
			}
		}
	}

	if (board.getPlayer().getFuel() == 0 || board.getPlayer().getScore() < 0)
		board.getGameOverStatus() = true;

	glutPostRedisplay();
}


void PrintableKeys(unsigned char key, int x, int y) 
{
	if (key == 27) 
		exit(1); 

	if (key == 'r' || key == 'R') 
		board.resetGame();

	if (key == 'b' || key == 'B')
	{
		board.buyFuel();
		cout << "b pressed" << endl;
	}

	if (key == 32) 
	{
		if (board.getPlayer().getIsTaxi()) 
		{
			board.getTaxi()->pickPassenger();
			board.getTaxi()->dropPassenger();
		}
		else
		{
			board.getDeliveryDriver()->pickPackage();
			board.getDeliveryDriver()->dropPackage();
		}
	}

	if (key == 'p' || key == 'P') 
		board.switchRole();

	glutPostRedisplay();
}

void Timer(int m) 
{

	if (currentScreen == 2)
	{
    	if (!board.getGameOverStatus()) 
		{
    	    if (board.getGameSeconds() > 0) 
			{
    	        board.getGameSeconds()--;
    	        glutPostRedisplay();
    	    }

    	    if (board.getGameSeconds() == 0 || board.getPlayer().getFuel() <= 0)
			{
    	        board.getGameOverStatus() = true;
    	        glutPostRedisplay(); 
    	    }
			board.moveNPCs();
    	}
	}

    glutTimerFunc(1000, Timer, 0);
}

void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

void MouseClicked(int button, int state, int x, int y)
{
    int clickX = x;
    int clickY = y; 

    if (button == GLUT_LEFT_BUTTON && currentScreen == 0)
	{
        if (clickX >= 600 && clickX <= 845 && clickY >= 400 && clickY <= 450) 
		{
            board.getPlayer().getIsTaxi() = true;
            currentScreen = 2;
        }

        else if (clickX >= 600 && clickX <= 845 && clickY >= 480 && clickY <= 525) 
		{
            board.getPlayer().getIsTaxi() = false;
            currentScreen = 2;
        }
    }

	glutPostRedisplay();
}

int main(int argc, char*argv[]) 
{
	InitRandomizer(); 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); 
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(board.getWidth(), board.getHeight());
	glutCreateWindow("Rush Hour - 24i-2552"); 
	SetCanvasSize(board.getWidth(), board.getHeight()); 

	glutDisplayFunc(GameDisplay);
	glutSpecialFunc(NonPrintableKeys); 
	glutKeyboardFunc(PrintableKeys);

	glutTimerFunc(1000.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); 
	glutMotionFunc(MousePressedAndMoved); 
	board.resetGame(); 

	glutMainLoop();
	return 1;
}
#endif 
