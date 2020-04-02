#include<iostream>
#include<fstream>
#include<conio.h>
#include<string.h>
#include<windows.h>
//#include<thread>
#include<stdio.h>
#include<cstdlib>
#include<iomanip>
using namespace std;
bool validity(int );
bool validity(char *);
int x ;// no of books which user want to add at once
char verifypass[30];
bool validity1(char *);

void del_of_books();
int g;/*used in return 2 different variable in the same program*/ int g1;//used in addition and subtraction of book while issue and deposit

COORD coord={0,0};
void gotoxy(int x,int y)       //  the function gotoxy is used to display content on the console screen at desired coordinate's
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

void border()
{
    for(int i=0;i<29;i++)
	{
		for(int j=0;j<79;j++)
		{
			if(i==0 || j==0 || j==78 || i==28 || i==2 )
				cout<<"*";
			else
				cout<<" ";
        }
		cout<<endl;
	}
	gotoxy(30,1);
	cout<<"National Library";
}
void border1(int c)
{
	int i,j;
	for(i=0;i<c;i++)
	{
		for(j=0;j<93;j++)
		{
			if(i==0 || j==0 || j==92 || i==(c-1) || i==2 || (j==8 && i>2) || (j==19 && i>2) || (j==50 && i>2) || (j==79 && i>2)|| i==4 )
				cout<<"*";
			else
				cout<<" ";

		}
		cout<<"\n";
	}
	//i=1;
	gotoxy(34,1);
	cout<<"National Library";
	gotoxy(2,3);
	cout<<"Sr.No";
	gotoxy(11,3);
	cout<<"Ref_id";
	gotoxy(29,3);
	cout<<"Name of Book";
	gotoxy(58,3);
	cout<<"Name of author";
	gotoxy(83,3);
	cout<<"Quantity";
	//int k=5;
}

void space(int a,int b, int c, int d)
{
    for(int j=a; j<=b; j++)
            {
                for(int i=c; i<=d; i++)
                {
                    gotoxy(i,j);
                    cout<<" ";
                }
                cout<<endl;
            }
}

class book // in this class name of book and their reference id is unique
{
    int reference_id,quantity;
    char name_of_book[50],name_of_author[50];
public:
    void getdata()
    {
        used_id:
        gotoxy(6,5);
        cout<<"Enter reference id of book : ";cin>>reference_id;
        fflush(stdin);
        if(validity(reference_id)==1)
        {
            gotoxy(6,7);
            cout<<"Book of reference id : "<<reference_id<<" already exist in library";
            getch();
            space(5,7,6,55);
            goto used_id;
        }
        used_book:
        gotoxy(6,7);
        cout<<"Enter name of book : ";gets(name_of_book);
        if(validity(name_of_book)==1)
        {
            gotoxy(6,9);
            cout<<"Book already exist in library enter any key to reenter ";
            getch();
            space(6,9,6,61);
            goto used_book;
        }
        gotoxy(6,9);
        cout<<"Enter name of author : ";gets(name_of_author);
        gotoxy(6,11);
        cout<<"Quantity of this book : ";cin>>quantity;
    }

    void putdata(int po, int ks, int is)     // variable Po is used to change value of y coordinate object by object while displaying book list
    {                                       // "is" is used for displaying serial no. of book
            gotoxy(3,ks);                  // ks is to set the y coordinate of serial no that is "is"
            cout<<setw(2)<<is;
            gotoxy(13,po);
            cout<<reference_id;
            gotoxy(23,po);
            puts(name_of_book);
            gotoxy(57,po);
            puts(name_of_author);
            gotoxy(85,po);
            cout<<quantity;
    }
   int return_id()
   {
       return reference_id;
   }
   char* return_book()
   {
       return name_of_book;
   }
    void get_quantity(int q)
   {
    if(g1==1){quantity=quantity-q;}
    else if(g1==2){quantity=quantity+q;}}
};

bool validity(int temp)  // as we know reference id is unique therefore while addition of new book
{                        // id of new book must not be same as any of existing book so to this function
    fstream f;         // is used to check whether the book of id no entered is their in the national library
    f.open("shail.dat",ios::in|ios::out|ios::app|ios::binary);
    book b;
    while(f.read((char*)&b,sizeof(b)))
          {
              if(temp==b.return_id())
                return 1;
          }
    f.close();
    return 0;
}

