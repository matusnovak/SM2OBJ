#include "window.hpp"

#include <algorithm>

//#include "exportBlueprint.h"
#include "blockConfig.h"
#include "loadMeta.h"
#include "chunkTempLoader.h"
#include "chunkLoader.h"
#include "chunkHeader.h"
#include "blockConstructor.h"
#include "polygonFiltering.h"
#include "blockExtractor.h"
#include "blockVerticeData.h"
#include "materialExport.h"
#include "textureExport.h"

struct progressStruct {
	ffw::uiLabel* label;
	ffw::uiProgressbar* progressbar;
	int status;
	int total;
	void setProgress(const std::string& Str){
		std::string text = Str + ": " + ffw::valToString(status) + "/" + ffw::valToString(total);
		label->setValue(ffw::ansiToWstr(text));
		progressbar->setValue((float(status) / float(total))*100.0f);
	}
};

static bool recursiveMetaLoader(sm2obj::entityInfoStruct* Output, const std::string& BlueprintFolder, const std::string& BlueprintName, const std::string& SubFolder);
static void recursiveMetaDump(sm2obj::entityInfoStruct* Output, int Indent);
static bool recursiveChunkLoader(sm2obj::entityInfoStruct* Input, const std::string& BlueprintFolder, const std::string& OutputTemp, int& FileIndex, progressStruct& Progress, volatile bool& Cancel);
static void recursiveChunkExport(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, std::vector<sm2obj::threadInfoStruct*>& Threads, progressStruct& Progress, const std::vector<sm2obj::blockInfoStruct>& BlockInfo, volatile bool& Cancel);
static void* processChunk(void* ThreadInfoPtr);
static void generateEntityQueue(sm2obj::entityInfoStruct* Input, std::vector<sm2obj::entityInfoStruct*>* Output);
static bool mergeVertices(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, ffw::file* Output, bool SplitTextures, bool ExportUvMaps);
static int getTotalEntities(const sm2obj::entityInfoStruct* Input);

