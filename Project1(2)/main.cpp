// This is the main file and this file is run in the start
#include <iostream>
#include <conio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.h>
#include <vector>
#include <iterator>
#include <time.h>

using namespace std;

//Function for different sections and task
void main1();//home page
void Dashboard(std::__cxx11::string id);//Dashboard
void attendence(string id);//Attendence Section
void create(void);//Create New Id
void login(void);//Login Page
void NotesSec(string id);//Study Material
int syllabus(string id);//Syllabus Section of study material 
int notes(string id);//Notes section of study material 
int videos(string id);//Videos section of study material 
void quiz(string id);//Quiz Section

int dash(int n, string section, string arr[]);//to navigate through option
int dashque(int n, string que, string arr[]);//Navigate thorugh option in a question to answer
std::string takePasswdFromUser();//To hide and save the password 

//User defined data type in enum 
enum IN
{
	IN_BACK = 8, // 8 is ASCII for Backspace;
	IN_RET = 13 // 13 is ASCII for carriage return
};

//Class for searching and sorting rows from csv files
class LoginRow
{
private:
	std::vector<std::string> m_data;

public:
	std::string const &operator[](std::size_t index) const
	{
		return m_data[index];
	}
	std::size_t size() const
	{
		return m_data.size();
	}
	void readNextRow(std::istream &str)
	{
		std::string line;
		std::getline(str, line);
		std::stringstream lineStream(line);
		std::string cell;

		m_data.clear();
		while (std::getline(lineStream, cell, ','))
		{
			m_data.push_back(cell);
		}

		if (!lineStream && cell.empty())
		{
			m_data.push_back("");
		}
	}
};

std::istream &operator>>(std::istream &str, LoginRow &data)
{
	data.readNextRow(str);
	return str;
}

int main()
{
	main1();
	return 0;
}

void main1()
{
	int n = 3;
	//Options
	string option[] = {" Create id", " Login", " Exit"};
	system("cls");
	cout << " Welcome to 'STUDENT STUDY MANAGER'" << endl;
	// function for scrolling menu
	int a = dash(n, " Welcome to 'STUDENT STUDY MANAGER'", option);

	if (a == 0)
	{
		//For creating the new account
		create();
	}
	else if (a == 1)
	{
		//for login page
		login();
	}
	else
	{
		// for exiting the program
		exit(0);
	}
}

//To create New Id
void create(void)
{
	string id, pass, num;
	LoginRow row;
	char a;
	int i;
	std::ofstream myfiles;
	std::ifstream files("test.csv");
	// This 'START' is the checkpoint for the function. use to navigate from end to this (using goto method.)
START:
	system("CLS");
	cout << "Enter the login ID:";
	cin >> id;
	while (files >> row)
	{
		if (row[0] == id)
		{
			cout << endl
				 << "This ID is already taken";
			Sleep(1000);
			goto START;
		}
	}
	files.close();
	cout << "\nEnter the password:";
	for (i = 0;;)
	{
		a = getch();
		// This will only allow to write alphabets or numbers.
		if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9'))
		{
			pass[i] = a;
			++i;
			//hiding the password
			cout << '*';
		}
		//for backspace
		if (a == '\b')
		{
			cout << "\b \b";
			--i;
		}
		//for saving the password and checking whether it is strong or not.
		if (a == '\r')
		{
			if (i <= 7)
			{

				cout << "\nPassword is too weak, please enter the correct password with more than 8 characters";
				getch();
				//direct to start.
				goto START;
			}
			else
			{
				cout << "\nThis is the password: ";
				for (int j = 0; j < i; j++)
				{
					cout << pass[j];
				}
				break;
			}
		}
	}
	//For phone number
	cout << "\nEnter the phone number:";
	cin >> num;
	//Saving the file in the csv format (in excel sheet)
	myfiles.open("test.csv", ios::app);
	myfiles << id << ",";
	for (int j = 0; j < i; j++)
	{
		myfiles << pass[j];
	}
	myfiles << "," << num << endl;
	//if account is not saved then it will direct you to start
	if (!myfiles)
	{
		cout << "YOUR ACCOUNT IS NOT SAVED." << endl
			 << "Loading..." << endl;
		Sleep(2000);
		goto START;
	}
	//else the account is created and you will be directed to the login page
	else
	{
		cout << "Your Account is created! Press enter to redirect you to the login page.";
		Sleep(2000);
		login();
	}
}

