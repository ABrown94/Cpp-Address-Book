#include <iostream>
#include <string>
#include <cstring>
#include <time.h>//for current date
#include "AddressBook.h"
using namespace std;

AddressList::AddressList()//constructor
{
	length = 0;
	
	head = new PersonNode; //header node
	head->firstName = "AAAAA";
	head->lastName = "AAAAA1";
	
	tail = new PersonNode;//trailer node
	tail->firstName = "ZZZZZ";
	tail->lastName = "ZZZZZ1";
	head->next = tail;
}
AddressList::~AddressList()//destructor
{
	  PersonNode* tempPtr;
	
	  while (tempPtr != tail)
	  {
	    tempPtr = head;
	    head = head->next;
	    delete tempPtr;
	  }
}
bool AddressList::IsEmpty()
{
	return (head->next == tail);
}
// returns date in DD/MM/YYYY format
string getDate() 
{
	string date;
	int day, month, year;
	cout<<"Enter day: ";
	cin>>day;
	if(day > 31 ){
		cout<<"Invalid day. Please enter another day: ";
		cin>>day;
	}	
	cout<<"Enter month: ";
	cin>>month;
	if(month > 12){
		cout<<"Invalid month. Please enter another month: ";
		cin>>month;
	}
	cout<<"Enter year: ";
	cin>>year;
	if(year < 1900 || year > 2018){
		cout<<"Please enter a valid year: ";
		cin>>year;
	}
	string strDay = to_string(day);
	string strMonth = to_string(month);
	string strYear = to_string(year);	
	date = strDay + "/" + strMonth + "/" + strYear;
	
	return date;
}
void AddressList::InsertNewNode(string first, string last, string address, string bday, string anniv)
{
	PersonNode *location = head; //traveling node
	PersonNode *prev = NULL; //trailing node	
	//new node
	PersonNode *newNode = new PersonNode;			
	newNode->firstName = first;
    newNode->lastName = last;
    newNode->homeAddress = address;
    newNode->birthDate = bday;
    newNode->anniversaryDate = anniv;
    
	//INSERTION	
	//if list is empty
	if(IsEmpty())
	{
		//insert after head node
		head->next = newNode;
		newNode->next = tail;
	}
	else
	{	//find insertion point	        
	                                    //compare strings alphabetically
		while(location != tail && last > location->lastName)
	    {   
	        prev = location;
	    	location = location->next;
	    }
   		//insert node in location 
   		prev->next = newNode;
		newNode->next = location;		
	}
	length++;
	
}
//INSERT
void AddressList::Insert()
{
	string first, last, address, bday;
	string anniv = "not married";
	
	cout<<"\nEnter first name: ";
	cin.ignore( 1024, '\n' );//end of line characters were left in buffer while reading command
	getline(cin, first);
	while(first == ""){
		cout<<"You didn't enter your first name. Please try again: ";
		getline(cin, first);
	}
	cout<<"\nEnter last name: ";
	getline(cin, last);
	while(last == ""){
		cout<<"You didn't enter your last name, please try again: ";
		getline(cin, last);
	}
	cout<<"\nEnter address: ";
	getline(cin, address);
	
	cout<<"\nEnter birth date (DD/MM/YYYY): "<<endl;			
	bday = getDate();
	
	string married;
	cout<<"\nAre you married? ";
	cin>>married;
	if(married == "yes" || married == "Yes" || married == "YES"){
		cout<<"Enter anniversary date (DD/MM/YYYY): "<<endl;
	    anniv = getDate();
	}
	InsertNewNode(first, last, address, bday, anniv);	
}

