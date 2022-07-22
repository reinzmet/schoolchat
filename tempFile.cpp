#include<iostream.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>

class stud
{
//private:
public:
    stud *node;
    int roll;
    char name[20];
    int getDetails();
    void display(stud *firstNode);
    stud(void);
    ~stud();
} *first, *temp, *ptr;

stud::stud(void)
{
}

stud::~stud()
{
}

struct student
{
    int roll;
    int name[20];
    student *node;
};


int main()
{
    first = temp = new stud;
    int nodes;

    cout<<"Enter number of nodes :";
    cin>>nodes;

    cout<<"Enter roll :";
    cin>>first->roll;
    cout<<"Enter name : ";
    gets(first->name);
    
    temp = first;

    for (int i = 2; i <= nodes; i++)
    {
        ptr = new stud;
        cout<<"Enter roll :";
        cin>>ptr->roll;
        cout<<"Enter name : ";
        gets(ptr->name);
        temp->node = ptr;
        ptr->node = nullptr;
        temp = ptr;
    }

    ptr = first;

    while (ptr!= nullptr)
    {
        cout<<"Name : "<<ptr->name<<"\t"<<"Roll :"<<ptr->roll<<endl;
        ptr = ptr->node;
    }
    
    delete temp,ptr, first;
    return 0;
}