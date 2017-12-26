#include "GroupObject.h"
#include "GameObject.h"
#include "QNode.h"
#include "World.h"

GroupObject::GroupObject()
{
}

GroupObject::GroupObject(World * manager)
{
	this->manager = manager;
}


GroupObject::~GroupObject()
{
}

std::vector<GameObject*> GroupObject::GetListGO()
{
	return objects;
}

int GroupObject::GetSize()
{
	return size;
}

void GroupObject::AddGameObject(GameObject * target)
{
	// trước khi thêm kiểm tra trùng lặp
	for (int i = 0; i < size; i++)
	{
		// Nếu trùng thì dừng
		if (objects[i] == target)
			return;
	}

	objects.push_back(target);
	size++;
}

void GroupObject::Update(int t)
{
	for (int i = 0; i < size; i++)
	{
		objects[i]->Update(t);
	}
}

void GroupObject::UpdateActive(int t)
{
	for (int i = 0; i < size; i++)
	{
		if (objects[i]->IsActive())
		{
			objects[i]->Update(t);
		}
	}
}

void GroupObject::Render()
{
	// Do trong mỗi GameObject đã có kiểm tra isActive trước khi render 
	// nên không cần kiểm tra nữa
	for (int i = 0; i < size; i++)
	{
		objects[i]->Render();
	}
}

void GroupObject::GetGroupObjectFrom(GroupObject * group)
{
	int group_size = group->size;
	for (int i = 0; i < group_size; i++)
	{
		// Chỉ lấy những GameObject đang active để xử lý
		if (group->objects[i]->IsActive())
		{
			this->AddGameObject(group->objects[i]);
		}
	}
}

void GroupObject::GetCollisionObjectQTree()
{
	// Xóa trước khi thêm cái khác
	this->objects.clear();
	this->size = 0;

	// Gửi những game objects va chạm với viewport vào trong GroupObject này
	manager->rootQNode->SendObjectsToGroup(this);
}

void GroupObject::GetCollisionObjects()
{
	// Enemy cần để xét va chạm
	this->GetGroupObjectFrom(manager->enemyGroup);
}