//Login Page
void login()
{
	int i = 0;
	char q;
//checkpoint
Start:
	system("CLS");
	fstream file;
	file.open("test.csv", ios::in);
	LoginRow row;
	string id, pass;
	cout << "Enter your ID: ";
	cin >> id;
	cout << "Enter your password:\n";
	//To type the password in hidden form directing to the function
	pass = takePasswdFromUser();
	//Searching for the id and and matching the password
	while (file >> row)
	{
		if (row[0] == id)
		{
			if (row[1] == pass)
			{
				cout << "\n\nOpening the Dashboard...";

				Sleep(2000);
				Dashboard(id);
				//flagging
				i = 1;
				break;
			}
			else
			{
				i = 2;
			}
		}
	}
	//If Id is not in the database, it will ask u to create id or to try again
	if (i == 0)
	{
		std::cout << "Sorry! No ID found!!" << endl
				  << "Do you want to create an ID (y/n)? : ";
		std::cin >> q;
		if (q == 'y')
		{
			Sleep(700);
			create();
			
		}
		else
		{
			std::cout << "Press enter to try again!";
			Sleep(2000);
			//Go to the checkpoint named 'Start'
			goto Start;
		}
	}
	//If password doesn't match, it will redirect u to the checkpoint
	else if (i == 2)
	{
		cout << endl
			 << "Incorrect Password!" << endl<< "Please try again";
		Sleep(2000);
		goto Start;
	}
}

// This function is used to scroll through the option in the list
int dash(int n, string section, string arr[])
{
	int pointer = -1;

	while (true)
	{
		//Clearing the screen
		system("cls");

		//Setting the colour of the text
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << section << "\n\n";

		for (int i = 0; i < n; ++i)
		{
			if (i == pointer)
			{
				//highlighting the option on which arrow for selection is present
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << arr[i] << endl;
			}

			else
			{
				//Remaining have same colour other than selected one
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << arr[i] << endl;
			}
		}
		//TO create a pause in the scroll
		Sleep(150);
		while (true)
		{
			// If up key is pressed the highlighting will shift up
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer == -1)
				{
					pointer = n - 1;
				}
				break;
			}
			// If down key is pressed the highlighting will shift down
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer == n)
				{
					pointer = 0;
				}
				break;
			}
			//If 'enter' key is press it will direct the file to the value stored in the option
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				for (int j = 0; j < n; j++)
				{
					if (pointer == j)
					{
						return j;
						break;
					}
				}

				break;
			}
		}

		Sleep(150);
	}
}

//Dashboard having different section
void Dashboard(std::__cxx11::string id)
{
	string Menu[] = {" Attendence", " Study Material", " Quiz", " Logout"};
	int a = dash(4, " DASHBOARD", Menu);
	//using switch case to go to different section
	switch (a)
	{
	case 0:

		cout << "\n\n\n Attendence Section is Opening....";
		Sleep(1000);
		attendence(id);
		break;
	case 1:

		cout << "\n\n\n Study Material Section is Opening....";
		Sleep(1000);
		NotesSec(id);
		break;
	case 2:
		cout << "\n\n\n Quiz Section is Opening....";
		Sleep(1000);
		quiz(id);

		break;
	case 3:
		cout << "\n\n\n Logging Out...";
		Sleep(1000);
		main1();
		break;
	}
}


time_t t;//time_t data type return the variable the standard time in seconds

