#include "Generator.h"



Generator::Generator(){
	maxLevelX = 15;
	maxLevelY = 15;
}


Generator::~Generator(){
}

std::vector<std::string> Generator::generate(){
	srand(time(NULL));
	std::vector<std::string> returnVal;
	for (int i = 0; i < maxLevelY; i++) {
		level.emplace_back();
		for (int j = 0; j < maxLevelX; j++) {
			level.back().emplace_back();
			level.back().back().val = '#';
			level.back().back().x = j;
			level.back().back().z = i;
		}
	}
	rooms = makeRooms(level);
	tunnel = makeCorridor(level);
	izpis(level);
	markDoors(level, rooms, tunnel);
	makeDungeon(level);
	for (auto& itZ : level) {
		returnVal.emplace_back();
		for (auto& itX : itZ) {
			returnVal.back().push_back(itX.val);
		}
	}
	return returnVal;
}


std::unordered_map<int, Room> Generator::makeRooms(std::vector< std::vector<Point> >& dng) {
	//	std::vector< std::vector<Point> >* lvl = &dng;
	std::unordered_map<int, Room> rooms;
	int mini = 2;
	int maxi = 6;
	int xLen, yLen, xPos, yPos;
	int attempts = 200;
	bool needsDel = false;
	for (int i = 0; i < attempts; i++) {
		needsDel = false;
		do {
			xPos = rand() % (dng.size() - 1);
		} while (xPos % 2 == 0);
		do {
			yPos = rand() % (dng.size() - 1);
		} while (yPos % 2 == 0);
		do {
			xLen = (rand() % (maxi - mini)) + mini;
		} while (xLen % 2 == 0);
		do {
			yLen = (rand() % (maxi - mini)) + mini;
		} while (yLen % 2 == 0);

		if (xPos + xLen >= dng.size() || yPos + yLen >= dng.size()) {
			continue;
		}
		rooms[i].sizeX = xLen;
		rooms[i].sizeY = yLen;
		rooms[i].bottomRightX = xPos + xLen - 1;
		rooms[i].bottomRightZ = yPos + yLen - 1;
		rooms[i].bottomLeftX = xPos;
		rooms[i].bottomLeftZ = yPos + yLen - 1;
		rooms[i].topRightX = xPos + xLen - 1;
		rooms[i].topRightZ = yPos;
		rooms[i].x = xPos;
		rooms[i].z = yPos;
		for (auto &it : rooms) {
			if (it.first != i) {
				if (rooms[i].x >= (it.second.x - 1) && rooms[i].x <= (it.second.x + it.second.sizeX + 1)) {
					if (rooms[i].z >= (it.second.z - 1) && rooms[i].z <= (it.second.z + it.second.sizeY + 1)) {
						needsDel = true;
					}
				}
				if (rooms[i].bottomRightX >= (it.second.x - 1) && rooms[i].bottomRightX <= (it.second.x + it.second.sizeX + 1)) {
					if (rooms[i].bottomRightZ >= (it.second.z - 1) && rooms[i].bottomRightZ <= (it.second.z + it.second.sizeY + 1)) {
						needsDel = true;
					}
				}
				if (rooms[i].bottomLeftX >= (it.second.x - 1) && rooms[i].bottomLeftX <= (it.second.x + it.second.sizeX + 1)) {
					if (rooms[i].bottomLeftZ >= (it.second.z - 1) && rooms[i].bottomLeftZ <= (it.second.z + it.second.sizeY + 1)) {
						needsDel = true;
					}
				}
				if (rooms[i].topRightX >= (it.second.x - 1) && rooms[i].topRightX <= (it.second.x + it.second.sizeX + 1)) {
					if (rooms[i].topRightZ >= (it.second.z - 1) && rooms[i].topRightZ <= (it.second.z + it.second.sizeY + 1)) {
						needsDel = true;
					}
				}
			}
		}
		if (needsDel) {
			rooms.erase(i);
		}
	}
	std::cout << rooms.size() << " <-- size of rooms\n";
	for (auto& it : rooms) {
		for (int z = it.second.z; z < (it.second.z + it.second.sizeY); z++) {
			for (int x = it.second.x; x < (it.second.x + it.second.sizeX); x++) {
				dng[z][x].val = 'F';
			}
		}
	}
	return rooms;
}

