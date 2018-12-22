#include <iostream>
#include <ncurses.h>

void initCurses(){
    initscr();
    raw();
    keypad(stdscr, TRUE);
    noecho();

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_CYAN, COLOR_BLACK);
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
            attron(COLOR_PAIR(3));
            mvprintw(x, y, "%c", tile);
            attroff(COLOR_PAIR(3));
            break;
    }

}

void randomGeneration(int x, int y, long n){
    if(n == 0)
        return;
    int seed = rand() % 4;
    char tile;
    switch(seed){
        case 0:
            if(x != LINES)
                x--;
            else
                x++;
            tile = tileSelector();
            printColoredTile(x, y, tile);
            break;
        case 1:
            if(x != LINES)
                x++;
            else
                x--;
            tile = tileSelector();
            printColoredTile(x, y, tile);
            break;
        case 2:
            if(x != LINES)
                y--;
            else
                y++;
            tile = tileSelector();
            printColoredTile(x, y, tile);
            break;
        case 3:
            if(x != LINES)
                y++;
            else
                y--;
            tile = tileSelector();
            printColoredTile(x, y, tile);
            break;
    }
    randomGeneration(x, y, n -1);
}

int main(int argc, char *argv[]){
    srand(time(NULL));
    initCurses();
    randomGeneration(LINES/2, COLS/2, std::stol(argv[1]));
    refresh();
    getch();
    endwin();
    return 0;
}
