#include "PositionManager.h"
#include "Camera.h"


PositionManager::PositionManager()
{
}

PositionManager::PositionManager(World * manager, ENEMY_TYPE enemy_type, int width, int height)
{
	this->manager = manager;
	this->enemy_type = enemy_type;
	this->width = width;
	this->height = height;
	// khởi tạo index;
	index = 0;
}


PositionManager::~PositionManager()
{
}

void PositionManager::Next()
{
	// Kiểm tra xem các pos từ index+1 đến cuối vector xem còn điểm nào chưa xuất hiện trong viewport
	for (int i = index + 1; i < size; i++)
	{
		// Nếu điểm tiếp theo đã nằm trong camera (đã hiển thị rồi) thì bỏ qua
		if (IsInCamera(list_pos[i]))
			continue;
		// Nếu không thì gán index bằng i rồi nghỉ
		index = i;
		return;
	}
}

void PositionManager::Back()
{
	// Kiểm tra xem các pos từ index-1 đến đầu vector xem còn điểm nào chưa xuất hiện trong viewport
	for (int i = index - 1; i > 0; i--)
	{
		// Nếu điểm tiếp theo đã nằm trong camera (đã hiển thị rồi) thì bỏ qua
		if (IsInCamera(list_pos[i]))
			continue;
		// Nếu không thì gán index bằng i rồi nghỉ
		index = i;
		return;
	}
}

bool PositionManager::IsInCamera(PosInfo * target)
{

	// Kiềm tra bên trái
	if (target->x + width < Camera::currentCamX)
		return false;
	// Kiểm tra phía trên
	if (target->y + height > Camera::currentCamY)
		return false;
	// Kiểm tra bên phải
	if (target->x > Camera::currentCamX + Camera::width)
		return false;
	// Kiểm tra phía dưới
	if (target->y < Camera::currentCamY - Camera::height)
		return false;

	return true;
}