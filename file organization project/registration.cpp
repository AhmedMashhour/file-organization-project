#include "registration.h"

registration::registration(void)
{
}

void registration::register_student()
{
	read_id_code();
	ifstream f6("registration.txt");

	string s1,s2;
	s1=id_s;
	s2=code_c;
	bool d=search_id_code(s1,s2,f6);

	if(search_id(s1)&&search_code(s2))
	{
		if (d==false)	
		{
			write("registration.txt");
			f6.close();}
		else 
		{
			cout<<"student is register in course"<<endl;
		}
	}
	else if(!search_id(s1)&&!search_code(s2))
		cout<<"student and course is not found"<<endl;
	else if(search_id(s1))
		cout<<"course is not found"<<endl;
	else
		cout<<"student is not found"<<endl;

}

void registration::show_courses(char id[11])
{
	string key;
	string st_id, name;
	key=id;
	ifstream ofile("student.txt");
	while(1)
	{
		getline(ofile,st_id,'#');
		if(ofile.fail())break;
		if(key==st_id)
		{
			getline(ofile,name,'#');
			cout<<"student name: "<<name<<endl;
			cout<<"*************"<<endl;
			break;
		}
	}
	ofile.close();
	if(search_id(key))
	{
		ifstream f6("registration.txt");	
		unpack_courses(id,f6);
		f6.close();
	}
	else
		cout<<"student not found in student file"<<endl;
}

void registration::show_students(char code[11])
{
	string c_code,c_name;
	stringstream ss1;
	int len;
	char *t;
	fstream ifile("course.txt");
	char c;
	while(1)
	{
		ifile>>c;
		if(ifile.fail())break;
		if(c!='*')
		{

			ifile.seekp(-1,ios::cur);
			ifile>>len;
			if(ifile.fail())break;
			ifile.ignore();
			t=new char[len+1];
			ifile.read(t,len);
			ss1.str(t);
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			if(strcmp(t,code)==0)
			{
				ss1>>len;
				ss1.ignore();
				t=new char[len+1];
				ss1.read(t,len);
				t[len]='\0';
				cout<<"course name: "<<t<<endl;
				cout<<"*************"<<endl;

				delete[] t;
				break;

			}
		}
	}
	ifile.close();
	string s;
	s=code;	
	if(search_code(s))
	{
		ifstream f6("registration.txt");
		unpack_student(code,f6);
		f6.close();
	}
	else
		cout<<"course not found in course file"<<endl;
}

void registration::drop(char key1[11],char key2[11])
{
	ifstream f6("registration.txt");
	string s1,s2;
	s1=key1;
	s2=key2;
	bool d=search_id_code(s1,s2,f6);

	if(search_id(s1)&&search_code(s2))
	{
		if (d==false)	
		{
			cout<<"student is not register in this course"<<endl;
		}
		else 
		{
			delete1(key1,key2);
		}
	}
	else if(search_id(s1))
		cout<<"course is not found"<<endl;
	else if(search_code(s2))
		cout<<"student is not found"<<endl;
	else
		cout<<"student and course is not found"<<endl;
		

}
/**********************************************************************************************************/
void registration::read_id_code()
{
	cout<<"enter student id: ";
	cin>>id_s;
	cout<<"enter course code: ";
	cin>>code_c;
}

void registration::write(string fn)
{
	fstream ofile(fn.c_str(),ios::out|ios::in);
	strcpy_s(buf,"");
	while(strlen(id_s)<10)
		strcat_s(id_s,".");
	strcat_s(buf,id_s);
	while(strlen(code_c)<10)
		strcat_s(code_c,".");
	strcat_s(buf,code_c);
	buf[20]='\0';
	fstream avai("r_avai.txt",ios::out|ios::in|ios::binary);
	int num;
	ofile.seekp(0,ios::end);
	if(avai>>num)
	{
		ofile.seekp(num,ios::beg);
		int y=avai.tellg();
		avai.seekp(-y,ios::cur);
		int counter=1;
		while(counter++<y+2)
			avai<<" ";
	}
	ofile.write(buf,20);

}