//EDIT
void AddressList::Edit(string nameToEdit)
{		
	if(IsEmpty())		
		cout<<"Address List is empty."<<endl;
	else
	{
		string yesOrNo;
		int choice;
		bool found = false;
		PersonNode *temp = head;
		while(temp != tail)
		{			
			if(temp->lastName == nameToEdit)
			{
			    cout<<"First Name: "<<temp->firstName<<endl;
	            cout<<"Last Name: "<<temp->lastName<<endl;
		        cout<<"Address: "<<temp->homeAddress<<endl;
		        cout<<"Birthday: "<<temp->birthDate<<endl;
		        cout<<"Anniversay: "<<temp->anniversaryDate;
		        cout<<" "<<endl;
			    cout<<"Is this the entry you wish to modify? (Y/N): ";
	        	cin>>yesOrNo;
	        	if(yesOrNo == "y" || yesOrNo == "Y" || yesOrNo == "yes" || yesOrNo == "Yes" || yesOrNo == "YES")
				{
		            found = true;		       
	     		    while(choice != 6)
				    {	
				       cout <<" "<<endl;		   
				       cout << "1. Edit First Name" << endl;
				       cout << "2. Edit Last Name" << endl;
				       cout << "3. Edit Address" << endl;
				       cout << "4. Edit Birthday" << endl;
				       cout << "5. Edit Anniversary Date" << endl;
				       cout << "6. Modification complete" <<endl;
				       cout << "Please select a number: ";
				       cin >> choice;
					   while(choice < 1 || choice > 6 || cin.fail()){
					   		cin.clear();
					   		cin.ignore(1024, '\n');
					        cout << "Invalid choice. Select another option:" << endl;
					        cin>>choice;
					   }
				       string newVal;
				       string formerLastName;
				       switch(choice)
					   {
				       		case 1:
			       				cout<<"\nEnter modified first name: ";
								cin.ignore( 1024, '\n' );
								getline(cin, newVal);
								while(newVal == ""){
									cout<<"You didn't enter a first name. Please try again: ";
									getline(cin, newVal);
								}
					            temp->firstName = newVal;
					            break;
				       		case 2:
				       			formerLastName = temp->lastName;
				       			cout<<"\nEnter modified last name: ";
								cin.ignore( 1024, '\n' );
								getline(cin, newVal);
								while(newVal == ""){
									cout<<"You didn't enter a last name. Please try again: ";
									getline(cin, newVal);
								}					       		
					            temp->lastName = newVal;
					            
					            if(formerLastName != newVal){
					            	//make copy of modified node
									PersonNode *editedNode = temp;
									string first = editedNode->firstName;
									string last = editedNode->lastName;
									string address = editedNode->homeAddress;
									string bday = editedNode->birthDate; 
									string anniv = editedNode->anniversaryDate;
									
									//delete node from list
									PersonNode* location = head;
								    PersonNode* prev = NULL;
	
								    while(location != tail)
								    {
								        if(location->lastName == temp->lastName)
								        {
								        	prev->next = temp->next;
								        	delete temp;							        	
								        	length--;
								        }
								        prev = location;
								        location = location->next;	        
								    }
								    //reinsert node
								    InsertNewNode(first, last, address, bday, anniv);			
								}				            	
					            break;
				       		case 3:
					       		cout << "Enter modified address: ";
								cin.ignore( 1024, '\n' );
								getline(cin, newVal);
					            temp->homeAddress = newVal;
					            break;
					        case 4:
					            temp->birthDate = getDate();
					            break;
					        case 5:
					            temp->anniversaryDate = getDate();
					            break;
					        case 6:
					        	break;
					    }
			        }
		        }
			}
			temp = temp->next;
		}
		if(!found)		    		
			cout<<nameToEdit<<" is not in the list."<<endl;							
	}
}
//DELETE
void AddressList::Delete(string nameToDelete)
{	
	if(IsEmpty())
		cout<<"Address List is empty."<<endl;
	else
	{	
		bool found = false;	
	    PersonNode* location = head;
	    PersonNode* prev = NULL;
	    int id = 0;
	    string yesOrNo;
	    while(location != tail)
	    {
	        if(location->lastName == nameToDelete)
	        {	        	
	        	cout<<"\nFirst Name: "<<location->firstName<<endl;
	            cout<<"Last Name: "<<location->lastName<<endl;
		        cout<<"Address: "<<location->homeAddress<<endl;
		        cout<<"Birthday: "<<location->birthDate<<endl;
		        cout<<"Anniversay: "<<location->anniversaryDate;
	        	cout<<" "<<endl;
	        	cout<<"Is this the entry you wish to delete? (Y/N): ";
	        	cin>>yesOrNo;
	        	if(yesOrNo == "y" || yesOrNo == "Y" || yesOrNo == "yes" || yesOrNo == "Yes" || yesOrNo == "YES"){
	        		found = true;
	        		prev->next = location->next;
		        	delete location;
		        	cout<<location->firstName<<" "<<nameToDelete<<" has been deleted."<<endl;	        	
		        	length--;
				}        	
	        }
	        prev = location;
	        location = location->next;	        
	    }	    
	    //length--;
	    if(!found)
	    	cout<<nameToDelete<<" is not in the list."<<endl;	    	
	}
}
//DISPLAY ALL ENTRIES
void AddressList::DisplayAll()
{	
	if(IsEmpty())
		cout<<"Address List is empty."<<endl;
	else
	{	
	    PersonNode *temp = head->next;	
		int count = 1;
		while(temp != tail)
		{
			
			cout<<" "<<endl;
			cout<< count << ") " << endl;
			cout<<"First Name: "<<temp->firstName<<endl;
			cout<<"Last Name: "<<temp->lastName<<endl;
			cout<<"Address: "<<temp->homeAddress<<endl;
			cout<<"Birthday: "<<temp->birthDate<<endl;
			cout<<"Anniversary: "<<temp->anniversaryDate<<endl;
			count++;
			temp = temp->next;
		}
	}
}
string GetCurrentDate()
{
	//full date
	string currentDate;	
	//date by month
	string currentDayAndMonth;
	
	time_t t = time(NULL);
	tm* timePtr = localtime(&t);
	int day = timePtr->tm_mday;
    int month = timePtr->tm_mon + 1;
    int year = timePtr->tm_year + 1900;
    
    //convert date to string for comparison
    string Day = to_string(day);
    string Month = to_string(month);
    string Year = to_string(year);
    
    currentDayAndMonth = Day + "/" + Month;
	return currentDayAndMonth;
}
void PrintBirthdayCard(string name)
{
	cout<<"Dear "<<name<<","<<endl;
	cout<<"I hope you have a wonderful birthday and that the coming year will be one of joy and success!"<<endl;
	cout<<"Sincerely, A. Brown\n"<<endl;	
}
void AddressList::GenerateBirthdayCards()
{
    string currentDate = GetCurrentDate();
    //compare current date to nodes
    if(IsEmpty())		
		cout<<"Address List is empty."<<endl;
	else
	{
		bool found = false;
		PersonNode *temp = head;
		string bdayByMonth;
		while(temp != tail)
		{
			bdayByMonth = temp->birthDate;
			bdayByMonth = bdayByMonth.substr(0,bdayByMonth.length()-5);	
			if(bdayByMonth == currentDate)
			{
				found = true;
				PrintBirthdayCard(temp->firstName);								
				//return;					
			}
			temp = temp->next;
		}
		if(!found)
			cout<<"There are no birthdays today."<<endl;
	}	
}
void PrintAnniversaryCard(string name)
{
	cout<<"Dear "<<name<<","<<endl;
	cout<<"I hope you have a wonderful anniversary!"<<endl;
	cout<<"Sincerely, A. Brown\n"<<endl;	
}
void AddressList::GenerateAnniversaryCards()
{
	string currentDate = GetCurrentDate();
    //compare current date to nodes
    if(IsEmpty())		
		cout<<"Address List is empty."<<endl;
	else
	{
		bool found = false;
		PersonNode *temp = head;
		string anniversaryByMonth;
		while(temp != tail)
		{
			anniversaryByMonth = temp->anniversaryDate;
			anniversaryByMonth = anniversaryByMonth.substr(0,anniversaryByMonth.length()-5);	
			if(anniversaryByMonth == currentDate)
			{
				found = true;
				PrintAnniversaryCard(temp->firstName);								
				//return;					
			}
			temp = temp->next;
		}
		if(!found)
			cout<<"There are no anniversaries today."<<endl;
	}	
}


