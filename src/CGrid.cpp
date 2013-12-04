/*
 * CGrid.cpp
 *
 *  Created on: Nov 19, 2013
 *      Author: zZelman
 */

#include "CGrid.h"

#include <iostream>
#include <fstream>
#include <assert.h>
#include <stdlib.h>
#include "rapidxml_utils.hpp"


CGrid::CGrid(sf::RenderWindow* pWindow, std::string fileName)
{
	m_pWindow = pWindow;

	m_fileName = fileName;
	m_filePath = "res/Maps/" + m_fileName;

	m_tileSetPath = "res/Map Tilesets/";

	parseFile();

	generateGrid();
}


CGrid::~CGrid()
{
	delete m_pTestTexture;
	m_pTestTexture = NULL;

	for (unsigned int i = 0; i < m_testSprites.size(); ++i)
	{
		CSprite* s = m_testSprites.at(i);
		delete s;
		s = NULL;
	}
	m_testSprites.clear();
}


void CGrid::update()
{
}


void CGrid::render()
{
	for (unsigned int i = 0; i < m_testSprites.size(); ++i)
	{
		m_testSprites.at(i)->render();
	}
}


void CGrid::generateGrid()
{
	CTexture* pTexture = generateGrid_texture();
	m_pTestTexture = pTexture;

	// use the info received at the specific 2D index to create a sprite
	//		with the correct texture, and in the correct position
	for (unsigned int i = 0; i < m_sLayerData.tiles.size(); ++i)
	{
		std::vector<int> internalVect = m_sLayerData.tiles.at(i);
		for (unsigned int n = 0; n < internalVect.size(); ++n)
		{
			int data = internalVect.at(n);
			if (data == 0) // 0 in the Tiled data structure represents "no tile present"
			{
				continue;
			}
			else
			{
				m_testSprites.push_back(generateGrid_sprite(n + 1, i + 1, data, pTexture));
			}
		}
	}
}


CTexture* CGrid::generateGrid_texture()
{
	// CTexture() data fields, pulled out for readability
	std::string fileName;
	sf::Vector2<int> subSize;
	sf::Vector2<int> subNum;

	// cut off everything exept the actuall file name
	int find = m_sTilesetData.image.source.find_last_of('/');
	fileName = m_sTilesetData.image.source.substr(find + 1, m_sTilesetData.image.source.size());
	fileName = m_tileSetPath + fileName;

	// fill in values
	subSize.x = m_sTilesetData.tileWidth;
	subSize.y = m_sTilesetData.tileHeight;

	// (total image demention size) / (size of sub images) = numer of sub images
	subNum.x = m_sTilesetData.image.width / subSize.x;
	subNum.y = m_sTilesetData.image.height / subSize.y;

	return new CTexture(fileName, subSize, subNum);
}


CSprite* CGrid::generateGrid_sprite(int posX, int posY, int gridNum, CTexture* pTexture)
{
	// CSprite() data fileds, pulled out for readability
	sf::RenderWindow* pWindow = m_pWindow;

	// because "gridNum" is given as a single value (see Tiled documentation of sprite sheet breakdowns)
	//		we need to devide the number out to find where on the sprite sheet it came from
	sf::Vector2<int> subNum = m_pTestTexture->getSubNum();
	int startingLength = m_sTilesetData.firstGrid;
	int recievedNum = gridNum;
	sf::Vector2<int> currSub;
	findSubImage(&subNum, startingLength, recievedNum, &currSub);

	CSprite* s = new CSprite(pWindow, pTexture, currSub);

	positionTile(s, posX, posY);

	return s;
}

void CGrid::findSubImage(sf::Vector2<int>* subNum, int startingLength,
                         int recievedNum, sf::Vector2<int>* returnedPos)
{

	// Find the row by subtracting the column size from the recievedNum
	// 	you have found it when that is less than the startingLenght
	int row = 0;
	for (int i = 0; i < subNum->y + 1; ++i)
	{
		int subtract = i * subNum->x;
		if (recievedNum - subtract < startingLength)
		{
			row = i;
			break;
		}
	}

	// fidning the column is easy once you have the row
	int col = recievedNum - (row - 1) * subNum->x;

//	std::cout << "(" << col << ", " << row << ")" << std::endl;

	// save the data into the return sf::Vector2
	returnedPos->x = col;
	returnedPos->y = row;
}


void CGrid::positionTile(CSprite* pSprite, int posX, int posY)
{
	// final position variables
	int x = (posX - 1) * m_sTilesetData.tileWidth;
	int y = (posY - 1) * m_sTilesetData.tileHeight;

	pSprite->setPosition(x, y);
}


void CGrid::parseFile()
{
	// internal flags to look for; direct children of node "map"
	std::string tileSetNode 	= "tileset";
	std::string layerNode 		= "layer";
	std::string objectGroupNode	= "objectgroup";
	std::string imageLayerNode 	= "imagelayer";

	rapidxml::file<> file(m_filePath.c_str());
	rapidxml::xml_document<> doc;
	doc.parse<0>(file.data());

	//
	// root of the DOM tree
	//
	rapidxml::xml_node<>* pMap = doc.first_node();

	for (rapidxml::xml_node<>* node = pMap->first_node(); node; node = node->next_sibling())
	{
		if (node->name() == tileSetNode)
		{
			parseFile_tileset(node, &m_sTilesetData);
		}
		else if (node->name() == layerNode)
		{
			parseFile_layer(node, &m_sLayerData);
		}
		else if (node->name() == objectGroupNode)
		{
			parseFile_objectgroup(node, &m_sObjectgroupData);
		}
	}
}


