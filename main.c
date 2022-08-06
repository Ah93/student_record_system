#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

struct student{
    char stud_id[15];
    char stud_name[20];
	char stud_age[20];
    char stud_class[20];
    char stud_contact_number[20];
};

struct student stu;

void SetColor(int ForgC)
{
     WORD wordcolor;
     HANDLE studentHandleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO conscrbufinfo;
     if(GetConsoleScreenBufferInfo(studentHandleOutput, &conscrbufinfo))
     {
          wordcolor = (conscrbufinfo.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(studentHandleOutput, wordcolor);
     }
     return;
}

void ClearConsoleToColors(int ForgC, int BackC)
{
     WORD wordColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);

     HANDLE studentHandleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

     COORD coordinates = {0, 0};

     DWORD counting;

     CONSOLE_SCREEN_BUFFER_INFO conscrbufinfo;

     SetConsoleTextAttribute(studentHandleOutput, wordColor);
     if(GetConsoleScreenBufferInfo(studentHandleOutput, &conscrbufinfo))
     {

          FillConsoleOutputCharacter(studentHandleOutput, (TCHAR) 32, conscrbufinfo.dwSize.X * conscrbufinfo.dwSize.Y, coordinates, &counting);
          FillConsoleOutputAttribute(studentHandleOutput, conscrbufinfo.wAttributes, conscrbufinfo.dwSize.X * conscrbufinfo.dwSize.Y, coordinates, &counting );

          SetConsoleCursorPosition(studentHandleOutput, coordinates);
     }
     return;
}

void Setting_Color_And_Background(int ForgC, int BackC)
{
     WORD wordColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wordColor);
     return;
}

