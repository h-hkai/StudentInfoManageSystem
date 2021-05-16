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
    printf("$ ��ӭ����ѧ������ϵͳ\n\n");
    printf("USAGE\n");
    printf(" $ �鿴ѧ����Ϣ���� 1\n");
    printf(" $ ¼��ѧ����Ϣ���� 2\n");
    printf(" $ ����ѧ����Ϣ���� 3\n");
    printf(" $ �˳����� 0\n\n");
    printf("$ ���������ѡ��");
    scanf("%d", choice);
    system("cls");
}

void readInfo() {
    printAll();
    getchar();
    printf("�����������������\n");
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
    printf("¼��ɹ�����\n");
    printf("�����������������\n");
    getchar();
}

void findInfo() {
    char sno[20];
    printf("������Ҫ��ѯѧ����ѧ�ţ�");
    scanf("%s", sno);
    getchar();
    printOne(sno);
    printf("�����������������\n");
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
    printf("%-20s %-20s %-10s %-10s %-20s %s\n", "ѧ��", "����", "�Ա�", "����",
           "רҵ", "����");
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
        // Ѱ�ҽ������ڵ�����
        int index = 0;
        int len = strlen(info);
        for (int i = 85; i < strlen(info) && info[i] != '\n'; ++i) {
            index = index * 10 + (info[i] - '0');
        }

        // ͨ���������ڵ�������������Ϣ����
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

        // �Ի�õĽ�����Ϣ�ͻ�����Ϣ����ƴ��
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
    printf("%-20s %-20s %-10s %-10s %-20s %s\n", "ѧ��", "����", "�Ա�", "����",
           "רҵ", "����");
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
            // Ѱ�ҽ������ڵ�����
            int index = 0;
            int len = strlen(info);
            for (int i = 85; i < strlen(info) && info[i] != '\n'; ++i) {
                index = index * 10 + (info[i] - '0');
            }
            // ͨ���������ڵ�������������Ϣ����
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
            // �Ի�õĽ�����Ϣ�ͻ�����Ϣ����ƴ��
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