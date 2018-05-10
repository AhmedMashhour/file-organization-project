#include "student.h"
#include "course.h"
#include "registration.h"

int main()
{
	student s;
	course c;
	registration r;
	char key1[11],key2[11],key[11];
	int y;
	bool x=true;	
	while(x) 
	{
		cout<<endl;
		cout<<"                                                 \\|||/                             "<<endl;
		cout<<"                                                 (o o)                              "<<endl;
		cout<<"    .-.__________  +------------------------------(_)------------------------------+"<<endl;
		cout<<"----/ \_)_________) | Enter  0  to  exit                                            |"<<endl;
		cout<<"   (    ()___)     | Enter  1  to  add new student                                 |"<<endl;
		cout<<"        ()__)      | Enter  2  to  show all student                                |"<<endl;
		cout<<"----\____()_)       | Enter  3  to  add new course                                  |"<<endl;
		cout<<"                   | Enter  4  to  show all course                                 |"<<endl;
		cout<<"                   | Enter  5  to  register student in course                      |"<<endl;
		cout<<"                   | Enter  6  to  show courses which are registered by a student  |"<<endl;
		cout<<"                   | Enter  7  to  show students registred in a course             |"<<endl;
		cout<<"                   | Enter  8  to  drop course from student list                   |"<<endl;
		cout<<"                   | Enter  9  to  delete student                                  |"<<endl;
		cout<<"                   | Enter 10  to  delete course                                   |"<<endl;
		cout<<"                   +---------------------------------------------------------------+"<<endl<<endl;
		cin>>y;
		switch (y)
		{
		case 0:
			x=false;
			break;
		case 1:
			s.add();
			break;
		case 2:
			s.show();
			break;
		case 3:
			c.add();
			break;
		case 4:
			c.show();
			break;
		case 5:
			r.register_student();
			break;
		case 6:
			cout<<"enter student id: ";
	        cin>>key;
			r.show_courses(key);
			break;
		case 7:
			cout<<"enter course code: ";
			cin>>key;
			r.show_students(key);
			break;
		case 8:
			cout<<"enter student id: ";
			cin>>key1;
			cout<<"enter course code: ";
			cin>>key2;
			r.drop(key1,key2);
			break;
		case 9:
			cout<<"enter student id: ";
			cin>>key;
			s.delete_student(key);
			break;
		case 10:
			cout<<"enter course code: ";
			cin>>key;
			c.delete_course(key);
			break;
		default:
			cout<<"wrong choice! ,please enter again"<<endl;
			break;
		}
	}
	system("pause");

}