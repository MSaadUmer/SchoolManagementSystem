/* 
*********************************************************************                 
                   TEACHING ASSISTANT APPLICATION                   
                           A project by                             
        Muhammad Saad Umer    Mati Ur Rehman    Ahmad Shajee    
           CS-144 Fundamentals of programming Final Project

                    Default Password: Faculty@123
            Please Input Data Before Calling Attendance
*********************************************************************        
*/

#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<unistd.h>
#include<ctype.h>
#include <string.h>
typedef struct
{
    char b[20];
}
                                            // making a struct type variable
log;
log faculty;
FILE *attendance_sheet;
FILE *student_rec;
int log_s = sizeof(faculty);
FILE *Admin;
                                            // Function for logging in to the TA - system
typedef struct Student{

  char name[30];
  int roll_2;
  char attended;
  char roll[100];
  char remarks[100];
  float exam,quiz,assignment;
}student;
student fop[100]={}; 
student array[100];
student student_test;
                                            // Function prototypes                                     
_Bool login_sys();
void attendance();
void Grading_system();
void read_Data();
void write_Data();
void Certain_student();
void New_student();
void Marking_class();
void Marks_Checking(); 
void Calculating_grade();
void Delete_student();
void Writing_diary();
void Read_notes();
void Write_notes();
void Delete_notes();
void Delete_a_certain_note();
void Students_data();
void Sort_Name();
void Access_Previous();
void Take_Attendance();
int  settings();
int  getch();
void all_student_data();

