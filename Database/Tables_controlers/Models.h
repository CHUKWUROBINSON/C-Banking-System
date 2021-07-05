/*

This file contains all the main data struct in the system. These include:

1) CB_UserInfo: for generic user class.
2) CB_CustomerInfo: for specific customer user class.
3) CB_AdminInfo: for specific administrator user class.
4) CB_UserNote: for a single user notification.
5) CB_UserTransacHstr: for single user transaction record.
*/
#ifndef CB_MODELS //include guard
#define CB_MODELS

#ifndef CB_STRING__LENGTHS

//defining some constants
#define MID_STRG_LENGTH 50
#define SHORT_STRG_LENGTH 20
#define LONG_STRG_LENGTH 100
#define V_LONG_STRG_LENGTH 200

#endif
#include <string.h>
#include <time.h>

void CB_cleanStdin(){
  int c;
  
  
  while((c = getchar()) != '\n' && c != EOF);
}

void CB_timeStampToGmtStrg(time_t timeStamp, char *strg, int UsertimeDiff){
  
  int serverTimeDiff =  gmtime(&timeStamp)->tm_hour - localtime(&timeStamp)->tm_hour;
  
  time_t adjustedServerTimeStamp = timeStamp + serverTimeDiff * 3600; //now the server has GMT/UTC time
  
  time_t userTime = adjustedServerTimeStamp + (UsertimeDiff * 3600);
  
  struct tm * tm = gmtime(&userTime);
  
  
  strftime(strg, V_LONG_STRG_LENGTH,"%a %d %b %Y   %H:%M:%S %p",tm);
  
  
  
}

typedef struct CB_UserInfo{
  
  char userId[MID_STRG_LENGTH];
  time_t createdAt;
  int timeDiff;
  char surname[MID_STRG_LENGTH];
  char firstName[MID_STRG_LENGTH];
  char lastName[MID_STRG_LENGTH];
  char email[MID_STRG_LENGTH];
  char password[MID_STRG_LENGTH];
  char phoneNumber[SHORT_STRG_LENGTH];
  char homeAdress[LONG_STRG_LENGTH];
  char securityQuestion[LONG_STRG_LENGTH];
  char securityAnswer[LONG_STRG_LENGTH];
  char preferedTitle[SHORT_STRG_LENGTH];
  char gender;
  char dateOfBirth[SHORT_STRG_LENGTH];
  time_t accountFreeze;
  char createdAtToStrg[V_LONG_STRG_LENGTH];
  
} CB_UserInfo;

typedef struct CB_AdminInfo{
  char officeAdress[LONG_STRG_LENGTH] ;
} CB_AdminInfo;

void CB_initAdminInfo(CB_AdminInfo *user,char *officeAdress){
  
  strcpy(user->officeAdress, officeAdress);
  
}
void CB_copyAdminInfo(CB_AdminInfo *dest, CB_AdminInfo *src){
  
  strcpy(dest->officeAdress, src->officeAdress);
  
}



typedef struct CB_CustomerInfo{
  int creditBalance;
  int loanBalance;
} CB_CustomerInfo;


void CB_initCustomerInfo(CB_CustomerInfo *user,int creditBalance,int loanBalance){
  
  user->creditBalance = creditBalance;
  user->loanBalance = loanBalance;
  
}
void CB_copyCustomerInfo(CB_CustomerInfo *dest, CB_CustomerInfo *src){
  dest->creditBalance = src->creditBalance;
  dest->loanBalance = src->loanBalance;
}
  
void CB_initUserInfo(CB_UserInfo *user,char *surname, char *firstName, char *lastName, char *email, char *password, char *homeAdress, char *phoneNumber, char *dateOfBirth, char *securityQuestion, char *securityAnswer, char gender, char *preferedTitle, time_t accountFreeze, time_t createdAt,char *userId){

  strcpy(user->userId,userId );
  strcpy(user->surname,surname );
  strcpy(user->firstName,firstName );
  strcpy(user->email,email );
  strcpy(user->lastName,lastName);
  strcpy(user->password,password );
  strcpy(user->homeAdress,homeAdress );
  strcpy(user->phoneNumber,phoneNumber );
  strcpy(user->securityQuestion,securityQuestion );
  strcpy(user->securityAnswer,securityAnswer );
  strcpy(user->preferedTitle,preferedTitle);
  strcpy(user->dateOfBirth, dateOfBirth );
  user->gender = gender;
  user->accountFreeze = accountFreeze;
  user->createdAt =  createdAt;
  
  //TODO: change 1 to message time zone
  
  CB_timeStampToGmtStrg(createdAt, user->createdAtToStrg, 1);
  //TODO: change 1 to message time zone
  
  
  
  
  
}
void CB_copyUserInfo(CB_UserInfo *dest, CB_UserInfo *src){
  
  strcpy(dest->userId,src->userId );
  strcpy(dest->lastName,src->lastName);
  strcpy(dest->surname,src->surname );
  strcpy(dest->firstName,src->firstName );
  strcpy(dest->email,src->email );
  strcpy(dest->password,src->password );
  strcpy(dest->homeAdress,src->homeAdress );
  strcpy(dest->phoneNumber,src->phoneNumber );
  strcpy(dest->securityQuestion,src->securityQuestion );
  strcpy(dest->securityAnswer,src->securityAnswer );
  strcpy(dest->preferedTitle,src->preferedTitle);
  strcpy(dest->dateOfBirth, src->dateOfBirth );
  dest->gender = src->gender;
  dest->accountFreeze = src->accountFreeze;
  dest->createdAt =  src->createdAt;
  strcpy(dest->createdAtToStrg,src->createdAtToStrg);
  
  
  
}

