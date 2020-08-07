// Raghubir Chimni
// Game.h 
// 7/31/2020

#pragma once
#ifndef GAME_H_
#define GAME_H_

#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2

void initializeGrid(int x, int y);
void drawGrid();
void square(int x, int y);
void drawSnake();
bool snakeCollides(int[], int[],  int);
void drawFood();
void random(int& x, int& y);

#endif