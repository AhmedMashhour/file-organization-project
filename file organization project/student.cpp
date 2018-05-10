#include "student.h"
#include "registration.h"

student::student(void)
{
}

void student::add()
{
	ofstream f1;
	f1.open("student.txt",ios::in|ios::out|ios::app);

	string s;
	cout<<"enter student id: ";
	cin>>id;
	s=id;
	if(!search_id(s))
	{
		id=s;
		cout<<"enter student name:";
		cin>>name;
		cout<<"enter student grade:";
		cin>>grade;
		cout<<"enter student address:";
		cin>>address;

		stringstream ss;
		ss.str("");
		ss<<id<<"#"<<name<<"#"<<grade<<"#"<<address<<"#";
		f1.seekp(0,ios::end);
		int rrn=f1.tellp();
		f1<<ss.str();
		f1.close();
		int r=0;
		bool found=false;
		stringstream ss2;
		string indid,indrrn;
		fstream ind("index.txt",ios::in);
		while(1)
		{
			getline(ind,indid,'#');
			if(ind.fail())break;
			getline(ind,indrrn,'#');
			if(strcmp(indid.c_str(),id.c_str())>=0)
			{
				ss2<<id<<"#"<<rrn<<"#";
				ss2<<indid<<"#"<<indrrn<<"#";
				while(1)
				{
					getline(ind,indid,'#');
					if(ind.fail())break;
					getline(ind,indrrn,'#');
					ss2<<indid<<"#"<<indrrn<<"#";
				}
				found=true;
				break;
			}
			else
			{
				ss2<<indid<<"#"<<indrrn<<"#";
			}
			r++;
		}
		if(!found)
		{
			ss2<<id<<"#"<<rrn<<"#";
		}
		ss2.seekg(0,ios::end);
		int len=ss2.tellg();
		char *t=new char[len+1];
		ss2.seekg(0);
		ss2.read(t,len);
		ind.close();
		ind.open("index.txt",ios::trunc|ios::out);
		ind.write(t,len);
		ind.close();
	}
	else 
	{

		cout<<"id is found"<<endl;

	}
}
void student::show()
{
	fstream ifile("student.txt");
	ifstream ind("index.txt");
	int r=0;
	char c;
	string s;
	int rrn ;
	while(1)
	{
		getline(ind,id,'#');
		if(ind.fail())break;
		ind>>rrn;
		ind.ignore();
		ifile.seekg(rrn);
		ifile>>c;
		if(c!='*')
		{
			ifile.seekp(-1,ios::cur);
			getline(ifile,id,'#');
			getline(ifile,name,'#');
			getline(ifile,grade,'#');
			getline(ifile,address,'#');
			cout<<"record # "<<r++<<endl;
			display();
		}
		else
		{
			getline(ifile,s,'#');
			r++;
		}
	}
	ifile.close();
}
void student::delete_student(char key[11])
{
	ofstream f1;
	f1.open("student.txt",ios::in|ios::out|ios::app);

	string s;
	s=key;
	if(search_id(s))
	{
		ifstream in("registration.txt");
		char id_s[11],code_c[11],buf[21];
		char temp1[11];
		registration r;
		while(1) 
		{
			int i,j;
			strcpy(buf,"");
			in.read(buf,20);
			if(in.fail())break;
			for(i=0,j=0;i<10;i++)
				if(buf[i]!='.')
					temp1[j++]=buf[i];
			temp1[j]='\0';
			strcpy(id_s,temp1);
			if(strcmp(key,id_s)==0)
			{for(i,j=0;i<20;i++)
			if(buf[i]!='.')
				temp1[j++]=buf[i];
			temp1[j]='\0';
			strcpy(code_c,temp1);
			r.drop(key,code_c);
			}
		}
		deleter(s);
	}
	else 
	{

		cout<<"id of student is not found"<<endl;

	}
}
/**********************************************************************************************************/
void student::display()
{
	cout<<"student id: "<<id<<endl<<"student name: "<<name<<endl<<"student grade: "<<grade<<endl<<"student address: "<<address<<endl<<endl;
}

bool student::search_id(string key)
{
	fstream ifile("student.txt");
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

void student::deleter(string key)
{
	fstream file("student.txt",ios::out|ios::in);
	fstream avai("s_avai.txt",ios::out|ios::in|ios::binary);
	int x;
	string s="";
	int r=0;
	char c;
	while(1)
	{
		file>>c;
		if(file.fail())break;
		if(c!='*')
		{
			file.seekp(-1,ios::cur);
			getline(file,id,'#');
			getline(file,name,'#');
			getline(file,grade,'#');
			getline(file,address,'#');
			s=id+'#'+name+'#'+grade+'#'+address+'#';
			x=s.length();
			if(id==key)
			{
				file.seekp(-x,ios::cur);
				int ref=file.tellg();
				file<<"*";
				int counter=1;
				while(counter++<(x-1))
					file<<" ";
				file<<"#";
				file.close();


				avai.seekg(0,ios::end);
				avai<<ref<<"#";
				avai<<x<<"#";
				avai.close();
				break;
			}
		}
		else
		{
			getline(file,s,'#');
			r++;
		}
	}
}

student::~student(void)
{
}
