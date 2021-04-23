/*
This header file is built as part of the utilities or helper functions.
The main purpose for building this file is to provide a linked list data struct and its manipulators,
which will be used in the remainder of the program.

Here, I have implemented, as best I could,a kind of, implementation of the JavaScript version of an array, hence the name. 
I also tried to provide as many helper functions as possible. 
One reason is for completeness sake, another reason for use in cases I might not be able to think of at the moment.
Due to the lack of natural polymorphism in a procedural language like C, this same JSArray.h file might be copied and modiefied to fit the need.


The main data structure is struct JSArry, which I have typedef to JSArray, sha, I don't know if that's good practice, but I'm just too lazy to use struct each time I want to instantiate a variable.
JSArray has only two members, headPtr and tailPtr which are used to point to the head and tail of the list. headPtr and tailPtr are pointers of type infoNode.
The nodes in the JSArray are of type infoNode, which have members:
->data: this stores the main information in the node;
->timeStamp: this stores the time the node was created;
->formatedTimeStamp: this stores the timeStamp as a string, in a way that is readable to a human;
->id: this stores the id of the node.
 nextPtr and prevPtr are pointers to the next and previous elements in the list.
 like I said above, infoNode is just a template which I will modify in other files to  get the required results and behavior.
 
 The main functions for the list are:
  ->enqueInfoNode()
  ->pushInfoNode()
  ->insertInfoNode()
  ->popInfoNode()
  ->dequeInfoNode()
  ->deinsertInfoNode()
  ------ these are the main functions used to manipulate the JSArray list.
  
  The other functions are either helper functions or use to test functionality.
  
  The helper functions are:
  ->initInfoNode()
  ->copyInfoNode()
  ->timeStampToStr()
  ->cleanStdin()
  
  The test functions are
  ->testList()
  ->inputInfoNode()
  ->printInfoNode()
  ->printList()
  
  
  The descriptions of the functions, that is, the main job the function does, the return value of the function and the type of parameters the function takes, are found at the function's implementation
*/
#define INFO_STRINGLENGTH 50
#define TIME_DEF_WITH_SERVER 3600
#include <stdlib.h>
#include <string.h>
#include <time.h>

void timeStampToStr (time_t timeStamp, char * formatedTimeStamp); // forward declaration of function to avoid compiller warning

//struct infoNode
typedef struct infoNode{
  char data [INFO_STRINGLENGTH];
  time_t timeStamp;
  char formatedTimeStamp[INFO_STRINGLENGTH];
  unsigned long int id;
  struct infoNode* prevPtr;
  struct infoNode* nextPtr;
} infoNode;


//struct JSArray
typedef struct JSArray{
  infoNode* headPtr;
  infoNode* tailPtr;
} JSArray;


//function initInfoNode(): allocates space for a node from the heap using malloc(),  initialises the node with the arguments passed into it.
  //The parameters for this function are:
  //array of char data, timestamp of type time_t, and a random number as id
  //the function returns the address of the allocated and initialised node
  
infoNode* initInfoNode( char *data, time_t timeStamp, unsigned long int id){
  
infoNode* node = (infoNode*) malloc(sizeof(infoNode));
  node->id = id;
  
  strcpy(node->data,data);
  node->timeStamp = timeStamp;
  
  timeStampToStr(timeStamp,node->formatedTimeStamp);
  
  node->prevPtr = node->nextPtr = NULL;
  
   return node;
}

//function copyInfoNode(): copies the values of the members of src to dest
//takes in dest and src infoNodes by reference. By reference because we want to use copyInfoNode() to edit node items in a list without having to insert and deinsert each time, also, to reduces memory usage since the variables are not copied 
//does not return anything

void copyInfoNode(infoNode* dest,infoNode* src){
  
  dest->id = src->id;
  strcpy(dest->data, src->data);
  dest->timeStamp = dest->timeStamp;
  strcpy(dest->formatedTimeStamp,src->formatedTimeStamp);
  
  
}

