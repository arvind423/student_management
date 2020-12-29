#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;


//class starts from here

class student
{
	int rollno;
	char name[50];
	int physics_marks, chemistry_marks, maths_marks, english_marks, c_marks;
	double per;
	char grade;
	void calculate();	//function to calculate grade



public:
	void getdata();	//function to accept data from user
	void showdata() const;	//function to show data on screen
	void show_tabular() const;
	int retrollno() const;
}; //class ends here


void student::calculate()
{
	per=(physics_marks+chemistry_marks+maths_marks+english_marks+c_marks)/5.0;
	if(per>80)
		grade='A';
	else if(per>=60&&per<=80)
		grade='B';
	else if(per>=33)
		grade='C';
	else
		grade='F';
}

void student::getdata()
{
	cout<<"\nEnter The roll number of student: ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student: ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in physics out of 100 : ";
	cin>>physics_marks;
	cout<<"\nEnter The marks in chemistry out of 100 : ";
	cin>>chemistry_marks;
	cout<<"\nEnter The marks in maths out of 100 : ";
	cin>>maths_marks;
	cout<<"\nEnter The marks in english out of 100 : ";
	cin>>english_marks;
	cout<<"\nEnter The marks in c out of 100 : ";
	cin>>c_marks;
	calculate();
}

void student::showdata() const
{
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in Physics : "<<physics_marks;
	cout<<"\nMarks in Chemistry : "<<chemistry_marks;
	cout<<"\nMarks in Maths : "<<maths_marks;
	cout<<"\nMarks in English : "<<english_marks;
	cout<<"\nMarks in c :"<<c_marks;
	cout<<"\nPercentage of student is  :"<<per<<" %";
	cout<<"\nGrade of student is :"<<grade;
}


void student::show_tabular() const
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(12)<<physics_marks<<setw(4)<<chemistry_marks<<setw(4)<<maths_marks<<setw(4)<<english_marks<<setw(4)<<c_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}
	 
int  student::retrollno() const
{
	return rollno;
}


//all function declaration


void write_student();	//write the record in file
void display_all_students();		//read all records from file
void display_student(int);	//accept rollno and read record from file
void delete_student(int);	//accept rollno and delete selected records from file
void class_result();	//display all records in tabular format from file
void result();	//display result menu
void intro();	//display welcome screen
void entry_menu();	//display entry menu on screen


//main function of the program



int main()
{
	char ch;
	intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
			default :cout<<"\a";
		}
    }while(ch!='3');
	return 0;
}

//function to create record



void write_student()
{
	student st;
	ofstream outFile;
	outFile.open("student.txt",ios::app);
	st.getdata();
	outFile.write((char*)&st,sizeof(student));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created.. ";
	cin.ignore();
	cin.get();
}

//display all record from file


void display_all_students()
{
	student st;
	ifstream inFile;
	inFile.open("student.txt");
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\n\t\tDISPLAY ALL RECORD !!!\n\n";
	while(inFile.read((char*)&st,sizeof(student)))
	{
		st.showdata();
		cout<<"\n\n====================================\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

//function for specific record


void display_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.txt");
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read((char*)&st,sizeof(student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
			 flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}


//function to delete record from the file

void delete_student(int n)
{
	student st;
	ifstream inFile;
	inFile.open("student.txt");
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.txt",ios::out);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char*)&st,sizeof(student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write((char*)&st,sizeof(student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.txt");
	rename("Temp.txt","student.txt");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}

//function to display all result


void class_result()
{
	student st;
	ifstream inFile;
	inFile.open("student.txt");
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"==========================================================\n";
	cout<<"R.No       Name        P   C   M   E   CS   %age   Grade"<<endl;
	cout<<"==========================================================\n";
	while(inFile.read((char*)&st,sizeof(student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

//function to display result menus


void result()
{
	char ch;
	int rno;
	system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Specific Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1' :	class_result(); break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_student(rno); break;
	case '3' :	break;
	default:	cout<<"\a";
	}
}

//intro of project


void intro()
{
	cout<<"\n\n\n\t\tSTUDENT\tREPORT\tCARD";
	cin.get();
}

//edit record


void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.DELETE STUDENT RECORD";
	cout<<"\n\n\t5.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-5) ";
	cin>>ch;
	system("cls");
	switch(ch)
	{
	case '1':	write_student(); break;
	case '2':	display_all_students(); break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				display_student(num); break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				delete_student(num);break;
	case '5':	break;
	default:	cout<<"\a"; entry_menu();
	}
}

