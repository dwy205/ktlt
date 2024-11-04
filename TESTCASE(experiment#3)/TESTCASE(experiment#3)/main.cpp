/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 01.03.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink2.h"
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <vector>

bool compareFiles(const std::string& p1, const std::string& p2) {
	std::ifstream f1(p1, std::ifstream::binary | std::ifstream::ate);
	std::ifstream f2(p2, std::ifstream::binary | std::ifstream::ate);

	if (f1.fail() || f2.fail()) {
		return false; //file problem
	}

	if (f1.tellg() != f2.tellg()) {
		return false; //size mismatch
	}

	//seek back to beginning and use std::equal to compare contents
	f1.seekg(0, std::ifstream::beg);
	f2.seekg(0, std::ifstream::beg);
	return std::equal(std::istreambuf_iterator<char>(f1.rdbuf()),
		std::istreambuf_iterator<char>(),
		std::istreambuf_iterator<char>(f2.rdbuf()));
}

void clear_screen()
{
#if defined(_WIN32) || defined(WIN32)
	system("cls");
#else
	system("clear");
#endif // _WIN32

}

using namespace std;
class TestStudyInPink {
public:
	static void Test01(); //Sherlock
	static void Test02(); //Watson
	static void Test03(); //Criminal
	static void Test04(); //Configuration
	static void Test05(); //RobotC
	static void Test06(); //RobotS
	static void Test07(); //RobotW
	static void Test08(); //RobotSW
	static void Test09(); //SherlockBag
	static void Test10(); //WatsonBag
	static void Test11(); //StudyInPinkProgram

};



void TestStudyInPink::Test01()
{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("Sherlock/input/TestCase" + to_string(idx) + ".txt");
		//row
		int r;
		InFile >> r;
		//col
		int c;
		InFile >> c;
		//wall
		int num_wall = 0;
		InFile >> num_wall;
		Position* arr_wall = new Position[num_wall];
		for (int i = 0; i < num_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_wall[i] = p;
		}
		//fake wall
		int num_fake_wall = 0;
		InFile >> num_fake_wall;
		Position* arr_fake_wall = new Position[num_fake_wall];
		for (int i = 0; i < num_fake_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_fake_wall[i] = p;
		}
		//init pos
		string str_pos;
		InFile >> str_pos;
		Position init_pos(str_pos);
		//moving rule
		string moving_rule;
		InFile >> moving_rule;
		//hp, exp
		int hp;
		InFile >> hp;
		int exp;
		InFile >> exp;

		InFile.close();
		Map map(r, c, num_wall, arr_wall, num_fake_wall, arr_fake_wall);
		Sherlock sherlock(0, moving_rule, init_pos, &map, hp, exp);

		ofstream OutFile;
		OutFile.open("Sherlock/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << sherlock.str() << endl;

		for (int i = 1; i <= 200; i++)
		{
			OutFile << "STEPT " + to_string(i) << ":" << endl;
			sherlock.move();
			OutFile << sherlock.str() << endl;
		}
		OutFile.close();

		delete[] arr_wall;
		delete[] arr_fake_wall;

		//Compare
		if (compareFiles("Sherlock/output/Output" + to_string(idx) + ".txt", "Sherlock/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}

	}
}
void TestStudyInPink::Test02()

{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("Watson/input/TestCase" + to_string(idx) + ".txt");
		//row
		int r;
		InFile >> r;
		//col
		int c;
		InFile >> c;
		//wall
		int num_wall = 0;
		InFile >> num_wall;
		Position* arr_wall = new Position[num_wall];
		for (int i = 0; i < num_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_wall[i] = p;
		}
		//fake wall
		int num_fake_wall = 0;
		InFile >> num_fake_wall;
		Position* arr_fake_wall = new Position[num_fake_wall];
		for (int i = 0; i < num_fake_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_fake_wall[i] = p;
		}
		//init pos
		string str_pos;
		InFile >> str_pos;
		Position init_pos(str_pos);
		//moving rule
		string moving_rule;
		InFile >> moving_rule;
		//hp, exp
		int hp;
		InFile >> hp;
		int exp;
		InFile >> exp;

		InFile.close();
		Map map(r, c, num_wall, arr_wall, num_fake_wall, arr_fake_wall);
		Watson watson(0, moving_rule, init_pos, &map, hp, exp);

		ofstream OutFile;
		OutFile.open("Watson/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << watson.str() << " EXP:" << watson.exp << endl;

		for (int i = 1; i <= 200; i++)
		{
			OutFile << "STEPT " + to_string(i) << ":" << endl;
			watson.move();
			OutFile << watson.str() << endl;
		}
		OutFile.close();

		delete[] arr_wall;
		delete[] arr_fake_wall;

		//Compare
		if (compareFiles("Watson/output/Output" + to_string(idx) + ".txt", "Watson/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}
void TestStudyInPink::Test03()
{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("Criminal/input/TestCase" + to_string(idx) + ".txt");
		//row
		int r;
		InFile >> r;
		//col
		int c;
		InFile >> c;
		//wall
		int num_wall = 0;
		InFile >> num_wall;
		Position* arr_wall = new Position[num_wall];
		for (int i = 0; i < num_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_wall[i] = p;
		}
		//fake wall
		int num_fake_wall = 0;
		InFile >> num_fake_wall;
		Position* arr_fake_wall = new Position[num_fake_wall];
		for (int i = 0; i < num_fake_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_fake_wall[i] = p;
		}
		//Sherlock
		//init pos
		string sher_str_pos;
		InFile >> sher_str_pos;
		Position sher_init_pos(sher_str_pos);
		//moving rule
		string sher_moving_rule;
		InFile >> sher_moving_rule;
		//hp, exp
		int sher_hp;
		InFile >> sher_hp;
		int sher_exp;
		InFile >> sher_exp;

		//Watson
		//init pos
		string wat_str_pos;
		InFile >> wat_str_pos;
		Position wat_init_pos(wat_str_pos);
		//moving rule
		string wat_moving_rule;
		InFile >> wat_moving_rule;
		//hp, exp
		int wat_hp;
		InFile >> wat_hp;
		int wat_exp;
		InFile >> wat_exp;

		//Criminal
		string cri_str_pos;
		InFile >> cri_str_pos;
		Position cri_init_pos(cri_str_pos);

		InFile.close();

		Map map(r, c, num_wall, arr_wall, num_fake_wall, arr_fake_wall);
		Sherlock sherlock(1, sher_moving_rule, sher_init_pos, &map, sher_hp, sher_exp);
		Watson watson(2, wat_moving_rule, wat_init_pos, &map, wat_hp, wat_exp);
		Criminal criminal(0, cri_init_pos, &map, &sherlock, &watson);

		ofstream OutFile;
		OutFile.open("Criminal/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << criminal.str() << endl;
		OutFile << sherlock.str() << endl;
		OutFile << watson.str() << endl;
		OutFile << "CRIMINAL -> SHERLOCK -> WATSON" << endl;

		for (int i = 1; i <= 200; i++)
		{
			OutFile << "STEPT " + to_string(i) << ":" << endl;
			criminal.move();
			sherlock.move();
			watson.move();
			OutFile << criminal.str() << endl;
			OutFile << sherlock.str() << endl;
			OutFile << watson.str() << endl;
		}
		OutFile.close();

		delete[] arr_wall;
		delete[] arr_fake_wall;

		//Compare
		if (compareFiles("Criminal/output/Output" + to_string(idx) + ".txt", "Criminal/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}

	}
}
void TestStudyInPink::Test04()
{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		Configuration cog("Configuration/input/TestCase" + to_string(idx) + ".txt");
		ofstream OutFile;
		OutFile.open("Configuration/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << cog.str();
		OutFile.close();
		//Compare
		if (compareFiles("Configuration/output/Output" + to_string(idx) + ".txt", "Configuration/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}

	}

}
void TestStudyInPink::Test05()

{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("Robot/RobotC/input/TestCase" + to_string(idx) + ".txt");
		//row
		int r;
		InFile >> r;
		//col
		int c;
		InFile >> c;
		//wall
		int num_wall = 0;
		InFile >> num_wall;
		Position* arr_wall = new Position[num_wall];
		for (int i = 0; i < num_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_wall[i] = p;
		}
		//fake wall
		int num_fake_wall = 0;
		InFile >> num_fake_wall;
		Position* arr_fake_wall = new Position[num_fake_wall];
		for (int i = 0; i < num_fake_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_fake_wall[i] = p;
		}
		//Sherlock
		//init pos
		string sher_str_pos;
		InFile >> sher_str_pos;
		Position sher_init_pos(sher_str_pos);
		//moving rule
		string sher_moving_rule;
		InFile >> sher_moving_rule;
		//hp, exp
		int sher_hp;
		InFile >> sher_hp;
		int sher_exp;
		InFile >> sher_exp;

		//Watson
		//init pos
		string wat_str_pos;
		InFile >> wat_str_pos;
		Position wat_init_pos(wat_str_pos);
		//moving rule
		string wat_moving_rule;
		InFile >> wat_moving_rule;
		//hp, exp
		int wat_hp;
		InFile >> wat_hp;
		int wat_exp;
		InFile >> wat_exp;

		//Criminal
		string cri_str_pos;
		InFile >> cri_str_pos;
		Position cri_init_pos(cri_str_pos);

		//RobotC
		string robotC_str_pos;
		InFile >> robotC_str_pos;
		Position robotC_init_pos(robotC_str_pos);

		InFile.close();

		Map map(r, c, num_wall, arr_wall, num_fake_wall, arr_fake_wall);
		Sherlock sherlock(1, sher_moving_rule, sher_init_pos, &map, sher_hp, sher_exp);
		Watson watson(2, wat_moving_rule, wat_init_pos, &map, wat_hp, wat_exp);
		Criminal criminal(0, cri_init_pos, &map, &sherlock, &watson);
		RobotC robotC(3, robotC_init_pos, &map, &criminal);

		ofstream OutFile;
		OutFile.open("Robot/RobotC/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << criminal.str() << endl;
		OutFile << sherlock.str() << endl;
		OutFile << watson.str() << endl;
		OutFile << robotC.str() << endl;
		OutFile << "CRIMINAL -> SHERLOCK -> WATSON -> ROBOTC" << endl;

		for (int i = 1; i <= 200; i++)
		{
			OutFile << "STEPT " + to_string(i) << ":" << endl;
			criminal.move();
			sherlock.move();
			watson.move();
			robotC.move();
			OutFile << criminal.str() << endl;
			OutFile << sherlock.str() << endl;
			OutFile << watson.str() << endl;
			OutFile << robotC.str() << endl;
		}
		OutFile.close();

		delete[] arr_wall;
		delete[] arr_fake_wall;

		//Compare
		if (compareFiles("Robot/RobotC/output/Output" + to_string(idx) + ".txt", "Robot/RobotC/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}
void TestStudyInPink::Test06()

{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("Robot/RobotS/input/TestCase" + to_string(idx) + ".txt");
		//row
		int r;
		InFile >> r;
		//col
		int c;
		InFile >> c;
		//wall
		int num_wall = 0;
		InFile >> num_wall;
		Position* arr_wall = new Position[num_wall];
		for (int i = 0; i < num_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_wall[i] = p;
		}
		//fake wall
		int num_fake_wall = 0;
		InFile >> num_fake_wall;
		Position* arr_fake_wall = new Position[num_fake_wall];
		for (int i = 0; i < num_fake_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_fake_wall[i] = p;
		}
		//Sherlock
		//init pos
		string sher_str_pos;
		InFile >> sher_str_pos;
		Position sher_init_pos(sher_str_pos);
		//moving rule
		string sher_moving_rule;
		InFile >> sher_moving_rule;
		//hp, exp
		int sher_hp;
		InFile >> sher_hp;
		int sher_exp;
		InFile >> sher_exp;

		//Watson
		//init pos
		string wat_str_pos;
		InFile >> wat_str_pos;
		Position wat_init_pos(wat_str_pos);
		//moving rule
		string wat_moving_rule;
		InFile >> wat_moving_rule;
		//hp, exp
		int wat_hp;
		InFile >> wat_hp;
		int wat_exp;
		InFile >> wat_exp;

		//Criminal
		string cri_str_pos;
		InFile >> cri_str_pos;
		Position cri_init_pos(cri_str_pos);

		//RobotS
		string robotS_str_pos;
		InFile >> robotS_str_pos;
		Position robotS_init_pos(robotS_str_pos);

		InFile.close();

		Map map(r, c, num_wall, arr_wall, num_fake_wall, arr_fake_wall);
		Sherlock sherlock(1, sher_moving_rule, sher_init_pos, &map, sher_hp, sher_exp);
		Watson watson(2, wat_moving_rule, wat_init_pos, &map, wat_hp, wat_exp);
		Criminal criminal(0, cri_init_pos, &map, &sherlock, &watson);
		RobotS robotS(3, robotS_init_pos, &map, &criminal, &sherlock);

		ofstream OutFile;
		OutFile.open("Robot/RobotS/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << criminal.str() << endl;
		OutFile << sherlock.str() << endl;
		OutFile << watson.str() << endl;
		OutFile << robotS.str() << endl;
		OutFile << "CRIMINAL -> SHERLOCK -> WATSON -> ROBOTS" << endl;

		for (int i = 1; i <= 200; i++)
		{
			OutFile << "STEPT " + to_string(i) << ":" << endl;
			criminal.move();
			sherlock.move();
			watson.move();
			robotS.move();
			OutFile << criminal.str() << endl;
			OutFile << sherlock.str() << endl;
			OutFile << watson.str() << endl;
			OutFile << robotS.str() << endl;
		}
		OutFile.close();

		delete[] arr_wall;
		delete[] arr_fake_wall;

		//Compare
		if (compareFiles("Robot/RobotS/output/Output" + to_string(idx) + ".txt", "Robot/RobotS/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}
void TestStudyInPink::Test07()

{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("Robot/RobotW/input/TestCase" + to_string(idx) + ".txt");
		//row
		int r;
		InFile >> r;
		//col
		int c;
		InFile >> c;
		//wall
		int num_wall = 0;
		InFile >> num_wall;
		Position* arr_wall = new Position[num_wall];
		for (int i = 0; i < num_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_wall[i] = p;
		}
		//fake wall
		int num_fake_wall = 0;
		InFile >> num_fake_wall;
		Position* arr_fake_wall = new Position[num_fake_wall];
		for (int i = 0; i < num_fake_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_fake_wall[i] = p;
		}
		//Sherlock
		//init pos
		string sher_str_pos;
		InFile >> sher_str_pos;
		Position sher_init_pos(sher_str_pos);
		//moving rule
		string sher_moving_rule;
		InFile >> sher_moving_rule;
		//hp, exp
		int sher_hp;
		InFile >> sher_hp;
		int sher_exp;
		InFile >> sher_exp;

		//Watson
		//init pos
		string wat_str_pos;
		InFile >> wat_str_pos;
		Position wat_init_pos(wat_str_pos);
		//moving rule
		string wat_moving_rule;
		InFile >> wat_moving_rule;
		//hp, exp
		int wat_hp;
		InFile >> wat_hp;
		int wat_exp;
		InFile >> wat_exp;

		//Criminal
		string cri_str_pos;
		InFile >> cri_str_pos;
		Position cri_init_pos(cri_str_pos);

		//RobotW
		string robotW_str_pos;
		InFile >> robotW_str_pos;
		Position robotW_init_pos(robotW_str_pos);

		InFile.close();

		Map map(r, c, num_wall, arr_wall, num_fake_wall, arr_fake_wall);
		Sherlock sherlock(1, sher_moving_rule, sher_init_pos, &map, sher_hp, sher_exp);
		Watson watson(2, wat_moving_rule, wat_init_pos, &map, wat_hp, wat_exp);
		Criminal criminal(0, cri_init_pos, &map, &sherlock, &watson);
		RobotW robotW(3, robotW_init_pos, &map, &criminal, &watson);

		ofstream OutFile;
		OutFile.open("Robot/RobotW/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << criminal.str() << endl;
		OutFile << sherlock.str() << endl;
		OutFile << watson.str() << endl;
		OutFile << robotW.str() << endl;
		OutFile << "CRIMINAL -> SHERLOCK -> WATSON -> ROBOTW" << endl;

		for (int i = 1; i <= 200; i++)
		{
			OutFile << "STEPT " + to_string(i) << ":" << endl;
			criminal.move();
			sherlock.move();
			watson.move();
			robotW.move();
			OutFile << criminal.str() << endl;
			OutFile << sherlock.str() << endl;
			OutFile << watson.str() << endl;
			OutFile << robotW.str() << endl;
		}
		OutFile.close();

		delete[] arr_wall;
		delete[] arr_fake_wall;

		//Compare
		if (compareFiles("Robot/RobotW/output/Output" + to_string(idx) + ".txt", "Robot/RobotW/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}
void TestStudyInPink::Test08()

{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("Robot/RobotSW/input/TestCase" + to_string(idx) + ".txt");
		//row
		int r;
		InFile >> r;
		//col
		int c;
		InFile >> c;
		//wall
		int num_wall = 0;
		InFile >> num_wall;
		Position* arr_wall = new Position[num_wall];
		for (int i = 0; i < num_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_wall[i] = p;
		}
		//fake wall
		int num_fake_wall = 0;
		InFile >> num_fake_wall;
		Position* arr_fake_wall = new Position[num_fake_wall];
		for (int i = 0; i < num_fake_wall; i++)
		{
			string str;
			InFile >> str;
			Position p(str);
			arr_fake_wall[i] = p;
		}
		//Sherlock
		//init pos
		string sher_str_pos;
		InFile >> sher_str_pos;
		Position sher_init_pos(sher_str_pos);
		//moving rule
		string sher_moving_rule;
		InFile >> sher_moving_rule;
		//hp, exp
		int sher_hp;
		InFile >> sher_hp;
		int sher_exp;
		InFile >> sher_exp;

		//Watson
		//init pos
		string wat_str_pos;
		InFile >> wat_str_pos;
		Position wat_init_pos(wat_str_pos);
		//moving rule
		string wat_moving_rule;
		InFile >> wat_moving_rule;
		//hp, exp
		int wat_hp;
		InFile >> wat_hp;
		int wat_exp;
		InFile >> wat_exp;

		//Criminal
		string cri_str_pos;
		InFile >> cri_str_pos;
		Position cri_init_pos(cri_str_pos);

		//RobotSW
		string robotSW_str_pos;
		InFile >> robotSW_str_pos;
		Position robotSW_init_pos(robotSW_str_pos);

		InFile.close();

		Map map(r, c, num_wall, arr_wall, num_fake_wall, arr_fake_wall);
		Sherlock sherlock(1, sher_moving_rule, sher_init_pos, &map, sher_hp, sher_exp);
		Watson watson(2, wat_moving_rule, wat_init_pos, &map, wat_hp, wat_exp);
		Criminal criminal(0, cri_init_pos, &map, &sherlock, &watson);
		RobotSW robotSW(3, robotSW_init_pos, &map, &criminal, &sherlock, &watson);

		ofstream OutFile;
		OutFile.open("Robot/RobotSW/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << criminal.str() << endl;
		OutFile << sherlock.str() << endl;
		OutFile << watson.str() << endl;
		OutFile << robotSW.str() << endl;
		OutFile << "CRIMINAL -> SHERLOCK -> WATSON -> ROBOTSW" << endl;

		for (int i = 1; i <= 200; i++)
		{
			OutFile << "STEPT " + to_string(i) << ":" << endl;
			criminal.move();
			sherlock.move();
			watson.move();
			robotSW.move();
			OutFile << criminal.str() << endl;
			OutFile << sherlock.str() << endl;
			OutFile << watson.str() << endl;
			OutFile << robotSW.str() << endl;
		}
		OutFile.close();

		delete[] arr_wall;
		delete[] arr_fake_wall;

		//Compare
		if (compareFiles("Robot/RobotSW/output/Output" + to_string(idx) + ".txt", "Robot/RobotSW/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}
void TestStudyInPink::Test09()
{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("BaseBag/SherlockBag/input/TestCase" + to_string(idx) + ".txt");
		//Sherlock
		//init pos
		string strpos = "";
		InFile >> strpos;
		Position init_pos(strpos);
		//moving rule
		string moving_rule;
		InFile >> moving_rule;
		//hp, exp
		int hp;
		InFile >> hp;
		int exp;
		InFile >> exp;
		//Activity
		vector<string> activity;
		while (!InFile.eof())
		{
			string inlstr = "";
			InFile >> inlstr;
			activity.push_back(inlstr);
		}
		InFile.close();

		int count = 0;
		for (int i = 0; i < activity.size(); i++)
		{
			if (activity[i].find("INSERT") != string::npos)
			{
				count++;
			}
		}
		BaseItem** arr_item = new BaseItem * [count];
		int loop = 0;
		Sherlock sherlock(0, moving_rule, init_pos, NULL, hp, exp);
		SherlockBag SBag(&sherlock);
		ofstream OutFile;
		OutFile.open("BaseBag/SherlockBag/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << sherlock.str() << " HP:" << sherlock.hp << " EXP:" << sherlock.exp << endl;
		OutFile << SBag.str() << endl;
		for (int i = 0; i < activity.size(); i++)
		{
			string action = "";
			if (activity[i] == "INSERTMAGICBOOK")
			{
				arr_item[loop] = new MagicBook();
				SBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT MAGIC BOOK";
			}
			else if (activity[i] == "INSERTENERGYDRINK")
			{
				arr_item[loop] = new EnergyDrink();
				SBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT ENERGY DRINK";
			}
			else if (activity[i] == "INSERTFIRSTAID")
			{
				arr_item[loop] = new FirstAid();
				SBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT FIRST AID";
			}
			else if (activity[i] == "INSERTEXCEMPTIONCARD")
			{
				arr_item[loop] = new ExcemptionCard();
				SBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT EXCEMPTION CARD";
			}
			else if (activity[i] == "INSERTPASSINGCARD")
			{
				arr_item[loop] = new PassingCard("");
				SBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT PASSING CARD";
			}
			else if (activity[i] == "GET")
			{
				SBag.get();
				action = "GET";
			}
			else if (activity[i] == "GETITEMMAGICBOOK")
			{
				SBag.get(MAGIC_BOOK);
				action = "GET MAGIC BOOK";
			}
			else if (activity[i] == "GETITEMENERGYDRINK")
			{
				SBag.get(ENERGY_DRINK);
				action = "GET ENERGY DRINK";
			}
			else if (activity[i] == "GETITEMFIRSTAID")
			{
				SBag.get(FIRST_AID);
				action = "GET FIRST AID";
			}
			else if (activity[i] == "GETITEMEXCEMPTIONCARD")
			{
				SBag.get(EXCEMPTION_CARD);
				action = "GET EXCEMPTION CARD";
			}
			else if (activity[i] == "GETITEMPASSINGCARD")
			{
				SBag.get(PASSING_CARD);
				action = "GET PASSING CARD";
			}
			OutFile << "ACTIVITY " + to_string(i) + " : " + action << endl;
			OutFile << SBag.str() << endl;
		}
		OutFile.close();
		for (int i = 0; i < count; i++)
		{
			delete arr_item[i];
		}
		delete[] arr_item;

		//Compare
		if (compareFiles("BaseBag/SherlockBag/output/Output" + to_string(idx) + ".txt", "BaseBag/SherlockBag/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}
void TestStudyInPink::Test10()
{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		ifstream InFile;
		InFile.open("BaseBag/WatsonBag/input/TestCase" + to_string(idx) + ".txt");
		//Watson
		//init pos
		string strpos = "";
		InFile >> strpos;
		Position init_pos(strpos);
		//moving rule
		string moving_rule;
		InFile >> moving_rule;
		//hp, exp
		int hp;
		InFile >> hp;
		int exp;
		InFile >> exp;
		//Activity
		vector<string> activity;
		while (!InFile.eof())
		{
			string inlstr = "";
			InFile >> inlstr;
			activity.push_back(inlstr);
		}
		InFile.close();

		int count = 0;
		for (int i = 0; i < activity.size(); i++)
		{
			if (activity[i].find("INSERT") != string::npos)
			{
				count++;
			}
		}
		BaseItem** arr_item = new BaseItem * [count];
		int loop = 0;
		Watson watson(0, moving_rule, init_pos, NULL, hp, exp);
		WatsonBag WBag(&watson);
		ofstream OutFile;
		OutFile.open("BaseBag/WatsonBag/output/Output" + to_string(idx) + ".txt", ios::trunc);
		OutFile << watson.str() << " HP:" << watson.hp << " EXP:" << watson.exp << endl;
		OutFile << WBag.str() << endl;
		for (int i = 0; i < activity.size(); i++)
		{
			string action = "";
			if (activity[i] == "INSERTMAGICBOOK")
			{
				arr_item[loop] = new MagicBook();
				WBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT MAGIC BOOK";
			}
			else if (activity[i] == "INSERTENERGYDRINK")
			{
				arr_item[loop] = new EnergyDrink();
				WBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT ENERGY DRINK";
			}
			else if (activity[i] == "INSERTFIRSTAID")
			{
				arr_item[loop] = new FirstAid();
				WBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT FIRST AID";
			}
			else if (activity[i] == "INSERTEXCEMPTIONCARD")
			{
				arr_item[loop] = new ExcemptionCard();
				WBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT EXCEMPTION CARD";
			}
			else if (activity[i] == "INSERTPASSINGCARD")
			{
				arr_item[loop] = new PassingCard("");
				WBag.insert(arr_item[loop]);
				loop++;
				action = "INSERT PASSING CARD";
			}
			else if (activity[i] == "GET")
			{
				WBag.get();
				action = "GET";
			}
			else if (activity[i] == "GETITEMMAGICBOOK")
			{
				WBag.get(MAGIC_BOOK);
				action = "GET MAGIC BOOK";
			}
			else if (activity[i] == "GETITEMENERGYDRINK")
			{
				WBag.get(ENERGY_DRINK);
				action = "GET ENERGY DRINK";
			}
			else if (activity[i] == "GETITEMFIRSTAID")
			{
				WBag.get(FIRST_AID);
				action = "GET FIRST AID";
			}
			else if (activity[i] == "GETITEMEXCEMPTIONCARD")
			{
				WBag.get(EXCEMPTION_CARD);
				action = "GET EXCEMPTION CARD";
			}
			else if (activity[i] == "GETITEMPASSINGCARD")
			{
				WBag.get(PASSING_CARD);
				action = "GET PASSING CARD";
			}
			OutFile << "ACTIVITY " + to_string(i) + " : " + action << endl;
			OutFile << WBag.str() << endl;
		}
		OutFile.close();
		for (int i = 0; i < count; i++)
		{
			delete arr_item[i];
		}
		delete[] arr_item;

		//Compare
		if (compareFiles("BaseBag/WatsonBag/output/Output" + to_string(idx) + ".txt", "BaseBag/WatsonBag/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}
void TestStudyInPink::Test11()
{
	cout << "\nTestcases run successfully: ";
	for (int idx = 1; idx <= 500; idx++)
	{
		streambuf* coutbuf = cout.rdbuf();
		ofstream OutFile;
		OutFile.open("StudyInPink/output/Output" + to_string(idx) + ".txt", ios::trunc);
		std::cout.rdbuf(OutFile.rdbuf());
		StudyPinkProgram prog("StudyInPink/input/TestCase" + to_string(idx) + ".txt");
		prog.run(true);
		std::cout.rdbuf(coutbuf);
		OutFile.close();
		//Compare
		if (compareFiles("StudyInPink/output/Output" + to_string(idx) + ".txt", "StudyInPink/expected/Expected" + to_string(idx) + ".txt"))
		{
			if (idx != 500)
			{
				cout << idx << " ";
			}
			else
			{
				cout << idx << endl << "Congratulations, all testcases ran successfully!";
			}
		}
		else
		{
			cout << "\nYou failed at testcase: " << idx;
			break;
		}
	}
}

int main()
{
	clear_screen();
Start:
	int choice = 0;
	cout << "Select the topic you want to test: " << endl;
	cout << "1.Sherlock moving\n";
	cout << "2.Watson moving\n";
	cout << "3.Criminal, Sherlock and Watson moving respectively (In this situation, we don't create robot\n";
	cout << "4.Configuration\n";
	cout << "5.Criminal, Sherlock, Watson and RobotC moving respectively\n";
	cout << "6.Criminal, Sherlock, Watson and RobotS moving respectively\n";
	cout << "7.Criminal, Sherlock, Watson and RobotW moving respectively\n";
	cout << "8.Criminal, Sherlock, Watson and RobotSW moving respectively\n";
	cout << "9.Activities with Sherlock's Bag\n";
	cout << "10.Activities with Watson's Bag\n";
	cout << "11.Run the StudyInPink program\n";
	cout << "Your choice: "; cin >> choice;
	while ((choice <= 0) || (choice >= 12))
	{
		cout << "Your choice: "; cin >> choice;
	}
	clear_screen();
	switch (choice)
	{
	case 1:
		TestStudyInPink::Test01();
		break;
	case 2:
		TestStudyInPink::Test02();
		break;
	case 3:
		TestStudyInPink::Test03();
		break;
	case 4:
		TestStudyInPink::Test04();
		break;
	case 5:
		TestStudyInPink::Test05();
		break;
	case 6:
		TestStudyInPink::Test06();
		break;
	case 7:
		TestStudyInPink::Test07();
		break;
	case 8:
		TestStudyInPink::Test08();
		break;
	case 9:
		TestStudyInPink::Test09();
		break;
	case 10:
		TestStudyInPink::Test10();
		break;
	case 11:
		TestStudyInPink::Test11();
		break;
	default:
		break;
	}

	int thread = -1;
	cout << "\nDo you want to continue test another topic, if:\n";
	cout << "Want. Enter 1\n";
	cout << "Don't want. Enter 0\n";
	cout << "Your choice: "; cin >> thread;
	if (thread == 1)
	{
		clear_screen();
		goto Start;
	}

	return 0;

}