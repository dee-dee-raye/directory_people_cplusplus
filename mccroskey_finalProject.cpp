//==================================================================
//Dee Dee McCroskey
//12-10-15
//Final rogramming Assingment
//Description: Menu Driven Directory
//==================================================================

#include <cstdlib>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

//stores infromation for individual persons 
//that will be grouped in an array
struct Person				
{
	string firstName;	
	string lastName;
	string phoneNumber;
	string emailAddress;
};

//======================================================
// displayMenu: Displays menu, reads in user's selection
// parameters:
// return type: string
// choice: updated String of user's choice of action
//======================================================
string displayMenu();

//======================================================
// toUpperCaseAll: changes all characters into uppercase
// parameters:
// whole: String to be turned upper case
// return type: string
// whole: now uppercase string
//======================================================
string toUpperCaseAll(string);

//======================================================
// addPerson: adds person to directory from user input
// parameters: none
// return type: Person
// contactInfo: element of contactInfo array
//======================================================
Person addPerson();

//======================================================
// displayPersons: prints out contactInfo
// parameters: 
// contactInfo: array of directory
// count: number of elements in contactInfo
// return type: void
//======================================================
void displayPersons(Person[], int);

//======================================================
// loadTheFile: loads the file into contactInfo array
// parameters: 
// inputFile: file of directory
// contactInfo: array of directory
// size: max size of contactInfo array
// count: number of elements in contactInfo
// return type: int
// count: updated count
//======================================================
int loadTheFile(ifstream&, Person[], int, int);

//======================================================
// saveTheFile: loads contactInfo array into the file
// parameters: 
// contactInfo: array of directory
// count: number of elements in contactInfo
// return type: void
//======================================================
void saveTheFile(Person[], int);

//======================================================
// findPerson: inputs name from user and locates person
// if in directory
// parameters: 
// name: lastname of person to find
// contactInfo: array of directory
// count: number of elements in contactInfo
// return type: int
// location: location of searched person or -1
//if searched person is not in array
//======================================================
int findPerson(string, Person[], int);

//======================================================
// findAndDisplay: locate person and display information
// parameters: 
// contactInfo: array of directory
// count: number of elements in contactInfo
// return type: void
//======================================================
void findAndDisplay(Person[], int);

//======================================================
// findAndDelete: locate person and remove it from array
// parameters: 
// contactInfo: array of directory
// count: number of elements in contactInfo
// return type: int
// count: updated count
//======================================================
int findAndDelete(Person[], int);

int main()
{
	ifstream inputFile;					//Opens file that holds the values
	inputFile.open("book.txt");			//of the directory.

	if (inputFile)						//Checks that file opened successfully
	{

		const int size = 100;			//Max number of people in the directory.
		int count = 0;					//Count of number of elements used in directory array.
		Person contactInfo[size];

		//Opens file and loads array with its contents.
		loadTheFile(inputFile, contactInfo, size, count);


		string choice;					//User's choice of action.
		choice = displayMenu();			//Displays menu and gets first selction from user.

		//Runs until user exits program.
		while (choice != "E")
		{

			if (choice == "A")			//Add Person			
			{
				contactInfo[count] = addPerson();
				count++;
			}
			else if (choice == "D")		//Delete Person
			{
				count = findAndDelete(contactInfo, count);
			}
			else if (choice == "F")		//Find Person
			{
				findAndDisplay(contactInfo, count);
			}
			else if (choice == "L")		//List Persons
			{
				displayPersons(contactInfo, count);
			}
			else if (choice == "S")		//Save Directory
			{
				saveTheFile(contactInfo, count);
			}

			//Displays menu and updates choice of user.
			cout << " " << endl;
			choice = displayMenu();
		}

		//Exit of program. Saves array into file.
		cout << "You have exited the program." << endl;
		saveTheFile(contactInfo, count);

	}
	else								//If file did not open successfully
	{
		cout << "Error Opening File\nCannot Run Program" << endl;
	}

	return 0;
}

string displayMenu()
{
	string choice;

	cout << "\tMain Menu" << endl;
	cout << " " << endl;
	cout << "A - Add Person" << endl;
	cout << "D - Delete Person" << endl;
	cout << "F - Find and Display Person" << endl;
	cout << "L - List All People" << endl;
	cout << "S - Save List" << endl;
	cout << "E - Exit" << endl;
	cout << " " << endl;
	cout << "Enter Choice: ";
	getline(cin, choice);
	
	//validates user choice
	choice=toUpperCaseAll(choice);
	while (!(choice == "A" || choice == "D" || choice == "F" || choice == "L" 
		|| choice == "S" || choice == "E"))
	{
		cout << "Did not enter a possible value. Try again." << endl;
		cout << "Enter Choice: ";
		getline(cin, choice);
		choice = toUpperCaseAll(choice);
	}
	return choice;
}

string toUpperCaseAll(string whole)
{
	string result = whole;

	//changes all elements in string to uppercase
	for (int x = 0; x < result.length(); x++)
	{
		result[x] = toupper(result[x]);
	}
	return result;
}