void CGrid::parseFile_tileset(rapidxml::xml_node<>* pTileSet, tileset_data* pData)
{
	//
	// Extract information from the "tileset" node
	//
	rapidxml::xml_attribute<>* pTileSet_Attrib = pTileSet->first_attribute();

	pData->firstGrid = atoi(pTileSet_Attrib->value());

	pTileSet_Attrib = pTileSet_Attrib->next_attribute();
	pData->name = pTileSet_Attrib->value();

	pTileSet_Attrib = pTileSet_Attrib->next_attribute();
	pData->tileWidth = atoi(pTileSet_Attrib->value());

	pTileSet_Attrib = pTileSet_Attrib->next_attribute();
	pData->tileHeight = atoi(pTileSet_Attrib->value());

//	std::cout << pData->name << ", " << pData->tileWidth << ", " << pData->tileHeight << std::endl;


	//
	// extract information from the sub-node "image"
	//
	rapidxml::xml_node<>* pImage = pTileSet->first_node();

	rapidxml::xml_attribute<>* pImage_Attrib = pImage->first_attribute();

	pData->image.source = pImage_Attrib->value();

	pImage_Attrib = pImage_Attrib->next_attribute();
	pData->image.width = atoi(pImage_Attrib->value());

	pImage_Attrib = pImage_Attrib->next_attribute();
	pData->image.height = atoi(pImage_Attrib->value());

//	std::cout << pData->image.source << ", " << pData->image.width << ", " << pData->image.height << std::endl;
}


void CGrid::parseFile_layer(rapidxml::xml_node<>* pLayer, layer_data* pData)
{
	//
	// Extract information from the "layer" node
	//
	rapidxml::xml_attribute<>* pLayer_attrib = pLayer->first_attribute();

	pData->name = pLayer_attrib->value();

	pLayer_attrib = pLayer_attrib->next_attribute();
	pData->width = atoi(pLayer_attrib->value());

	pLayer_attrib = pLayer_attrib->next_attribute();
	pData->height = atoi(pLayer_attrib->value());

//	std::cout << pData->name << ", " << pData->width << ", " << pData->height << std::endl;


	//
	// Move to, and extract information from each of the (width * height) number of "tile" nodes
	//
	rapidxml::xml_node<>* pTile = pLayer->first_node()->first_node(); // move through the "data" node

	// note the (width, height) element access, this is for later when the tile is obj'etified
	for (int i = 0; i < pData->width; ++i)
	{
		// [INTERESTING] because we are using a dynamic data structure here,
		//		we can always just push back on the internal vector
		//		then just push that back on to the whole vector
		std::vector<int> rowData;
		for (int n = 0; n < pData->height; ++n)
		{
			rowData.push_back(atoi(pTile->first_attribute()->value()));
			pTile = pTile->next_sibling();
		}

		pData->tiles.push_back(rowData);
	}

//	for (int i = 0; i < pData->width; ++i)
//	{
//		std::vector<int> rowData = pData->tiles.at(i);
//		for(int n = 0; n < pData->height; ++n)
//		{
//			std::cout << rowData.at(n) << " ";
//		}
//		std::cout << std::endl;
//	}
}


void CGrid::parseFile_objectgroup(rapidxml::xml_node<>* pObjectgroup, objectgroup_data* pData)
{
	//
	// Extract information from "objectgroup" node
	//
	rapidxml::xml_attribute<>* pObjG_attrib = pObjectgroup->first_attribute();

	pData->name = pObjG_attrib->value();

	pObjG_attrib = pObjG_attrib->next_attribute();
	pData->width = atoi(pObjG_attrib->value());

	pObjG_attrib = pObjG_attrib->next_attribute();
	pData->height = atoi(pObjG_attrib->value());

//	std::cout << pData->name << ", " << pData->width << ", " << pData->height << std::endl;


	//
	// Move to and extract information from the "object" nodes
	//
	for (rapidxml::xml_node<>* node = pObjectgroup->first_node(); node; node = node->next_sibling())
	{
		rapidxml::xml_attribute<>* attr = node->first_attribute();

		struct objectgroup_objectRect obj;

		obj.x = atoi(attr->value());

		attr = attr->next_attribute();
		obj.y = atoi(attr->value());

		attr = attr->next_attribute();
		obj.width = atoi(attr->value());

		attr = attr->next_attribute();
		obj.height = atoi(attr->value());

		pData->rectObjects.push_back(obj);
	}

	// NOTE: if there are multiple "object"s in the target file, they will stack up here (because vector)
//	for (unsigned int i = 0; i < pData->rectObjects.size(); ++i)
//	{
//		struct objectgroup_objectRect obj = pData->rectObjects.at(i);
//		std::cout << obj.x << ", " << obj.y << ", " << obj.height << ", "
//		          << obj.width << std::endl;
//	}
//	std::cout << std::endl;
}
