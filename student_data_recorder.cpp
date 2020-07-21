#include <fstream>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

using namespace std;

void write_student();       //to write data to file
void display_all();         //to display all stduent records
void display_sp(int);       //to display a specific record
void delete_record(int);

struct DOB          //date of birth
{
	int date, year;
	char month[10];
};

class Student
{
	private:

	int rollno;
	int admno;
	char name[20];
	int marks;
    char add[30];
    DOB dob;

    public:

	void getdata();            //to take input of student records from user
	void updatedata(int);      //to edit stduent record
	void display();            //to display student record
	int getno()            
	{
		return admno;
	}
}s;

void displayAll();
void Searchdisplay(int);
void DisplayClassResult();
void DisplayResult();

int main()          //**MAIN FUNCTION**
{
	int ch;
	int num;
	
	cout << "\t\t======STUDENT RECORD MANAGEMENT======\n\n";
	
    cout.setf(ios::fixed|ios::showpoint);
	cout<<setprecision(2);
	
    do
	{
		cout << "\t\t*MAIN MENU*";
		cout << "\n\n\t1.CREATE STUDENT RECORD";
		cout << "\n\n\t2.DISPLAY ALL STUDENT RECORDS";
		cout << "\n\n\t3.SEARCH STUDENT RECORD";
		cout << "\n\n\t4.EDIT STUDENT RECORD";
		cout << "\n\n\t5.DELETE STUDENT RECORD";
		cout << "\n\n\t6.DELETE ALL RECORDS";
		cout << "\n\n\t7.EXIT";
		cout << "\n\nPlease Enter Your Choice (1-7): ";
		cin >> ch;
		
		switch (ch)
		{
			case 1:     write_student();                   //write to file
			            cout << "\nPress Enter to continue...";
			            getch();
			            system("cls");
					    break;
			
            case 2:	    display_all();                     //display all student records
                        cout << "\nPress Enter to continue...";
                        getch();
                        system("cls");
						break;
			
            case 3:	    cout << "\n\nPlease Enter the Student's Admission No.: ";
						cin >> num;
						display_sp(num);                   //display specific student record
						cout << "\nPress Enter to continue...";
						getch();
						system("cls");
					    break;	    
					    
			case 4:     cout << "\n\nPlease Enter Admission No. of student whose record is to be edited: ";
			            cin >> num;
                        s.updatedata(num);                  //to edit a student record
                        cout << "\nPress Enter to continue...";
                        getch();
                        system("cls");
                        break;
			
			case 5:     cout << "\n\nPlease Enter Admission No. of student whose record is to be deleted: ";
			            cin >> num;
                        delete_record(num);                 //to delete a student record
                        cout << "\nPress Enter to continue...";
                        getch();
                        system("cls");
                        break;
                        
            case 6:     char c;
                        cout << "\nAre you sure you want to delete all student records? (y/n): ";
                        cin >> c;
                        
                        if (c == 'y' || c == 'Y')
                        {
                            remove("student.dat");           //deletes the file 'student.dat'
                            cout << "\nAll student records have been successfully deleted!";
                        }
                        cout << "\nPress Enter to continue...";
                        getch();
                        system("cls");
                        break;
                        
			             
			case 7:	    cout << "\nPress Enter to exit...";
			            getch();
                        exit(0);
			
			default:	cout << "\nINVALID CHOICE!";
			            cout << "\nPress Enter to continue...";
			            getch();
			            system("cls");
						break;
	    }
	}while(ch!='7');

	return 0;
}

void Student::getdata()
{
    cout << "\nEnter the Admission No.: ";
	cin >> admno;
	cout << "Enter the Roll No.: ";
	cin >> rollno;
	cout << "Enter the Name: ";
	cin.ignore( 1000, '\n' );
    gets(name);
	cout << "Enter the Address: ";
	gets(add);
	cout << "Enter the date of birth: ";
	cin >> dob.date;
	cout << "Enter the month of birth: ";
	cin >> dob.month;
	cout << "Enter the year of birth: ";
	cin >> dob.year;
}

