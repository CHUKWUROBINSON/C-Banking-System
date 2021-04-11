#define INFO_STRINGLENGTH 50
#define TIME_DEF_WITH_SERVER 3600
#include <stdlib.h>
#include <string.h>
#include <time.h>

void timeStampToStr(time_t timeStamp, char* formatedTimeStamp);

typedef struct infoNode{
  char data [INFO_STRINGLENGTH];
  time_t timeStamp;
  char formatedTimeStamp[INFO_STRINGLENGTH];
  unsigned long int id;
  struct infoNode* prevPtr;
  struct infoNode* nextPtr;
} infoNode;

typedef struct JSArray{
  infoNode* headPtr;
  infoNode* tailPtr;
} JSArray;

infoNode* initInfoNode(char *data,time_t timeStamp, unsigned long int id){
  
infoNode* node = (infoNode*) malloc(sizeof(infoNode));
  node->id = id;
  
  strcpy(node->data,data);
  node->timeStamp = timeStamp;
  
  timeStampToStr(timeStamp,node->formatedTimeStamp);
  
  node->prevPtr = node->nextPtr = NULL;
  
   return node;
}
void copyInfoNode(infoNode* dest,infoNode* src){
  
  dest->id = src->id;
  strcpy(dest->data, src->data);
  dest->timeStamp = dest->timeStamp;
  strcpy(dest->formatedTimeStamp,src->formatedTimeStamp);
  
  
}
JSArray* enqueInfoNode(JSArray* list,infoNode* node){
  
  if(list->headPtr && list->tailPtr){
    node->prevPtr = list->tailPtr;
    list->tailPtr = list->tailPtr->nextPtr = node;
    
  }
  else{
    list->headPtr = list->tailPtr = node;
  }
  
  return list;
}

JSArray* pushInfoNode(JSArray* list,infoNode* node){
  
  
  if(list->headPtr){
  node->nextPtr = list->headPtr;
  node->nextPtr->prevPtr = list->headPtr = node;
  return list;
  }
    list->headPtr = list->tailPtr = node;
  
   return list;
}

void insertInfoNode(JSArray *list, infoNode *node, const int pos){
  infoNode *current = list->headPtr;
  int count = 0;
  if(pos < 0) return;
  

  if(!current){
    list->headPtr = list->tailPtr = node;
    printf("\never true\n");
    return;
  }
  
  do{
    
    
    if(!current && count ){
      
      list->tailPtr->nextPtr = node;
      node->prevPtr = list->tailPtr;
      list->tailPtr = node;
      return;
    }
    
    if(count == pos){
      
      node->nextPtr = current;
      node->prevPtr = current->prevPtr;
      current->prevPtr = node;
      if(pos == 0){
        
        list->headPtr = node;
        return;
      }
      node->prevPtr->nextPtr = node;    
       return;
    }
    ++count;
    current = current->nextPtr;
  }while(1);
  
}

JSArray* popInfoNode(JSArray* list){
  infoNode* tempPtr;
  printf("\n Me is here\n");
  if(!list->headPtr){
    return list;
  }
  if(list->headPtr == list->tailPtr){
    printf("\nWere in here!\n");
    free(list->headPtr);
    list->headPtr = list->tailPtr = NULL;
    return list;
  }
    tempPtr = list->headPtr->nextPtr;
    free(list->headPtr);
    list->headPtr = tempPtr;
    
    return list;
}

JSArray* dequeInfoNode(JSArray* list){
  infoNode* tempPtr;
  if(!list->headPtr) return list;
  else if(list->headPtr == list->tailPtr){
    free(list->tailPtr);
    list->tailPtr = list->headPtr = NULL;
    return list;
  }
   tempPtr = list->tailPtr->prevPtr;
   free(list->tailPtr);
   list->tailPtr = tempPtr;
   
   return list;
}

void deinsertInfoNode(JSArray *list,const int pos){
  infoNode *current = list->headPtr;
  int count = 0;
  
  if(pos < 0) return;
  if(list->headPtr == list->tailPtr){
    list->headPtr = list->tailPtr = NULL;
    free(current);
    printf("\n freedee!!\n");
    return;
    
  }
  if(!pos){
    
    list->headPtr = list->headPtr->nextPtr;
    free(current);
    return;
    
  }

  
  do{
    
    if((!current && count) || ((pos == count) && (current == list->tailPtr))){
      
      list->tailPtr = list->tailPtr->prevPtr;
      free(list->tailPtr->nextPtr);
      list->tailPtr->nextPtr = NULL;
      printf("\n free the last one \n");
      return;
    }
    
    
    
    if(pos == count){
      printf("\n I am True\n");
      current->nextPtr->prevPtr = current->prevPtr;
      current->prevPtr->nextPtr = current->nextPtr;
      
      free(current);
      
      return;
    }
    ++count;
    current = current->nextPtr;
  }while(1);
  
}

void timeStampToStr(time_t timeStamp, char* formatedTimeStamp){
  struct tm* tm = localtime(&timeStamp);
  strftime(formatedTimeStamp,INFO_STRINGLENGTH,"%a %b %d %Y   %H:%M:%S %p",tm);
}

void cleanStd(){
  int c;
  
  
  while((c = getchar()) != '\n' && c != EOF);
}

//test functions
void printInfoNode(infoNode* node){
printf("%lu||\t %s ||\t %s\n\n", node->id, node->data,node->formatedTimeStamp);
}
void printList(JSArray* list){
  infoNode* current = list->headPtr;
  while(current){
    printInfoNode(current);
    current = current->nextPtr;
  }
}

infoNode* inputNode(){
  char msg[INFO_STRINGLENGTH];
  printf("\n input data: ");
  
  fgets(msg, INFO_STRINGLENGTH,stdin);
  msg[strcspn(msg,"\n")] = '\0';
  if((strlen(msg) + 1) < INFO_STRINGLENGTH) ungetc('\n', stdin);
  cleanStd();
  srand(time(NULL));
  
  return initInfoNode(msg,time(NULL) + TIME_DEF_WITH_SERVER,rand());
}

void testList(){
  /*int stop = 0;
  JSArray history;
  infoNode* node;
  history.headPtr = history.tailPtr = NULL;
  while(!stop){
    
    //node = inputNode();
     //enqueInfoNode(&history, node);
     
    //printf("\n The list so far\n\n");
    //printList(&history);
     
     node = inputNode();
    
    pushInfoNode(&history, node);
    printf("\n The list so far\n\n");
    printList(&history);
    printf("stop? 1 for yes and 0  ");
    
    scanf("%d",&stop);
    cleanStd();
  }
  printList(&history);
  printf("\n-----------------\n");
  popInfoNode(&history);
  printList(&history);
  
  printf("\n------------------\n");
  popInfoNode(&history);
  printList(&history);

printf("\n------------------\n");
  
  popInfoNode(&history);
  printList(&history);
  */
  infoNode* node = inputNode();
  printf("\n The first node is \n");
  printInfoNode(node);
  
  infoNode* node1 = inputNode();
  printf("\n the second Node is \n");
  printInfoNode(node1);
  printf("\n------------------\n");
  printf("after copying node to node1\n");
  copyInfoNode(node1,node);
  printInfoNode(node);
}