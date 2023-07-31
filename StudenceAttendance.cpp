#include <iostream>
#include <string>
#include <string.h>
#include <cstring>
#include <istream>
#include <fstream> // THIS HEADER FILE HELPS US TO STORE OUR DATA PERMANENTLLY.
#include <vector> //  A VECTOR IS NOTHIG BUT AN ARRAY WHICH CAN BE DYNAMICALLY RESIZED.

using namespace std;
vector<string> fName_v,lName_v,id_v,gender_v,date_v,status_v; //We Use The "_v" Extension To Imply It Is A Vector Value.
vector<char> attendanceStatus;
struct students{
  string firstName,lastName,id,gender;
} stud[20];
void appendStudents();
void adminLogIn();
void adminView();
void markAttendance();
int  deleteStudent();
void clearData();
void registerStudent();
void checkListOfRegistredStudent();
void checkPresence();
void studentLogIn();
void announceClassDays();
void seeClassSchedual(int);
void prepareAttendance(int);
void updateSchedual(int);
void registeredCourses();
int goBack(int to = 1);
int setting();
void delay();
void delay2();
void developersInfo();

// Main Function
int main(){
  int choice;
  appendStudents();
  system("cls");
  cout<<"\t\t\tWELCOME TO STUDENT ATTENDANCE MANAGEMENT SYSTEM\n\n";
  cout<<"1 ADMIN LOGIN\n";
  cout<<"2 STUDENT LOGIN\n";
  cout<<"3 DEVELOPERS INFO\n";
  cout<<"0 EXIT\n";
  retry:
  cout<<"\nENTER CHOICE: ";
  cin>>choice;
  switch(choice){
    case 1: adminLogIn();break;
    case 2: studentLogIn();break;
    case 3: developersInfo();break;
    case 0: break;
    default: cout<<"\nInvalid Input!!!";goto retry;break;
  }
  return 0;
}

// HERE,THE |appendStudents()| FUNCTION READS DATA FROM THE FILE IN THE COMPUTER AND PREPARE FOR THE UPCOMING PROCESS.
void appendStudents(){
  delay();
  fName_v = {}; lName_v = {},gender_v = {};id_v = {};
  fstream file1("firstName.txt");
  fstream file2("lastName.txt");
  fstream file3("id.txt");
  fstream file4("gender.txt");
  if((!file1.good()) || (!file2.good()) || (!file3.good()) || (!file4.good())){
    file1.open("firstName.txt",ios::out);
    file2.open("lastName.txt",ios::out);
    file3.open("id.txt",ios::out);
    file4.open("gender.txt",ios::out);

    file1<<"FIRST_NAME";file2<<"LAST_NAME";file3<<"ID";file4<<"SEX";
    file1.close();file2.close();file3.close();file4.close();
  }

  fstream Myfile1,Myfile2,Myfile3,Myfile4;
  Myfile1.open("firstName.txt",ios::in);
  Myfile2.open("lastName.txt",ios::in);
  Myfile3.open("id.txt",ios::in);
  Myfile4.open("gender.txt",ios::in);
  if(Myfile1.is_open() && Myfile2.is_open() && Myfile3.is_open() && Myfile4.is_open()){
    string f_name,l_name,id,gender;
    while(getline(Myfile1,f_name) && getline(Myfile2,l_name) && getline(Myfile3,id) && getline(Myfile4,gender)){
      fName_v.push_back(f_name);
      lName_v.push_back(l_name);
      gender_v.push_back(gender);
      id_v.push_back(id);
    }
    Myfile1.close();Myfile2.close();Myfile3.close();Myfile4.close();
  }else{
    cout<<"\nERROR: OPENING FILE FAILD WHIEL APPENDING STUDENT!\n";
  }
}

// ADMIN COULD BE ANY PERSON, CLASS REP OR LECTURE(PROFESSOR) WHO HAVE AUTHORIZED ACCESS TO MANIPULATE THE DATA.
void adminLogIn(){
  system("cls");
  string adminPassWord, systemDeafaultPassWord ="1234";
  fstream file1("password.txt");
  if(!file1.good()){
    file1.open("password.txt",ios :: out);
    file1<<systemDeafaultPassWord;
    file1.close();
  }
  fstream file;
  file.open("password.txt",ios::in);
  if(file.is_open()){
    while(getline(file,adminPassWord));
    file.close();
  }else{
    cout<<"\nERROR: OPENING PASSWORD FILE!\n";exit(0);
  }
  int attemptCount = 0;
  tryAgain:
  string password;
  cout<<"ENTER PASSWORD:";
  cin>>password;
  if(password == adminPassWord){
    adminView();
  }else{
    if(attemptCount == 2){
      delay();
      cout<<"\n\t\t------- || ACCESS DENIED || ----------!\n\n";
      exit(0);
    }else{
      ++attemptCount;
    }
    delay();
    cout<<"\n\t\tWRONG PASSWORD!"<<endl;goto tryAgain;
  }
}

