/*
 * JumblePuzzle_15gjm2.h
 *
 *  Created on: Nov 7, 2018
 *      Author: gregmaceachern
 */

#ifndef JUMBLEPUZZLE_15GJM2_H_
#define JUMBLEPUZZLE_15GJM2_H_

#include <string>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

typedef char *charArrayPtr;

class BadJumbleException {
public:
	BadJumbleException(const string& msg);
	string what() const;
private:
	string message;
};

class JumblePuzzle {
public:

	// default constructor sets all attributes to 0 or NULL
	JumblePuzzle();

	// makes a puzzle with the hiddenWord somewhere in it
	JumblePuzzle(const string& hiddenWord, const string& difficulty);

	// deep copies an existing puzzle
	JumblePuzzle(const JumblePuzzle& orig);

	// destructor deletes the jumble grid, which is on the heap
	virtual ~JumblePuzzle();

	// deep copies an existing puzzle
	JumblePuzzle& operator=(const JumblePuzzle& right);

	char** getJumble() const; // returns a pointer to a deep copy of the jumble grid
	int getSize() const; // returns the size (width or height) of the grid
	int getRowPos() const; // returns the row at which the word is hidden
	int getColPos() const; // returns the column at which the word is hidden
	char getDirection() const; // returns the direction (n,e,s,w) the word is facing

private:
	int size;
	int row;
	int col;
	charArrayPtr* jumble;
	char direction;
};
#endif /* JUMBLEPUZZLE_15GJM2_H_ */
