#include<iostream>
#include<string>
#include "game.h"
using namespace std;

int main(int argc, char * argv[]){
	string temp;
	string commands[10] = {"clockwise", "counterclockwise", "down", "drop", "left", "leveldown", "levelup", "restart", "right"};
	Game game;
	//commands array
	while(cin>>temp){						//read loop
	
	char inc = '\0';						//temporary character
	unsigned int pos = 0;					//position
	int repeat = 0;							//multiplier
	string inputCmd = "";					//given command
	bool badInput = false;					//bad input check
	int cmd = -1;							//location on the command array
	
		while(pos < temp.length()){			//parse loop
			inc = temp.at(pos);
			if(inc >= '0' && inc <= '9'){
			//check for numeric multiplier
				repeat = repeat * 10 + inc;
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
		if(badInput) continue; 				//check for bad input
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
			}
			pos++;							//post incrementer
		}
		
		//abort conditions
		if(badInput) continue;				//check for bad input
		if(inputCmd == "" || inputCmd.length() > commands[1].length()) continue;	
		//do nothing if no command or invalid input
		if(repeat == 0) continue;			//do nothing if multiplier is zero

		
		if(inputCmd == "restart"){
		//edge case where multiplier does not matter
			game.command("restart");
			continue;
		}
		
		
		for(int i=0;i<10;i++){
		//find the corresponding command, if it exists
			if(commands[i].substr(0,inputCmd.length()) == inputCmd){
				if(((i+1) < 10) && (commands[i+1].substr(0,inputCmd.length()) != inputCmd)){
					cmd = i;
				}
			}
		}
		
		if(cmd == -1) continue;				//do nothing is command not found
		
		for(int i=0;i<repeat;i++){
			//call the command at cmd multiple times
			//or pass the command to game
			game.command(commands[cmd]);
			cout << "\033[2J\033[1;1H";
			cout << game;					//updates the gameboard on screen for each command
		}

		
	}
}

