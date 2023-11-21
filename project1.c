#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
// #include <conio.h>

int count = 0;
int roll;
void admin();
void student();
int roll_number();
int sat();
int ecat();
int military();
int registration_checker();
int appendSat();
int appendEcat();
int appendMil();
int appendiq();
typedef struct student
{
    char cnic[15];
    char name[100];
    int age;
    char gender;
    int rollno;

} std;

int main()
{
    int flag = 0;
    std *ptr;

    ptr = (std *)calloc(count, sizeof(std));
    if (ptr == NULL)
    {
        printf("Insufficient memory\n");
    }
    else
    {
        do
        {

            int interface;

            printf("\tWELCOME\n\n1:Administrator Interface\n2:Student Interface\n0:Exit\n");
            scanf("%d", &interface);
            switch (interface)
            {
            case 1:
                admin(ptr);
                break;
            case 2:
                student(ptr);
                break;
            case 0:
                flag = 1;
                break;
            }
        } while (flag == 0);
    }

    free(ptr);
    return 0;
}
void admin(std *a)
{
    int option, op,flag=1;
    printf("1: Student record\n2: Question append\n");
    scanf("%d", &option);
    switch (option)
    {
    case 1:
        printf("Enter roll number:\n");
        scanf("%d",&op);
        for (int i = 0; i <=count; i++)
        {
            if (a[i].rollno == op){
                printf("Registration done\n");
                flag=0;
                break;
            }
        }
        if (flag==1)
        {
            printf("Record not found\n");
        }else{
           FILE *sat=fopen("Sresult.txt","r");
           FILE *ecat=fopen("Eresult.txt","r");
           FILE *military=fopen("Mresult.txt","r");
           int R;
           char record[100];
        do
        {
            fscanf(sat, "%d",&R);
            if (R==op)
            {
                printf("\tSAT\nRoll No:\tResult\n");
                printf("%d",R);
                fscanf(sat,"%[^\n]",record);
                printf("%s\n",record);
            break;
            }
            
        } while (feof(sat)==0);
        R=0;
        do
        {
            fscanf(ecat, "%d",&R);
            if (R==op)
            {
                printf("\tECAT\nRoll No:\tResult\n");
                printf("%d",R);
                fscanf(ecat,"%[^\n]",record);
                printf("%s\n",record);
            break;
            }
            
        } while (feof(ecat)==0);
        R=0;

        do
        {
            fscanf(military, "%d",&R);
            if (R==op)
            {
                printf("\tMILITARY\nRoll No:\tIQ\tTheory\n");
                printf("%d",R);
                fscanf(military,"%[^\n]",record);
                printf("%s\n",record);
            break;
            }
            
        } while (fgetc(military)!=EOF);       
        fclose(sat);
        fclose(military);
        fclose(ecat);
        }
        
        break;
    case 2:
        printf("Which portion:\n1:SAT\n2:ECAT\n3:Military\n");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            appendSat();
            break;
        case 2:
            appendEcat();

            break;
        case 3:
            printf("\n1:IQ\n2:Theory\n");
            scanf("%d", &option);
            switch (option)
            {
            case 1:
            appendMil();
                break;
            case 2:
            appendiq();
                break;

            default:
                break;
            }

            break;
        default:
            break;
        }
        break;
    default:
        printf("Invalid Input");
        break;
    }
}

