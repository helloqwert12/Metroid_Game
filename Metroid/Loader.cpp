#include "Loader.h"
#include <fstream>
#include <sstream>
#include "trace.h"
#include "Brick.h"
#include <utility>
#include <string.h>
#include "World.h"
Loader::Loader()
{
}

Loader::Loader(LPD3DXSPRITE spriteHandler, int room_number, World * manager)
{
	this->spriteHandler = spriteHandler;

	this->room_number = room_number;
	this->manager = manager;
	// Build đường dẫn đến matrix dựa vào room
	this->matrix_path = "map\\matrix_room_" + std::to_string(room_number) + ".txt";

	// Build đường dẫn đến quadtree dựa vào room
	this->quadtree_path = "map\\quadtree_room_" + std::to_string(room_number) + ".txt";

	// Build đường dẩn đến file info dựa vào room
	this->info_path = "map\\info_room_" + std::to_string(room_number) + ".txt";

	// Đọc file matrix
	this->ReadMatrixFromFile(matrix_path.c_str());

	// Đọc file quadtree
	this->ReadQuadTreeFromFile(quadtree_path.c_str());


	// Link các node lại
	this->LinkNodes();

	// rootGONode tại manager sẽ do ở đây quản lý
	this->manager->rootQNode = this->rootQNode;
}


Loader::~Loader()
{
}

// Tạo các GameObject dựa theo id
void Loader::ReadMatrixFromFile(const char* path)
{
	int row_count = 0;		// index của dòng đang đọc
	int width = 0;			// width của room
	int height = 0;			// height của room
	int counter = 0;		// biến counter để tính key cho map, biến này đếm liên tục từ phải sang trái trên xuống dưới

	//Read file info of file
	ifstream f;
	try
	{
		f.open(path);
		
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Loader class]: Failed to load matrix path");
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên cũng bỏ qua, vì dòng đầu bị lỗi
		if (row_count == 0)
		{
			row_count++;
			continue;
		}

		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Dòng này chứa width và height của room này
		if (row_count == 1)
		{	
			height = stoi(pos[0]);
			width = stoi(pos[1]);
			row_count++;
			continue;
		}

		// Đây là dòng thứ 3 chứa width và height của tile (mặc định là 32 nên khỏi xét)
		if (row_count == 2)
		{
			row_count++;
			continue;
		}

		// Nếu dòng không có gì thì bỏ qua
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Những dòng còn lại là map
		for (int i = 0; i < size; i++)
		{
			int id = stoi(pos[i]);
			// Xét xem id là loại gì
			// Nếu id là 8 thì bỏ qua (ô trống trong sprite)
			if (id == 8)
			{
				counter++;
				continue;
			}

			// Tính pos_x và pos_y cho Brick
			int pos_x = i * 32;
			int pos_y = height*32 - ((row_count - 3) * 32);	// trừ đi 3 dòng đầu không tính
			// chỗ y trên này tính theo world???

			Brick* brick = new Brick(spriteHandler, manager, BLUE, id, pos_x, pos_y);

			pair<int, GameObject*> pair_to_add(counter, brick);
			mapGameObjects.insert(pair_to_add);

			// cập nhật counter
			counter++;
		}
		row_count++;
	}
	f.close();
}

