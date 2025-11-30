#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define MINX 2
#define MINY 2
#define MAXX 35
#define MAXY 20

using namespace std;
const int WIDTH = 40;   // chiều rộng khung
const int HEIGHT = 20;  // chiều cao khung

void gotoxy(int column, int line);

struct Point {
    int x, y;
};

class CONRAN {
public:
    Point A[200];
    int DoDai;

    CONRAN() {
        DoDai = 3;
        A[0] = {10, 10};
        A[1] = {11, 10};
        A[2] = {12, 10};
    }

    void XoaDuoi() {
        gotoxy(A[DoDai - 1].x, A[DoDai - 1].y);
        cout << " ";
    }

    void Ve(Point Qua) {
        // vẽ rắn
        for (int i = 0; i < DoDai; i++) {
            gotoxy(A[i].x, A[i].y);
            cout << "O";
        }

        // vẽ quả
        gotoxy(Qua.x, Qua.y);
        cout << "*";
    }

    void DiChuyen(int Huong, Point &Qua) {
        XoaDuoi();

        // dời thân rắn
        for (int i = DoDai - 1; i > 0; i--)
            A[i] = A[i - 1];

        // di chuyển đầu
        if (Huong == 0) A[0].x++;
        if (Huong == 1) A[0].y++;
        if (Huong == 2) A[0].x--;
        if (Huong == 3) A[0].y--;

        // kiểm tra ăn quả
        if (A[0].x == Qua.x && A[0].y == Qua.y) {
            DoDai++;
            Qua.x = rand() % (MAXX - MINX - 1) + MINX + 1;
            Qua.y = rand() % (MAXY - MINY - 1) + MINY + 1;
        }
    }
};

void VeKhung() {
    for (int i = MINX; i <= MAXX; i++)
        for (int j = MINX; j <= MAXY; j++)
            if ((i == MINX) || (i == MAXX) || (j == MINY) || (j == MAXY)) {
                gotoxy(i, j);
                printf("+");
            }
// Hàm vẽ 1 dòng ký tự
void drawLine(char c) {
    for (int i = 0; i < WIDTH; i++)
        cout << c;
    cout << endl;
}

// Hàm vẽ khung rỗng bên trong
void drawFrame() {
    // Vẽ hàng trên
    drawLine('#');

    // Vẽ thân khung
    for (int i = 0; i < HEIGHT; i++) {
        cout << "#";                        // biên trái
        for (int j = 0; j < WIDTH - 2; j++)
            cout << " ";                    // phần rỗng bên trong
        cout << "#";                        // biên phải
        cout << endl;
    }

    // Vẽ hàng dưới
    drawLine('#');
}

int main() {
    CONRAN r;
    int Huong = 0;
    char t;
    Point Qua;

    srand((int)time(0));

    Qua.x = rand() % (MAXX - MINX - 1) + MINX + 1;
    Qua.y = rand() % (MAXY - MINY - 1) + MINY + 1;

    while (1) {
        if (kbhit()) {
            t = getch();
            if (t == 'a') Huong = 2;
            if (t == 'w') Huong = 3;
            if (t == 'd') Huong = 0;
            if (t == 's') Huong = 1;
        }

        system("cls");

        VeKhung();
        r.Ve(Qua);
        r.DiChuyen(Huong, Qua);

        Sleep(150);
    }
     cout << "=== KHUNG GAME SNAKE ===" << endl << endl;
    drawFrame();

    return 0;
}

void gotoxy(int column, int line) {
    COORD coord;
    coord.X = column;
    coord.Y = line;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
