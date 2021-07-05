#ifndef CB_UTA_USER_TABLE_API_H
#define CB_UTA_USER_TABLE_API_H
#include "./Tables_utilities/UserJSArray.h"
#include "Models.h"
#include <stdio.h>


/*
function CB_UTA_writeUser(): This function creates file in the directory specified by its argument  cmptFileName. The function also writes the first data record with the values of its second argument user
CB_UTA_writeUser returns an integer for error detection. 1 incase of a successful write and 0 incase of failure
*/

int CB_UTA_writeUser(char *cmptFileName, CB_User *user){
  
  FILE *ptr;
  if(!(ptr = fopen(cmptFileName,"wb"))){
     
     printf("\n could not create file\n");
     return 0;
  }
  
  
  fwrite(user,sizeof(*user),1,ptr);
  
  fclose(ptr);
  
  return 1;
  
}


/*
function CB_UTA_addNewUser(): This function apends a new user record to the botom of the file if there are no empty records. if there are empty records, the function overwrites the first one it finds.
CB_UTA_writeUser returns an integer for error detection. 1 incase of a successful write and 0 incase of failure
*/

int CB_UTA_addNewUser(char *cmptFileName, CB_User *user){
  
  FILE *ptr;
  long int seekPos;
  CB_User temp;
  
  if(!(ptr = fopen(cmptFileName,"rb+"))){
    
    printf("\n could not open file \n");
    return 0;
  }
  
  while(!feof(ptr)){
    
    seekPos = ftell(ptr); // save current position 
    
    fread(&temp,sizeof(temp),1,ptr);
    
    //test if record is empty
    if(!strcmp( temp.userInfo.userId,"")){
       printf("\n were in\n");
       printf("\n %s",temp.userInfo.userId);
      fseek(ptr,seekPos,SEEK_SET); // reposition pointer to prepare for overwriting
      break;
    }
  }
  
  fwrite(user, sizeof(*user),1,ptr);
  
  fclose(ptr);
  
  return 1;
  
}

void CB_UTA_searchUserById(char *id,CB_User *user, char *cmptFileName){
  
  FILE *ptr;
  
  if(!(ptr = fopen(cmptFileName,"rb"))){
    
    printf("\n could not open file");
    
    return;  
  }
  
  while(!feof(ptr)){
    fread(user,sizeof(*user),1,ptr);
    
    if(!strcmp(id,user->userInfo.userId)){
      
      return;
      
    }
  }
  
  printf("\n No record with id: %s found\n",id);
  
  return;
  
}

void CB_UTA_insertSortUserList(CB_UJSA_UserJSArray *list,CB_User *users, const int arrSize){
  
  
  int i, count;
  CB_UJSA_UserNode *current,*temp;
  
  
  for(i = 0; i < arrSize; i++){
      
      count =  0;
      
      if(!list->headPtr){
        printf("\nI am if\n");
        temp = CB_UJSA_initUserNode(&users[0]);
        CB_UJSA_insertNode(list,temp,0);
        continue;
      }
      
      current = list->headPtr;
      
      
    do{
      
      printf("\ncount %d list->length %d\n", count, CB_UJSA_getUserListLength(list));
      
      
      if(CB_compareUser(&current->data,&users[i]) >= 0 ){
        printf("True i am %d\n", CB_compareUser(&current->data,&users[i]));
        temp = CB_UJSA_initUserNode( &users[i]);
        
        CB_UJSA_insertNode(list,temp,count);
        
        break;
        
      }
      else{
        printf("False i am %d\n", CB_compareUser(&current->data,&users[i]));
      }  
      
      ++count;
      current = current->nextPtr;
    }
    while(current);
    if((CB_UJSA_getUserListLength(list) < arrSize) && (count >= CB_UJSA_getUserListLength(list))){
      temp = CB_UJSA_initUserNode(&users[i]);
      CB_UJSA_enqueNode(list,temp);
    }
    
  }
  
  
}





/* Test functions */
void CB_UTA_dataBaseTryU(char *cmptFileName,CB_User *user){
  int bit = 1;
  CB_inputUser(user);
  CB_UTA_writeUser(cmptFileName,user);
  
  while(bit){
    
    CB_inputUser(user);
    CB_UTA_addNewUser(cmptFileName,user);
    
    printf("\ncontinue ? (1 for yes 0 for no) :");
    scanf("%d",&bit);
    
  }
  
}

void CB_UTA_testUserApi(){
  CB_User users[5];
  int i;
  CB_UJSA_UserJSArray list;
  list.headPtr = list.tailPtr = NULL;
  //CB_Message msg;
  
  //CB_UTA_dataBaseTryU("myFile.met",&user);
  for(i = 0;i < 5; i++){
    
    CB_inputUser(&users[i]);
    
  }
  
  CB_UTA_insertSortUserList(&list,users,5);
  
  CB_UJSA_printList(&list);
  
}



#endif