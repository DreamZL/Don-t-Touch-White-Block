#ifndef __Block_H_
#define __Block_H_
#include "cocos2d.h"
USING_NS_CC;
class Block : public Sprite
{
public:
	static Block * create(Size size,Color3B color,String str,
						  float strSize,Color3B strColor);
	bool init(Size size,Color3B color,String str,
			  float strSize,Color3B strColor);

	//类内部静态成员在单独的内存里的，
	//在定义的时候已经存在了，它不属于某一个对象，只属于这个类
	static Vector<Sprite *> vec;
	static Vector<Sprite *> getBlockVector();

	CC_SYNTHESIZE(int,_LineIndex,LineIndex);

	void moveDownAndCleanUp();
};

#endif