///=============================================================================
void* sm2obj::window::exportThreadFunc(void* Data){
	// General settings
	//bool exportMaterials = (radioUvMapsAtlas->getValue() || radioUvMapsTiles->getValue());
	//bool exportAtlas = radioUvMapsAtlas->getValue();
	//bool exportObject = true;
	//bool exportTextures = true;
	std::string mtlOutputPath = outputFolder + "\\" + blueprintName + ".mtl";
	std::string objOutputPath = outputFolder + "\\" + blueprintName + ".obj";
	std::string blueprintFolder = starMadeFolder + "\\Blueprints\\" + blueprintName;
	std::string blockTypesPath = starMadeFolder + "\\data\\config\\BlockTypes.properties";
	std::string blockConfigPath = starMadeFolder + "\\data\\config\\BlockConfig.xml";
	std::string tempFolder = outputFolder + "\\" + blueprintName + "_TEMP_DELETE_THIS";
	std::string textureFolder = starMadeFolder + "\\data\\textures\\block\\Default\\";
	int textureSize = 0;
	int numOfThreads = comboNumOfThreads->getSelected() +1;
	bool exportAttachments = checkboxExportAttachments->getValue();
	bool exportDiffuse = checkboxMatDiffuse->getValue();
	bool exportAlpha = checkboxMatAlpha->getValue();
	bool exportNormals = (radioMatBumps->getValue() || radioMatNormals->getValue());
	bool exportEmissive = checkboxMatEmissive->getValue();
	warningMessageFlag = false; // extern in config
	exportFinished = false;
	std::vector<threadInfoStruct*> threads;
	std::string textureExtension;
	progressStruct guiProgress;

	switch(comboTextureFormat->getSelected()){
		case 0: textureExtension = "png"; break;
		case 1: textureExtension = "tga"; break;
		case 2: textureExtension = "bmp"; break;
		case 3: textureExtension = "tiff"; break;
	}

	switch(comboTextureSize->getSelected()){
		case 0: textureFolder += "64"; textureSize = 64; break;
		case 1: textureFolder += "128"; textureSize = 128; break;
		case 2: textureFolder += "256"; textureSize = 256; break;
	}

	ffw::logDebug() << "Exporting object? -> " << (exportObject ? "true" : "False");
	ffw::logDebug() << "Exporting textures? -> " << (exportTextures ? "true" : "False");
	ffw::logDebug() << "Exporting materials? -> " << (exportMaterials ? "true" : "False");

	// Edit GUI labels & progressbars
	if(exportObject){
		labelReadingMeta->setColor(ffw::rgb(0x000000));
		labelLoadingChunks->setColor(ffw::rgb(0x000000));
		labelGeneratingBlocks->setColor(ffw::rgb(0x000000));
		labelCreatingPolys->setColor(ffw::rgb(0x000000));
		labelMergingVertices->setColor(ffw::rgb(0x000000));

		labelReadingMeta->setValue(L"Reading meta: ...");
		labelLoadingChunks->setValue(L"Loading chunks: ...");
		labelGeneratingBlocks->setValue(L"Generating blocks: ...");
		labelCreatingPolys->setValue(L"Creating polygons: ...");
		labelMergingVertices->setValue(L"Merging vertices: ...");
	} else {
		labelReadingMeta->setColor(ffw::rgb(0x777777));
		labelLoadingChunks->setColor(ffw::rgb(0x777777));
		labelGeneratingBlocks->setColor(ffw::rgb(0x777777));
		labelCreatingPolys->setColor(ffw::rgb(0x777777));
		labelMergingVertices->setColor(ffw::rgb(0x777777));

		labelReadingMeta->setValue(L"Reading meta: X");
		labelLoadingChunks->setValue(L"Loading chunks: X");
		labelGeneratingBlocks->setValue(L"Generating blocks: X");
		labelCreatingPolys->setValue(L"Creating polygons: X");
		labelMergingVertices->setValue(L"Merging vertices: X");
	}

	if(exportTextures){
		labelExportingTextures->setColor(ffw::rgb(0x000000));
		labelExportingTextures->setValue(L"Exporting textures: ...");
	} else {
		labelExportingTextures->setColor(ffw::rgb(0x777777));
		labelExportingTextures->setValue(L"Exporting textures: X");
	}

	labelBlockConfig->setColor(ffw::rgb(0x000000));
	labelBlockConfig->setValue(L"Block config: ...");

	// Output files
	ffw::file objOutput;
	ffw::file mtlOutput;

	// Block config data
	std::vector<blockTypeStruct> blockTypes;
	std::vector<blockInfoStruct> blockInfo;

	// Blueprint output data
	entityInfoStruct entityRoot;

	if(exportObject){
		// Open MTL file
		if(exportObject && exportMaterials){
			if(!mtlOutput.open(mtlOutputPath, std::ios::out | std::ios::trunc)){
				ffw::showModalError(this, L"Error!", L"Can not open output file for writing: " + ffw::utf8ToWstr(mtlOutputPath));
				buttonCancel->setLabel(L"Close");
				exportFinished = true;
				return NULL;
			} else {
				ffw::logSuccess() << "MTL destination path: " << objOutputPath;
			}
		}

		// Open OBJ file
		if(exportObject){
			if(!objOutput.open(objOutputPath, std::ios::out | std::ios::trunc)){
				ffw::showModalError(this, L"Error!", L"Can not open output file for writing: " + ffw::utf8ToWstr(objOutputPath));
				buttonCancel->setLabel(L"Close");
				exportFinished = true;
				return NULL;
			} else {
				ffw::logSuccess() << "OBJ destination path: " << objOutputPath;
			}
		}
	}

	labelBlockConfig->setValue(L"Block config: 0/2");
	progressBlockConfig->setValue(0);

	std::cout << "checking... " << exportThreadStop << std::endl;

	// Check for cancelation
	if(exportThreadStop){
		return NULL;
	}

	std::cout << "loading..." << std::endl;

	// Load block types
	if(!loadBlockTypes(blockTypes, blockTypesPath)){
		ffw::showModalError(this, L"Error!", L"Failed to open block type properties: " + ffw::utf8ToWstr(blockTypesPath));
		buttonCancel->setLabel(L"Close");
		exportFinished = true;
		return NULL;
	}

	ffw::logSuccess() << "Loaded: " << blockTypes.size() << " block types";
	labelBlockConfig->setValue(L"Block config: 1/2");
	progressBlockConfig->setValue(50);

	// Check for cancelation
	if(exportThreadStop){
		return NULL;
	}

	// Load block config
	if(!loadBlockConfig(blockTypes, blockInfo, blockConfigPath)){
		ffw::showModalError(this, L"Error!", L"Failed to open block config: " + ffw::utf8ToWstr(blockConfigPath));
		buttonCancel->setLabel(L"Close");
		exportFinished = true;
		return NULL;
	}

	// Check for cancelation
	if(exportThreadStop){
		return NULL;
	}

	ffw::logSuccess() << "Loaded: " << blockInfo.size() << " blocks from config";
	labelBlockConfig->setValue(L"Block config: 2/2");
	progressBlockConfig->setValue(100);

	if(exportObject){
		labelReadingMeta->setValue(L"Reading meta: 0/1");
		progressReadingMeta->setValue(0);

		// Load meta files if exporting attachments
		if(exportAttachments){
			ffw::logDebug() << "Loading attached ships and turrets...";
			if(!recursiveMetaLoader(&entityRoot, blueprintFolder, blueprintName, "")){
				ffw::showModalError(this, L"Error!", L"Failed to load meta data! Try to export the ship without attached turrets and ships!");
				buttonCancel->setLabel(L"Close");
				exportFinished = true;
				return NULL;
			}
		}

		labelReadingMeta->setValue(L"Reading meta: 1/1");
		progressReadingMeta->setValue(100);

		// Check for cancelation
		if(exportThreadStop){
			return NULL;
		}

		// Dump information about ship
		recursiveMetaDump(&entityRoot, 0);

		// Create temp folder
		ffw::createDirectory(tempFolder);

		// Export chunks to temp folder
		int fileIndex = 0;
		guiProgress.label = labelLoadingChunks;
		guiProgress.progressbar = progressLoadingChunks;
		guiProgress.total = getTotalEntities(&entityRoot);
		guiProgress.status = 0;
		guiProgress.setProgress("Loading chunks");
		if(!recursiveChunkLoader(&entityRoot, blueprintFolder, tempFolder, fileIndex, guiProgress, exportThreadStop)){
			ffw::showModalError(this, L"Error!", L"Failed to export chunks to temporary folder! The ship might be corrupted or program has no privileges to create temporary files");
			buttonCancel->setLabel(L"Close");
			exportFinished = true;
			return NULL;
		}

		// Check for cancelation
		if(exportThreadStop){
			return NULL;
		}

		// Create thread data
		for(int i = 0; i < numOfThreads; i++){
			threads.push_back(new threadInfoStruct(blockInfo));
			threads[i]->thread.bindFunction(&processChunk);
		}

		// Export chunks
		guiProgress.label = labelGeneratingBlocks;
		guiProgress.progressbar = progressGeneratingBlocks;
		guiProgress.total = fileIndex;
		guiProgress.status = 0;
		guiProgress.setProgress("Generating blocks");
		recursiveChunkExport(&entityRoot, tempFolder, threads, guiProgress, blockInfo, exportThreadStop);

		// Delete threads
		for(int i = 0; i < numOfThreads; i++){
			delete threads[i];
		}
		threads.clear();

		// Check for cancelation
		if(exportThreadStop){
			return NULL;
		}

		// Generate queue
		std::vector<entityInfoStruct*> entityQueue;
		generateEntityQueue(&entityRoot, &entityQueue);

		// Export vertices
		//progress = 0;
		uint64_t indicesOffset = 0;
		uint64_t texPosOffset = 0;
		chunkBufferStruct* chunkRawBuffer = new chunkBufferStruct;

		guiProgress.label = labelCreatingPolys;
		guiProgress.progressbar = progressCreatingPolys;
		guiProgress.total = entityQueue.size();
		guiProgress.status = 0;
		guiProgress.setProgress("Creating polygons");

		for(auto& entity : entityQueue){
			chunkRawBuffer->extractedMaterialsList.clear();
			for(auto& chunk : entity->chunks){
				//progress++;
				//ffw::logDebug() << "Generating vertices: " << progress << " out of: " << progressTotal;
				//Args.callbackProgress(progress, progressTotal);
				// Load a temp block to memory
				sm2obj::loadRawBlocks(tempFolder, chunkRawBuffer, chunk.fileIndex);
				// Export block to temp as indices and vertices
				sm2obj::extractBlocks(tempFolder, chunkRawBuffer, chunk.fileIndex, &indicesOffset, &texPosOffset, exportAtlas, exportMaterials, exportUV, blockInfo);
			}

			if(!exportAtlas)texPosOffset += 4;
			else texPosOffset += chunkRawBuffer->extractedMaterialsList.size()*4;

			if(exportAtlas){
				for(auto i : chunkRawBuffer->extractedMaterialsList)entity->extractedTiles.push_back(i.x);
			} else {
				for(auto i : chunkRawBuffer->extractedMaterialsList)entity->extractedMaterials.push_back(i);
			}

			guiProgress.status++;
			guiProgress.setProgress("Creating polygons");
		}
		delete chunkRawBuffer;

		// Check for cancelation
		if(exportThreadStop){
			return NULL;
		}

		// Merge files
		guiProgress.label = labelMergingVertices;
		guiProgress.progressbar = progressMergingVertices;
		guiProgress.total = entityQueue.size();
		guiProgress.status = 0;
		guiProgress.setProgress("Merging vertices");
		ffw::logSuccess() << "Merging vertices and indices into a single file...";

		objOutput.writeLine("# SM2OBJ");
		if(exportMaterials)objOutput.writeLine("mtllib " + blueprintName + ".mtl");

		//recursiveVerticesMerge(&entityRoot, tempFolder, &objOutput, !Args.useAtlas, Args.exportUV);
		for(auto& entity : entityQueue){
			mergeVertices(entity, tempFolder, &objOutput, !exportAtlas, exportUV);

			guiProgress.status++;
			guiProgress.setProgress("Merging vertices");
		}

		ffw::logSuccess() << "Creating material file...";

		// Check for cancelation
		if(exportThreadStop){
			return NULL;
		}

		// Export materials
		if(exportMaterials && exportAtlas){
			ffw::logDebug() << "Exporting altas materials";
			ffw::logDebug() << "Creating 3 materials...";
			createMaterialAtlas(&mtlOutput, true, exportDiffuse, exportAlpha, exportNormals, exportEmissive, textureExtension);

		} else if(exportMaterials){
			ffw::logDebug() << "Exporting block materials";
			std::vector<ffw::vec2i> materialList;

			for(auto& entity : entityQueue){
				for(auto& mat :entity->extractedMaterials){
					// Find if material is already added
					bool found = false;
					for(auto& item : materialList){
						if(item == mat){
							found = true;
							break;
						}
					}
					if(found)continue;
					// Add to list
					materialList.push_back(mat);
				}
			}

			ffw::logDebug() << "Creating " << materialList.size() << " materials...";

			mtlOutput.writeLine("# SM2OBJ\n");
			for(auto& mat : materialList){
				const blockInfoStruct* block = findBlock(blockInfo, mat.x);
				if(block == NULL)continue;
				createMaterialTile(&mtlOutput, block, mat.y, true, exportDiffuse, exportAlpha, exportNormals, exportEmissive, textureExtension);
			}
		}

		// Check for cancelation
		if(exportThreadStop){
			return NULL;
		}
	}

	// Export textures
	if(exportTextures){
		guiProgress.label = labelExportingTextures;
		guiProgress.progressbar = progressExportingTextures;
		guiProgress.total = 0;
		if(exportDiffuse)guiProgress.total++;
		if(exportAlpha)guiProgress.total++;
		if(exportEmissive && exportAtlas)guiProgress.total++;
		if(exportNormals)guiProgress.total++;
		guiProgress.status = 0;
		guiProgress.setProgress("Exporting textures");

		std::string textureOutputFolder = outputFolder + "\\textures";
		ffw::createDirectory(textureOutputFolder);

		if(exportAtlas){
			if(exportDiffuse){
				exportDiffuseAtlas(textureFolder + "\\t000.png", textureSize, textureOutputFolder + "\\Atlas_0_diff." + textureExtension);
				exportDiffuseAtlas(textureFolder + "\\t001.png", textureSize, textureOutputFolder + "\\Atlas_1_diff." + textureExtension);
				exportDiffuseAtlas(textureFolder + "\\t002.png", textureSize, textureOutputFolder + "\\Atlas_2_diff." + textureExtension);

				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");
			}

			// Check for cancelation
			if(exportThreadStop){
				return NULL;
			}

			if(exportAlpha){
				exportAlphaAtlas(textureFolder + "\\t000.png", textureSize, textureOutputFolder + "\\Atlas_0_alpha." + textureExtension);
				exportAlphaAtlas(textureFolder + "\\t001.png", textureSize, textureOutputFolder + "\\Atlas_1_alpha." + textureExtension);
				exportAlphaAtlas(textureFolder + "\\t002.png", textureSize, textureOutputFolder + "\\Atlas_2_alpha." + textureExtension);

				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");
			}

			// Check for cancelation
			if(exportThreadStop){
				return NULL;
			}

			if(exportEmissive){
				exportEmissiveAtlas(blockInfo, textureSize, 0, textureOutputFolder + "\\Atlas_0_emissive." + textureExtension);
				exportEmissiveAtlas(blockInfo, textureSize, 1, textureOutputFolder + "\\Atlas_1_emissive." + textureExtension);
				exportEmissiveAtlas(blockInfo, textureSize, 2, textureOutputFolder + "\\Atlas_2_emissive." + textureExtension);

				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");
			}

			// Check for cancelation
			if(exportThreadStop){
				return NULL;
			}

			if(exportNormals && useBumps){
				exportBumpAtlas(textureFolder + "\\t000_NRM.png", textureSize, textureOutputFolder + "\\Atlas_0_bump." + textureExtension);
				exportBumpAtlas(textureFolder + "\\t001_NRM.png", textureSize, textureOutputFolder + "\\Atlas_1_bump." + textureExtension);
				exportBumpAtlas(textureFolder + "\\t002_NRM.png", textureSize, textureOutputFolder + "\\Atlas_2_bump." + textureExtension);

				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");

			} else if(exportNormals){
				exportNormalAtlas(textureFolder + "\\t000_NRM.png", textureSize, textureOutputFolder + "\\Atlas_0_bump." + textureExtension);
				exportNormalAtlas(textureFolder + "\\t001_NRM.png", textureSize, textureOutputFolder + "\\Atlas_1_bump." + textureExtension);
				exportNormalAtlas(textureFolder + "\\t002_NRM.png", textureSize, textureOutputFolder + "\\Atlas_2_bump." + textureExtension);

				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");
			}

		} else {
			if(exportDiffuse){
				exportTileDiffuse(blockInfo, textureFolder, textureSize, textureOutputFolder, textureExtension);
				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");
			}

			// Check for cancelation
			if(exportThreadStop){
				return NULL;
			}

			if(exportAlpha){
				exportTileAlpha(blockInfo, textureFolder, textureSize, textureOutputFolder, textureExtension);
				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");
			}

			// Check for cancelation
			if(exportThreadStop){
				return NULL;
			}

			if(exportNormals && useBumps){
				exportTileBump(blockInfo, textureFolder, textureSize, textureOutputFolder, textureExtension);
				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");

			} else if(exportNormals){
				exportTileNormals(blockInfo, textureFolder, textureSize, textureOutputFolder, textureExtension);
				guiProgress.status++;
				guiProgress.setProgress("Exporting textures");
			}
		}
	}

	std::fstream logIn(ffw::getExecutablePath() + "\\log.txt", std::ios::in);
	std::fstream logOut(outputFolder + "\\" + blueprintName + "_log.txt", std::ios::out | std::ios::trunc);
	if(logIn && logOut){
		logOut << logIn.rdbuf();
		logIn.close();
		logOut.close();
	}

	if(warningMessageFlag) ffw::showModalWarning(this, L"Warning!", L"Blueprint might not be correctly exported! There were some minor errors! Check log file located in exported folder for warning and errors messages!");
	else ffw::showModalInfo(this, L"Success!", L"Blueprint exported without any errors nor warnings! Destination folder: " + ffw::utf8ToWstr(outputFolder));

	buttonCancel->setLabel(L"Close");
	exportFinished = true;
	return NULL;
}

