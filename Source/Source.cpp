#include <iostream>
#include "Headers/Conversion.h"






int main(int argc, char* argv[]) {
	std::map<std::string, std::string> OldNew;

	std::filesystem::path BlocksSheetPath = "Blocks.csv";
	std::filesystem::path ItemsSheetPath = "Items.csv";

	std::vector<std::string> ToRename;
	std::filesystem::path NewDir;

	NewDir = CreateDir(argv[1]);
	PopulateDirMap(DirMap);

	PopulateMap(BlocksSheetPath, OldNew);	//figure out how to do this efficiently, re-using the same map but identifying which sheet to pull data from

	if (!argv[1]) {
		return 0;
	}
	IterateFolder(argv[1], argv[1], NewDir, ToRename, OldNew);

	std::cout << "Copmlete, your updated texture pack can be found at " << NewDir << std::endl;
	return 0;
}