void student(std *a)
{
    int FLAG = 0, option, error = 0, exit = 3, choice;
    do
    {
        printf("1:Regisration\n2:Take test\n3:Result\n0: Exit\n");
        scanf("%d", &option);

        switch (option)
        {
        case 1:
            count++;
            a = realloc(a, count);
            if (a + count == NULL)
            {
                printf("Insufficient memory\n");
            }
            else
            {

                printf("Enter your name: \n");
                scanf("%s", a[count].name);
                do
                {
                    error = 0;
                    printf("Enter your cnic: \n");
                    scanf("%s", &a[count].cnic);

                    for (int i = 0; i < count; i++)
                    {
                        if (strcmp(a[i].cnic, a[count].cnic) == 0)
                        {
                            if (exit > 0)
                            {
                                printf("This cnic is already used\n");
                                error = 1;
                                exit--;
                                printf("%d attempt left:\n", exit);
                            }
                            else
                            {
                                printf("Maximum attempt reached\n");
                            }
                        }
                    }

                } while (error == 1 && exit != 0);
                if (exit == 0)
                {
                    break;
                }

                printf("Enter your age: \n");
                scanf("%d", &a[count].age);
                printf("Enter your gender: (M,F) \n");
                scanf(" %c", &a[count].gender);
                roll_number(a, 0);
                printf("Your roll number is %d\n", a[count].rollno);
            }
            break;
        case 2:

            printf("1: SAT\n2: ECAT\n3: Military\n");
            scanf("%d", &choice);
            float result,theory;
            int id, checker;
            switch (choice)
            {
            case 1:

                printf("Enter your roll number:\n");
                scanf("%d", &id);
                checker = registration_checker(id, a);
                if (checker == 0)
                {
                    printf("You have not registered yet\nPlz register first\n\n");
                }
                else
                {
                    sat(&result);
                    FILE *s_res=fopen("Sresult.txt","a");
                    fprintf(s_res,"%d\t\t",id);
                    fprintf(s_res,"%.2f\n",result);
                    fclose(s_res);
                }

                break;
            case 2:
                printf("Enter your roll number:\n");
                scanf("%d", &id);
                checker = registration_checker(id, a);
                if (checker == 0)
                {
                    printf("You have not registered yet\nPlz register first\n\n");
                }
                else
                {
                    ecat(&result);
                    FILE *e_res=fopen("Eresult.txt","a");
                    fprintf(e_res,"%d\t\t",id);
                    fprintf(e_res,"%.2f\n",result);
                    fclose(e_res);
                }
                break;
            case 3:
                printf("Enter your roll number:\n");
                scanf("%d", &id);
                checker = registration_checker(id, a);
                if (checker == 0)
                {
                    printf("You have not registered yet\nPlz register first\n\n");
                }
                else
                {
                   theory=0.0;  
                    military(&result,&theory);
                    FILE *m_res=fopen("Mresult.txt","a");
                    fprintf(m_res,"%d\t\t",id);
                    fprintf(m_res,"%.2f\t",result);
                    fprintf(m_res,"%.2f\n",theory);
                    fclose(m_res);
                }

                break;
            default:
                printf("Invalid Input\n");
                break;
            }
            break;
            break;

        case 3:
            printf("Enter your roll no\n");
            scanf("%d", &roll);
            for (int i = 0; i < count; i++)
            {
                if (a[i].rollno == roll)
                {
                    roll = i;
                    break;
                }
            }

            printf("1: SAT\n2: ECAT\n3: Military\n");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
                // printf("Your score is %f", a[roll].sat);
                break;
            case 2:
                // printf("Your score is %f", a[roll].ecat);

                break;
            case 3:
                // printf("Your score is %f", a[roll].military);

                break;
            default:
                break;
            }
            break;
        case 0:
            FLAG = 1;
            break;
        default:
            printf("Invalid Input\n\n");
            break;
        }
    } while (FLAG == 0);
}
int roll_number(std *a, int i)
{
    int error = 0;
    if (a[count].cnic[i] == '\0')
    {
        roll = 0;
        return 0;
    }
    roll_number(a, i + 1);
    if (roll < 5)
    {

        a[count].rollno += ((int)(a[count].cnic[roll] - '0') * pow(10, roll));
        roll++;
    }
    do
    {
        for (int i = 0; i < count; i++)
        {
            error = 0;
            if (a[i].rollno == a[count].rollno)
            {
                a[count].rollno++;
                error = 1;
            }
        }
    } while (error == 1);
}
int sat(float *result)
{
    FILE *sat_file;
    FILE *sat_key;
    sat_file = fopen("SAT.txt", "r");
    sat_key = fopen("sat_key.txt", "r");
    if (sat_file == NULL)
    {
        printf("Error\n");
        return 0;
    }

    printf("\t\tSAT TEST\n");
    char question[1000];
    char user_answer, correct_answer;
    int num_of_question = 0;
    int right_answer = 0;
    do
    {
        for (int i = 0; i < 5; i++)
        {
            fscanf(sat_file, "%[^\n]\n", question);
            printf("%s\n", question);
        }
        fscanf(sat_key, "%c", &correct_answer);
        scanf(" %c", &user_answer);
        if (user_answer == correct_answer)
        {
            right_answer++;
        }
        num_of_question++;
    } while (fgetc(sat_file) != EOF);
    *result = right_answer * 100.00 / num_of_question;
    printf("You score %f\n\n", *result);
    fclose(sat_file);
    fclose(sat_key);
    return 1;
}
int ecat(float *result)
{
    FILE *e_qs;
    FILE *e_key;
    e_qs = fopen("ECAT.txt", "r");
    e_key = fopen("ecat_key.txt", "r");
    if (e_qs == NULL)
    {
        printf("Error\n");
        return 0;
    }

    printf("\t\tECAT TEST\n");
    char qs[1000];
    char uAns, cAns;
    int nQs = 0;
    int rAns = 0;
    do
    {
        for (int i = 0; i < 5; i++)
        {
            fscanf(e_qs, "%[^\n]\n", qs);
            printf("%s\n", qs);
        }
        fscanf(e_key, "%c", &cAns);
        scanf(" %c", &uAns);
        if (uAns == cAns)
        {
            rAns++;
        }
        nQs++;
    } while (fgetc(e_qs) != EOF);
    *result = rAns * 100.00 / nQs;
    printf("You score %.2f\n\n", *result);

    fclose(e_qs);
    fclose(e_key);
    return 1;
}
int military(float *iq, float *theo)
{
    FILE *military1_file;
    FILE *military1_key;
    military1_file = fopen("military_iq.txt", "r");
    military1_key = fopen("military_iq_key.txt", "r");
    if (military1_file == NULL)
    {
        printf("Error\n");
        return 0;
    }
    printf("\t\tMILITARY TEST\n");
    char ques1[1000];
    char user_answer1, correct_answer1;
    int num_of_question1 = 0;
    int right_answer1 = 0;
    do
    {
        for (int i = 0; i < 5; i++)
        {
            fscanf(military1_file, "%[^\n]\n", ques1);
            printf("%s\n", ques1);
        }
        fscanf(military1_key, "%c", &correct_answer1);
        scanf(" %c", &user_answer1);
        if (user_answer1 == correct_answer1)
        {
            right_answer1++;
        }
        num_of_question1++;
    } while (fgetc(military1_file) != EOF);
    *iq = right_answer1 * 100.00 / num_of_question1;
    printf("You score %f\n\n", *iq);
    fclose(military1_key);
    fclose(military1_file);
    if (*iq >= 50.0)
    {
        printf("Congratulations! You have sucessfully cleared IQ test.\n\n");
        FILE *military_file;
        FILE *military_key;
        military_file = fopen("Military.txt", "r");
        military_key = fopen("militarykey.txt", "r");
        if (military_file == NULL)
        {
            printf("Error\n");
            return 0;
        }
        printf("\t\tMILITARY TEST (Round #2)\n");
        char ques[1000];
        char user_answer2, correct_answer2;
        int num_of_question2 = 0;
        int right_answer2 = 0;
        do
        {
            for (int i = 0; i < 5; i++)
            {
                fscanf(military_file, "%[^\n]\n", ques);
                printf("%s\n", ques);
            }
            fscanf(military_key, "%c", &correct_answer2);
            scanf(" %c", &user_answer2);
            if (user_answer2 == correct_answer2)
            {
                right_answer2++;
            }
            num_of_question2++;
        } while (fgetc(military_file) != EOF);
        *theo = right_answer2 * 100.00 / num_of_question2;
        printf("You score %f\n\n",*theo );
        fclose(military_file);
        fclose(military_key);
        if (*theo >= 50.0)
        {
            printf("Congratulations! You have sucessfully cleared Military test.\n");
        }
        else
        {
            printf("You have not cleared Military test. Better luck next time :(\n");
        }
    }
    else
    {
        printf("You have not cleared IQ test. Better luck next time :( \n");
    }
}