///=============================================================================
bool recursiveMetaLoader(sm2obj::entityInfoStruct* Output, const std::string& BlueprintFolder, const std::string& BlueprintName, const std::string& SubFolder){
    std::string path = BlueprintFolder + SubFolder + "\\meta.smbpm";

	if(!loadMeta(Output, path, BlueprintName)){
		ffw::logError() << "Failed to open meta file from: " << path;
		return false;
    } else {
		ffw::logSuccess() << "Meta file loaded from: " << path;
	}

    for(auto& item : Output->attachments){
        if(!recursiveMetaLoader(&item, BlueprintFolder, BlueprintName, item.path)){
            return false;
        }
    }

    return true;
}

///=============================================================================
void recursiveMetaDump(sm2obj::entityInfoStruct* Output, int Indent){
    std::string ind;
    ind.resize(Indent, ' ');

    ffw::logNotice() << ind + "> Name: " << Output->name;
    ffw::logNotice() <<ind + "> Path: " << Output->path;
    //Args.callbackLogDebug(ind + "> Position: " + ffw::valToString(Output->pos.x) + ", " + ffw::valToString(Output->pos.y) + ", " + ffw::valToString(Output->pos.z));
    //Args.callbackLogDebug(ind + "> Orientation: " + ffw::valToString(Output->orientation.x) + ", " + ffw::valToString(Output->orientation.y) + ", " + ffw::valToString(Output->orientation.z));
    ffw::logNotice() << ind + "> Dock module position: " << Output->dockModule.x << ", " << Output->dockModule.y << ", " << Output->dockModule.z;
    for(auto& item : Output->attachments){
        recursiveMetaDump(&item, Indent+2);
    }
}

