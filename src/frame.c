#include "frame.h"
#include "stdio.h"

void print_frame(frame f) {
    char type_char;
    switch (f.type) {
        case TYPE_I:
            type_char = 'I';
            break;
        case TYPE_P:
            type_char = 'P';
            break;
        case TYPE_B:
            type_char = 'B';
            break;
    }
    printf("%c (%d) - %d\n", type_char, f.size, f.priority);
}