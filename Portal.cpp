#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

class Person
{
	public:
		int id, semester;
		string fname, lname, courses;
		string username, password, un, pw;
		
		int view_courses()
		{
			cout << "Availible Course List: \n";
			cout << "|COURSE_ID|COURSE_NAME|SEMESTER| \n";
			string myfile;
			ifstream ReadData("courselist.txt");
			while (getline (ReadData, myfile))
			{
				cout << myfile << endl;
			}
		
			ReadData.close();
		}
		
		int select_course()
		{
			view_courses();
			int x;
			cout << "\n How many courses you want to register?(Max 5): \n"; cin >> x;
			for (int i=0; i<x; i++)
			{
			    cin >> courses[i];
			}
			
			for (int i=0; i<x; i++)
			{
				cout << "  *You have been registered in: " << courses[i] << endl;
			}
		}

		int view_students()
		{
			cout << "Student List: \n";
			cout << "|Student_ID|Student_NAME|Program|CGPA|Credit_Hours|Pre-Req|Fee_Defaulter|Courses_Registered| \n";
			string myfile;
			ifstream ReadData("studentlist.txt");
			while (getline (ReadData, myfile))
			{
				cout << myfile << endl;
			}
		
			ReadData.close();
		}
		
		int view_teachers()
		{
			cout << "Teacher List: \n";
			string myfile;
			ifstream ReadData("teacherlist.txt");
			while (getline (ReadData, myfile))
			{
				cout << myfile << endl;
			}
		
			ReadData.close();
		}
};

class Student : public Person
{
	public:
		string program, pre_req, fee_def;
		float cgpa, credit_hours;
		
		int reg_courses()
		{
			cout << "Enter ID: "; 
			cin >> id;
			cout << "Enter First Name: "; 
			cin >> fname;
			cout << "Enter Last Name: "; 
			cin >> lname;
			cout << "Enter Program: "; 
			cin >> program;
			cout << "Enter CGPA: "; 
			cin >> cgpa;
			if(cgpa >= 3)
			{
				credit_hours = 21;	
			} 
			else if (cgpa >= 2)
			{
				credit_hours = 15;
			}
			cout << "Has the student completed prerequisite?(y/n) "; 
			cin >> pre_req;
			cout << "Is the student fee-defaulter?(y/n) "; 
			cin >> fee_def;
			
			ofstream Data;
			Data.open("studentlist.txt", ios::app);
			Data << "ID: " << id << "\nName: " << fname << " " << lname << "\nProgram: " << program << "\nCGPA:"<< cgpa;
			Data << "\nCredit Hours: " << credit_hours << "\nPre-Request: " << pre_req;
			Data << "\nFee Defaulter: " << fee_def << "\t" <<endl<< "Courses Registered: " << select_course() << endl;
			
			Data.close();
		}
		
		int student_portal()
		{
			char a;
			do
			{
				int o;
				cout << "\n\nSuccessfully logged in! \n";
				cout << "1. Register For Courses \n";
				cout << "2. View Student Details \n";
				cout << "Choose an option: \n"; cin >> o;
				switch (o)
				{
					case 1:
						reg_courses();
						break;
					case 2:
						view_students();
						break;
					default:
						cout << "Invalid Input Error \n";
				}
				cout << "Run Again(y/n)? "; cin >> a;
			} while(a == 'Y' || a == 'y');
		}
};

class Teacher : public Person
{
	public:
		int teach_course()
		{
			cout << "Enter First Name: \n"; cin >> fname;
			cout << "Enter Last Name: \n"; cin >> lname;
			view_courses();
			cout << "Select a course from above list: \n"; cin >> courses;
			
			ofstream Data;
			Data.open("teacherlist.txt", ios::app);
			
			Data << fname << " " << lname << "\t" << courses << "\t\n";
			Data.close();
		}
		
		int teacher_portal()
		{
			char a;
			do
			{
				int o;
				cout << "\n\nSuccessfully logged in! \n";
				cout << "1. Course Selection \n";
				cout << "2. View Teacher List \n";
				cout << "3. View Student List \n";
				cout << "Choose an option: \n"; cin >> o;
				switch (o)
				{
					case 1:
						teach_course();
						break;
					case 2:
						view_teachers();
						break;
					case 3:
						view_students();
					break;
					default:
						cout << "Invalid Input Error \n";
				}
				cout << "Run Again(y/n)? "; cin >> a;
			} while(a == 'Y' || a == 'y');
		}
};

class Advisor : public Person
{
	public:
		int n;
		string cname, i;
		int course_list_update()
		{
			char a;
			do
			{
				ofstream Data;
				Data.open("courselist.txt", ios::app);
			    cout << "Enter Course ID(do not enter spaces): "; 
				cin >> i;
				cout << "Enter Course Name(do not enter spaces): "; 
				cin >> cname;
				cout << "Enter Semester: "; 
				cin >> semester;
				
				Data << id << "\t" << cname << "\t" << semester << "\t" << endl;
				Data.close();
				
				cout << "Enter Another Course?(y/n): \n";
				cin >> a;
			} while(a == 'Y' || a == 'y');
		}
				
		int advisor_portal()
		{
			char a;
			do
			{
				int o;
				cout << "\n\nSuccessfully logged in! \n";
				cout << "1. Update Course List \n";
				cout << "2. View Teacher List \n";
				cout << "3. View Student List \n";
				cout << "4. View Course List \n";
				cout << "Choose an option: \n"; cin >> o;
				switch (o)
				{
					case 1:
						course_list_update();
						break;
					case 2:
						view_teachers();
						break;
					case 3:
						view_students();
						break;
					case 4:
						view_courses();
						break;
					default:
						cout << "Invalid Input Error \n";
				}
				cout << "Run Again(y/n)? "; cin >> a;
			} while(a == 'Y' || a == 'y');
		}
};

class Login_Signup : public Advisor
{
	public: 
		Person p;
		Student s;
		Teacher t;
		Advisor a;
		
		bool IsLoggedIn()
		{
			cout << "Enter username: "; cin >> username;
			cout << "Enter password: "; cin >> password;
			
			ifstream read(username.c_str());
			getline(read, un);
			getline(read, pw);
			
			if (un == username && pw == password)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	
		int login()
		{
			int c;
			cout << "1. Register\n2. Login\n choose option: "; cin >> c;
			if (c == 1)
			{
				cout << "Select username: "; cin >> username;
				cout << "Select password: "; cin >> password;
				ofstream file;
				file.open(username.c_str());
				file << username << endl << password;
				file.close();
				login();
			}
			else if (c == 2)
			{
				bool status = IsLoggedIn();
				if (!status)
				{
					cout << "Incorrect login! \n";
					return 0; 
				}
				else
				{
					cout << "\t\tWelcome To Our University Portal \n\n";
					cout << "1. Student Portal \n";
					cout << "2. Teacher Portal \n";
					cout << "3. Batch Advisor Portal \n";
					
					int option;
					cin >> option;
				 	
					switch (option)
					{
						case 1:
							s.student_portal();
							break;
						case 2:
							t.teacher_portal();
							break;
						case 3:
							a.advisor_portal();
							break;
						default:
							cout << "Invalid Input, try again";
							break;
					}
					
					return 1;
				}
			}
		}
};

int main()
{
	Login_Signup l;
	l.login();
	return 0;
}




