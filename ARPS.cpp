// RPS.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "player.h"
#include <windows.h>
#include <iomanip>
#include <conio.h>  
#include <stdio.h>
#include <cmath>

player player1 = player::player();
player player2 = player::player();
int comp_move;
char timed;
int rps_timer;

bool isNumber(std::string s )
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

void init(player p1, player p2) {
	// Decide streak
	std::string streak_player = "-";
	int streak_num = 0;
	char streak_move = '-';
	if (p1.r_consecutive != 0) {
		streak_player = p1.name;
		streak_num = p1.r_consecutive;
		streak_move = 'r';
	}
	else if (p1.p_consecutive != 0) {
		streak_player = p1.name;
		streak_num = p1.p_consecutive;
		streak_move = 'p';
	}
	else if (p1.s_consecutive != 0) {
		streak_player = p1.name;
		streak_num = p1.s_consecutive;
		streak_move = 's';
	}
	else if (p2.r_consecutive != 0) {
		streak_player = p2.name;
		streak_num = p2.r_consecutive;
		streak_move = 'r';
	}
	else if (p2.p_consecutive != 0) {
		streak_player = p2.name;
		streak_num = p2.p_consecutive;
		streak_move = 'p';
	}
	else if (p2.s_consecutive != 0) {
		streak_player = p2.name;
		streak_num = p2.s_consecutive;
		streak_move = 's';
	}

	std::cout << "|=============================|" << std::endl;
	std::cout << "|         Advanced RPS        |" << std::endl;
	std::cout << "|=============================|" << std::endl;
	std::cout << "| Player  |Points | R | P | S |" << std::endl;
	std::cout << "|=============================|" << std::endl;
	std::cout << "| " << std::left << std::setw(8) << p1.name << "|   " << p1.score << "   | " << p1.r_win << " | " << p1.p_win << " | " << p1.s_win << " |" << std::endl;
	std::cout << "| " << std::left << std::setw(8) << p2.name << "|   " << p2.score << "   | " << p2.r_win << " | " << p2.p_win << " | " << p2.s_win << " |" << std::endl;
	std::cout << "|=============================|" << std::endl;
	std::cout << "|Current streak: " << std::left << std::setw(8) << streak_player << "(" << streak_move << " " << streak_num << ")|" << std::endl;
	std::cout << "|=============================|" << std::endl;

}

void printRock() {
	std::cout << "     -------------------" << std::endl;
	std::cout << "    /  =                \\" << std::endl;
	std::cout << "   /   ==      =         \\" << std::endl;
	std::cout << "  /   = =             =   \\" << std::endl;
	std::cout << " /                  ===    \\" << std::endl;
	std::cout << " \\    =                    /" << std::endl;
	std::cout << "  \\  ==     ====          /" << std::endl;
	std::cout << "   \\          =          /" << std::endl;
	std::cout << "    \\                   /" << std::endl;
	std::cout << "     -------------------" << std::endl;
}

void printPaper() {
	std::cout << " ----------" << std::endl;
	std::cout << "|         |" << std::endl;
	std::cout << " \\        \\" << std::endl;
	std::cout << "  \\        \\" << std::endl;
	std::cout << "  |        |" << std::endl;
	std::cout << " /         /" << std::endl;
	std::cout << " ----------" << std::endl;
}

void printScissors() {
	std::cout << "   ----" << std::endl;
	std::cout << " /      \\                 ----" << std::endl;
	std::cout << " \\      / ---          ---" << std::endl;
	std::cout << "   ----      ---    ---" << std::endl;
	std::cout << "                ----" << std::endl;
	std::cout << "   ----      ---    ---" << std::endl;
	std::cout << " /      \\ ---          ---" << std::endl;
	std::cout << " \\      /                 ----" << std::endl;
	std::cout << "   ----" << std::endl;
}

void compareMoves(player &p1, player &p2) {
	std::cout << player1.name << " played:" << std::endl;
	Sleep(1000);
	switch (p1.move) {
	case 'r':
		printRock();
		Sleep(1000);
		std::cout << player2.name << " played:" << std::endl;
		Sleep(1000);
		switch (p2.move) {
		case 'r':
			printRock();
			Sleep(1000);
			std::cout << std::endl << "It's a tie!" << std::endl;
			break;
		case 'p':
			printPaper();
			Sleep(1000);
			std::cout << std::endl << p2.name << " wins!" << std::endl;
			p1.lose();
			p2.win(p2.move);
			break;
		case 's':
			printScissors();
			Sleep(1000);
			std::cout << std::endl << p1.name << " wins!" << std::endl;
			p1.win(p1.move);
			p2.lose();
			break;
		}
		break;
	case 'p':
		printPaper();
		Sleep(1000);
		std::cout << player2.name << " played:" << std::endl;
		Sleep(1000);
		switch (p2.move) {
		case 'r':
			printRock();
			Sleep(1000);
			std::cout << std::endl << p1.name << " wins!" << std::endl;
			p1.win(p1.move);
			p2.lose();
			break;
		case 'p':
			printPaper();
			Sleep(1000);
			std::cout << std::endl << "It's a tie!" << std::endl;
			break;
		case 's':
			printScissors();
			Sleep(1000);
			std::cout << std::endl << p2.name << " wins!" << std::endl;
			p1.lose();
			p2.win(p2.move);
			break;
		}
		break;
	case 's':
		printScissors();
		Sleep(1000);
		std::cout << player2.name << " played:" << std::endl;
		Sleep(1000);
		switch (p2.move) {
		case 'r':
			printRock();
			Sleep(1000);
			std::cout << std::endl << p2.name << " wins!" << std::endl;
			p1.lose();
			p2.win(p2.move);
			break;
		case 'p':
			printPaper();
			Sleep(1000);
			std::cout << std::endl << p1.name << " wins!" << std::endl;
			p1.win(p1.move);
			p2.lose();
			break;
		case 's':
			printScissors();
			Sleep(1000);
			std::cout << std::endl << "It's a tie!" << std::endl;
			break;
		}
		break;
	}
}

