#include "param.h"


char** createField() {
    char** field = new char* [FIELD_SIZE];
    for (int i = 0; i < FIELD_SIZE; i++) {
        field[i] = new char[FIELD_SIZE];
    }
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field[i][j] = SEA; // ~ = 126; 176
        }
    }
    return field;

}

bool isCanSetGorizontal(char** field, int x, int y, int deck){
    for (int y0 = y - 1; y0 <= y + 1; y0++) {

        for (int x0 = x - 1; x0 <= x + deck; x0++) {
            if (x0 >= FIELD_SIZE || x0 < 0 || y0 >= FIELD_SIZE || y0 < 0) { 
                //cout << "зона проверки за пределами поля, не важно" << endl;
                continue; 
            }
            if (field[y0][x0] != SEA) { 
                //cout << "зона проверки не море" << endl;
                return false; 
            }
        }

    }

    for (int x0 = x; x0 <= x + deck - 1 ; x0++) {
        if (x0 >= FIELD_SIZE || x0 < 0) {
            //cout << "Часть корабля за пределами поля" << endl;
            return false;
        }
    }
    return true;
}

void setGorizontal(char** field, int x, int y, int deck) {
    for (int x0 = x; x0 < x + deck; x0++) {
        field[y][x0] = SHIP;
    }
    render(field);
}

bool isCanSetVertical(char** field, int x, int y, int deck) {
    bool flag = true;
    for (int y0 = y - deck; y0 <= y + 1; y0++) {


        for (int x0 = x - 1; x0 <= x + 1; x0++) {
            if (y0 < 0 || x0 < 0 || y0 >= FIELD_SIZE || x0 >= FIELD_SIZE) {
                //cout << "зона проверки за пределами поля, не важно" << endl;
                continue;
            }
            if (field[y0][x0] != SEA) {
                //cout << "зона проверки не море" << endl;
                return false;
            }
        }

    }
    for (int y0 = y - deck + 1; y0 <= y; y0++) {
        if (y0 < 0 || y0 >= FIELD_SIZE) {
            //cout << "Часть корабля за пределами поля" << endl;
            return false;
        }
    }
    return true;
}

void setVertical(char** field, int x, int y, int deck) {
    for (int y0 = y; y0 > y - deck; y0--) {
        field[y0][x] = SHIP;
    }
    render(field);
}

bool isCanSetShip(int*& SHIPCount, int deck) {
    if (deck == 1) {
        if (SHIPCount[3] == 0) return true;
        else SHIPCount[3]--;
    }
    else if (deck == 2) {
        if (SHIPCount[2] == 0) return true;
        else SHIPCount[2]--;
    }
    else if (deck == 3) {
        if (SHIPCount[1] == 0) return true;
        else SHIPCount[1]--;
    }
    else if (deck == 4) {
        if (SHIPCount[0] == 0) return true;
        else SHIPCount[0]--;
    }
    else {
        cout << "Такого корабля нет!" << endl;
        return true;
    }
    return false;
}


void setShips(char** field) {
    int deck;
    char let;
    int x;
    int y;
    string direction;
    int* SHIPCount = new int[4] { 1, 2, 3, 4 };
    while ((SHIPCount[0] != 0 || SHIPCount[1] != 0 || SHIPCount[2] != 0 || SHIPCount[3] != 0)) {
        do {
            cout << "Сколько палубный корабль хотите разместить(1, 2, 3, 4)? ";
            cin >> deck;
        } while (isCanSetShip(SHIPCount, deck));
        direction = "G";
        cout << "Вериткально или Горизонтально (по умолчанию горизонтально)? (V/G)";
        cin >> direction;
        do {
            cout << "Введите координаты носа корабля ( буква и цифра ): ";
            cin >> let >> y;
            x = int(let) - 65;
            y--;

            if (direction == "V") {
                if (isCanSetVertical(field, x, y, deck)) {
                    setVertical(field, x, y, deck);
                    break;

                }
                else {
                    cout << "Нет возможности установить на эти координаты" << endl;
                }
            }
            else {
                if (isCanSetGorizontal(field, x, y, deck)) {
                    setGorizontal(field, x, y, deck);
                    break;
                }
                else {
                    cout << "Нет возможности установить на эти координаты" << endl;
                }
            }
        } while (true);
        // вкл/выкл
        cout << endl << "1-а палубный " << SHIPCount[3] << " | 2-х палубный: " << SHIPCount[2] << " | 3-х палубный: " << SHIPCount[1] << " | 4-х палубный: " << SHIPCount[0] << endl;

    }
}

