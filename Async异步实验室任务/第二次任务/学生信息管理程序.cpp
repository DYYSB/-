#define _CRT_SECURE_NO_WARNINGS     //防止scanf报错
#include <iostream>
#include <cstdio>
#include <string>

enum sextype { man, woman };   //枚举类型
typedef struct student
{
    union birthdate
    {
        unsigned int date = 0;
        struct
        {
            unsigned int day : 5;
            unsigned int month : 4;

            unsigned int year : 12;
        };
    } birth;
    //用共用体+位域来表示出生日期，以减少内存占用。
    int id;
    std::string name;
    sextype sex;
    int score1;
    int score2;
    int score3;
    int score4;
    student* next;
} _STUDENT;

_STUDENT* createHead()      //创建链表头
{
    _STUDENT* head = new _STUDENT;
    head->id = 0;
    head->name = "0";
    head->score1 = 0;
    head->score2 = 0;
    head->score3 = 0;
    head->score4 = 0;
    head->sex = man;
    head->birth.date = 0;
    head->next = NULL;
    return head;
}

_STUDENT* createNode(int id, std::string name, _STUDENT::birthdate birth, sextype sex, int score1, int score2, int score3, int score4)
//创建链表结点，即每一个学生的信息
{
    _STUDENT* mid = new _STUDENT;
    mid->id = id;
    mid->birth = birth;
    mid->name = name;
    mid->sex = sex;
    mid->score1 = score1;
    mid->score2 = score2;
    mid->score3 = score3;
    mid->score4 = score4;
    mid->next = NULL;
    return mid;
}

_STUDENT* createData()
{
    int id;
    std::string name;
    _STUDENT::birthdate birth;
    unsigned year;
    unsigned month;
    unsigned day;
    sextype sex;
    int sexnum;
    int score1;
    int score2;
    int score3;
    int score4;
    char separate;
    //bool flag = false;
    _STUDENT* head = createHead();
    _STUDENT* p = head;
    _STUDENT* r = head;
    std::cout << "Please input students' data until you input -1." << std::endl;
    std::cout << "Input student's ID, name, birth date, sex(0 is man, 1 is woman), score1, score2, score3, score4 like this:" << std::endl;
    std::cout << "000 dyy 1970/1/1 0 100 100 100 100" << std::endl << std::endl;
    std::cin >> id;
    while (id != -1)
    {
        //std::scanf("%s %u/%u/%u %d %d %d %d %d", &name, &year, &month, &day, &sex, &score1, &score2, &score3, &score4);
        std::cin >> name >> year >> separate >> month >> separate >> day;
        std::scanf("%d", &sex);
        std::cin >> score1 >> score2 >> score3 >> score4;
        birth.day = day;
        birth.month = month;
        birth.year = year;
        p = createNode(id, name, birth, sex, score1, score2, score3, score4);
        r->next = p;
        r = p;
        std::cin >> id;
    }
    return head;
}

void outputNode(_STUDENT* p)        //输出链表，即输出所有的学生信息，传入值是表头地址
{
    int i = 0;                   //把p指针定位到链表的第一个非表头元素
    do
    {
        p = p->next;
        i++;
        std::cout << i << ".\t" << p->id << '\t' << p->name << '\t' << p->birth.year << '/' << p->birth.month << '/' << p->birth.day << '\t';
        std::cout << p->sex << '\t' << p->score1 << '\t' << p->score2 << '\t' << p->score3 << '\t' << p->score4 << std::endl;
    } while (p->next != NULL);
}

_STUDENT* searchNode(_STUDENT* p, std::string name)     //按照名字查找结点，传入值是表头地址和名字，暂时不支持重名查找
{
    do
    {
        p = p->next;
        if (p->name == name)
            return p;
    } while (p->next != NULL);
    return NULL;
}

int calAverage(_STUDENT* p, int i)          //计算第i科的平均成绩，传入表头和i
{
    int j = 0;
    int sum = 0;
    switch (i)
    {
    case 1:
        do
        {
            p = p->next;
            sum += p->score1;
            j++;
        } 
        while (p->next != NULL);
        return sum / j;

    case 2:
        do
        {
            p = p->next;
            sum += p->score2;
            j++;
        } while (p->next != NULL);
        return sum / j;

    case 3:
        do
        {
            p = p->next;
            sum += p->score3;
            j++;
        } while (p->next != NULL);
        return sum / j;

    case 4:
        do
        {
            p = p->next;
            sum += p->score4;
            j++;
        } while (p->next != NULL);
        return sum / j;
    
    default:
        return -1;
    }
}

