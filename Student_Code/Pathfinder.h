#pragma once
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

#include "PathfinderInterface.h"

using namespace std;

class Pathfinder : public PathfinderInterface
{

private:


public:

	Pathfinder();
	~Pathfinder();

	int Maze[5][5][5];
	int otherMaze[5][5][5];

	bool valid(string inString);
	int converter(string intString);

	string getMaze();
	void createRandomMaze();
	bool importMaze(string file_name);
	bool find(int x, int y, int z);
	vector<string> solveMaze();
	vector<string> solved;


};
/*
 *
 *
 *
 *
 *
 *
 *
	 * //function that counts the cells and lines
	if(linecount != 0){
		cout << "bad number line: " << linecount << endl;
		return false;
	}


	import.close();
	import.open(file_name.c_str());

	int TempArray[5][5][5];

	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			string line;
			getline(import, line);
			if(line.length() <2){
				line.clear();
				getline(import, line);
			}
			stringstream incell(line);
			for(int x = 0; x < 5; x++){
				string cell;
				incell << cell;
				ifcellisvalid(cell){ //fuction to check if cell is valid
					TempArray[x][y][z] = stringToInt(cell); //tf?idk
				}
				else return false;
			}
			cout << endl;
		}
		cout << endl;
	}
	if (TempArray[0][0][0] != 1 || TempArray [4][4][4] ){ return false;}
 *
 *
 *
 *
 * */
