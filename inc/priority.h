#ifndef PRIORITY_H
#define PRIORITY_H

#include "frame.h"
#include "frame_vector.h"
#include "vector.h"

typedef struct s_blocked_frame_status {
    char is_blocked;
    char is_source;
} blocked_status;

void assign_priorities(vector* frame_vec);

#endif // PRIORITY_H