bool validity(char *temp) // similarly book name is also unique
{                           // so book of same name must not be their in the library thus
    fstream f;             // this function will check if their exist any book which admin want to add.

    f.open("shail.dat",ios::in|ios::out|ios::app|ios::binary);
    book b;
    while(f.read((char*)&b,sizeof(b)))
    {
        if(strcmp(temp,b.return_book())==0)
            return 1;
    }
    f.close();
    return 0;
}

void add_of_books() // only for admin to add books to the library
{
    system("CLS");
	border();
	gotoxy(7,7);
	cout<<"Enter the No. of books you want to add...";
	cin>>x;


	for(int i=0;i<x;i++)
    {
        system("CLS");
        border();
        int c;
        fstream f;
        f.open("shail.dat",ios::app | ios::out | ios::binary);
         book b;
        b.getdata();
        f.write((char*)&b,sizeof(b));
        f.close();

        fstream cf;//to add length of border
        cf.open("count.txt",ios::in);
        if(cf)
        {
            fstream cf1;
            getch();
            cf1.open("count.txt",ios::out|ios::in);
            cf1>>c;

            cf1.close();
            cf1.open("count.txt",ios::trunc|ios::out);
            c++;
           // cout<<c;
            cf1<<c;
            cf1.close();
        }
        else
        {
            fstream cf1;
            cf1.open("count.txt",ios::out);
            cf1<<"7";
            cf1.close();
        }
        cf.close();
	}
}
void book_list() // a simple function which will display a book list
{
    gotoxy(4,4);
    system("CLS");
    int c;
    fstream  cf;
   cf.open("count.txt",ios::in);
   cf>>c;
   border1(c);
   cf.close();
    fstream f;
    f.open("shail.dat",ios::app|ios::out|ios::in|ios::binary);
   //border1(n);
    int p=5;
    book b;
    int k=5;
    int i=1;
    while(f.read((char*)&b,sizeof(b)))
    {
        b.putdata(p,k,i);
        p++;
        i++;
        k++;
    }
    getch();
}

int adminscreen() // when you choose admin in the very first screen being displayed
//adminscreen features will be displayed if and only if you enter the right password
{
	system("CLS");
	int x;
	border();
	gotoxy(5,5);
	cout<<"1.Addition of Books";
	gotoxy(5,7);
	cout<<"2.Deletion of Books";
	gotoxy(5,9);
	cout<<"3.List of Books available";
	gotoxy(5,11);
	cout<<"4.Login Screen";
	gotoxy(5,13);
	cout<<"5.Exit";
	gotoxy(27,17);
	cout<<"Enter your choice...";
	cin>>x;
	return x;
}
void del_of_books(int id)  // to delete a particular book this function is created , this function is only for admin
{
    book b;
    fstream f,tf;
    f.open("shail.dat",ios::in|ios::out|ios::app|ios::binary);
    tf.open("tshail.dat",ios::in|ios::out|ios::app|ios::binary);
    while(f.read((char*)&b,sizeof(b)))
          {
              if(id!=b.return_id())
              {
                tf.write((char*)&b,sizeof(b));
              }

          }
    f.close();
    tf.close();
    remove("shail.dat");
    rename("tshail.dat","shail.dat");
     int c;
    fstream  cf;
   cf.open("count.txt",ios::out| ios::in);   // value in the file count.txt is assigned to so called variable c
   cf>>c;                                       // as admin delete a book value of c is updated and then given back to file count.txt
   cf.close();
   cf.open("count.txt",ios::trunc|ios::out);
   c--;
   cf<<c;
  // border1(c);
   cf.close();
   // n--;
}

