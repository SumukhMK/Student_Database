#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include <libgen.h>
enum in
{
    sport = 1,
    culture = 2,
    tech = 3
};
typedef enum in in;

typedef struct TI
{
    struct TI *rlink;

    short int ch;
    struct currentsem
    {
        int marks[5];
        float attedance;
    } curSem;

    struct student
    {
        char usn[12];
        char name[10];
        short int age;
        char branch[5];
        short int sem;

    } stu;

    struct interest
    {
        in i;
        char tals[10];
    } interest;
} TI;

#define TISZ sizeof(TI)
TI *getnode();
void display(TI *);
void addRec(TI *);
void report(TI *);
TI *search(TI *, char *);
void sorting(TI *);
void stats(TI *);
void modify(TI *);
void delete(TI *, char *);
void admin(TI *);

int main()
{
    TI header;
    char usn[12];
    int ch;
    static int cnt = 0;
    for (;;)
    {
   
        relogin:printf("1.ADMIN LOGIN\n2.STUDENT LOGIN\n3.EXIT");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            char pass[10];
            printf("ENTER ADMIN PASSWORD\n");
            scanf("%s", pass);
            if (strcmp(pass, "admin@123") == 0)
            {
                for (;;)
                {
                    printf("\n*STUDENT DATABASE\n");
                    printf("1.ADD RECORD\n2.DISPLAY\n3.REPORT\n4.COLLEGE STATS\n5.MODIFY RECORD\n6.DELETE RECORD\n7.EXPORT RECORDS\n8.RE LOGIN\n9.EXIT\n");
                    scanf("%d", &ch);
                    switch (ch)
                    {
                    case 1:
                        cnt++;
                        addRec(&header);
                        break;
                    case 2:
                        display(&header);
                        break;
                    case 3:
                        printf("ENTER THE STUDENT USN\n");
                        scanf("%s", usn);
                        report(search(&header, usn));
                        break;
                    case 4:
                        stats(&header);
                        break;
                    case 5:
                    
                        printf("ENTER USN TO BE SEARCHED \n");
                        scanf("%s", usn);
                        modify(search(&header, usn));
                        break;
                    case 6:
                        printf("ENTER THE USN OF RECORD TO BE DELETED\n");
                        scanf("%s", usn);
                        delete (&header, usn);
                        cnt--;
                        break;
                    case 7:
                        admin(&header);
                        break;
                    case 8:
                        goto relogin;
                        break;
                    default:
                        return 0;
                    }
                }
            }
            else
            {
                printf("WRONG PASSWORD\n");
                break;
            }
        case 2:
        {
            char pass[10], USN[12];
            printf("ENTER THE USN\n");
            scanf("%s", USN);
            printf("ENTER PASSWORD\n");
            scanf("%s", pass);
            if (strcmp(pass,"student@123") == 0)
            {
                printf("1.REPORT\n2.COLLEGE STATS\n3.MODIFY RECORD\n4.RE LOGIN\n5.EXIT");
                scanf("%d", &ch);
                switch (ch)
                {
                case 1:
                    report(search(&header, USN));
                    break;
                case 2:
                    stats(&header);
                    break;
                case 3:
                    modify(search(&header, USN));
                    break;
                case 4:
                    goto relogin;
                    break;
                default:
                    return 0;
                }
            }
            else
            {
                printf("WRONG PASSWORD\n");
                break;
            }
        }
        default:
            return 0;
        }
    }
    return 0;
}
void addRec(TI *root)
{
    // Getting input
    TI *new = getnode();
    int ch;
    new->rlink = NULL;
    printf("ENTER PERSONAL INFO:\n");
    printf("ENTER NAME\n");
    scanf("%s", new->stu.name);
    printf("ENTER USN\n");
    scanf("%s", new->stu.usn);
    printf("ENTER THE BRANCH\n");
    scanf("%s", new->stu.branch);
    printf("ENTER AGE\n");
    scanf("%hd", &new->stu.age);
    printf("ENTER SEM\n");
    scanf("%hd", &new->stu.sem);
    printf("ENTER FIELD OF INTEREST\n\t1 - SPORTS\n\t2 - CULTURAL\n\t3 - TECHNOLOGY\n");
    scanf("%d", &new->interest.i);
    printf("ENTER TALENT IN ABOVE SELECTED FIELD\n");
    scanf("%s", new->interest.tals);
    printf("WOULD YOU LIKE TO FILL THE CURRENT SEM INFO?[1/0]\n");
    scanf("%hd", &new->ch);
    if (new->ch)
    {
        printf("ENTER CURRENT SEM INFO:\n");
        printf("ENTER MARKS OF FIVE SUBJECTS\n");
        for (int i = 0; i < 5; i++)
            scanf("%d", &new->curSem.marks[i]);
        printf("ENTER ATTENDENCE PERCENTAGE\n");
        scanf("%f", &new->curSem.attedance);
    }
    // inserting front
    if (!root->rlink)
        root->rlink = new;
    else
    {
        new->rlink = root->rlink;
        root->rlink = new;
    }
}

TI *getnode()
{
    TI *t = NULL;
    t = (TI *)malloc(sizeof(TI));
    return (t);
}

