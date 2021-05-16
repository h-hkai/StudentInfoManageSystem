#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    char sno[20];
    char name[20];
    char gender[10];
    char age[10];
    char career[20];
    int reward;
};

void welcome(int *);
void writeInfo();
void readInfo();
void findInfo();
int getLines();
void printAll();
void printOne(char *);

int main() {
    int choice;
    int *cp = &choice;
    while (true) {
        system("cls");
        welcome(cp);
        if (choice == 0) break;
        switch (choice) {
            case 1:
                readInfo();
                break;
            case 2:
                writeInfo();
                break;
            case 3:
                findInfo();
                break;

            default:
                break;
        }
    }
    printf("GoodBey!!\n");
    return 0;
}

void welcome(int *choice) {
    printf("$ 欢迎来到学籍管理系统\n\n");
    printf("USAGE\n");
    printf(" $ 查看学生信息输入 1\n");
    printf(" $ 录入学生信息输入 2\n");
    printf(" $ 查找学生信息输入 3\n");
    printf(" $ 退出输入 0\n\n");
    printf("$ 请输入你的选择：");
    scanf("%d", choice);
    system("cls");
}

void readInfo() {
    printAll();
    getchar();
    printf("按任意键继续！！！\n");
    getchar();
}

void writeInfo() {
    FILE *fp1, *fp2;
    if ((fp1 = fopen("studentInfo.dat", "a+")) == NULL) {
        printf("studentInfo open error!\n");
        exit(0);
    }
    if ((fp2 = fopen("studentAward.dat", "a+")) == NULL) {
        printf("studentAward open error!\n");
        exit(0);
    }
    Student stu;
    char date[1024];
    char award[1024];
    printf("Please input students' information:\n");
    printf("student's sno: ");
    scanf("%s", stu.sno);
    printf("student's name: ");
    scanf("%s", stu.name);
    printf("student's gender: ");
    scanf("%s", stu.gender);
    printf("student's age: ");
    scanf("%s", stu.age);
    printf("student's career: ");
    scanf("%s", stu.career);
    stu.reward = getLines();
    fprintf(fp1, "%-20s %-20s %-10s %-10s %-20s %d\n", stu.sno, stu.name,
            stu.gender, stu.age, stu.career, stu.reward);
    printf("student's award: ");
    getchar();
    gets(award);
    strcat(award, "\n");
    fputs(award, fp2);
    if (fclose(fp1)) {
        printf("studentInfo close error!\n");
        exit(0);
    }
    if (fclose(fp2)) {
        printf("studentAward close error!\n");
        exit(0);
    }
    printf("录入成功！！\n");
    printf("按任意键继续！！！\n");
    getchar();
}

void findInfo() {
    char sno[20];
    printf("请输入要查询学生的学号：");
    scanf("%s", sno);
    getchar();
    printOne(sno);
    printf("按任意键结束！！！\n");
    getchar();
}

int getLines() {
    FILE *fp;
    if ((fp = fopen("studentAward.dat", "r")) == NULL) {
        printf("studentAward open error!\n");
        exit(0);
    }
    int count = 0;
    while (!feof(fp)) {
        char info[200];
        fgets(info, 1024, fp);
        count++;
    }
    return count;
}

void printAll() {
    printf("%-20s %-20s %-10s %-10s %-20s %s\n", "学号", "姓名", "性别", "年龄",
           "专业", "奖励");
    FILE *fp1, *fp2;
    if ((fp1 = fopen("studentInfo.dat", "r")) == NULL) {
        printf("studentInfo open error!\n");
        exit(0);
    }
    if ((fp2 = fopen("studentAward.dat", "r")) == NULL) {
        printf("studentAward open error!\n");
        exit(0);
    }
    while (!feof(fp1)) {
        char info[1024];
        char award[1024];
        fgets(info, 1000, fp1);
        // 寻找奖励所在的行数
        int index = 0;
        int len = strlen(info);
        for (int i = 85; i < strlen(info) && info[i] != '\n'; ++i) {
            index = index * 10 + (info[i] - '0');
        }

        // 通过奖励所在的行数将奖励信息读出
        int count = 1;
        bool found = false;
        while (!feof(fp2)) {
            fgets(award, 1000, fp2);
            if (count == index) {
                found = true;
                fseek(fp2, 0, 0);
                break;
            }
            count++;
        }

        // 对获得的奖励信息和基本信息进行拼接
        info[85] = '\0';
        strcat(info, award);
        if (found) puts(info);
    }
    if (fclose(fp1)) {
        printf("studentInfo close error!\n");
        exit(0);
    }
    if (fclose(fp2)) {
        printf("studentAward close error!\n");
        exit(0);
    }
}

void printOne(char *sno) {
    printf("%-20s %-20s %-10s %-10s %-20s %s\n", "学号", "姓名", "性别", "年龄",
           "专业", "奖励");
    FILE *fp1, *fp2;
    if ((fp1 = fopen("studentInfo.dat", "r")) == NULL) {
        printf("studentInfo open error!\n");
        exit(0);
    }
    if ((fp2 = fopen("studentAward.dat", "r")) == NULL) {
        printf("studentAward open error!\n");
        exit(0);
    }
    bool found = false;
    while (!feof(fp1)) {
        char info[1024];
        char award[1024];
        fgets(info, 1000, fp1);
        char *p = strstr(info, sno);
        if (p != NULL && p[0] == info[0]) {
            // 寻找奖励所在的行数
            int index = 0;
            int len = strlen(info);
            for (int i = 85; i < strlen(info) && info[i] != '\n'; ++i) {
                index = index * 10 + (info[i] - '0');
            }
            // 通过奖励所在的行数将奖励信息读出
            int count = 1;

            while (!feof(fp2)) {
                fgets(award, 1000, fp2);
                if (count == index) {
                    found = true;
                    fseek(fp2, 0, 0);
                    break;
                }
                count++;
            }
            // 对获得的奖励信息和基本信息进行拼接
            info[85] = '\0';
            strcat(info, award);
            if (found) puts(info);
            found = true;
            break;
        }
    }
    if (!found) {
        printf("Not found!\n");
    }
    if (fclose(fp1)) {
        printf("studentInfo close error!\n");
        exit(0);
    }
    if (fclose(fp2)) {
        printf("studentAward close error!\n");
        exit(0);
    }
}