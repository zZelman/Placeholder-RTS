#include "CGame.h"

#include "include_sfml.h"
#include <iostream>

void testingBasics()
{
	// loading a texture from a file
	sf::Texture* pTexture = new sf::Texture();
	pTexture->loadFromFile("res/room 1x1.png");
	pTexture->setSmooth(true);
	pTexture->setRepeated(false);

	// creating a sprite with arbitary sizes then applying the texture to it
	sf::Sprite* pSprite = new sf::Sprite();
	pSprite->setTexture(*pTexture);

	sf::RenderWindow* pWindow = new sf::RenderWindow(sf::VideoMode(800, 600), "Testing");
	pWindow->setFramerateLimit(60);
	while (pWindow->isOpen())
	{
		sf::Event event;
		while (pWindow->pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed ||
			        event.key.code == sf::Keyboard::Escape)
			{
				pWindow->close();
				return;
			}
		}

		pWindow->clear(sf::Color::White);

		pWindow->draw(*pSprite);

		pWindow->display();
	}
}

class Test
{
public:
	Test() {}
	void run()
	{
		for (int i = 0; i < 100; ++i)
		{
			std::cout << ">> Object" << std::endl;
			sf::sleep(sf::milliseconds(15));
		}
	}
};

void func()
{
	for (int i = 0; i < 100; ++i)
	{
		std::cout << "-- Function" << std::endl;
		sf::sleep(sf::milliseconds(20));
	}
}
void testingThreads()
{
	sf::Thread functionThread(&func); // arguments are possible, but only 1
	functionThread.launch();

	Test* testObj = new Test();
	sf::Thread objThread(&Test::run, testObj); // note the obj* and NO arguments
	objThread.launch();

	for (int i = 0; i < 100; ++i)
	{
		std::cout << "Main" << std::endl;
		sf::sleep(sf::milliseconds(10));
	}
}

#include "rapidxml_utils.hpp"
void testingRapidXML()
{
	rapidxml::file<> file("res/Maps/simple map.tmx");
	rapidxml::xml_document<> doc;
	doc.parse<0>(file.data());
	std::string tabSize = "  ";

	rapidxml::xml_node<>* node = doc.first_node();

	// starts at "map"
	std::cout << node->name() << "\n";

	// moves to "tileset"
	node = node->first_node();
	std::cout << tabSize <<  node->name() << "\n";

	// goes within the "tileset" tree
	node = node->first_node();
	std::cout << tabSize + tabSize << node->name() << "\n";

	// moves out of the "tileset" tree
	node = node->parent();

	// moves to "layer"
	node = node->next_sibling();
	std::cout << tabSize <<  node->name() << "\n";

	// goes within the "layer" tree to find "data"
	node = node->first_node();
	std::cout << tabSize + tabSize <<  node->name() << "\n";

	// goes within the "data" tree to find the "tile"
	node = node->first_node();
	rapidxml::xml_attribute<>* attr = node->first_attribute(); // use this to get the name and data from a node
	std::cout << tabSize + tabSize + tabSize <<  node->name() << ": " << attr->name() << "=" << attr->value() << "\n";


	std::cout << "end" << std::endl;
}


void functionToCall_1(int x, int y)
{
	std::cout << "1!! : " << x+y << std::endl;
}

void functionToCall_2(int x, int y)
{
	std::cout << "2!! : " << x*y << std::endl;
}

void chooseFunction(int x, int y, void (*functionToCall)(int, int))
{
	(*functionToCall)(x, y);
}

void testingFunctionPTRs()
{
	void (*funct)(int, int) = functionToCall_1;
	chooseFunction(5, 5, funct);
}


int main()
{
//	testingBasics();
//	testingThreads();
//	testingRapidXML();
//	testingFunctionPTRs();

	CGame* pGame = new CGame();

	pGame->startGame();
	delete pGame;
	pGame = NULL;

	return EXIT_SUCCESS;
}
