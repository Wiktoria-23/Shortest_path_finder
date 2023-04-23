﻿#include <iostream>
#include <stdio.h>
#include "Graph.h"
#define SPACE ' '
#define NEW_LINE '\n'
#define TAB '\t'
#define CITY_SYMBOL '*'
#define NOTHING '.'
#define ROAD '#'
#define BUFFER_SIZE 50
#define END_OF_TEXT '\0'
using namespace std;

enum direction {
	UP,
	DOWN,
	RIGHT,
	LEFT,
	NONE
};

void getMap(int height, int width, char** map);
int readCityName(char* cityName, int x, char* mapLine);
void addCityName(int x, int y, char** map, int width, int height, Graph* mapGraph);
void addRoad();
void readRoad(Graph* mapGraph, char** map, int x, int y, direction roadDirection, int lengthCounter, int width, int height);
void checkRoads(int x, int y, char** map, int width, int height, Graph* mapGraph, direction previousRoadDirection, int lengthCounter = 0);
int readRoadLength(int x, int y, int lengthCounter, char** map, direction roadDirection, Graph* mapGraph, int width, int height);
void readMap(int height, int width, char** map, Graph* mapGraph);

void getMap(int height, int width, char** map) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width;) {
			char input = getchar();
			if (input != SPACE && input != NEW_LINE && input != TAB) {
				map[y][x] = input;
				x++;
			}
		}
	}
}

int readCityName(char* cityName, int x, char* mapLine) {
	while (mapLine[x - 1] != NOTHING && mapLine[x -1] != ROAD) { //checks if previous character is '.'
		x -= 1;
	}
	int i = 0;
	int size = 0;
	while (mapLine[x] != NOTHING && mapLine[x] != ROAD) {
		cityName[i] = mapLine[x];
		size += 1;
		x += 1;
		i++;
	}
	return size;
}

void addCityName(int x, int y, char** map, int width, int height, Graph* mapGraph) {
	char* input = new char[BUFFER_SIZE];
	int size = 0;
	if (y - 1 >= 0 && map[y - 1][x] != NOTHING && map[y - 1][x] != ROAD) {
		size = readCityName(input, x, map[y - 1]);
	}
	else if (y + 1 < height && map[y + 1][x] != NOTHING && map[y + 1][x] != ROAD) {
		size = readCityName(input, x, map[y + 1]);
	}
	else if (x + 1 < width && map[y][x + 1] != NOTHING && map[y][x + 1] != ROAD) {
		size = readCityName(input, x + 1, map[y]);
	}
	else if (x - 1 >= 0 && map[y][x - 1] != NOTHING && map[y][x - 1] != ROAD) {
		size = readCityName(input, x - 1, map[y]);
	}
	else if (x + 1 < width && y + 1 < height && map[y + 1][x + 1] != NOTHING && map[y + 1][x + 1] != ROAD) {
		size = readCityName(input, x + 1, map[y + 1]);
	}
	else if (y + 1 < height && x - 1 >= 0 && map[y + 1][x - 1] != NOTHING && map[y + 1][x - 1] != ROAD) {
		size = readCityName(input, x - 1, map[y + 1]);
	}
	else if (x - 1 >= 0 && y - 1 >= 0 && map[y - 1][x - 1] != NOTHING && map[y - 1][x - 1] != ROAD) {
		size = readCityName(input, x - 1, map[y - 1]);
	}
	else if (x + 1 < width && y - 1 >= 0 && map[y - 1][x + 1] != NOTHING && map[y - 1][x + 1] != ROAD) {
		size = readCityName(input, x + 1, map[y - 1]);
	}
	char* cityName = new char[size + 1];
	for (int i = 0; i < size; i++) {
		cityName[i] = input[i];
	}
	cityName[size] = END_OF_TEXT;
	delete[] input;
	mapGraph->addNewCityName(cityName, size);
}

void addRoad() {

}

