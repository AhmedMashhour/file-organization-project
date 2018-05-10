#include "course.h"
#include "registration.h"

course::course(void)
{
}

void course::add()
{
	cout<<"enter course code:";
	cin>>c_code;
	string s;
	s=c_code;
	if(search_code(s))
	{
		cout<<"course code is found "<<endl;
	}
	else
	{
		c_code=s;
		cout<<"enter course name:";
		cin>>c_name;
		cout<<"enter course description:";
		cin>>c_description;
		ofstream f3;
		f3.open("course.txt",ios::in|ios::out|ios::app);
		pack(f3);
		f3.close();
	}
}

void course::show()
{
	fstream f4("course.txt");
	unpack(f4);
	f4.close();
}

void course::delete_course(char key[11])
{
	string s;
	s=key;
	if(search_code(s))
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

			for(i,j=0;i<20;i++)
				if(buf[i]!='.')
					temp1[j++]=buf[i];
			temp1[j]='\0';
			strcpy(code_c,temp1);
			if(strcmp(key,code_c)==0)
				r.drop(id_s,key);
		}
		deleter(s);
	}
	else 
	{

		cout<<"course code is not found"<<endl;

	}
}
/**********************************************************************************************************/
void course::pack(ofstream &ofile)
{
	ss1.str("");


	ss1<<c_code.size()<<" "<<c_code<<c_name.size()<<" "<<c_name<<c_description.size()<<" "<<c_description;
	ofile<<ss1.str().size()<<" "<<ss1.str();																
}

void course::unpack(fstream &ifile)
{
	int re=0;
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
			cout<<"record="<<re<<endl;
			re++;
			ifile.ignore();
			t=new char[len+1];
			ifile.read(t,len);
			ss1.str(t);
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			cout<<"course code: "<<t<<endl;
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			cout<<"course name: "<<t<<endl;
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			cout<<"course description: "<<t<<endl;

			delete[] t;
		}
		else
		{
			re++;
		}
	}
}

bool course::search_code(string key)
{
	fstream ifile("course.txt");
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
			else{ss1>>len;
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
		}
	}
	return false;
}

void course::deleter(string key)
{
	fstream file("course.txt",ios::out|ios::in);
	fstream avai("c_avai.txt",ios::out|ios::in|ios::binary);
	c_code="";
	int x=0,re,len;
	int r=0;
	char *t;
	stringstream s;
	char c;
	while(1)
	{
		file>>c;
		if(file.fail())break;
		if(c!='*')
		{
			s.str("");
			file.seekp(-1,ios::cur);
			file>>len;
			x=len;
			s<<len<<" ";
			file.ignore();
			t=new char[len+1];
			file.read(t,len);
			ss1.str(t);
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			c_code=t;
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			c_name=t;
			ss1>>len;
			ss1.ignore();
			t=new char[len+1];
			ss1.read(t,len);
			t[len]='\0';
			c_description=t;

			delete[] t;
		}
		x=x+s.str().size();
		if(c_code==key)
		{
			file.seekp(-x,ios::cur);
			int ref=file.tellg();
			file<<"*";
			int counter=1;
			while(counter++<x)
				file<<" ";
			file.close();


			avai.seekg(0,ios::end);
			avai<<ref<<"#";
			avai<<x<<"#";
			avai.close();
			break;
		}
		else
			r++;
	}
}

course::~course(void)
{
}
