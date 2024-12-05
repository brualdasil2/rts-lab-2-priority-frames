#ifndef VECTOR_H
#define VECTOR_H

#include <stdlib.h>

typedef struct s_vector {
    int size;
    char* data;
} vector;

typedef enum e_vec_status {
    VEC_OK,
    VEC_ERROR
} vec_status;

vec_status create_vector(vector* vec_ptr, int initial_size, size_t data_size);

vec_status write_vector(vector* vec_ptr, int index, char* data, size_t data_size);

#endif // VECTOR_H