#include "enemy_object.h"
#include <iostream>

EnemyObject::EnemyObject() : GameObject()
{
}


bool checkPixelPerfectCollision(int x1, int y1, int x2, int y2) {
	unsigned char pixel1[4];
	unsigned char pixel2[4];

	glReadPixels(x1, y1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel1);
	glReadPixels(x2, y2, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel2);

	return (pixel1[3] > 0);// && pixel2[3] > 0); // Check if both pixels are opaque
}

bool checkPixelPerfectCollisionForFirst(int x1, int y1)
{
	unsigned char pixel1[4];

	glReadPixels(x1, y1, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &pixel1);

	return (pixel1[3] > 0);
}

EnemyObject::EnemyObject(glm::vec2 pos, glm::vec2 size, glm::vec2 velocity, glm::vec3 color, Texture2D sprite)
	: GameObject(pos, size, velocity, color, sprite)
{
	/*std::cout << "Enemy Physics mask" << std::endl;
	for (int y = 0; y != size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			if (checkPixelPerfectCollisionForFirst(pos.x + x, pos.y + y))
				std::cout << "1 ";
			else
				std::cout << "0 ";
		}
		std::cout << std::endl;
	}*/
	//Position = pos;
	//Size = size;
	//Sprite = sprite;
	//Velocity = glm::vec2(0.0f, 1.0f);
}

glm::vec2 EnemyObject::Move(float dt, glm::vec2 parentVelocity)
{
	this->Position.y += dt * (parentVelocity.y + this->Velocity.y);
	return this->Position;
}




void EnemyObject::Reset(glm::vec2 position, glm::vec2 velocity)
{
	this->Position = position;
	this->Velocity = velocity;
}

//bool EnemyObject::CheckCollision(glm::vec2 aPosition
//	, glm::vec2 aSize
//	, glm::vec2 bPosition
//	, glm::vec2 bSize)
//{
//	int aLeft, aRight, aBottom, aTop;
//	int bLeft, bRight, bBottom, bTop;
//
//	aLeft = aPosition.x; 
//	aRight = aLeft + aSize.x;
//	aBottom = aPosition.y;
//	aTop = aBottom - aSize.y;
//
//	bLeft = bPosition.x;
//	bRight = bLeft + bSize.x;
//	bBottom = bPosition.y;
//	bTop = bBottom - bSize.y;
//
//	if (aLeft > bRight || aRight < bLeft
//		|| aBottom < bTop || aTop > bBottom)
//		return false;
//
//	int left, right, bottom, top;
//	int columns, rows;
//
//	left = std::max(aLeft, bLeft);
//	right = std::min(aRight, bRight);
//	top = std::max(aTop, bTop);
//	bottom = std::min(aBottom, bBottom);
//	columns = right - left + 1;
//	rows = bottom - top + 1;
//
//	aLeft = left - aLeft;
//	aBottom = aBottom - bottom;
//
//	bLeft = left - bLeft;
//	bBottom = bBottom - bottom;
//
//	// std::cout << "Enemy mask" << std::endl;
//	for (int y = 0; y != rows; ++y)
//	{	
//		for (int x = 0; x != columns; ++x)
//		{
//			if (this->Sprite.Mask[(aLeft + x) + (aBottom + y) * this->Sprite.Width])
//				return true;
//			//if (checkPixelPerfectCollisionForFirst(aLeft + x, aBottom + y))
//			////	std::cout << "1 ";
//			////else
//			////	std::cout << "0 ";
//			//	return true;
//		}
//		// std::cout << std::endl;
//	}
//
//	return false;
//}
//
//bool EnemyObject::DoCollisions(GameObject* gameObject)
//{
//	glm::vec2 projectileCollider = { gameObject->Size.x, gameObject->Size.y / 1.0f };
//
//	return CheckCollision(this->Position, this->Size
//		, gameObject->Position, projectileCollider);
//}
