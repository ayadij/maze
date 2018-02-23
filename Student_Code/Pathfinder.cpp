#include "Pathfinder.h"



Pathfinder::Pathfinder()
{
	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			for(int x = 0; x < 5; x++){
					Maze[x][y][z] = 1;
			}
		}
	}
}

Pathfinder::~Pathfinder() {}



bool Pathfinder::valid(string inString)
{
	if(inString.length() > 1){
		return false;
	}
	stringstream convert(inString);
	int number;
	convert >> number;
	if(convert.fail()){
		return false;
	}
	return true;
}

int Pathfinder::converter(string intString)
{
	int number;
	stringstream integer(intString);
	integer >> number;
	return number;
}


bool Pathfinder::find(int x, int y, int z){
	if(x == 4 && y == 4 && z == 4){
		stringstream ss;
		ss << "(" << x << "," << " " << y << "," << " " << z << ")";
		solved.push_back(ss.str());
		return true;
	}

	if(otherMaze[x][y][z] == 0){return false;}
	if(otherMaze[x][y][z] == 2){return false;}

	if(x > 4 || x < 0 || y > 4 || y < 0 || z > 4 || z < 0){return false;}

	otherMaze[x][y][z] = 2;

	if(find(x + 1, y, z)){
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		string path = ss.str();
		solved.push_back(path);
		return true;
	}
	if(find(x - 1, y, z)){
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		string path = ss.str();
		solved.push_back(path);
		return true;
	}
	if(find(x, y + 1, z)){
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		string path = ss.str();
		solved.push_back(path);
		return true;
	}
	if(find(x, y - 1, z)){
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		string path = ss.str();
		solved.push_back(path);
		return true;
	}
	if(find(x, y, z+1)){
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		string path = ss.str();
		solved.push_back(path);
		return true;
	}
	if(find(x, y, z-1)){
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		string path = ss.str();
		solved.push_back(path);
		return true;
	}
	return false;
}





string Pathfinder::getMaze()
{
	stringstream ss;
	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			for(int x = 0; x < 5; x++){
					ss << Maze[x][y][z];
					if(x < 4){
						ss << " ";
					}
			}
			ss << "\n";
		}
		ss << "\n";
	}
	return ss.str(); //return a string representation of the current maze or default maze
}


void Pathfinder::createRandomMaze()
{

	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			for(int x = 0; x < 5; x++){
					Maze[x][y][z] = rand()%2;	// randomly generates 1s and 0s
			}
		}
	}

	Maze[0][0][0] = 1;	//setting the entrance cell to 1
	Maze[4][4][4] = 1;	//setting the exit cell to 1

//print Maze
/*
	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			for(int x = 0; x < 5; x++){
					cout << Maze[x][y][z] << " ";
			}
			cout << endl;
		}
		cout << endl;
	}
*/

}






	//125 1s and 0s
	//separated by spaces
	//5x5 grids
	//open entrance and exit cell
	//x east west
	//y south north
	//z down up
	//checks if the map is valid
		//if(entrypoint != 1)
		//if(exitpoint != 1)
		//if(cellcount != 125)
		//if(linecount != 29)
		//if(cell != 0 || cell !=1)
//Part 2-----------------------------------------------------------------------------------
//Accept a file name from the test driver and read a maze from that file in the indicated format.
//Invalid mazes (e.g. bad tokens, not enough 1's and 0's) in the files should be rejected.

/* importMaze
 * Reads in a maze from a file with the given file name and stores it as the current maze.
 * Does nothing if the file does not exist or if the file's data does not represent a valid
 * maze.
 * The file's contents must be of the format described above to be considered valid.
 * Parameter:	file_name
 *				The name of the file containing a maze
 * Returns:		bool
 *				True if the maze is imported correctly; false otherwise*/
bool Pathfinder::importMaze(string file_name)
{


	ifstream openfile(file_name);
	string instring;
	int ycount = 0;

	while(getline(openfile, instring)){
		if(ycount == 0){
			string cells;
			int xcount = 0;
			stringstream cellcounter(instring);
			while(cellcounter >> cells){
				xcount++;
			}
			if(xcount != 5){return false;}
			xcount = 0;
		}

		ycount++;
	}

	if(ycount != 29){return false;}




	openfile.close();
	openfile.open(file_name.c_str());

	int Scratch[5][5][5];

	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			string line;
			getline(openfile, line);
			if(line.length() < 2){
				line.clear();
				getline(openfile, line);
			}
			stringstream incell(line);
			for(int x = 0; x < 5; x++){
				string cell;
				incell >> cell;
				if(valid(cell)){
					Scratch[x][y][z] = converter(cell);
					}
					else return false;
			}
		}
	}
	openfile.close();


	if(Scratch[0][0][0] != 1){return false;}
	if(Scratch[4][4][4] != 1){return false;}

	//If valid, copies everything from the temporary array into the maze array.
	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			for(int x = 0; x < 5; x++){
				Maze[x][y][z] = Scratch[x][y][z];
			}
		}
	}
	return true;