COORD coordinates = {0,0};
void x_and_y_coordinates(int x, int y){
    coordinates.X = x; coordinates.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void Drawing_Rectangle(){
    int a, b;
    x_and_y_coordinates(0,0);
    printf("%c",201);
    for(a = 1; a < 78; a++){
        x_and_y_coordinates(a, 0);
        printf("%c",205);
    }
    x_and_y_coordinates(78,0);
    printf("%c",187);
    for(a = 1; a < 25; a++){
        x_and_y_coordinates(78, a);
        if(a == 6){
            printf("%c",185);
        }else{
            printf("%c",186);
        }
    }
    x_and_y_coordinates(78, 25);
    printf("%c",188);
    for(a = 77; a > 0; a--){
        x_and_y_coordinates(a,25);
        if(a == 35){
            printf("%c",202);
        }else{
            printf("%c",205);
        }
    }
    x_and_y_coordinates(0,25);
    printf("%c",200);
    for(a = 24; a > 0; a--){
        x_and_y_coordinates(0,a);
        if(a == 6){
            printf("%c",204);
        }else{
            printf("%c",186);
        }
    }

    for(a = 1; a < 78; a++){
        x_and_y_coordinates(a,6);
        if(a == 35){
            printf("%c",203);
        }else{
            printf("%c",205);
        }
    }

    for(a = 7; a < 25; a++){
        x_and_y_coordinates(35,a);
        printf("%c",186);
    }

}

void Reset_Window(){
    int a,b;
    for(a = 37; a < 78; a++){
        for(b = 7; b < 25; b++){
            x_and_y_coordinates(a,b);printf(" ");
        }
    }
    return;
}

void window(){
    Drawing_Rectangle();
    x_and_y_coordinates(28,2);
    SetColor(35);
    printf("STUDENT RECORD SYSTEM");
    x_and_y_coordinates(20,3);
    printf("Jeddah Memorial State College");
    x_and_y_coordinates(31,4);
    printf("SCIENCE CAMPUS");
    x_and_y_coordinates(25,24);
    SetColor(17);

}


void print_heading(const char st[]){
    Setting_Color_And_Background(31,28);
    x_and_y_coordinates(38,8);printf("STUDENT RECORD SYSTEM : %s",st);
    Setting_Color_And_Background(17,15);
}

int configuration_record(char id[]){

}

void adding_student(){
    Reset_Window();
    print_heading("Add New Student");
    int print = 37;
    FILE *openfile;
    openfile = fopen("data.txt","ab+");
    SetColor(45);
    if(openfile == NULL){
        MessageBox(0,"Error in Opening file\nMake sure your file is not write protected","Warning",0);

    }else{
        fflush(stdin);
        x_and_y_coordinates(print,10);printf("ID: ");gets(stu.stud_id);
        x_and_y_coordinates(print,12);printf("Name: ");gets(stu.stud_name);
		x_and_y_coordinates(print,18);printf("Age: ");gets(stu.stud_age);
        x_and_y_coordinates(print,19);printf("Class: ");gets(stu.stud_class);
        x_and_y_coordinates(print,22);printf("Contact Number: ");gets(stu.stud_contact_number);
        fwrite(&stu, sizeof(stu), 1, openfile);
        x_and_y_coordinates(40,22); printf("New Student is Added Successfully");
    }
    SetColor(28);
    fclose(openfile);
    return;
}

void modify_student(){
    Reset_Window();
    print_heading("Modify Record");
    SetColor(45);
    char student_id[15];
    int isFound = 0, print = 37;
    x_and_y_coordinates(37,10);printf("Enter ID to Modify: ");fflush(stdin);
    gets(student_id);
    FILE *openfile;
    openfile = fopen("data.txt","rb+");
    while(fread(&stu, sizeof(stu),1,openfile) == 1){
        if(strcmp(student_id, stu.stud_id) == 0){
            fflush(stdin);
            x_and_y_coordinates(print,12);printf("ID: ");gets(stu.stud_id);
            x_and_y_coordinates(print,13);printf("Name: ");gets(stu.stud_name);
			x_and_y_coordinates(print,16);printf("Age: ");gets(stu.stud_age);
            x_and_y_coordinates(print,17);printf("Class: ");gets(stu.stud_class);
            x_and_y_coordinates(print,18);printf("Contact Number: ");gets(stu.stud_contact_number);
            fseek(openfile,-sizeof(stu), SEEK_CUR);
            fwrite(&stu,sizeof(stu), 1, openfile);
            x_and_y_coordinates(40,22); printf("New Student is Updated Successfully");
            isFound = 1;
            break;
        }
    }
    if(!isFound){
        x_and_y_coordinates(print, 12);printf("No Record Found");
    }
    fclose(openfile);
    SetColor(28);
    return;
}


void delete_student(){
    Reset_Window();
    print_heading("Delete Record");
    SetColor(45);
    char student_id[15];
    int isFound = 0, print = 37;
    x_and_y_coordinates(37,10);printf("Enter ID to Delete: ");fflush(stdin);
    gets(student_id);
    FILE *openfile, *temporary;
    openfile = fopen("data.txt","rb");
    temporary = fopen("temp.txt", "wb");
    while(fread(&stu, sizeof(stu),1,openfile) == 1){
        if(strcmp(student_id, stu.stud_id) == 0){
            fwrite(&stu,sizeof(stu),1,temporary);
        }
    }
    fclose(openfile);
    fclose(temporary);
    remove("data.txt");
    rename("temp.txt","data.txt");
    x_and_y_coordinates(37,12);printf("The record is sucessfully deleted");
    SetColor(28);
    return;
}

void view_students_record()
{
    Reset_Window();
    print_heading("View Records");
    SetColor(45);
    int isFound = 0;
    x_and_y_coordinates(37,10);
    FILE *openfile;
    openfile = fopen("data.txt","rb");
    while(fread(&stu,sizeof(stu),1,openfile) == 1){
       x_and_y_coordinates(37,12);printf("The record is Found");
        x_and_y_coordinates(37,14);printf("ID: %s",stu.stud_id);
        x_and_y_coordinates(37,15);printf("Name: %s",stu.stud_name);
		x_and_y_coordinates(37,18);printf("Age: %s",stu.stud_age);
        x_and_y_coordinates(37,19);printf("Class: %s",stu.stud_class);
        x_and_y_coordinates(37,20);printf("Contact Number: %s",stu.stud_contact_number);
    }
    SetColor(28);
    fclose(openfile);
    return;
}

void main_window(){
    int option;
    SetColor(28);
    int x = 2;
    while(1){
        x_and_y_coordinates(x,8);printf("Choice 1. Add Student");
        x_and_y_coordinates(x,10);printf("Choice 2. View Student");
        x_and_y_coordinates(x,12);printf("Choice 3. Modify Student Record");
        x_and_y_coordinates(x,14);printf("Choice 4. Delete Student Record");
        x_and_y_coordinates(x,16);printf("Choice 5. Exit");
        x_and_y_coordinates(x,18);printf("Enter your Choice: ");
        scanf("%d",&option);
        switch(option){
            case 1:
                adding_student();
                break;
            case 2:
                view_students_record();
                break;
            case 3:
                modify_student();
                break;
            case 4:
                delete_student();
                break;
            case 5:
                exit(0);
                break;
            default:
                break;
        }

    }

}

int main(){
    ClearConsoleToColors(17,15);
    SetConsoleTitle("STUDENT RECORD SYSTEM");
    window();
    main_window();
    return 0;
}
