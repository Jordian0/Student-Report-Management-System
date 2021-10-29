#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;


// Class that stores data
class Student {
private:
	int rollno;
	char name[50];
	int eng_marks, math_marks, sci_marks, lang2_marks, cs_marks;
	double average;
	char grade;

public:
	void getdata();
	void showdata() const;
	void calculate();
	int retrollno() const;
};


void Student::calculate(){
	average = (eng_marks + math_marks + sci_marks + lang2_marks + cs_marks) / 5.0;
	if(average >= 90)
		grade = 'A';
	else if(average >= 75)
		grade = 'B';
	else if(average >= 50)
		grade = 'C';
	else
		grade = 'F';
}


void Student::getdata() {
	cout << "\nEnter student's roll number: " << flush;
	cin >> rollno;

	cout << "\n\nEnter student's name: " << flush;
	cin.ignore();
	cin.getline(name, 50);

	cout << "\nAll marks should be out of 100" << endl;
	cout << "Enter marks in English: " << flush;
	cin >> eng_marks;
	cout << "\nEnter marks in Math: " << flush;
	cin >> math_marks;
	cout << "\nEnter marks in Science: " << flush;
	cin >> sci_marks;
	cout << "\nEnter marks is 2nd language: " << flush;
	cin >> lang2_marks;
	cout << "\nEnter marks in Computer Science: " << flush;
	cin >> cs_marks;
	cout << endl;

	calculate();
}


void Student::showdata() const {
	cout << "\nRoll number of student : " << rollno << endl;
	cout << "Name of student : " << name << endl;
	cout << "English : " << eng_marks << endl;
	cout << "Maths : " << math_marks << endl;
	cout << "Science : " << sci_marks << endl;
	cout << "Language2 : " << lang2_marks << endl;
	cout << "Computer Science : " << cs_marks << endl;
	cout << "Average Marks : " << average;
	cout << "Grade of student is: " << grade << endl;
}


int Student::retrollno() const {
	return rollno;
}


// Function declaration
void create_student();  // creates student
void display_sp(int);  // display particular record
void display_all();   // display all records
void delete_student(int);  // delete particular record
void change_student(int);  // edit particular record


// Main
int main() {
	char ch;
	cout << setprecision(2);

	do {
		char ch;
		int num;
		system("cls");
		cout << "\n\tMENU" << endl;
		cout << "\t1. Create student record" << endl;
		cout << "\t2. Search student record" << endl;
		cout << "\t3. Display all students records: " << endl;
		cout << "\t4. Delete student record" << endl;
		cout << "\t5. Modify student record" << endl;
		cout << "\t6. Exit" << endl;
		cout << "What is your choice (1/2/3/4/5/6):  ";
		cin >> ch;
		system("cls");

		switch(ch) {
		case '1':
			create_student();
			break;
		case '2':
			cout << "Enter the roll number: " << flush;
			cin >> num;
			cout << endl;
			display_sp(num);
			break;
		case '3':
			display_all();
			break;
		case '4':
			cout << "Enter the roll number: " << flush;
			cin >> num;
			cout << endl;
			delete_student(num);
			break;
		case '5':
			cout << "Enter the roll number: " << flush;
			cin >> num;
			cout << endl;
			change_student(num);
			break;
		case '6':
			cout << "Exiting, Thank you!" << endl;
			exit(0);
		}
	} while(ch != '6');

	return 0;
}





// Write student details to file
void create_student() {
	Student stud;
	ofstream oFile;
	oFile.open("student.dat", ios::binary|ios::app);
	stud.getdata();
	oFile.write(reinterpret_cast<char *> (&stud), sizeof(Student));
	oFile.close();
	cout << "\nStudent record has been created. " << endl;
	cin.ignore();
	cin.get();
}


// Read file records
void display_all() {
	Student stud;
	ifstream inFile;
	inFile.open("student.dat", ios::binary);

	if(!inFile) {
		cout << "File could not be opened !! Press any key to exit" << endl;
		cin.ignore();
		cin.get();
		return;
	}
	cout << "\nDISPLAYING ALL RECORDS\n" << endl;

	while(inFile.read(reinterpret_cast<char *> (&stud), sizeof(Student))) {
		stud.showdata();
		cout << "\n===================================================" << endl;
	}
	inFile.close();
	cin.ignore();
	cin.get();
}


// Read specific record based on roll number
void display_sp(int n) {
	Student stud;
	ifstream iFile;
	iFile.open("student.dat", ios::binary);

	if(!iFile) {
		cout << "File could not be opened... Press any key to exit" << endl;
		cin.ignore();
		cin.get();
		return;
	}

	bool flag = false;
	while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(Student))) {
		if(stud.retrollno() == n) {
			stud.showdata();
			flag = true;
		}
	}

	iFile.close();
	if(flag == false)
		cout << "\n Record does not exist" << endl;
	cin.ignore();
	cin.get();
}


// Modify record for specified roll number
void change_student(int n) {
	bool found = false;
	Student stud;
	fstream fl;
	fl.open("student.dat", ios::binary|ios::in|ios::out);

	if(!fl) {
		cout << "File could not be opened. Press any key to exit... " << endl;
		cin.ignore();
		cin.get();
		return;
	}

	while(!fl.eof() && found == false) {
		fl.read(reinterpret_cast<char *> (&stud), sizeof(Student));

		if(stud.retrollno() == n) {
			stud.showdata();
			cout << "Enter new student details: " << endl;
			stud.getdata();
			int pos = (-1) * static_cast<int>(sizeof(stud));
			fl.seekp(pos, ios::cur);
			fl.write(reinterpret_cast<char *> (&stud), sizeof(Student));
			cout << "\nRecord Updated" << endl;
			found = true;
		}
	}

	fl.close();
	if(found == false)
		cout << "\nRecord Not Found" << endl;
	cin.ignore();
	cin.get();
}


// delete record with particular roll number
void delete_student(int n) {
	Student stud;
	ifstream iFile;
	iFile.open("student.dat", ios::binary);

	if(!iFile) {
		cout << "File could not be opened... Press any key to exit... " << endl;
		cin.ignore();
		cin.get();
		return;
	}

	ofstream oFile;
	oFile.open("Temp.dot", ios::out);
	iFile.seekg(0, ios::beg);

	while(iFile.read(reinterpret_cast<char *> (&stud), sizeof(Student))) {
		if(stud.retrollno() != n) {
			oFile.write(reinterpret_cast<char *> (&stud), sizeof(Student));
		}
	}

	oFile.close();
	iFile.close();

	remove("student.dat");
	rename("Temp.dat", "student.dat");
	cout << "\nRecord Deleted...." << endl;
	cin.ignore();
	cin.get();
}
