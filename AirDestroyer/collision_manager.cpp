#include "collision_manager.h"

#include "game_object.h"
#include <iostream>

bool CollisionManager::DoCollisions(GameObject* aGameObject, GameObject* bGameObject, bool aPixelPerfectCollision, bool bPixelPerfectCollision)
{
	int aLeft, aRight, aBottom, aTop;
	int bLeft, bRight, bBottom, bTop;

	aLeft = aGameObject->Position.x;
	aRight = aLeft + aGameObject->Size.x;
	aTop = aGameObject->Position.y;
	aBottom = aTop + aGameObject->Size.y;


	bLeft = bGameObject->Position.x;
	bRight = bLeft + bGameObject->Size.x;
	bTop = bGameObject->Position.y;
	bBottom = bTop + bGameObject->Size.y;

	//if (aBottom < 0 || bBottom < 0)
	//	return false;

	if (aLeft > bRight || aRight < bLeft
		|| aBottom < bTop || aTop > bBottom)
		return false;

	if (aPixelPerfectCollision == false && bPixelPerfectCollision == false)
	{
		//std::cout << "Border" << std::endl;
		//std::cout << "Position: " << std::endl
		//	<< "aLeft: " << aLeft << "; aRight: " << aRight << std::endl
		//	<< "aBottom: " << aBottom << "; aTop: " << aTop << std::endl;
		//std::cout << "Size: " << aGameObject->Size.x << "; " << aGameObject->Size.y << std::endl;

		//std::cout << "Projectile" << std::endl;
		//std::cout << "Position: " << std::endl
		//	<< "bLeft: " << bLeft << "; bRight: " << bRight << std::endl
		//	<< "bBottom: " << bBottom << "; bTop: " << bTop << std::endl;
		//std::cout << "===============================" << std::endl;
		//std::cout << "Projectile" << std::endl;
		//std::cout << "Position: " << bGameObject->Position.x << "; " << bGameObject->Position.y << std::endl;
		//std::cout << "Size: " << bGameObject->Size.x << "; " << bGameObject->Size.y << std::endl;
		return true;
	}


	
	int left, right, bottom, top;
	int columns, rows;

	left = std::max(aLeft, bLeft);
	right = std::min(aRight, bRight);
	top = std::max(aTop, bTop);
	bottom = std::min(aBottom, bBottom);
	columns = right - left + 1;
	rows = bottom - top + 1;

	aLeft = left - aLeft;
	aBottom = aBottom - bottom;

	bLeft = left - bLeft;
	bBottom = bBottom - bottom;

	// std::cout << "Enemy mask" << std::endl;
	for (int y = 0; y != rows; ++y)
	{
		for (int x = 0; x != columns; ++x)
		{
			//if (aGameObject->Sprite.Mask[(aLeft + x) + (aBottom + y) * aGameObject->Sprite.Width])
			//	return true;
			bool aPixel = aPixelPerfectCollision == true ? CheckMask(aGameObject, aLeft + x, aBottom + y) : true;
			bool bPixel = bPixelPerfectCollision == true ? CheckMask(bGameObject, bLeft + x, bBottom + y) : true;
			if (aPixel && bPixel)
				return true;
			//if (checkPixelPerfectCollisionForFirst(aLeft + x, aBottom + y))
			////	std::cout << "1 ";
			////else
			////	std::cout << "0 ";
			//	return true;
		}
		// std::cout << std::endl;
	}

	return false;

	//if (!CheckCOllisionAABB(aGameObject->Position, aGameObject->Size
	//	, bGameObject->Position, bGameObject->Size))
	//	return false;
	//if (!CheckCollisionRect(aGameObject, bGameObject))
	//	return false;

	//if ((aPixelPerfectCollision || bPixelPerfectCollision) == false)
	//	return true;
	//return CheckCollisionPixelPerfect(aGameObject, bGameObject, aPixelPerfectCollision, bPixelPerfectCollision);
}

bool CollisionManager::CheckMask(GameObject* gameObject, int xOffset, int yOffset)
{
	if (gameObject->Sprite.Mask[xOffset + yOffset * gameObject->Sprite.Width])
		return true;
	return false;
}

//bool CollisionManager::CheckCOllisionAABB(glm::vec2 aPosition, glm::vec2 aSize, glm::vec2 bPosition, glm::vec2 bSize)
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
//    return true;
//}

