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
	std::cout << "PopulateMap()" << std::endl;
	std::ifstream FileToRead(ReadFrom);


	if (!FileToRead.is_open()) {
		std::cout << "Error opening file" << std::endl;
		return 0;
	}


	std::map<std::string, std::string>::iterator It;


	std::string Line;
	while (std::getline(FileToRead, Line)) {

		std::vector<std::string> Value = SplitString(Line, ','); // Assuming comma is the delimiter

//		for (const auto& Token : Value) {
//			std::cout << "\"" << Token << "\" ";
//		}
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
}



int Search() {

	return 0;
}



int Rename(std::vector<std::string>& ToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 
	std::cout << "Rename()" << std::endl;
	std::cout << "ToRename size: " << ToRename.size() << std::endl;
	for (auto a : ToRename) {	//find key in Names to match a
		if (Names.find(a) == Names.end()) {
			//if a not found
			//deal with errors, either no matching key or no value

		}
		else {
			
		}
	}

	for (int i = 0; i < ToRename.size(); i++) {
		if (Names.find(ToRename[i]) == Names.end()) {
			std::cout << "No key found" << std::endl;
		}
		else {
			std::cout << ToRename[i] << " Renamed to ";
			ToRename[i] = Names[ToRename[i]]; 
			std::cout << ToRename[i] << std::endl;
		}
	}



	return 0;
}


int ReWrite(std::vector<std::string> NewNames, std::filesystem::path Dir) {

	for (auto i : NewNames) {
		//append i to Dir
		Dir += "\\" + i;
		std::cout << "New file name: " << Dir << std::endl;
		std::filesystem::rename(std::string(i), std::string());
	}

}

int FetchNames(std::string Path, std::vector<std::string>& Names) {	//fetch all files in directory,
//while not null, fetch file name
	std::cout << "FetchNames()" << std::endl;
	for (auto& Entry : std::filesystem::directory_iterator(Path)) {	//populate vector of file names
		Names.push_back(Entry.path().filename().string());
	}
	for (auto i : Names) {
		std::cout << "Added: " << i << std::endl;
	}
	//rename all files to new names
	//Rename(Names, UpdatedNames);


	return 1;
}

std::filesystem::path CreateDir(std::string OldDir) {
	std::filesystem::path NewDir = OldDir + "NEW";
	std::map<std::string, std::string> FolderMap = {};
	std::string assets = "assets";
	std::string minecraft = "minecraft";
	std::vector<std::string> minecraftFolders = { "textures", "texts", "lang", "optifine" };
	std::vector<std::string> texturesFolders = { "block", "font", "gui", "item", "misc", "models", "particle", "entity", "environment", "map", "mob_effects", "painting" };
	
	//populate folder map
	std::filesystem::path assetsPath = NewDir / assets;
	if (!std::filesystem::exists(assetsPath)) {
		std::filesystem::create_directory(assetsPath);
	}
	
	std::filesystem::path minecraftPath = NewDir / minecraft;
	if (std::filesystem::exists(minecraftPath)) {
		std::filesystem::create_directory(minecraftPath);
	}

	for (auto i : minecraftFolders) {
		std::filesystem::path NewFolderPath = minecraftPath / i;
		if (!std::filesystem::exists(NewFolderPath)) {
			std::filesystem::create_directory(NewFolderPath);
			std::cout << "Created folder: " << NewFolderPath << std::endl;
		}
		else {
			std::cout << "Folder already exists: " << NewFolderPath << std::endl;
		}
	}


	for (auto i : texturesFolders) {
		std::filesystem::path NewFolderPath = NewDir / i;
		if (!std::filesystem::exists(NewFolderPath)) {
			std::filesystem::create_directory(NewFolderPath);
			std::cout << "Created folder: " << NewFolderPath << std::endl;
		}
		else {
			std::cout << "Folder already exists: " << NewFolderPath << std::endl;
		}
	}
	return NewDir;
}