typedef struct CB_User{
  
  CB_UserInfo userInfo;
  CB_CustomerInfo customerInfo;
  CB_AdminInfo adminInfo;
} CB_User;

void CB_initUser(CB_User *user,char *surname, char *firstName, char *lastName, char *email, char *password, char *homeAdress, char *phoneNumber, char *dateOfBirth, char *securityQuestion, char *securityAnswer, char gender, char *preferedTitle, time_t accountFreeze, time_t createdAt,char *userId, int creditBalance,int loanBalance, char *officeAdress){
  
  CB_initUserInfo(&user->userInfo,surname,firstName,lastName,email,password,homeAdress,phoneNumber,dateOfBirth, securityQuestion,securityAnswer,gender,preferedTitle, accountFreeze,createdAt,userId);
  
  CB_initCustomerInfo(&user->customerInfo,creditBalance,loanBalance);
  
  CB_initAdminInfo(&user->adminInfo,officeAdress);
  
  
}

void CB_copyUser( CB_User *dest, CB_User *src){
  
  CB_copyUserInfo(&dest->userInfo,&src->userInfo);
  CB_copyCustomerInfo(&dest->customerInfo, &src->customerInfo);
  CB_copyAdminInfo(&dest->adminInfo, &src->adminInfo);
  
}

int CB_compareUser(CB_User * user1, CB_User *user2){
  
  int testBit;
  
    if((testBit =  strcmp(user1->userInfo.surname,user2->userInfo.surname))){
       return testBit;
    }
    else if((testBit = strcmp(user1->userInfo.firstName,user2->userInfo.firstName))){
      return testBit;
    }
    
    return strcmp(user1->userInfo.lastName,user2->userInfo.lastName);
}

//Todo: this function is not complete. Not all members of UserInfo have been added, e.g account freezeToStrg, TimeZone, etc

void CB_userInfoToString(CB_UserInfo *user, char *userStr){
  
  sprintf(userStr,"\nUser ID: %s \n __________ \nFull Name: %s %s %s\nContact Details:\n\tAdress: %s\n\tPhone Number: %s \nOther Details:\n\tGender: %c\n\tPrefered Title: %s",user->userId,user->surname, user->firstName, user->lastName,user->homeAdress, user->phoneNumber, user->gender,user->preferedTitle);
  
}

void CB_customerUserInfoToStrg(CB_User *customerUser, char *strg){
  
  char tempStrg[sizeof(CB_User) + 40];
  
  CB_userInfoToString(&customerUser->userInfo,strg);
  sprintf(tempStrg,"\nAccount Details: Credit Balance: %d Loan Balance: %d\nThis account was created on : %s", customerUser->customerInfo.creditBalance, customerUser->customerInfo.loanBalance, customerUser->userInfo.createdAtToStrg);
  
  strcat(strg,tempStrg);
}

void CB_AcustomerUserInfoToStrg(CB_User *customerUser, char *strg){
  
  char tempStrg[sizeof(CB_User) + 40];
  
  CB_userInfoToString(&customerUser->userInfo,strg);
  sprintf(tempStrg,"\nLogin Details:\n\tEmail:%s\n\tPassword:%s \nCustomer Account Details:\n\tCredit Balance: %d\n\tLoan Balance: %d\nThis account was created on : %s", customerUser->userInfo.email, customerUser->userInfo.password,customerUser->customerInfo.creditBalance, customerUser->customerInfo.loanBalance, customerUser->userInfo.createdAtToStrg);
  strcat(strg,tempStrg);
}

void CB_adminUserInfoToStrg(CB_User *customerUser, char *strg){
  
  char tempStrg[sizeof(CB_User) + 40];
    
  CB_userInfoToString(&customerUser->userInfo,strg);
  sprintf(tempStrg,"\nLogin Details:\n\tEmail:%s\n\tPassword:%s \nAdmin Account Details:\n\tOffice Adress: %s\nThis account was created on : %s", customerUser->userInfo.email, customerUser->userInfo.password, customerUser->adminInfo.officeAdress, customerUser->userInfo.createdAtToStrg);
  strcat(strg,tempStrg);
}

