#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Date {
    int day;
    int month;
    int year;
};

struct Employee {
    int empID;
    char fullName[50];
    char dept[20];
    char role[20];
    float salary;
    struct Date joinDate;
    char phone[15];
    char email[50];
};

int calculateExperience(struct Date join) {
    int currentYear = 2025;
    int currentMonth = 11;
    int currentDay = 30;

    int years = currentYear - join.year;
    if (currentMonth < join.month || (currentMonth == join.month && currentDay < join.day)) {
        years--;
    }
    return years;
}

void addEmployee(struct Employee *staff, int index) {
    printf("Enter Employee ID: ");
    scanf("%d", &staff[index].empID);
    printf("Enter Full Name: ");
    scanf(" %[^\n]", staff[index].fullName);

    int validDept = 0;
    while(!validDept) {
        printf("Enter Department (IT, HR, Finance, Marketing, Operations): ");
        scanf("%s", staff[index].dept);
        if (strcmp(staff[index].dept,"IT")==0 || strcmp(staff[index].dept,"HR")==0 || strcmp(staff[index].dept,"Finance")==0 || strcmp(staff[index].dept,"Marketing")==0 || strcmp(staff[index].dept,"Operations")==0) validDept = 1;
        else printf("Invalid Department!\n");
    }

    int validRole = 0;
    while(!validRole) {
        printf("Enter Role (Intern, Junior, Senior, Manager, Director): ");
        scanf("%s", staff[index].role);
        if (strcmp(staff[index].role,"Intern")== 0 || strcmp(staff[index].role,"Junior")== 0 || strcmp(staff[index].role,"Senior")== 0 || strcmp(staff[index].role,"Manager")== 0 || strcmp(staff[index].role,"Director")== 0) validRole = 1;
        else printf("Invalid Role!\n");
    }

    printf("Enter Salary: ");
    scanf("%f", &staff[index].salary);

    printf("Enter Joining Date (DD MM YYYY): ");
    scanf("%d %d %d", &staff[index].joinDate.day, &staff[index].joinDate.month, &staff[index].joinDate.year);

    printf("Enter Phone Number: ");
    scanf("%s", staff[index].phone); 

    printf("Enter Email: ");
    scanf("%s", staff[index].email);
    // assuming that user enters correct mail and phone number
}

void displayEmployee(struct Employee emp) {
    int exp = calculateExperience(emp.joinDate);
    printf("\nID: %d\nName: %s\nDepartment: %s\nRole: %s\nSalary: %.2f\nJoining Date: %02d-%02d-%04d\nPhone: %s\nEmail: %s\nExperience: %d years\n", emp.empID, emp.fullName, emp.dept, emp.role, emp.salary, emp.joinDate.day, emp.joinDate.month, emp.joinDate.year, emp.phone, emp.email, exp);
}

void departmentSalaryStats(struct Employee staff[], int total) {
    float totalSalary = 0; 
    int count = 0;
    char dept[20];
    printf("Enter Department to view salary stats: ");
    scanf("%s", dept);
    for(int i=0;i<total;i++){
        if(strcmp(staff[i].dept, dept)==0){
            totalSalary += staff[i].salary;
            count++;
        }
    }
    if(count>0) printf("Total Salary: %.2f | Average Salary: %.2f\n", totalSalary, totalSalary/count);
    else printf("No employees in this department.\n");
}

void annualAppraisal(struct Employee staff[], int total) {
    float performance;
    for(int i=0;i<total;i++){
        printf("Enter performance score for %s (0-100): ", staff[i].fullName);
        scanf("%f", &performance);
        if(performance>=90) staff[i].salary *= 1.15;
        else if(performance>=75) staff[i].salary *= 1.10;
        else if(performance>=50) staff[i].salary *= 1.05;
    }
    printf("Appraisal completed.\n");
}

void searchEmployees(struct Employee staff[], int total) {
    int choice;
    printf("Search by: 1-Department 2-Role 3-Experience\nEnter choice: ");
    scanf("%d", &choice);
    if(choice==1){
        char dept[20];
        printf("Enter Department: ");
        scanf("%s", dept);
        for(int i=0;i<total;i++){
            if(strcmp(staff[i].dept, dept)==0) displayEmployee(staff[i]);
        }
    } else if(choice==2){
        char role[20];
        printf("Enter Role: ");
        scanf("%s", role);
        for(int i=0;i<total;i++){
            if(strcmp(staff[i].role, role)==0) displayEmployee(staff[i]);
        }
    } else if(choice==3){
        int exp;
        printf("Enter minimum years of experience: ");
        scanf("%d", &exp);
        for(int i=0;i<total;i++){
            if(calculateExperience(staff[i].joinDate) >= exp) displayEmployee(staff[i]);
        }
    }
}

void eligibleForPromotion(struct Employee staff[], int total) {
    
	for(int i=0;i<total;i++){
        int exp = calculateExperience(staff[i].joinDate);
        if(exp>3) displayEmployee(staff[i]);
    }
}

int main(){
    struct Employee staff[100];
    int totalEmployees=0, choice;

    while(1){
        printf("\n1: Add Employee\n2: Display All Employees\n3: Department Salary Stats\n4: Annual Appraisal\n5: Search Employees\n6: Employees Eligible for Promotion\n7: Exit\nEnter choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
                addEmployee(staff, totalEmployees);
                totalEmployees++;
                break;
            case 2:
                for(int i=0;i<totalEmployees;i++) displayEmployee(staff[i]);
                break;
            case 3:
                departmentSalaryStats(staff, totalEmployees);
                break;
            case 4:
                annualAppraisal(staff, totalEmployees);
                break;
            case 5:
                searchEmployees(staff, totalEmployees);
                break;
            case 6:
                eligibleForPromotion(staff, totalEmployees);
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice :)\n");
        }
    }
    return 0;
}
