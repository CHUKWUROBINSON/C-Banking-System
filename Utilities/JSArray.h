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
  
  
  if(list->headPtr && list->tailPtr){
  node->nextPtr = list->headPtr;
  list->headPtr->prevPtr = list->headPtr = node; 
  }
  else{
    list->headPtr = list->tailPtr = node;
  }
   return list;
}

void insertInfoNode(JSArray *list, infoNode *node, const int pos){
  infoNode *current = list->headPtr;
  int count = 0;
  if(pos < 0) return;
  
  
  do{
    
    if(!current){
    list->headPtr = list->tailPtr = current;
    return;
    }
    
    if(count == pos){
      
      node->nextPtr = current;
      node->prevPtr = current->prevPtr;
      current->prevPtr = node;
      node->prevPtr->nextPtr = node;
      return;
    }
    ++count
    current = current->nextPtr;
  }while(1)
  
}

JSArray* popInfoNode(JSArray* list){
  infoNode* tempPtr;
  if(!list->headPtr){
    return list;
  }
  else if(list->headPtr == list->tailPtr){
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
  int stop = 0;
  JSArray history;
  infoNode* node;
  history.headPtr = history.tailPtr = NULL;
  while(!stop){
    
     node = inputNode();
    
    insertInfoNode(&history, node);
    printf("\n The list so far\n\n");
    printList(&history);
    printf("stop? 1 for yes and 0  ");
    
    scanf("%d",&stop);
    cleanStd();
  }
}