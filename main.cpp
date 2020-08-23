#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
//make files with a command and edit


bool running = true;
//All available functions, last one is quit
int createF() {
	std::cout<<"\tEnter a file name:";
	std::string fileName;
	std::cin>>fileName;
	try{
	std::ofstream MyFile(fileName);
	} catch (std::exception e) {
		std::cout<<"Error!\n";
		return -1;
	}
	std::cout<<"Made a file!\n";
	return 0;
}
int editF() {
	std::cout<<"\tEnter a file name:";
	std::string fileName;
	std::cin>> fileName;
	//////////////////////
	std::fstream file;
	file.open(fileName, std::fstream::in);
	if(file.is_open()) {
		std::cout<<"Type [exit] to save and quit file\n";

		while (!file.eof()) {
			std::string line; 
			std::getline(file, line);
			std::cout<<line<<"\n";
		}
		file.close();

		bool editing = true;
		while(editing) {
			std::string input;
			std::cout<<">";
			std::getline(std::cin, input);
			if (input != "[exit]"){
				file.open(fileName, std::fstream::app);
				file << input<<"\n";
				file.close();
				continue;
			}
			editing = false;
		}

		file.close();
		return 0;
	///////////////////////
	}	else{
			std::cout<<"\nError! Couldn't find file.\n";
			return -1;
	}
}
int ping() {
	return 0;
}
int quit() {
	running = false;
	std::cout<<"\nExiting.\n";
	return 0;
}

struct CommandLine {
	//Keys for the map, also a rudimentary list of functions
	std::string MAKE_FILE = "createF";
	std::string EDIT_FILE = "editF";
	std::string PING = "ping";
	std::string QUIT = "quit";
	std::string HELP = "help";

	//The map, has function pointers with string keys
	std::unordered_map<std::string, int(*)()> cmds ={
		{MAKE_FILE, &createF},
		{EDIT_FILE, &editF},
		{PING, &ping},
		{QUIT, &quit}
	};
	//Help not implemented in normal area bc it needs to access cmd list
	void help() {
		std::cout<<"\nList of functions:\n";
    int i =1;
		for (auto itr : cmds) {
			std::cout<<"\t" <<i<<")"<< itr.first << "\n";
      i++;
		}
	}

	void input() {
		std::string input;
		std::cout<<"\n:";
		std::cin>>input;

		if (cmds.find(input) != cmds.end() && input != "help") {
			auto command = cmds.find(input);
			std::cout<<(command->second)();
		}else if (input == "help") {
			help();
		}
		else{
			std::cout<<"\nError, command not found.\n";
		}
	}
};

int main() {
	CommandLine cmdL;
	std::cout<<"To view the list of current commands, type \'help\'.";
	while (running) {
  cmdL.input();
	}
}