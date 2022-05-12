#include <stdio.h>
#include "termcolor-c.h"
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

void outputAmino(char c) {

    if (c >= 'a' && c <= 'z')
        c += 'A' - 'a';

    if (c < 'A' || c > 'Z') {
        reset_colors(stdout);
        fputc(c, stdout);
        return;
    }

    switch (c) {
        // ASP/GLU - bright red
        case 'D': case 'E':
            putc(c, background_white(text_red(stdout)));
            break;

            // CYS/MET - yellow
        case 'C': case 'M':
            putc(c, background_yellow(text_grey(stdout)));
            break;

            // LYS/ARG - blue
        case 'K': case 'R':
            putc(c, background_blue(text_white(stdout)));
            break;

            // SER/THR - orange
        case 'S': case 'T':
            putc(c, background_yellow(text_red(stdout)));
            break;

            // PHE/TYR - dark blue
        case 'F': case 'Y':
            putc(c, background_blue(text_red(stdout)));
            break;

            // ASN/GLN -  cyan
        case 'N': case 'Q':
            putc(c, background_cyan(text_grey(stdout)));
            break;

            // GLY - light grey
        case 'G':
            putc(c, background_white(text_grey(stdout)));
            break;

            // LEU/VAL/ILE - green
        case 'L': case 'V': case 'I':
            putc(c, background_green(text_grey(stdout)));
            break;

            // ALA - dark grey
        case 'A':
            putc(c, background_grey(text_white(stdout)));
            break;

            // TRP - purple
        case 'W':
            putc(c, background_magenta(text_grey(stdout)));
            break;

            // HIS - pale blue
        case 'H':
            putc(c, background_white(text_blue(stdout)));
            break;

            // PRO - flesh
        case 'P':
            putc(c, background_grey(text_white(stdout)));
            break;

        default: // tan
            reset_colors(stdout);
            fputc(c, stdout);
            break;
    }

}

#define NORMAL_LINE 0
#define HEADER_LINE 1
#define HEADER_META 2
#define COMMENT_LINE 3
int main() {


    int state = NORMAL_LINE;

    char c = getc(stdin);

    while (c != EOF) {
        if (state == NORMAL_LINE) {
            if (c == '>')
                state = HEADER_LINE;
            if (c == ';')
                state = COMMENT_LINE;
        }

        if (c == '\n') {
            reset_colors(stdout);
            state = NORMAL_LINE;
        }

        if (state == NORMAL_LINE)
            outputAmino(c);

        if (state == COMMENT_LINE)
            putc(c, background_grey(text_white(stdout)));

        if (state == HEADER_LINE) {
            if (isalnum(c) || c == '_' || c=='-' || c == '>') {
                putc(c, background_white(text_grey(text_bold(stdout))));
            }

            else {
                state = HEADER_META;
                reset_colors(stdout);
            }
        }

        if (state == HEADER_META) {
            putc(c, background_grey(text_white(stdout)));
        }

        c = getc(stdin);
    }

    return 0;
}