// HERE ADMIN CAN MAKE REGISTRATION,ATTENDANCE MARKING, DELETING STUDENT AND SO ON.
void adminView(){
  appendStudents();
  system("cls");
    cout<<"--------------------------------------- ||     WELCOME TO ADMIN VIEW     || -------------------------------------------\n\n";
    int choice;
    cout<<"1 REGISTRATION\n";
    cout<<"2 STUDENT PROFILE\n";
    cout<<"3 CHECK STUDENT PROFILE BY ID\n";
    cout<<"4 MARK ATTENDANCE\n";
    cout<<"5 MANAGE CLASS SCHEDUAL\n";
    cout<<"6 DELETE STUDENT\n";
    cout<<"7 CLEAR DATA\n"; // MAKES ALL THE DATA EMPTY AND AVAILABLE FOR NEW PROCESS.
    cout<<"8 SETTING\n";
    cout<<"0 BACK\n";
    retry:
    cout<<"\nENTER CHOICE: ";
    cin>>choice;
    switch(choice){
      case 1: registerStudent();break;
      case 2: checkListOfRegistredStudent();break;
      case 3: checkPresence();break;
      case 4: markAttendance();break;
      case 5: announceClassDays();break;
      case 6: deleteStudent();break;
      case 7: clearData();break;
      case 8: setting();break;
      case 0: main();break;
      default: cout<<"\nInvalid Input!!!";goto retry;break;
    }
}

// ONCE THE STUDENT IS REGISTERD IN THE DATABASE HE/SHE CAN ACCESS THE STUDENT LOG IN FUNCTION.
void studentLogIn(){
  appendStudents();
  system("cls");
  if(fName_v.size() == 1){
    cout<<"\nSTUDENTS ARE NOT REGISTERED YET!\n";
    goBack(2);exit(0);
  }

  string userId;
  cout<<"\nID: ";
  cin.ignore();
  getline(cin,userId);

          // First Check Whether The Student Is Registered Or Not Before Going To Another Process.
  for(int i = 0; i < id_v.size(); ++i){
    if(userId == id_v[i]){
      delay();
      system("cls");
      cout<<"\t\t\t"<<fName_v[i]<<" "<<lName_v[i]<<"\n\n";
      break;
    }else if(i == (id_v.size()-1) && userId != id_v[i]){
      delay();
      cout<<"\nERROR: STUDENT NOT FOUND!\n";goBack(2);exit(1);
    }else{
      continue;
    }
  }

  // If The Student Is Already Register, Then He Can Accesses |studentLogIn()| Function Here.
  cout<<"\n1 PROFILE";
  cout<<"\n2 SEE CLASS SCHEDUAL";
  cout<<"\n0 Back"<<endl;

  logInAgain:
  int choice;
  cout<<"\nEnter: ";
  cin>>choice;
  switch(choice){
    case 0: main();break;
    case 1: delay();
            system("cls");
            for(int i = 0; i < id_v.size(); ++i){
              if(id_v[i] != userId){
                continue;
              }else{
                cout<<"\t\t\tPROFILE\n\n\n";
                cout<<"\t\t"<<fName_v[0]<<"  :  "<<fName_v[i]<<endl;
                cout<<"\t\t"<<lName_v[0]<<"  :  "<<lName_v[i]<<endl;
                cout<<"\t\t"<<gender_v[0]<<"  :  "<<gender_v[i]<<endl;
                cout<<"\t\t"<<id_v[0]<<"  :  "<<id_v[i]<<endl;
                break;
              }
            }break;
    case 2: delay();
            system("cls");
            registeredCourses();
            pleaseTryAgain:
            int courseChoice;
            cout<<"\n\nEnter Choice: ";
            cin>>courseChoice;
            switch(courseChoice){
              case 1:seeClassSchedual(1);break;
              case 2:seeClassSchedual(2);break;
              case 3:seeClassSchedual(3);break;
              case 4:seeClassSchedual(4);break;
              case 5:seeClassSchedual(5);break;
              case 0:main();break;
              default: goto pleaseTryAgain;break;
            }break;
    default: cout<<"\n\t\tINVALID INPUT\n";goto logInAgain;
  }
  cout<<"\n\n";
  goBack(2);
  exit(0);
}