//переделать
void setRandomShips(char** field) {
    int deck;
    char let;
    int x;
    int y;
    int* SHIPCount = new int[4] { 1, 2, 3, 4 };
    while ((SHIPCount[0] != 0 || SHIPCount[1] != 0 || SHIPCount[2] != 0 || SHIPCount[3] != 0)) {
        do {
            deck = random(1, 4);
        } while (isCanSetShip(SHIPCount, deck));
        do {
            x = random(0, FIELD_SIZE - 1);
            y = random(0, FIELD_SIZE - 1);
            if (random(1, 2) == 1) {
                if (isCanSetVertical(field, x, y, deck)) {
                    setVertical(field, x, y, deck);
                    break;
                }
            }
            else {
                if (isCanSetGorizontal(field, x, y, deck)) {
                    setGorizontal(field, x, y, deck);
                    break;
                }
            }
        } while (true);
    }
}


void render(char** field) {
    for (int i = 0; i < MARGIN; i++) {
        cout << endl;
    }
    // рендер букв
    for (int j = 0; j < MARGIN; j++) {
        cout << "\t";
    }
    cout << "   ";
    for (int i = 0; i < FIELD_SIZE; i++) {
        cout << char(65+i) << " ";
    }
    cout << endl;
    // рендер поля
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < MARGIN; j++) {
            cout << "\t";
        }
        if (i < 9) cout << " " << i + 1 << " ";
        else cout << i + 1 << " ";
        for (int j = 0; j < FIELD_SIZE; j++) {
            cout << field[i][j] << " ";
        }
        cout << endl;
    }
}


// Начальная расстановка кораблей. ВОЗМОЖНО ПЕРЕДЕЛАТЬ
void startInit(char** field, char** enemyField) {
    string isRand;
    cout << "Случайное заполнение? (Yes/No) ";
    do {
        cin >> isRand;
        if (isRand == "No" || isRand == "no") {
            system("cls");
            render(field);
            setShips(field); 
            break;
        }
        else if (isRand == "Yes" || isRand == "yes") {
            system("cls");
            setRandomShips(field);
            break;
        }
        else cout << "Я вас не понял." << endl;
    } while (true);

    system("cls");
    setRandomShips(enemyField);
}


// Проверка на убийство.
bool isKill(char** enemyField, int x, int y) {
    int decks = 1;
    int minX = x;
    int minY = y;
    bool check = false;
    bool isKill = true;
    for (int x0 = x + 1; x0 <= x + 3; x0++) {
        if (x0 < 0 || x0 >= FIELD_SIZE) continue;
        if (enemyField[y][x0] == SHIP || enemyField[y][x0] == HIT) {
            decks++;
            
        }
        else {
            //cout << "справа нет палуб" << endl;
            break;
            
        }
    }
    for (int x0 = x - 1; x0 >= x - 3; x0--) {
        if (x0 < 0 || x0 >= FIELD_SIZE) continue;
        if (enemyField[y][x0] == SHIP || enemyField[y][x0] == HIT) {
            decks++;
            if (minX > x0) minX = x0;
        }
        else {
            //cout << "слева нет палуб" << endl;
            
            break;
        }
    }
    if (decks == 1) check = true;

    if (check == true) {
        for (int y0 = y + 1; y0 <= y + 3; y0++) {
            if (y0 < 0 || y0 >= FIELD_SIZE) continue;
            if (enemyField[y0][x] == SHIP || enemyField[y0][x] == HIT) {
                decks++;
            }
            else {
                break;
            }
        }
        for (int y0 = y - 1; y0 >= y - 3; y0--) {
            if (y0 < 0 || y0 >= FIELD_SIZE) continue;
            if (enemyField[y0][x] == SHIP || enemyField[y0][x] == HIT) {
                decks++;
                if (minY > y0) minY = y0;
            }
            else {
                break;
                
            }
        }
    }
    //cout << "CHECK(X - 0 / Y - 1)" << check << endl;
    //cout << "DECKS - " << decks << endl;
    //cout << "minX - " << minX << endl;
    if (check == false) {
        for (int x0 = minX; x0 <= minX + decks - 1; x0++) {
            if (enemyField[y][x0] != HIT) {
                isKill = false;
                break;
            }
        }
        if (isKill) {
            for (int y0 = y - 1; y0 <= y + 1; y0++) {
                for (int x0 = minX - 1; x0 <= minX + decks; x0++) {
                    if (y0 < 0 || x0 < 0 || y0 >= FIELD_SIZE || x0 >= FIELD_SIZE) continue;

                    if (enemyField[y0][x0] != HIT) {
                        enemyField[y0][x0] = MISS;
                        // hitField[y0][x0] = MISS; добавить перерисовку поля из enemyField in hitField
                    }
                }
            }
            return true;
        }
        else return false;
    }
    else {
        for (int y0 = minY; y0 <= minY + decks - 1; y0++) {
            if (enemyField[y0][x] != HIT) {
                isKill = false;
                break; 
            }
        }
        if (isKill) {
            for (int y0 = minY - 1; y0 <= minY + decks; y0++) {
                for (int x0 = minX - 1; x0 <= minX + 1; x0++) {
                    if (y0 < 0 || x0 < 0 || y0 >= FIELD_SIZE || x0 >= FIELD_SIZE) continue;
                    if (enemyField[y0][x0] != HIT) {
                        enemyField[y0][x0] = MISS;
                    }
                }
            }
            return true;
        }
        else return false;
        
    }
}


