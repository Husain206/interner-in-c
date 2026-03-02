#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
*
* fixed size(for now) string interner in c
*
*/


#define MAX_SIZE 10

typedef struct couple {
  char* name;
  int id;
} couple;

typedef struct intern{
  couple pool[MAX_SIZE];
  char* arr[MAX_SIZE];
} intern;


static void init_interner(intern* it){
  for(int i = 0; i < MAX_SIZE; i++){
    it->arr[i] = NULL;
    it->pool[i].name = NULL;
    it->pool[i].id = -1;
  }

}

static int interner(intern* it, const char* str){
    if(!it || !str) return -1;
  
    for (int i = 0; i < MAX_SIZE; i++) {
      if(it->pool[i].name != NULL && strcmp(it->pool[i].name, str) == 0) return it->pool[i].id;
    }

    int id = -1;
    for(int i = 0; i < MAX_SIZE; i++){
      if(it->arr[i] == NULL) {
        id = i;
        break;
        }
    }
    if(id == -1) return -1;

    int p = -1;
    for(int i = 0; i < MAX_SIZE; i++){
      if(it->pool[i].name == NULL){
        p = i;
        break;
      }
    }
    if(p == -1) return -1;

    char* iownyou = strdup(str);
    if(!iownyou) return -1;

    it->arr[id] = iownyou;
    it->pool[p].name = iownyou;
    it->pool[p].id = id;

    return id;
}

static const char* view(intern* intern, const int id){
  if(id == -1) return NULL;
  if(!intern || id >= MAX_SIZE || id < 0) return NULL;
    return intern->arr[id];
}


static void free_interner(intern* it){
  if(!it) return;
  for(int i = 0; i < MAX_SIZE; i++){
    free(it->arr[i]);
    it->arr[i] = NULL;
    it->pool[i].name = NULL;
    it->pool[i].id = -1;
  }
}