//Gọi hàm này sau khi gọi hàm ReadMatrixFromFile !!!
void Loader::ReadQuadTreeFromFile(const char* path)
{
	int row_count = 0;
	//Read file info of file
	ifstream f;
	try
	{
		f.open(path);
	}
	catch (std::fstream::failure e)
	{
		trace(L"[Loader class]: Failed to load matrix path");
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên cũng bỏ qua, vì dòng đầu bị lỗi
		if (row_count == 0)
		{
			row_count++;
			continue;
		}

		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Nếu dòng không có gì thì bỏ qua
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Đọc dữ liệu mỗi dòng
		// index 0 là nodeID
		const int nodeID = stoi(pos[0]);

		// index 1 và 2 là x và y
		int node_x = stoi(pos[1]);
		int node_y = stoi(pos[2]);

		// index 3 và 4 là width và height
		int node_w = stoi(pos[3]);
		int node_h = stoi(pos[4]);

		// Khởi tạo QNode và gán vào
		QNode* node = new QNode(nodeID, node_x, node_y, node_w, node_h);

		// Nếu không có list GameObject phía sau thì dùng
		if (size <= 5)
		{
			pair<int, QNode*> pair_to_add(nodeID, node);
			mapQNodes.insert(pair_to_add);
			row_count++;
			continue;
		}

		// Những thằng còn lại là index của GameObject trong file matrix
		// Add vào node
		for (int i = 5; i < size; i++)
		{
			int index = stoi(pos[i]);

			// Phải xem trước xem index đó có trong map hay không?
			// (Vì trong map matrix có id = 8 không xét do là nền)
			map<int, GameObject*>::const_iterator temp = mapGameObjects.find(index);
			// Nếu không tồn tại thì bỏ qua
			if (temp == mapGameObjects.end())
				continue;

			switch (mapGameObjects[index]->GetType())
			{
			case BRICK:
				// ép kiểu về Brick
				Brick* brick = (Brick*)mapGameObjects[index];
				node->objects->AddGameObject(brick);
				break;
			}
		}
		
		// Insert vào map
		pair<int, QNode*> pair_to_add(nodeID, node);
		mapQNodes.insert(pair_to_add);

		row_count++;
	}
	f.close();
}

void Loader::ReadInfoFromFile(const char * path)
{
	int row_count = 0;
	ifstream f;
	try
	{
		f.open(path);
	}
	catch (std::fstream::failure e)
	{
		return;
	}
	string line;
	while (!f.eof())
	{
		vector<string> pos;		// vector dùng để chứa dữ liệu từng dòng
		int size = 0;				// size của vector
		string split;			// chuỗi sau khi đã tách ra
		getline(f, line);

		istringstream iss(line);

		// Nếu là dòng đầu tiên cũng bỏ qua, vì dòng đầu bị lỗi
		if (row_count == 0)
		{
			row_count++;
			continue;
		}


		// tách từng dòng ra thành các chuỗi dựa vào \t
		while (getline(iss, split, '\t'))
		{
			// gán từng chuỗi trong dòng vào vector
			pos.push_back(split);
			size++;
		}

		// Nếu dòng không có gì thì bỏ qua
		if (size == 0)
		{
			row_count++;
			continue;
		}

		// Gặp END thì không đọc nữa
		if (pos[0] == "END")
			break;

		switch (row_count)
		{
		case 1:	//Camera
			Camera::min_x = stoi(pos[0]);
			Camera::max_x = stoi(pos[1]);
			break;
		case 2:	//Vị trí samus
			manager->samus->SetPosX(stoi(pos[0]));
			manager->samus->SetPosY(stoi(pos[1]));
			break;
		}

		row_count++;
	}
	f.close();
}

void Loader::LinkNodes()
{
	map<int, QNode*>::iterator it;
	for (it = mapQNodes.begin(); it != mapQNodes.end(); it++)
	{
		// Trong map được sắp xếp tăng dần theo nodeID nên khỏi cần lo

		// Nếu là node Gốc thì gán vào rootQNode
		if (it->first == 1)
		{
			rootQNode = it->second;
			continue;
		}

		// Tính id của node cha và offset của node hiện tại
		const int parent_id = it->second->GetParentID();
		const int offset = it->second->GetOffsetID();

		// Xét offset rồi lấy node cha trỏ vào
		switch (offset)
		{
		case 1:
			mapQNodes[parent_id]->tl = it->second;
			break;
		case 2:
			mapQNodes[parent_id]->tr = it->second;
			break;
		case 3:
			mapQNodes[parent_id]->bl = it->second;
			break;
		case 4:
			mapQNodes[parent_id]->br = it->second;
			break;
		}
	}
}

void Loader::Load()
{
	this->ReadInfoFromFile(info_path.c_str());
}

void Loader::TestRenderMapGO()
{
	map<int, GameObject*>::iterator i;
	for (i = mapGameObjects.begin(); i != mapGameObjects.end(); i++)
	{
		i->second->Render();
	}
}


