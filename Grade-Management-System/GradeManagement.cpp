#include <ios>
#include <iostream>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;
    
const int MAX_STUDENTS = 30;
const int MAX_GRADES = 5;

int readInt(const string& prompt, int minValue, int maxValue){
    int value;
    while(true){
        cout << prompt;
        if (cin >> value && value >= minValue && value <= maxValue){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Enter a whole number from "<<maxValue<< " to " <<maxValue << "\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');

    }
}

double readGrades(const string& prompt){
    double value; 
        while(true){
            cout << prompt;
            if(cin>> value && value >=0.0 && value <= 100.0){
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                return value;

            }cout << "Invalid grade. Enter a number from 0-100.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');

        }
}

class Student {
    private:
        string name;
        double grades[MAX_GRADES];
        int gradeCount;

    public:

        Student(){
            name= "";
            gradeCount = 0;
        }

        void setName(const string& newName){
            name = newName;
        }

        string getName()const{
            return name;
        }

        bool addGrade(double grade){
            if(gradeCount >= MAX_GRADES || grade <0 || grade >100){
                return false;
            }
            grades[gradeCount]=grade;
            gradeCount++;
            return true;
        }

        double getAverage()const{
            if(gradeCount == 0){
                return 0.0;
            }
            double total=0;
            for (int i=0; i<gradeCount; i++){
                total += grades[i];

            }
            return total/gradeCount;

        }

        char getLetterGrade()const{
            if (gradeCount==0)
                return '-';
            double average = getAverage();
            if(average >= 90)
                return 'A';
            if (average >= 80)
                return 'B';
            if (average >= 70)
                return 'C';
            if (average >= 60)
                return 'D';
            return 'F';
        }

        void display()const{
            cout << "Name: " << name << "\n Grades: ";
                if (gradeCount==0){
                    cout << "None";
                }
                else{
                    for (int i=0; i <gradeCount; i++){
                        cout<< grades[i];
                        if(i<gradeCount -1) cout << ", : ";
                    }
                }
                cout<< "\n";
                if (gradeCount==0){
                    cout << "Average: N/A | Letter: N/A\n";
                }else{
                    cout << fixed << setprecision(2)<< "Average: "<< getAverage() << "Letter: " << getLetterGrade() << "\n";
                    
                }
        }

};

class GradeBook{
    private:
        Student students[MAX_STUDENTS];
        int studentCount;
        int findStudent(const string& name)const{
            for (int i=0; i<studentCount; i++){
                if(students[i].getName()==name)return i;
            }
            return -1;
        }

    public: 
        GradeBook(){
            studentCount=0;

        }
        
        void addStudent(){
            if(studentCount >= MAX_STUDENTS){
                cout << "The grade book is full.\n";
                return;
            }
            string name;
            cout << "Enter the students name: ";
            getline(cin,name);
            if (name.empty()){
                cout  << "Students name can not be empty.\n";
                return;
            }
            if(findStudent(name) !=-1){
                cout << "student with that name already exists,\n";
                return;
            }

            students[studentCount].setName(name);
            studentCount ++;
            cout << "Student added\n";
        }

        void addGradeToStudent(){
            string name;
            cout << "Enter students name: ";
            getline(cin, name);
            int index= findStudent(name);
            if (index == -1){
                cout << "Student not found.\n";
                return;
            }

            double grade =readGrades("Enter grade(0-100): ");
            if (students[index].addGrade(grade)){
                cout << "grade added.\n";
            }else{
                cout << "This student alreadyn has 5 grades.\n";

            }

        }

        void showAllStudents()const{
            if(studentCount==0){
                cout << "No students added yet,\n";
                return;
            }
            for(int i=0;i<studentCount; i++){
                cout <<"\n --- Student " << (i+1) << " ---\n";
                students[i].display();
            }
        }

        void searchStudent() const {
            string name;
            cout << "Enter student name: ";
            getline(cin, name);
            int index = findStudent(name);
            if(index == -1){
                cout << "Student not found.\n";

            }
            else{
                students[index].display();
            }
        }
        
        void showClassAverage() const {
            double total = 0.0;
            int withGrades = 0;
            for (int i =0 ; i<studentCount; i++){
                if(students[i].getLetterGrade() != '-'){
                    total += students[i].getAverage();
                    withGrades++;
                }
            }
            if (withGrades==0){
                cout << "No grades are available for a class average.\n";

            }else{
                cout << fixed << setprecision(2) << "Class Average: " << total/withGrades << "\n";
            }
        }


};

int main(){

    GradeBook book;
    int choice;

    do{
        cout << "\n ======GRADE MANAGEMENT SYSTEM ======\n"
             << "1. Add student\n"
             << "2. Display grade to student\n"
             << "3. Display all students\n"
             << "4. Search for student\n"
             << "5. Show class average\n"
             << "6. Exit\n";
        choice = readInt("Choose an option (1-6): ",1,6);

        switch (choice){
            case 1: book.addStudent(); break;
            case 2: book.addGradeToStudent(); break;
            case 3: book.showAllStudents(); break;
            case 4: book.searchStudent(); break;
            case 5: book.showClassAverage(); break;
            case 6: cout << "Goodbye!!\n"; break;
        }

    }while(choice !=6);



    return 0;
}

