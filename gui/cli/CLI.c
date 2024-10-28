#include "CLI.h"

int render(GameInfo_t *gameInfo, int code) {
    DeleteStartBanner();
    DeleteGameOver();

    if (gameInfo->field) {
        DrawingGameFieldBorders((const int **)gameInfo->field);
        PrintGameField((const int **)gameInfo->field);
    }

    if (code == 1 || code == 2 || code == 3) {
        if (code == 3) {
            DrawingWinBanner();
            refresh();
            napms(1500);
            endwin();
            return 0;
        }

        if (code == 2) DrawingGameOver();

        DrawingStartBanner();
    }

    if (gameInfo->pause)
        DrawPause();
    else
        DeletePause();

    if (gameInfo->next) {
        DrawingNextFigureField();
        DrawingNextFigure((const int **)gameInfo->next);
    }

    if (gameInfo->high_score != -1) DrawingHighScore(gameInfo->high_score);

    if (gameInfo->score != -1) DrawingScore(gameInfo->score);

    if (gameInfo->level != -1) DrawingLevel(gameInfo->level);

    return 1;
}

void PrintGameField(const int **field) {
    attrset(A_BOLD);

    int color = 0;
    int height = field[0][0] - 1;
    int width = field[1][0] - 1;

    wchar_t block = L'\U0001F793';

    for (int i = 0; i < height; i++)
        for (int j = 1; j < width; j++) {
            color = GetColor(field[i][j]);

            attron(COLOR_PAIR(color));

            if (field[i][j] >= '*')
                mvprintw(i, j * 3, "%lc", block);
            else
                mvprintw(i, j * 3, "%c", ' ');

            attroff(COLOR_PAIR(color));
        }

    attroff(A_BOLD);
}

void print_rectangle(int top_y, int bottom_y, int left_x, int right_x) {
    MVADDCH(top_y, left_x, ACS_ULCORNER);

    int i = left_x + 1;

    for (; i < right_x; i++) MVADDCH(top_y, i, ACS_HLINE);

    MVADDCH(top_y, i, ACS_URCORNER);

    for (int i = top_y + 1; i < bottom_y; i++) {
        MVADDCH(i, left_x, ACS_VLINE);
        MVADDCH(i, right_x, ACS_VLINE);
    }

    MVADDCH(bottom_y, left_x, ACS_LLCORNER);

    i = left_x + 1;

    for (; i < right_x; i++) MVADDCH(bottom_y, i, ACS_HLINE);

    MVADDCH(bottom_y, i, ACS_LRCORNER);
}

void DrawingGameFieldBorders(const int **field) {
    int height = field[0][0];

    attrset(A_BOLD);
    print_rectangle(-3, height - 3, 0, 30);
    attroff(A_BOLD);
}

void DrawingGameOver() {
    int color = 1;

    attrset(A_BOLD);

    PrintColorStr(4, 12, "GAME OVER", color);

    attroff(A_BOLD);
}

void DeleteGameOver() { mvprintw(4, 9, "%s", "               "); }

void PrintColorStr(int x, int y, const char *string, int color) {
    attron(COLOR_PAIR(color));

    mvprintw(x, y, "%s", string);

    attroff(COLOR_PAIR(color));
}

void PrintColorWc(int x, int y, wchar_t symbol, int color) {
    attron(COLOR_PAIR(color));

    mvprintw(x, y, "%lc", symbol);

    attroff(COLOR_PAIR(color));
}

void DrawingStartBanner() {
    int color = 2;

    attrset(A_BOLD);

    PrintColorStr(6, 7, "Click", 0);

    PrintColorStr(6, 13, "ENTER", color);

    PrintColorStr(6, 18, " for start", 0);

    attroff(A_BOLD);
}

void DeleteStartBanner() {
    for (int i = 6; i < 19; i++) mvprintw(i, 7, "%s", "                    ");
}

void DrawPause() {
    attrset(A_BOLD);

    print_rectangle(17, 20, 34, 55);

    PrintColorStr(20, 38, "PAUSE ", 1);

    PrintColorWc(20, 44, 0, 0);

    attroff(A_BOLD);
}

void DeletePause() {
    for (int i = 19; i < 23; i++)
        mvprintw(i, 34, "%s", "                         ");
}

void DrawingWinBanner() {
    attrset(A_BOLD);
    PrintColorStr(8, 13, "YOU WIN!", 3);
    attroff(A_BOLD);
}

void DrawingNextFigureField() {
    attrset(A_BOLD);

    print_rectangle(-2, 4, 34, 55);

    PrintColorStr(1, 38, "NEXT", 3);

    attroff(A_BOLD);
}

void DrawingHighScore(int high_score) {
    attrset(A_BOLD);

    print_rectangle(5, 8, 34, 55);

    PrintColorStr(8, 38, "HIGHSCORE", 5);

    mvprintw(9, 55, "%d", high_score);

    attroff(A_BOLD);
}

void DrawingScore(int score) {
    attrset(A_BOLD);

    mvprintw(13, 53, "%s", "          ");

    print_rectangle(9, 12, 34, 55);

    PrintColorStr(12, 38, "SCORE", 4);

    mvprintw(13, 55, "%d", score);

    attroff(A_BOLD);
}

void DrawingLevel(int level) {
    attrset(A_BOLD);

    mvprintw(17, 55, "%s", "   ");

    print_rectangle(13, 16, 34, 55);

    PrintColorStr(16, 38, "LEVEL", 1);

    mvprintw(17, 55, "%d", level);

    attroff(A_BOLD);
}

void DrawingNextFigure(const int **field) {
    int sym = 0;
    int next = field[0][4];
    int color = field[0][5];

    attrset(A_BOLD);
    attron(COLOR_PAIR(color));

    wchar_t wc = L'\0';

    for (int i = 0; i < 2; i++)
        for (int j = 0; j < 4; j++) {
            sym = field[i + 2][j];

            if (!sym)
                wc = L' ';
            else
                wc = L'\U0001F793';

            mvprintw(i + 3, j * 3 + 43, "%lc", wc);
        }

    attroff(COLOR_PAIR(color));
    attroff(A_BOLD);
}

int GetColor(int symbol) {
    return symbol >= '*' ? symbol - '*' : 0;
}

void ncursesInit() {
    initscr();

    InitColors();

    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);
    keypad(stdscr, TRUE);
    curs_set(0);
}

void InitColors() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
}