bool errorWB = false;
std::vector<Corridor> Generator::makeCorridor(std::vector<std::vector<Point>>& dng) {
	Corridor tmp;
	bool hasFound = false;
	std::vector<Corridor>tunnel;
	std::vector<int> openCorrID;
	for (auto& itZ : dng) {
		for (auto& itX : itZ) {
			tmp.x = itX.x;
			tmp.z = itX.z;
			tmp.dirs = checkDirs(tmp, dng, "start");
			if (getNumOfDirs(tmp, true) >= 1) {
				tunnel.emplace_back(tmp);
				printf("start point found!: %d %d \n", tunnel.back().z, tunnel.back().x);
				dng[tunnel.back().z][tunnel.back().x].val = 'S';
				hasFound = true;
				break;
			}
		}
		if (hasFound) {
			break;
		}
	}
	openCorrID.push_back(0);
	std::string ogn = "start";
	printf("loading... \n");
	int stevc = 0;
	bool maze = true;
	while (maze) {
		stevc++;
		int tmpX;
		int tmpZ;
		tunnel.back().dirs = checkDirs(tunnel.back(), dng, ogn);
		if (getNumOfDirs(tunnel.back(), true) > 0) {
			std::string path = declareDir(tunnel.back().dirs);
			if (path == "north") {
				tmpX = tunnel.back().x;
				tmpZ = tunnel.back().z;
				tunnel.emplace_back();
				tunnel.back().x = tmpX;
				tunnel.back().z = tmpZ - 1;
				tunnel.back().dirs = checkDirs(tunnel.back(), dng, "south");
				ogn = "south";
			}

			else if (path == "south") {
				tmpX = tunnel.back().x;
				tmpZ = tunnel.back().z;
				tunnel.emplace_back();
				tunnel.back().x = tmpX;
				tunnel.back().z = tmpZ + 1;
				tunnel.back().dirs = checkDirs(tunnel.back(), dng, "north");
				ogn = "north";
			}

			else if (path == "east") {
				tmpX = tunnel.back().x;
				tmpZ = tunnel.back().z;
				tunnel.emplace_back();
				tunnel.back().x = tmpX + 1;
				tunnel.back().z = tmpZ;
				tunnel.back().dirs = checkDirs(tunnel.back(), dng, "west");
				ogn = "west";
			}

			else if (path == "west") {
				tmpX = tunnel.back().x;
				tmpZ = tunnel.back().z;
				tunnel.emplace_back();
				tunnel.back().x = tmpX - 1;
				tunnel.back().z = tmpZ;
				tunnel.back().dirs = checkDirs(tunnel.back(), dng, "east");
				ogn = "east";
			}
			dng[tunnel.back().z][tunnel.back().x].val = 'S';
			if (getNumOfDirs(tunnel.back(), true) > 1) {
				openCorrID.push_back(tunnel.size() - 1);
			}
		}
		else {
			Corridor tmp;
			if (!openCorrID.empty()) {
				tmp = tunnel[openCorrID.back()];
				tunnel[openCorrID.back()] = tunnel.back();
				tunnel.back() = tmp;
				openCorrID.pop_back();
			}
			else {
				maze = findPoint(dng, tunnel);
			}
			errorWB = true;
		}
	}
	printf("load complete!\n");
	return tunnel;
}

void Generator::makeDungeon(std::vector<std::vector<Point>> dng) {
	std::ofstream file("dungeon.txt");
	for (auto itY : dng) {
		for (auto itX : itY) {
			file << itX.val;
		}
		file << '\n';
	}
}

std::unordered_map<std::string, bool> Generator::checkDirs(Corridor p, std::vector<std::vector<Point>> dng, std::string origin) {
	std::unordered_map<std::string, bool> tmp;
	if (p.x - 2 >= 0) {
		if (dng[p.z][p.x - 2].val == '#') {
			if (checkNS((p.x - 1), p.z, dng)) {
				if (origin != "west") {
					tmp["west"] = true;
				}
				else {
					tmp["west"] = false;
				}
			}
			else {
				tmp["west"] = false;
			}
		}
		else {
			tmp["west"] = false;
		}
	}
	else {
		tmp["west"] = false;
	}
	if (p.x + 2 < maxLevelX) {
		if (dng[(p.z)][p.x + 2].val == '#') {
			if (checkNS((p.x + 1), p.z, dng)) {
				if (origin != "east") {
					tmp["east"] = true;
				}
				else {
					tmp["east"] = false;
				}
			}
			else {
				tmp["east"] = false;
			}
		}
		else {
			tmp["east"] = false;
		}
	}
	else {
		tmp["east"] = false;
	}
	if (p.z + 2 < maxLevelY) {
		if (dng[(p.z + 2)][p.x].val == '#') {
			if (checkEW(p.x, p.z + 1, dng)) {
				if (origin != "south") {
					tmp["south"] = true;
				}
				else {
					tmp["south"] = false;
				}
			}
			else {
				tmp["south"] = false;
			}
		}
		else {
			tmp["south"] = false;
		}
	}
	else {
		tmp["south"] = false;
	}
	if (p.z - 2 >= 0) {
		if (dng[(p.z - 2)][p.x].val == '#') {
			if (checkEW(p.x, p.z - 1, dng)) {
				if (origin != "north") {
					tmp["north"] = true;
				}
				else {
					tmp["north"] = false;
				}
			}
			else {
				tmp["north"] = false;
			}
		}
		else {
			tmp["north"] = false;
		}
	}
	else {
		tmp["north"] = false;
	}
	return tmp;
}

