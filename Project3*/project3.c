/*
 * Copy the contents of header.txt (filled out) and paste here
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "utstring.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
bool isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return true; }
    else { return false; }
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {
    UTString* a = malloc(sizeof(UTString));
    a -> length = strlen(src);
    a -> capacity = strlen(src);
    a -> string = malloc(sizeof(char) * (strlen(src) + 5));
    //a -> string = malloc(sizeof(char) * strlen(src) + 5);
    char* b = a -> string;
    for (int i = 0; i < strlen(src); i++){
        b[i] = src[i];
    }
    CHECK(a) = SIGNATURE;
    return a;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    assert(isOurs(s));
    return s -> length;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    assert(isOurs(s));
    uint32_t cap = s-> capacity;
    uint32_t len = s -> length;
    char *b = s ->string;
    int count = 0;
    int i = len;
    while(i < cap && suffix[count]){
        b[i] = suffix[count];
        count++;
        i++;
    }
//    for( int i = len; i < cap; i++){
//        if(suffix[count]){
//            b[i] = suffix[count];
//            count++;
//        }
//    }
    s -> length = len + count;
    s-> string[s->length] = '\0';
    CHECK(s) = SIGNATURE;
    return s;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    assert(isOurs(dst));
    uint32_t cap = dst-> capacity;
    char *b = dst ->string;
    int count = 0;
    for( int i = 0; i < cap; i++){
        if(src[i]){
            b[i] = src[i];
            count++;
        }
    }
    //CHECK(dst) = SIGNATURE;
    dst -> length = count;
    dst-> string[dst->length] = '\0';
    CHECK(dst) = SIGNATURE;
    return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    assert(isOurs(self));
    free(self->string);
    free(self);
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    assert(isOurs(s));
    uint32_t current_cap = s-> capacity;
    char* str = s-> string;
    if(current_cap < new_capacity){
        str = realloc(str, new_capacity + sizeof(char)*5);
        s -> string = str;
        s-> capacity = new_capacity;
    }
    CHECK(s) = SIGNATURE;
    return s;
}
