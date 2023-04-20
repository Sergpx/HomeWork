#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#define random(min, max) min + rand() % (max + 1 - min)
using namespace std;



const int MARGIN = 5;
const int FIELD_SIZE = 10;
const char sea = char(126);
const char ship1 = char(49);
const char ship2 = char(50);
const char ship3 = char(51);
const char ship4 = char(52);
const char shipTest = char(127);

void render(char** field);
void setShips(char** field);
bool isCanSet(char** field, int x, int y, int deck);
char** createField();
