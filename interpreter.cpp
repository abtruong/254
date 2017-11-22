#include "interpreter.h"
#include "output.h"									// Will create a separate output header/cpp
#include <vector>

Interpreter::Interpreter() {
	binary = "";									//	Assign binary conversion from hex to bin cpp
	outMsg = "";									//	Output message
	wordCount = 0;									//	Track number of words from addresses
													// wordTotal = array.size() * 2					//	For future use to determine number of words
	i = 0;
	j = 0;
	bitMap1 = {};									// Use 2 bitMaps to separate binary conversion into 2 binary-converted fields, ex:
	bitMap2 = {};									// 1A022DFE ->  Map1 = 0001101000000010 and Map2 = 0010110111111110
}

Interpreter::~Interpreter() {}

string Interpreter::message(char* binary) {			// Final step in entire program - outputing after gathering binary information
	while (true) {
		if (wordCount == wordTotal)					// Currently useless, will update with further
			break;									// progress to wordTotal's array implementation

		for (i = 15, j = 0; i > -1; i--, j++) {
			bitMap1[i] = binary[j];
		}
		outMsg = outputConv(wordCount, bitMap1);	// Will create output.h/cpp to output this message
		wordCount++;

		for (i = 15, j = 0; i > -1; i--, j++) {
			bitMap2[i] = binary[j];
		}
		outMsg = outputConv(wordCount, bitMap2);	// Will create output.h/cpp to output this message
		wordCount++;

		break;										// Temporary placeholder to prevent test-crashing, delete if needed
	}
}

string Interpreter::outputConv(int wordCount, map<int, char> bitMap) {		// Output messages depending on word number, see assignment
	switch (wordCount) {
	case 0: {
		if (bitMap[14, 13] == '1')
			return "Rec_Ctrl = 3 (processing & recording)";
		else if (bitMap[14] == '1' && bitMap[13] == '0')
			return "Rec_Ctrl = 2 (no processing)";
		else if (bitMap[14, 13] == '0')
			return "Rec_Ctrl = 0 (no recording)";
		else
			return "Rec_Ctrl = 1 (unknown)";
		break;
	}
	case 1: {
		if (bitMap[15] == '1') {
			if (bitMap[14] == '1' && bitMap[13] == '0')
				return "Cmd_Type = 6 (Type C)";
			else if (bitMap[14] == '0' && bitMap[13] == '1')
				return "Cmd_Type = 5 (Type B)";
			else if (bitMap[14, 13] == '0')
				return "Cmd_Type = 4 (Type A)";
			else
				return "Cmd_Type = 7 (unknown)";
		}
		else if (bitMap[15] == '0')
			if (bitMap[14, 13] == '1')
				return "Cmd_Type = 3 (unknown)";
			else if (bitMap[14] == '1' && bitMap[13] == '0')
				return "Cmd_Type = 2 (unknown)";
			else if (bitMap[14] == '0' && bitMap[13] == '1')
				return "Cmd_Type = 1 (unknown)";
			else
				return "Cmd_Type = 0 (unknown)";
		break;
	}
	case 4: {
		if (bitMap[0] == '1')
			return "Rec_Rawr = 1 (enable)";
		else
			return "Rec_Rawr = 0 (disable)";
		break;
	}
	case 5: {
		int total = 0;
		for (int i = 0; i < 7; i++) {
			if (bitMap[i] == 1)
				total += (pow((bitMap[i] * 2), i));
		}
		return ("Cmd_ID = " + to_string(total));
	}
	case 10: {
		int total = 0;
		for (int i = 11; i < 16; i++) {
			if (bitMap[i] == 1)
				total += (pow((bitMap[i] * 2), (i - 11)));
		}
		return ("Num_Responses = " + to_string(total));
	}
	case 15: {
		if (bitMap[2] == '1')
			return "Reset_Enable = 1 (enable)";
		else
			return "Reset_Enable = 0 (disable)";
	}
	case 22: {
		if (bitMap[3] == '1')
			return "Direction = 1 (left)";
		else
			return "Direction = 0 (right)";
	}
	case 32: {
		int total = 0;
		for (int i = 0; i < 15; i++) {
			if (bitMap[i] == 1)
				total += (pow((bitMap[i] * 2), i));
		}
		return ("Num_Samples = " + to_string(total));
	}
	case 37: {
		if (bitMap[15] == '1')
			return "Parity = 1 (odd)";
		else
			return "Parity = 0 (even)";
	}
	case 38: {
		if (bitMap[14] == '1')
			return "Test = 1 (enable)";
		else
			return "Test = 0 (disable)";
	}
	case 40: {
		if (bitMap[7] == '1')
			return "Ctrl_Enable = 1 (enable)";
		else
			return "Ctrl_Enable = 0 (disable)";
	}
	case 41: {
		int total;
		for (int i = 8; i < 15; i++) {
			if (bitMap[i] == 1)
				total += (pow((bitMap[i] * 2), (i - 8)));
		}
		return ("Code = " + to_string(total));
	}
	default:
		break;
	}
}