// STUDENT(S) REGISTRATION GOES HERE.
void registerStudent(){
  delay();
  system("cls");
  cout<<"\t\t\tREGISTRATION FORM\n\n";
  int n;
  cout<<"HOW MANY STUDENTS TO REGISTER?: ";
  cin>>n;
  fstream Myfile1,Myfile2,Myfile3,Myfile4;
  Myfile1.open("firstName.txt",ios::app);
  Myfile2.open("lastName.txt",ios::app);
  Myfile3.open("id.txt",ios::app);
  Myfile4.open("gender.txt",ios::app);
  if(Myfile1.is_open() && Myfile2.is_open() && Myfile3.is_open() && Myfile4.is_open()){
    for(int i = 0; i < n; ++i){
    cout<<"STUDENT"<<i+1<<" : "<<endl;
    cout<<"FIRST_NAME: ";
    cin>>stud[i].firstName;
    cout<<"LAST_NAME: ";
    cin>>stud[i].lastName;
    cout<<"SEX: ";
    cin>>stud[i].gender;

    checkId:                    // IT CKECKS IF THE ID IS ALREADY IN USE OR NOT WHILE REGISTERING NEW STUDENTS.
    cout<<"ID: ";
    cin>>stud[i].id;
    for(const string &b: id_v){
      if(stud[i].id == b){
        cout<<"\nID ALREADY EXISTS!.\n";goto checkId;
      }
    }
    Myfile1<<endl<<stud[i].firstName;
    Myfile2<<endl<<stud[i].lastName;
    Myfile3<<endl<<stud[i].id;
    Myfile4<<endl<<stud[i].gender;
    }
    Myfile1.close();Myfile2.close();Myfile3.close();Myfile4.close();
    appendStudents();
    cout<<"\n\nREGISTRATION FINISHED SUCCESSFULY!!"<<endl; // REGISTRATION ENDS.
  }else{
    cout<<"\nERROR: OPENING FILE FAILED!"<<endl;
  }
  cout<<"\n\n\n";
  goBack();
  exit(1);
};

// HERE THE ADMIN CAN SEE ALL THE REGISTERD STUDENTS.
void checkListOfRegistredStudent(){
  appendStudents();
  system("cls");
  cout<<"\t\t\tREGISTERED STUDENTS LIST"<<endl<<endl;
  if(fName_v.size() == 1){
      cout<<"\n\t\t\t --------------";
      cout<<"\n\t\t\t|              |";
      cout<<"\n\t\t\t|  EMPTY FILE  |";
      cout<<"\n\t\t\t|              |";
      cout<<"\n\t\t\t --------------"<<endl;
  }else{
    cout<<"1 ALPHABETIZED\n";
    cout<<"2 All LIST\n";
    cout<<"3 BACK\n";
    int choice;
    retry:
    cout<<"\n\nENTER CHOICE: ";
    cin>>choice;
    if(choice==1){
      delay();
      system("cls");
      cout<<"\t\t\tREGISTERED STUDENTS LIST"<<endl<<endl;
      char letter;
      cout<<"\n\nALPHABET: ";
      cin>>letter;
      char convertToUpperCase = static_cast<char>(toupper(letter));
      delay();
      system("cls");
      cout<<"\t\t\tALPHABET: "<<letter<<endl<<endl;
      for(int i = 0; i < fName_v.size(); ++i){
        for(int j = 0; j < fName_v[i].size(); ++j){
          if((fName_v[j][0] == letter || fName_v[j][0] == convertToUpperCase || static_cast<char>(toupper(fName_v[j][0])) == letter) && j!=0){
            break;
          }else if(j == (fName_v.size() - 1) && letter != fName_v[j][0]){
            cout<<"\nNO STUDENT FOUND!"<<endl;goBack();exit(1);
          }
        }
        if(i == 0){
          cout<<fName_v[i]<<"\t"<<lName_v[i]<<"\t"<<id_v[i]<<"\t"<<gender_v[i]<<endl;
        }else if((fName_v[i][0] == letter) || (fName_v[i][0] == convertToUpperCase) || (static_cast<char>(toupper(fName_v[i][0])) == letter)){
          cout<<fName_v[i]<<"\t\t"<<lName_v[i]<<"\t\t"<<id_v[i]<<"\t\t"<<gender_v[i]<<endl;
        }
      }
    }else if(choice == 2){
      delay();
      system("cls");
      cout<<"\t\t\tALL REGISTERED STUDENTS LIST"<<endl<<endl;
      for(int i = 0; i < fName_v.size(); ++i){
        if(i == 0){
          cout<<fName_v[i]<<"\t"<<lName_v[i]<<"\t"<<id_v[i]<<"\t"<<gender_v[i]<<endl;
        }else{
          cout<<fName_v[i]<<"\t\t"<<lName_v[i]<<"\t\t"<<id_v[i]<<"\t\t"<<gender_v[i]<<endl;
        }
      }
    }else if(choice == 3){
     adminView();exit(0);
    }else{
      cout<<"\nINVALID INPUT!\n";goto retry;
    }
  }
  cout<<"\n\n\n";
  goBack();
  exit(0);
}

// IF THE ADMIN WANTS TO CHECK WHETHER THE STUDENT IS REGISTERD OR NOT, HE COMES HERE AND TYPES ITS ID.
void checkPresence(){
  delay();
  system("cls");
  string id;
  cout<<"\t\t\tSEARCH FOR STUDENT PROFILE\n\n";
  cout<<"ID: ";
  cin.ignore();getline(cin,id);
  delay();
  system("cls");
  for(int i = 0; i < id_v.size(); ++i){
    if(i == (id_v.size()-1) && (id_v[i] != id)){
      cout<<"\nSTUDENT HAS NOT BEEN REGISTERED YET!";
    }else if(id_v[i] != id){
      continue;
    }else{
      cout<<fName_v[0]<<"\t"<<lName_v[0]<<"\t"<<gender_v[0]<<"\t"<<id_v[0]<<endl;
      cout<<fName_v[i]<<"\t\t"<<lName_v[i]<<"\t\t"<<gender_v[i]<<"\t\t"<<id_v[i]<<endl;
      break;
    }
  }
  cout<<"\n\n\n";
  goBack();
  exit(0);
}

