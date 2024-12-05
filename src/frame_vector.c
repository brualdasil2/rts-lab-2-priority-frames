#include "frame_vector.h"
#include "string.h"

vec_status add_frame_to_vector(vector* vec_ptr, int index, frame f) {
    return write_vector(vec_ptr, index, (char*)(&f), sizeof(frame));
}

frame get_frame_from_index(vector* vec_ptr, int index) {
    frame f;
    memcpy(&f, vec_ptr->data + index*sizeof(frame), sizeof(frame));
    return f;
}
