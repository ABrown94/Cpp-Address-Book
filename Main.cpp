#include <iostream>
#include <string>
#include <time.h>
#include "AddressBook.h"
using namespace std;

int getCommand(){
   cout <<" "<<endl;
   cout << "1. Add entry" << endl;
   cout << "2. Modify an entry" << endl;
   cout << "3. Delete an entry" << endl;
   cout << "4. Display all entries" << endl;
   cout << "5. Print birthday card" <<endl;
   cout << "6. Print anniversary card" <<endl;
   cout << "7. Quit" << endl;
   cout << "Enter your choice: ";
   int choice;
   cin >> choice;
   while(choice < 1 || choice > 7 || cin.fail()){
   		cin.clear();
   		cin.ignore(1024, '\n');
        cout << "Invalid choice. Select another option:" << endl;
        cin>>choice;
   }
   return choice;
}

int main(int argc, char** argv) {
		
	AddressList AL;
	string firstname;
	string lastname;
	string address;
	string bday;
	string anniv;
	int cmnd;
	do{
		cmnd = getCommand();
		switch(cmnd)
		{
			case 1:	
				AL.Insert();	
				break;
			case 2:
				cout<<"Enter the last name of the entry you wish to modify: ";
				cin>>lastname;
				AL.Edit(lastname);
				break;
			case 3:
				cout<<"Enter the last name of the entry you wish to delete: ";
				cin>>lastname;
				AL.Delete(lastname);
				break;
			case 4:
				AL.DisplayAll();
				break;
			case 5:
				AL.GenerateBirthdayCards();
				break;
			case 6:
				AL.GenerateAnniversaryCards();
				break;
			case 7:
				cout<<"Ending Program...";
				return 0;
				break;
		}
	}while(cmnd != 7);
	//return 0;
}