// THIS FUNCTION DELETE THE STUDENT FROM THE FILE IF THE STUDENT IS ALREADY REGISTERD.
int deleteStudent(){
  delay();
  system("cls");
  cout<<"\t\t\tDELETE\n\n";
  if(fName_v.size() == 1){
    cout<<"\nTHERE IS NO STUDENT RECORD YET!"<<endl;
    cout<<"\n\n\n";
  }else{
    string id;
    cout<<"ID: ";
    cin.ignore();getline(cin,id);
    for(int i = 0; i < fName_v.size(); i++){
        if(i == (id_v.size()-1) && id_v[i] != id){ // Checking the last id.
          delay();
          system("cls");
          cout<<"\nERROR : STUDENT  NOT FOUND!\n";
          cout<<"\n\n\n";
          break;
        }else if(id_v[i] == id){
        delay();
        cout<<"\n"<<fName_v[i]<<" "<<lName_v[i]<<" DELETED SUCCESSFULLY!"<<endl;
        fName_v.erase(fName_v.begin()+i);
        lName_v.erase(lName_v.begin()+i);
        id_v.erase(id_v.begin()+i);
        gender_v.erase(gender_v.begin()+i);
    // Removing the First line of the list
        fName_v.erase(fName_v.begin()+0);
        lName_v.erase(lName_v.begin()+0);
        id_v.erase(id_v.begin()+0);
        gender_v.erase(gender_v.begin()+0);
    // Writting the first line of the list
        fstream Myfile1,Myfile2,Myfile3,Myfile4;
        Myfile1.open("firstName.txt",ios::out);
        Myfile2.open("lastName.txt",ios::out);
        Myfile3.open("id.txt",ios::out);
        Myfile4.open("gender.txt",ios::out);
        if(Myfile1.is_open() && Myfile2.is_open() && Myfile3.is_open() && Myfile4.is_open()){
          Myfile1<<"FIRST_NAME";Myfile2<<"LAST_NAME";Myfile3<<"ID";Myfile4<<"SEX";
          Myfile1.close();Myfile2.close();Myfile3.close();Myfile4.close();
        }else{
          cout<<"\nERROR: OPENING FILE FAILED!"<<endl;
        }
    // Appending the new List
        Myfile1.open("firstName.txt",ios::app);
        Myfile2.open("lastName.txt",ios::app);
        Myfile3.open("id.txt",ios::app);
        Myfile4.open("gender.txt",ios::app);
        if(Myfile1.is_open() && Myfile2.is_open() && Myfile3.is_open() && Myfile4.is_open()){
          for(int i = 0; i < fName_v.size(); i++){
            Myfile1<<endl<<fName_v[i];
            Myfile2<<endl<<lName_v[i];
            Myfile3<<endl<<id_v[i];
            Myfile4<<endl<<gender_v[i];
          }
          Myfile1.close();Myfile2.close();Myfile3.close();Myfile4.close();
          appendStudents();
          break;
        }else{
          cout<<"\nERROR: OPENING FILE FAILED!"<<endl;
        }
        break;
      }
    }
  }
  cout<<"\n\n\n";
  goBack();
 return 0;
}

