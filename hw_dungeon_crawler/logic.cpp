#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    //return nullptr;
    ifstream infs;
    infs.open(fileName);
    if (!infs.is_open()) {
        return nullptr;
    }
    if (!(infs >> maxRow >> maxCol) || maxRow <= 0 || maxCol <= 0 || maxRow > 999999 || maxCol > 999999) {
        return nullptr;
    }
    if (maxRow > INT32_MAX / maxCol || maxCol > INT32_MAX / maxRow) {
        return nullptr;
    }

    // allocate map
    char** map = createMap(maxRow, maxCol);
    if (map == nullptr) {
        deleteMap(map,maxRow);
        return nullptr;
    }
    int playerRow;
    int playerCol;
    //infs >> maxRow >> maxCol;
    if (!(infs >>playerRow>>playerCol) || playerRow < 0 || playerCol < 0 || playerRow >= maxRow || playerCol >= maxCol) {
        return nullptr;
    }
    infs.ignore(); // skip newline

    //bool playerFound = false;
    bool escape = false;
    for (int i = 0; i < maxRow; ++i) {
        for (int j = 0; j < maxCol; ++j) {
            infs >> map[i][j];
            //check if any of them fail
            if(infs.fail()){
                deleteMap (map, maxRow);
                return nullptr;
            }
            if (map[i][j] == TILE_EXIT || map[i][j] == TILE_DOOR){
                 escape = true;
            }
            if(map[i][j] != TILE_AMULET || map[i][j] != TILE_DOOR || map[i][j] != TILE_EXIT || map[i][j] != TILE_MONSTER || map[i][j] != TILE_OPEN || map[i][j] != TILE_PILLAR || map[i][j] != TILE_PLAYER || map[i][j] != TILE_TREASURE)
            {
                deleteMap(map, maxRow);
                return nullptr;
            }
            /*char current_position;
            infs >> current_position;
            current_position = map[i][j];*/
        }
    }
    player.row = playerRow;
    player.col = playerCol;
    map[playerRow][playerCol] = TILE_PLAYER;
    /*if(current_position == TILE_PLAYER){
        deleteMap (map, maxRow);
        return nullptr;
    }*/
    /*if (!playerFound) {
        for (int i = 0; i < maxRow; ++i) {
            delete[] map[i];
        }
        delete[] map;
        return nullptr;
    } */
    if (!escape) {
        return nullptr;
    }
    if (infs >> std::ws && !infs.eof()) {
        throw std::runtime_error("Too many values");
    }
    infs.close();
    return map; 
}


/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    switch (input) {
        case 'w':  // upwards
            nextRow -= 1;
            break;
        case 's':  // downwards
            nextRow += 1;
            break;
        case 'd':  // right
            nextCol += 1;
            break;
        case 'a':  // left
            nextCol -= 1;
            break;
        default:
            break; // else
    }
    // complete
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    // return nullptr;
    if (maxRow <= 0 || maxCol <= 0 || maxRow > 999999 || maxCol > 999999) { // check if valid
         return nullptr;
    }
    // column major array --> might need to change to row major later
    char** map = new char*[maxRow]; // allocate rows
    for (int i = 0; i < maxRow; ++i) { // i for columns
        map[i] = new char[maxCol]; // allocate columns
        for (int j = 0; j < maxCol; ++j) { // j for rows
            map[i][j] = TILE_OPEN;
        } 
    }
    return map;
    // finish: missing one test - 07C
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    if (map != nullptr) { // first check if map is null or not
        for (int i = 0; i < maxRow; ++i) {
            delete[] map[i]; // deallocate each row
        }
        delete[] map; // deallocate array
        map = nullptr; // to avoid floating pointer
    }
    maxRow = 0; // shows that map has been deleted
    // complete
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    // return nullptr;
    if (maxRow <= 0 || maxCol <= 0 || map == nullptr ) {//|| maxRow > 999 || maxCol > 999) {
        return nullptr;
    }

    if (maxRow > 999999 / 2 || maxCol > 999999 / 2 ) {
        return nullptr;
    }

    int nextRow = 2*maxRow; // doubling
    int nextCol = 2*maxCol; // doubling

    char** resizedMap = createMap(nextRow, nextCol);

    for (int i = 0; i < maxRow; ++i) { 
        for (int j = 0; j < maxCol; ++j) {
            char tile = map[i][j];
            char tileVal = tile;

            // set tile val to open for quadrants B, C, and D
            if (tile == TILE_PLAYER) {
                tileVal = TILE_OPEN;
            }

            // assigning tile
            resizedMap[i][j] = tile;                // top-left (A)
            resizedMap[i][j + maxCol] = tileVal;  // top-right (B)
            resizedMap[i + maxRow][j] = tileVal;  // bottom-left (C)
            resizedMap[i + maxRow][j + maxCol] = tileVal; // bottom-right (D)
        }
    }

    // deallocate the original map
    for (int i = 0; i < maxRow; ++i) {
        delete[] map[i];
    }
    delete[] map;
 
    maxRow = nextRow;
    maxCol = nextCol;

    return resizedMap;
    /*if (map != nullptr) {
        return resizedMap;
    }
    else {
        return nullptr;
    } */
}


