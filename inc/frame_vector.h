#ifndef FRAME_VECTOR_H
#define FRAME_VECTOR_H

#include "vector.h"
#include "frame.h"

vec_status add_frame_to_vector(vector* vec_ptr, int index, frame f);

frame get_frame_from_index(vector* vec_ptr, int index);

#endif // FRAME_VECTOR_H