typedef struct CB_Message{
  
  char userId[MID_STRG_LENGTH];
  time_t createdAt;
  char message[V_LONG_STRG_LENGTH];
  char createdAtToStrg[V_LONG_STRG_LENGTH];
} CB_Message;

void CB_initMessage(CB_Message *msg,char *userId, time_t createdAt, char *message){
  
  strcpy(msg->userId,userId);
  msg->createdAt = createdAt;
  strcpy(msg->message,message);
  
  //TODO: change 1 to message time zone
  
  CB_timeStampToGmtStrg(createdAt, msg->createdAtToStrg, 1);
  //TODO: change 1 to message time zone
   
}

void CB_copyMessage(CB_Message *dest, CB_Message *src){
  
  strcpy(dest->userId,src->userId);
  dest->createdAt = src->createdAt;
  strcpy(dest->message,src->message);
  
  
}

int CB_compareMessage(CB_Message *msg1, CB_Message *msg2){
  
  return  msg1->createdAt - msg2->createdAt;
}

void CB_messageToStrg(CB_Message *msg, char *strg){
  
 sprintf(strg,"%s:\t%s\n_______\n%s",msg->userId,msg->message,msg->createdAtToStrg); 
  
}



//Test function for this header
void CB_MODELS_TEST_inputMessage(CB_Message *msg){
  
  char myMsg[V_LONG_STRG_LENGTH],msgStr[V_LONG_STRG_LENGTH];
  
  printf("\nPlease input a message\n");
  fgets(myMsg, V_LONG_STRG_LENGTH, stdin);
  myMsg[strcspn(myMsg,"\n")] = '\0'; //remove new line character
  
  CB_initMessage(msg,"uuid",time(NULL),myMsg);
  
  CB_messageToStrg(msg,msgStr);
  printf("%s",msgStr);
  
}


void CB_inputUser(CB_User *user){
  char surname[MID_STRG_LENGTH], firstName[MID_STRG_LENGTH],lastName[MID_STRG_LENGTH];
  printf("\nInput user's surname first name and last name\n");
  scanf("%s %s %s",surname,firstName,lastName);
  CB_cleanStdin();
 
  
  char userId[MID_STRG_LENGTH];
  time_t createdAt = time(NULL) ;
  char timestampText[MID_STRG_LENGTH];
  sprintf(timestampText,"%ld", createdAt);
  
  char email[MID_STRG_LENGTH] = "chukwurobbi@gmail.com";
  char password[MID_STRG_LENGTH] = "submarine14";
  char phoneNumber[SHORT_STRG_LENGTH] = "07061580886";
  char homeAdress[LONG_STRG_LENGTH] = "Iwofe, by St John's bus stop";
  char securityQuestion[LONG_STRG_LENGTH]= "What is your father's name";
  char securityAnswer[LONG_STRG_LENGTH] = "Anayo Rufus";
  char preferedTitle[SHORT_STRG_LENGTH] =  "Mr";
  char gender = 'M';
  char dateOfBirth[SHORT_STRG_LENGTH] = "20/04/2000";
  time_t accountFreeze = -1;
  int creditBalance = 10000;
  int loanBalance = 67;
  char officeAdress[LONG_STRG_LENGTH] = "Mile 3, central Port Harcourt";
   
  strcat(timestampText,surname);
  strcpy(userId,timestampText);
  
  CB_initUser(user,surname,firstName,lastName,email,password,homeAdress,phoneNumber,dateOfBirth, securityQuestion,securityAnswer,gender,preferedTitle, accountFreeze,createdAt,userId, creditBalance,loanBalance,officeAdress);
  

}

void CB_MODELS_TEST(){
  
  CB_Message msg;
  
  /*
  CB_User user;
  
  
  CB_inputUser(&user);
  
  
 char userString[V_LONG_STRG_LENGTH];
    
  
  CB_adminUserInfoToStrg(&user, userString);
  
  printf("%s", userString);
  */
  CB_MODELS_TEST_inputMessage(&msg);
  
  /*printf(" \n %s %s %s \n createdAt :%s \n",user.userInfo.userId, user.userInfo.surname, user.userInfo.dateOfBirth, user.userInfo.createdAtToStrg);
  
  CB_User user1;
  CB_copyUser(&user1,&user);
  strcpy(user1.userInfo.surname, "Paul");
  
  strcpy(msg.userId ,user.userInfo.userId);
  msg.createdAt = time(NULL);
  strcpy(msg.message,"Transaction successful, well done sir!");
  CB_Message msg2;
  CB_copyMessage(&msg2,&msg);
  msg2.createdAt = 500;
  printf(" \n %s %s %s \n",user1.userInfo.userId, user1.userInfo.surname, user1.userInfo.dateOfBirth);
  
  printf("\n\n _________\n\n");
  printf("%s %ld %s", msg.userId, msg.createdAt,msg.message);
  printf("\n I'm comparing :%d and messages %d\n", CB_compareUser(&user1,&user), CB_compareMessage(&msg,&msg2));
*/  
}




#endif