//function enqueInfoNode(): adds an InfoNode to the tail end of the list
//takes in two parameters node to be added and the list to which the node is added. Just the standard for queues

// it also returns the list for chaining operations, like in OOP
JSArray* enqueInfoNode(JSArray* list,infoNode* node){
  
  if(list->headPtr && list->tailPtr){ //if list is not empty
  
   //add node to tail end of list
    node->prevPtr = list->tailPtr;
    list->tailPtr = list->tailPtr->nextPtr = node;
    
  }
  else{
    list->headPtr = list->tailPtr = node;
  }
  
  return list;
}

//function pushInfoNode(): adds an InfoNode to the head end of the list
//takes in two parameters node to be added and the list to which the node is added. Just the standard for stacks
// it also returns the list for chaining operations, like in OOP

JSArray* pushInfoNode(JSArray* list,infoNode* node){
  
  
  if(list->headPtr){
  
  //if the list is not empty add node to head end of list  
  
  node->nextPtr = list->headPtr;
  node->nextPtr->prevPtr = list->headPtr = node;
  return list;
  }
    list->headPtr = list->tailPtr = node;
  
   return list;
}

//function insertInfoNode(): inserts a node at the possition specified by pos argument. If the pos argument is less than zero, it does nothing, if the pos arguement is greater than the total number of elements in the list, the node is added to the tail end of the list. All else, the node is added to the specified possition
//The arguments are the node to be added, the list in which the node will be added, and the possition to add the node.
//the function returns the list for OOP like chaining
void insertInfoNode(JSArray *list, infoNode *node, int pos) {
  
  infoNode *current = list->headPtr;
  int count = 0;
  
  if(pos < 0) return; //if pos is less than zero, do nothing
  

  if(!list->headPtr) {
    
   //if list is empty, add node and return
    
    list->headPtr = list->tailPtr = node;
    return;
  }
  
  do{
    
    
    if(!current && count ){
      
      //if pos is greater than length of list, add node to tail end of list
      
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
        //update headPtr when adding at the top
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


//function popInfoNode(): this function pops a node  from the list.
//the function takes the list on which to perform the pop as parameter
//The function returns the list for method chaining
JSArray* popInfoNode(JSArray* list) {
  
  infoNode* tempPtr;
  
  if(!list->headPtr){ //if list is empty return
    return list;
  }
  if(list->headPtr == list->tailPtr){
    //if there is only one element in the list
    
    free(list->headPtr);
    list->headPtr = list->tailPtr = NULL;
    return list;
  }
    tempPtr = list->headPtr->nextPtr;
    free(list->headPtr);
    list->headPtr = tempPtr;
    
    return list;
}


//function dequeInfoNode(): the function removes a node from the tail end of list.
//the function takes in as parameter the list on which tonremove the node.
//the function returns the list
JSArray* dequeInfoNode(JSArray* list){
  
  
  infoNode* tempPtr;
  
  if(!list->headPtr) return list; //if the list is empty, return
  
  if(list->headPtr == list->tailPtr) {
    
    //if there is only one element in the list
    
    free(list->tailPtr);
    list->tailPtr = list->headPtr = NULL;
    return list;
  }
   tempPtr = list->tailPtr->prevPtr;
   free(list->tailPtr);
   list->tailPtr = tempPtr;
   
   return list;
}

//function deinsertInfoNode(): removes a node from the list at the possition specified by the pos argument. If pos is less than zero, it does nothing. If there's only one element in the list, it removes that element, irrespective of the value of pos (except pos is less than zero, where it does nothing). If pos is larger than the total number of elements in the list, it removes the node at the tail end of the list. All else, it removes the element specified by the pos parameter from the list. The function also frees the memory space occupied by the node
//The arguments are the list in which the node is to be removed and the possition of the node to be removed
//The function returns the list for OOP like chaining
void deinsertInfoNode(JSArray *list,const int pos){
  
  infoNode *current = list->headPtr;
  int count = 0;
  
  if(pos < 0) return; //if the list is empty
  
  if(list->headPtr == list->tailPtr){//id there is only one element in the list
    
    list->headPtr = list->tailPtr = NULL;
    free(current);
  
    return;
    
  }
  if(!pos){
    
    list->headPtr = list->headPtr->nextPtr;
    free(current);
    return;
    
  }

  
  do{
    
    if((!current && count) || ((pos == count) && (current == list->tailPtr))){
      //if pos is larger than the length of the list OR you are at the end of the list
      list->tailPtr = list->tailPtr->prevPtr;
      free(list->tailPtr->nextPtr);
      list->tailPtr->nextPtr = NULL;
    
      return;
    }
    
    
    
    if(pos == count){
    
      current->nextPtr->prevPtr = current->prevPtr;
      current->prevPtr->nextPtr = current->nextPtr;
      
      free(current);
      
      return;
    }
    ++count;
    current = current->nextPtr;
  }while(1);
  
}

//function timeStampToStr(): converts a time_t object to a string and stores it in a char array
//the parameters the time_t object to convert and a pointer to the char array where the string is to be stored
//the function does not return anything

void timeStampToStr(const time_t timeStamp, char * formatedTimeStamp) {
  
  struct tm* tm = localtime(&timeStamp);
  
  strftime(formatedTimeStamp,INFO_STRINGLENGTH,"%a %b %d %Y   %H:%M:%S %p",tm);
}


//function cleanStdin(): this function cleans the stdin buffer if there is something in it.
//(CAUTION!!  this function blocks stdin if the input buffer is empty. use it wisely)
//the function takes no parameters
//the function does not return a value
void cleanStdin(){
  int c;
  
  
  while((c = getchar()) != '\n' && c != EOF);
}

//test functions
//____________________

/*
 This section contains functions that test the functionality of the header file.  The functions themselves are not explicitly useful in the general project... avoid using them
*/


//prints an InfoNode
void printInfoNode(infoNode* node){
printf("%lu||\t %s ||\t %s\n\n", node->id, node->data,node->formatedTimeStamp);
}

//prints a JSArray list
void printList(JSArray* list){
  infoNode* current = list->headPtr;
  while(current){
    printInfoNode(current);
    current = current->nextPtr;
  }
}

//prompts the user to input data fit for an infoNode, the allocates memory for the node, initialises the node with the data provided by the user and then returns the adress of the allocated node

infoNode* inputNode(){
  char msg[INFO_STRINGLENGTH];
  printf("\n input data: ");
  
  fgets(msg, INFO_STRINGLENGTH,stdin);
  msg[strcspn(msg,"\n")] = '\0'; //remove new line character
  if((strlen(msg) + 1) < INFO_STRINGLENGTH) ungetc('\n', stdin); //if stdin is empty, add '\n' to stdin buffer
  cleanStdin();
  srand(time(NULL));
  
  return initInfoNode(msg,time(NULL) + TIME_DEF_WITH_SERVER,rand());
}


//main test function for JArray.h
void testList(){
  int stop = 0;
  JSArray history;
  infoNode* node;
  history.headPtr = history.tailPtr = NULL;
  while(!stop){
    
    //node = inputNode();
     //enqueInfoNode(&history, node);
     
    //printf("\n The list so far\n\n");
    //printList(&history);
     
     node = inputNode();
    
    insertInfoNode(&history, node, 4);
    printf("\n The list so far\n\n");
    printList(&history);
    printf("stop? 1 for yes and 0  ");
    
    scanf("%d",&stop);
    cleanStdin();
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
  
  /*infoNode* node = inputNode();
  printf("\n The first node is \n");
  printInfoNode(node);
  
  infoNode* node1 = inputNode();
  printf("\n the second Node is \n");
  printInfoNode(node1);
  printf("\n------------------\n");
  printf("after copying node to node1\n");
  copyInfoNode(node1,node);
  printInfoNode(node);*/
}