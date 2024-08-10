#include <iostream>
#include "Headers/Conversion.h"






int main() {

	std::map<std::string, std::string> BlocksMap;
	std::map<std::string, std::string> ItemsMap;

	std::filesystem::path BlocksSheetPath = "C:\\Users\\harri\\Desktop\\BlocksMap.csv";
	//std::ifstream BlocksSheet = "C:\\Users\\harri\\Desktop\\BlocksMap";
	//BlocksSheet.open("C:\\Users\\harri\\Desktop\\BlocksMap");



	PopulateMap(BlocksSheetPath, BlocksMap);




	return 0;
}