// CLEAR ALL THE DATA AND MAKE THE SYSTEM EMPTY FOR NEW PROCESS.
void clearData(){
  delay();
  system("cls");
  cout<<endl<<"\t\t\t ------------------  WARNING  -----------------------";
  cout<<endl<<"\t\t\t|                                                    |";
  cout<<endl<<"\t\t\t|THE FOLLOWING DATA WILL BE PERMANENTLT DELETED!     |";
  cout<<endl<<"\t\t\t|                                                    |";
  cout<<endl<<"\t\t\t|1.THE REGISTERED STUDENTS LIST.                     |";
  cout<<endl<<"\t\t\t|                                                    |";
  cout<<endl<<"\t\t\t|2.ALL COURSES SCHEDUAL.                             |";
  cout<<endl<<"\t\t\t|                                                    |";
  cout<<endl<<"\t\t\t|#THIS PROCESS CAN'T BE UNDO!                        |";
  cout<<endl<<"\t\t\t ----------------------------------------------------"<<endl;
  char choice;
  here:
  cout<<"\n\t\tARE YOUR SURE YOU WANT TO CLEAR ALL THE DATA? |y/Y| Or |n/N|: ";
  cin>>choice;
  fstream Myfile1,Myfile2,Myfile3,Myfile4,Myfile5,Myfile6,Myfile7,Myfile8,Myfile9;
  switch(choice){
      case 'Y':
      case 'y': Myfile1.open("firstName.txt",ios::out);Myfile2.open("lastName.txt",ios::out);Myfile3.open("id.txt",ios::out);
                Myfile4.open("gender.txt",ios::out);Myfile5.open("FUNDAMENTALS_OF_PROGRAMING_II.txt",ios::out); Myfile6.open("DATA_COMMUNICATION_AND_COMPUTER_NETWORKS.txt",ios::out);
                Myfile7.open("DATABASE_SYSTEM.txt",ios::out);Myfile8.open("DIGITAL_LOGIC_DESIGN.txt",ios::out);
                Myfile9.open("ECONOMICS.txt",ios::out);
                if(Myfile1.is_open() && Myfile2.is_open() && Myfile3.is_open() && Myfile4.is_open() && Myfile5.is_open() && Myfile6.is_open() && Myfile7.is_open() && Myfile8.is_open() && Myfile9.is_open()){
                  Myfile1<<"FIRST_NAME";Myfile2<<"LAST_NAME";Myfile3<<"ID";Myfile4<<"SECTION";
                  Myfile5<<"FUNDAMENTALS_OF_PROGRAMING_II";Myfile6<<"DATA_COMMUNICATION_AND_COMPUTER_NETWORKS";Myfile7<<"DATABASE_SYSTEM";Myfile8<<"DIGITAL_LOGIC_DESIGN";Myfile9<<"ECONOMICS";
                  Myfile1.close();Myfile2.close();Myfile3.close();Myfile4.close(); Myfile5.close();
                  Myfile6.close();Myfile7.close();Myfile8.close();Myfile9.close();
                  delay();
                  cout<<"\nDATA CLEARED SUCCESSFULLY!"<<endl;
                  cout<<"\n\n\n";
                  goBack();exit(0);
                  break;
                }else{
                  cout<<"ERROR: OPENING FILE FAILED!"<<endl;break;
                }
      case 'N':
      case 'n': adminView();break;
      default: cout<<"\nINVALID INPUT!\n";goto here;break;
    }
}

//THSI FUNCTION MARK STUDENTS ATTENDANCE.IT WORKS FOR MULTIPLE SECTIONS.
void markAttendance(){
  delay();
  system("cls");
  cout<<"\t\t\tATTENDANCE"<<endl<<endl;
  if(fName_v.size() == 1){
    cout<<"\n\t\t\t -------------------------------";
    cout<<"\n\t\t\t|                               |";
    cout<<"\n\t\t\t| REGISTER SOME STUDENTS FIRST  |";
    cout<<"\n\t\t\t|                               |";
    cout<<"\n\t\t\t -------------------------------"<<endl;
  }else{
      registeredCourses();
      enterCourseAgain:
      int courseChoice;
      cout<<"\n\nENTER CHOICE: ";
      cin>>courseChoice;
      switch(courseChoice){
        case 1:prepareAttendance(1); break;
        case 2:prepareAttendance(2);break;
        case 3:prepareAttendance(3);break;
        case 4:prepareAttendance(4);break;
        case 5:prepareAttendance(5);break;
        case 0:adminView();exit(0);break;
        default: goto enterCourseAgain;break;
      }
  }
  cout<<"\n\n\n";
  goBack();
}

