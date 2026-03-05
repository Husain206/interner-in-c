#ifndef INTERNER_H
#define INTERNER_H

#include <stddef.h>
#include <stdint.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

/*
*
* fixed size(for now) string interner in c
*
*/

typedef struct couple {
  uint16_t len;
  int id;
} couple;

typedef struct intern{
  char** arr;
  int count;
  int cap;
  couple* pool;
} intern;


// static void init_interner(intern* it){
//     it->count = 0;
//   for(int i = 0; i < MAX_SIZE; i++){
//     it->arr[i] = NULL;
//     it->pool[i].name = NULL;
//     it->pool[i].id = -1;
//     it->pool[i].len = 0;
//   }
// }

static void init_interner(intern* it){
  it->count = 0;
  it->cap = 1;
  it->pool = (couple*)calloc((size_t)it->cap, sizeof(*it->pool));
  it->arr = (char**)calloc((size_t)it->cap, sizeof(*it->arr));
  if(!it->pool || !it->arr){
    perror("calloc error");
    exit(1);
  }
}

static int resize(intern* it){
  if(it->count < it->cap) return 0;

  int oldcap = it->cap;
  it->cap *= 2;

  couple* newpool = (couple*)realloc(it->pool, (size_t)it->cap * sizeof(*it->pool));
  char** newarr = (char**)realloc(it->arr, (size_t)it->cap * sizeof(char*));
  if(!newpool || !newarr){
    perror("realloc failed");
    exit(1);
  }

  it->pool = newpool;
  it->arr = newarr;

  return 0;
}

static int interner(intern* it, const char* s){
    if(!it || !s) return -1;

    size_t lens = strlen(s);
    if(lens > UINT16_MAX) return -1;
    uint16_t len = (uint16_t)lens;
    
    for (int i = 0; i < it->count; i++) {
      if(it->pool[i].len != len || it->arr[i][0] != s[0]) continue;
      if(memcmp(it->arr[i], s, len) == 0) return it->pool[i].id;
    }

    if(resize(it) != 0) return -1;
    int id = it->count;

    char* iownyou = (char*)malloc((size_t)len+1);
    if(!iownyou) return -1;

    memcpy(iownyou, s, len);
    iownyou[len] = '\0';
    
    it->arr[id] = iownyou;
    it->pool[id].id = id;
    it->pool[id].len = len;

    it->count++;
    
    return id;
}

static const char* view(intern* it, const int id){
  if(!it|| id >= it->count || id < 0) return NULL;
    return it->arr[id];
}


static void free_interner(intern* it){
  if(!it) return;
  for(int i = 0; i < it->count; i++){
    free(it->arr[i]);
  }
  free(it->arr);
  free(it->pool);
  it->arr = NULL;
  it->pool = NULL;
  it->count = 0;
  it->cap = 0;
}


#endif
