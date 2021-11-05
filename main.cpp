#include <iostream>
#include <fstream>
#include <string>
#include <sstream> //Used for char* to int conversion
#include <cstring>
#include <windows.h> //Used for color
using namespace std;

const string globalList = "C:/Users/Katu/projects/c++/todo/globalList.txt";
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

int color[3] = {12, 11, 10};

void createList(string filename){
	ofstream file(filename);
	file.close();
}

void displayList(string filename){
	ifstream file(filename);
	if(!file){
		cout << "\ntodoList.txt does not exist in the current folder!\n";
		return;
	}

	int nr;
	string content;
	
	SetConsoleTextAttribute(console, 7);
	cout << endl;
	while(file >> nr){
		file >> content;
		SetConsoleTextAttribute(console, color[1]);
		cout << nr << " " << content << endl;
	}
	SetConsoleTextAttribute(console, 7);

	file.close();
}

void addTask(string filename, string text){
	int nr = 0;
	string content;

	ifstream input_file(filename);
	if(!input_file){
			SetConsoleTextAttribute(console, color[0]);
			cout << "\ntodoList.txt does not exist in the current folder!\n";
			SetConsoleTextAttribute(console, 7);
			return;
	}
	
	while(input_file >> nr){
		input_file >> content;
	}
	input_file.close();

	ofstream output_file(filename, ios_base::app);
	output_file << nr + 1 << " " << text << endl;
	output_file.close();

	SetConsoleTextAttribute(console, color[2]);
	cout << "\n Task Added Successfully!\n";
	SetConsoleTextAttribute(console, 7);	
}

void removeTask(string filename, int id){
	int nr[1000], i = 1;
	string content[1000];

	ifstream input_file(filename);
	if(!input_file){
		SetConsoleTextAttribute(console, color[0]);
		cout << "\ntodoList.txt does not exist in the current folder!\n";
		SetConsoleTextAttribute(console, 7);
		return;
	}

	while(input_file >> nr[i]){
		input_file >> content[i];
		i++;		
	}
	input_file.close();

	bool flag = false;
	ofstream output_file(filename);
	for(int x = 1; x <= i - 1; x++){
		if(nr[x] != id)
			output_file << ((flag) ? nr[x]-1 : nr[x]) << " " << content[x] << endl;

		else
			flag = true;
		
	}
	output_file.close();

	SetConsoleTextAttribute(console, color[2]);
	cout << "\n Task Removed Successfully!\n";
	SetConsoleTextAttribute(console, 7);
}

int charToInt(char nrText[1000]){
	string text(nrText);
	if(text[0] == '0'){
		SetConsoleTextAttribute(console, color[0]);
		cout << "\n Task number cannot start with 0!\n";
		SetConsoleTextAttribute(console, 7);
		return -1;
	}
	for(unsigned int i = 0; i < text.length(); i++){
		if(strchr("0123456789", text[i]) == NULL){
			SetConsoleTextAttribute(console, color[0]);
			cout << "\n Task number can ONLY contain digits!\n";
			SetConsoleTextAttribute(console, 7);
			return -1;
		}
	}
	
	stringstream stream(text);

	int nr;
	stream >> nr;
	return nr;
}

int main(int argc, char** argv){

	if(argc == 1)
		displayList(globalList);
	
	else if(strcmp(argv[1], "-create") == 0){
		createList("todoList.txt");
		createList(globalList);
	}
		
		
	else if(strcmp(argv[1], "-list") == 0)
		displayList("todoList.txt");
			
	else if(strcmp(argv[1], "-add") == 0)
		addTask("todoList.txt", argv[2]);
		
	else if(strcmp(argv[1], "-del") == 0)
		removeTask("todoList.txt", charToInt(argv[2]));
		
	else if(strcmp(argv[1], "-global") == 0){
		if(strcmp(argv[2], "-add") == 0)
			addTask(globalList, argv[3]);
		else if(strcmp(argv[2], "-del") == 0)
			removeTask(globalList, charToInt(argv[3]));
		else if(strcmp(argv[2], "-list") == 0)
			displayList(globalList);
	}
}
