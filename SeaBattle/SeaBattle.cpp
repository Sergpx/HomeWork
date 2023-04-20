#include "param.h"

char** createField() {
    char** field = new char* [FIELD_SIZE];
    for (int i = 0; i < FIELD_SIZE; i++) {
        field[i] = new char[FIELD_SIZE];
    }
    for (int i = 0; i < FIELD_SIZE; i++) {
        for (int j = 0; j < FIELD_SIZE; j++) {
            field[i][j] = sea; // ~ = 126; 176
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
            if (field[y0][x0] != '~') { 
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
        field[y][x0] = shipTest;
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
            if (field[y0][x0] != '~') {
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
        field[y0][x] = shipTest;
    }
    render(field);
}

bool isCanSetShip(int*& shipCount, int deck) {
    if (deck == 1) {
        if (shipCount[3] == 0) return true;
    }
    else if (deck == 2) {
        if (shipCount[2] == 0) return true;
    }
    else if (deck == 3) {
        if (shipCount[1] == 0) return true;
    }
    else if (deck == 4) {
        if (shipCount[0] == 0) return true;
    }
    else {
        cout << "Такого корабля нет!" << endl;
        return true;
    }
    return false;
}

void setShips(char** field, int* shipCount) {
    int deck;
    char let;
    int x;
    int y;
    string direction;
    do {
        cout << "Сколько палубный корабль хотите разместить(1, 2, 3, 4)? ";
        cin >> deck;
    } while (isCanSetShip(shipCount, deck));
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

    switch (deck) {
    case 1:
        shipCount[3]--;
        break;
    case 2:
        shipCount[2]--;
        break;
    case 3:
        shipCount[1]--;
        break;
    case 4:
        shipCount[0]--;
        break;
    }

}

void setRandomShips(char** field, int* shipCount) {
    int deck;
    char let;
    int x;
    int y;
    
    do {
        deck = random(1, 4);
    } while (isCanSetShip(shipCount, deck));
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

    switch (deck) {
    case 1:
        shipCount[3]--;
        break;
    case 2:
        shipCount[2]--;
        break;
    case 3:
        shipCount[1]--;
        break;
    case 4:
        shipCount[0]--;
        break;
    }
    cout << endl << "1-а палубный " << shipCount[3] << " | 2-х палубный: " << shipCount[2] << " | 3-х палубный: " << shipCount[1] << " | 4-х палубный: " << shipCount[0] << endl;

}

void render(char** field) {
    //system("cls");
    // верхний отступ
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
// Начальная расстановка кораблей.
void startInit(char** field, char** enemyField, int* shipCount, int* enemyShipCount) {
    string isRand;
    cout << "Случайное заполнение? (Yes/No) ";
    do {
        cin >> isRand;
        if (isRand == "No" || isRand == "no") {
            while ((shipCount[0] != 0 || shipCount[1] != 0 || shipCount[2] != 0 || shipCount[3] != 0)) {
                system("cls");
                setShips(field, shipCount);
                
            }
            break;
        }
        else if (isRand == "Yes" || isRand == "yes") {
            while ((shipCount[0] != 0 || shipCount[1] != 0 || shipCount[2] != 0 || shipCount[3] != 0)) {
                system("cls");
                setRandomShips(field, shipCount);
                
            }
            break;
        }
        else cout << "Я вас не понял." << endl;
    } while (true);

    
    while ((enemyShipCount[0] != 0 || enemyShipCount[1] != 0 || enemyShipCount[2] != 0 || enemyShipCount[3] != 0)) {
        system("cls");
        setRandomShips(enemyField, enemyShipCount);
    }
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
        if (enemyField[y][x0] == shipTest || enemyField[y][x0] == 'x') {
            decks++;
            
        }
        else {
            cout << "справа нет палуб" << endl;
            break;
            
        }
    }
    for (int x0 = x - 1; x0 >= x - 3; x0--) {
        if (x0 < 0 || x0 >= FIELD_SIZE) continue;
        if (enemyField[y][x0] == shipTest || enemyField[y][x0] == 'x') {
            decks++;
            if (minX > x0) minX = x0;
        }
        else {
            cout << "слева нет палуб" << endl;
            
            break;
        }
    }
    if (decks == 1) check = true;

    if (check == true) {
        for (int y0 = y + 1; y0 <= y + 3; y0++) {
            if (y0 < 0 || y0 >= FIELD_SIZE) continue;
            if (enemyField[y0][x] == shipTest || enemyField[y0][x] == 'x') {
                decks++;
            }
            else {
                break;
            }
        }
        for (int y0 = y - 1; y0 >= y - 3; y0--) {
            if (y0 < 0 || y0 >= FIELD_SIZE) continue;
            if (enemyField[y0][x] == shipTest || enemyField[y0][x] == 'x') {
                decks++;
                if (minY > y0) minY = y0;
            }
            else {
                break;
                
            }
        }
    }
    cout << "CHECK(X - 0 / Y - 1)" << check << endl;
    cout << "DECKS - " << decks << endl;
    cout << "minX - " << minX << endl;
    if (check == false) {
        for (int x0 = minX; x0 <= minX + decks - 1; x0++) {
            if (enemyField[y][x0] != 'x') {
                isKill = false;
                break;
            }
        }
        if (isKill) {
            for (int y0 = y - 1; y0 <= y + 1; y0++) {
                for (int x0 = minX - 1; x0 <= minX + decks; x0++) {
                    if (y0 < 0 || x0 < 0 || y0 >= FIELD_SIZE || x0 >= FIELD_SIZE) continue;

                    if (enemyField[y0][x0] != 'x') {
                        enemyField[y0][x0] = 'o';
                        // hitField[y0][x0] = 'o'; добавить перерисовку поля из enemyField in hitField
                    }
                }
            }
            return true;
        }
        else return false;
    }
    else {
        for (int y0 = minY; y0 <= minY + decks - 1; y0++) {
            if (enemyField[y0][x] != 'x') {
                isKill = false;
                break; 
            }
        }
        if (isKill) {
            for (int y0 = minY - 1; y0 <= minY + decks; y0++) {
                for (int x0 = minX - 1; x0 <= minX + 1; x0++) {
                    if (y0 < 0 || x0 < 0 || y0 >= FIELD_SIZE || x0 >= FIELD_SIZE) continue;
                    if (enemyField[y0][x0] != 'x') {
                        enemyField[y0][x0] = 'o';
                    }
                }
            }
            return true;
        }
        else return false;
        
    }
}

// Проверка попадания. Убил, ранил, промазал.
bool myTurn(char** enemyField, char** hitField) {
    int x, y;
    char let;
    cout << "Введите координаты выстрела ( буква и цифра ): ";
    cin >> let >> y;
    x = int(let) - 65;
    y--;
    if (enemyField[y][x] == '~') {
        enemyField[y][x] = 'o';
        hitField[y][x] = 'o';
        cout << "Промах" << endl;
        return false;
    }
    else if (enemyField[y][x] == shipTest) {
        enemyField[y][x] = 'x';
        hitField[y][x] = 'x';
        if (isKill(enemyField, x, y) == true) {
            cout << "Убил" << endl;
            return true;
        }
        else { 
            cout << "Ранил" << endl;
            return true;
        }
    }
    else if (enemyField[y][x] == 'o') cout << "Уже стреляли!" << endl; // скорее всего не нужно
    else cout << "Палуба уже пробита" << endl; // скорее всего не нужно


}
// проверка право - лево
int checkRightLeft(char** field, int &lastX, int &lastY, char &lastDirection) {
    // проверка вправо
    for (int x0 = lastX + 1; x0 <= lastX + 3; x0++) {
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == 'o') break;
        else if (field[lastY][x0] == '~') {
            field[lastY][x0] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == shipTest) {
            field[lastY][x0] = 'x';
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
    // проверка влево
    for (int x0 = lastX - 1; x0 >= lastX - 3; x0--) {
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == 'o') break;
        else if (field[lastY][x0] == '~') {
            field[lastY][x0] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == shipTest) {
            field[lastY][x0] = 'x';
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
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == 'o') break;
        else if (field[lastY][x0] == '~') {
            field[lastY][x0] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == shipTest) {
            field[lastY][x0] = 'x';
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
    // проверка вправо
    for (int x0 = lastX + 1; x0 <= lastX + 3; x0++) {
        if (x0 < 0 || x0 >= FIELD_SIZE || field[lastY][x0] == 'o') break;
        else if (field[lastY][x0] == '~') {
            field[lastY][x0] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[lastY][x0] == shipTest) {
            field[lastY][x0] = 'x';
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
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == 'o') break;
        else if (field[y0][lastX] == '~') {
            field[y0][lastX] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == shipTest) {
            field[y0][lastX] = 'x';
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
    // проверка вниз
    for (int y0 = lastY + 1; y0 <= lastY + 3; y0++) {
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == 'o') break;
        else if (field[y0][lastX] == '~') {
            field[y0][lastX] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == shipTest) {
            field[y0][lastX] = 'x';
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
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == 'o') break;
        else if (field[y0][lastX] == '~') {
            field[y0][lastX] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == shipTest) {
            field[y0][lastX] = 'x';
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
    //проверка вверх
    for (int y0 = lastY - 1; y0 >= lastY - 3; y0--) {
        if (y0 < 0 || y0 >= FIELD_SIZE || field[y0][lastX] == 'o') break;
        else if (field[y0][lastX] == '~') {
            field[y0][lastX] = 'o';
            cout << "соперник промазал" << endl;
            return 0;
        }
        else if (field[y0][lastX] == shipTest) {
            field[y0][lastX] = 'x';
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




bool enemyTurn(char** field , int &lastY, int &lastX, char &lastDirection) {
    cout << "ход соперника" << endl;
    int x;
    int y;
    int rnd;
    int test;
    cout << "LastDirection - " << lastDirection << endl;
    if (lastY != -1 && lastX != -1) {
        if (lastDirection == 'G') {
            rnd = random(1, 2);
            Sleep(1000);
            switch (rnd) {
            case 1:
                cout << "VAR G1" << endl;
                return optionRightTop(field, lastX, lastY, lastDirection);
                break;
            case 2:
                cout << "VAR G2" << endl;
                return optionLeftTop(field, lastX, lastY, lastDirection);
                break;
            }
        }
        else if (lastDirection == 'V') {
            rnd = random(1, 2);
            Sleep(1000);
            switch (rnd) {
            case 1:
                cout << "VAR V1" << endl;
                return optionTopRight(field, lastX, lastY, lastDirection);
                break;
            case 2:
                cout << "VAR V2" << endl;
                return optionDownLeft(field, lastX, lastY, lastDirection);
                break;
            }
        }
        else {
            rnd = random(1, 8);
            Sleep(1000);
            switch(rnd) {
                case 1:
                    cout << "VAR R1" << endl;
                    return optionRightTop(field, lastX, lastY, lastDirection);
                    break;
                case 2:
                    cout << "VAR R2" << endl;
                    return optionTopRight(field, lastX, lastY, lastDirection);
                    break;
                case 3:
                    cout << "VAR R3" << endl;
                    return optionLeftTop(field, lastX, lastY, lastDirection);
                    break;
                case 4:
                    cout << "VAR R4" << endl;
                    return optionTopLeft(field, lastX, lastY, lastDirection);
                    break;
                case 5:
                    cout << "VAR R5" << endl;
                    return optionLeftDown(field, lastX, lastY, lastDirection);
                    break;
                case 6:
                    cout << "VAR R6" << endl;
                    return optionDownLeft(field, lastX, lastY, lastDirection);
                    break;
                case 7:
                    cout << "VAR R7" << endl;
                    return optionRightDown(field, lastX, lastY, lastDirection);
                    break;
                case 8:
                    cout << "VAR R8" << endl;
                    return optionDownRight(field, lastX, lastY, lastDirection);
                    break;
            }
            
        }
    }
    else {
        //x = random(0, FIELD_SIZE - 1);
        //y = random(0, FIELD_SIZE - 1);
        char let;
        cout << "Введите координаты выстрела для врага: ";
        cin >> let >> y;
        x = int(let) - 65;
        y--;
        if (field[y][x] == '~') {
            field[y][x] = 'o';
            cout << "Соперник промахнулся" << endl;
            return false;
        }
        else if (field[y][x] == shipTest) {
            field[y][x] = 'x';
            if (isKill(field, x, y)) {
                cout << "Враг потопил ваш корабль" << endl;
                return true;
            }
            else {
                cout << "Враг попал в ваш корабль." << endl;
                lastX = x;
                lastY = y;
                return true;
            }
        }
        else if (field[y][x] == 'o') {
            cout << "Уже стреляли!" << endl;
            return true;
        }
        else {
            cout << "Палуба уже пробита" << endl; 
            return true;
        }
    }
}

void game(char** field, char** enemyField, char** hitField) {
    int turn = 0;
    int lastX = -1;
    int lastY = -1;
    char lastDirection = NULL; // V or G
    bool isHit;
    while (true) {
        if (turn % 2 == 0) {
            do { 
                
                system("cls");
                render(field);
                isHit = myTurn(enemyField, hitField); 
                //render(enemyField);
                //render(hitField);
                
            } while (isHit == true);

            
            turn++;


        }
        else {
            do {
                
                system("cls");
                render(field);
                isHit = enemyTurn(field, lastX, lastY, lastDirection);
               // render(enemyField);
                //render(hitField);
                
            } while (isHit == true);
            turn++;

        }
    }
}




int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int* shipCount = new int[4] { 1, 2, 3, 4 };
    int* enemyShipCount = new int[4] { 1, 2, 3, 4 };
    char** field = createField();
    char** enemyField = createField();
    char** hitField = createField();
    render(field);
    startInit(field, enemyField, shipCount, enemyShipCount);
    cout << "Начало!" << endl;
    render(hitField);
    render(field);
    game(field, enemyField, hitField);
    cout << "END";


    
}

