#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>


struct CurrentDir {
	//hold current directory parameters such as path etc. 
};

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


int PopulateMap(std::filesystem::path ReadFrom, std::map<std::string, std::string>& OldNew) {	//Map old & new names of folder contents, read from pre compiled excel sheet
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
}



int Search() {

	return 0;
}


//Store old path and store new path, in order to move the newly-named files to new dir, change old path to new path, which involves excluding the file name which has been changed, so that only the file path is left to be changed
int Rename(std::vector<std::string>& ToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 
	std::cout << "Rename()" << std::endl;													//Afterwards, rename the full file path to the new file path
	std::cout << "ToRename size: " << ToRename.size() << std::endl;

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
	
//also remember to change the file directory of the original file to the newly created directory
//, after it has been renamed
	return 0;
}
int RenameSingle(std::string& ToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 
	std::cout << "Rename()" << std::endl;													//Afterwards, rename the full file path to the new file path
	std::cout << "ToRename size: " << ToRename.size() << std::endl;


		if (Names.find(ToRename) == Names.end()) {
			std::cout << "No key found" << std::endl;
		}
		else {
			std::cout << ToRename << " Renamed to ";
			ToRename = Names[ToRename];
			std::cout << ToRename << std::endl;
		}
	

	//also remember to change the file directory of the original file to the newly created directory
	//, after it has been renamed
	return 0;
}

int FetchNames(std::string Path, std::vector<std::string>& Paths) {	//fetch all files in directory,
	std::cout << "FetchNames()" << std::endl;
	for (auto& Entry : std::filesystem::directory_iterator(Path)) {	
		Paths.push_back(Entry.path().string());
		//Names.push_back(Entry.path().filename().string());
	}
	for (auto i : Paths) {
		std::cout << "Added: " << i << std::endl;
	}

	return 1;
}

void IterateFolder(std::filesystem::path Folder, std::filesystem::path NewDir, std::vector<std::string> Names, std::map<std::string, std::string> NamesMap) {
	
	MoveFiles(Folder, NewDir, Names, NamesMap); 

	for (auto i : std::filesystem::directory_iterator(Folder)) {
		if (!i.is_directory()) {
			
		}
		else {
			std::cout << i << std::endl;
			//std::filesystem::path Entry = i;
			//MoveFiles(Entry, NewDir, Names, NamesMap);
			IterateFolder(i, NewDir, Names, NamesMap);
		}
	}
}

void MoveFiles(std::filesystem::path OldDir, std::filesystem::path NewDir, std::vector<std::string>& Names, std::map<std::string, std::string> NamesMap){	//call this function for each directory in the folder
	std::string OldPath;
	std::filesystem::path NewPath;
	std::string TempPath;

	

	for (auto& Entry : std::filesystem::directory_iterator(OldDir)) {
		OldPath = Entry.path().string();
		std::string Temp = OldPath.substr(OldPath.find_last_of("/\\") + 1);
		std::cout << "Temp: " << Temp << std::endl;	
		RenameSingle(Temp, NamesMap);
		NewPath = NewDir / Temp;
		Names.push_back(Entry.path().filename().string());

		std::cout << "NewPath: " << NewPath << std::endl;
		std::filesystem::rename(OldPath, NewPath);
		std::cout << OldPath << " Changed to: " << NewPath << std::endl;
	}
	//reconstruct path with renamed names

	return;
}

std::filesystem::path CreateDir(std::string OldDir) {
	std::filesystem::path NewDir = OldDir + "NEW";
	std::map<std::string, std::string> FolderMap;
	std::string assetsDir = "assets";
	std::string minecraftDir = "minecraft";
	std::vector<std::string> minecraftSubDirs = { "textures", "texts", "lang", "optifine" };
	std::vector<std::string> texturesSubDirs = { "block", "font", "gui", "item", "misc", "models", "particle", "entity", "environment", "map", "mob_effects", "painting" };
	
	if (!std::filesystem::exists(NewDir)) {	//NewDir hasn't been created yet, thus NewDir/assets cannot exist
		std::filesystem::create_directory(NewDir);
	}

	//populate folder map
	std::cout << NewDir << std::endl;
	std::filesystem::path assetsPath = NewDir / assetsDir;
	std::cout << assetsPath << std::endl;
	if (!std::filesystem::exists(assetsPath)) {	//NewDir hasn't been created yet, thus NewDir/assets cannot exist
		try {
			std::filesystem::create_directory(assetsPath);
		}
		catch (const std::filesystem::filesystem_error& e) {
			std::cerr << "Filesystem error: " << e.what() << std::endl;
		}
	}

	
	std::filesystem::path minecraftPath = assetsPath / minecraftDir;
	if (!std::filesystem::exists(minecraftPath)) {
		std::filesystem::create_directory(minecraftPath);
	}

	for (auto i : minecraftSubDirs) {
		std::filesystem::path NewFolderPath = minecraftPath / i;
		if (!std::filesystem::exists(NewFolderPath)) {
			std::filesystem::create_directory(NewFolderPath);
			std::cout << "Created folder: " << NewFolderPath << std::endl;

			if (i == "textures") {
				for (auto i : texturesSubDirs) {	//when complete, go back to minecraftSubDirs loop
					std::filesystem::path SubDirs = NewFolderPath / i;
					if (!std::filesystem::exists(SubDirs)) {
						std::filesystem::create_directory(SubDirs);
						std::cout << "Created folder: " << SubDirs << std::endl;
					}
					else {
						std::cout << "Folder already exists: " << SubDirs << std::endl;
					}
				}
			}

		}
		else {
			std::cout << "Folder already exists: "  << NewFolderPath << std::endl;
		}
	}




	return NewDir;
}

//void PopulateDirs(std::filesystem::path, std::vector<std::string> Names){		//copy files from initial folder, with newly-updated names and 
//	if (Names.size() <= 0) {
//		return;
//	}
//	
//	for (auto i : Names) {
//		std::filesystem::create_directories		//may not even be a directory, as it isn't a folder. Try 
//	}
//
//
//	return;
//}




//SpriteSheetSplitter