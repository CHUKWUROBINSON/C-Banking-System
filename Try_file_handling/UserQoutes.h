/*
 This header and folder serve as a source of simple functions which may lead to a better understanding of file handling in C.
 
 The functions here are not useful the main project and they will not be #included. But please, do feel free to check out the various functions... you can try to find out what each function does. Good luck with that ;)

*/



#define STRING_LENGTH 50
#define NUM_O_QUOTES 3
#include <string.h>
typedef struct Table{
 long int c0;
 long int c1;
 long int c2;
 long int c3;
} Table;
typedef struct UserQuotes {
  
  char name[STRING_LENGTH];
  int age;
  char userQuotes[NUM_O_QUOTES][STRING_LENGTH];
} UserQuotes;

void inputUserQuotes(UserQuotes *user){
  
  printf("\nPlease input the user's name :");
  scanf("%s",user->name);
  
  printf("\nPlease input the user's age :");
  scanf("%d",&user->age);
  getchar();
  
  printf("\nEnter the user's quotes\n");
  printf("1). ");
  fgets(user->userQuotes[0],STRING_LENGTH,stdin);
  user->userQuotes[0][strcspn(user->userQuotes[0],"\n")] = '\0'; // remove newline character
  printf("2). ");
  fgets(user->userQuotes[1],STRING_LENGTH,stdin);
  user->userQuotes[1][strcspn(user->userQuotes[1],"\n")] = '\0';
  printf("3). ");
  fgets(user->userQuotes[2],STRING_LENGTH,stdin);
  user->userQuotes[2][strcspn(user->userQuotes[2],"\n")] = '\0';
}

void fprintUserQuotesTxt(UserQuotes *user, FILE *ptr){
  
  //printf("printing users");
  
  fprintf(ptr,"Currently %d years old, %s had at certain times said:\n",user->age,user->name);
  fprintf(ptr,"1). \"%s\" \n",user->userQuotes[0]);
  fprintf(ptr,"2).  \"%s\" \n",user->userQuotes[1]);
  fprintf(ptr,"3).  \"%s\" \n",user->userQuotes[2]);
}
void fscanUserQuotes(FILE *ptr,UserQuotes *user,int num){
  
  int count = 0;
  char line[90];
  char *token;
  rewind(ptr);
  
  
  while(!feof(ptr)){
    
    if(count > num - 1) break;
    
    fgets(line,90,ptr);
    sscanf(line,"Currently %d years old, %s had at certain times said:",&user->age,user->name);
  
    fgets(line, 90, ptr);
    strtok(line,"\"");
    token = strtok(NULL,"\"");
    strcpy(user->userQuotes[0],token);
    fgets(line, 90, ptr);
    strtok(line,"\"");
    token = strtok(NULL,"\"");
    strcpy(user->userQuotes[1],token);
    
    fgets(line, 90, ptr);
    strtok(line,"\"");
    token = strtok(NULL,"\"");
    strcpy(user->userQuotes[2],token);
  
    ++count;
  }
  
}

void writeToText(char *fileName){
  
  FILE *userText;
  
 UserQuotes user;
 inputUserQuotes(&user);
  if(!(userText = fopen(fileName,"a"))){
    
    printf("unable to open file");
    return;
  }
  
  fprintUserQuotesTxt(&user, userText);
  
  fclose(userText);
  
}

