#include <ctype.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>

int main(int argc, char** argv)
{
    struct termios old;
    // int tty = open("/dev/tty1", 0);
    int            tty = 0;
    tcgetattr(tty, &old);

    struct termios n;
    memcpy(&n, &old, sizeof(struct termios));
    n.c_lflag &= ~ICANON;
    n.c_lflag &= ~ECHO;
    tcsetattr(tty, TCSANOW, &n);

    if (argc > 1) printf("\e[?1%c", argv[1][0]);
    char c;
    bool escape   = false;
    bool nextchar = false;

    printf("START\n");
    while ((c = getchar()))
    {
        if (nextchar)
        {
            printf("\e[%c", c);
            nextchar = false;
            escape   = false;
        }
        else if (escape && c == '[') nextchar = true;
        else if (c == '\e') escape = true;
        else if (c == '\t') break;

        if (isprint(c)) printf("c: %c", c);
        else printf("c: %#x", c);
        printf("\n");
    }
    printf("END\n");

    printf("\e[?1l");
    tcsetattr(tty, TCSANOW, &old);
}