void prepareAttendance(int couresCode){
  int choosenCourse = couresCode;
  string courseName;
  switch(choosenCourse){
    case 1: courseName = "FUNDAMENTALS_OF_PROGRAMING_II";break;
    case 2: courseName = "DATA_COMMUNICATION_AND_COMPUTER_NETWORKS";break;
    case 3: courseName = "DATABASE_SYSTEM";break;
    case 4: courseName = "DIGITAL_LOGIC_DESIGN";break;
    case 5: courseName = "ECONOMICS";break;
    default:break;
  }
  cout<<"\t\t"<<courseName<<endl;
  fstream file;
  file.open(courseName+".txt",ios::in);
  if(file.is_open()){
    delay();
    system("cls");
    cout<<"\t\t\t"<<courseName<<" CLASS DAYS\t\t||SELECT DAY||\n\n";
    string courseDate;
    while(getline(file,courseDate)){
      date_v.push_back(courseDate);
    }
    file.close();
  }else{
    cout<<"\nERROR: OPENING "<<courseName<<" FILE FAILD!";exit(1);
  }

  if(date_v.size() == 1){
    delay();
    cout<<"\n\t\t\t -------------------------------";
    cout<<"\n\t\t\t|                               |";
    cout<<"\n\t\t\t| PLEASE MAKE A SCHEDUAL FIRST  |";
    cout<<"\n\t\t\t|                               |";
    cout<<"\n\t\t\t -------------------------------"<<endl;
  }else{
    for(int i = 0; i < date_v.size(); ++i){
      if(i != 0){
        cout<<i<<" "<<date_v[i]<<endl;
      }
    }
    int chooseCourseDate;
    cout<<"ENTER CHOICE: ";
    cin>>chooseCourseDate;
    for(int i = 0; i < date_v.size(); ++i){
      if(chooseCourseDate == i && i!=0){
        attendanceStatus = {'s'};
        delay();
        system("cls");
        cout<<"\n\t\t\tMARK ATTENDACE\n";
        cout<<"\nCOURSE: "<<courseName<<"\t\t\tDATE: "<<date_v[i]<<endl;
        for(int j = 0; j < fName_v.size(); ++j){
          if(j!=0){
            char tick;
            cout<<"\nIS "<<fName_v[j]<<" "<<lName_v[j]<<" PRESENT? (y/n): ";
            cin>>tick;
            attendanceStatus.push_back(tick);
          }
        }
        delay();
        system("cls");
        cout<<"\n\n"<<courseName<<" ATTENDANCE ON :  "<<date_v[i]<<endl;
        for(int k = 0; k < fName_v.size(); ++k){
          if(k!=0){
            cout<<"\n"<<fName_v[k]<<" "<<lName_v[k]<<" Is "<<(attendanceStatus[k] == 'y'? "PRESENT" : "ABSENT")<<".";
          }
        }
        break;
      }
    }
  }
}
// HERE ADMIN ANNOUNCES THE DAY FOR THE COURSES.
void announceClassDays(){
  // delay();
  system("cls");
  cout<<"\t\t\tCLASS DAYS"<<endl<<endl;
  cout<<"1 SEE AVAILABLE CLASS DAYS\n";
  cout<<"2 MAKE CLASS SCHEDUAL\n";
  cout<<"3 BACK\n";
  int choice;
  cout<<"\nENTER CHOICE: ";
  cin>>choice;
  if(choice == 1){
    delay();
    system("cls");
    registeredCourses();
    enterAgain:
    int courseChoice;
    cout<<"\n\nENTER CHOICE: ";
    cin>>courseChoice;
    switch(courseChoice){
      case 1:seeClassSchedual(1);break;
      case 2:seeClassSchedual(2);break;
      case 3:seeClassSchedual(3);break;
      case 4:seeClassSchedual(4);break;
      case 5:seeClassSchedual(5);break;
      case 0:seeClassSchedual(0);break;
      default: goto enterAgain;break;
    }
  }else if(choice == 2){
    delay();
    system("cls");
    cout<<"\n\t\t\tMAKE SCHEDUAL\n";
    registeredCourses();
    TryAgain:
    int courseChoice2;
    cout<<"\n\nENTER CHOICE: ";
    cin>>courseChoice2;
    switch(courseChoice2){
      case 1:updateSchedual(1);break;
      case 2:updateSchedual(2);break;
      case 3:updateSchedual(3);break;
      case 4:updateSchedual(4);break;
      case 5:updateSchedual(5);break;
      case 0:updateSchedual(0);break;
      default: goto TryAgain;break;
    }
  }else if(choice == 3){
    adminView();
  }
  goBack();
};

// HERE REGISTERD STUDENTS CAN SEE AVAILABLE CLASS DAYS TO ATTEND.
void seeClassSchedual(int courseCode){
  int choosenCourse = courseCode;
  string courseName;
  switch(choosenCourse){
    case 1: courseName = "FUNDAMENTALS_OF_PROGRAMING_II";break;
    case 2: courseName = "DATA_COMMUNICATION_AND_COMPUTER_NETWORKS";break;
    case 3: courseName = "DATABASE_SYSTEM";break;
    case 4: courseName = "DIGITAL_LOGIC_DESIGN";break;
    case 5: courseName = "ECONOMICS";break;
    case 0: announceClassDays();break;
    default:break;
  }
  cout<<"\t\t"<<courseName<<endl;
  fstream file;
  file.open(courseName+".txt",ios::in);
  if(file.is_open()){
    date_v = {};
    string courseDate;
    while(getline(file,courseDate)){
      date_v.push_back(courseDate);
    }
    file.close();
  }else{
    cout<<"\nERROR: OPENING "<<courseName<<" FILE FAILD!";exit(1);
  }
  delay();
  system("cls");
  cout<<"\t\t\tAVAILABLE CLASS DAYS FOR "<<courseName<<endl<<endl;
  if(date_v.size()==1){
    cout<<"\n\t\t\t -------------------------------";
    cout<<"\n\t\t\t|                               |";
    cout<<"\n\t\t\t| NO AVAILABLE CLASS THIS WEEK  |";
    cout<<"\n\t\t\t|                               |";
    cout<<"\n\t\t\t -------------------------------"<<endl;
  }else{
    for(int i = 0; i < date_v.size(); ++i){
      if(i!=0){
        cout<<"# UPCOMING CLASS ON (mm/dd/yy) : "<<date_v[i]<<endl;
      }
    }
  }
};
void updateSchedual(int crs){
  delay();
  system("cls");
  int courseCode = crs;
  string courseName;
  switch(courseCode){
    case 1: courseName = "FUNDAMENTALS_OF_PROGRAMING_II";break;
    case 2: courseName = "DATA_COMMUNICATION_AND_COMPUTER_NETWORKS";break;
    case 3: courseName = "DATABASE_SYSTEM";break;
    case 4: courseName = "DIGITAL_LOGIC_DESIGN";break;
    case 5: courseName = "ECONOMICS";break;
    case 0: announceClassDays();exit(0);break;
    default:break;
  }
  cout<<"\t\t"<<courseName<<endl;
  fstream file;
  file.open(courseName+".txt",ios::out);
  if(file.is_open()){
    file<<courseName;
    file.close();
  }else{
    cout<<"ERROR: OPENING "<<courseName<<"FILE FAILD!"<<endl;exit(1);
  }
  file.open(courseName+".txt",ios::app);
  if(file.is_open()){
    string dateForCourse;
    char wantToContinue = 'y';
    while(wantToContinue == 'y' || wantToContinue == 'Y'){
      cout<<"\nDATE(mm/dd/yyyy): ";
      cin>>dateForCourse;
      file<<endl<<dateForCourse;
      cout<<"\nCONTINUE?(y/n): ";
      cin>>wantToContinue;
    }
    file.close();
    delay();
    cout<<"\n\nCLASS FOR "<<courseName<<" SCHEDUALED SUCCESSFULLY!\n";
  }else{
    cout<<"ERROR: OPENING "<<courseName<<" FILE FAILD!"<<endl;exit(1);
  }
};


