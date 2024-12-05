#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "frame.h"
#include "frame_vector.h"

int main() {

    vector frame_vec;
    vec_status res;
    frame f;

    res = create_vector(&frame_vec, 5, sizeof(frame));
    if (res == VEC_ERROR) {
        printf("Error creating vector\n");
        return 0;
    }
    f.size = 200;
    f.type = TYPE_I;
    add_frame_to_vector(&frame_vec, 0, f);
    f.size = 120;
    f.type = TYPE_P;
    add_frame_to_vector(&frame_vec, 1, f);
    f.size = 80;
    f.type = TYPE_B;
    add_frame_to_vector(&frame_vec, 2, f);
    f.size = 70;
    f.type = TYPE_B;
    add_frame_to_vector(&frame_vec, 3, f);
    f.size = 110;
    f.type = TYPE_P;
    add_frame_to_vector(&frame_vec, 4, f);
    
    for (int i = 0; i < frame_vec.size; i++) {
        f = get_frame_from_index(&frame_vec, i);
        print_frame(f);
    }

    return 0;
}