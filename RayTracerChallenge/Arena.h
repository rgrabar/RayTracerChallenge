#pragma once

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

bool is_power_of_two(uintptr_t x);

uintptr_t align_forward(uintptr_t ptr, size_t align);

#ifndef DEFAULT_ALIGNMENT
#define DEFAULT_ALIGNMENT (2*sizeof(void *))
#endif

typedef struct Arena Arena;
struct Arena {
	unsigned char* buf = nullptr;
	size_t         buf_len;
	size_t         prev_offset; // This will be useful for later on
	size_t         curr_offset;
};

void arena_init(Arena* a, void* backing_buffer, size_t backing_buffer_length);

void* arena_alloc_align(Arena* a, size_t size, size_t align);

// Because C doesn't have default parameters
void* arena_alloc(Arena* a, size_t size);

void arena_free(Arena* a, void* ptr);
void* arena_resize_align(Arena* a, void* old_memory, size_t old_size, size_t new_size, size_t align);

// Because C doesn't have default parameters
void* arena_resize(Arena* a, void* old_memory, size_t old_size, size_t new_size);

void arena_free_all(Arena* a);