#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

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


void print_sieves(int max)
{
    //Denna pointer håller addressen for blocket av minne som skapas for vektorn prime_list
    int *prime_list;
    //Reserverar ett block av minne som är tillräckligt stort för att rymma max heltal, sizeOf(int) ger storleken i byte för ett ensklit heltal
    prime_list = (int *)malloc((max) * sizeof(int));

    if (prime_list == NULL)
    {
        printf("Memory has not been allocated\n");
    }
    else
    {
        printf("Memory successfully allocated using malloc\n");

        for (int i = 0; i <= max; i++)
        {
            prime_list[i] = 1;
        }
    }

      //Loop börjar på värdet 2 till när p*p är större än max 
        for (int p = 2; p *p <= max; p++)
    {
        //Om p är ett primtal vet vi att alla tal som är en produkt av det primtalet inte är ett primtal
        if (prime_list[p] == 1)
        {
        for (int i = p*p; i <= max; i+= p)
            {
            prime_list[i] = 0;
            } 
        }

    }
    for (int i = 2; i <= max; i++)
    {
        if (prime_list[i] == 1)
        {
        print_number(i);
        }
        
    }

    printf("\n");

    free(prime_list);
}

int main(int argc, char *argv[])
{
    if (argc == 2)
        print_sieves(atoi(argv[1]));
    else
        printf("Please state an integer number.\n");

    return 0;
}