// проверка право - лево
int checkRightLeft(char** field, int &lastX, int &lastY, char &lastDirection) {
    // проверка вправо
    for (int x0 = lastX + 1; x0 <= lastX + 3; x0++) {
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == MISS) break;
        else if (field[lastY][x0] == SEA) {
            field[lastY][x0] = MISS;
            cout << "Противник не попал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == SHIP) {
            field[lastY][x0] = HIT;
            if (isKill(field, x0, lastY)) {
                cout << "Противник потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Противник попал в ваш корабль." << endl;
                lastDirection = 'G';
                return 1;
            }
        }
    }
    // проверка влево
    for (int x0 = lastX - 1; x0 >= lastX - 3; x0--) {
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == MISS) break;
        else if (field[lastY][x0] == SEA) {
            field[lastY][x0] = MISS;
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == SHIP) {
            field[lastY][x0] = HIT;
            if (isKill(field, x0, lastY)) {
                cout << "Враг потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Враг попал в ваш корабль." << endl;
                lastDirection = 'G';
                return 1;
            }
        }
    }
    return 2;
}
// проверка лево - право
int checkLeftRight(char** field, int& lastX, int& lastY, char &lastDirection) {
    
    // проверка влево
    for (int x0 = lastX - 1; x0 >= lastX - 3; x0--) {
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == MISS) break;
        else if (field[lastY][x0] == SEA) {
            field[lastY][x0] = MISS;
            cout << "Противник не попал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == SHIP) {
            field[lastY][x0] = HIT;
            if (isKill(field, x0, lastY)) {
                cout << "Противник потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Противник попал в ваш корабль." << endl;
                lastDirection = 'G';
                return 1;
            }
        }
    }
    // проверка вправо
    for (int x0 = lastX + 1; x0 <= lastX + 3; x0++) {
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == MISS) break;
        else if (field[lastY][x0] == SEA) {
            field[lastY][x0] = MISS;
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == SHIP) {
            field[lastY][x0] = HIT;
            if (isKill(field, x0, lastY)) {
                cout << "Враг потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Враг попал в ваш корабль." << endl;
                lastDirection = 'G';
                return 1;
            }
        }
    }
    return 2;
}
// проверка верх - низ
int checkTopDown(char** field, int &lastX, int &lastY, char &lastDirection) {
    //проверка вверх
    for (int y0 = lastY - 1; y0 >= lastY - 3; y0--) {
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == MISS) break;
        else if (field[y0][lastX] == SEA) {
            field[y0][lastX] = MISS;
            cout << "Противник не попал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == SHIP) {
            field[y0][lastX] = HIT;
            if (isKill(field, lastX, y0)) {
                cout << "Противник потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Противник попал в ваш корабль." << endl;
                lastDirection = 'V';
                return 1;
            }
        }
    }
    // проверка вниз
    for (int y0 = lastY + 1; y0 <= lastY + 3; y0++) {
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == MISS) break;
        else if (field[y0][lastX] == SEA) {
            field[y0][lastX] = MISS;
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == SHIP) {
            field[y0][lastX] = HIT;
            if (isKill(field, lastX, y0)) {
                cout << "Враг потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Враг попал в ваш корабль." << endl;
                lastDirection = 'V';
                return 1;
            }
        }
    }
    return 2;
}
// проверка низ - верх
int checkDownTop(char** field, int& lastX, int& lastY, char &lastDirection) {
    // проверка вниз
    for (int y0 = lastY + 1; y0 <= lastY + 3; y0++) {
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == MISS) break;
        else if (field[y0][lastX] == SEA) {
            field[y0][lastX] = MISS;
            cout << "Противник не попал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == SHIP) {
            field[y0][lastX] = HIT;
            if (isKill(field, lastX, y0)) {
                cout << "Противник потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Противник попал в ваш корабль." << endl;
                lastDirection = 'V';
                return 1;
            }
        }
    }
    //проверка вверх
    for (int y0 = lastY - 1; y0 >= lastY - 3; y0--) {
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == MISS) break;
        else if (field[y0][lastX] == SEA) {
            field[y0][lastX] = MISS;
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == SHIP) {
            field[y0][lastX] = HIT;
            if (isKill(field, lastX, y0)) {
                cout << "Враг потопил ваш корабль" << endl;
                lastX = -1;
                lastY = -1;
                lastDirection = NULL;
                return 1;
            }
            else {
                cout << "Враг попал в ваш корабль." << endl;
                lastDirection = 'V';
                return 1;
            }
        }
    }
    return 2;
}