///=============================================================================
int getTotalEntities(const sm2obj::entityInfoStruct* Input){
	int num = 1;
	for(auto& item : Input->attachments){
        num += getTotalEntities(&item);
    }
	return num;
}

///=============================================================================
bool recursiveChunkLoader(sm2obj::entityInfoStruct* Input, const std::string& BlueprintFolder, const std::string& OutputTemp, int& FileIndex, progressStruct& Progress, volatile bool& Cancel){
    std::vector<std::string> allFiles;

    // Open target directory
    ffw::directory dir;
	std::string path = BlueprintFolder + Input->path + "\\DATA";
    if(!dir.open(path)){
        ffw::logError() << "Failed to open folder: " << path << " The program might not have permission to do it!";
        return false;
    }

    // Include all files that match
    for(const auto& file : dir.getFiles()){
        std::string extension;
        ffw::getFilePathProperties(file, NULL, NULL, &extension);
        if(extension != "smd2")continue;

        allFiles.push_back(file);
    }

    // Load all files
    for(const auto& file : allFiles){
        ffw::file fileInput;

        ffw::logDebug() << "Reading file: " << file;

        // Get file position from file name
        size_t pos = file.find('.');
        if(pos == std::string::npos){
            ffw::logError() << "Error while retrieving file position from file name! Expected dot with coordinates!";
            return false;
        }

        // Get position as tokens
        std::vector<std::string> tokens = ffw::getTokens(file.substr(pos+1, file.size()-pos-6), '.');
        if(tokens.size() != 3){
            ffw::logError() << "Error while retrieving file position from file name! Wrong coordinates!";
            return false;
        }

        // Convert position to integers
        ffw::vec3i filePos;
        try {
            filePos.x = ffw::stringToVal<int>(tokens[0]);
            filePos.y = ffw::stringToVal<int>(tokens[1]);
            filePos.z = ffw::stringToVal<int>(tokens[2]);
            filePos *= 256;
        } catch (std::exception e){
            ffw::logError() << "Error while retrieving file position from file name! Wrong coordinates!";
            return false;
        }

        // Print file position
        ffw::logDebug() << "File position: " << tokens[0] << ", " << tokens[1] + ", " << tokens[2];

        // Open a file
        if(!fileInput.open(path + "\\" + file, std::ios::in | std::ios::binary)){
            ffw::logError() << "Failed to open file: " << path << "\\" << file;
            return false;
        }

        // Check if file is big enough to contain header
        size_t fileSize = fileInput.getSize();
        if(fileSize < size_t(4+32768+16384)){
            ffw::logError() << "File is invalid! File is too small. Expected at least 49156 bytes.";
            return false;
        }

        // Load header
        int chunkIndex[SM2OBJ_CHUNK_SIZE];
        int totalChunks = 0;
        if(!sm2obj::loadChunkHeader(&fileInput, &chunkIndex[0], &totalChunks)){
            //ffw::logError() << "Failed to load chunk header!";
            return false;
        }

        // Remember the file offset
        size_t fileOffset = fileInput.getPos();

        ffw::logDebug() << "Total chunks: " << totalChunks;
        //fileChunksTotal += totalChunks;

        // Sort indexes
        // We need to load chunks ordered
        std::sort(std::begin(chunkIndex), std::end(chunkIndex));

        // Load all chunks
        uint32_t chunkData[16][16][16];
        ffw::vec3i chunkPos;
        for(int i = 0; i < SM2OBJ_CHUNK_SIZE; i++){
            if(chunkIndex[i] < 0)continue;
            ffw::logDebug() << "Loading chunk index: " << chunkIndex[i];

            // Load chunk
            fileInput.gotoPos(fileOffset + chunkIndex[i]*5120);
            if(!sm2obj::loadChunk(&fileInput, fileOffset, chunkIndex[i], chunkData, &chunkPos)){
                continue;
            }

            // Save decompressed raw chunk data to temp folder
            if(!sm2obj::saveTempChunk(OutputTemp, FileIndex, &chunkData[0][0][0])){
                ffw::logError() << "Error while saving chunk to temp! Make sure the program has permissions to create files!";
                continue;
            }

            // Add chunk to list
            Input->chunks.push_back({chunkPos, filePos, FileIndex});
            FileIndex++;
        }
    }

	Progress.status++;
	Progress.setProgress("Loading chunks");

    for(auto& item : Input->attachments){
        if(Cancel)return true;

		if(!recursiveChunkLoader(&item, BlueprintFolder, OutputTemp, FileIndex, Progress, Cancel))return false;
    }

    return true;
}