int main()
{   read_Data();
    fflush(stdout);
    for (int i = 0;!login_sys() && i < 3; i++) // the user has three tries to login in otherwise they are required to restart the program
    {
        if (i == 2)
        {

            printf("\033[0;31m");
            system("cls");
            printf("\n\n\n\n\n\n");
            printf("You have entered wrong password 3 times.\n");
            printf("Restart!\n\n");
            printf(" \033[0;37m");
            return 0;
        }
    }
   
    printf("\033[0;37m");
    printf("\n\n");

    while(1){
        system("cls");
        printf("\033[0;36m");
    printf("\n\t*********************************************************\n");    
    printf("\t*\t---==Welcome to Teaching Assistant==---\t       *\n");
    printf("\t*\t1.Students Data Management         \t\t*\n");
    printf("\t*\t2.Grade Book                       \t\t*\n");
    printf("\t*\t3.Attendance Manager               \t\t*\n");
    printf("\t*\t4.Diary                            \t\t*\n");
    printf("\t*\t5.Change Password                  \t\t*\n");
    printf("\t*\t6.Exit program                     \t\t*\n");
    printf("\t*********************************************************\n\n\n");
            printf("\033[0;37m");
     printf("Enter Your Choice:");
    int choice;
    char character;
    scanf("%d",&choice);
    switch (choice){
        case 1:Students_data();
               break;
        case 2:Grading_system();
               break;
        case 3:
                write_Data();
                read_Data();
                fclose(fopen("student_rec.txt","wb"));
                Admin = fopen("student_rec.txt", "ab");
                for(int i = 0; ;i++){
                    if(fop[i].name[0]=='\0'){
                        break;
                    }
                    if (fop[i].name[1]=='\0'){
                        i++;
                        continue;
                    }
                    // student_test = fop[i];
                    strcpy(student_test.name, fop[i].name);
                    student_test.attended = fop[i].attended;
                    student_test.roll_2 = fop[i].roll_2;

                    fwrite(&student_test, sizeof(student), 1, Admin);
                }
                fclose(Admin);
                attendance();
               break;
        case 4:Writing_diary();
               break;
        case 5:while(!settings())
        {
            ;
        }
               break;       
        case 6:
               write_Data();
               return 0;       
        default:printf("    Inavlid Choice\n\tPlease Choose again");
              printf("\nEnter any key to continue...");
              scanf("%c",&character);          
    }
    }
    
}
// This function opens the attendance sheet (Call by name)
void all_student_data(){
    printf("\t\t\tAll Students Data\n ");
    int i=0;
    char a;
    scanf("%c",&a);
    while(1){
        if(fop[i].name[0]=='\0'){
            break;
        }
        if(fop[i].name[2]=='\0'){
            i++;
            continue;
        }
   printf("\n\t***************************************************\n");
    printf("\t\t            Roll No : %s\n",fop[i].roll);
    printf("\t\t              Name  : %s\n",fop[i].name);
    printf("\t\t      Marks In Exam : %.2f\n",fop[i].exam);
    printf("\t\t      Marks In Quiz : %.2f\n",fop[i].quiz);
    printf("\t\tMarks In Assignment : %.2f\n",fop[i].assignment);
    printf("\t\t            Remarks : %s\n\n\n",fop[i].remarks);
    printf("\t******************************************************\n\n\n");
    i++;
    }
    printf("\t\tEnter any key to continue....");
    scanf("%c",&a);
}
void Take_Attendance()
{
    printf("\033[0;36m");
    system("cls");
    char today_Date[12];
    time_t t = time(NULL);
    struct tm time = *localtime(&t);
    printf("\t\t\t\t   STUDENT RECORDS - Date: %02d/%02d/%2d",time.tm_mday, time.tm_mon+1, time.tm_year+1900);
    printf(" \033[0;37m\n");
    sprintf(today_Date, "%02d%02d%2d.txt", time.tm_mday, time.tm_mon+1, time.tm_year+1900);
    if (fopen(today_Date, "rb+")==NULL)
    {
        attendance_sheet = fopen(today_Date, "wb+");
    }
    fclose(attendance_sheet);
    attendance_sheet = fopen(today_Date, "rb+");
    student_rec = fopen("student_rec.txt", "rb");
    fseek(student_rec, 0, SEEK_SET);
    for(int i = 1; fread(&student_test, sizeof(student), 1, student_rec)==1; i++)
    {
        printf("%i.", i);
        printf("\tName    : %s\n", student_test.name);
        printf("\tID      : %i\n", student_test.roll_2);
        printf("\tPresent/Absent (p/a) : ");
        scanf(" %c", &(student_test.attended));
        while (!(student_test.attended=='p'|| student_test.attended=='a'))
        {
            printf("\nPresent/Absent (p/a) : ");
            fflush(stdin);
            scanf("%c", &(student_test.attended));
            tolower(student_test.attended);
        }
        fwrite(&student_test, sizeof(student), 1, attendance_sheet);
        printf("\n");
    }
    fclose(attendance_sheet);
    fclose(student_rec);
    fflush(stdin);
    printf("Enter any key to continue......");
    getchar();
    attendance();
}
// This fuction allows user to access previous attendance sheets, The user is required to enter date in particular format
void Access_Previous()
{
    system("cls");
    char date[7+6];
    printf("Enter date of attendance in following format ");
    printf("\033[0;33m");
    printf("[DD-MM-YYYY]: ");
    printf("\033[0;37m");
    fflush(stdin);
    scanf("%c%c-%c%c-%c%c%c%c", &date[0],&date[1],&date[2],&date[3], &date[4], &date[5], &date[6],&date[7]);
    date[8] = '.';date[9] = 't'; date[10] = 'x'; date[11] = 't';date[12] = '\0';
    student_rec = fopen(date, "rb");
    if (student_rec!=NULL)
    {
        printf("Information Retrieval Successful\nEnter any key to display........");
        fflush(stdin);
        getchar();
        system("cls");
        printf("\033[0;36m");
        system("cls");
        printf("\t\t\t\t   STUDENT RECORDS - DATED : %c%c-%c%c-%c%c%c%c\n\n",date[0],date[1],date[2],date[3], date[4], date[5], date[6],date[7]);
        printf("\033[0;37m\n");
        fflush(stdout);
        for (int j = 1; fread(&student_test, sizeof(student), 1, student_rec) == 1;j++)
        {
            printf("%i.", j);
            printf("\tName    : %s\n", student_test.name);
            printf("\tID      : %i\n", student_test.roll_2);
            printf("\tPresent/Absent: %c\n", student_test.attended);
        }
        fclose(student_rec);
        printf("\nSuccessful! Press any key to continue........");
        fflush(stdin);
        getchar();
        attendance();

    }
    else
    {
        printf("\nNo records found\n");
        printf("Enter any key to continue........");
        fflush(stdin);
        getchar();
        attendance();
    }

}
// This function allows user to have a custom password
int settings()
{
    printf("\033[0;37m");
    char name[20];
    char check[20];
    printf("Enter New Password: ");
    scanf("%s", &name);
    printf("Confirm New Password: ");
    scanf("%s", &check);
    if (!strcmp(check, name))  //  confirming and comparing the new password
    {
        strncpy(faculty.b, name, sizeof(faculty.b));
        Admin = fopen("priv.bin", "w");
        fwrite(&faculty, log_s, 1, Admin);
        fclose(Admin);
        printf("The Password has been successfully changed!\nEnter any key to continue........");
        fflush(stdin);
        getchar();
        return 1;
    }
    printf("\nThe confirmation password doesn't match!\nPlease Enter any key to try again.......");
    fflush(stdin);
    getchar();
    return 0;

}
// This function alphabetically sorts the attendance sheet.
void Sort_Name()
{
    system("cls");
    student_rec = fopen("student_rec.txt", "rb+");
    int count = 0;
    fseek(student_rec, 0, SEEK_SET);
    for(int i = 0; fread(&student_test, sizeof(student), 1, student_rec) == 1; i++)
    {
        array[i] = fop[i];
        count++;
    }
    fclose(student_rec);
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (strncmp(array[i].name, array[j].name, 5) < 0)
            {
                student_test = array[i];
                array[i] = array[j];
                array[j] = student_test;
            }
        }
    }
    fclose(fopen("student_rec.txt", "w"));
    student_rec = fopen("student_rec.txt", "rb+");
    for (int i = 0; fwrite(&array[i], sizeof(student), 1, student_rec)&& i < count-1;i++);
    fclose(student_rec);
    printf("Successful! Press any key to continue........");
    fflush(stdin);
    getchar();
    attendance();
}
// This fuctions opens the menu for Attendance Manager
void attendance()
{
    system("cls");
    printf("\033[0;36m");
    printf("\t\t\t\t   ATTENDANCE MANAGER\n\n");
    printf(" \033[0;37m");
    printf("\n1 - Sort by Name\n2 - Access previous records\n3 - Call Attendance\n4 - Main Menu\n\n");
    int a;
    scanf(" %i", &a);
    switch (a)
    {
        case 1:
            Sort_Name();
            break;
        case 2:
            Access_Previous();
            break;
        case 3:
            Take_Attendance();
            break;
        case 4:
            return;
    }
}
void Students_data(){
    while(1){
    system("cls");
            printf("\033[0;33m");
    printf("\t*********************************************************\n");    
    printf("\t*\t---==Welcome to Students Data==--- \t\t*\n");
    printf("\t*\t1. Check Data of a Certain Student \t\t*\n");
    printf("\t*\t2. New Students Data               \t\t*\n");
    printf("\t*\t3. Delete a Student Record         \t\t*\n");
    printf("\t*\t4. All students data               \t\t*\n");
    printf("\t*\t5. Main Menu                       \t\t*\n");
    printf("\t*********************************************************\n\n\n");
        printf(" \033[0;37m");
    printf("Enter Your Choice:");
    int choice;
    char character;
    scanf("%d",&choice);
    switch(choice){
        case 1:Certain_student();
               break;
        case 2:New_student(); 
               break;
        case 3:Delete_student();
               break;
        case 4:all_student_data();
              break;                     
        case 5:printf("Program Executed Successfully.\n");
               return;   
        default:printf("    Inavlid Choice\n\tPlease Choose again");
              printf("\nEnter any key to continue...");
              scanf("%c",&character);                          
    }
    }   
}
// This function prompts user to enter password and enter into the TA - Application.
// Three tries are allowed if wrong password is entered
_Bool login_sys()
{
    system("cls");
    printf("\n\n\n\n");
    printf("\033[0;33m");
    printf("\t\t\t\t\t             #####################################\n");
    printf("\t\t\t\t\t             #                                   #\n");
    printf("\t\t\t\t\t             #         TEACHING ASSISTANT        #\n");
    printf("\t\t\t\t\t             #            LOGIN PORTAL           #\n");
    printf("\t\t\t\t\t             #                                   #\n");
    printf("\t\t\t\t\t             #####################################\n\n\n");
    if (fopen("priv.bin", "rb+")==NULL)
        {Admin = fopen("priv.bin","w");fclose(Admin);}

    Admin = fopen("priv.bin","rb+");        // opening file in read+write mode
    if (!fread(&faculty, log_s, 1, Admin))
    {
        strncpy(faculty.b, "Faculty@123", sizeof(faculty.b));
        fwrite(&faculty,log_s, 1, Admin);   // writing Password and Faculty ID
    }
    char pass[20];
    char k;
    int i = strlen(faculty.b);
    int j;
    printf("\t\t\t\t\t             Enter Password: ");
    for (j = 0;j<i; j++)
    {
        k=getch();
        pass[j] = k;
        k = '*';
        printf("%c", k);
    }
    pass[i]='\0';
    fclose(Admin);                          // close the opened file after modifications (if req)
    if (!strcmp(pass, faculty.b))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void Grading_system (){

    while(1){
    system("cls");
    printf("\t*********************************************************\n");    
    printf("\t*\t---==Welcome to Grades Section==---\t\t*\n");
    printf("\t*\t1.Marks for whole Class            \t\t*\n");
    printf("\t*\t2.Checking marks for a certain test\t\t*\n");
    printf("\t*\t3.Check Final Grades               \t\t*\n");
    printf("\t*\t4.Return to main menu              \t\t*\n");
    printf("\t*********************************************************\n\n\n");
    printf("Enter Your Choice:");
    int choice;
    char character;
    scanf("%d",&choice);
    switch(choice){
        case 1:Marking_class();
               break;   
        case 2:Marks_Checking();
               break; 
        case 3:Calculating_grade();
               break;              
        case 4: printf("Program Executed Successfully.\n");
               return;   
        default:printf("    Inavlid Choice\n\tPlease Choose again");
              printf("\nEnter any key to continue...");
              scanf("%c",&character);                          
    }
    }   
}
/*This Function is used to Delete a Certain students Data.We do it by changing the second character of name to nullcharcter and 
when we further operate stidents in other files we will keep checking if the student name has second character as null
if it is found to be null it is not operated.In this way at the end of program this data is not written in file so next time we
open program student data is lost completely */
void Delete_student(){
    system("cls");
    printf("Enter student name :");
    char arr[30];
    int i=0;
    scanf("%c",&arr[0]);
    gets(arr);
    while(1){
        if(strcmp(fop[i].name,arr)==0){
            break;
        }
        i++;
    }
    fop[i].name[2]='\0';
    printf("  Student data has been Deleted  \n");
    printf("Enter Any key to Continue......");
    scanf("%c",&arr[0]);
}
/*For calculating the final grade of student we ask the teacher to enter the percentage weightage he wants to assign to each 
student later on the data of each student is processed and a final sum of the scores in each test gives us the resulting 
grade*/
void Calculating_grade(){
    system("cls");
    int exam,quiz,assignment,sum;
    int i=0;
    char a;
    again:
    printf("\t  Select Percentage weightage for Each Test \n\n");
    printf("\n      Enter Percentage For Quiz : ");
    scanf("%d",&quiz);
    printf("\nEnter Percentage For Assignment : ");
    scanf("%d",&assignment);
    printf("\n      Enter Percentage For Exam : ");
    scanf("%d",&exam);
    if(exam+quiz+assignment!=100){
      printf("\n\n\tOverall percentage is not 100.\n\t\tPlease Enter again\n");
      printf("\n\tEnter any key to Continue....");
       scanf("%c",&a); scanf("%c",&a);
       system("cls");
       goto again;
    }
    printf("\n\n");
    while (1){
        sum=0;
        if(fop[i].name[0]=='\0'){
            break;
        }
        if(fop[i].name[2]=='\0'){
            i++;
            continue;
        }
        sum=(fop[i].exam/100)*exam;
        sum+=(fop[i].quiz/10)*quiz;
        sum+=(fop[i].assignment/50)*assignment;
        printf("\t\t%-15s",fop[i].name);
        if(sum>=90){
            printf(" A Grade\n ");
        }else if(sum>=80&&sum<90){
            printf(" B+ Grade\n ");
        }else if(sum>=70&&sum<80){
            printf(" B Grade\n");
        }else if(sum>=60&&sum<70){
            printf(" C+ Grade\n");
        }else if(sum>=50&&sum<60){
            printf(" C Grade\n");
        }else if(sum<50){
            printf(" F Grade\n");
        }
        i++;
    }
    printf("\n\n\t These are the Final grades of the Students.\n\n");
    scanf("%c",&a);
    printf("    Enter any Key to Continue...");
    scanf("%c",&a);
}
/*This function will help teacher to check the marks assigned to each student.This function will be help full as teacher will be 
able to analyze the class average and also to check if any student was awarded wrong marks by mistake */
void Marks_Checking(){
    system("cls");
   int choice,i=0,avg=0;
   char a;
   float sum=0;
       printf("\033[0;33m");
   printf("\t**************************\n");
   printf("\t*\t1.Exam           *\n");
   printf("\t*\t2.Quiz           *\n");
   printf("\t*\t3.Assignment     *\n");
   printf("\t**************************\n\n\n");
       printf("\033[0;37m");
   printf("Choose the subject for Checking Marks:");
   scanf("%d",&choice);
   scanf("%c",&a);
       printf("\033[0;33m");
   printf("\nName           Roll no      Marks\n");
       printf("\033[0;37m");
   while(1){
      if(fop[i].name[1]=='\0'){
        break;
      }
      if(fop[i].name[2]=='\0'){
        i++;
        continue;
      }
      printf("%-15s%-11s  ",fop[i].name,fop[i].roll);
      switch(choice){
      case 1:printf("%.2f\n",fop[i].exam);
             sum+=fop[i].exam;
             break;      
      case 2:printf("%.2f\n",fop[i].quiz);
            sum+=fop[i].quiz;
            break;
      case 3:printf("%.2f\n",fop[i].assignment);
             sum+=fop[i].assignment;
      }
      i++;avg++;
   }
      printf("\n\nClass Average is %f\n\n",sum/avg);
      printf("Enter any key to continue...");
      scanf("%c",&a);
}
/*This function will enable teacher to award marks to all students at the same time.This will save a lot of time for teacher.
Each student is accessed by using a loop which terminates as it encounters a name will its first character as null character */
void Marking_class(){
    int choice,i=0;
    char a;
    system("cls");
        printf("\033[0;33m");
    printf("\t**************************\n");
   printf("\t*\t1.Exam           *\n");
   printf("\t*\t2.Quiz           *\n");
   printf("\t*\t3.Assignment     *\n");
   printf("\t**************************\n\n\n");
       printf("\033[0;37m");
   printf("Choose the subject for marking :");
   scanf("%d",&choice);
   scanf("%c",&a);
   printf("Write Marks In front of respective students names :\n");
    printf("\033[0;33m");
   printf("\nName           Roll no      Marks\n");
       printf("\033[0;37m");
   while(1){
      if(fop[i].name[0]=='\0'){
        break;
      }
      if(fop[i].name[1]=='\0'){
        i++;
        continue;
      }
      again:
      printf("%-15s%-11s  ",fop[i].name,fop[i].roll);
      switch(choice){
      case 1:scanf("%f",&fop[i].exam);
             if(fop[i].exam>100){
                printf("\tInvalid marks \n");
                printf("\tEnter marks again\n");
                goto again;
             }
             break;      
      case 2:scanf("%f",&fop[i].quiz);
            if(fop[i].quiz>10){
                printf("\tInvalid marks \n");
                printf("\tEnter marks again\n");
                goto again;
             }
            break;
      case 3:scanf("%f",&fop[i].assignment);
             if(fop[i].assignment>50){
                printf("\tInvalid marks \n");
                printf("\tEnter marks again\n");
                goto again;
             }
      }
      i++;
   }
   printf("    Marks Entered Successfully\n\n ");
    printf("     Enter any key to continue...");
    scanf("%c",&a);    
   return;
}
/*This function is helpful in adding new student.It also enables teacher to enter marks for tests along with remarks about him at the same 
time.position for new student in data structure is found by a lpp that terminates as soon as it encounters a name with its first character 
as null.Null character shows that this name has not been initialized before.*/
void New_student(){
    int i=0,choice;
    char arr[10];
    char *arr2;
    system("cls");
    while(1){
        if(fop[i].roll[0]=='\0'){
            break;
        }
        i++;
    }
    scanf("%c",&fop[i].name);
    printf("\t\t      Enter name  : ");
    gets(fop[i].name);
    again:
    printf("\n\t       Enter roll number  : ");
    gets(fop[i].roll);
    for (int j = 0; fop[i].roll[j] != '\0'; j++ )
    {
        if (!isdigit(fop[i].roll[j]))
        {
            printf("        Invalid Entry\n        Must be a numeric value!\n");
            goto again;
        }
    }
    fop[i].roll_2=strtod(arr,&arr2);
    printf("\n\nIf You want to enter marks enter 1:");
    scanf("%d",&choice);
    if (choice==1){
    printf("\n            Enter marks in Exam :");
    scanf("%f",&fop[i].exam);
    while(fop[i].exam>100){
                printf("\tInvalid marks \n");
                printf("\tEnter marks again :");
                scanf("%f",&fop[i].exam);
             }
    printf("             Enter marks in Quiz :");
    scanf("%f",&fop[i].quiz);
     while(fop[i].quiz>10){
                printf("\tInvalid marks \n");
                printf("\tEnter marks again :");
                scanf("%f",&fop[i].quiz);
             }
    printf("         Enter marks in Assignment :");
    scanf("%f",&fop[i].assignment);
     while(fop[i].assignment>50){
                printf("\tInvalid marks \n");
                printf("\tEnter marks again :");
                scanf("%f",&fop[i].assignment);
             }
             }
    scanf("%c",&fop[i].remarks[0]);
    printf("\n\n\t            Enter remarks : ");
    gets(fop[i].remarks);
     printf("\n\tEnter any key to continue...");
      scanf("%c",&arr[0]);
}
/*Often teacher wants to check and edit Data of a certain student.This fiunction will help in operating a single student.First 
the sudent by using a string comparison function.Later on it prints the already available data about the student.After this the
teacher is given with the choice to edit any part of the data.*/
void Certain_student(){
    system("cls");
    printf("\n\n\t\tEnter Name of Student :");
    int i=0,choice;
    char arr[100]; 
    scanf("%c",&arr[0]);
    gets(arr);
    while(1){
        if(strcmp(fop[i].name,arr)==0){
            break;
        }
        if(fop[i].name[0]=='\0'){
            printf("\n\n   Student data not Found \n");
            printf("\nEnter any Key to Continue......");
            scanf("%c",&arr[0]);
            return;
        }
        i++;
    }
    printf("\n\t***************************************************\n");
    printf("\t\t            Roll No :%s\n",fop[i].roll);
    printf("\t\t              Name  :%s\n",fop[i].name);
    printf("\t\t      Marks In Exam :%.2f\n",fop[i].exam);
    printf("\t\t      Marks In Quiz :%,2f\n",fop[i].quiz);
    printf("\t\tMarks In Assignment :%.2f\n",fop[i].assignment);
    printf("\t\t            Remarks :%s\n\n\n",fop[i].remarks);
    printf("\t******************************************************\n\n\n");
    printf("\t******************************************************\n");
    printf("\t\tEnter any of the following command \n");
    printf("\t\t1.Edit name\n");
    printf("\t\t2.Edit roll number\n");
    printf("\t\t3.Edit Marks\n");
    printf("\t\t4.Edit remarks\n");
    printf("\t\t5.Return to main menu\n");
    printf("\t******************************************************\n\n");
    printf("\t\tEnter Your Choice :");
    scanf("%d",&choice);
    system("cls");
    scanf("%c",&arr[0]);
    switch (choice){
        case 1:printf("Enter new name :");
               gets(fop[i].name);
               break;
        case 2:again:
              printf("\nEnter New roll number :");
              gets(fop[i].roll);
              for (int j = 0; fop[i].roll[j] != '\0'; j++ )
            {
             if (!isdigit(fop[i].roll[j]))
               {
                printf("\n\n        Invalid Entry\n        Must be a numeric value!\n");
                goto again;
                }
            }
              break;
        case 3: printf("\t**************************\n");
                printf("\t*\t1.Exam           *\n");
                printf("\t*\t2.Quiz           *\n");
                printf("\t*\t3.Assignment     *\n");
                printf("\t**************************\n\n\n");
               printf("Choose for changing marks :");
               scanf("%d",&choice);
               switch(choice){
                case 1 :printf("Enter new marks for Exam :");
                        scanf("%d",&fop[i].exam);
                         while(fop[i].exam>100){
                        printf("\tInvalid marks \n");
                        printf("\tEnter marks again :");
                        scanf("%f",&fop[i].exam);
                        }
                        break;
                case 2 :printf("Enter New Marks For Quiz :");
                        scanf("%d",&fop[i].quiz);
                         while(fop[i].quiz>10){
                        printf("\tInvalid marks \n");
                        printf("\tEnter marks again :");
                        scanf("%f",&fop[i].quiz);
                        }
                        break;
                case 3: printf("Enter New Marks For Assignment :");
                        scanf("%d",&fop[i].assignment);
                        while(fop[i].assignment>50){
                        printf("\tInvalid marks \n");
                        printf("\tEnter marks again :");
                        scanf("%f",&fop[i].assignment);
                        }
                        break;                    
                case 4:printf("Enter New remarks :");
                        gets(fop[i].remarks);
                        break;
                case 5:  return;     
                default: printf("Wrong choice\n");                             
    }

}
}
/*This function is used at the start of the program.it will retreive all the data in the structures available.We didn't use the files 
in the program as the program is made for a single teachers use and data of a single teacher will be easily used during the program.The 
Data Written in the file is written in such a format that it is easy to convert that data into the available structure.fgets fuction is used 
to retreive data from the file and then it is sent to respective structure.For copying strings strcpy function is used.Also strtod fuction
is used to convert string itno float data type.  */
void read_Data(){
    FILE *Student;
    char arr[100];
    char *arr2;
    float marks;
    int i=0,j;
    Student =fopen("Student2.txt","r");
    if(Student==NULL){
        system("cls");
        printf("\n\n\n\n\n\t\t\t\t---===Welcome To Our Program for First Time===---\n");
        printf("\t\t\t\t       Your Password is Faculty@123\n\n\n");
        printf("\t\t\t\t         Enter 1 to continue...");
        int a = getchar();
        return;
    }
    while(1){
        char array[10];
        if(fgets(arr,100,Student)==NULL){
            return;
        }
        strcpy(fop[i].roll,arr);
        j=0;
        while(1){
            if(fop[i].roll[j]=='\n'){
                fop[i].roll[j]='\0';break;
            }j++;
        }
        fop[i].roll_2=strtod(arr,&arr2);
        fgets(arr,100,Student);
        strcpy(fop[i].name,arr);
        j=0;
        while(1){
            if(fop[i].name[j]=='\n'){
                fop[i].name[j]='\0';break;
            }j++;
        }
        fgets(arr,100,Student);
        fop[i].exam=strtod(arr,&arr2);
        fgets(arr,100,Student);
        fop[i].quiz=strtod(arr,&arr2);
        fgets(arr,100,Student);
        fop[i].assignment=strtod(arr,&arr2);
        fgets(arr,100,Student);
        strcpy(fop[i].remarks,arr);
        j=0;
        while(1){
            if(fop[i].remarks[j]=='\n'){
                fop[i].remarks[j]='\0';break;
            }j++;
        }
        i++;
    }
}
/*This is the last step each time program is terminated. It first clears the previous data in file by openning in write mode.
After this it writes data of each student in such a way that later on it is read Easily.gcvt function is used to convert float 
to string. */
void write_Data(){
     FILE *Student;
     char arr[10];
     int i=0;
     Student=fopen("Student2.txt","w");
   while(1){
    if(fop[i].roll[0]=='\0'){
        fclose(Student);
        return;
    }
    if(fop[i].name[2]=='\0'){
     i++;
     continue;
    }
   fprintf(Student,"%s",fop[i].roll);
   fprintf(Student,"%c",'\n');
   fprintf(Student,"%s",fop[i].name);
   fprintf(Student,"%c",'\n');
   gcvt(fop[i].exam,4,arr);
   fprintf(Student,"%s",arr);
   fprintf(Student,"%c",'\n');
   gcvt(fop[i].quiz,4,arr);
   fprintf(Student,"%s",arr);
   fprintf(Student,"%c",'\n');
   gcvt(fop[i].assignment,4,arr);
   fprintf(Student,"%s",arr);
   fprintf(Student,"%c",'\n');
   if(fop[i].remarks[0]=='\0'){
    strcpy(fop[i].remarks,"No Remarks");
   }
   fprintf(Student,"%s",fop[i].remarks);
   fprintf(Student,"%c",'\n');
   i++;
   }
}
void Writing_diary(){
   int choose,character;
    while(1){
    system("cls");
    printf("\t\t********************************************\n");
    printf("\t\t*\t1.Read Existing Notes\t\t   *\n");
    printf("\t\t*\t2.Add Notes\t\t\t   *\n");
    printf("\t\t*\t3.Delete Existing Notes\t\t   *\n");
    printf("\t\t*\t4.Return\t\t\t   *\n");
    printf("\t\t********************************************\n\n\n");
    printf("Enter Choice :");
    scanf("%d",&choose);
    scanf("%c",&character);
    character='0';
    switch(choose){
        case 1 :Read_notes();
                break;
        case 2:Write_notes();
               break;
        case 3: Delete_notes();
               break;      
        case 4:return;
        default:printf("False Command.\n");
                printf("\n Enter any Key to continue......");
                scanf("%c",&character);               
    }
  }
}
void Read_notes(){
              FILE *NOTES1;
              char character,eof_character;
                NOTES1=fopen("notes.txt","r");
                if (NOTES1==NULL){
                    printf("There are no NOTES");
                   printf("Enter any Key to continue...");
                   scanf("%c",&character);
                   return;
                }
                    while((eof_character=fgetc(NOTES1))!=EOF)
                    {
                    printf("%c",eof_character);
                    }
                    printf("\n\n\n");
                    printf("Enter 1 To Continue :");
                    scanf("%c",&character);
                    fclose(NOTES1);
                    return;
}
void Write_notes(){
                FILE *NOTES1;
                FILE *count;
                char characters[100];
                int counting,i;
                  NOTES1=fopen("notes.txt","r");
		            if(NOTES1==NULL){
						count=fopen("count.txt","w");
						fprintf(count,"%c","1");
						fclose(count);
					}
					fclose(NOTES1);
                    NOTES1=fopen("notes.txt","a");
                    printf("Enter Your Note:");
                    count=fopen("count.txt","r");
                    fscanf(count,"%s",characters);
					counting=atoi(characters);
                    fclose(count);
                    count=fopen("count.txt","w");
					sprintf(characters,"%d",counting+1);
                    fprintf(count,"%s",characters);
                    fclose(count);
					sprintf(characters,"%d",counting+1);
                    fprintf(NOTES1,"%s",characters);
                    fprintf(NOTES1,"%c",'.');
                    gets(characters);
                    fprintf(NOTES1,"%s",characters);
                    fprintf(NOTES1,"%c",'\n');
                    fclose(NOTES1);
                    return;
}
void Delete_notes(){
    while(1){
    system("cls");
    int choose;
    char character;
     FILE *NOTES1;
    printf("\t\t********************************************\n");
    printf("\t\t*\t1.Delete all Existing Notes \t   *\n");
    printf("\t\t*\t2.Delete a certain Note\t\t   *\n");
    printf("\t\t*\t3.Return to main menu  \t\t   *\n");
    printf("\t\t********************************************\n\n");
    printf("Enter Choice :");
    scanf("%d",&choose);
    switch (choose){
    case 1:
            NOTES1=fopen("notes.txt","w");
            printf("All Previous notes have been deleted.");
            printf("\nEnter Any Key to continue....");
            scanf("%c",&character);
            fclose(NOTES1);
            NOTES1=fopen("count.txt","w");
            fprintf(NOTES1,"%c",'c');
            fclose(NOTES1);
            break;
    case 2:Delete_a_certain_note();
          break;
    case 3:return;      
    default: printf("    Inavlid Choice\n\tPlease Choose again");
              printf("\nEnter any key to continue...");
              scanf("%c",&character);
          }   
        }
}
void Delete_a_certain_note(){
int choose,eof_character,i,j;
char character,numbers[10],characters[100];
FILE *NOTES1,*NOTES2,*count;
    NOTES1=fopen("notes.txt","r");
    while((eof_character=fgetc(NOTES1))!=EOF)
     {
        printf("%c",eof_character);
            }
        scanf("%c",&eof_character);
        fclose(NOTES1);
        printf("Enter Number :");
        gets(numbers);
        i=0;
    while(1){
    if(numbers[i]=='\0'){
         numbers[i]=='.';numbers[i+1]='\0';break;
        }
        i++;
    }
    NOTES1=fopen("notes.txt","r");
    NOTES2=fopen("notes2.txt","w");
	fclose(NOTES2);
    NOTES2=fopen("notes2.txt","a");
    while(fgets(characters,100,NOTES1)!=NULL){
         i=0;
        character=characters[i];
         i++;
    if(strstr(characters,numbers)==NULL){
     while(1){
        if(character==EOF){
         goto hell;
         }         
    fprintf(NOTES2,"%c",character);
         character=characters[i];
        i++;
    if (character=='\0'){
        fprintf(NOTES2,"%c",character);break;
        }
        }
      }
    }
            hell:
                 fclose(NOTES1);fclose(NOTES2);
                 NOTES1=fopen("notes.txt","w");
	            fclose(NOTES1);
                NOTES1=fopen("notes.txt","a");
                NOTES2=fopen("notes2.txt","r");
                j=1;
               while(fgets(characters,100,NOTES2)!=NULL){
                i=0;
	           if(j+48<58){
               characters[0]=j+48;}
	          else {
	          characters[0]=j/10+48;
	           characters[1]=j%10+48;
	           }
               character=characters[i];
             i++; j++;
             while(1){
            if(character==EOF){
              break;
             }         
            fprintf(NOTES1,"%c",character);
            character=characters[i];
            i++;
            if (character=='\0'){
            fprintf(NOTES2,"%c",character);break;
            }
          }
         }
          fclose(NOTES1);fclose(NOTES2);
          printf("Operation Successful.");
           count=fopen("count.txt","w");
          fprintf(count,"%c",j+47);
          fclose(count);
           printf("\n Enter any Key to continue......");
          scanf("%c",&character);
}