//Attendence section having option to give or see the attendence 
void attendence(string id)
{
	
	char n;
	std::string sub[2], que, ans[2];
Start:
	//Use to get the time one gave the attendence
	struct tm *ptr;
	t = time(NULL);
	system("CLS");
	string arr[] = {" Give Attendence", " See the Attendence Sheet", " Back to Dashboard"};
	int a = dash(3, "*********ATTENDANCE SECTION*********", arr);
	if (a == 0)
	{	
			system("CLS");
			ifstream files;
			ofstream myfiles;
			//Subject u want to give attendence
			cout << " Enter the Subject: ";
			cin >> sub[0];
			files.open("test.txt", ios::in);//open file to get data 
			
			if (files.is_open())//is file open or not
			{
				//taking lines one by one from file to sub[1]
				while (getline(files, sub[1]))
				{
					if (sub[1] == sub[0])
					{
						getline(files, que);
						cout << que << endl;
						cin >> ans[0];
						getline(files, ans[1]);
						myfiles.open("attendence.csv", ios::app);
						
						//If answer correct, attendence will be filled
						if (ans[1] == ans[0])
						{
							myfiles << endl<< id << "," << sub[0] << "," << ctime(&t);
							cout <<endl<<"Attendence Has been recorded!!"<< endl<< id << "\t" << sub[0] << "\t" << ctime(&t);
						}
						else{//else no attendence will be recorded
							cout<<"Sorry Incorrect Answer!!"<<endl;
						}
						myfiles.close();
						break;
					}
				}
				
			}

			cout << endl<< endl;
			system("pause"); // Asks user to enter key to go forward
			goto Start;
			
			}
	else if (a == 1)//To see the attendence history subject-wise
	{
		
			system("CLS");
			std::ifstream myfiles("attendence.csv");
			LoginRow row;
			cout << " Enter the Subject: ";
			cin >> sub[0];
			cout << endl<< "\t   "<< "Date"<< "      "<< "Time"<< "\t   "<< "Subject";
			while (myfiles >> row)
			{
				if (row[0] == id)
				{
					if(row[1]==sub[0]){

					cout << endl<< "\t" << row[2] << "   " << row[1];
					}
				}
			}

			cout << endl<< endl;
	system("pause"); // Asks user to enter key to go forward
	goto Start;
	}
	else if (a == 2)
	{
		//Direct you to Dashboard function
		Dashboard(id);
	}

	// cout<<endl<<"Do you want to give the attendence or go back to the dashboard?"<<endl;
}

//Study Material Section
void NotesSec(string id)
{
	system("cls");

	string Menu[] = {" Syllabus", " Notes", " Reference Videos", " Back to Dashboard"};
	int choice = dash(4, "*********STUDY MATERIAL**********", Menu);
	switch (choice)
	{
	case 0:

		cout << "\n\n\n Syllabus opening...";
		Sleep(1000);
		syllabus(id);
		break;
	case 1:

		cout << "\n\n\n Notes opening...";
		Sleep(1000);
		notes(id);
		break;
	case 2:

		cout << "\n\n\n Reference Videos Opening...";
		Sleep(1000);
		videos(id);
		break;
	case 3:

		Dashboard(id);
		break;
	}
}

// Showing syllabus
int syllabus(string id)
{
	system("cls");
	string line;

	cout << " STUDY MATERIAL : SYLLABUS\n\n";
	ifstream myfile("Syllabus.txt"); //Reading Syllbus.txt file
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else
		cout << " Unable to open file"; //If file not opened
	cout << endl<< endl;
	system("pause"); // Asks user to enter key to go forward
	NotesSec(id);
	return 0;
}