///=============================================================================
void recursiveChunkExport(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, std::vector<sm2obj::threadInfoStruct*>& Threads, progressStruct& Progress, const std::vector<sm2obj::blockInfoStruct>& BlockInfo, volatile bool& Cancel){
    ffw::logDebug() << "Exporting: " << Input->name << " from: " << Input->path;

    // export chunks one by one
    for(auto& chunk : Input->chunks){
        // Find an empty thread
        while(true){
            bool found = false;
            // Loop through all threads
            for(int i = 0; i < Threads.size(); i++){
                // We can lock a thread only of it has finished
                if(Threads[i]->mut.tryLock()){
                    // We found an empty thread, bind information and run it
                    Progress.status++;
					Progress.setProgress("Generating blocks");
                    //progress(processedChunks, fileChunksTotal);
                    //Args.callbackLogInfo("Processing chunk: " + ffw::valToString(Progress) + " out of: " + ffw::valToString(ProgressTotal));
                    //Args.callbackProgress(Progress, ProgressTotal);
                    // Where are raw chunks stored
                    Threads[i]->tempFolder = InputOutputTemp;
                    // Unlock mutex
                    Threads[i]->mut.unlock();
                    // Always join even if thread has stopped
                    Threads[i]->thread.join();
                    // Bind chunk
                    Threads[i]->chunkPtr = &chunk;
                    // Set matrix
                    Threads[i]->entityPtr = Input;
                    // Start
                    Threads[i]->thread.start(Threads[i]);
                    // Wait 100ms and go to next chunk
                    ffw::usleep(100000);
                    found = true;
                    break;
                }
				if(Cancel)break;
            }
			if(Cancel)break;
            // An empty thread was not found, wait and then try again
            if(found)break;
            ffw::usleep(100000);
        }
		if(Cancel)break;
    }

    ffw::logDebug() << "Waiting for threads...";
    // Join all threads
    for(int i = 0; i < Threads.size(); i++){
        Threads[i]->thread.join();
    }

    for(auto& item : Input->attachments){
        if(Cancel)break;
		recursiveChunkExport(&item, InputOutputTemp, Threads, Progress, BlockInfo, Cancel);
    }
}