void registeredCourses(){
  fstream file1("FUNDAMENTALS_OF_PROGRAMING_II.txt");
  fstream file2("DATA_COMMUNICATION_AND_COMPUTER_NETWORKS.txt");
  fstream file3("DATABASE_SYSTEM.txt");
  fstream file4("DIGITAL_LOGIC_DESIGN.txt");
  fstream file5("ECONOMICS.txt");
  if((!file1.good()) || (!file2.good()) || (!file3.good()) || (!file4.good()) || (!file5.good())){
    file1.open("FUNDAMENTALS_OF_PROGRAMING_II.txt",ios::out);
    file2.open("DATA_COMMUNICATION_AND_COMPUTER_NETWORKS.txt",ios::out);
    file3.open("DATABASE_SYSTEM.txt",ios::out);
    file4.open("DIGITAL_LOGIC_DESIGN.txt",ios::out);
    file5.open("ECONOMICS.txt",ios::out);

    file1<<"FUNDAMENTALS_OF_PROGRAMING_II";file2<<"DATA_COMMUNICATION_AND_COMPUTER_NETWORKS";file3<<"DATABASE_SYSTEM";file4<<"DIGITAL_LOGIC_DESIGN";file5<<"ECONOMICS";
    file1.close();file2.close();file3.close();file4.close();file5.close();
  }
  cout<<"\nCOURSESE\n";
  cout<<"\n1 FUNDAMENTALS_OF_PROGRAMING_II";
  cout<<"\n2 DATA_COMMUNICATION_AND_COMPUTER_NETWORKS";
  cout<<"\n3 DATABASE_SYSTEM";
  cout<<"\n4 DIGITAL_LOGIC_DESIGN";
  cout<<"\n5 ECONOMICS";
  cout<<"\n0 BACK";
}

// HERE GOES SECURITY MANAGEMNET.
int setting(){
  delay();
  system("cls");
  cout<<"\t\t\tSETTING"<<endl<<endl;
  cout<<"\n1 CHANGE PASSWORD";
  cout<<"\n0 BACK";
  int option;
  cout<<"\n\nENTER CHOICE: ";
  cin>>option;
  switch(option){
    default : return 0;
    case 0: adminView();break;
    case 1: delay();
            system("cls");
            cout<<"\t\t\tSECURITY"<<endl<<endl;
            string oldPassword,newPassword,confirmPassword;
            cout<<"\nOLD PASSWORD: ";
            cin>>oldPassword;
            fstream file;
            file.open("password.txt",ios :: in);
            string realPassword;;
            if(file.is_open()){
              while(getline(file,realPassword));
              file.close();
            }else{
              cout<<"\nERRO: OPENING PASSWORD FILE FAILD!\n";break;
            }
            if(oldPassword == realPassword){
              delay();
              system("cls");
              cout<<"\t\t\t------- || PERMISSION GRANTED || ----------"<<endl<<endl;
              cout<<"\nNEW PASSWORD: ";
              cin>>newPassword;
              reEnterPassword:
              cout<<"\nCONFIRM PASSWORD: ";
              cin>>confirmPassword;
              if(newPassword == confirmPassword){
                file.open("password.txt",ios :: out);
                if(file.is_open()){
                  file<<confirmPassword;
                  delay();
                  system("cls");
                  cout<<"\n\n\tPASSWORD CHANGED SUCCESSFULLY!\n";
                  file.close();
                }else{
                  cout<<"\nERROR: OPENING PASSWORD FILE!\n";break;
                }
              }else{
                  cout<<"\nPASSWORD MISMATCHED\n";goto reEnterPassword;
              }
            }else{
              delay();
              system("cls");
              cout<<"\n\n\n\t\t\t------- || PERMISSION DENIED || ----------"<<endl<<endl;
            }
            break;
  }
  cout<<"\n\n\n";
  goBack();
  return 0;
}

// THIS FUNCTION MAKES THE USER INTERFACE AND EXPIRIENCE MORE ATTRACTIVE.
void delay(){
  cout<<"LOADING";
  for(int a = 0 ; a<4; ++a){
    cout<<".";
    for(int i = 0; i < 100000;++i){
      for(int j = 0; j < 1000; ++j){

      }
  }
  }
  for(int b = 0 ; b<1; ++b){
    for(int i = 0; i < 100000;++i){
      for(int j = 0; j < 1000; j+=10){
      }
  }
  }
}