double passRate(_STUDENT* p, int i)         //计算第i个学科的通过率，传入表头和i
{
    int j = 0;
    int sum = 0;
    double prate;
    switch (i)
    {
    case 1:
        do
        {
            p = p->next;
            if (p->score1 >= 60)
                sum++;
            j++;
        } 
        while (p->next != NULL);
        prate = (double)sum / (double)j;
        return prate;

    case 2:
        do
        {
            p = p->next;
            if (p->score2 >= 60)
                sum++;
            j++;
        } 
        while (p->next != NULL);
        prate = (double)sum / (double)j;
        return prate;

    case 3:
        do
        {
            p = p->next;
            if (p->score3 >= 60)
                sum++;
            j++;
        } 
        while (p->next != NULL);
        prate = (double)sum / (double)j;
        return prate;

    case 4:
        do
        {
            p = p->next;
            if (p->score4 >= 60)
                sum++;
            j++;
        } 
        while (p->next != NULL);
        prate = (double)sum / (double)j;
        return prate;

    default:
        return -1.0;
    }
}

_STUDENT* searchMinAge(_STUDENT* p)
{
    unsigned int max;
    _STUDENT* maxdate = p;
    if (p->next != NULL)
    {
        max = maxdate->birth.date;
    }
    do
    {
        p = p->next;
        if (max < p->birth.date)
        {
            max = p->birth.date;
            maxdate = p;
        }
    } 
    while (p->next != NULL);
    return maxdate;
}

void outputHello()
{
    std::cout << "-------------------------------------------------------" << std::endl;
    std::cout << std::endl;
    std::cout << "         Student Information Management System" << std::endl;
    std::cout << std::endl;
    std::cout << "              1.Input information" << std::endl << std::endl;
    std::cout << "              2.Show information" << std::endl << std::endl;
    std::cout << "              3.Search by name" << std::endl << std::endl;
    std::cout << "              4.Search the youngest" << std::endl << std::endl;
    std::cout << "              5.Calculate average score and pass rate" << std::endl << std::endl;
    std::cout << "              6.Exit" << std::endl << std::endl;
    std::cout << "-------------------------------------------------------" << std::endl << std::endl;
    std::cout << "Please input your choice:  ";
}

int main()
{
    int choice;
    _STUDENT* head = NULL;
    while (1)
    {
        system("cls");
        outputHello();
        std::cin >> choice;
        switch (choice)
        {
        case 1:
            system("cls");          //这一行是windows的清屏命令，在linux上使用请手动改动
            head = createData();
            std::cout << "Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
            break;

        case 2:
            system("cls");
            if (head != NULL)
            {
                outputNode(head);
            }
            else
            {
                std::cout << "It seems that you haven't entered any data." << std::endl;
            }
            std::cout << "Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
            break;

        case 3:
        {
            system("cls");
            if (head != NULL)
            {
                std::string stuname;
                std::cout << "Input the student's name: " << std::endl;
                std::cin >> stuname;
                _STUDENT* sname = searchNode(head, stuname);
                if (sname != NULL)
                {
                    std::cout << sname->id << ' ' << sname->name << ' ' << sname->birth.year << '/' << sname->birth.month << '/' << sname->birth.day << ' ';
                    std::cout << sname->sex << ' ' << sname->score1 << ' ' << sname->score2 << ' ' << sname->score3 << ' ' << sname->score4 << std::endl;
                    std::cout << "Press any key to continue...";
                    std::cin.ignore();
                    std::cin.get();
                }
                else
                {
                    std::cout << "Student not found!" << std::endl;
                    std::cout << "Press any key to continue...";
                    std::cin.ignore();
                    std::cin.get();
                }
            }
            else
            {
                std::cout << "It seems that you haven't entered any data." << std::endl;
                std::cout << "Press any key to continue...";
                std::cin.ignore();
                std::cin.get();
            }
            break;
        }
            
        case 4:
            system("cls");
            if (head != NULL)
            {
                _STUDENT* minage = searchMinAge(head);
                std::cout << minage->id << ' ' << minage->name << ' ' << minage->birth.year << '/' << minage->birth.month << '/' << minage->birth.day << ' ';
                std::cout << minage->sex << ' ' << minage->score1 << ' ' << minage->score2 << ' ' << minage->score3 << ' ' << minage->score4 << std::endl;
            }
            else
            {
                std::cout << "It seems that you haven't entered any data." << std::endl;
            }
            std::cout << "Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
            break;

        case 5:
            system("cls");
            if (head != NULL)
            {
                std::cout << "Please input the number of subject you want to calculate: ";
                int i;
                std::cin >> i;
                std::cout << "The average score is " << calAverage(head, i) << ", the pass rate is " << passRate(head, i) << "." << std::endl;
            }
            else
            {
                std::cout << "It seems that you haven't entered any data." << std::endl;
            }
            std::cout << "Press any key to continue...";
            std::cin.ignore();
            std::cin.get();
            break;

        case 6:
        {
            if (head != NULL)
            {
                _STUDENT* p = head->next;
                _STUDENT* r = head;
                while (p->next != NULL)
                {
                    free(r);
                    r = p;
                    p = p->next;
                }
            }
            return 0;
        }

        default:
        {
            std::cout << "Invalid input!" << std::endl << "Press any key to continue..." << std::endl;
            std::cin.ignore();
            std::cin.get();
        }  
        }
    }
}