void registration::unpack_courses (char id[11],ifstream &in)
{
	int count=0;
	char temp1[11];
	string key;
	stringstream ss1;
	while(1) 
	{
		int i,j;
		strcpy_s(buf,"");
		in.read(buf,20);
		if(in.fail())break;
		for(i=0,j=0;i<10;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
		temp1[j]='\0';
		strcpy_s(id_s,temp1);
		if(strcmp(id,id_s)==0)
		{
			for(i,j=0;i<20;i++)
				if(buf[i]!='.')
					temp1[j++]=buf[i];
			temp1[j]='\0';
			strcpy_s(code_c,temp1);
			cout<<"course code: "<<code_c<<endl;

			key=code_c;
			int len;
			char *t;
			fstream ifile("course.txt");
			char c;
			while(1)
			{
				ifile>>c;
				if(ifile.fail())break;
				if(c!='*')
				{
					ifile.seekp(-1,ios::cur);
					ifile>>len;
					if(ifile.fail())break;


					ifile.ignore();
					t=new char[len+1];
					ifile.read(t,len);
					ss1.str(t);
					ss1>>len;
					ss1.ignore();
					t=new char[len+1];
					ss1.read(t,len);
					t[len]='\0';
					if(strcmp(t,key.c_str())==0)
					{
						ss1>>len;
						ss1.ignore();
						t=new char[len+1];
						ss1.read(t,len);
						t[len]='\0';
						cout<<"course name: "<<t<<endl;
						cout<<"*************"<<endl;

						delete[] t;
						break;

					}
				}
			}
			count++;
			ifile.close();
		}
	}
	if(count==0)
		cout<<"student has not register on any course"<<endl;
}
void registration::unpack_student(char code[11],ifstream &in)
{
	int count=0;
	char temp1[11];
	string key;
	string st_id, name;
	while(1) 
	{
		int i,j;
		strcpy_s(buf,"");
		in.read(buf,20);
		if(in.fail())break;
		for(i=0,j=0;i<10;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
		temp1[j]='\0';
		strcpy_s(id_s,temp1);

		for(i,j=0;i<20;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
		temp1[j]='\0';
		strcpy_s(code_c,temp1);
		if(strcmp(code,code_c)==0){
			cout<<"student id: "<<id_s<<endl;
			key=id_s;
			ifstream ofile("student.txt");
			while(1)
			{
				getline(ofile,st_id,'#');
				if(ofile.fail())break;
				if(key==st_id)
				{
					getline(ofile,name,'#');
					cout<<"student name: "<<name<<endl;
					cout<<"*************"<<endl;
					break;
				}
			}
			ofile.close();
			count++;
		}
	}
	if(count==0)
	{
		cout<<"course has not been registered by any student"<<endl;
	}
}
bool registration::search_id_code(string s, string s2,ifstream &ifile)
{
	int c=0;
	int d=0;
	char temp1[11];

	while(1)
	{
		int i,j;
		strcpy_s(buf,"");
		ifile.read(buf,20);
		if(ifile.fail())break;
		for(i=0,j=0;i<10;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
		temp1[j]='\0';
		strcpy_s(id_s,temp1);
		for(i,j=0;i<20;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
		temp1[j]='\0';
		strcpy_s(code_c,temp1);
		if(strcmp(id_s,s.c_str())==0)
		{
			if (strcmp(code_c,s2.c_str())==0)
				return 1;

		}

	}
	strcpy_s(id_s,s.c_str());
	strcpy_s(code_c,s2.c_str());
	return 0;
}

bool registration::search_id(string key)
{
	fstream ifile("student.txt");
	string id, name,grade,address;
	char c;
	string s;
	while(1)
	{
		ifile>>c;
		if(c!='*')
		{
			ifile.seekp(-1,ios::cur);
			getline(ifile,id,'#');
			if(ifile.fail())break;
			if(key==id)
			{
				return true;
			}
			getline(ifile,name,'#');
			getline(ifile,grade,'#');
			getline(ifile,address,'#');
		}
		else
		{
			getline(ifile,s,'#');
		}
	}
	return false;
}

bool registration::search_code(string key)
{
	fstream ifile("course.txt");
	string c_code,c_name,c_description;
	stringstream ss1;
	int len;
	char *t;
	char c;
	while(1)
	{
		ifile>>c;
		if(ifile.fail())break;
		if(c!='*')
		{
			ifile.seekp(-1,ios::cur);
			ifile>>len;
			if(ifile.fail())break;

			ifile.ignore();
			t=new char[len+1];
			ifile.read(t,len);
			ss1.str(t);
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			if(strcmp(t,key.c_str())==0)
			{
				return true;
				break;
			}
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';

			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';

			delete[] t;
		}
		else
			ifile.ignore();
	}
	return false;
}

void registration::delete1(char key1[11],char key2[11])
{
	fstream file("registration.txt",ios::out|ios::in);
	fstream avai("r_avai.txt",ios::out|ios::in|ios::binary);
	int r=0;
	char temp1[11];
	while(1)
	{
		int i,j;
		strcpy_s(buf,"");
		file.read(buf,20);
		if(file.fail())break;
		for(i=0,j=0;i<10;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
		temp1[j]='\0';
		strcpy_s(id_s,temp1);
		for(i,j=0;i<20;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
		temp1[j]='\0';
		strcpy_s(code_c,temp1);
		if((strcmp(id_s,key1)==0)&&(strcmp(code_c,key2)==0))
		{
			file.seekp(-20,ios::cur);
			int ref=file.tellg();
			file<<"*";
			int counter=1;
			while(counter++<20)
				file<<".";
			file.close();


			avai.seekg(0,ios::end);
			avai<<ref<<"#";
			avai.close();
			break;
		}
		else
			r++;
	}
}

registration::~registration(void)
{
}
