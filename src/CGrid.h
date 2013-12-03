/*
 * CGrid.h
 *
 *  Created on: Nov 19, 2013
 *      Author: zZelman
 */

#ifndef CGRID_H_
#define CGRID_H_

#include "include_sfml.h"
#include "IUpdateable.h"
#include "IRenderable.h"
#include <iostream>
#include <vector>
#include "rapidxml_utils.hpp"

class CGrid : public IUpdateable, public IRenderable
{
public:
	CGrid(std::string fileName);
	~CGrid();

	void update();
	void render();

private:
	// Initial (relative) file path to the Tiled XML map file directory
	std::string m_filePath;
	std::string m_fileName;			// name within the map file directory that is used for this CGrid

	sf::Vector2<int> m_gridSize; 	// holds the total number of tiles in (width, height)

	sf::Vector2<int> m_tileSubSize; // holds the individual tile size in (width, height)
	sf::Vector2<int> m_tileSetSize;	// total size of the tile set in (width, height)
	std::string m_tileSetName;		// name of the singular tile set image file
	std::string m_tileSetPath;		// path to the directory containing the tilesets

	std::vector<std::vector<int> > m_grid;

	// parses the given Tiled XML document into required data fields
	void parseFile();


	// Relevant data fields (in plane-old-data-structure) to "tileset" DOM
	struct tileset_imageData
	{
		std::string source;
		int width;
		int height;
	};
	struct tileset_data
	{
		int firstGrid;
		std::string name;
		int tileWidth;
		int tileHeight;
		struct tileset_imageData image;
	} m_sTilesetData;

	// * parse the "tileset" section of the DOM tree
	// * takes a pointer to the "tileset" node
	// * manipulates the data within "pData" allocated outside of this function
	void parseFile_tileset(rapidxml::xml_node<>* pTileSet, tileset_data* pData);


	// Relavent data fileds (in plane-old-data-structure) to "layer" DOM
	struct layer_data
	{
		std::string name;
		int width;
		int height;
		std::vector<std::vector<int> > tiles; // only the sprite sheet LENGTH number (not an obj)
	} m_sLayerData;

	// * parse the "layer" section of the DOM tree
	// * takes a pointer to the "layer" node
	// * manipulates the data within "pData" allocated outside of this function
	void parseFile_layer(rapidxml::xml_node<>* pLayer, layer_data* pData);


	// Relavent data fileds (in plane-old-data-structure) to "layer" DOM
	struct objectgroup_objectRect
	{
		int x;
		int y;
		int width;
		int height;
	};
	struct objectgroup_data
	{
		std::string name;
		int width;
		int height;
		std::vector<struct objectgroup_objectRect> rectObjects;
	} m_sObjectgroupData;

	// * parse the "objectgroup" section of the DOM tree
	// * takes a pointer to the "layer" node
	// * manipulates the data within "pData" allocated outside of this function
	void parseFile_objectgroup(rapidxml::xml_node<>* pObjectgroup, objectgroup_data* pData);

};

#endif /* CGRID_H_ */
