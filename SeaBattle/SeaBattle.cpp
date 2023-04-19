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
bool isKill(char** enemyField, char** hitField, int x, int y) {
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
                        hitField[y0][x0] = 'o';
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
                        hitField[y0][x0] = 'o';
                    }
                }
            }
            return true;
        }
        else return false;
        
    }
}

// Проверка попадания. Убил, ранил, промазал.
void myTurn(char** enemyField, char** hitField) {
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
    }
    else if (enemyField[y][x] == shipTest) {
        enemyField[y][x] = 'x';
        hitField[y][x] = 'x';
        if (isKill(enemyField, hitField, x, y) == true) {
            cout << "Убил" << endl;
        }
        else cout << "Ранил" << endl;
    }
    else if (enemyField[y][x] == 'o') cout << "Уже стреляли!" << endl;
    else cout << "Палуба уже пробита" << endl;


}

void enemyTurn(char** field) {
    cout << "ход соперника" << endl;
    int a;
    cin >> a;
}

void game(char** field, char** enemyField, char** hitField) {
    int turn = 0;
    while (true) {
        if (turn % 2 == 0) {

            myTurn(enemyField, hitField);
            render(enemyField);
            render(hitField);

            render(field);

            turn++;


        }
        else {

            enemyTurn(field);
            render(enemyField);
            render(hitField);
            render(field);
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

