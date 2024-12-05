#ifndef FRAME_H
#define FRAME_H

typedef enum e_frame_type {
    TYPE_I,
    TYPE_P,
    TYPE_B
} frame_type;

typedef struct s_frame {
    frame_type type;
    int size;
} frame;

void print_frame(frame f);

#endif // FRAME_H

