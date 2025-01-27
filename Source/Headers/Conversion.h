#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <map>
#include "Dependencies/opencv2/opencv.hpp"




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

	FileToRead.close();

	return 0;
}

 
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

	DirMap["assets\\minecraft\\textures\\blocks"] = "assets\\minecraft\\textures\\block";
	DirMap["assets\\minecraft\\textures\\items"] = "assets\\minecraft\\textures\\item";
	DirMap["assets\\minecraft\\textures\\font"] = "assets\\minecraft\\textures\\font";
	DirMap[""] = "assets\\minecraft\\textures\\mob_effect";

	return DirMap;
}


int Search() {

	return 0;
}


//Store old path and store new path, in order to move the newly-named files to new dir, change old path to new path, which involves excluding the file name which has been changed, so that only the file path is left to be changed
int Rename(std::vector<std::string>& ToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 



	for (int i = 0; i < ToRename.size(); i++) {
		if (Names.find(ToRename[i]) == Names.end()) {
		}
		else {
			ToRename[i] = Names[ToRename[i]]; 
		}
	}
	
//also remember to change the file directory of the original file to the newly created directory
//, after it has been renamed
	return 0;
}
std::string RenameFilename(std::string& ToRename, std::map<std::string, std::string> Names) {	//Put all to-be-renamed names in vector, match them with first value of Names map, 

		if (Names.find(ToRename) == Names.end()) {
		}
		else {
			ToRename = Names[ToRename];
		}
	

	//also remember to change the file directory of the original file to the newly created directory
	//, after it has been renamed
	return ToRename;
}

int FetchNames(std::string Path, std::vector<std::string>& Paths) {	//fetch all files in directory,
	for (auto& Entry : std::filesystem::directory_iterator(Path)) {	
		Paths.push_back(Entry.path().string());
		//Names.push_back(Entry.path().filename().string());
	}

	return 1;
}



void MoveFiles(std::filesystem::path Master, std::filesystem::path OldDir, std::filesystem::path NewDir, std::vector<std::string>& Names, std::map<std::string, std::string> NamesMap) {	//call this function for each directory in the folder

	std::filesystem::path OldPath;
	std::filesystem::path NewPath;
	//add check if it's not a file but a directory
	for (auto& Entry : std::filesystem::directory_iterator(OldDir)) {
		OldPath = Entry.path();
		std::string Temp = Entry.path().string();
		std::string FileName = Temp.substr(Temp.find_last_of("/\\") + 1);

		RenameFilename(FileName, NamesMap);

		std::filesystem::path RelativePath = std::filesystem::relative(OldPath.parent_path(), Master);	//if old and new relative path is the same, continue, if different then try and fix it with DirMap
		if (DirMap.find(RelativePath) != DirMap.end()) {
			RelativePath = DirMap[RelativePath];
		}

		NewPath = NewDir / RelativePath / FileName;
		Names.push_back(Entry.path().filename().string());

		if (!std::filesystem::exists(NewPath)) {
			std::filesystem::rename(OldPath, NewPath);  
		}
		else {
		}
	}
	return;
}



//Particle Splitter - Cuts each particle from the one.png in the old version & creates a new.png for each particle.

void CutParticle(std::filesystem::path & ImagePath, std::filesystem::path & OutputPath) {

	std::string Input;
	std::string Output;
	Input = ImagePath.string();
	Output = OutputPath.string();


	cv::Mat Image = cv::imread(Input, cv::IMREAD_UNCHANGED);
	cv::Mat ImageRGBA;
//	cv::imshow("Original", Image);

	cv::cvtColor(Image, ImageRGBA, cv::COLOR_BGR2BGRA);
	if (Image.empty()) {
		std::cout << "Error opening Image" << std::endl;
		return;
	}

	//Greyscale the image
	cv::Mat Grey;
	cv::cvtColor(Image, Grey, cv::COLOR_BGR2GRAY);

	//Intensified greyscale to black & white
	cv::Mat Binary;
	cv::threshold(Grey, Binary, 1, 255, cv::THRESH_BINARY);

	cv::Mat Labels, Stats, Centroids;
	int NumComponents = cv::connectedComponentsWithStats(Binary, Labels, Stats, Centroids, 8, CV_32S);

	for (int i = 0; i < NumComponents; i++) {
		int x = Stats.at<int>(i, cv::CC_STAT_LEFT);
		int y = Stats.at<int>(i, cv::CC_STAT_TOP);
		int Width = Stats.at<int>(i, cv::CC_STAT_WIDTH);
		int Height = Stats.at<int>(i, cv::CC_STAT_HEIGHT);

		cv::Rect BoundingBox(x, y, Width, Height);
		cv::Mat Particle = Image(BoundingBox);

		cv::Mat SpriteMask = Binary(BoundingBox);

		cv::Mat ParticleRGBA(Particle.rows, Particle.cols, CV_8UC4);
		Particle.copyTo(ParticleRGBA, SpriteMask);

		cv::cvtColor(Particle, ParticleRGBA, cv::COLOR_BGR2BGRA);
		for (int row = 0; row < ParticleRGBA.rows; ++row) {               //rows & columns represent 
			for (int col = 0; col < ParticleRGBA.cols; ++col) {
				cv::Vec4b& pixel = ParticleRGBA.at<cv::Vec4b>(row, col);
				if (SpriteMask.at<uchar>(row, col) == 0) {
					pixel[3] = 0; // Set alpha to 0 for transparent pixels
				}
				else {
					pixel[3] = 255; // Set alpha to 255 for visible pixels
				}
			}
		}

		std::string OutputPath = Output + "\\" + std::to_string(i) + ".png";

		cv::imwrite(OutputPath, Particle);
	}

	return;
}


