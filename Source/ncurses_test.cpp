/*
 * Created by v1tr10l7 on 19.09.2025.
 * Copyright (c) 2024-2025, Szymon Zemke <v1tr10l7@proton.me>
 *
 * SPDX-License-Identifier: GPL-3
 */
#include <ncurses.h>
#include <stdio.h>

int main(void)
{
    int ch;

    // Initialize ncurses
    initscr();            // start ncurses mode
    raw();                // disable line buffering, pass keys straight through
    keypad(stdscr, TRUE); // enable function keys & arrows
    noecho();             // don't echo typed characters

    printw("Press arrow keys (↑ ↓ ← →), or 'q' to quit.\n");
    refresh();

    while ((ch = getch()) != 'q')
    {
        switch (ch)
        {
            case KEY_UP: printw("Up arrow pressed\n"); break;
            case KEY_DOWN: printw("Down arrow pressed\n"); break;
            case KEY_LEFT: printw("Left arrow pressed\n"); break;
            case KEY_RIGHT: printw("Right arrow pressed\n"); break;
            default: printw("Key code: %d\n", ch); break;
        }
        refresh();
    }

    // Cleanup
    endwin();
    return 0;
}
