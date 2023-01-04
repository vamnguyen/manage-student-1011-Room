#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;
#define lengthTable 70

struct Score
{
    double oop, dataStruct, dataBase;
};

typedef struct Student
{
    string id;
    string name;
    int age;
    Score score;

    void getStudentInfomation()
    {
        cout << "Enter ID: ";
        getline(cin, id);
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter score oop, dataStruct, dataBase: ";
        cin >> score.oop >> score.dataStruct >> score.dataBase;
        cin.ignore();
    }
} sv;

// Function read student infomation from file
void readFileStudentInfo(sv list[], int &num)
{
    // Init index of struct array list
    int i = 0;
    ifstream fileIn;

    fileIn.open("studentInfo.txt", ios_base::in);

    // Read the number students for num variable
    fileIn >> num;
    // Ignore character \n
    fileIn.ignore();
    // The loop will stop when the pointer reaches the end of the file
    while (!fileIn.eof())
    {
        // Initial struct temporary save data of file
        sv a;
        getline(fileIn, a.id, ',');
        getline(fileIn, a.name, ',');
        fileIn >> a.age;
        // Ignore character comma
        fileIn.ignore();

        fileIn >> a.score.oop;
        fileIn.ignore();
        fileIn >> a.score.dataStruct;
        fileIn.ignore();
        fileIn >> a.score.dataBase;
        // Ignore character \n
        fileIn.ignore();

        list[i++] = a;
    }

    fileIn.close();
}

void menu()
{
    cout << "-----------Menu Manage Student-----------\n";
    cout << "1. Get student infomation list from file" << endl;
    cout << "2. Print student list" << endl;
    cout << "3. Add one student" << endl;
    cout << "4. Delete one student" << endl;
    cout << "5. Find student infomation by ID" << endl;
    cout << "6. Sort student list by ID ascending" << endl;
    cout << "7. Sort student list alphabetically" << endl;
    cout << "0. Exit" << endl;
}

// void enterStudentList(sv list[], int &num)
// {
//     cout << "Enter the number students: ";
//     cin >> num;
//     cin.ignore();
//     for (int i = 0; i < num; i++)
//     {
//         cout << "Enter Student Infomation " << i + 1 << ":\n";
//         getStudentInfomation(list[i]);
//     }
// }

void printStudentInformation(sv sv)
{
    cout << "|" << setw(10) << left << sv.id << "|"
         << setw(25) << left << sv.name << "|"
         << setw(6) << left << sv.age << "|"
         << setw(4) << left << sv.score.oop << "|"
         << setw(10) << left << sv.score.dataStruct << "|"
         << setw(8) << left << sv.score.dataBase << "|" << endl;
}

void title()
{
    for (int i = 0; i < lengthTable; i++)
    {
        cout << "_";
    }
    cout << endl;

    cout << "|" << setw(10) << left << "ID"
         << "|"
         << setw(25) << left << "Full name"
         << setw(7) << left << "|Age"
         << setw(5) << left << "|OOP"
         << setw(11) << left << "|dataStruct"
         << setw(9) << left << "|dataBase"
         << "|" << endl;

    for (int i = 0; i < lengthTable; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void printStudentList(sv list[], int num)
{
    cout << "---------Student Infomation List---------\n";

    title();

    for (int i = 0; i < num; i++)
    {
        printStudentInformation(list[i]);
    }

    for (int i = 0; i < lengthTable; i++)
    {
        cout << "-";
    }
    cout << endl;
}

void addOneStudent(sv list[], int &num)
{
    num++;
    cout << "Enter the student information you need add:\n";

enterAgain:
    list[num - 1].getStudentInfomation();
    for (int i = 0; i < num - 1; i++)
    {
        if (list[i].id == list[num - 1].id)
        {
            cout << "ID is duplicated. Please enter again!\n";
            goto enterAgain;
        }
    }
    cout << "Added student information to the list\n";
}

void deleteOneStudent(sv list[], int &num)
{
    string idDel;
    cout << "Enter the student ID to delete: ";
    getline(cin, idDel);
    int flag = 0;
    for (int i = 0; i < num; i++)
    {
        if (list[i].id == idDel)
        {
            flag = 1;
            for (int j = i; j < num - 1; j++)
            {
                list[j] = list[j + 1];
            }
            num--;
        }
    }
    if (flag == 0)
        cout << "Can't find ID student to delete.\n";
    else
        cout << "Deleted student infomation\n";
}

void findStudentByID(sv list[], int num)
{
    string idFind;
    cout << "Enter the student ID you want to search: ";
    getline(cin, idFind);

    int flag = 0;
    for (int i = 0; i < num; i++)
    {
        if (list[i].id == idFind)
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        cout << "Can't find ID student\n";
        return;
    }
    // flag == 1
    title();
    for (int i = 0; i < num; i++)
    {
        if (list[i].id == idFind)
        {
            printStudentInformation(list[i]);
        }
    }
}

void sortStudentListIDascending(sv list[], int num)
{
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (list[i].id > list[j].id)
            {
                swap(list[i], list[j]);
            }
        }
    }
    cout << "ID had sorted ascending.\n";
}

// Get last word in string full name
string getLastWord(string name)
{
    int len = name.length();
    string s;
    int i = len - 1;
    while (name[i] != ' ')
    {
        i--;
    }
    // name[i] == ' '
    s = name.substr(i + 1);
    return s;
}

void sortNameByAlpha(sv list[], int num)
{
    // Iterate through student list
    for (int i = 0; i < num - 1; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (getLastWord(list[i].name).compare(getLastWord(list[j].name)) > 0)
            {
                swap(list[i], list[j]);
            }
        }
    }
    cout << "The list of students has been sorted alphabetically.\n";
}

int main()
{
    sv list[100];
    int num;
    char choose;

    do
    {
        system("cls");
        menu();

        int choice;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
            readFileStudentInfo(list, num);
            break;
        case 2:
            printStudentList(list, num);
            break;
        case 3:
            addOneStudent(list, num);
            break;
        case 4:
            deleteOneStudent(list, num);
            break;
        case 5:
            findStudentByID(list, num);
            break;
        case 6:
            sortStudentListIDascending(list, num);
            break;
        case 7:
            sortNameByAlpha(list, num);
            break;
        case 0:
            break;
        default:
            cout << "Your choice invalid!";
            break;
        }
        cout << "\nWould you like continue choose? (y/n): ";
        cin >> choose;
        if (choose == 'n' || choose == 'N')
            cout << "Good bye!" << endl;
    } while (choose == 'y' || choose == 'Y');

    return 0;
}
