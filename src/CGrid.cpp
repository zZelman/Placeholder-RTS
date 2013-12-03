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


CGrid::CGrid(std::string fileName)
{
	m_fileName = fileName;
	m_filePath = "res/Maps/" + m_fileName;

	m_tileSetPath = "res/Map Tilesets/";

	parseFile();
}


CGrid::~CGrid()
{
	// TODO Auto-generated destructor stub
}


void CGrid::update()
{
}


void CGrid::render()
{
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
	for (unsigned int i = 0; i < pData->rectObjects.size(); ++i)
	{
		struct objectgroup_objectRect obj = pData->rectObjects.at(i);
		std::cout << obj.x << ", " << obj.y << ", " << obj.height << ", "
		          << obj.width << std::endl;
	}
	std::cout << std::endl;
}