void readRoad(Graph* mapGraph, char** map, int x, int y, direction roadDirection, int lengthCounter, int width, int height) {
	if (y - 1 >=0 && map[y - 1][x] == ROAD && roadDirection != DOWN) {
		if (roadDirection != UP) {
			checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
		}
		else {
			lengthCounter = readRoadLength(x, y - 1, lengthCounter, map, roadDirection, mapGraph, width, height);
		}
	}
	if (y + 1 < height && map[y + 1][x] == ROAD && roadDirection != UP) {
		if (roadDirection != DOWN) {
			checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
		}
		else {
			lengthCounter = readRoadLength(x, y + 1, lengthCounter, map, roadDirection, mapGraph, width, height);
		}
	}
	if (x - 1 >= 0 && map[y][x - 1] == ROAD && roadDirection != RIGHT) {
		if (roadDirection != LEFT) {
			checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
		}
		else {
			lengthCounter = readRoadLength(x - 1, y, lengthCounter, map, roadDirection, mapGraph, width, height);
		}
	}
	if (x + 1 < width && map[y][x + 1] == ROAD && roadDirection != LEFT) {
		if (roadDirection != RIGHT) {
			checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
		}
		else {
			lengthCounter = readRoadLength(x + 1, y, lengthCounter, map, roadDirection, mapGraph, width, height);
		}
	}
}

void checkRoads(int x, int y, char** map, int width, int height, Graph* mapGraph, direction previousRoadDirection, int lengthCounter) {
	lengthCounter += 1;
	if (y - 1 >= 0 && map[y - 1][x] == ROAD && previousRoadDirection != DOWN) {
		readRoad(mapGraph, map, x, y - 1, UP, lengthCounter, width, height);
	}
	if (y + 1 < height && map[y + 1][x] == ROAD && previousRoadDirection != UP) {
		readRoad(mapGraph, map, x, y + 1, DOWN, lengthCounter, width, height);
	}
	if (x - 1 >= 0 && map[y][x - 1] == ROAD && previousRoadDirection != RIGHT) {
		readRoad(mapGraph, map, x - 1, y, LEFT, lengthCounter, width, height);
	}
	if (x + 1 < width && map[y][x + 1] == ROAD && previousRoadDirection != LEFT) {
		readRoad(mapGraph, map, x + 1, y, RIGHT, lengthCounter, width, height);
	}
}

int readRoadLength(int x, int y, int lengthCounter, char** map, direction roadDirection, Graph* mapGraph, int width, int height) {
	while (map[y][x] == ROAD) {
		lengthCounter += 1;
		if (roadDirection == UP) {
			if (y - 1 >= 0 && map[y - 1][x] == ROAD) {
				y -= 1;
			}
			else if (y - 1 >= 0 && map[y - 1][x] == CITY_SYMBOL) {
				addRoad();
				break;
			}
			else {
				checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
				break;
			}
		}
		else if (roadDirection == DOWN) {
			if (y + 1 < height && map[y + 1][x] == ROAD) {
				y += 1;
			}
			else if (y + 1 < height && map[y + 1][x] == CITY_SYMBOL) {
				addRoad();
				break;
			}
			else {
				checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
				break;
			}
		}
		else if (roadDirection == LEFT) {
			if (x - 1 >= 0 && map[y][x - 1] == ROAD) {
				x -= 1;
			}
			else if (x - 1 >= 0 && map[y][x - 1] == CITY_SYMBOL) {
				addRoad();
				break;
			}
			else {
				checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
				break;
			}
		}
		else if (roadDirection == RIGHT) {
			if (x + 1 < width && map[y][x + 1] == ROAD) {
				x += 1;
			}
			else if (x + 1 < width && map[y][x + 1] == CITY_SYMBOL) {
				addRoad();
				break;
			}
			else {
				checkRoads(x, y, map, width, height, mapGraph, roadDirection, lengthCounter);
				break;
			}
		}
		else {
			break;
		}
	}
	return lengthCounter;
}

void readMap(int height, int width, char** map, Graph* mapGraph) {
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			if (map[y][x] == CITY_SYMBOL) {
				addCityName(x, y, map, width, height, mapGraph);
				checkRoads(x, y, map, width, height, mapGraph, NONE);
			}
		}
	}
}

int main() {
	int width, height;
	cin >> width;
	cin >> height;
	Graph* mapGraph = new Graph();
	char** map = new char*[height];
	for (int i = 0; i < height; i++) {
		map[i] = new char[width];
	}
	getMap(height, width, map);
	readMap(height, width, map, mapGraph);
	for (int i = 0; i < height; i++) {
		delete[] map[i];
	}
	delete[] map;
	return 0;
}