void readFromText(char *fileName,int userPos){
  
  FILE *ptr;
  
  UserQuotes user;
  
  if(!(ptr = fopen(fileName,"r"))){
    printf("could not open file");
    return;
  }
  
  fscanUserQuotes(ptr,&user,userPos);
  fprintUserQuotesTxt(&user, stdout);
}
void createBinaryFile(char *fileName){
  
  FILE *ptr;
   char cmptFileName[100] = "./Try_file_handling/";
   Table table[3];
   table[0].c0 = 78;
   table[0].c1 = 67;
   table[0].c2 = 18;
   table[0].c3 = 5;
   
    
   strcat(cmptFileName,fileName);
  
  if(!(ptr = fopen(cmptFileName,"wb"))){
    printf("Could not create file");
    return;
  }
  printf("%zu",sizeof(table));
  
  fwrite(table, sizeof(table),1,ptr);
  fclose(ptr);
  
}
void readBinaryTable(Table *table,char *cmpFileName){
  
  FILE *ptr;
  
  if(!(ptr = fopen(cmpFileName,"rb"))){
    printf("Could not create file");
    return;
  }
  
  fread(table,3 * sizeof(*table),1,ptr);

  fclose(ptr);
  
}
void writeBinaryFile(Table *table,char *cmpFileName){
  FILE *ptr;
  
  if(!(ptr = fopen(cmpFileName,"rb+"))){
    printf("could not open file");
    return;
  }
  
  fwrite(table, 3 * sizeof(*table),1,ptr);
  fclose(ptr);
}
void writeBinaryUserInfo(Table *table,int userpos, UserQuotes *user,char *cmpFileName){
  
  FILE *ptr;
  
  
  if(!(ptr = fopen(cmpFileName,"rb+"))){
    printf("could not open file");
    return;
  }
  fseek(ptr,0,SEEK_END);
  table[userpos].c0 = ftell(ptr);
  fwrite(user->name,sizeof(user->name),1,ptr);
  fwrite(&user->age,sizeof(user->age),1,ptr);
  rewind(ptr);
  fwrite(table,3 * sizeof(*table),1,ptr);
  
  fclose(ptr);
  
  
}
void readBinaryUserInfo(Table *table,int userpos, UserQuotes *user, char *cmpFileName){
  
  FILE *ptr;
  
  if(!(ptr = fopen(cmpFileName,"rb"))){
    printf("could not open file");
    return;
  }
  
  fseek(ptr, table[userpos].c0,SEEK_SET);
  
  fread(user->name, sizeof(user->name),1,ptr);
  fread(&user->age, sizeof(user->name),1,ptr);
 
  fclose(ptr);
}
void writeBinaryUserQuotes(UserQuotes *user,int userPos,int quotePos,Table *table, char *cmpFileName){
  
  FILE *ptr;
  
  if(!(ptr = fopen(cmpFileName,"rb+"))){
    
    printf("could not open file\n");
    return;
  }
  
  fseek(ptr,0,SEEK_END);
  
  switch(quotePos){
    case 1:
      table[userPos].c1 = ftell(ptr);
      break;
    case 2:
      table[userPos].c2 =  ftell(ptr);
      break;
    case 3:
      table[userPos].c1 =  ftell(ptr);
      break;
    default:
      table[userPos].c3 = ftell(ptr);
      break;
  }
  
  fwrite(user->userQuotes, sizeof(user->userQuotes),1,ptr);
  rewind(ptr);
  fwrite(table,3 * sizeof(*table),1,ptr);
  fclose(ptr);
}
void readBinaryUserQuotes(UserQuotes *user, int userPos, int quotePos, Table *table, char *cmpFileName){
  
  FILE *ptr;
  
  if(!(ptr = fopen(cmpFileName,"rb"))){
    
    printf("could not open file\n""");
    return;
  }
  
  fread(table,3 * sizeof(table),1,ptr);
  
  switch(quotePos){
    case 1:
      fseek(ptr,table[userPos].c1,SEEK_SET);
      break;
    case 2:
      fseek(ptr,table[userPos].c2,SEEK_SET);
      break;
    case 3:
      fseek(ptr,table[userPos].c3,SEEK_SET);
      break;
    
    default:
      fseek(ptr,table[userPos].c3,SEEK_SET);
      break;
  }
  fread(user->userQuotes, sizeof(user->userQuotes),1,ptr);

  fclose(ptr);
}


  


void testTry_file_handling(){
 
  printf("Hello World!");
}