#include "Block.h"
#include "AppMacros.h"
//vec是类的静态成员，只能在类的外部初始化。且默认的Vector的初始化为Vector<Sprite *>()！！
Vector<Sprite *> Block::vec = Vector<Sprite *>();

Block * Block::create(Size size,Color3B color,String str, 
					  float strSize,Color3B strColor)
{
	
	Block * pRet =new Block;
	if (pRet && pRet->init(size,color,str,strSize,strColor))
	{
		pRet->autorelease();
		vec.pushBack(pRet);//每次创建一个Block都将其加入到 vec 中
	}
	else
	{
		delete pRet;
		pRet = NULL;
	}
	return pRet;
}

bool Block::init(Size size,Color3B color,String str, 
				 float strSize,Color3B strColor)
{
	if (!Sprite::init())
	{
		return false;
	}
	this->setContentSize(size);
	this->setTextureRect(Rect(0,0,size.width-1,size.height-1));
	this->setColor(color);
	this->setAnchorPoint(Point(0,0));

	LabelTTF * label = LabelTTF::create();
	label->setString(str.getCString());
	label->setFontSize(strSize);
	label->setColor(strColor);
	label->setPosition(Point(size.width/2,size.height/2));
	this->addChild(label);

	return true;
}

Vector<Sprite *> Block::getBlockVector()
{
	return vec;
}

void Block::moveDownAndCleanUp()
{
	_LineIndex--;
	MoveTo * to = MoveTo::create(0.01,
								Point(getPositionX(),
								getPositionY()-winSize.height/4));
	this->runAction(to);
	if (_LineIndex < 0)
	{
		
		//从渲染树上拿下来
		this->removeFromParentAndCleanup(true);
		//从vec中删除当前块
		vec.eraseObject(this);
	}
}