void delay2(){
  for(int a = 0 ; a<3; ++a){
    for(int i = 0; i < 100000;++i){
      for(int j = 0; j < 1000; j+=10){
      }
  }
  }
  for(int b = 0 ; b<1; ++b){
    for(int i = 0; i < 100000;++i){
      for(int j = 0; j < 1000; j += 10){

      }
  }
  }
}
// THIS LAST(BUT NOT LEAST) FUNCTION HELPS US TO FLOW THROUGH THE PROGRAM EASLY.
int goBack(int to){
  int backTo = to;
  switch(backTo){
    case 1: cout<<"\nENTER |1| TO GO |BACK| OR ANY KEY TO |EXTI|"<<endl;
            int choice1;
            cin>>choice1;
            switch (choice1){
              case 1: adminView(); break;
              default: break; }
              break;
    case 2:cout<<"\nENTER |1| TO GO |BACK| OR ANY KEY TO |EXTI|"<<endl;
            int choice2;
            cin>>choice2;
            switch (choice2){
              case 1:main(); break;
              default: break; }
              break;
    default: break;
  }
  return 0;
}

void developersInfo(){
  delay();
  system("cls");
  cout<<"\n\t\t\t\t\t\tDEVELOPERS INFO\n";
  delay2();
  cout<<"\t  --------------------------------------------------------------------------------------------"<<endl;
  delay2();
  cout<<"\t|   -> C++ PROJECT                                                                            |"<<endl;
  delay2();
  cout<<"\t|   -> ADDIS ABABA SCIENCE AND TECHNOLOGY UNIVERSTY ||DEPARTMENT OF SOFTWARE ENGINEERING||;   |"<<endl;
  delay2();
  cout<<"\t|   -> PROJECT TITLE : STUDENT ATTENDANCE MANAGEMENT SYSTEM;                                  |"<<endl;
  delay2();
  cout<<"\t|   -> SECTION : D;                                                                           |"<<endl;
  delay2();
  cout<<"\t|   -> COURSE INSTRUCTOR : INS.ELENI THESHOME;                                                |"<<endl;
  delay2();
  cout<<"\t|                 ------------------------------------------                                  |"<<endl;
  delay2();
  cout<<"\t|               |        PREPARED BY                         |                                |"<<endl;
  delay2();
  cout<<"\t|               |   NAME                        ID           |                                |"<<endl;
  delay2();
  cout<<"\t|               |   1.NAHOM TSEGAYE             ETS 1154/14  |                                |"<<endl;
  delay2();
  cout<<"\t|               |   2.NANATI DEREJE             ETS 1177/14  |                                |"<<endl;
  delay2();
  cout<<"\t|               |   3.NEBAT HUSSEN              ETS 1178/14  |                                |"<<endl;
  delay2();
  cout<<"\t|               |   4.NASIFAY CHALA             ETS 1195/14  |                                |"<<endl;
  delay2();
  cout<<"\t|               |   5.NATAN ADDIS               ETS 1199/14  |            --------------------|"<<endl;
  delay2();
  cout<<"\t|                 ------------------------------------------             |  AUGUST 4,2023 G.C |"<<endl;
  delay2();
  cout<<"\t ---------------------------------------------------------------------------------------------"<<endl;
  delay2();
  cout<<"\n\n\t\t# A GENTLE REMINDER\n\n";
  delay2();
  cout<<"\t1.IF YOU ARE USING THIS SOFTWARE FOR THE VERY FIRST TIME, THE DEFAULT PASSWORD IS '1234'.\n";
  delay2();
  cout<<"\t  THEN YOU CAN CHANGE IT LATER IF YOU WANT.(GOTO: ADMIN LOGIN >> SETTING >> CHANGE PASSWORD )\n";
  delay2();
  cout<<"\t2.USE LETTERS,NUMBERS AND SPECIAL CHARACTERS FOR STRONG PASSWORD\n";
  delay2();
  cout<<"\t3.UPDATE YOUR PASSWORD FREQUENTLY FOR MORE SECURED SYSTEM\n\n";
  delay2();
  cout<<"\tNEED HELP? CONTACT US: \n";
  delay2();
  cout<<"\t\tnasifayc11@gmail.com"<<endl;
  delay2();
  cout<<"\t\tnataddis21@gmail.com"<<endl;
  delay2();
  cout<<"\t\tnahihaile4253@gmail.com"<<endl;
  delay2();
  cout<<"\t\tnanatidereje@gmail.com"<<endl;
  delay2();
  cout<<"\t\tnebathussen989@gmail.com"<<endl;
  delay2();
  cout<<"\t\tnebiyattakele23@gmail.com"<<endl;
  delay2();
  delay2();
  delay2();
  cout<<"\n\n\t|---------------------------------- ||  THANK YOU, STAY SAFE || -------------------------------------|"<<endl;
  goBack(2);
}
