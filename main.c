#include "interner.h"

int main(void){

  // intern intern = {0};
  intern intern;
  init_interner(&intern);
  int id0 = interner(&intern, "hello");
  const char* v0 = view(&intern, id0);

  int id1 = interner(&intern, ", world");
  const char* v1 = view(&intern, id1);

  int  id2 = interner(&intern, "husein");
  const char* v2 = view(&intern, id2);

  int  id3 = interner(&intern, "idk");
  const char* v3 = view(&intern, id3);

  int  id4 = interner(&intern, "what");
  const char* v4 = view(&intern, id4);

  int  id5 = interner(&intern, "hmm");
  const char* v5 = view(&intern, id5);

  int  id6 = interner(&intern, "bruh");
  const char* v6 = view(&intern, id6);

  int  id7 = interner(&intern, "fuck");
  const char* v7 = view(&intern, id7);

  int  id8 = interner(&intern, "i");
  const char* v8 = view(&intern, id8);

  int  id9 = interner(&intern, "lol");
  const char* v9 = view(&intern, id9);

  for(int i = 0; i < MAX_SIZE; i++){
    printf("id: %d, v: %s\n", intern.pool[i].id, intern.pool[i].name);
  }

  free_interner(&intern);
  return 0;
}
