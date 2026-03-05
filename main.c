#include "interner.h"
#include <time.h>

#define MAX_SIZE 10000


void generate_random_string(char *dest, size_t length) {
    const char charset[] = "0123456789"
                           "abcdefghijklmnopqrstuvwxyz"
                           "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t charset_size = sizeof(charset) - 1; 
    
    if (charset_size == 0) return;

    for (size_t i = 0; i < length; i++) {
        size_t index = rand() % charset_size; 
        dest[i] = charset[index];
    }
    dest[length] = '\0';
}
int main(void){
  srand((unsigned int)time(NULL));
  size_t length = 10;
  char random_string[length + 1]; 
  intern intern;
  init_interner(&intern);
  
  for(int i = 0; i < MAX_SIZE; i++){
    generate_random_string(random_string, length);
    interner(&intern, random_string);
  }
  for(int i = 0; i < intern.count; i++){
    printf("id: %d, v: %s\n", intern.pool[i].id, intern.arr[i]);
  }

  free_interner(&intern);
  return 0;
}
