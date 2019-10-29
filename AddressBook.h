#include <iostream>
#include <string>
using namespace std;
struct PersonNode;

//Person node class
class AddressList
{
	private:
		PersonNode *head;
		PersonNode *tail;
		int length;
	public:
		//class constructor & destructor
		AddressList();
		~AddressList();
		
		bool IsEmpty();
		void Insert();
		void InsertNewNode(string first, string last, string address, string bday, string anniv);
		void Edit(string name);
		void Delete(string name);

		//print functions
		void DisplayAll();
		void GenerateBirthdayCards();
		void GenerateAnniversaryCards();	
};
struct PersonNode
{
	string firstName;
	string lastName;
	string homeAddress;
	string birthDate;
	string anniversaryDate;
	PersonNode *next;
};


