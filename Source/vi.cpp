#include <cstdio>

#include <ncurses.h>

int  g_StatusBarAttributtes = 0;
int  g_RulerAttributes      = 0;

void draw()
{
    clear();
    clrtoeol();
    attron(A_BOLD);
    addstr(":D");
    attroff(A_BOLD);

    refresh();
}

int main()
{
    initscr();
    start_color();
    use_default_colors();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, -1);

    g_StatusBarAttributtes = COLOR_PAIR(1);
    g_RulerAttributes      = COLOR_PAIR(2);

    raw();
    keypad(stdscr, true);
    timeout(10);
    noecho();
    refresh();
    bool shouldQuit = false;
    while (!shouldQuit)
    {
        draw();
        int ch = getch();
        if (ch == ERR) continue;

        if (ch == 'q') shouldQuit = true;
    }

    endwin();

    printf("Hello, World!\n");

    return 0;
}
