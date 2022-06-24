#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "die.h"

int main(){

  Die *d=NULL;
  Id id;
  char letter;

  printf("Introduce an id for a die: ");
  scanf("%ld", &id);

  d=die_create(id);
  if(!d){ 
    
    printf("Couldn't create the die.");
    return 1;
  }
  
  printf("Die created.\n");
  
  srand(time(NULL));
  
  if(die_roll(d)==ERROR){ 
    
    printf("Couldn't roll the die.");
    return 1;
  }
  
  printf("Press 'c' to roll the die: ");
  scanf("\n%c", &letter);

  while(letter=='c'){

    die_roll(d);
    die_print_content(d);

    printf("Press 'c' to roll again or any letter to exit.\n");
    scanf("\n%c", &letter);
  }

  die_destroy(d);	
  return 0;
}