void display(TI *root)
{
    char tal[][30] = {{""}, {"SPORTS"}, {"CULTURAL"}, {"TECH"}};
    if (root->rlink == NULL)
    {
        printf("EMPTY");
        return;
    }
    TI *t;
    for (t = root->rlink; t != NULL; t = t->rlink)
    {
        printf("%s\n", t->stu.name);
        printf("%s\n", t->stu.usn);
        printf("%s\n", t->stu.branch);
        printf("%d\n", t->stu.age);
        printf("%s\n", tal[t->interest.i]);
        printf("%s\n", t->interest.tals);
    }
}

void report(TI *rep)
{
    if (rep == NULL)
    {
        printf("STUDENT NO FOUND\n");
        return;
    }
    printf("STUDENT REPORT\n");
    printf("\nNAME: %s\n", rep->stu.name);
    printf("USN: %s\n", rep->stu.usn);
    printf("BRANCH: %s\n", rep->stu.usn);
    if (rep->ch)
    {
        for (int i = 0; i < 5; i++)
        {
            char c = (rep->curSem.marks[i] > 20) ? 'P' : 'F';
            printf("MARKS: %d : %c\n", rep->curSem.marks[i], c);
        }
        printf("ATTENDANCE : %.2f\n", rep->curSem.attedance);
        if (rep->curSem.attedance < 75)
            printf("ATTEDENCE SHORTAGE\n");
    }
    else
        return;
}

TI *search(TI *head, char usn[12])
{
    TI *temp = head->rlink;
    for (; temp != NULL; temp = temp->rlink)
    {
        if (!(strcmp(usn, temp->stu.usn)))
            return temp;
    }
    return NULL;
}

void stats(TI *head)
{
    TI *temp = head->rlink;
    printf("\nSPORTS:\n");
    for (int i = 1; temp; temp = temp->rlink, i++)
    {
        if (temp->interest.i == 1)
        {
            printf("STUDENT : %d.\n", i);
            printf("NAME: %s\n", temp->stu.name);
            printf("USN: %s\n", temp->stu.usn);
            printf("BRANCH: %s\n\n", temp->stu.branch);
        }
    }
    temp = head->rlink;
    printf("\nCULTURAL:\n");
    for (int i = 1; temp; temp = temp->rlink, i++)
    {
        if (temp->interest.i == 2)
        {
            printf("STUDENT : %d.\n", i);
            printf("\nNAME: %s\n", temp->stu.name);
            printf("USN: %s\n", temp->stu.usn);
            printf("BRANCH: %s\n\n", temp->stu.branch);
        }
    }
    temp = head->rlink;
    printf("\nTECHNICAL:\n");
    for (int i = 1; temp; temp = temp->rlink, i++)
    {
        if (temp->interest.i == 3)
        {
            printf("STUDENT: %d.\n", i);
            printf("NAME: %s\n", temp->stu.name);
            printf("USN: %s\n", temp->stu.usn);
            printf("BRANCH: %s\n", temp->stu.branch);
        }
    }
}

void modify(TI *mod)
{
    int ch;
    printf("ENTER 1 RE ENTER PERSONAL DETAILS\n\tENTER  2 TO RE ENTER CURRENT SEM DETAILS\n");
    scanf("%d", &ch);
    if (ch == 1)
    {
        printf("ENTER PERSONAL INFO:\n");
        printf("ENTER NAME\n");
        scanf("%s", mod->stu.name);
        printf("ENTER USN\n");
        scanf("%s", mod->stu.usn);
        printf("ENTER BRANCH\n");
        scanf("%s", mod->stu.branch);
        printf("ENTER AGE\n");
        scanf("%hd", &mod->stu.age);
        printf("ENTER SEM");
        scanf("%hd", &mod->stu.sem);
        printf("ENTER FIELD OF INTEREST\n\t1 - SPORTS\n\t2 - CULTURAL\n\t3 - TECHNOLOGY\n");
        scanf("%d", &mod->interest.i);
        printf("ENTER TALENTS IN ABOVE SELECTED FIELD\n");
        scanf("%s", mod->interest.tals);
        return;
    }
    if (ch == 2)
    {
        printf("ENTER CURRENT SEM INFO:\n");
        printf("ENTER MARKS OF 5 SUBJECTS\n");
        for (int i = 0; i < 5; i++)
            scanf("%d", &mod->curSem.marks[i]);
        printf("ENTER ATTEDENCE PERCENTAGE\n");
        scanf("%f", &mod->curSem.attedance);
        return;
    }
}

void delete(TI *h, char usn[12])
{
    TI *prev = NULL;
    for (TI *temp = h->rlink; temp; prev = temp, temp = temp->rlink)
    {
        if (strcmp(usn, temp->stu.usn) == 0)
        {
            prev->rlink = temp->rlink;
            printf("DELETING RECORD:\n");
            printf("NAME: %s\nUSN : %s", temp->stu.name, temp->stu.usn);
            free(temp);
            return;
        }
    }
    printf("RECORD NOT FOUND");
}

void admin(TI *h)
{
    FILE *fp = fopen("StudentDatabase.txt", "w");
    rewind(fp);
    for (TI *temp = h->rlink; temp; temp = temp->rlink)
        fwrite(temp->curSem.marks, TISZ, 1, fp);
    printf("FILE PATH: StudentDatabase.txt\n");
    fclose(fp);
}