/*

	ifstream openfile(file_name);

	string instring;
	int linecount = 0;
	while(getline(openfile, instring)){
		int cellcount = 0;

		stringstream readcell(instring);
		int cells;
		while(readcell >> cells){
		cellcount++;
		}
		while(cellcount != 5){ return false;}
		linecount++;
	}
	while(linecount != 5){return false;}



return true;
*/








//eof()
//fail()



/*

	ifstream openfile;
	openfile.open(file_name.c_str());

	if(!openfile){
		return false;
	}




	while(!openfile.eof()){

		cout << endl << file_name << endl;
		string stringline;
		int linecount = 0;
		while (getline(openfile, stringline)){
			stringstream readcell(stringline);
			cout << stringline << endl;
			string cells;
			int cellcount = 0;
			while(readcell >> cells)
			{
				cellcount++;
				cout << "cellcount: " << cellcount << endl;




			}
			cout << "now: " << cellcount << endl;


			if(cellcount != 5 || cellcount != 0){
				cout << "invalid cellcount: " << cellcount << endl;
				return false;
			}


		linecount++;
		cout << "linecount: " << linecount << endl;
		}

		if(linecount != 29){
			cout << "invalid linecount: " << linecount << endl;
			return false;
		}


	}


	return true;




	cout << endl << file_name << endl;
 	string stringline;
	int linecount = 0;
	while (getline(openfile, stringline)){
		linecount++;
		cout << "linecount: " << linecount << endl;

	}
	if(linecount != 29){
		cout << "invalid linecount: " << linecount << endl;
		return false;
	}



	string line;
	while (getline(openfile, line)){
	stringstream readcell(line);
	cout << stringline << endl;
	string cells;
	int cellcount =  0;
	while(readcell >> cells)
	{
		cellcount ++;
		cout << "cellcount: " << cellcount << endl;
	}

	if(cellcount != 5){
		cout << "invalid cellcount: " << cellcount << endl;
		return false;
	}

	}






	openfile.close();
	openfile.open(file_name.c_str());

	int tempArray[5][5][5];

	for(int z = 0; z < 5; z++){
		for(int y = 0; y < 5; y++){
			string line;
			getline(openfile, line);
			if(line.length() < 2){
				line.clear();
				getline(openfile, line);
			}
			stringstream incell(line);
			for(int x = 0; x < 5; x++){
				string cell;
				incell << cell;
				if(cell != "0" || cell != "1"){ //fuction to check if cell is valid
					tempArray[x][y][z] = 1; //function to convert string to int?
				}
				else return false;
			}
			cout << "\n";
		}
		cout << "\n";
	}
	if (tempArray[0][0][0] != 1 || tempArray [4][4][4] ){
		return false;
	}


*/



}







//Part 3-----------------------------------------------------------------------------------
/* solveMaze
 * Attempts to solve the current maze and returns a solution if one is found.
 * A solution to a maze is a list of coordinates for the path from the entrance to the exit
 * (or an empty vector if no solution is found). This list cannot contain duplicates, and
 * any two consecutive coordinates in the list can only differ by 1 for only one
 * coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
 * in the solution. Each string in the solution vector must be of the format "(x, y, z)",
 * where x, y, and z are the integer coordinates of a cell.
 * Understand that most mazes will contain multiple solutions
 * Returns:		vector<string>
 *				A solution to the current maze, or an empty vector if none exists*/





vector<string> Pathfinder::solveMaze(){

	solved.clear();
	for(int z = 0; z < 5; z++){
			for(int y = 0; y < 5; y++){
				for(int x = 0; x < 5; x++){
					otherMaze[x][y][z] = Maze[x][y][z];
				}
			}
		}

	find(0, 0, 0);

	reverse(solved.begin(), solved.end());

	return solved;
}






