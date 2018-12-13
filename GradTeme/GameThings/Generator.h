#pragma once
#include <iostream>
#include <stdio.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include <unordered_map>

struct CoordStr {
	int x;
	int z;
};
struct Room {
	int x;
	int z;
	int topRightX;
	int topRightZ;
	int bottomRightX;
	int bottomRightZ;
	int bottomLeftX;
	int bottomLeftZ;
	int sizeX;
	int sizeY;
	std::vector<CoordStr> psbDrs;

};

struct Corridor {
	int x;
	int z;
	std::unordered_map<std::string, bool> dirs;
};

struct Point {
	char val;
	int x;
	int z;
};
class Generator
{
public:
	Generator();
	~Generator();
	std::vector<std::string> generate();
	std::unordered_map<int, Room> getRooms() { return rooms; }
private:
	std::unordered_map<int, Room> makeRooms(std::vector<std::vector<Point>>&);
	std::vector<Corridor> makeCorridor(std::vector<std::vector<Point>>&);
	void makeDungeon(std::vector<std::vector<Point>>);
	std::unordered_map<std::string, bool> checkDirs(Corridor, std::vector<std::vector<Point>>, std::string);
	bool checkNS(int x, int z, std::vector<std::vector<Point>>);
	bool checkEW(int x, int z, std::vector<std::vector<Point>>);
	int getNumOfDirs(Corridor, bool);
	std::string declareDir(std::unordered_map<std::string, bool>);
	void izpis(std::vector<std::vector<Point>>);
	bool findPoint(std::vector<std::vector<Point>>&, std::vector<Corridor>&);
	void markDoors(std::vector<std::vector<Point>>&, std::unordered_map<int, Room>&, std::vector<Corridor>&);
	void findDeadEnds(std::vector<std::vector<Point>>&, std::vector<Corridor>&, std::vector<Corridor>&);


	std::unordered_map<int, Room> rooms;
	std::vector<std::vector<Point>> level;
	std::vector<Corridor> tunnel;
	int maxLevelX;
	int maxLevelY;
};