void Student::updatedata(int n)
{
    char c;
    
    fstream file;
	file.open ("student.dat", ios::in | ios::binary | ios::out | ios::ate);
	
    if (!file)
	{
		cout << "File could not be opened !!";
		cin.ignore();
		return;
	}
	
	cout << "\nAre you sure you want to edit the student record (y/n): ";
    cin >> c;

    if(c != 'y')
        return;
    
    bool flag = false;
	
    file.seekg(0);          //moves the file pointer to the beginning of the file
    
    while (file.read ((char*) &s, sizeof(s)))
	{
        if (admno == n)        //compares the input by user with the admission number
		{ 
            flag = true; 
		    int num;		    
		    char choice = 'y';
		    
		    while (choice == 'y' || choice == 'Y')
		    {
		        cout << "\n\t1. UPDATE ROLL NO.\n\t2. UPDATE NAME\n\t3. UPDATE ADDRESS\n\t4. UPDATE DOB";
		        cout << "\n\nEnter the record to be edited: ";
		        cin >> num;
		        cout << endl;
		        switch (num)
		        {
		            case 1:   cout << "Enter the new roll no.: ";
		                      cin >> rollno;
		                      break;
		                  
		            case 2:   cout << "Enter the new name: ";
		                      cin.ignore( 1000, '\n' );
                              gets(name);
                              break;
                          
                    case 3:   cout << "Enter the new address: ";
                              cin.ignore( 1000, '\n' );
                              gets(add);
                              break;
                          
                    case 4:   cout << "Enter the new date of birth: ";
                              cin >> dob.date;
	                          cout << "Enter the new month of birth: ";
	                          cin >> dob.month;
	                          cout << "Enter the new year of birth: ";
	                          cin >> dob.year;
	                          break;
		            
		            default:  cout << "INVALID CHOICE!";
		                      break;
                }
            
		        file.seekp (file.tellp() - sizeof(s));        //to move the file pointer to the required position 
		        file.write ((char*)&s, sizeof(s));            //to write to 'file'
		    
			    cout << "\nDo you want to edit any other data: ";
			    cin >> choice;
	        }
        }    
	}
	
	if (flag == false)             //if no admission number matches with the user input
	{
	    cout << "\nRecord does not exist!";
	    return;
    }
    
    cout << "\nThe student record has been edited successfully." << endl;
    
    file.close();
    
    cin.ignore();
}

void Student::display()
{
	std::cout << std::right << std::setw(5) << admno << std::right << std::setw(17) << rollno << std::right << std::setw(30) << name << std::right << std::setw(22) << add << std::setw(15);
	cout << dob.date << "/" << dob.month << "/" << dob.year << endl;
}

void write_student()
{
	char ch = 'y';
	
	while (ch == 'y' || ch == 'Y')
	{
        Student st;
        
	    ofstream outFile;
    	outFile.open ("student.dat", ios::binary|ios::app);
    	
	    st.getdata();
        outFile.write ((char*)&st, sizeof(st));
	    outFile.close();
        
        cout << "\nStudent record has been created successfully.";
        cin.ignore();
        cout << "\n\nDo you want to enter more records? (y/n): ";
        cin >> ch;
    }
	
    cin.ignore();
}

void display_all()
{
	Student st;
	ifstream inFile;
	inFile.open ("student.dat", ios::binary);
	
    if (!inFile)
	{
		cout << "\nFile could not be opened!!";
		cin.ignore();
		return;
	}
	
	cout << "\n\n\t\tALL STUDENT RECORDS\n\n";
	cout << "===========================================================================================================\n";
	cout << "Adm.No.\t\tRollNo.\t\t\tName\t\t\t  Add.\t\t\tD.O.B" << endl;
	cout << "===========================================================================================================\n";
	while (inFile.read ((char*)&st, sizeof(st)))
	{
		st.display();
	}
	
	inFile.close();
	cin.ignore();
}

void display_sp(int n)
{
	Student st;
	ifstream inFile;
	inFile.open ("student.dat",ios::binary);
	
    if (!inFile)
	{
		cout<<"\nFile could not be opened!!";
		cin.ignore();
		return;
	}
	
	bool flag = false;
	
	while (inFile.read ((char*)&st, sizeof(st)))
	{
		if (st.getno() == n)
		{
			cout << "\n===========================================================================================================\n";
	        cout << "Adm.No.\t\tRollNo.\t\t\t\tName\t\t\tAdd.\t\tD.O.B" << endl;
	        cout << "===========================================================================================================\n";
	        st.display();
			flag = true;
		}
	}
	
	inFile.close();
	
    if (flag == false)
		cout << "\nRecord does not exist!";
	
    cin.ignore();
}


void delete_record(int n)
{
    char c;
	
    Student st;
	
    ifstream inFile;
	inFile.open ("student.dat", ios::binary);
	
    ofstream temp;
	temp.open ("temp.dat", ios::out|ios::binary);
	
    if (!inFile)
	{
		cout << "\nFile could not be opened !!";
		cin.ignore();
		return;
	}
	
	cout << "\nAre you sure you want to delete the student record (y/n): ";
    cin >> c;

    if(c != 'y')
        return;
        
    bool flag = false;
	
    while (inFile.read ((char*) &st, sizeof(st)))
	{	        
		if (st.getno() != n)
		{  
			temp.write ((char*)&st, sizeof(st));
	    }
	    
	    else 
	       flag = true;
	}
	
	if (flag == false)
	{
	    cout << "\nRecord does not exist!";
	    return;
    }
    
    cout << "\nThe student record has been deleted successfully." << endl;
    
    inFile.close();
    temp.close();
    
    remove("student.dat");
    rename("temp.dat", "student.dat");
    
    cin.ignore();
}
