#ifndef _STUD_CLASS_H
#define _STUD_CLASS_H 1

#ifndef _GLIBCXX_FSTREAM
#include<fstream>
#endif
 
#ifndef _CONIO_H
#include<conio.h>
#endif

enum updateArgs = {updateName = 1, updateStandard, updateRoll, updateUsername, updatePassword};

using namespace std;

class studClass
{
private:
    int ID;
    char* name;
    char* standard;
    int roll;
    char* password;

public:
    char* userName;
    char* status;
    studClass();
    int getDetails();
    const char* getPassword(char* prompt = "Enter your password :");
    int showDetails();
    int showDetails(char* name, char* username = nullptr);
    int updateUserDetails(int argInt, string argv = nullptr);
    int writeUserDetails(char* name = nullptr);
    ~studClass();
};

studClass::studClass()
{
    name = nullptr;
    standard = nullptr;
    roll = 0;
    password = nullptr;
    userName = nullptr;
}

studClass::~studClass()
{
    
}

int studClass::getDetails()
{
    int i=0;
    string ans;
    while(ans == "n" || ans == "N" || (strcasecmp(ans.c_str(), "no") == 0) )
    {
        try
        {
            cout<<"Enter name :";
            cin>>name;

            cout<<"Enter class :";
            cin>>standard;

            cout<<"Enter Roll number :";
            cin>>roll;

            cout<<"Enter userName :";
            cin>>userName;

            strcpy(password,getPassword() );

            cout<<"Your details are as follows :";
            cout<<"Name : "<<name<<endl
                <<"Class :"<<standard<<endl;
                <<"Roll number :"<<roll<<endl
                <<"Username : "<<userName<<endl;
            cout<<"Accept (y/n) [You can change later.] ? ";
            cin>>ans;
        }
        catch(const std::exception& e)
        {
            cerr << e.what() << '\n';
            return false;
        }
    }

    ofstream fout("\\\\qh-server\\SUMITRA\\E Old\\schoolChat\\Database.bin",ios::binary | ios::app);
    fout.write((char*) &this, sizeof(this));
    fout.close();

    return true;
}

const char* studClass::getPassword(char* prompt)
{
    const char BACKSPACE=8;
    const char RETURN=13;

    string password,confPassword;
    unsigned char ch=0;

    cout<<prompt<<endl;

    while( (ch = _getch()) != RETURN)
    {
        if(ch == BACKSPACE)
        {
            if(password.length() != 0)
            {
                cout <<"\b \b";
                password.erase(password.length()-1);
            }
        }

        else
        {
            password+=ch;
            cout <<'*';
        }
    }
    cout <<endl;
    cout<<"Confirm Password :";

    while( (ch = _getch()) != RETURN)
    {
        if(ch == BACKSPACE)
        {
            if(confPassword.length() != 0)
            {
                cout <<"\b \b";
                confPassword.erase(password.length()-1);
            }
        }

        else
        {
            confPassword+=ch;
            cout <<'*';
        }
    }
    cout<<endl;
    
    if (confPassword == password)
    {
        return password.c_str();
    }
    
    cout<<"Passwords are not matching please enter again!"<<endl<<endl;
    getPassword();
}

int studClass::showDetails()
{
    cout<<"Name : "<<name<<endl;
    cout<<"Roll :"<<roll<<endl;
    cout<<"Class :"<<standard<<endl;
    cout<<"Username :"<<userName<<endl;
}
int studClass::showDetails(char* queryName, char* queryUser)
{
    ifstream fin("\\\\qh-server\\SUMITRA\\E Old\\schoolChat\\Database.bin",ios::binary | ios::in)
    while (fin.read( (char*) &this, sizeof(this)))
    {
        if( strcasecmp(queryName , this->name) == 0 || strcasecmp(queryUser, this->userName) == 0)
        {
            this->showDetails();
            return true;
        }
    }
    
    return false;
}

int studClass::updateUserDetails(int argInt, string argv = nullptr)
{
    switch (argInt)
    {
    case updateName:
        cout<<"Enter new Name: ";
        cin>>name;
        writeUserDetails();
        break;
    
    default:
        break;
    }   
    
}

int studClass::writeUserDetails(char* queryName)
{
    studClass *temp;

    fstream finout("\\\\qh-server\\SUMITRA\\E Old\\schoolChat\\Database.bin", ios::binary | ios::in | ios::out);

    while (finout.read( (char*) temp, sizeof(temp)))
    {
        if(strcmp(this->userName, temp->userName) == 0 || strcmp(temp->name, queryName) == 0)
        {
            finout.seekp(-sizeof(this), SEEK_CUR);
            finout.write( (char*) this, sizeof(this));
            finout.close();
            delete temp;
            return true;
        }
    }
    return false;
}
#endif