// Showing Notes
int notes(string id)
{
	Notes:
	system("cls");

	string Menu[] = {" Mathematics Notes", " Physics Notes", " Chemistry Notes",
					 " English Notes", " Computer Science Notes", " Environment Science Notes", " Back"};
	// int pointer = 0;
	int choice = dash(7, " STUDY MATERIAL : NOTES", Menu);

	// Links for the notes in Google Drive
	string math = "start https://drive.google.com/folderview?id=15R6LDGuPKyRLQ15YNxd8dCb0ftU0r5an";
	string physics = "start https://drive.google.com/folderview?id=15SODgH8e674Dpv8nEYQSMfaKe9bzZWLK";
	string chemistry = "start https://drive.google.com/folderview?id=15T54LKvdZN4So2WKWsya0kinmaGxeHx4";
	string english = "start https://drive.google.com/folderview?id=15U7sNfBBOMDjXkvXxyiDNDYVMLVzxScB";
	string computer = "start https://drive.google.com/folderview?id=15VHVghwAQSsMgPMJA1BjLekHdO5-wm30";
	string evs = "start https://drive.google.com/folderview?id=1Z69u8-_8KmS9N0Qhopq0h8cQO5nG2I9n";

	switch (choice)
	{
	case 0:

		cout << "\n\n\n Mathematics Notes Opening...";
		Sleep(1000);
		system(math.c_str()); //Opening the link
		goto Notes;
		break;
	case 1:

		cout << "\n\n\n Physics Notes Opening...";
		Sleep(1000);
		system(physics.c_str()); 
		goto Notes;
		break;
	case 2:

		cout << "\n\n\n Chemistry Notes Opening...";
		Sleep(1000);
		system(chemistry.c_str());
		goto Notes;
		break;
	case 3:
		cout << "\n\n\n English Notes Opening...";
		Sleep(1000);
		system(english.c_str());
		goto Notes;
		break;
	case 4:

		cout << "\n\n\n Computer Science Notes Opening...";
		Sleep(1000);
		system(computer.c_str());
		goto Notes;
		break;
	case 5:

		cout << "\n\n\n Environment Science Notes Opening...";
		Sleep(1000);
		system(evs.c_str());
		goto Notes;
		break;

	case 6:
		NotesSec(id);
		return 0;
		break;
	}

	return 0;
}


// Showing Videos
int videos(string id)
{
	Videos:
	system("cls");

	string Menu[] = {" Mathematics Videos", " Physics Videos", " Chemistry Videos",
					 " English Videos", " Computer Science Videos", " Environment Science Videos", " Back"};
	int choice = dash(7, " STUDY MATERIAL : VIDEOS", Menu);

	// Links for Reference Videos
	string math = "start https://youtube.com/playlist?list=PLiSPNzs4fD9vGQD-aUVKpDuzsRaXekgjj";
	string physics = "start https://youtube.com/playlist?list=PLF_SObSnxBuDnV3Xeh6MlUe1knThNyyPz";
	string chemistry = "start https://youtube.com/playlist?list=PLm_MSClsnwm9p_yaZ8zIW1LxkK7_n98gD";
	string english = "start https://youtube.com/playlist?list=PLm_MSClsnwm-AIEbpyIxoTT8t7UzkHSYC";
	string computer = "start https://youtube.com/playlist?list=PLOp-kUrMswHcCcBlspdSRiDKb603sVVsR";
	string evs = "start https://youtube.com/playlist?list=PLgzsL8klq6DIOpwb57vb_ha_IUyNKRUyS";
	switch (choice)
	{
	case 0:

		cout << "\n\n\n Mathematics Videos Opening...";
		Sleep(1000);
		system(math.c_str()); // Opens the link
		goto Videos;
		break;

	case 1:

		cout << "\n\n\n Physics Videos Opening...";
		Sleep(1000);
		system(physics.c_str());
		goto Videos;
		break;

	case 2:

		cout << "\n\n\n Chemistry Videos Opening...";
		Sleep(1000);
		system(chemistry.c_str());
		goto Videos;
		break;

	case 3:

		cout << "\n\n\n English Videos Opening...";
		Sleep(1000);
		system(english.c_str());
		goto Videos;
		break;

	case 4:

		cout << "\n\n\n Computer Science Videos Opening...";
		Sleep(1000);
		system(computer.c_str());
		goto Videos;
		break;

	case 5:

		cout << "\n\n\n Environment Science Videos Opening...";
		Sleep(1000);
		system(evs.c_str());
		goto Videos;
		break;

	case 6:
		NotesSec(id);
		return 0;
		break;
	}
	return 0;
}

