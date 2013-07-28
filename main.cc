#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
#include "game.h"
using namespace std;

int main(int argc, char * argv[]){
	Game * game;
	int pos = 1;
	bool GUI = true;
	int seed = 0;
	string fileName = "";
	int startLevel = 0;
	
	
	while(pos < argc){
	//command line argument interpreter
		string temp = argv[pos];
		if(strcmp(argv[pos], "-text") == 0){
			GUI = false;
		}else if(strcmp(argv[pos], "-seed") == 0){
			if(pos + 1 < argc){
				pos++;
				stringstream ss(argv[pos]);
				ss >> seed;
			}else {
				cerr << "BAD ARGUMENTS" << endl;
			}
		}else if(strcmp(argv[pos], "-scriptfile") == 0){
			if(pos + 1 < argc){
				pos++;
				stringstream ss(argv[pos]);
				ss >> fileName;
			}else {
				cerr << "BAD ARGUMENTS" << endl;
			}
		}else if(strcmp(argv[pos], "-startlevel") == 0){
			if(pos + 1 < argc){
				pos++;
				stringstream ss(argv[pos]);
				ss >> startLevel;
			}else {
				cerr << "BAD ARGUMENTS" << endl;
			}
		}else {
			cerr << "BAD ARGUMENTS" << endl;
		}
		pos++;
	}
	
	if(fileName == ""){
		game = new Game (startLevel, seed, GUI);
	}else {
		game = new Game (fileName, startLevel, seed, GUI);
	}
	
	
	string temp;
	string commands[10] = {"clockwise", "counterclockwise", "down", "drop", "left", "leveldown", "levelup", "restart", "right"};
	//commands array
	cerr << "game sucess" <<endl;
	cout << "\033[2J\033[1;1H";
	cout << *game;
	
	
	while(cin>>temp){						//read loop
		char inc = '\0';						//temporary character
		unsigned int pos = 0;					//position
		int repeat = 0;							//multiplier
		string inputCmd = "";					//given command
		bool badInput = false;					//bad input check
		bool multi = false;								//check if multiplier exists
		int cmd = -1;							//location on the command array
		
		while(pos < temp.length()){			//parse loop
			inc = temp.at(pos);
			if(inc >= '0' && inc <= '9'){
			//check for numeric multiplier
				if(!multi) multi = true;
				repeat = repeat * 10 + inc - '0';
				cerr << "r:" << repeat <<endl;
			}else if((inc >= 'A' && inc <= 'Z') || (inc >= 'a' && inc <= 'z')){
			//fetching the actual command
				inputCmd = inputCmd + inc;
			}else{
			//abort the program if there exists invalid input
				cerr << "bad input" << endl; 
				badInput = true;
			}
			pos++;							//post incrementer
		}
		cerr << "first loop" <<endl;
		cerr << repeat << endl;
		cerr << inputCmd <<endl;
		cerr << badInput <<endl;
		
		if(badInput) continue; 				//check for bad input
		
		cerr << "after badinput1" <<endl;
		if(inputCmd == ""){
		//if there is a space between multiplier and command
		//then fetch command from cin
			cin >> temp;
			pos = 0;
			while(pos < temp.length()){
				inc = temp.at(pos);
				if((inc >= 'A' && inc <= 'Z') || (inc >= 'a' && inc <= 'z')){
				//fetching the actual command
					inputCmd = inputCmd + inc;
				}else{
				//abort the program if there exists invalid input
					cerr << "bad input" << endl;
					badInput = true;
				}
				pos++;
			}
										//post incrementer
		}
		
		//abort conditions
		if(badInput) continue;				//check for bad input
		if(inputCmd == "" || inputCmd.length() > commands[1].length()) continue;	
		//do nothing if no command or invalid input
		if(multi && (repeat == 0)) continue;			//do nothing if multiplier is zero
		if(!multi) repeat = 1;
		
		cerr << "before restart" <<endl;
		if(inputCmd == "restart"){
		//edge case where multiplier does not matter
			game->command(inputCmd);
			continue;
		}
		
		cerr << "before  finding command" << endl;
		for(int i=0;i<10;i++){
		//find the corresponding command, if it exists
			if(commands[i].substr(0,inputCmd.length()) == inputCmd){
				if(((i+1) < 10) && (commands[i+1].substr(0,inputCmd.length()) != inputCmd)){
					cmd = i;
				}
			}
		}
		
		if(cmd == -1) continue;				//do nothing is command not found
		cerr << "command found" <<endl;
		cerr << commands[cmd] << endl;
		cerr << "repeat: " << repeat <<endl;
		for(int i=0;i<repeat;i++){
			//call the command at cmd multiple times
			//or pass the command to game
			game->command(commands[cmd]);
			cout << "\033[2J\033[1;1H";
			cout << *game;					//updates the gameboard on screen for each command
		}
		cout << "\033[2J\033[1;1H";
		cout << *game;	
		
	}
	delete game;
}

