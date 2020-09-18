#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct json
{
    char Name[50];
    char Age[50];
    char BG[5];
    char State[50];
    char Country[50];
    int Agenum;

} cjson;

// char *serialize(const cjson *p);
char *serialize(char datas[10][10]);
void addJSON(char buf[1024], int a);

char buf[1024], datas[10][10];
int i = 0, state = 1, counter = 0, isFirst = 0;
;
cjson data;

int main(void)
{
    FILE *fp = fopen("input.csv", "r");
    FILE *fp1 = fopen("input.csv", "a");
    FILE *fptr = fopen("data.json", "a");
    // fprintf(fp1, "\r%d\n", 111);

    if (!fp)
    {
        printf("Can't open file\n");
        return 1;
    }
    //-----------------------------------First Object-----------------------------------------------//

    fgets(buf, 1024, fp);

    addJSON(buf, 1);

    //------------------------------------Rest Objects-----------------------------------------//

    while (fgets(buf, 1024, fp))
    {
        addJSON(buf, 0);
    }

    //------------------------------------Ending Bracket--------------------------------------------//

    fprintf(fptr, "%s", "]");

    //------------------------------------Closing The File--------------------------------------------//

    fclose(fp);
    fclose(fp1);
    fclose(fptr);

    return 0;
};
//------------------------------------------Struct Method------------------------------------------------//

/* 
char *serialize(const cjson *p)
{
    char *out = malloc(1024 * sizeof(*out));
    if (!out)
    {
        fprintf(stderr, "!! could not allocate memory\n");
    }
    else
    {
        memset(out, '\0', 1024);
        sprintf(out, "{\"Name\":\"%s\",\"Age\":%d,\"BG\":\"%s\",\"State\":\"%s\",\"Country\":\"%s\"}", p->Name, p->Agenum, p->BG, p->State, p->Country);
    }
    return out;
}

void addJSON(char buf[1024], int a)
{

    i = 0, state = 1, counter = 0;

    while (buf[i] != '\n')
    {
        printf("%c", buf[i]);
        if (buf[i] == ',')
        {
            switch (state)
            {
            case 1:
                state++;
                strncpy(data.Name,buf + (counter + 1), (i - 1) - counter);
                data.Name[i] = '\0';
                // printf("%s\n", data.Name);
                counter = i;
                break;
            case 2:
                state++;
                strncpy(data.Age, buf + (counter + 1), (i - 1) - counter);
                int value = atoi(data.Age);
                // printf("%d\n", value);
                data.Agenum = value;
                counter = i;
                break;
            case 3:
                state++;
                strncpy(data.BG, buf + (counter + 1), (i - 1) - counter);
                data.BG[(i - counter) - 1] = '\0';
                // printf("%s\n", data.BG);
                counter = i;
                break;

            case 4:
                state++;
                strncpy(data.State, buf + (counter + 1), (i - 1) - counter);
                data.State[(i - counter) - 1] = '\0';
                // printf("%s\n", data.State);
                counter = i;
                break;

            case 5:
                state++;
                strncpy(data.Country, buf + (counter + 1), (i - 1) - counter);
                data.Country[(i - counter) - 1] = '\0';
                // printf("%s\n", data.Country);
                counter = i;
                break;

            default:
                break;
            }
        }
        i++;
    }

    strncpy(data.Country, buf + (counter + 1), (i - 1) - counter);
    data.Country[(i - counter) - 1] = '\0';
    printf("%s\n", data.Country);
    counter = i;

    char *sdata1 = serialize(&data);
    FILE *fptr = fopen("data.json", "a");
    if (a == 1)
    {
        fprintf(fptr, "%s", "[");
        fprintf(fptr, "%s\n", sdata1);
    }
    else if (a == 0)
    {
        fprintf(fptr, "%s", ",");
        fprintf(fptr, "%s\n", sdata1);
    }

    free(sdata1);
    fclose(fptr);
}
*/

//---------------------------------------------Array Method----------------------------------------------//

char *serialize(char datas[10][10])
{
    // printf("%s", datas[0]);
    char *out = malloc(1024 * sizeof(*out));
    if (!out)
    {
        fprintf(stderr, "!! could not allocate memory\n");
    }
    else
    {
        memset(out, '\0', 1024);
        sprintf(out, "{\"Name\":\"%s\",\"Age\":%s,\"BG\":\"%s\",\"State\":\"%s\",\"Country\":\"%s\"}", datas[0], datas[1], datas[2], datas[3], datas[4]);
    }
    return out;
}

void addJSON(char buf[1024], int a)
{

    i = 0, state = 0, counter = 0, isFirst = 0;

    while (buf[i] != '\n')
    {
        // printf("%c", buf[i]);
        if (buf[i] == ',')
        {
            if (isFirst == 0)
            {
                strncpy(datas[state], buf + (counter), (i + 1) - counter);
                datas[state][(i)] = '\0';
                // printf("%s\n", datas[state]);
                counter = i;
                state++;
                isFirst = 1;
            }
            else
            {
                strncpy(datas[state], buf + (counter + 1), (i - 1) - counter);
                datas[state][(i - counter) - 1] = '\0';
                // printf("%s\n", datas[state]);
                counter = i;
                state++;
            }
        }
        i++;
    }
    strncpy(datas[state], buf + (counter + 1), (i - 1) - counter);
    datas[state][(i - counter) - 1] = '\0';
    // printf("%s\n", datas[state]);
    counter = i;

    char *sdata1 = serialize(datas);
    FILE *fptr = fopen("data.json", "a");
    if (a == 1)
    {
        fprintf(fptr, "%s", "[");
        fprintf(fptr, "%s\n", sdata1);
    }
    else if (a == 0)
    {
        fprintf(fptr, "%s", ",");
        fprintf(fptr, "%s\n", sdata1);
    }

    free(sdata1);
    fclose(fptr);
}
