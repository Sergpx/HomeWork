#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#define random(min, max) min + rand() % (max + 1 - min)
using namespace std;



const int MARGIN = 5;
const int FIELD_SIZE = 10;
const char SEA = char(126);
const char SHIP = char(127);
const char MISS = 'o';
const char HIT = 'x';
const int TIME = 3000;
int myCount = 0;
int enemyCount = 0;



char** createField();
bool isCanSetGorizontal(char** field, int x, int y, int deck);
void setGorizontal(char** field, int x, int y, int deck);
bool isCanSetVertical(char** field, int x, int y, int deck);
void setVertical(char** field, int x, int y, int deck);

bool isCanSetShip(int*& SHIPCount, int deck);

void setShips(char** field);
void setRandomShips(char** field);

void render(char** field);
void totalRender(char** field, char** &enemyField, char** &hitField);

void startInit(char** field, char** enemyField);

bool isKill(char** enemyField, int x, int y);

int checkRightLeft(char** field, int& lastX, int& lastY, char& lastDirection);
int checkLeftRight(char** field, int& lastX, int& lastY, char& lastDirection);
int checkTopDown(char** field, int& lastX, int& lastY, char& lastDirection);
int checkDownTop(char** field, int& lastX, int& lastY, char& lastDirection);

bool optionRightTop(char** field, int& lastX, int& lastY, char& lastDirection);
bool optionTopRight(char** field, int& lastX, int& lastY, char& lastDirection);
bool optionLeftTop(char** field, int& lastX, int& lastY, char& lastDirection);
bool optionTopLeft(char** field, int& lastX, int& lastY, char& lastDirection);
bool optionLeftDown(char** field, int& lastX, int& lastY, char& lastDirection);
bool optionDownLeft(char** field, int& lastX, int& lastY, char& lastDirection);
bool optionRightDown(char** field, int& lastX, int& lastY, char& lastDirection);
bool optionDownRight(char** field, int& lastX, int& lastY, char& lastDirection);

bool isCanHit(char** anyField, int x, int y);

bool enemyTurn(char** field, int& lastY, int& lastX, char& lastDirection, char** &enemyField, char** &hitField);
bool myTurn(char** field, char** &enemyField, char** &hitField);

void copyField(char** &enemyField, char** &hitField);

void game(char** field, char** enemyField, char** hitField);