///=============================================================================
static void* processChunk(void* ThreadInfoPtr){
	// Get pointer to the thread info struct
    sm2obj::threadInfoStruct* threadInfo = static_cast<sm2obj::threadInfoStruct*>(ThreadInfoPtr);
    // Lock this thread
    threadInfo->mut.lock();
    // Get chunk pointer
    sm2obj::chunkInfoStruct* chunk = threadInfo->chunkPtr;

    // Load chunk from file
    uint32_t chunkData[16][16][16];
    if(!sm2obj::loadTempChunk(threadInfo->tempFolder, chunk->fileIndex, &chunkData[0][0][0])){
        ffw::logError() << "Error loading chunk file index: " << chunk->fileIndex;
        threadInfo->mut.unlock();
        return NULL;
    }

    // Reset buffer A
    threadInfo->chunkBufferA.indicesCount = 0;
    threadInfo->chunkBufferA.verticesCount = 0;
    threadInfo->chunkBufferA.indicesOffset = 0;

    // Build blocks by looking through all XYZ positions in chunk
    ffw::vec3i posRel;
    for(posRel.z = 0; posRel.z < 16; posRel.z++){
        for(posRel.y = 0; posRel.y < 16; posRel.y++){
            for(posRel.x = 0; posRel.x < 16; posRel.x++){
                if(chunkData[posRel.z][posRel.y][posRel.x] == 0)continue;

                buildBlock(posRel, chunk->pos, chunk->posFile, chunkData, &threadInfo->chunkBufferA, threadInfo->blockInfo);

            }
        }
    }

    // Reset buffer B
    threadInfo->chunkBufferB.indicesCount = 0;
    threadInfo->chunkBufferB.verticesCount = 0;
    threadInfo->chunkBufferB.indicesOffset = 0;

    // Filter polygons that occupies same space
    removeDuplicatedFaces(&threadInfo->chunkBufferA, &threadInfo->chunkBufferB);

    // Now the data is in buffer B
    // We will use buffer A as a output
    threadInfo->chunkBufferA.indicesCount = 0;
    threadInfo->chunkBufferA.verticesCount = 0;
    threadInfo->chunkBufferA.indicesOffset = 0;

    // Remove duplicated vertices
    removeDuplicatedVertices(&threadInfo->chunkBufferB, &threadInfo->chunkBufferA);

    // Transform vertices
    ffw::vec3f translation(-8.0f, -8.0f, -8.0f);
    //ffw::vec3f dockOffset = threadInfo->entityPtr->dockModule - ffw::vec3f(8.0f, 8.0f, 8.0f);
    //translation -= dockOffset;

    /*ffw::mat4 m;
    ffw::vec3f globalPos;

    sm2obj::entityInfoStruct* entity = threadInfo->entityPtr;
    std::vector<sm2obj::entityInfoStruct*> entityStack;
    while(entity != NULL){
        entityStack.push_back(entity);
        entity = entity->parent;
    }

    if(entityStack.size() > 0){
        for(int i = entityStack.size()-1; i >= 0; i--){
            m.rotate(entityStack[i]->orientation);
        }
    }

    ffw::mat4 mr;
    entity = threadInfo->entityPtr;
    while(entity != NULL){

        ffw::vec3f pos = (entity->pos - ffw::vec3f(8.0f, 8.0f, 8.0f));
        ffw::vec3f dockModule;
        ffw::vec3f offset = entity->dockOffset;
        //std::cout << "pos: " << pos << std::endl;
        //std::cout << "dockOffset: " << offset << std::endl;

        //ffw::vec4f v;
        ffw::mat4 rr;
        constructRotation(entity, &rr);

        entity = entity->parent;

        if(entity != NULL){
            dockModule = (entity->dockModule - ffw::vec3f(8.0f, 8.0f, 8.0f));
            ffw::mat4 mr;

            constructRotation(entity, &mr);

            ffw::vec4f v;
            v.x = pos.x;
            v.y = pos.y;
            v.z = pos.z;
            v = mr * v;
            pos.x = v.x;
            pos.y = v.y;
            pos.z = v.z;

            v.x = offset.x;
            v.y = offset.y;
            v.z = offset.z;
            v.w = 1.0f;
            v = mr * v;
            offset.x = v.x;
            offset.y = v.y;
            offset.z = v.z;

            v.x = dockModule.x;
            v.y = dockModule.y;
            v.z = dockModule.z;
            v.w = 1.0f;
            v = mr * v;
            dockModule.x = v.x;
            dockModule.y = v.y;
            dockModule.z = v.z;
        }
        globalPos -= dockModule;
        globalPos += pos + offset;
    }*/

    for(uint32_t i = 0; i < threadInfo->chunkBufferA.verticesCount; i++){
        threadInfo->chunkBufferA.vertices[i] += translation;
        /*ffw::vec4f v;

        v.x = threadInfo->chunkBufferA.vertices[i].x;
        v.y = threadInfo->chunkBufferA.vertices[i].y;
        v.z = threadInfo->chunkBufferA.vertices[i].z;
        v.w = 1.0f;
        v = m * v;
        threadInfo->chunkBufferA.vertices[i].x = v.x;
        threadInfo->chunkBufferA.vertices[i].y = v.y;
        threadInfo->chunkBufferA.vertices[i].z = v.z;
        threadInfo->chunkBufferA.vertices[i] += globalPos;*/
    }

    // Now the data is in buffer A
    // Save it to temp file
    saveRawBlocks(threadInfo->tempFolder, &threadInfo->chunkBufferA, chunk->fileIndex);

    ffw::logSuccess() << "Chunk index: " << chunk->fileIndex << " exported!";

    // Unlock this thread
    threadInfo->mut.unlock();
    return NULL;
}

