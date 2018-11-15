/*
 * JumblePuzzle_15gjm2.cpp
 *
 *  Created on: Nov 7, 2018
 *  Author: gregmaceachern
 */

#include "JumblePuzzle_15gjm2.h"

using namespace std;


JumblePuzzle::JumblePuzzle() {
	size = 0;
	row = 0;
	col = 0;
	jumble = nullptr;
	direction = 0;
}

JumblePuzzle::JumblePuzzle(const string& word, const string& difficulty) {
	string directions = "nesw";
	int randDirection = rand() % 4;

	direction = directions[randDirection];

	int incrementSouth;
	int incrementEast;


	int incrementSouthArr[4] = {-1, 0, 1, 0};
	int incrementEastArr[4] = {0, 1, 0, -1};

	incrementSouth = incrementSouthArr[randDirection];
	incrementEast = incrementEastArr[randDirection];

	if (word.length() < 3 || word.length() > 10) {
        throw BadJumbleException("Error. Word must be between 3 and 10 letters long");
	}
	if (difficulty == "hard") {
		size = 4 * word.length();
	} else if (difficulty == "medium") {
		size = 3 * word.length();
	} else if (difficulty == "easy") {
		size = 2 * word.length();
	} else {
		throw BadJumbleException("Error. Difficulty must be hard, medium or easy.");
	}
	col = rand() % (size - (incrementEast ? word.length() - 1 : 0)) + ( incrementEast == -1 ? word.length() - 1 : 0);
	row = rand() % (size - (incrementSouth ? word.length() - 1 : 0)) + (incrementSouth == -1 ? word.length() - 1 : 0);

//	if (incrementEast) {
//		if (incrementEast == -1){
//			col = rand() % (size - 2*(word.length() -1));
//		} else {
//			col = rand() % (size - (word.length() -1));
//		}
//	} else {
//		if (incrementEast == -1){
//			col = rand() % (size + (word.length() -1));
//		} else {
//			col = rand() % size;
//		}
//	}
//
//	if (incrementSouth) {
//		if (incrementSouth == -1){
//			row = rand() % (size - 2*(word.length() -1));
//		} else {
//			row = rand() % (size - (word.length() -1));
//		}
//	} else {
//		if (incrementSouth == -1){
//			row =  rand() %(size + (word.length() -1));
//		} else {
//			row = rand() % size;
//		}
//	}

	int i, j;

	jumble = new char*[size];

	for (i=0; i<size; i++)
		jumble[i] = new char[size];
	for (i=0; i<size; i++) {
		for (j=0; j<size; j++) {
			jumble[i][j] = rand() % 26 + 'a';
		}
	}

	i = row;
	j = col;
	for (int count = 0; count < word.length(); count++) {
		jumble[i][j] = word[count];
		i += incrementSouth;
		j += incrementEast;
	}
}

JumblePuzzle::JumblePuzzle(const JumblePuzzle& original) {
	direction = original.getDirection();
	size = original.getSize();
	row = original.getRowPos();
	col = original.getColPos();

	if (original.getJumble()) {
		jumble = new char*[size];
		for (int i=0; i<size; i++)
			jumble[i] = new char[size];
		for (int i=0; i<size; i++) {
			for (int j=0; j<size; j++) {
				jumble[i][j] = original.getJumble()[i][j];
			}
		}
	}
}

JumblePuzzle::~JumblePuzzle() {
	for (int i=size-1; i>=0; i--) {
		delete[] jumble[i];
		jumble[i] = NULL;
	}
	delete[] jumble;
	jumble = NULL;
}


JumblePuzzle& JumblePuzzle::operator=(const JumblePuzzle& next) {
	if (this != &next) {
		for (int i=size-1; i>=0; i--) {
			delete[] jumble[i];
		}

		direction = next.getDirection();
		size = next.getSize();
		row = next.getRowPos();
		col = next.getColPos();

		delete[] jumble;

		if (next.getJumble()) {
			jumble = new char*[size];
			for (int i=0; i<size; i++)
				jumble[i] = new char[size];
			for (int i=0; i<size; i++) {
				for (int j=0; j<size; j++) {
					jumble[i][j] = next.getJumble()[i][j];
				}
			}
		}
	}
	return *this;
}


int JumblePuzzle::getSize() const {
	return size;
}

int JumblePuzzle::getRowPos() const {
	return row;
}

int JumblePuzzle::getColPos() const {
	return col;
}

charArrayPtr* JumblePuzzle::getJumble() const {
	charArrayPtr* jumbleDup = new char*[size];
	for (int i=0; i<size; i++)
		jumbleDup[i] = new char[size];
	for (int i=0; i<size; i++) {
		for (int j=0; j<size; j++) {
			jumbleDup[i][j] = jumble[i][j];
		}
	}
	return jumbleDup;
}

char JumblePuzzle::getDirection() const {
	return direction;
}

BadJumbleException::BadJumbleException(const string& errorMsg) {
	 message = errorMsg + '\n';
}

string BadJumbleException::what() const {
	return message;
}