/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol) {
    if (nextRow < 0 || nextRow >= maxRow || nextCol < 0 || nextCol >= maxCol) {
        //cout << "stay 1" << endl;
        return STATUS_STAY;
    }
    if (map[nextRow][nextCol] == TILE_PILLAR || map[nextRow][nextCol] == TILE_MONSTER) {
        //cout << "stay 12" << endl;
        return STATUS_STAY;
    }

    if (map[nextRow][nextCol] == TILE_TREASURE) {
        player.treasure++;
        map[player.row][player.col] = TILE_OPEN; // old position is now open again
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER; 
        return STATUS_TREASURE;
    }
    else if (map[nextRow][nextCol] == TILE_AMULET) { 
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER; 
        return STATUS_AMULET;
    }
    else if (map[nextRow][nextCol] == TILE_DOOR) {
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER; 
        //map[player.row][player.col] = TILE_PLAYER;
        return STATUS_LEAVE;
    }
    else if (map[nextRow][nextCol] == TILE_EXIT) {
        if (player.treasure >= 1) {
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow;
            player.col = nextCol;
            map[nextRow][nextCol] = TILE_PLAYER; 
            return STATUS_ESCAPE;
        }
        else {
            //map[player.row][player.col] = TILE_OPEN;
            //cout << "stay 14" << endl;
            return STATUS_STAY; // treat as a pillar
        }
    }
    else { // deafult return statement if none of the above is true
        /*map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER;
        return STATUS_MOVE;*/
    //}
        if (map[nextRow][nextCol] == TILE_OPEN) {
            map[player.row][player.col] = TILE_OPEN;
            player.row = nextRow; // update player position
            player.col = nextCol;
            map[nextRow][nextCol] = TILE_PLAYER; 
            return STATUS_MOVE;
        } 
        else {
            return STATUS_STAY; 
        }
    }
} // finished: missing one test

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    int x = player.row;
    int y = player.col;
    //bool attack = false;

    // upward
    for (int i = x - 1; i >= 0; --i) {
        if (map[i][y] == TILE_PILLAR) {
            break; // pillar blocks
        }
        if (map[i][y] == TILE_MONSTER) { // monster blocks
            map[i][y] = TILE_OPEN; // monsters tile is open
            map[i + 1][y] = TILE_MONSTER; // move monster
        }
    } // follow similar logic for the rest

    // downward
    for (int i = x + 1; i < maxRow; ++i) {
        if (map[i][y] == TILE_PILLAR) {
            break;
        }
        if (map[i][y] == TILE_MONSTER) {
            map[i][y] = TILE_OPEN;
            map[i - 1][y] = TILE_MONSTER;
        }
    }

    // rightward
    for (int j = y + 1; j < maxCol; ++j) {
        if (map[x][j] == TILE_PILLAR) {
            break;
        }
        if (map[x][j] == TILE_MONSTER) {
            map[x][j] = TILE_OPEN;
            map[x][j - 1] = TILE_MONSTER;
        }
    }

    // leftward
    for (int j = y - 1; j >= 0; --j) {
        if (map[x][j] == TILE_PILLAR) {
            break;
        }
        if (map[x][j] == TILE_MONSTER) {
            map[x][j] = TILE_OPEN;
            map[x][j + 1] = TILE_MONSTER;
        }
    }
    
    if (map[x][y] == TILE_MONSTER) {
        return true;
    }
    else {
        return false;
    }
}


/*resize map:
if (maxRow <= 0 || maxCol <= 0 || map == nullptr) {
        return nullptr;
    }

    int nextRow = 2*maxRow; // doubling
    int nextCol = 2*maxCol; // doubling

    char** resizedMap = createMap(nextRow, nextCol);
    for (int i = 0; i < maxRow; ++i) { 
        for (int j = 0; j < maxCol; ++j) {
            resizedMap[i][j] = map[i][j];
        }
        int row1 = maxRow;
        int col1 = maxCol;

        for(int i = 0; i < maxRow; ++i) { // down
            for(int j = 0; j < maxCol; ++j){
                resizedMap[i + row1][j] = map[i][j];
                if(map[i][j] == TILE_PLAYER){
                    resizedMap[i + row1][j] = TILE_OPEN;
                }
            }   
        }

        for(int i = 0; i < maxRow; ++i) { // diagonal
            for(int j = 0; j < maxCol; ++j){
                resizedMap[i + row1][j + col1] = map[i][j];
                if(map[i][j] == TILE_PLAYER){
                    resizedMap[i + row1][j + col1]  = TILE_OPEN;
                }
            }
        }

        for(int i = 0; i < maxRow; ++i) { // right
            for(int j = 0; j < maxCol; ++j){
                resizedMap[i][j + maxCol] = map[i][j];
                if(map[i][j] == TILE_PLAYER){
                    resizedMap[i][j + maxCol]  = TILE_OPEN;
                }
            }
        }
        int myRow = maxRow;
        deleteMap (map, myRow);
        maxRow = nextRow;
        maxCol = nextCol;
    
    if (map != nullptr) {
        return resizedMap;
    }
    else {
        return nullptr;
    } */
   //}
   //return resizedMap;
   