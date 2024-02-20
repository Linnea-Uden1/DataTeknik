


#include <stdio.h>

char* text1 = "This is a string."; //text1 is a pointer that holds the memory address of the first character in "This is a string"
char* text2 = "Yet another thing.";
int count = 500; 
int list1[18];
int list2[18];

void copycode(const char text[], int list[], int *cnt){
  //This has the value of the first charachter in text array, 
  char currentChar = *text; //This gets the values that *text points to in this case the character 'T' and sets it to currentChar

  while (currentChar != '\0')//Continues as long as the currentChar is not null
  {
    *list = currentChar; //Copies the ASCII code of the current character into the location pointed to by list 
    list+=1; 
    text+=1;
    *cnt +=1; 
    currentChar = *text; //Uppdates the currentChar var with the next character from the text
  }

}

void work(){
  copycode(text1, list1, &count); //& takes the address to count 
  copycode(text2, list2, &count);

}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n", 
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));
  
}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count);
}
