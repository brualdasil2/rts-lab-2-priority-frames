#include "priority.h"
#include <stdio.h>
#include <string.h>

#define INITIAL_BLOCK_RADIUS 2
#define BLOCK_RADIUS_DECREMENT 1
#define ALL_B_BLOCKED -1

blocked_status get_blocked_from_index(vector* vec_ptr, int index) {
    blocked_status b;
    memcpy(&b, vec_ptr->data + index*sizeof(blocked_status), sizeof(blocked_status));
    return b;
}

int get_biggest_unblocked_b_index(vector* frame_vec, vector* blocked_vec) {
    frame f;
    blocked_status b;
    int biggest_size = -1;
    int biggest_index;
    char found_unblocked_b = 0;
    for (int i = 0; i < frame_vec->size; i++) {
        f = get_frame_from_index(frame_vec, i);
        if (f.type != TYPE_B) {
            continue;
        }
        // f is type B, is it blocked?
        b = get_blocked_from_index(blocked_vec, i);
        if (b.is_blocked) {
            continue;
        }
        // f is type B and unblocked. Is it the current biggest?
        if (f.size <= biggest_size) {
            continue;
        }
        // f is type B, unblocked and the current biggest
        biggest_size = f.size;
        biggest_index = i;
        found_unblocked_b = 1;
    }
    if (!found_unblocked_b) {
        return ALL_B_BLOCKED;
    }
    return biggest_index;
}

void unblock_if_not_source(vector* blocked_vec, int index) {
    blocked_status b;
    if (index < 0) {
        return;
    }
    if (index > blocked_vec->size) {
        return;
    }
    b = get_blocked_from_index(blocked_vec, index);
    if (b.is_source) {
        return;
    }
    // b is not source, unblock it
    b.is_blocked = 0;
    b.is_source = 0;
    write_vector(blocked_vec, index, (char*) &b, sizeof(blocked_status));
}


// Returns new block radius
int reduce_block_radius(vector* blocked_vec, int block_radius) {
    blocked_status b;
    int block_decrement = BLOCK_RADIUS_DECREMENT > block_radius ? block_radius : BLOCK_RADIUS_DECREMENT;
    for (int i = 0; i < blocked_vec->size; i++) {
        b = get_blocked_from_index(blocked_vec, i);
        if (!b.is_source) {
            continue;
        }
        // b is a block source
        // would break if decrement > radius
        // unblock not sources on low edge of radius
        for (int j = i-block_radius; j < i-block_radius+block_decrement; j++) {
            unblock_if_not_source(blocked_vec, j);
        }
        // unblock not sources on high edge of radius
        for (int j = i+block_radius; j > i+block_radius-block_decrement; j--) {
            unblock_if_not_source(blocked_vec, j);
        }
    }
    return block_radius - block_decrement;
}

void block_b(vector* blocked_vec, int index) {
    blocked_status b;
    b = get_blocked_from_index(blocked_vec, index);
    b.is_blocked = 1;
    write_vector(blocked_vec, index, (char*) &b, sizeof(blocked_status));
}

void block_around_index(vector* blocked_vec, int index, int block_radius) {
    blocked_status b;
    b.is_blocked = 1;
    b.is_source = 1;
    write_vector(blocked_vec, index, (char*) &b, sizeof(blocked_status));
    // block low edge of radius
    for (int i = index-block_radius; i < index; i++) {
        block_b(blocked_vec, i);
    }
    // block high edge of radius
    for (int i = index+block_radius; i > index; i--) {
        block_b(blocked_vec, i);
    }
}

void assign_priorities(vector* frame_vec) {
    vector blocked_vec;
    vec_status res;
    frame f;
    int block_radius = INITIAL_BLOCK_RADIUS;
    int curr_priority = 0;
    int biggest_b_index;
    
    res = create_vector(&blocked_vec, frame_vec->size, sizeof(blocked_status));
    if (res == VEC_ERROR) {
        printf("Error creating blocked vector\n");
        return;
    }
    // Initialize blocked_vec data with not blocked and not source
    memset(blocked_vec.data, 0, blocked_vec.size*sizeof(blocked_status));

    // Priority for B frames
    while (1) {
        biggest_b_index = get_biggest_unblocked_b_index(frame_vec, &blocked_vec);
        if (biggest_b_index == ALL_B_BLOCKED) {
            if (block_radius == 0) {
                // radius is 0 and all B are blocked, all Bs were assigned
                break;
            }
            block_radius = reduce_block_radius(&blocked_vec, block_radius);
            continue;
        }
        // we have a b index, lets assign a priority to it and block around the radius
        f = get_frame_from_index(frame_vec, biggest_b_index);
        f.priority = curr_priority;
        curr_priority++;
        add_frame_to_vector(frame_vec, biggest_b_index, f);
        block_around_index(&blocked_vec, biggest_b_index, block_radius);
    }

}