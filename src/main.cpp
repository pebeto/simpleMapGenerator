#include <iostream>
#include <ncurses.h>

void initCurses(){
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
}

char tileSelector(){
    int seed = rand() % 100;
    if(seed <= 90)
        return '#';
    return '&';
}

void printColoredTile(int x, int y, char tile){
    switch(tile){
        case '#':
            attron(COLOR_PAIR(1));
                mvprintw(x, y, "%c", tile);
            attroff(COLOR_PAIR(1));
            break;
        case '&':
            attron(COLOR_PAIR(2));
                mvprintw(x, y, "%c", tile);
            attroff(COLOR_PAIR(2));
            break;
        default:
            attron(COLOR_PAIR(3));
            mvprintw(x,y, "%c", tile);
            attroff(COLOR_PAIR(3));
    }
}

void randomGeneration(char **mapa, int x, int y, long n){
    if(n == 0)
        return;
    int seed = rand() % 4;
    switch(seed){
        case 0:
            x++;
            if(x == LINES)
                x--;
            break;
        case 1:
            x--;
            if(x < 0)
                x++;
            break;
        case 2:
            y++;
            if(y == COLS)
                y--;
            break;
        case 3:
            y--;
            if(y < 0)
                y++;
            break;
    }
    mapa[x][y] = tileSelector();
    randomGeneration(mapa, x, y, --n);
}

void printWorldMap(char **mapa){
    for(int i = 0; i < LINES; i++){
        for(int j = 0; j < COLS; j++){
            if(mapa[i][j] != '#' && mapa[i][j] != '&')
                mapa[i][j] = '~';
            printColoredTile(i, j, mapa[i][j]);
        }
    }
}

int main(int argc, char *argv[]){
    if (argc <= 1) {
        printf("%s\n", "not enough arguments");
        return 0;
    }

    srand(time(NULL));
    initCurses();

    char **mapa = new char*[LINES];
    for(int i = 0; i < LINES; i++)
        mapa[i] = new char[COLS];

    randomGeneration(mapa, LINES/2, COLS/2, std::stol(argv[1]));
    printWorldMap(mapa);
    mvprintw(0, 0, "%s %d %d", "Terminal size: ", LINES, COLS);
    refresh();
    getch();
    endwin();
    return 0;
}
