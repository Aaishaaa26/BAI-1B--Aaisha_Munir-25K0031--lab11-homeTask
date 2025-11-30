#include <stdio.h>
#include <string.h>

struct marks{
    int sub1;
    int sub2;
    int sub3;
};

struct student{
    char name[20];
    int rollNum;
    struct marks subjects;    
};

void add(struct student *students, int n){
    for(int i = 0; i < n ; i++){
        printf("Enter student %d Name: ", i+1);
        scanf("%s", students[i].name);
        printf("Enter student %d Roll Number: ", i+1);
        scanf("%d", &students[i].rollNum);
        do{
            printf("Enter Marks In Subject 1 (0-100): ");
            scanf("%d", &students[i].subjects.sub1);
        }while(students[i].subjects.sub1 < 0 || students[i].subjects.sub1 > 100);
        do{
            printf("Enter Marks In Subject 2 (0-100): ");
            scanf("%d", &students[i].subjects.sub2);
        }while(students[i].subjects.sub2 < 0 || students[i].subjects.sub2 > 100);
        do{
            printf("Enter Marks In Subject 3 (0-100): ");
            scanf("%d", &students[i].subjects.sub3);    
        }while(students[i].subjects.sub3 < 0 || students[i].subjects.sub3 > 100);    
    }
}

void calcPercentage(struct student students[], int n, float percentage[][2]){
    for(int i = 0; i < n ; i++){
        percentage[i][0] = students[i].rollNum;
        percentage[i][1] = (students[i].subjects.sub1 + students[i].subjects.sub2 + students[i].subjects.sub3) / 3.0;
    }    
}

void calcGrade(struct student students[], float percentage[][2], char grade[][2][3], int n){
    for(int i = 0; i < n; i++){
        sprintf(grade[i][0], "%d", students[i].rollNum);
        if (percentage[i][1] >= 90) strcpy(grade[i][1], "A+");
        else if (percentage[i][1] >= 80) strcpy(grade[i][1], "A");
        else if (percentage[i][1] >= 70) strcpy(grade[i][1], "B+");
        else if (percentage[i][1] >= 60) strcpy(grade[i][1], "B");
        else if (percentage[i][1] >= 50) strcpy(grade[i][1], "C");
        else strcpy(grade[i][1], "F");
    }
}

void searchRoll(struct student students[], float percentage[][2], char grade[][2][3], int n){
    int r, found = 0;
    printf("Enter Roll Number to Search: ");
    scanf("%d", &r);
    for(int i = 0; i < n; i++){
        if(students[i].rollNum == r){
            printf("\nName: %s\nRoll: %d\nPercentage: %.2f\nGrade: %s\n",
            students[i].name, students[i].rollNum, percentage[i][1], grade[i][1]);
            found = 1;
        }
    }
    if(!found) printf("Roll number not found\n");
}

void searchName(struct student students[], float percentage[][2], char grade[][2][3], int n){
    char name[20];
    int found = 0;
    printf("Enter Name to Search: ");
    scanf("%s", name);
    for(int i = 0; i < n; i++){
        if(strcmp(students[i].name, name) == 0){
            printf("\nName: %s\nRoll: %d\nPercentage: %.2f\nGrade: %s\n",
            students[i].name, students[i].rollNum, percentage[i][1], grade[i][1]);
            found = 1;
        }
    }
    if(!found) printf("Name not found\n");
}

void findByGrade(char grade[][2][3], struct student students[], float percentage[][2], int n){
    char g[3];
    printf("Enter Grade to Search (A+, A, B+, B, C, F): ");
    scanf("%s", g);
    for(int i = 0; i < n; i++){
        if(strcmp(grade[i][1], g) == 0){
            printf("%s  Roll: %d\tPercentage: %.2f\n", grade[i][1], students[i].rollNum, percentage[i][1]);
        }
    }
}

void classAverageReport(struct student students[], float percentage[][2], char grade[][2][3], int n){
    float sum = 0;
    for(int i = 0; i < n; i++)
        sum += percentage[i][1];
    float avg = sum / n;

    printf("Class Average: %.2f\n", avg);

    printf("\n____Students Above Average____\n");
    for(int i = 0; i < n; i++){
        if(percentage[i][1] > avg){
            printf("%s  Roll:%d  Percentage:%.2f  Grade:%s\n",
                students[i].name, students[i].rollNum, percentage[i][1], grade[i][1]);
        }
    }

    printf("\n_____Students Below Average_____\n");
    for(int i = 0; i < n; i++){
        if(percentage[i][1] < avg){
            printf("%s  Roll:%d  Percentage:%.2f  Grade:%s\n",
                students[i].name, students[i].rollNum, percentage[i][1], grade[i][1]);
        }
    }
}

void rankStudents(struct student students[], float percentage[][2], char grade[][2][3], int n){
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < n - i - 1; j++){
            if(percentage[j][1] < percentage[j+1][1]){
                float tempP[2];
                tempP[0] = percentage[j][0];
                tempP[1] = percentage[j][1];
                percentage[j][0] = percentage[j+1][0];
                percentage[j][1] = percentage[j+1][1];
                percentage[j+1][0] = tempP[0];
                percentage[j+1][1] = tempP[1];

                char tempG[3];
                strcpy(tempG, grade[j][1]);
                strcpy(grade[j][1], grade[j+1][1]);
                strcpy(grade[j+1][1], tempG);

                struct student tempS = students[j];
                students[j] = students[j+1];
                students[j+1] = tempS;
            }
        }
    }

    for(int i = 0; i < n; i++){
        printf("Rank %d --> %s  Roll:%d  Percentage:%.2f  Grade:%s\n",
        i+1, students[i].name, students[i].rollNum, percentage[i][1], grade[i][1]);
    }
}

int main(){
    int n, choice;

    printf("Enter Number Of Students: ");
    scanf("%d", &n);    
    
    struct student students[n]; 
    float percentage[n][2];
    char grade[n][2][3];

    add(students, n);
    calcPercentage(students, n, percentage);
    calcGrade(students, percentage, grade, n);

    while(1){
        printf("\nMenu:\n1.Search by Roll\n2.Search by Name\n3.Find by Grade\n4.Class Average Report\n5.Ranking\n6.Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                searchRoll(students, percentage, grade, n);
                break;
            case 2:
                searchName(students, percentage, grade, n);
                break;
            case 3:
                findByGrade(grade, students, percentage, n);
                break;
            case 4:
                classAverageReport(students, percentage, grade, n);
                break;
            case 5:
                rankStudents(students, percentage, grade, n);
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice, Please Try again(prefered not to :D)\n");
        }
    }

    return 0;
}