bool Generator::checkNS(int x, int z, std::vector<std::vector<Point>> dng) {
	if (z - 1 < 0) {
		if (dng[z + 1][x].val == '#') {
			return true;
		}
		else {
			return false;
		}
	}
	else if (z + 1 >= maxLevelY) {
		if (dng[z - 1][x].val == '#') {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (dng[z + 1][x + 1].val == '#' && dng[z - 1][x].val == '#') {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Generator::checkEW(int x, int z, std::vector<std::vector<Point>> dng) {
	if (x - 1 < 0) {
		if (dng[z][x + 1].val == '#') {
			return true;
		}
		else {
			return false;
		}
	}
	else if (x + 1 >= maxLevelX) {
		if (dng[z][x - 1].val == '#') {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (dng[z][x + 1].val == '#' && dng[z][x - 1].val == '#') {
			return true;
		}
		else {
			return false;
		}
	}
}

int Generator::getNumOfDirs(Corridor p, bool wut) {
	int counter = 0;
	if (!p.dirs.empty()) {
		for (auto& it : p.dirs) {
			if (it.second == wut) {
				counter++;
			}
		}
	}
	return counter;
}

std::string Generator::declareDir(std::unordered_map<std::string, bool>dirs) {
	//printf("declareDir: %d %d %d %d\n", dirs["north"], dirs["east"], dirs["south"], dirs["west"]);
	std::vector<std::string> dirValVec;
	int id;
	for (auto& it : dirs) {
		if (it.second) {
			dirValVec.push_back(it.first);
		}
	}
	if (dirValVec.size() > 1) {
		id = rand() % (dirValVec.size() - 1);
	}
	else {
		id = 0;
	}
	return dirValVec[id];
}

void Generator::izpis(std::vector<std::vector<Point>> dng) {
	for (auto& itZ : dng) {
		for (auto& itX : itZ) {
			printf("%c ", itX.val);
		}
		printf("\n");
	}
	printf("\n\n\n");
}

bool Generator::findPoint(std::vector<std::vector<Point>>& dng, std::vector<Corridor>& tunnel) {
	Corridor tmp;
	bool hasFound = false;
	for (auto& itZ : dng) {
		for (auto& itX : itZ) {
			tmp.x = itX.x;
			tmp.z = itX.z;
			tmp.dirs = checkDirs(tmp, dng, "start");
			if (getNumOfDirs(tmp, true) >= 1 && dng[tmp.z][tmp.x].val == '#') {
				tunnel.emplace_back(tmp);
				//		printf("start point found!: %d %d \n", tunnel.back().z, tunnel.back().x);
				dng[tunnel.back().z][tunnel.back().x].val = 'S';
				hasFound = true;
				break;
			}
		}
		if (hasFound) {
			break;
		}
	}
	return hasFound;
}

void Generator::markDoors(std::vector<std::vector<Point>>& dng, std::unordered_map<int, Room>& rooms, std::vector<Corridor>& tunnel) {
	int x, z;
	std::vector<Corridor> doors;
	std::vector<Corridor> deadEnds;
	for (auto &rIt : rooms) {
		//north
		for (x = rIt.second.x; x < rIt.second.topRightX + 1; x++) {
			int tmpX = x;
			int tmpZ = rIt.second.z - 1;
			if (tmpZ - 1 >= 0) {
				if (dng[tmpZ - 1][tmpX].val == 'S' && dng[tmpZ + 1][tmpX].val == 'F' && dng[tmpZ][tmpX].val == '#') {
					dng[tmpZ][x].val = 'D';
					CoordStr tmp;
					tmp.x = tmpX;
					tmp.z = tmpZ;
					rIt.second.psbDrs.emplace_back(tmp);
				}
			}
		}
		//east
		for (z = rIt.second.topRightZ - 1; z < rIt.second.bottomRightZ + 1; z++) {
			int tmpX = x;
			int tmpZ = z;
			if (tmpX + 1 < maxLevelX) {
				if (dng[tmpZ][tmpX + 1].val == 'S' && dng[tmpZ][tmpX - 1].val == 'F' && dng[tmpZ][tmpX].val == '#') {
					dng[tmpZ][tmpX].val = 'D';
					CoordStr tmp;
					tmp.x = tmpX;
					tmp.z = tmpZ;
					rIt.second.psbDrs.emplace_back(tmp);
				}
			}
		}
		//south
		for (; x > rIt.second.bottomLeftX - 1; x--) {
			int tmpX = x;
			int tmpZ = z;
			if (tmpZ + 1 < maxLevelY) {
				if (dng[tmpZ + 1][tmpX].val == 'S' && dng[tmpZ - 1][tmpX].val == 'F' && dng[tmpZ][tmpX].val == '#') {
					dng[tmpZ][tmpX].val = 'D';
					CoordStr tmp;
					tmp.x = tmpX;
					tmp.z = tmpZ;
					rIt.second.psbDrs.emplace_back(tmp);
				}
			}

		}
		//west
		for (; z >= rIt.second.z - 1; z--) {
			int tmpX = x;
			int tmpZ = z;
			if (tmpX - 1 >= maxLevelX) {
				if (dng[tmpZ][tmpX + 1].val == 'F' && dng[tmpZ][tmpX - 1].val == 'S' && dng[tmpZ][tmpX].val == '#') {
					dng[tmpX][tmpZ].val = 'D';
					CoordStr tmp;
					tmp.x = tmpX;
					tmp.z = tmpZ;
					rIt.second.psbDrs.emplace_back(tmp);
				}
			}
		}
	}
	for (auto rIt : rooms) {
		int ID;
		if (rIt.second.psbDrs.size() > 1) {
			ID = rand() % (rIt.second.psbDrs.size() - 1);
		}
		else {
			ID = 0;
		}
		for (int i = 0; i < rIt.second.psbDrs.size(); i++) {
			if (i != ID) {
				dng[rIt.second.psbDrs[i].z][rIt.second.psbDrs[i].x].val = '#';
			}
			else {
				doors.emplace_back();
				doors.back().x = rIt.second.psbDrs[i].x;
				doors.back().z = rIt.second.psbDrs[i].z;
			}
		}
	}
	findDeadEnds(dng, deadEnds, tunnel);
	while (!deadEnds.empty()) {
		findDeadEnds(dng, deadEnds, tunnel);
		for (auto& it : deadEnds) {
			dng[it.z][it.x].val = '#';
			for (size_t i = 0; i < tunnel.size(); i++) {
				if (tunnel[i].x == it.x && tunnel[i].z == it.z) {
					tunnel[i] = tunnel.back();
					tunnel.pop_back();
				}
			}
		}
	}
}

void Generator::findDeadEnds(std::vector<std::vector<Point>>& dng, std::vector<Corridor>& deadEnds, std::vector<Corridor>&tunnel) {
	deadEnds.clear();
	for (auto it : tunnel) {
		int tmpX = it.x;
		int tmpZ = it.z;
		int stevc = 0;
		bool isAtDoor = false;
		if (tmpZ - 1 >= 0) {
			if (dng[tmpZ - 1][tmpX].val == '#') {
				stevc++;
			}
			else if (dng[tmpZ - 1][tmpX].val == 'D') {
				isAtDoor = true;
			}
		}
		else {
			stevc++;
		}
		if (tmpZ + 1 < maxLevelY) {
			if (dng[tmpZ + 1][tmpX].val == '#' || dng[tmpZ + 1][tmpX].val == 'F') {
				stevc++;
			}
			if (dng[tmpZ + 1][tmpX].val == 'D') {
				isAtDoor = true;
			}
		}
		else {
			stevc++;
		}
		if (tmpX - 1 >= 0) {
			if (dng[tmpZ][tmpX - 1].val == '#' || dng[tmpZ][tmpX - 1].val == 'F') {
				stevc++;

			}
			else if (dng[tmpZ][tmpX - 1].val == 'D' || dng[tmpZ][tmpX - 1].val == 'F') {
				isAtDoor = true;
			}
		}
		else {
			stevc++;
		}
		if (tmpX + 1 < maxLevelX) {
			if (dng[tmpZ][tmpX + 1].val == '#' || dng[tmpZ][tmpX + 1].val == 'F') {
				stevc++;

			}
			else if (dng[tmpZ][tmpX + 1].val == 'D') {
				isAtDoor = true;
			}
		}
		else {
			stevc++;
		}
		if (stevc >= 3 && (!isAtDoor)) {
			deadEnds.emplace_back();
			deadEnds.back().x = tmpX;
			deadEnds.back().z = tmpZ;
		}
	}
}
