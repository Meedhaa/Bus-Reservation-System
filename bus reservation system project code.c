#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<string>
#include<string.h>
#include<ctype.h>
#include<math.h>

using namespace std;

static int p{0};


void display_detail(int);
void display_codes();
void write();
void read();
void search_name();
void delete_record();
void modify();
void sort_name();
void count_res();

class reservation
{
    char first_name[10];
    char last_name[10];
    int age{};
    int date_of_birth{};
    char journey_end[15];
    char journey_start[15];

public:
    int bus1[48],bus2[48],bus3[48],bus4[48],bus5[48];

    reservation()
    {
        age=0;
        date_of_birth=0;
        first_name[0]='\0';
        last_name[0]='\0';
        journey_end[0]='\0';
        journey_start[0]='\0';
    }

    reservation(reservation &R)
    {
        age=R.age;
        date_of_birth=R.date_of_birth;
        strcpy(first_name,R.first_name);
        strcpy(last_name,R.last_name);
        strcpy(journey_start,R.journey_start);
        strcpy(journey_end,R.journey_end);
    }

    void getdata();
    void show();


    char *retfirstname()
    {
        return (first_name);
    }
    char *retlastname()
    {
        return (last_name);
    }
    char *retjs()
    {
        return (journey_start);
    }
    char *retje()
    {
        return (journey_end);
    }

};


/*----------------------------------------------------------------------------------------------*/

void reservation :: getdata()
{
    cout<<"\n\t Enter your First name: ";
    cin>>first_name;

    cout<<"\n\t Enter your Last name: ";
    cin>>last_name;

    cout<<"\n\t Enter your Age: ";
    cin>>age;

    cout<<"\n\t Enter your date_of_birth (ddmmyyyy): ";
    cin>>date_of_birth;

    cout<<"\n\t From: ";
    cin>>journey_start;

    cout<<"\n\t To: ";
    cin>>journey_end;

    p++;

}

/*----------------------------------------------------------------------------------------------*/

void reservation :: show()
{
    cout<<"                   FIRST NAME:     "<<first_name<<endl;
    cout<<"                   LAST NAME:      "<<last_name<<endl;
    cout<<"                   AGE:            "<<age<<endl;
    cout<<"                   DATE OF BIRTH:  "<<date_of_birth<<endl;
    cout<<"                   FROM:           "<<journey_start<<endl;
    cout<<"                   TO:             "<<journey_end<<endl;
}

/*----------------------------------------------------------------------------------------------*/

void write()
{
    reservation r;
    ofstream f("details.txt",ios::binary | ios::app );

    char reply;
    do
    {
        r.getdata();
        f.write((char*)&r,sizeof(r));
        cout<<"\n Do you wish to make another reservation? ";
        cin>>reply;

    }while(reply=='Y' || reply=='y');

    f.close();
}

/*----------------------------------------------------------------------------------------------*/

void read()
{
    ifstream f("details.txt",ios::binary | ios::in);
    reservation r;

    if(!f)
    {
        cout<<endl<<"\n Error! File does not exist!";
        return;
    }
    int ctr=0;

    while(f.read((char*)&r,sizeof(r)))
    {
        cout<<endl<<"\n Record: "<<++ctr<<endl;
        r.show();
    }
    f.close();
}

/*----------------------------------------------------------------------------------------------*/

void search_name()
{
    ifstream f("details.txt",ios::in | ios::binary);

    char found='N';
    reservation r;

    if(!f)
    {
        cout<<endl<<"\n Error! File does not exist. ";
        return;
    }

    char name[30];

    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    cout<<"\n Enter First name whose record is to be searched: ";
    gets(name);

    while(f.read((char*)&r,sizeof(r)))
    {
        if(strcmp(r.retfirstname(),name)==0)
        {
            cout<<"\n Details of the person are :";
            r.show();
            found='Y';
            break;
        }
    }

    if(found=='N')
    {
        cout<<"\n Sorry! No such record found!"<<endl;
    }

    f.close();
}

/*----------------------------------------------------------------------------------------------*/

void delete_record()
{
    ifstream fmain("details.txt", ios::binary | ios::in);
    ofstream ftemp("temp.dat", ios::binary | ios::out);

    reservation r;

    char name[20];

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"\n Enter First name to delete the record: ";
    gets(name);

    char found='N';
    while(fmain.read((char*)&r,sizeof(r)))
    {
        if(strcmp(r.retfirstname(),name)!=0)
        {
            ftemp.write((char*)&r,sizeof(r));
        }
        else
        {
            found='Y';
        }
    }

    if(found=='N')
    {
        cout<<"\n No such record found!!"<<endl;
    }
    else
    {
        cout<<"\n Record deleted!"<<endl;
    }

    fmain.close();
    ftemp.close();
    remove("details.txt");
    rename("temp.dat","details.txt");
}

/*----------------------------------------------------------------------------------------------*/

