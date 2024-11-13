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

//Fill map of updated directories e.g. assets/minecraft/mcpatcher -> assets/minecraft/optifine
//loop through an old directory, 
std::map<std::filesystem::path, std::filesystem::path> DirMap;
 std::map<std::filesystem::path, std::filesystem::path> PopulateDirMap(std::map<std::filesystem::path, std::filesystem::path>& DirMap) {
	DirMap[""] = "assets\\minecraft\\lang";
	DirMap["assets\\minecraft\\mcpatcher"] = "assets\\minecraft\\optifine";
	DirMap["assets\\minecraft\\font"] = "assets\\minecraft\\optifine\\font";
	DirMap["assets\\minecraft\\mcpatcher\\colormap"] = "assets\\minecraft\\optifine\\colormap";
	DirMap["assets\\minecraft\\mcpatcher\\ctm"] = "assets\\minecraft\\optifine\\ctm";
	DirMap["assets\\minecraft\\mcpatcher\\ctm\\glass"] = "assets\\minecraft\\optifine\\ctm\\glass";
	DirMap["assets\\minecraft\\mcpatcher\\lightmap"] = "assets\\minecraft\\optifine\\lightmap";
	DirMap["assets\\minecraft\\mcpatcher\\mob"] = "assets\\minecraft\\optifine\\mob";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\cow"] = "assets\\minecraft\\optifine\\mob\\cow";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\creeper"] = "assets\\minecraft\\optifine\\mob\\creeper";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\enderman"] = "assets\\minecraft\\optifine\\mob\\enderman";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\ghast"] = "assets\\minecraft\\optifine\\mob\\ghast";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\pig"] = "assets\\minecraft\\optifine\\mob\\pig";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\skeleton"] = "assets\\minecraft\\optifine\\mob\\skeleton";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\slime"] = "assets\\minecraft\\optifine\\mob\\slime";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\spider"] = "assets\\minecraft\\optifine\\mob\\spider";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\wolf"] = "assets\\minecraft\\optifine\\mob\\wolf";
	DirMap["assets\\minecraft\\mcpatcher\\mob\\zombie"] = "assets\\minecraft\\optifine\\mob\\zombie";
	DirMap["assets\\minecraft\\mcpatcher\\sky"] = "assets\\minecraft\\optifine\\sky";
	DirMap["assets\\minecraft\\mcpatcher\\sky\\world0"] = "assets\\minecraft\\optifine\\sky\\world0";
	DirMap[""] = "assets\\minecraft\\texts";
	
	//DirMap["assets\minecraft\textures\entity\cat"] = "assets\minecraft\textures\entity\cat";
	//DirMap["assets\minecraft\textures\entity\chest"] = "assets\minecraft\textures\entity\chest";
	//DirMap["assets\minecraft\textures\entity\cow"] = "assets\minecraft\textures\entity\cow";
	//DirMap["assets\minecraft\textures\entity\creeper"] = "assets\minecraft\textures\entity\creeper";
	//DirMap["assets\minecraft\textures\entity\endercrystal"] = "assets\minecraft\textures\entity\endercrystal";
	//DirMap["assets\minecraft\textures\entity\enderdragon"] = "assets\minecraft\textures\entity\enderdragon";
	//DirMap["assets\minecraft\textures\entity\enderman"] = "assets\minecraft\textures\entity\enderman";
	//DirMap["assets\minecraft\textures\entity\ghast"] = "assets\minecraft\textures\entity\ghast";
	//DirMap["assets\minecraft\textures\entity\horse"] = "assets\minecraft\textures\entity\horse";
	//DirMap["assets\minecraft\textures\entity\pigsheep"] = "assets\minecraft\textures\entity\pigsheep";
	//DirMap["assets\minecraft\textures\entity\skeleton"] = "assets\minecraft\textures\entity\skeleton";
	//DirMap["assets\minecraft\textures\entity\slime"] = "assets\minecraft\textures\entity\slime";
	//DirMap["assets\minecraft\textures\entity\spider"] = "assets\minecraft\textures\entity\spider";
	//DirMap["assets\minecraft\textures\entity\villager"] = "assets\minecraft\textures\entity\villager";
	//DirMap["assets\minecraft\textures\entity\wither"] = "assets\minecraft\textures\entity\wither";
	//DirMap["assets\minecraft\textures\entity\wolf"] = "assets\minecraft\textures\entity\wolf";
	//DirMap["assets\minecraft\textures\entity\zombie"] = "assets\minecraft\textures\entity\zombie";
	//DirMap["assets\minecraft\textures\environment"] = "assets\minecraft\textures\environment";
	//DirMap["assets\minecraft\textures\font"] = "assets\minecraft\textures\font";
	//DirMap["assets\minecraft\textures\gui"] = "assets\minecraft\textures\gui";
	//DirMap["assets\minecraft\textures\gui\achivement"] = "assets\minecraft\textures\gui\achivement";
	//DirMap["assets\minecraft\textures\gui\container"] = "assets\minecraft\textures\gui\container";
	//DirMap["assets\minecraft\textures\gui\container\creative_inventory"] = "assets\minecraft\textures\gui\container\creative_inventory";
	DirMap["assets\\minecraft\\textures\\blocks"] = "assets\\minecraft\\textures\\block";
	DirMap["assets\\minecraft\\textures\\items"] = "assets\\minecraft\\textures\\item";
	DirMap["assets\\minecraft\\textures\\font"] = "assets\\minecraft\\textures\\font";

	//DirMap["assets\minecraft\textures\map"] = "assets\minecraft\textures\map";
	//DirMap["assets\minecraft\textures\misc"] = "assets\minecraft\textures\misc";
	DirMap[""] = "assets\\minecraft\\textures\\mob_effect";
	//DirMap["assets\minecraft\textures\models"] = "assets\minecraft\textures\models";
	//DirMap["assets\minecraft\textures\models\armor"] = "assets\minecraft\textures\models\armor";
	//DirMap["assets\minecraft\textures\painting"] = "assets\minecraft\textures\painting";
	//DirMap["assets\minecraft\textures\particle"] = "assets\minecraft\textures\particle";
	return DirMap;
}