// 1. вправо -> вверх
bool optionRightTop(char** field, int &lastX, int& lastY, char &lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkRightLeft(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkTopDown(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}

// 2. вверх -> вправо
bool optionTopRight(char** field, int& lastX, int& lastY, char& lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkTopDown(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkRightLeft(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}

// 3. влево -> вверх
bool optionLeftTop(char** field, int& lastX, int& lastY, char& lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkLeftRight(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkTopDown(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}

// 4. вверх -> влево
bool optionTopLeft(char** field, int& lastX, int& lastY, char& lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkTopDown(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkLeftRight(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}

// 5. влево -> вниз
bool optionLeftDown(char** field, int& lastX, int& lastY, char& lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkLeftRight(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkDownTop(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}

// 6. вниз -> влево
bool optionDownLeft(char** field, int& lastX, int& lastY, char& lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkDownTop(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkLeftRight(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}

// 7. право -> вниз
bool optionRightDown(char** field, int& lastX, int& lastY, char& lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkRightLeft(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkDownTop(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}

// 8. вниз -> вправо
bool optionDownRight(char** field, int& lastX, int& lastY, char& lastDirection) {
    int isHitX;
    int isHitY;
    isHitX = checkDownTop(field, lastX, lastY, lastDirection);
    if (isHitX == 2) {
        isHitY = checkRightLeft(field, lastX, lastY, lastDirection);
        if (isHitY == 1) {
            return true;
        }
        else if (isHitY == 0) return false;
    }
    else if (isHitX == 1) {
        return true;
    }
    else if (isHitX == 0) return false;
}



bool isCanHit(char** anyField, int x, int y) {
    if (0 <= x && x <= 9 && 0 <= y && y <= 9) {
        if (anyField[y][x] == MISS) return true;
        else if (anyField[y][x] == HIT) return true;
        else return false;
    }
    else return true;
}

// логика ходов противника
bool enemyTurn(char** field , int &lastY, int &lastX, char &lastDirection, char** &enemyField, char** &hitField) {
    int x;
    int y;
    int rnd;
    int test;
    if (lastY != -1 && lastX != -1) {
        if (lastDirection == 'G') {
            rnd = random(1, 2);
            switch (rnd) {
            case 1:
                //cout << "VAR G1" << endl;
                return optionRightTop(field, lastX, lastY, lastDirection);
                break;
            case 2:
                //cout << "VAR G2" << endl;
                return optionLeftTop(field, lastX, lastY, lastDirection);
                break;
            }
        }
        else if (lastDirection == 'V') {
            rnd = random(1, 2);
            switch (rnd) {
            case 1:
                //cout << "VAR V1" << endl;
                return optionTopRight(field, lastX, lastY, lastDirection);
                break;
            case 2:
                //cout << "VAR V2" << endl;
                return optionDownLeft(field, lastX, lastY, lastDirection);
                break;
            }
        }
        else {
            rnd = random(1, 8);
            switch(rnd) {
                case 1:
                    //cout << "VAR R1" << endl;
                    return optionRightTop(field, lastX, lastY, lastDirection);
                    break;
                case 2:
                    //cout << "VAR R2" << endl;
                    return optionTopRight(field, lastX, lastY, lastDirection);
                    break;
                case 3:
                    //cout << "VAR R3" << endl;
                    return optionLeftTop(field, lastX, lastY, lastDirection);
                    break;
                case 4:
                    //cout << "VAR R4" << endl;
                    return optionTopLeft(field, lastX, lastY, lastDirection);
                    break;
                case 5:
                    //cout << "VAR R5" << endl;
                    return optionLeftDown(field, lastX, lastY, lastDirection);
                    break;
                case 6:
                    //cout << "VAR R6" << endl;
                    return optionDownLeft(field, lastX, lastY, lastDirection);
                    break;
                case 7:
                    //cout << "VAR R7" << endl;
                    return optionRightDown(field, lastX, lastY, lastDirection);
                    break;
                case 8:
                    //cout << "VAR R8" << endl;
                    return optionDownRight(field, lastX, lastY, lastDirection);
                    break;
            }
            
        }
    }
    else {
        system("cls");
        cout << "Ход противника" << endl;
        do {
            x = random(0, FIELD_SIZE - 1);
            y = random(0, FIELD_SIZE - 1);
        } while (isCanHit(field, x, y));
        /*char let;
        cout << "Введите координаты выстрела для врага: ";
        cin >> let >> y;
        x = int(let) - 65;
        y--;*/

        

        if (field[y][x] == SEA) {
            field[y][x] = MISS;
            totalRender(field, enemyField, hitField);
            cout << "Противник промахнулся" << endl;
            return false;
        }
        else if (field[y][x] == SHIP) {
            field[y][x] = HIT;
            if (isKill(field, x, y)) {
                totalRender(field, enemyField, hitField);
                cout << "Противник потопил ваш корабль" << endl;
                return true;
            }
            else {
                totalRender(field, enemyField, hitField);
                cout << "Противник попал в ваш корабль." << endl;
                lastX = x;
                lastY = y;
                return true;
            }
        }
    }
}

// Проверка попадания. Убил, ранил, промазал.
bool myTurn(char** field, char** &enemyField, char** &hitField) {
    int x, y;
    char let;
    do {
        cout << "Введите координаты выстрела ( буква и цифра ): ";
        cin >> let >> y;
        x = int(let) - 65;
        y--;

        //x = random(0, FIELD_SIZE - 1);
        //y = random(0, FIELD_SIZE - 1);

    } while (isCanHit(enemyField, x, y));

    system("cls");

    if (enemyField[y][x] == SEA) {
        enemyField[y][x] = MISS;
        totalRender(field, enemyField, hitField);
        cout << "Промах" << endl;
        return false;
    }
    else if (enemyField[y][x] == SHIP) {
        enemyField[y][x] = HIT;
        if (isKill(enemyField, x, y) == true) {
            totalRender(field, enemyField, hitField);
            cout << "Убил" << endl;
            return true;
        }
        else {
            totalRender(field, enemyField, hitField);
            cout << "Ранил" << endl;
            return true;
        }
    }


}

void copyField(char** &enemyField, char** &hitField) {
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            if (enemyField[i][j] == MISS) hitField[i][j] = enemyField[i][j];
            else if(enemyField[i][j] == HIT) hitField[i][j] = enemyField[i][j];
        }
    }
}

void totalRender(char** field, char** &enemyField, char** &hitField) {
    copyField(enemyField, hitField);
    render(hitField);
    render(field);
}

void game(char** field, char** enemyField, char** hitField) {
    int turn = 0;
    int lastX = -1;
    int lastY = -1;
    char lastDirection = NULL; // V or G
    bool isHit;
    while (myCount != 20 && enemyCount != 20) {
        // мой ход
        if (turn % 2 == 0) {
            do { 
                
                //copyField(enemyField, hitField);
                //render(hitField);
                //render(field);
                //cout << "MyCount - " << myCount << endl;
                isHit = myTurn(field, enemyField, hitField);
                if (isHit) myCount++;
                if (myCount == 20) break;
                Sleep(TIME);

            } while (isHit == true);
            turn++;


        }
        // ход соперника
        else {
            do {
                /*copyField(enemyField, hitField);
                render(hitField);
                render(field); */
                //cout << "EnemyCount - " << enemyCount << endl;
                isHit = enemyTurn(field, lastX, lastY, lastDirection , enemyField, hitField);
                if (isHit) enemyCount++;
                if (enemyCount == 20) break;
                Sleep(TIME);

                
            } while (isHit == true);
            turn++;

        }
    }
}



int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    char** field;
    char** enemyField;
    char** hitField;
    int* SHIPCount;
    int* enemyShipCount;
    string repeat;

    do {
        myCount = 0;
        enemyCount = 0;
        SHIPCount = new int[4] { 1, 2, 3, 4 };
        enemyShipCount = new int[4] { 1, 2, 3, 4 };
        field = createField();
        enemyField = createField();
        hitField = createField();
        render(field);
        startInit(field, enemyField);
        system("cls");
        render(hitField);
        render(field);
        cout << "Начало!" << endl;

        game(field, enemyField, hitField);
        system("cls");
        totalRender(field, enemyField, hitField);
        cout << (myCount > enemyCount ? "Вы победили!" : "Вы проиграли!") << endl;
        cout << "GAME OVER\nRepeat? ";
        cin >> repeat;
    } while (repeat == "yes" || repeat == "Yes");


    
}