void modify()
{
    fstream f("details.txt", ios::in | ios::out | ios::binary);
    reservation r;

    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    char name[20];

    cout<<"\n Enter First name for modification: ";
    gets(name);

    int rec_count=0;
    char found='N';

    while(f.read((char*)&r,sizeof(r)))
    {
        if(strcmp(name,r.retfirstname())==0)
        {
            cout<<"\n Enter New Information";
            r.getdata();

            f.seekg(rec_count*sizeof(reservation),ios::beg);
            f.write((char*)&r,sizeof(reservation));

            found='Y';
            break;
        }

        rec_count++;
    }

    if(found=='Y')
    {
        cout<<"\n Reservation Updated";
    }
    else
    {
        cout<<"\n Record Not Found!!!!";
    }

    f.close();
}

/*----------------------------------------------------------------------------------------------*/

void sort_name()
{
    fstream f;
    f.open("details.txt",ios::binary | ios::in);
    reservation r[500];

    if(!f)
    {
        cout<<"\n Error! File does not exist. ";
        return;
    }

    int n=0;
    while(f.read((char*)&r[n],sizeof(reservation)))
     {
         n++;
     }

    reservation temp;

    int choice;

    cout<<"Sort"<<endl;
    cout<<"1. Ascending"<<endl;
    cout<<"2. Descending"<<endl;
    cin>>choice;

    if(choice==1)
    {
        for(int i=1;i<n;i++)
        {
            for(int j=0;j<n-i;j++)
            {
                if(strcmp(r[j].retfirstname(),r[j+1].retfirstname())>0)
                {
                    temp=r[j];
                    r[j]=r[j+1];
                    r[j+1]=temp;
                }
            }
        }
    }
    else
    {
        for(int i=1;i<n;i++)
        {
            for(int j=0;j<n-i;j++)
            {
                if(strcmp(r[j].retfirstname(),r[j+1].retfirstname())<0)
                {
                    temp=r[j];
                    r[j]=r[j+1];
                    r[j+1]=temp;
                }
            }
        }
    }

    f.close();
    f.open("details.txt",ios::binary | ios::out);

    int i=0;
    while(i<n)
    {
        f.write((char*)&r[i],sizeof(reservation));
        ++i;
    }

    cout<<"\n FILE SORTED"<<endl;
    f.close();

}

/*----------------------------------------------------------------------------------------------*/

void count_res()
{
    int num=0;
    reservation r;
    ifstream f("details.txt",ios::in|ios::binary);

    if(!f)
    {
        cout<<"\n Error! File does not exist. "<<endl;
        return;
    }

    while(f.read((char*)&r,sizeof(r)))
    {
        num++;
    }
    cout<<"\n Number of reservations recorded so far: "<<num;

    f.close();
}

/*----------------------------------------------------------------------------------------------*/