/*
 *
 *
 *
 *
 *
 *
 *
 *
 *
develop a 30-40 minute lecture based upon the Book of Mormon,
which you will then teach to someone else (roommate, friend, spouse, etc.)
one-page, single-spaced, 12-point font, Times New Roman, outline of the lecture
	(Including topic,
	what scriptures you will use,
	what points of doctrine you will emphasize,
	overall message, etc).
Following the lecture, you will prepare a
	one-page,
	single-spaced paper reporting on how the experience went
	(What did you learn?
	What worked and what didn’t?
	What would you do differently next time, etc).



 *
 *
 *
Topic: Christ Loves All

Thought stimulating questions: What is love? Who do you love? Why do you love them? Who loves you?

Something that has stood out in my recent reading of the Book of Mormon is how much Jesus Christ loves all of His children.
He loves all of His children with all of His love. Even in the very first chapter of first Nephi, Lehi praises the Lord for being merciful over "all the inhabitants of the earth". I am not sure how much Lehi knew about the vastness of the earth or how many inhabitants there were but he did know that the Lord's love is all encompassing. That is something that he felt and something that many other Book of Mormon prophets had a testimony of and taught.

In fact, the Book of Mormon itself is a testament of His love for all of His children.
The Prophets in the Book of Mormon were instructed to write for a wise purpose. Part of that purpose was for other people to receive the Gospel of Jesus Christ-- not just the Jews. Not just the Gentiles.
When Christ visited the earth, he didn't just visit one group of people. He also visited “other sheep I have which are not of this fold”

More scriptural references:
• “power, and goodness, and mercy are over all the inhabitants of the earth”
(1 Ne. 1:14)
• “he inviteth them all to come unto him and partake of his goodness; and he denieth none that come unto him, black and white, bond and free, male and female; and he remembereth the heathen; and all are alike unto God, both Jew and Gentile."
(2 Nephi 26:33)
• “He manifesteth himself unto all those who believe in him, by the power of the Holy Ghost; yea, unto every nation, kindred, tongue, and people, working mighty miracles, signs, and wonders, among the children of men according to their faith”
(2 Ne. 26:13).
• “Know ye not that I, the Lord your God, have created all men, and that I remember those who are upon the isles of the sea; and that I rule in the heavens above and in the earth beneath; and I bring forth my word unto the children of men, yea, even upon all the nations of the earth?”
(2 Ne. 29:7)
• “The atonement was prepared from the foundation of the world for all mankind, which ever were since the fall of Adam”
(Mosiah 4:7).
• “He suffereth the pains of all… And he suffereth this that the resurrection might pass upon all men”
(2 Ne. 9:21–22).
• “Hath he commanded any that they should not partake of his salvation? Nay; but he hath given it free for all men; and all men are privileged the one like unto the other, and none are forbidden”
(2 Ne. 26:27–28).
• “Come unto Christ, and be perfected in him, and deny yourselves of all ungodliness; and if ye shall deny yourselves of all ungodliness, and love God with all your might, mind and strength, then is his grace sufficient for you, that by his grace ye may be perfect in Christ”
(Moro. 10:32)

These teachings in the Book of Mormon are meant for us to help us understand the universality and eternal nature of Christ's love.

2 Nephi 26:33 breaks it down for us pretty clearly.
Male and Female. Black and white, or all races. Bond and Free.
Bond can mean many things. Dallan H. Oaks, in his April 2006 conference talk taught that "bond" means being in bondage. This includes physical disabilities, addictions, emotional afflictions, traditions and customs contrary to the gospel.
His love does go out to everyone. Even those who, for us, might be hard to love or not deserving of it.

The ultimate sign of that love is His Atonement.
The scriptures are full of invitations for us to partake of his Atonement. He is practically pleading for us to accept His love.

The Lord provides a way for all His children come unto Him.

In the closing chapter of the Book of Mormon, Moroni pleads:
“Come unto Christ, and be perfected in him, and deny yourselves of all ungodliness; and if ye shall deny yourselves of all ungodliness, and love God with all your might, mind and strength, then is his grace sufficient for you, that by his grace ye may be perfect in Christ” (Moro. 10:32).

The gospel and His Atonement is for all people everywhere. All are invited. Christ loves All.


PRESENTATION TO MATTIE MAPONGO and ALEX PROBST – 29 JANUARY 2016


The presentation went well!
I am glad I was able to present to people who I felt comfortable sharing spiritual things with. They were open and receptive and played a good audience.
I started out my lecture by proposing a few questions about love. These questions were meant to spark thoughts in my audience. I wanted them to really think about love and what it is. What it means to love someone and what it means to be loved by someone. It turned out to be perfect that Mattie and Alex were my audience because they are a newly engaged couple. They were giggly about talking about love. Alex of course said that he loves Mattie. He said that Mattie is the woman of his dreams. He said that he even loves her when she is mad or tired or sick or not at her 100%. That was a good comment that I was able to tie in later.
I then was able to share with them my experiences as I have been reading the Book of Mormon. I shared my love for the Book of Mormon and introduced my topic. We read scritpures together and expounded upon each of the referenced verses.
As I was reading the verse in 2 Nephi 26:27–28, the phrase, "none are forbidden" threw me back into a flash back. A flood of memories from when I was a beehive in Young Womens came over me. I actually rememeber the exact time and place I read that scripture for the first time. I highlighted it and put a sticky note in the page as I sprawled across my downstairs bedroom daybed.
What a clear message the Book of Mormon shares. Jesus Christ loves everyone. It is not an exclusive love. We don't even have to deserve it. I shared this thought and memory with my audience which was great because I was able to tie in their comments with the points of my lecture.
The only thing I would change about my lecture is make it a bit longer. It barely cut thirty mintues but I was streaching it. I would like to have had prepared an example of Christ's everlasting love from the book of mormon. Not just scriptural passages but one or two actual story examples.
I learned that love is an attribute of Christ and we can only attempt to emulate it through following his example and keeping his commandments.



 *
 * */