int registration_checker(int roll_no, std *a)
{
    for (int i = 0; i < count; i++)
    {
        if (a[i].rollno == roll_no)
        {
            return 1;
        }
    }
}
int appendSat()
{
    FILE *ptr = fopen("SAT.txt", "a");
    FILE *ptr1 = fopen("sat_key.txt", "a");
    if (ptr == NULL || ptr1 == NULL)
    {
        printf("Error\n");
        return 0;
    }

    char input[1000], key;
    printf("Enter a question:\n");
    for (int i = 0; i < 6; i++)
    {
        fgets(input, 1000, stdin);
        fprintf(ptr, "%s", input);
    }
    printf("Enter answer key\n");
    scanf(" %c", &key);
    fprintf(ptr1, "%c", key);

    fclose(ptr);
    fclose(ptr1);
}
int appendEcat()
{
    FILE *ptr = fopen("ECAT.txt", "a");
    FILE *ptr1 = fopen("ecat_key.txt", "a");
    if (ptr == NULL || ptr1 == NULL)
    {
        printf("Error\n");
        return 0;
    }

    char input[1000], key;
    printf("Enter a question:\n");
    for (int i = 0; i < 6; i++)
    {
        fgets(input, 1000, stdin);
        fprintf(ptr, "%s", input);
    }
    printf("Enter answer key\n");
    scanf(" %c", &key);
    fprintf(ptr1, "%c", key);

    fclose(ptr);
    fclose(ptr1);
}
int appendMil()
{
    char key;
        FILE *ptr = fopen("Military.txt", "a");
        FILE *ptr1 = fopen("militarykey.txt", "a");
        if (ptr == NULL || ptr1 == NULL)
        {
            printf("Error\n");
            return 0;
        }

        char input[1000];
        printf("Enter a question:\n");
        for (int i = 0; i < 6; i++)
        {
            fgets(input, 1000, stdin);
            fprintf(ptr, "%s", input);
        }
        printf("Enter answer key\n");
        scanf(" %c", &key);
        fprintf(ptr1, "%c", key);

        fclose(ptr);
        fclose(ptr1);
}
int appendiq(){
    char key;
        FILE *ptr = fopen("military_iq.txt", "a");
        FILE *ptr1 = fopen("military__iq_key.txt", "a");
        if (ptr == NULL || ptr1 == NULL)
        {
            printf("Error\n");
            return 0;
        }

        char input[1000];
        printf("Enter a question:\n");
        for (int i = 0; i < 6; i++)
        {
            fgets(input, 1000, stdin);
            fprintf(ptr, "%s", input);
        }
        printf("Enter answer key\n");
        scanf(" %c", &key);
        fprintf(ptr1, "%c", key);

        fclose(ptr);
        fclose(ptr1);
     
}
