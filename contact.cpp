#include<iostream>
using namespace std;
#include<fstream>
string fname,lname,num;
//function declaration
void add_new();
void search();
void display();
bool check_num(string num);
void del_num();
void rename();
//function to add new contact to the file
void add_new()
{
	//output file stream 
	//opening the file to create/ write information ot the file
    ofstream phone("number.txt",ios :: app); 	
	system("cls");
	cout<<"\nEnter first name :";
	cin>>fname;
	cout<<"\nEnter last name :";
	cin>>lname;
	cout<<"\nEnter 10-digit phone number :";
	cin>>num;
	//call function ot check if the number is valid
	if(check_num(num)==true)
	{
		//write the inputted info to the file
		if(phone.is_open())
			{
				phone<<fname<<"\t"<<lname<<"\t"<<num<<"\n";
				cout<<"Number added successfully";
			}
		else
			cout<<"\nError opening the file";
	}
	else cout<<"\nInvalid input ! Please enter 10 digit valid phone number";
}
//function to check if all inputted characters of  phone number are digits
bool check_num(string num)
{
	bool check=true;
	//if the length of phone number is 10 and all characters are digits
	if(num.length()==10){
		for(int i=0;i<num.length();i++)
		{
			if(!(num[i]>=48 && num[i]<=57))
			{
			check= false;
			break;
			}
		}
	}
	else check=false;
	return check;
}
//function to search a contact
void search()
{
	string data;
	int f=0;
	cout<<"Enter the name to search :\n";
	cin>>data;
	//clear the screen
	system("cls");
    //opening the file in read mode
	ifstream phone("number.txt");
	//fetch each line from the file in 3 variables
	while(phone>>fname>>lname>>num)
	{
		//if inputted data matches with fname or lname, print the contact details
		if(fname==data || lname==data)
		{
			cout<<"\n\n\tCONTACT DETAILSS";
			cout<<"\nFirst Name : "<<fname;
			cout<<"\nLast Name : "<<lname;
			cout<<"\nPhone Number : "<<num;
			f=1;
		}
	}
	if(f==0) cout<<"\nData not found..";
}
//display all the contact information stored in the flie
void display()
{
	ifstream phone("number.txt");
    system("cls");
    cout<<"\n\n\tCONTACT DETAILS:";
	cout<<"\n\nFIRSTNAME\tLASTNAME\tNUMBER\n";
	while(phone>>fname>>lname>>num)
	{	
    	cout<<"\n"<<fname<<"\t\t"<<lname<<"\t\t"<<num<<"\n";
    }
    phone.close();
}
//function to delete a contact from the file
void del_num()
{
	string data1,data2;
	bool f=0;
	//input the first name and last name of contact to be deleted
	cout<<"Enter the first name whose number you want to delete :";
	cin>>data1;
	cout<<"Enter the last name whose number you want to delete :";
	cin>>data2;
	ifstream phone("number.txt");  //open in read mode(in)
	ofstream ovar;
	ovar.open("temp.txt",ofstream::out); //open in write mode(out)
	//read each line from number.txt
	while(phone>>fname>>lname>>num)
	{
		//if data does not match then only write all data to temp.txt
		if(!(fname==data1 && lname==data2))
		{
			ovar<<fname<<"\t"<<lname<<"\t"<<num<<"\n";
		}
		else f=1;
	}
	if(f==0) cout<<"\nContact does not exist..";
	else cout<<"Deletion Successful";
	//after writing contacts of number.txt to temp.txt, close both files
	ovar.close();
	phone.close();
	//delete number.txt file and rename temp.txt as number.txt
	remove("number.txt");
	rename("temp.txt","number.txt");
}
//function to rename a field in the contact file 
void rename()
{
	string data, data1;
	int f=0;
	int choice;
	cout<<"\nEnter the existing field :";
	cin>>data;
	ifstream phone("number.txt");  //open in read mode(in)
	ofstream ovar;
	ovar.open("temp.txt",ofstream::out); //open in write mode(out)
	//read each line from the file
	while(phone>>fname>>lname>>num)
	{
		//if none of the field matches wiht data, write the fields to the temp.txt file
		if(!(fname==data || lname==data || num==data))
		{
			ovar<<fname<<"\t"<<lname<<"\t"<<num<<"\n";
		}
		//if fistname matches with data, input new first name and replace old fname by new first name
		else if(fname==data)
		{
		    cout<<"\nEnter the new first name:";
			cin>>data1; f=1;	
			ovar<<data1<<"\t"<<lname<<"\t"<<num<<"\n";
		}  
		//if lastname matches with data, input new last name and replace old lname by new last name
		else if(lname==data)
		{ 
		    cout<<"\nEnter the new last name:";
			cin>>data1; f=2;
		    ovar<<fname<<"\t"<<data1<<"\t"<<num<<"\n";
		}
		//if number matches with data, input new number and replace old number by new number 
		else if(num==data)
		{
			//input the number and chekc if it is valid then add it to the file, else ask user to re-enter
			cout<<"\nEnter the new phone number: ";
		    cin>>data1;
			while(!check_num(data1)) 
			{
				cout<<"Please enter the new phone number: ";
				cin>>data1;
			}
			f=3;
		    ovar<<fname<<"\t"<<lname<<"\t"<<data1<<"\n";
	    }
	}
	if(f==0) cout<<"\nThis contact does not exist..";
	else cout<<"Rename operation successful";
	ovar.close();
	phone.close();
	remove("number.txt");
	rename("temp.txt","number.txt");
}
int main()
{
	int choice;
	system("cls");
	system("color 0A");
	cout<<"\n\t\tCONTACT MANAGEMENT";
	cout<<"\n\t\t------------------";
	while(1){
		cout<<"\n\n1. Add new contact\n2. Search an existing contact\n3. Display all contacts\n4. Delete a contact\n5. Renaming a field\n6. Exit";
		cout<<"\n\nENTER YOUR CHOICE : ";
		cin>>choice;
		switch(choice)
		{
			case 1: add_new(); break;
			case 2: search(); break;
			case 3: display(); break;
			case 4: del_num(); break;
			case 5: rename(); break;
			case 6: cout<<"\nThank you"; exit(0); break;
			default: cout<<"\nEnter valid choice..."; break;
		}
    }
	return 0;
}
