// Raghubir Chimni
// Game.cpp 
// 7/31/2020

#include "Game.h"
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include <ctime>
#include <stdlib.h>

int gridX, gridY; // window size

int snake_length = 2; 
int posX[60] = {20, 20}, posY[60] = {20, 19}; // initial snake 

bool food = true; // if food is on screen
int foodX, foodY; // coordinates of food

short direction = RIGHT; // snake starts out moving to the right

extern bool gameOver; 
extern int score;

void initializeGrid(int x, int y)
{
	gridX = x;
	gridY = y;
}

void drawGrid()
{
	for (int ix = 0; ix < gridX; ix++)
	{
		for (int iy = 0; iy < gridY; iy++)
			square(ix, iy);
	}
}

void square(int x, int y) // draws the boxes for the grid
{
	if ((x == 0 || y == 0) || (x == gridX - 1 || y == gridY - 1))
	{
		glLineWidth(3);
		glColor3f(1, 0, 0);
	}
	else
	{
		glLineWidth(1);
		glColor3f(1, 1, 1);

	glBegin(GL_LINE_LOOP);
		glVertex2i(x, y);
		glVertex2i(x+1, y);
		glVertex2i(x+1, y+1);
		glVertex2i(x, y+1);
	}

	glEnd();
}

void drawSnake() // draws snake's body 
{
	for (int i = snake_length - 1; i > 0; i--)
	{
		posX[i] = posX[i - 1];
		posY[i] = posY[i - 1];
	}

	if (direction == UP)
		posY[0]++;
	else if (direction == DOWN)
		posY[0]--;
	else if (direction == RIGHT)
		posX[0]++;
	else if (direction == LEFT)
		posX[0]--;

	for (int i = 0; i < snake_length; i++)
	{
		glColor3f(1, 0, 1);
		glRectd(posX[i], posY[i], posX[i] + 1, posY[i] + 1);
	}

	if (posX[0] == 0 || posX[0] == gridX - 1 || posY[0] == 0 || posY[0] == gridY - 1) // if snake goes out of bounds
		gameOver = true;

	if (snakeCollides(posX, posY, snake_length)) // if snake overlaps with itself
		gameOver = true;

	if (gameOver)
		return;

	if (posX[0] == foodX && posY[0] == foodY) // if snake eats food
	{
		score++;
		snake_length++;
		food = true;
	}
}

bool snakeCollides(int x[], int y[], int n)
{
	for (int i = 1; i < n; i++)
	{
		if (x[0] == x[i] && y[0] == y[i]) // checks if head collides with the body
			return true;
	}

	return false;
}

void drawFood()
{
	if (food)
		random(foodX, foodY);

	food = false;

	glColor3f(1, 0, 0);
	glRectf(foodX, foodY, foodX + 1, foodY + 1);

}

void random(int& x, int& y) // decides where to place the food (random function for food's coordinates)
{
	int max_x = gridX - 2, max_y = gridY - 2;
	int min = 1;

	srand(time(NULL));
	
	x = min + rand() % (max_x - min);
	y = min + rand() % (max_y - min);

}