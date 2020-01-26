#ifndef STRUCT_H
#define STRUCT_H

/**
 * MACRO: define_struct_set_string(struct, member, struct_param, char_param)
 *
 * Simple macro to simplify a common pattern of writing setter functions for
 * potentially uninitialized members. 
 *
 * This defines a function which, if the member is uninitialized, allocates 
 * the signing_key field, and takes an optional char* to set the newly allocated field to. 
 *
 * If NULL is passed, only allocation occurs. 
 *
 * The macro will substitute struct as the struct type being used (e.g. animal),
 * member with the name of the member being allocated/modified (e.g. name), struct_param
 * with the name of the struct parameter (e.g. anim), and char_param with the name
 * of the char* parameter (e.g. n).
 */
#define define_struct_set_string(struct, member, struct_param, char_param) void struct##_set_##member(struct* struct_param, const char* tmpl) { \
    free(struct_param->member); \
    struct_param->member = safemalloc(strlen(char_param) + 1); \
    if(char_param) { \
        strcpy(struct_param->member, char_param); \
    } \
}

/**
 * MACRO: declare_struct_set_string(struct, member, struct_param, char_param)
 *
 * Simple macro which declares the function defined with define_struct_set_string.
 */
#define declare_struct_set_string(struct, member, struct_param, char_param) void struct##_set_##member(struct* struct_param, const char* tmpl);

#endif
