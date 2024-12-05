#include "vector.h"
#include <string.h>

vec_status create_vector(vector* vec_ptr, int initial_size, size_t data_size) {
    vec_ptr->size = initial_size;
    vec_ptr->data = (char*) malloc(data_size*initial_size);
    if (vec_ptr->data == NULL) {
        return VEC_ERROR;
    }
    return VEC_OK;
}

vec_status write_vector(vector* vec_ptr, int index, char* data, size_t data_size) {
    if (index >= vec_ptr->size) {
        return VEC_ERROR;
    }
    memcpy(vec_ptr->data + index*data_size, data, data_size);
    return VEC_OK;
}