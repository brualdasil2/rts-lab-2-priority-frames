#ifndef FRAME_H
#define FRAME_H

#define UNASSIGNED -1

typedef enum e_frame_type {
    TYPE_I,
    TYPE_P,
    TYPE_B
} frame_type;

typedef struct s_frame {
    frame_type type;
    int size;
    int priority;
} frame;

void print_frame(frame f);

#endif // FRAME_H

