#pragma once
#ifndef _POSITION_H_
#define _POSITION_H_
#include <vector>
#include "Parameters.h"
/*
Class này quản lý một vector các vị trí xuất hiện của một enemy, dùng cho pooling
*/
struct PosInfo
{
	float x;
	float y;
};

class PositionManager
{
protected:
	World * manager;
	std::vector<PosInfo*> list_pos;	// vector chứa các cặp vị trí (x,y)
	int size;					// size của vector
	int index;					// trỏ đến vị trí của một cặp (x,y) trong vector
	int width;					// width của enemy (để tính xem nó có xuất hiện trong camera hay không)
	int height;					// height của enemy (để tính xem nó có xuất hiện trong camera hay không)
	ENEMY_TYPE enemy_type;
public:
	PositionManager();
	// Truyền vào world, loại enemy và kích thước của loại enemy đó
	PositionManager(World * manager, ENEMY_TYPE enemy_type, int width, int height);
	~PositionManager();

	//-- TO DO: Load từ file vào vector
	void ImportFromFile(char* path);

	// Trỏ đến vị trí kế tiếp trong vector
	void Next();

	// Trỏ đến vị trí phía sau trong vector
	void Back();

	// Kiểm tra pos cùng với width height có nằm trong camera hay không
	bool IsInCamera(PosInfo * target);
};

#endif
