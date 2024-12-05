#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vector.h"
#include "frame.h"
#include "frame_vector.h"
#include "priority.h"

#define FRAME_VEC_SIZE 20
#define MAX_FRAME_SIZE 1000
#define B_TO_P_PROPORTION 5

int random_size() {
    return (rand()%MAX_FRAME_SIZE) + 1;
}

frame_type random_type() {
    if (rand()%B_TO_P_PROPORTION == 0) {
        return TYPE_P;
    }
    return TYPE_B;
}

vec_status generate_frame_vector(vector* frame_vec, int size) {
    frame f;
    vec_status res;

    res = create_vector(frame_vec, size, sizeof(frame));
    if (res == VEC_ERROR) {
        return res;
    }

    f.size = MAX_FRAME_SIZE;
    f.type = TYPE_I;
    f.priority = UNASSIGNED;
    add_frame_to_vector(frame_vec, 0, f);
    for (int i = 1; i < size; i++) {
        f.size = random_size();
        f.type = random_type();
        // priority stays UNASSIGNED
        add_frame_to_vector(frame_vec, i, f);
    }
    return res;
}

int main() {
    srand(time(NULL));
    vec_status res;
    vector frame_vec;
    frame f;
    res = generate_frame_vector(&frame_vec, FRAME_VEC_SIZE);
    if (res == VEC_ERROR) {
        printf("Error creating vector\n");
        return 0;
    }
    
    assign_priorities(&frame_vec);

    for (int i = 0; i < frame_vec.size; i++) {
        f = get_frame_from_index(&frame_vec, i);
        print_frame(f);
    }

    return 0;
}