//To attempt the quiz and show the scoreboard of user
void quiz(string id)
{
	Start:
	string front ="*************QUIZ TIME***************";
	string Menu[] = {" Atempt the quiz", " See the ScoreBoard"," Back to Dashboard"};
	int b = dash(3, front, Menu);
	if (b == 0)
	{
		system("CLS");
		cout << "******* Welcome to QUIZ GAME ********* \n\n";
		int a, count = 0;
		string cor;
		string que, ans[4];
		ofstream scores;//to store the score
		ifstream question, answer;//get questions and options 
		question.open("question.txt", ios::in);
		answer.open("answer.txt", ios::in);
		for (int i = 0; i < 20; i++)
		{
			getline(question, que);
			for (int j = 0; j < 4; j++)
			{
				getline(question, ans[j]);
			}
			a = dashque(4, que, ans);
			getline(answer, cor);
			if (ans[a] == cor)//check if correct
			{
				cout << endl << " CORRECT!";
				++count;//Increment the score
				Sleep(1000);
			}
			else//Not then incorrect
			{
				cout << endl << " Incorrect!";
				Sleep(1000);
			}
		}
		//Note the time when the quiz attempted
		struct tm *ptr;
		time_t t;
		t = time(NULL);
		scores.open("score.csv", ios::app);
		scores << endl<< id << "," << count << "," << ctime(&t);//Saving the score
		scores.close();
		cout << endl<< endl;
	system("pause"); // Asks user to enter key to go forward
	goto Start;
	}
	else if (b == 1)
	{
		system("CLS");
		std::ifstream myfiles("score.csv");
		LoginRow row;
		cout << "Id : " << id;
		cout << endl<< "\t   "<< "Date"<< "      "<< "Time"<< "\t   "<< "Subject";
		while (myfiles >> row)
		{
			if (row[0] == id)
			{
				cout << endl<< "\t" << row[2] << "   " << row[1];//Displaying the ScoreCard
			}
		}
		cout << endl<< endl;
	system("pause"); // Asks user to enter key to go forward
	goto Start;
	}
	else if(b==2){
		Dashboard(id);//Back to Dashboard
	}
}

int dashque(int n, string que, string arr[])
{

	int pointer = -1;

	while (true)
	{
		//Clearing the screen
		system("cls");

		//Setting the colour of the text
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		cout << endl
			 << que << endl
			 << " (Use arrow keys to navigate through options)\n\n";

		for (int i = 0; i < n; ++i)
		{
			if (i == pointer)
			{
				//highlighting the option on which arrow for selection is present
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << arr[i] << endl;
			}

			else
			{
				//Remaining have same colour other than selected one
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				cout << arr[i] << endl;
			}
		}
		//TO create a pause in the scroll
		Sleep(150);
		while (true)
		{
			// If up key is pressed the highlighting will shift up
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				pointer -= 1;
				if (pointer <= -1)
				{
					pointer = n - 1;
				}
				break;
			}
			// If down key is pressed the highlighting will shift down
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				pointer += 1;
				if (pointer >= n)
				{
					pointer = 0;
				}
				break;
			}
			//If 'enter' key is press it will direct the file to the value stored in the option
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				for (int j = 0; j < n; j++)
				{
					if (pointer == j)
					{
						return j;
						break;
					}
				}

				break;
			}
		}

		Sleep(150);
	}
}

std::string takePasswdFromUser()
{
	char sp = '*';
	// Stores the password
	string passwd = "";
	char ch_ipt;

	// Until condition is true
	while (true)
	{

		ch_ipt = getch();

		// if the ch_ipt
		if (ch_ipt == IN::IN_RET)
		{
			cout << endl;
			return passwd;
		}
		else if (ch_ipt == IN::IN_BACK && passwd.length() != 0)
		{
			passwd.pop_back();

			// Cout statement is very
			// important as it will erase
			// previously printed character
			cout << "\b \b";

			continue;
		}

		// Without using this, program
		// will crash as \b can't be
		// print in beginning of line
		else if (ch_ipt == IN::IN_BACK && passwd.length() == 0)
		{
			continue;
		}

		passwd.push_back(ch_ipt);
		cout << sp;
	}
}