int main()
{
    cout<<"\n\n\n\n\n\t\t\t**********************************************************************"<<endl;
    cout<<"\t\t\t\t\tWelcome to the Bus Reservation Portal"<<endl;

    cout<<"\n\n\n\n\n\t\t\t\tCheck the services for admin and customer"<<endl;

    cout<<"\t\t SERVICES FOR CUSTOMER "<<endl;
    cout<<"\t\t\t\t1. Buses codes "<<endl;
    cout<<"\t\t\t\t2. Buses Details "<<endl;
    cout<<"\t\t\t\t3. Get  details of the user "<<endl;
    cout<<"\t\t\t\t4. Search a record "<<endl;
    cout<<"\t\t\t\t5. Calculate the total price of the ticket "<<endl;

    cout<<"\t\t SERVICES FOR ADMIN "<<endl;
    cout<<"\t\t\t\t1. Delete a record "<<endl;
    cout<<"\t\t\t\t2. Print details of the user "<<endl;
    cout<<"\t\t\t\t3. Modify a record "<<endl;
    cout<<"\t\t\t\t4. Count the number of records in the file "<<endl;

    cout<<"\t\t\t\t5. Sorting "<<endl;

    cout<<"\n\n\n\n\n\t\t\t**********************************************************************"<<endl;

    char ch;
    int select;

    do{

        cout<<"\t\t\t\t CUSTOMER? PRESS 1 "<<endl;
        cout<<"\t\t\t\t ADMIN? PRESS 2 "<<endl;

        cout<<"\t\n Enter your response: ";
        int response{};
        cin>>response;

        if (response==1)
        {
            cout<<"\t\t\t SERVICES FOR CUSTOMER "<<endl;
            cout<<"\t\t\t\t1. Buses codes "<<endl;
            cout<<"\t\t\t\t2. Buses Details "<<endl;
            cout<<"\t\t\t\t3. Get  details of the user "<<endl;
            cout<<"\t\t\t\t4. Search a record "<<endl;
            cout<<"\t\t\t\t5. Calculate the total price of the ticket "<<endl;
        }
        else if (response==2)
        {
            cout<<"\t\t\t\t SERVICES FOR ADMIN "<<endl;
            cout<<"\t\t\t\t6. Delete a record "<<endl;
            cout<<"\t\t\t\t7. Print details of the user "<<endl;
            cout<<"\t\t\t\t8. Modify a record "<<endl;
            cout<<"\t\t\t\t9. Count the number of records in the file "<<endl;
            cout<<"\t\t\t\t10. Sorting"<<endl;
        }

    cout<<"\t\t\t\t\nEnter your choice here: ";
    cin>>select;

    switch(select)
    {
        case 1:
        {
            cout<<"\t\n FOLLOWING ARE THE CODES FOR BUSES \n"<<endl;
            display_codes();
            break;
        }

        //**********************************************************
        case 2:
        {
            int number{};
            cout<<"\n Enter the bus number : ";
            cin>>number;
            display_detail(number);
        }
        break;
        //**********************************************************

        case 3:
        {
            cout<<"\n Enter the details :- \n"<<endl;
            write();
        }
        break;
        //**********************************************************

        case 4:
            {
                search_name();
            }
        break;
        //**********************************************************

        case 5:
            {
                cout<<"Calculation of total price :"<<" 500 rupees * "<<p<<" = "<<500*p<<endl;
            }
            break;
        //**********************************************************

        case 6:
            {
                int password{};
                cout<<"\nEnter the password : ";
                cin>>password;
                if (password==12345)
                {
                    delete_record();
                }
                else
                {
                    cout<<"\nWrong password!!"<<endl;
                }
                break;
            }
        //**********************************************************

        case 7:
            {
                int password{};
                cout<<"Enter the password : ";
                cin>>password;
                if (password==12345)
                {
                    read();
                }
                else
                {
                    cout<<"\nWrong password!!"<<endl;
                }
                break;
            }
        //**********************************************************

        case 8:
            {
                int password{};
                cout<<"Enter the password : ";
                cin>>password;
                if (password==12345)
                {
                    modify();
                }
                else
                {
                    cout<<"\nWrong password!!"<<endl;
                }
            }
        break;
        //**********************************************************

        case 9:
            {
                int password{};
                cout<<"Enter the password : ";
                cin>>password;
                if (password==12345)
                {
                    count_res();
                }
                else
                {
                    cout<<"\nWrong password!!"<<endl;
                }
            }
        break;
        //**********************************************************

        case 10:
        {
            sort_name();
        }
        break;
        //**********************************************************

        default:
        {
            cout<<"Alert! Invalid entry!"<<endl;
        }
        break;

    }

    cout<<"\n CONTINUE??";
    cin>>ch;
    cout<<endl;

    }while(ch=='y'||ch=='Y');


    cout<<"\n\n\n\n"<<endl;
    return 0;
}

/*----------------------------------------------------------------------------------------------*/

void display_detail(int num)
{
    switch(num)
    {
        case 100:
        {
            cout<<"\n Bus Number: 100"<<endl;
            cout<<" Driver's Name: Mukesh"<<endl;
            cout<<" Number plate: DL 1000 "<<endl;
        }
        break;

        case 101:
        {
            cout<<"\n Bus Number: 101"<<endl;
            cout<<" Driver's Name: Sanjay"<<endl;
            cout<<" Number plate: DL 1100 "<<endl;
        }
        break;

        case 102:
        {
            cout<<"\n Bus Number: 102"<<endl;
            cout<<" Driver's Name: Ali"<<endl;
            cout<<" Number plate: DL 1200 "<<endl;
        }
        break;

        case 103:
        {
            cout<<"\n Bus Number: 103"<<endl;
            cout<<" Driver's Name: Ravi"<<endl;
            cout<<" Number plate: DL 1300 "<<endl;
        }
        break;

        case 104:
        {
            cout<<"\n Bus Number: 104"<<endl;
            cout<<" Driver's Name: Rahul"<<endl;
            cout<<" Number plate: DL 1400 "<<endl;
        }
        break;
    }
}

/*----------------------------------------------------------------------------------------------*/

void display_codes()
{
            cout<<"                        BUS CODES"<<endl;
            cout<<"\n                   Bus Number: 100"<<endl;

            cout<<" Journey: "<<endl;
            cout<<" From: DELHI                                        TO: AGRA"<<endl;

            cout<<"\n                   Bus Number: 101"<<endl;

            cout<<" Journey: "<<endl;
            cout<<" From: DELHI                                        TO: JAIPUR"<<endl;

            cout<<"\n                   Bus Number: 102"<<endl;

            cout<<" Journey: "<<endl;
            cout<<" From: DELHI                                        TO: CHANDIGARH"<<endl;

            cout<<"\n                   Bus Number: 103"<<endl;

            cout<<" Journey: "<<endl;
            cout<<" From: DELHI                                        TO: LUCKNOW"<<endl;

            cout<<"\n                   Bus Number: 104"<<endl;

            cout<<" Journey: "<<endl;
            cout<<" From: DELHI                                        TO: UDAYPUR"<<endl;

}
