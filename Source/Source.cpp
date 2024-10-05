#include <iostream>
#include "Headers/Conversion.h"






int main(int argc, char* argv[]) {		//when complete change to int main(int argc, char *argv[]) for providing folder names in command line

	std::string OldPath;
	std::string NewPath;
	OldPath = "C:\\Users\\harri\\Desktop\\Eum x Faith Mashup";
	NewPath = OldPath + "NEW";

	std::map<std::string, std::string> BlocksMap;
	std::map<std::string, std::string> ItemsMap;
	std::map<std::string, std::string> NewMap;

	std::filesystem::path BlocksSheetPath = "C:\\Users\\harri\\Desktop\\BlocksSheet.csv";
	std::filesystem::path ItemsSheetPath = "C:\\Users\\harri\\Desktop\\ItemsSheet.csv";
	//std::ifstream BlocksSheet = "C:\\Users\\harri\\Desktop\\BlocksMap";
	//BlocksSheet.open("C:\\Users\\harri\\Desktop\\BlocksMap");

	std::vector<std::string> ToRename;
	std::string OldDir = "C:\\Users\\harri\\Desktop\\Eum x Faith Mashup";
	std::string NewDir;

	std::filesystem::directory_iterator DirIterator;

	
	CreateDir(argv[1]);


	//Loop through main subdirectories
	PopulateMap(BlocksSheetPath, NewMap);	//figure out how to do this efficiently, re-using the same map but identifying which sheet to pull data from


//	for (auto i : std::filesystem::directory_iterator("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup")) {
//		if (!i.is_directory()) {
//
//		}
//		else {
//			std::cout << "123" << std::endl;
//			//std::filesystem::path Entry = i;
//			//MoveFiles(Entry, NewDir, Names, NamesMap);
//			IterateFolder(i, NewDir, Names, NamesMap);
//		}
//	}


	
	IterateFolder("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets", "C:\\Users\\harri\\Desktop\\TestPackNEW", ToRename, NewMap);
	//MoveFiles("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks", "C:\\Users\\harri\\Desktop\\TestPackNEW\\assets\\minecraft\\textures\\block", ToRename, BlocksMap);
	//FetchNames("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks", ToRename);
	//Rename(ToRename, BlocksMap);


	

	return 0;
}

//try run the main functions in a loop (populate map, iterate folders etc.)