int logscreen() // first screen to be displayed
{
	int ch;
system("CLS");	//
	border();
	gotoxy(15,10);
	cout<<"1.ADMIN";
	gotoxy(37,10);
	cout<<"2.USER";
	gotoxy(54,10);
	cout<<"3.EXIT";
	gotoxy(27,17);
	cout<<"Enter your choice...";
	cin>>ch;
	return ch;
}
string getpass(const char *prompt, bool show_asterisk=true)   // this function will display asterisk while entering password
{
  const char BACKSPACE=8;
  const char RETURN=13;

  string password;
  unsigned char ch=0;

  cout <<prompt;

  while((ch=getch())!=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                 cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else if(ch==0 || ch==224) // handle escape sequences
         {
             getch(); // ignore non printable chars
             continue;
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
}

class users   // user class it  stores some detail of user which are necessary. And are listed in the class
{
    char Id[40];
    char password[30];
    char  ph_no[12];
public:
    void getdata1()   // getdata1 is for new user that is to create a new library id
    {
        gotoxy(12,6);
        cout<<"Create your Library id : ";
        cin>>Id;
        reenter_pass1:
        gotoxy(12,8);
        cout<<"Create a password : ";
        cin>>password;
        gotoxy(12,10);
        cout<<"Reenter your password : ";
        cin>>verifypass;
        if(strcmp(password,verifypass)!=0)
        {
            gotoxy(12,12);
            cout<<"Both password are different press any key to continue";
            getch();
            space(8,12,10,70);
            goto reenter_pass1;
        }
        phno:
        gotoxy(12,12);
        cout<<"Enter your Contact no. : ";
        cin>>ph_no;
        if(strlen(ph_no)!=10)
        {
            gotoxy(12,14);
            cout<<"Invalid length of contact no :";
            getch();
            space(12,14,12,70);
            goto phno;
        }
    }

    void getdata2()  // getdata 2 is for login screen
    {
        g=1;
        id:
        gotoxy(12,6);
        cout<<"Enter your library id : ";
        cin>>Id;
        if(validity1(Id)==1)
           {
                gotoxy(12,8);
                cout<<"Invalid Library Id";
                getch();
                space(6,8,12,60);
        goto id;
        }
        else{
            g++;}

        reenter_pass2:
        gotoxy(12,8);
        cout<<"Enter your password : ";
        cin>>password;
        if(validity1(password)==1)
        {
            gotoxy(12,10);
            cout<<"Invalid Password";
            getch();
            space(8,10,12,60);
            goto reenter_pass2;
        }    // }
    }
    char * return_id()
    {
        return Id;
    }

    char * return_pass()
    {
        return password;
    }
};

bool validity1(char *temp)
{
    fstream uf;
    uf.open("ushail.dat",ios::in|ios::out|ios::app|ios::binary);
    users u;

    while(uf.read((char*)&u,sizeof(u)))
    {
        if(g==1)
        {
        if(strcmp(temp,u.return_id())==0)             //to verify id of user
        return 0;
        }
        else
        {
        if(strcmp(temp,u.return_pass())==0)
        return 0;
        }
    }
    uf.close();
    return 1;
}

int userscreen()      // displays user screen in which login and such options are their
{
	system("cls");
	border();
	gotoxy(9,9);
	cout<<"1.Sign up ";
	gotoxy(36,9);
	cout<<"2.Log In ";
    gotoxy(60,9);
	cout<<"3.Login Screen ";
	gotoxy(25,17);
	cout<<"Enter your choice....";
	int x;
	cin>>x;
	return x;
}

int mscreen_user() // Main screen user function is used to display the option which user can operate
{
	int x;
    system("CLS");
	border();
	gotoxy(5,5);
	cout<<"1.List of Books available";
	gotoxy(5,7);
	cout<<"2.Issue Books";
	gotoxy(5,9);
	cout<<"3.Deposit Books";
	gotoxy(5,11);
	cout<<"4.login Screen";
	gotoxy(5,13);
	cout<<"5.Exit";
	gotoxy(27,17);
	cout<<"Enter your choice...";
	cin>>x;
	return x;
}

void signup()  // this function is for new user to sign up in national library
{
    system("cls");
    border();
    fstream uf;
    uf.open("ushail.dat",ios::app|ios::out|ios::binary);
    users u;
    u.getdata1();
    uf.write((char*)&u,sizeof(u));
    uf.close();
}

void login()  // login function will allow signed user to open the main screen user function
{
    system("cls");
    border();
    fstream uf;
    uf.open("ushail.dat",ios::app|ios::out|ios::binary);
    users u;
    u.getdata2();
    uf.read((char *)&u,sizeof(u));
    uf.close();
}

void Issue_book()    // this function is for user to issue book which are their in the library
{
    g1=1;
    char ubook[40];
    int uquantity;
    system("cls");
    border();
    gotoxy(17,10);
    cout<<"Enter the name of book : ";
    cin>>ubook;//    gotoxy();
    exceed_book:
    gotoxy(17,12);
    cout<<"Enter quantity of books you want : ";
    cin>>uquantity;
    if(uquantity>5)
    {
        gotoxy(17,14);
        cout<<"you can't issue more then 5 books";
        getch();
        space(12,14,17,60);//system("cls");
        goto exceed_book;
    }
    fstream f,tf;
    f.open("shail.dat",ios::in|ios::out|ios::app |ios::binary);
    tf.open("tshail.dat",ios::in|ios::out|ios::app|ios::binary);
    book b;
    while(f.read((char *)&b,sizeof(b)))
    {
        if(strcmp(ubook,b.return_book())!=0)
        {
            tf.write((char*)&b,sizeof(b));   // to remove no of books ( no equal to no of books issued by user) of a particular book from book list
        }
        else
        {
            b.get_quantity(uquantity);
            tf.write((char*)&b,sizeof(b));
        }
    }
    f.close();
    tf.close();
     remove("shail.dat");
    rename("tshail.dat","shail.dat");
    getch();
}

  void deposit()
{
    g1=2;
    char ubook[40];
    int uquantity;
    system("cls");
    border();
    gotoxy(23,10);
    cout<<"Enter the name of book : ";
    cin>>ubook;//    gotoxy();
    gotoxy(23,12);
    cout<<"Enter quantity of books you want to deposit : ";
    cin>>uquantity;
    fstream f,tf;
    f.open("shail.dat",ios::in|ios::out|ios::app |ios::binary);
    tf.open("tshail.dat",ios::in|ios::out|ios::app|ios::binary);
    book b;
    while(f.read((char *)&b,sizeof(b)))
    {
        if(strcmp(ubook,b.return_book())!=0)
        {
            tf.write((char*)&b,sizeof(b));
        }
        else
        {
            b.get_quantity(uquantity);
            tf.write((char*)&b,sizeof(b));
        }
    }
    f.close();
    tf.close();
     remove("shail.dat");
    rename("tshail.dat","shail.dat");
    getch();
}

 library()  // this is the base function , from here it starts
{
  border();
  a:
  int mainscreen=logscreen();
  if(mainscreen==1)
  {
        b:
            system("cls");
            border();
            gotoxy(27,19);
            string pass=getpass("Enter your Password : ",true);
            if(pass=="Shail")
            {
                c:
                int admin=adminscreen();
                switch(admin)
                {
                case 1:
                    add_of_books();
                    goto c;
                case 2:
                    system("cls");
                    border();
                    gotoxy(10,14);
                    cout<<"Enter the reference id of book you want to delete : ";
                    int id;
                    cin>>id;
                    del_of_books(id);
                    goto c;
                case 3:
                    book_list();
                    goto c;
                case 4:
                    goto a;
                case 5:
                    goto exit;
                default:
                    cout<<"Wrong choice entered please try again :";
                    getch();
                    goto c;
                }
            }
            else
            {
                system("CLS");
                border();
                gotoxy(10,18);
                cout<<"Invalid password press any key to enter password ";
                getch();
                goto b;
            }
    }
    else if(mainscreen==2)  // user screen option are listed below using switch case
    {
        d:
            system("cls");
            border();
            int user=userscreen();
            switch(user)
            {
            case 1:
                signup();
                goto d;
            case 2:
                login();
                e:
                int msu;
                msu=mscreen_user();
                switch(msu)
                {
                case 1:
                    book_list();
                    goto e;
                case 2:
                    system("cls");
                    border();
                    Issue_book();
                    goto e;
                case 3:
                   deposit();
                    goto e;
                case 4:
                    goto a;
                case 5:
                    goto exit ;
                    //break;
                default :
                    system("cls");
                    border();
                    gotoxy(15,6);
                    cout<<"Invalid choice press any key to try again :";
                    getch();
                    goto e;
                }
                goto d;
            case 3:
                goto a;
            default:
                gotoxy(24,20);
                cout<<"Wrong choice entered please try again :";
                getch();
                goto d;
            }
    }
    else if(mainscreen==3)
        exit;
    else
    {
        system("cls");
        border();
        gotoxy(18,16);
        cout<<"Wrong Choice entered enter any key to continue :";
        getch();
        goto a;
    }
                exit:
                system("CLS");
                gotoxy(37,13);
                cout<<"THANK YOU";
                return 0;
}
int main()
{
    library();
}
