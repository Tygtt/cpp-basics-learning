#include <iostream>
#include <conio.h>
#include <random>
#include <windows.h>

using namespace std;

const int HEIGHT = 7;
const int WIDTH = 15;

int scor = 0;
char key;

// الماب
char map[HEIGHT][WIDTH] = {
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
    {'#','.','.','.','.','#','.','.','.','.','.','#','.','E','#'},
    {'#','.','#','#','.','#','.','#','#','#','.','#','.','.','#'},
    {'#','.','#','.','.','.','.','.','.','#','.','.','.','#','#'},
    {'#','.','#','.','#','#','#','#','.','#','#','#','.','.','#'},
    {'#','P','.','.','.','.','.','#','.','.','.','.','.','.','#'},
    {'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};

// رسم الماب
void drawMap() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            cout << map[i][j];
        }
        cout << endl;
    }
}

// Spawn عشوائي لـ E
void spawnExit() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> h(1, HEIGHT - 2);
    uniform_int_distribution<> w(1, WIDTH - 2);

    int x, y;
    do {
        x = h(gen);
        y = w(gen);
    } while (map[x][y] != '.');

    map[x][y] = 'E';
}

// تحكم اللاعب
void control() {
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (map[i][j] == 'P') {

                int ni = i, nj = j;

                if (key == 'w' || key == 'W') ni--;
                if (key == 's' || key == 'S') ni++;
                if (key == 'a' || key == 'A') nj--;
                if (key == 'd' || key == 'D') nj++;

                // حماية من الخروج عن المصفوفة
                if (ni < 0 || ni >= HEIGHT || nj < 0 || nj >= WIDTH)
                    return;

                if (map[ni][nj] == '#')
                    return;

                if (map[ni][nj] == 'E') {
                    scor++;
                    spawnExit();
                }

                map[i][j] = '.';
                map[ni][nj] = 'P';
                return;
            }
        }
    }
}

int main() {
    while (true) {
        system("cls");
        cout << "SCOR: " << scor << "\n\n";
        drawMap();

        key = _getch();
        control();
    }
}
