#include<iosteam>
#include<string>
#include "game.h"
using namespace std;

int main(int argc, char * argv[]){
	string temp;
	Game game;
	string commands[10] = {"clockwise", "counterclockwise", "down", "drop", "left", "leveldown", "levelup", "restart", "right"};
	//commands array
	char inc = '\0';		//temporary character
	int pos = 0;			//position
	int repeat = 0;			//multiplier
	string inputCmd = "":		//given command
	while(cin>>temp){
	
		while(pos < temp.length()){
		//read loop
			inc = temp.at(pos);
			if(inc >= '0' && inc <= '9'){
			//check for numeric multiplier
				repeat = repeat * 10 + inc;
			}else if((inc >= 'A' && inc <= 'Z') || (inc >= 'a' && inc <= 'z')){
			//fetching the actual command
				inputCmd = inputCmd + inc;
			}else{
			//abort the program if there exists invalid input
				cerr << "bad input" << endl; //error msg
				return ;	
			}
			pos++;	//post incrementer
		}
		if(inputCmd == "" || inputCmd.length() > commands[1].length()) return ;		//do nothing if no command or invalid input
		if(repeat == 0) return ;	//do nothing if multiplier is zero
		int cmd = -1;
		if(inputCmd == "restart"){
		//edge case where multiplier does not matter
			//call restart
			return;
		}
		while(int i=0;i<10;i++){
			if(commands[i].substr(0,inputCmd.length()) == inputCmd){
				if((i+1)<10 && command[i+1].substr(0,inputCmd.length()) != inputCmd){
					cmd = i;
				}
			}
		}
		for(int i=0;i<repeat;i++){
			//call the command at cmd multiple times
			//or pass the command to game
			out << game;	//updates the gameboard on screen for each command
		}
		
		out << game;		//updates the gameboard on screen
	}
}