void IterateFolder(std::filesystem::path Master, std::filesystem::path Folder, std::filesystem::path NewDir, std::vector<std::string> Names, std::map<std::string, std::string> NamesMap) {
	
	if (Folder.filename() == "particle") {
		std::string ImageIn = Folder.string() + "\\particles.png";
		std::filesystem::path ImagePath = ImageIn;

		CutParticle(ImagePath, Folder);	//output should should be relative path of new master dir
		MoveFiles(Master, Folder, NewDir, Names, NamesMap);
	}
	for (auto& i : std::filesystem::directory_iterator(Folder)) {	

		if (!i.is_directory()) {
			MoveFiles(Master, Folder, NewDir, Names, NamesMap);
		}
		else {
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
	std::filesystem::path assetsPath = NewDir / assetsDir;
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

			if (i == "textures") {
				for (auto i : texturesSubDirs) {	//when complete, go back to minecraftSubDirs loop
					std::filesystem::path SubDirs = NewFolderPath / i;
					if (!std::filesystem::exists(SubDirs)) {
						std::filesystem::create_directory(SubDirs);
					}

					else {
					}

					if (i == "entity") {
						for (auto i : entitySubDirs) {
							std::filesystem::path SubDirs = NewFolderPath / "entity" / i;
							if (!std::filesystem::exists(SubDirs)) {
								std::filesystem::create_directory(SubDirs);
							}
							else {
							}
						}
					}
					if (i == "gui") {
						for (auto i : guiSubDirs) {
							std::filesystem::path SubDirs = NewFolderPath / "gui" / i;
							if (!std::filesystem::exists(SubDirs)) {
								std::filesystem::create_directory(SubDirs);
							}
							if (i == "container") {
								if (!std::filesystem::exists("conatainer\\creative_inventory")) {
									std::filesystem::create_directory(SubDirs / "creative_inventory");
								}
							}
							if (i == "title") {
								if (!std::filesystem::exists("conatainer\\background")) {
									std::filesystem::create_directory(SubDirs / "background");
								}
							}
							else {
							}
						}
					}
					if (i == "models") {
						if (!std::filesystem::exists("models\\armor")) {
							std::filesystem::create_directory(NewFolderPath / "models" / "armor");
						}
						else {
						}
					}
				}
			}
			if (i == "optifine") {
				for (auto i : optifineSubDirs) {
					std::filesystem::path SubDirs = NewFolderPath / i;
					if (!std::filesystem::exists(SubDirs)) {
						std::filesystem::create_directory(SubDirs);
					}
					else {
					}
					if (i == "mob") {
						for (auto i : mobSubDirs) {  
							std::filesystem::path SubDirs = NewFolderPath / "mob" / i;
							if (!std::filesystem::exists(SubDirs)) {
								std::filesystem::create_directory(SubDirs);
							}
							else {
							}
						}
					}
					if (i == "sky") {
						if (!std::filesystem::exists(NewFolderPath / "sky" / "world0")) {
							std::filesystem::create_directory(NewFolderPath / "sky" / "world0");
						}
						else {
						}
					}
					if (i == "ctm") {
						if (!std::filesystem::exists(NewFolderPath / "ctm" / "glass")) {
							std::filesystem::create_directory(NewFolderPath / "ctm" / "glass");
						}
						else {
						}
					}
				}

			}
			
		}
		else {
		}
	}
	return NewDir;
}


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







