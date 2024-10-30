#include <iostream>
#include "Headers/Conversion.h"






int main(int argc, char* argv[]) {	
	std::map<std::string, std::string> BlocksMap;
	std::map<std::string, std::string> ItemsMap;
	std::map<std::string, std::string> OldNew;

	std::filesystem::path BlocksSheetPath = "C:\\Users\\harri\\Desktop\\BlocksSheet.csv";
	std::filesystem::path ItemsSheetPath = "C:\\Users\\harri\\Desktop\\ItemsSheet.csv";

	std::vector<std::string> ToRename;
	std::string OldDir = "C:\\Users\\harri\\Desktop\\Eum x Faith Mashup - Copy";
	std::filesystem::path NewDir;

	NewDir = CreateDir(argv[1]);
	std::cout << "NewDir: " << NewDir << std::endl;
	PopulateDirMap(DirMap);
	//Loop through main subdirectories
	PopulateMap(BlocksSheetPath, OldNew);	//figure out how to do this efficiently, re-using the same map but identifying which sheet to pull data from

	//IterateFolder(argv[1], argv[1], NewDir, ToRename, NewMap);	//NewDir needs to be corresponding directory of the original subdir
	IterateFolder(argv[1], argv[1], NewDir, ToRename, OldNew);




//	for (auto i : std::filesystem::directory_iterator(argv[1])) {
//		if (!i.is_directory()) {
//
//		}
//		else {
//			std::cout << "123" << std::endl;
//			//std::filesystem::path Entry = i;
//			//MoveFiles(Entry, NewDir, Names, NamesMap);
//			IterateFolder(i, NewDir, ToRename, NewMap);
//		}
//	}


	
	//IterateFolder("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets", "C:\\Users\\harri\\Desktop\\TestPackNEW", ToRename, NewMap);
	//MoveFiles("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks", "C:\\Users\\harri\\Desktop\\TestPackNEW\\assets\\minecraft\\textures\\block", ToRename, BlocksMap);
	//FetchNames("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks", ToRename);
	//Rename(ToRename, BlocksMap);
	std::cout << "Copmlete, your updated texture pack can be found at " << NewDir << std::endl;
	return 0;
}