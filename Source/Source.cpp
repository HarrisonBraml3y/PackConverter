#include <iostream>
#include "Headers/Conversion.h"






int main() {

	std::map<std::string, std::string> BlocksMap;
	std::map<std::string, std::string> ItemsMap;

	std::filesystem::path BlocksSheetPath = "C:\\Users\\harri\\Desktop\\BlocksSheet.csv";
	//std::ifstream BlocksSheet = "C:\\Users\\harri\\Desktop\\BlocksMap";
	//BlocksSheet.open("C:\\Users\\harri\\Desktop\\BlocksMap");

	std::vector<std::string> ToRename;
	std::string OldDir = "C:\\Users\\harri\\Desktop\\Eum x Faith Mashup";
	std::string NewDir;




	PopulateMap(BlocksSheetPath, BlocksMap);
	FetchNames("C:\\Users\\harri\\Desktop\\Eum x Faith Mashup\\assets\\minecraft\\textures\\blocks", ToRename);
	Rename(ToRename, BlocksMap);




	return 0;
}