Person addPerson()
{
	cout << " " << endl;
	Person toBeAdded;

	//get name from user
	string firstName;
	string lastName;
	cout << "Enter First Name: ";
	getline(cin, toBeAdded.firstName);
	cout << "Enter Last Name: ";
	getline(cin, toBeAdded.lastName);

	//get phone number from user
	cout << "Enter Phone Number: ";
	getline(cin, toBeAdded.phoneNumber);

	//get email address from user
	string email;
	int placeOfAt;
	bool valid;
	//verify email address until passes three checks
	do{
		cout << "Enter Email Address: ";
		getline(cin, email);
		valid = true;

		//check1 - for whitespace
		int x = 0;
		while (x < email.length() && valid)
		{
			if (email[x] == ' ')
			{
				valid = false;
				cout << "Your email address cannot have whitespace. Try again." << endl;
			}
			x++;
		}

		//check2 - for @
		placeOfAt = 0;
		bool noAt = true;
		x = 0;
		while (x < email.length() && valid && noAt)
		{
			if (email[x] == '@')
			{
				placeOfAt = x;
				noAt = false;
			}
			x++;
		}
		if (valid && (placeOfAt == 0 || noAt))
		{
			valid = false;
			cout << "You must have an @ sign and it has to be\n";
			cout << "somewhere between two characters in your email.Try again." << endl;
		}

		//check3 - for .
		bool noDot = true;
		x = placeOfAt + 1;
		while (x < email.length() && valid && noDot)
		{
			if (email[x] == '.')
			{
				noDot = false;
			}
			x++;
		}
		if (valid && noDot)
		{
			cout << "You must have a dot somewhere after your @ sign. Try again." << endl;
			valid = false;
		}

	} while (!(valid));
		
	toBeAdded.emailAddress = email;
	return toBeAdded;

}

void displayPersons(Person people[], int size)
{
	//sorts array into alphabetical order
	bool swap;
	Person temp;
	do
	{
		swap = false;
		for (int x = 0; x < (size - 1); x++)
		{
			if (toUpperCaseAll(people[x].lastName)>toUpperCaseAll(people[x+1].lastName))
			{
				temp = people[x];
				people[x] = people[x + 1];
				people[x + 1]= temp;
				swap = true;
			}
		}

	} while (swap);
	
	//prints out array
	for (int x = 0; x < size; x++)
	{
		cout<< "\nName: " << people[x].firstName <<" "<<people[x].lastName << endl;
		cout << "Phone Number: " << people[x].phoneNumber << endl;
		cout << "Email Address: " << people[x].emailAddress << endl;
	}

}

int loadTheFile(ifstream& inputFile, Person contactInfo[], int size, int count)
{
	//reads previous entries from file into the array
	while (getline(inputFile, contactInfo[count].lastName, ',') && count<size)				
	{
		getline(inputFile, contactInfo[count].firstName, ',');
		getline(inputFile, contactInfo[count].phoneNumber, ',');
		getline(inputFile, contactInfo[count].emailAddress, ',');
		count++;
	}
	count++;		//sets count to the total number of elements in the array
	return count;
}

void saveTheFile(Person contactInfo[], int count)
{
	//loads contents of array into newly blank file
	ofstream outputFile;
	outputFile.open("book.txt");
	for (int x = 0; x < count; x++)
	{
		outputFile << contactInfo[x].lastName << ",";
		outputFile << contactInfo[x].firstName << ",";
		outputFile << contactInfo[x].phoneNumber << ",";
		outputFile << contactInfo[x].emailAddress << endl;
	}
	//close file
	outputFile.close();
}

int findPerson(string name, Person contactInfo[], int count)
{
	bool stillLooking = true;
	int location = -1;

	//compares lastnames until one matches or out of elements to check
	for (int x = 0; x < count && stillLooking; x++)
	{
		if (toUpperCaseAll(name) == toUpperCaseAll(contactInfo[x].lastName))
		{
			location = x;
			stillLooking = false;
		}
	}

	return location;
}

void findAndDisplay(Person contactInfo[],int count)
{
	//get name of Person to search for
	string name;
	cout << "Enter Lastname of Person to Search For: ";
	getline(cin, name);
	//get location of person
	int lookHere = findPerson(name, contactInfo, count);

	if (lookHere != -1)		//if in array
	{
		cout << "Name: " << contactInfo[lookHere].firstName << " " << contactInfo[lookHere].lastName << endl;
		cout << "Phone: " << contactInfo[lookHere].phoneNumber << endl;
		cout << "Email: " << contactInfo[lookHere].emailAddress << endl;
	}
	else					//if not in array
	{
		cout << name << " is not in the directory." << endl;
	}
}

int findAndDelete(Person contactInfo[], int count)
{
	//get name of Person to delete
	string name;
	cout << "Enter Last Name of Person to be Deleted: ";
	getline(cin, name);
	// get location of Person in array
	int lookHere = findPerson(name, contactInfo, count);
	
	if (lookHere != -1)			//if in array
	{
		contactInfo[lookHere] = contactInfo[count - 1];
		count--;
	}
	else						//if not in array
	{
		cout << name << " is not in the directory." << endl;
	}
	return count;
}
