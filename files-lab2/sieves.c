#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



#define COLUMNS 6


void print_number(int n){
  static int count = 0; 
  printf("%10d", n);
  count ++;
  if (count == COLUMNS)
  {
    printf("\n");
    count = 0;
  }
  
}

void print_sieves(int max){

  bool prime_list[max];

  //Sätter alla värden i prime_list till 1, dvs utgår från att de är ett primtal och ändrar sedan alla som inte är ett primtal 
  for (int i = 0; i < max; i++)
  {
    prime_list[i] = 1;
  }
  
  
  //Loop börjar på värdet 2 till när p*p är större än max 
  for (int p = 2; p *p < max; p++)
  {
    //Om p är ett primtal vet vi att alla tal som är en produkt av det primtalet inte är ett primtal
    if (prime_list[p] == true)
    {
      for (int i = p*p; i <= max; i+= p)
        {
          prime_list[i] = false;
        } 
    }

  }
  for (int i = 2; i < max; i++)
  {
    if (prime_list[i] == true)
    {
      print_number(i);
    }
    
  }
  printf("\n");

}


int main(int argc, char *argv[]){
  if(argc == 2)
    print_sieves(atoi(argv[1]));
  else
    printf("Please state an interger number.\n");
  return 0;
}