///=============================================================================
void generateEntityQueue(sm2obj::entityInfoStruct* Input, std::vector<sm2obj::entityInfoStruct*>* Output){
    Output->push_back(Input);

    for(auto& item : Input->attachments){
        generateEntityQueue(&item, Output);
    }
}

///=============================================================================
bool mergeVertices(sm2obj::entityInfoStruct* Input, const std::string& InputOutputTemp, ffw::file* Output, bool SplitTextures, bool ExportUvMaps){
    Output->writeLine("o " + Input->name);

    for(auto& chunk : Input->chunks){
        ffw::file vertices;

        // Open chunk temp file which contains vertices
        if(!vertices.open(InputOutputTemp + "\\chunk-temp-" + ffw::valToString(chunk.fileIndex) + ".vertices", std::ios::in)){
            ffw::logError() << "Error failed to open vertex temp data! Index: " << chunk.fileIndex;
            return false;
        }

        // Read whole file and put contents in output OBJ
        std::string temp;
        while(!vertices.eof()){
            vertices.readLine(&temp);
            if(temp.size() == 0)continue;
            Output->writeLine(temp);
        }
    }

    // Export UVs
    if(ExportUvMaps && SplitTextures){
        for(int i = 0; i < 4; i++){
            Output->writeLine("vt " + ffw::valToString(sm2obj::globalTextureUvs[i].x, 6) + " " + ffw::valToString(sm2obj::globalTextureUvs[i].y, 6));
        }
    } else if(ExportUvMaps){
        for(const auto& tile : Input->extractedTiles){
            int atlasId = tile / 256;
            int posY = tile / 16;
            int posX = tile - posY*16;
            posY -= atlasId*16;
            ffw::vec2f tilePos(posX / 16.0f, posY / 16.0f);
            tilePos.y = 1.0f - tilePos.y - 0.0625f;

            for(int i = 0; i < 4; i++){
                ffw::vec2f uvs = sm2obj::globalTextureUvs[i];
                uvs.y = 1.0f - uvs.y;
                ffw::vec2f texPos = uvs * ffw::vec2f(0.052734375f, 0.052734375f) + tilePos + 0.0048828125f;
                Output->writeLine("vt " + ffw::valToString(texPos.x, 10) + " " + ffw::valToString(texPos.y, 10));
            }
        }
    }

    // Shading off
    Output->writeLine("s off");

    // Do the same for indices
    for(auto& chunk : Input->chunks){
        ffw::file indices;

        // Open chunk temp file which contains indices
        if(!indices.open(InputOutputTemp + "\\chunk-temp-" + ffw::valToString(chunk.fileIndex) + ".indices", std::ios::in)){
            ffw::logError() << "Error failed to open indice temp data! Index: " << chunk.fileIndex;
            return false;
        }

        // Read whole file and put contents in output OBJ
        std::string temp;
        while(!indices.eof()){
            indices.readLine(&temp);
            if(temp.size() == 0)continue;
            Output->writeLine(temp);
        }
    }

    return true;
}
