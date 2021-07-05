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
// forward declaration of function to avoid compiller warning

//struct infoNode
#ifndef CB_UserJSA
#define CB_UserJSA

#include "../Models.h"


typedef struct CB_UJSA_UserNode{
  CB_User data;
  struct CB_UJSA_UserNode *prevPtr;
  struct CB_UJSA_UserNode *nextPtr;
} CB_UJSA_UserNode;


//struct JSArray
typedef struct CB_UJSA_UserJSArray{
  struct CB_UJSA_UserNode* headPtr;
  struct CB_UJSA_UserNode* tailPtr;
} CB_UJSA_UserJSArray;


//function initInfoNode(): allocates space for a node from the heap using malloc(),  initialises the node with the arguments passed into it.
  //The parameters for this function are:
  //array of char data, timestamp of type time_t, and a random number as id
  //the function returns the address of the allocated and initialised node
  
CB_UJSA_UserNode* CB_UJSA_initUserNode( CB_User *user){
  //printf("\nBefore user init\n");
  
CB_UJSA_UserNode* node = (CB_UJSA_UserNode*) malloc(sizeof(CB_UJSA_UserNode));
  
  CB_copyUser(&node->data,user);
  
  node->prevPtr = node->nextPtr = NULL;
  //printf("\nUser initialized\n");
   return node;
}

int CB_UJSA_getUserListLength(CB_UJSA_UserJSArray *list){


  CB_UJSA_UserNode *current = list->headPtr;
  int count = 0;

  while(current){
    ++count;
    current = current->nextPtr;
  }
  return count;
}

//function copyInfoNode(): copies the values of the members of src to dest
//takes in dest and src infoNodes by reference. By reference because we want to use copyInfoNode() to edit node items in a list without having to insert and deinsert each time, also, to reduces memory usage since the variables are not copied 
//does not return anything



//function enqueInfoNode(): adds an InfoNode to the tail end of the list
//takes in two parameters node to be added and the list to which the node is added. Just the standard for queues

// it also returns the list for chaining operations, like in OOP
CB_UJSA_UserJSArray* CB_UJSA_enqueNode( CB_UJSA_UserJSArray* list,CB_UJSA_UserNode* node){
  
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

CB_UJSA_UserJSArray* CB_UJSA_pushNode(CB_UJSA_UserJSArray* list,CB_UJSA_UserNode* node){
  
  
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
void CB_UJSA_insertNode(CB_UJSA_UserJSArray *list, CB_UJSA_UserNode *node, int pos) {
  
  CB_UJSA_UserNode *current = list->headPtr;
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
CB_UJSA_UserJSArray* CB_UJSA_popNode(CB_UJSA_UserJSArray* list) {
  
  CB_UJSA_UserNode* tempPtr;
  
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
CB_UJSA_UserJSArray* CB_UJSA_dequeNode(CB_UJSA_UserJSArray* list){
  
  
  CB_UJSA_UserNode* tempPtr;
  
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
void CB_UJSA_deinsertNode(CB_UJSA_UserJSArray *list,const int pos){
  
  CB_UJSA_UserNode *current = list->headPtr;
  int count = 0;
  
  if(pos < 0) return; //if the list is empty
  
  if(list->headPtr == list->tailPtr){//id there is only one element in the list
    
    list->headPtr = list->tailPtr = NULL;
    free(current);
  
        return;
    
  }
  if(!pos)// if pos is possition zero
  {
    
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

//function cleanStdin(): this function cleans the stdin buffer if there is something in it.
//(CAUTION!!  this function blocks stdin if the input buffer is empty. use it wisely)
//the function takes no parameters
//the function does not return a value
void CB_UJSA_cleanStdin(){
  int c;
  
  
  while((c = getchar()) != '\n' && c != EOF);
}

//test functions
//____________________

/*
 This section contains functions that test the functionality of the header file.  The functions themselves are not explicitly useful in the general project... avoid using them
*/


//prints an InfoNode

//prints a JSArray list
void CB_UJSA_printList(CB_UJSA_UserJSArray* list){
  CB_UJSA_UserNode* current = list->headPtr;
  char strg[sizeof(CB_User) +40];
  
  while(current){
  
    CB_AcustomerUserInfoToStrg(&current->data,strg);
    current = current->nextPtr;
    printf("\n%s\n",strg);
  }
}

//prompts the user to input data fit for an infoNode, the allocates memory for the node, initialises the node with the data provided by the user and then returns the adress of the allocated node




//main test function for JArray.h
void CB_UJSA_testUserJSArray(){
  
  CB_User user;
  CB_UJSA_UserJSArray list;
  CB_UJSA_UserNode *temp, *ptr;
  
  list.headPtr = list.tailPtr = NULL;
  
  int i;
  
  for(i = 0; i < 5; i++){
    
  CB_inputUser(&user);
  temp = CB_UJSA_initUserNode(&user);
  
  //ptr = temp->nextPtr;
  
  CB_UJSA_enqueNode(&list,temp);
  printf("%d",CB_UJSA_getUserListLength(&list));
  
  //list.headPtr = list.tailPtr = temp;
  
  printf("\nThe list so far\n\n");
  CB_UJSA_printList(&list);
  
  }
  
}

#endif