int Search() {

	return 0;
}


//Store old path and store new path, in order to move the newly-named files to new dir, change old path to new path, which involves excluding the file name which has been changed, so that only the file path is left to be changed
int Rename(std::vector<std::string>& ToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 
	std::cout << "Rename()" << std::endl;													//Afterwards, rename the full file path to the new file path
	std::cout << "ToRename: " << ToRename.size() << std::endl;
	for (auto i : ToRename) {
		std::cout << i << std::endl;
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
	
//also remember to change the file directory of the original file to the newly created directory
//, after it has been renamed
	return 0;
}
std::string RenameFilename(std::string& ToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 
	std::cout << "RenameFilename()" << std::endl;													//Afterwards, rename the full file path to the new file path
	std::cout << "Renaming " << ToRename << std::endl;

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
	return ToRename;
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



//Doesn't account for files which may be in different directories post-update or renamed directories
void MoveFiles(std::filesystem::path Master, std::filesystem::path OldDir, std::filesystem::path NewDir, std::vector<std::string>& Names, std::map<std::string, std::string> NamesMap) {	//call this function for each directory in the folder

	std::filesystem::path OldPath;
	std::filesystem::path NewPath;
	//add check if it's not a file but a directory
	for (auto& Entry : std::filesystem::directory_iterator(OldDir)) {
		OldPath = Entry.path();
		std::string Temp = Entry.path().string();
		std::string FileName = Temp.substr(Temp.find_last_of("/\\") + 1);
		std::cout << "Filename retrieved:" << FileName << std::endl;


		RenameFilename(FileName, NamesMap);
		//std::cout << "OldPath:" << OldPath << std::endl;
		//std::cout << "OldPath parent:" << OldPath.parent_path() << std::endl;
		//std::cout << "Master:" << Master << std::endl;

		std::filesystem::path RelativePath = std::filesystem::relative(OldPath.parent_path(), Master);	//if old and new relative path is the same, continue, if different then try and fix it with DirMap
		if (DirMap.find(RelativePath) != DirMap.end()) {
			std::cout << "Relative path not required - path stayed the same." << std::endl;
			RelativePath = DirMap[RelativePath];
			std::cout << "Relative Path renamed to " << DirMap[RelativePath] << std::endl;

		}

		NewPath = NewDir / RelativePath / FileName;
		Names.push_back(Entry.path().filename().string());

		if (!std::filesystem::exists(NewPath)) {
			std::filesystem::rename(OldPath, NewPath);  
			std::cout << OldPath << " Changed to: " << NewPath << std::endl;
		}
		else {
			std::cout << NewPath << " Already exists." << std::endl;
		}
	}
	return;
}

//void MoveFiles(std::filesystem::path OldDir, std::filesystem::path NewDir, std::vector<std::string>& Names, std::map<std::string, std::string> NamesMap) {	//call this function for each directory in the folder
//	std::string OldPath;
//	std::filesystem::path NewPath;
//	std::filesystem::path Master = OldDir;
//	//add check if it's not a file but a directory
//	for (auto& Entry : std::filesystem::directory_iterator(OldDir)) {
//		OldPath = Entry.path().string();
//		std::string FileName = OldPath.substr(OldPath.find_last_of("/\\") + 1);
//		std::cout << "Temp: " << FileName << std::endl;
//
//		RenameSingle(FileName, NamesMap);
//		std::cout << "OldDir:" << OldDir << std::endl;
//		std::cout << "OldDir parent:" << OldDir.parent_path() << std::endl;
//		std::cout << "Master:" << Master << std::endl;
//		std::filesystem::path RelativePath = std::filesystem::relative(OldDir.parent_path(), Master);
//		std::cout << "NewDir:" << NewDir << std::endl;
//		std::cout << "RelativePath:" << RelativePath << std::endl;
//		std::cout << "FileName:" << FileName << std::endl;
//
//		NewPath = NewDir / RelativePath / FileName;
//		Names.push_back(Entry.path().filename().string());
//
//		std::cout << "NewPath: " << NewPath << std::endl;
//		std::filesystem::rename(OldPath, NewPath);
//		std::cout << OldPath << " Changed to: " << NewPath << std::endl;
//	}
//	//reconstruct path with renamed names
//
//	return;
//}

void IterateFolder(std::filesystem::path Master, std::filesystem::path Folder, std::filesystem::path NewDir, std::vector<std::string> Names, std::map<std::string, std::string> NamesMap) {
	
	std::cout << "FOLDER:" << Folder << std::endl;
	for (auto& i : std::filesystem::directory_iterator(Folder)) {	
		std::cout << "SubDir:" << i << std::endl;

		if (!i.is_directory()) {
			MoveFiles(Master, Folder, NewDir, Names, NamesMap);
		}
		else {
			//std::filesystem::path Entry = i;
			//MoveFiles(Entry, NewDir, Names, NamesMap);
			IterateFolder(Master, i, NewDir, Names, NamesMap);
		}
	}
}



std::filesystem::path CreateDir(std::string OldDir) {
	std::filesystem::path NewDir = OldDir + "NEW";
	std::map<std::string, std::string> FolderMap;
	std::string assetsDir = "assets";
	std::string minecraftDir = "minecraft";
	std::vector<std::string> minecraftSubDirs = { "textures", "texts", "lang", "optifine" };
	std::vector<std::string> texturesSubDirs = { "block", "font", "gui", "item", "misc", "models", "particle", "entity", "environment", "map", "mob_effects", "painting" };
	std::vector<std::string> optifineSubDirs = { "font", "lightmap", "ctm", "colormap", "mob", "sky" };
	std::vector<std::string> entitySubDirs = { "cat", "chest", "cow", "creeper", "endercrystal", "enderdragon", "enderman", "ghast", "horse", "pig", "sheep", "skeleton", "slime", "spider", "villager", "wither", "wolf", "zombie"};
	std::vector<std::string> mobSubDirs = { "cat", "cow", "creeper", "enderman", "ghast", "pig", "skeleton", "slime", "spider", "wolf", "zombie" };
	std::vector<std::string> guiSubDirs = { "achievement", "container", "title"};

	
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

					if (i == "entity") {
						for (auto i : entitySubDirs) {
							std::filesystem::path SubDirs = NewFolderPath / "entity" / i;
							if (!std::filesystem::exists(SubDirs)) {
								std::filesystem::create_directory(SubDirs);
								std::cout << "Created folder: " << SubDirs << std::endl;
							}
							else {
								std::cout << "Folder already exists: " << SubDirs << std::endl;
							}
						}
					}
					if (i == "gui") {
						for (auto i : guiSubDirs) {
							std::cout << i << std::endl;
							std::filesystem::path SubDirs = NewFolderPath / "gui" / i;
							std::cout << NewFolderPath << std::endl;
							if (!std::filesystem::exists(SubDirs)) {
								std::filesystem::create_directory(SubDirs);
								std::cout << "Created folder: " << SubDirs << std::endl;
							}
							if (i == "container") {
								if (!std::filesystem::exists("conatainer\\creative_inventory")) {
									std::filesystem::create_directory(SubDirs / "creative_inventory");
									std::cout << "Created folder: " << SubDirs / "creative_inventory" << std::endl;
								}
							}
							if (i == "title") {
								if (!std::filesystem::exists("conatainer\\background")) {
									std::filesystem::create_directory(SubDirs / "background");
									std::cout << "Created folder: " << SubDirs / "background" << std::endl;
								}
							}
							else {
								std::cout << "Folder already exists: " << SubDirs << std::endl;
							}
						}
					}
					if (i == "models") {
						if (!std::filesystem::exists("models\\armor")) {
							std::filesystem::create_directory(NewFolderPath / "models" / "armor");
							std::cout << "Created folder: " << "models\\armor" << std::endl;
						}
						else {
							std::cout << "Folder already exists: " << "models\\armor" << std::endl;
						}
					}
				}
			}
			if (i == "optifine") {
				for (auto i : optifineSubDirs) {
					std::filesystem::path SubDirs = NewFolderPath / i;
					if (!std::filesystem::exists(SubDirs)) {
						std::filesystem::create_directory(SubDirs);
						std::cout << "Created folder: " << SubDirs << std::endl;
					}
					else {
						std::cout << "Folder already exists: " << SubDirs << std::endl;
					}
					if (i == "mob") {
						for (auto i : mobSubDirs) {  
							std::filesystem::path SubDirs = NewFolderPath / "mob" / i;
							if (!std::filesystem::exists(SubDirs)) {
								std::filesystem::create_directory(SubDirs);
								std::cout << "Created folder: " << SubDirs << std::endl;
							}
							else {
								std::cout << "Folder already exists: " << SubDirs << std::endl;
							}
						}
					}
					if (i == "sky") {
						if (!std::filesystem::exists(NewFolderPath / "sky" / "world0")) {
							std::filesystem::create_directory(NewFolderPath / "sky" / "world0");
							std::cout << "Created folder: " << NewFolderPath / "sky" / "world0" << std::endl;
						}
						else {
							std::cout << "Folder already exists: " << NewFolderPath / "sky" / "world0" << std::endl;
						}
					}
					if (i == "ctm") {
						if (!std::filesystem::exists(NewFolderPath / "ctm" / "glass")) {
							std::filesystem::create_directory(NewFolderPath / "ctm" / "glass");
							std::cout << "Created folder: " << NewFolderPath / "ctm" / "glass" << std::endl;
						}
						else {
							std::cout << "Folder already exists: " << NewFolderPath / "ctm" / "glass" << std::endl;
						}
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


void RewriteMeta(std::string FilePath) {
	std::ofstream OutFile(FilePath);
	OutFile
		<< "{\n"
		<< "  \"pack\": {\n"
		<< "    \"pack_format\": 15,\n"
		<< "    \"description\": \"By denqy\"\n"
		<< "  },\n"
		<< "  \"meta\": {\n"
		<< "    \"game_version\": \"1.20\"\n"
		<< "  }\n"
		<< "}\n";
	OutFile.close();
}







