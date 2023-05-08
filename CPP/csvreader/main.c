#include <stdio.h>
#include <string.h>

struct Node
{
    int val;
    union
    {
        unsigned int day : 5;
        unsigned int month : 4;
        unsigned int year : 12;
        unsigned int date_comparer;
    } date;
    struct Node* next;
};

struct NodeField2
{
    int val;
    int max;
    struct Node* next;
};

struct NodeField1
{
    int val;
    struct NodeField2* next[81];
};

struct Root
{
    struct NodeField1* next[81];
};

struct Root* createTree()
{
    struct Root* root = (struct Root*)malloc(sizeof(struct Root));
    int i;
    for(i = 0; i < 81; i++)
    {
        root->next[i] = (struct NodeField1*)malloc(sizeof(struct NodeField1));
        int j;
        for(j = 0; j < 82; j++)
        {
            root->next[i]->next[j] = NULL;
        }
    }
    return root;
}



void readFile(struct Root* root, char* filepath)
{
    FILE* fp = fopen(filepath, "r");
    char buffer[100] = {0};
    fgets(buffer, 100, fp);
    memset(buffer, 0, 100);
    while(1)
    {
        int field1, field2, val;
        unsigned int day, year, month;
        int stat = fscanf(fp, "DC%d,DC%d,%u-%u-%u,%d\n", &field1, &field2, &year, &month, &day, &val);
        if(stat == EOF)
        {
            fclose(fp);
            printf("读取数据完成。\n");
            return;
        }
        // struct NodeField2* temp_p = root->next[field1]->next[field2];
        if(!root->next[field1]->next[field2])
        {
            root->next[field1]->next[field2] = (struct NodeField2*)malloc(sizeof(struct NodeField2));
            root->next[field1]->next[field2]->next = NULL;
        }
        struct Node* p = root->next[field1]->next[field2]->next;
        struct NodeField2* r = root->next[field1]->next[field2];
        while(p)
        {
            p = p->next;
            r = r->next;
            r = (struct Node*)r;
        }
        p = (struct Node*)malloc(sizeof(struct Node));
        p->next = NULL;
        r->next = p;
        p->val = val;
        p->date.day = day;
        p->date.month = month;
        p->date.year = year;
        printf("新数据存储完成。%d->%d。\n", field1, field2);
    }
    fclose(fp);
}

void compare(struct Root* root)
{
    int i, j;
    for(i = 0; i < 81; i++)
    {
        for(j = 0; j < 82; j++)
        {
            if(root->next[i] && root->next[i]->next[j] && root->next[i]->next[j]->next)
            {
                struct Node* p = root->next[i]->next[j]->next;
                while(p)
                {
                    if(root->next[i]->next[j]->max < p->val)
                    {
                        root->next[i]->next[j]->max = p->val;
                    }
                    p = p->next;
                }
            }
        }
    }
    printf("比较完成。\n");
}

void print(struct Root* root)
{
    FILE* fp = fopen("Route Data.txt", "w");
    int i, j;
    for(i = 0; i < 81; i++)
    {
        for(j = 0; j < 82; j++)
        {
            if(root->next[i] && root->next[i]->next[j] && root->next[i]->next[j]->next && root->next[i]->next[j]->max)
            {
                printf("DC%d到DC%d的线路中，物流量最大值为%d。\n", i, j, root->next[i]->next[j]->max);
                fprintf(fp, "DC%d到DC%d的线路中，物流量最大值为%d。\n", i, j, root->next[i]->next[j]->max);
            }
        }
    }
    fclose(fp);
}

int main()
{
    struct Root* root = createTree();
    char filepath[400] = {0};   // The path where you save your CSV file. 
    printf("拖入您的CSV文件存储路径（如果您将本程序和CSV文件放在同一个目录下，那么可以直接输入文件名（包含扩展名））");
    gets(filepath);
    readFile(root, filepath);
    compare(root);
    print(root);
    return 0;
}