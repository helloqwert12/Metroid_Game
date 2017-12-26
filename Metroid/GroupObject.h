#pragma once
#ifndef _GROUPOBJECT_H_
#define _GROUPOBJECT_H_

#include <vector>
#include "Parameters.h"

/*
	Class này có tác dụng gom nhóm các GameObject cùng loại lại để quản lý cho dễ
	Vd: Các loại enemy khác nhau gom chung vào để dễ quản lý
*/
class GroupObject
{
protected:
	World* manager;
public:
	std::vector<GameObject*> objects;	// vector quản lý list các GameObject cùng loại
	int size;							// số lượng GameObject trong vector (tránh moi từ vector vì không tối ưu thời gian)

	GroupObject();
	GroupObject(World* manager);
	~GroupObject();

	//==================== GET - SET METHOD ====================
	// Trả về mảng vector chứa GameObject
	std::vector<GameObject*> GetListGO();

	// Trả về số lượng GameObject trong vector
	int GetSize();
	//==================== END GET - SET METHOD ================


	void AddGameObject(GameObject* target);

	// Hàm update các GameObject có trong vector (dùng cho SpecialCollision và QuadtreeCollision)
	void Update(int t);

	// Hàm update các GameObject có trong vector (dùng cho Projectile, Enemy, ...)
	void UpdateActive(int t);

	// Hàm render các GameObject có trong vector (dùng cho SpecialCollision và QuadtreeCollision)
	void Render();

	
	// Lấy GroupGameObject khác bỏ vào vector này
	void GetGroupObjectFrom(GroupObject* group);

	//Lấy ra những GameObject trong quadtree nằm trong viewport
	void GetCollisionObjectQTree();	//--TO-DO: Hoàn thành hàm này sau khi code QNode
	
	//Lấy ra những GameObject cần xử lý va chạm (không nằm trong quadtree)
	void GetCollisionObjects();

};
#endif // !_GROUPOBJECT_H_

