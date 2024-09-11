#include <iostream>
#include "Headers/Conversion.h"






int main() {

	std::string OldPath;
	std::string NewPath;
	std::map<std::string, std::string> BlocksMap;
	std::map<std::string, std::string> ItemsMap;

	std::filesystem::path BlocksSheetPath = "C:\\Users\\harri\\Desktop\\BlocksSheet.csv";
	//std::ifstream BlocksSheet = "C:\\Users\\harri\\Desktop\\BlocksMap";
	//BlocksSheet.open("C:\\Users\\harri\\Desktop\\BlocksMap");

	std::vector<std::string> ToRename;
	std::string OldDir = "C:\\Users\\harri\\Desktop\\Eum x Faith Mashup";
	std::string NewDir;


	//CreateDir("C:\\Users\\harri\\Desktop\\TestPack");

	OldPath = "C:\\Users\\harri\\Desktop\\Eum x Faith Mashup";
	NewPath = OldPath + "NEW";

	PopulateMap(BlocksSheetPath, BlocksMap);

	
	MoveFiles("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks", "C:\\Users\\harri\\Desktop\\TestPackNEW\\assets\\minecraft\\textures\\block", ToRename);
	//FetchNames("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks", ToRename);
	Rename(ToRename, BlocksMap);


	

	return 0;
}


//Have pre-compiled list of old & new names in excel sheet, 
//Take in old-version folder, populate vector for old names from this folder
//Rename all vector indices from map of both old & new names
//Insert new names into new folder created by CreateDir()... Either move the files across to the new dir first then rename them, or rename them before they reach the new dir then move them

//for each file directory e.g. blocks, items, particles etc. temporarily save the directory path,
//"C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks"
//changing the file path to the updated file path of 
//"C:\\Users\\harri\\Desktop\\Eum x Faith MashupNEW\\assets\\minecraft\\textures\\block"
//this should be done in the 
