//             PASSWORD FOR ADMINISTRATOR IS   "namang"
#include<fstream.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<process.h>
class canteen
{
	int code,price;
	char name[20];
	public:
	void read()
	{
		cout<<"\nEnter code ";
		cin>>code;
		cout<<"\nEnter name ";
		gets(name);
		cout<<"\nEnter price ";
		cin>>price;
		cout<<endl;
	}
	void disp()
	{
		cout<<"\ncode :"<<code;
		cout<<"\tname :"<<name;
		cout<<"\tprice :"<<price;
		cout<<endl;
	}
	int retcode()
	{
		return code;
	}
	int retprice()
	{
		return price;
	}
	char * retname()
	{
		return name;
	}
	void modify_c()
	{
		cout<<"\ncode ";
		cout<<code;
		cout<<"\nname ";
		puts(name);
		cout<<"\nprice ";
		cout<<price;
		cout<<endl;
		cout<<"ENTER NEW DETAILS\n";
		char num[20];
		int pie;
		cout<<"Enter new name(press. to retain old one)";
		gets(num);
		cout<<"Enter new price(press -1 to retain old one)";
		cin>>pie;
		if(strcmp(num,".")!=0)
		strcpy(name,num);
		if(pie!=-1)
		price=pie;
	}
};
void insert()
{
	ofstream fout("menu.txt",ios::app);
	canteen c;
	c.read();
	fout.write((char*)&c, sizeof(c));
	fout.close();
}
void display()
{
	ifstream fin("menu.txt");
	canteen c;
	while(!fin.eof())
	{
		fin.read((char*)&c,sizeof(c));
		if(fin.eof())
		break;
		c.disp();
	}
	fin.close();
}
void searchcode()
{
	ifstream fin("menu.txt");
	canteen c;
	int r,flag;
	flag=0;
	cout<<"\nenter code to be searched ";
	cin>>r;
	while(!fin.eof())
	{
		fin.read((char*)&c,sizeof(c));
		if(c.retcode()==r)
		{
			c.disp();
			flag=1;
			break;
		}
	}
	if(flag==0)
	cout<<"\nnot found";
	fin.close();
}
int bill()
{
	ifstream fin("menu.txt");
	canteen c;
	int cno,q,flag,l;
	flag=0;
	cout<<"\nEnter the code no. ";
	cin>>cno;
	cout<<"\nEnter quantity ";
	cin>>q;
	while(!fin.eof())
	{
		fin.read((char*)&c,sizeof(c));
		if(c.retcode()==cno)
		{
			l=c.retprice()*q;
			flag=1;
			return l;
		}
	}
	if(flag==0)
	cout<<"\ncode not found";
	fin.close();
	l=0;
	return l;
}
void searchname()
{
	ifstream fin("menu.txt");
	canteen c;
	int flag=0;
	char nm[20];
	cout<<"\nenter name to be searched ";
	gets(nm);
	while(!fin.eof())
	{
		fin.read((char*)&c,sizeof(c));
		if(strcmpi(c.retname(),nm)==0)
		{
			c.disp();
			flag=1;
			break;
		}
	}
	if(flag==0)
	cout<<"\nnot found";
	fin.close();
}
void Delete()
{
	canteen c;
	ifstream fin("menu.txt");
	ofstream fout("temp.txt");
	int r,flag;
	flag=0;
	cout<<"\nenter code whose record is to be deleted";
	cin>>r;
	while(!fin.eof())
	{
		fin.read((char*)&c,sizeof(c));
		if(fin.eof())
		break;
		if(c.retcode()==r)
		{
			flag=1;
			break;
		}
		else
		{
			fout.write((char*)&c,sizeof(c));
		}
	}
	if(!fin.eof())
	{
		while(!fin.eof())
		{
			fin.read((char*)&c,sizeof(c));
			if(fin.eof())
			break;
			fout.write((char*)&c,sizeof(c));
		}
	}
	if(flag==0)
	cout<<"\nnot found";
	fin.close();
	fout.close();
	remove("menu.txt");
	rename("temp.txt","menu.txt");
}
void modify()
{
	fstream fio;
	fio.open("menu.txt",ios::in|ios::out);
	canteen c;
	int r,flag,pos;
	flag=0;
	cout<<"\nenter code ";
	cin>>r;
	while(!fio.eof())
	{
		pos=fio.tellg();
		fio.read((char*)&c,sizeof(c));
		if(c.retcode()==r)
		{
			flag=1;
			c.modify_c();
			fio.seekg(pos,ios::beg);
			fio.write((char*)&c,sizeof(c));
		}
	}
	if(flag==0)
	cout<<"\nnot found";
	fio.close();
}
void main()
{
	int choice;
	char ans,a1,a2,ans1;
	char pass[7],str[7]="namang";
	do{
		clrscr();
		k:
		y:
		int c1;
		cout<<"\n------------------------------------------------------------------------------ ";
		cout<<"\n<<<<<<<<<<<<<<<<<<<<<<<<WELCOME TO GOEL FOOD COURT>>>>>>>>>>>>>>>>>>>>> ";
		cout<<"\n------------------------------------------------------------------------------ ";
		cout<<"\n1.Administrator";
		cout<<"\n2.User";
		cout<<"\n3.Exit";
		cout<<"\nEnter choice\n";
		cin>>c1;
		int c2;
		switch(c1)
		{
			case 1:
				cout<<"\nEnter password";
				char ch;
				int g=0;
				while(ch!=13)
				{
					ch=getch();
					if(ch==13)
						break;
					pass[g]=ch;
					g++;
					cout<<"*";
				}
				pass[g]='\0';
				if(strcmp(pass,str)==0)
				{
					do{
						clrscr();
						cout<<"\n1.insert new record in menu ";
						cout<<"\n2.display menu ";
						cout<<"\n3.delete a particular dish in menu ";
						cout<<"\n4.modify menu ";
						cout<<"\nEnter choice";
						cin>>c2;
						switch(c2)
						{
							case 1:
								int s;
								cout<<"\nEnter no of dishes to be inserted in the menu";
								cin>>s;
								for(int i=1;i<=s;i++)
								{
									insert();
								}
								break;
							case 2:
								display();
								break;
							case 3:
								Delete();
								break;
							case 4:
								modify();
								break;
						}
						cout<<"\nWant to continue for this menu(y/n)";
						cin>>a1;
					}while(a1=='y');
				}
				else
				{
					cout<<"\nwrong password";
					goto k;
				}
				break;
			case 2:
				do{
				f:
				clrscr();
				cout<<"\n1.search for price ";
				cout<<"\n2.display menu ";
				cout<<"\n3.billing ";
				cout<<"\n4.Exit";
				cout<<"\nEnter choice ";
				cin>>choice;
				switch(choice)
				{
					case 1:
						int ch;
						char ans1;
						do{
							clrscr();
							cout<<"\nsearch by ";
							cout<<"\n1.code ";
							cout<<"\n2.name ";
							cout<<"\n3.to go back to main menu ";
							cout<<"\nenter choice ";
							cin>>ch;
							switch(ch)
							{
								case 1:
									searchcode();
									break;
								case 2:
									searchname();
									break;
								case 3:
									goto f;
									break;
							}cout<<"\nWant to Go to Main Menu (y/n)";
							 cin>>ans1;
							}while(ans1=='n');
						break;
					case 2:
						display();
						break;
					case 3:
						float t=0;
						char a;
						ifstream fin("menu.txt");
						do{
							t=t+bill();
							cout<<"\nWant to enter more(y/n)";
							cin>>a;
						}while(a=='y');
						if(t>=500)
						{
							cout<<"\nAfter discount of 10%\n";
							t=t-(t*(1/10));

						}
						cout<<"\ntotal amount = "<<t;
						break;
					case 4:
						exit(0);
				}cout<<"\nWant to continue for this menu(y/n)";
				 cin>>a2;
				}while(a2=='y');
			case 3:
				goto y;
		}cout<<"\nWant to continue for main menu(y/n)";
		 cin>>ans;
	}while(ans=='y');
}