int getMove(player &p1, player p2, int timer) {
	for (int i = timer; i > 0; i--) {
		std::string message = p1.name + ": Select a move (r/p/s) (" + std::to_string(i) + "): ";
		std::string errorMessage = "Please enter an 'r', 'p', or 's'";
		std::cout << message;
		if (!_kbhit()) {
			Sleep(1000);
			std::cout << std::string(message.length(), '\b');
		}
		else {
			p1.move = _getch();
			if (p1.move != 'r' && p1.move != 'p' && p1.move != 's') {
				std::cout << std::string(message.length(), '\b');
				std::cout << std::endl << errorMessage;
				Sleep(2000);
				std::cout << std::string(errorMessage.length(), '\b');
			}
			else {
				break;
			}
		}
	}

	if (p1.move != 'r' && p1.move != 'p' && p1.move != 's') {
		std::cout << std::endl << "Time's up! (+1) for " << p2.name << "!" << std::endl;
		Sleep(3000);
		return 1;
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Obtain players' names and timer option
	bool nameObtained = false;
	std::string inputName;
	while (nameObtained == false) {
		std::cout << "Enter name for player1: ";
		std::cin >> inputName;
		if (inputName.size() > 8)
			std::cout << "Name must be 8 or less characters." << std::endl;
		else
			nameObtained = true;
	}
	player1.name = inputName;

	nameObtained = false;
	while (nameObtained == false) {
		std::cout << "Enter name for player2: ";
		std::cin >> inputName;
		if (inputName.size() > 8)
			std::cout << "Name must be 8 or less characters." << std::endl;
		else
			nameObtained = true;
	}
	player2.name = inputName;

	bool timerObtained = false;
	char timerInput;
	while (timerObtained == false) {
		std::cout << "Timed or Untimed (t/u): ";
		std::cin >> timerInput;
		if (timerInput != 't' && timerInput != 'u')
			std::cout << "Please enter a 't' for Timed or a 'u' for untimed." << std::endl;
		else
			timerObtained = true;
	}
	timed = timerInput;

	// If 'timed' was selected, prompt for number of seconds per turn
	if (timed == 't') {
		timerObtained = false;
		std::string secondInput;
		while (timerObtained == false) {
			std::cout << "Enter time (s): ";
			std::cin >> secondInput;
			if (!isNumber(secondInput)) 
				std::cout << "Please enter a number of seconds between 5 and 60." << std::endl;
			else if (stoi(secondInput) > 60 || stoi(secondInput) < 5)
				std::cout << "Please enter a number of seconds between 5 and 60." << std::endl;
			else
				timerObtained = true;
		}
		rps_timer = stoi(secondInput);
	}

	system("CLS");
	while (player1.score < 10 && player2.score < 10) {
		// if the game is timed
		if (timed == 't') {
			init(player1, player2);
			if (getMove(player1, player2, rps_timer) == 0) {
				system("CLS");
				init(player1, player2);
				if (getMove(player2, player1, rps_timer) == 0) {
					system("CLS");
					init(player1, player2);
					compareMoves(player1, player2);
					player1.move = ' ';
					player2.move = ' ';
					Sleep(2500);
				}
				else {
					player1.score++;
				}
			}
			else {
				player2.score++;
			}
		}
		else if (timed == 'u') {
			std::string p1message = player1.name + ": Select a move (r/p/s): ";
			std::string p2message = player2.name + ": Select a move (r/p/s): ";
			init(player1, player2);
			bool moveObtained = false;
			char moveInput;
			
			// get player 1's move
			while (moveObtained == false) {
				std::cout << p1message;
				std::cin >> moveInput;
				if (moveInput != 'r' && moveInput != 'p' && moveInput != 's')
					std::cout << "Please enter an 'r', 'p', or 's'." << std::endl;
				else
					moveObtained = true;
			}
			player1.move = moveInput;
			system("CLS");
			init(player1, player2);

			// get player 2's move
			moveObtained = false;
			while (moveObtained == false) {
				std::cout << p2message;
				std::cin >> moveInput;
				if (moveInput != 'r' && moveInput != 'p' && moveInput != 's')
					std::cout << "Please enter an 'r', 'p', or 's'." << std::endl;
				else
					moveObtained = true;
			}
			player2.move = moveInput;
			system("CLS");
			init(player1, player2);

			compareMoves(player1, player2);
			Sleep(2500);
		}
		if (player1.score < 10 && player2.score < 10)
			system("CLS");
	}

	if (player1.score >= 10)
		std::cout << "VICTORY FOR " << player1.name << "!" << std::endl;
	else
		std::cout << "VICTORY FOR " << player2.name << "!" << std::endl;
	std::system("pause");
	return 0;
}

