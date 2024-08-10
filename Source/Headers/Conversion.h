#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>


std::string FileIn;
std::string FileOut;

//std::string UpdateName() {
//}


std::vector<std::string> SplitString(const std::string& Line, char Delimiter) {	//possible unnecessary, Delimiter can be removed but it seems like both strings are put into once vec index
	std::vector<std::string> Tokens;
	std::string Token;
	std::istringstream TokenStream(Line);
	while (std::getline(TokenStream, Token, Delimiter)) {
		Tokens.push_back(Token);
	}
	return Tokens;
}


int PopulateMap(std::filesystem::path ReadFrom, std::map<std::string, std::string>& OldNew) {
	std::ifstream FileToRead(ReadFrom);


	if (!FileToRead.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return 0;
	}


	std::map<std::string, std::string>::iterator It;


	std::string Line;
	while (std::getline(FileToRead, Line)) {

		std::vector<std::string> Value = SplitString(Line, ','); // Assuming comma is the delimiter

		for (const auto& Token : Value) {
			std::cout << "\"" << Token << "\" ";
		}
		if (Value.size() == 2) {
			OldNew[Value[0]] = Value[1];
		}
		if (Value.size() == 1) { //case of no matching name value
			OldNew[Value[0]] = Value[0];

		}

	}





	//while (std::getline(FileToRead, Line)) {
	//	size_t DelimiterPos = Line.find('=');
	//	if (DelimiterPos != std::string::npos) {
	//		std::string key = Line.substr(0, DelimiterPos);
	//		std::string value = Line.substr(DelimiterPos + 1);
	//		OldNew[key] = value;
	//	}
	//	else {
	//		std::cerr << "Error: Line format is incorrect: " << Line << std::endl;
	//		return 1;
	//	}


	FileToRead.close();

	for (auto i : OldNew) {
		std::cout << i.first << " " << i.second << std::endl;
	}



	return 0;

	//	if (!std::getline(FileToRead, Key, ','))
	//		
	//
	//	if (!std::getline(FileToRead, Value, ','))
	//
	//	OldNew[Key] = Value;
	//}
	//



}



int Search() {

	return 0;
}

int Fetch() {	//fetch all files in directory,

	return 0;
}

int Rename(std::vector<std::string> FilesToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 





	return 0;
}