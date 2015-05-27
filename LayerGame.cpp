#include "LayerGame.h"
#include "AppMacros.h"
#include "Block.h"
#include "SimpleAudioEngine.h"
#include "LayerFailed.h"
using namespace CocosDenshion;
USING_NS_CC;


Scene * LayerGame::scene()
{
	Scene * scene = Scene::create();
	LayerGame * layer = LayerGame::create();
	scene->addChild(layer);
	return scene;
}

bool LayerGame::init()
{
	if (!Layer::init())
	{
		return false;
	}
	isRunning = false;
	startTime = 0;
	showEnd = false;
	this->setLineCount(0);
	ttf = LabelTTF::create("0.000","Courier New",30);
	ttf->setZOrder(100);
	ttf->setPosition(Point(winSize.width/2,winSize.height - 20));
	ttf->setColor(Color3B::BLUE);
	this->addChild(ttf);
	srand(time(NULL));

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);//吞噬
	listener->onTouchBegan = CC_CALLBACK_2(LayerGame::onTouchBegan,this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

	this->startGame();
	return true;
}

void LayerGame::startGame()
{
	addStartLineBlock();
	addNormalLineBlocks(1);
	addNormalLineBlocks(2);
	addNormalLineBlocks(3);
}
void LayerGame::addStartLineBlock()
{
	Size startBlockSize = Size(winSize.width,winSize.height/4);
	Block * b = Block::create(startBlockSize,
							  Color3B::YELLOW,
							  "Start Game",
							  30,
							  Color3B::BLUE);
	b->setPosition(Point(0,0));
	this->addChild(b);
	b->setLineIndex(0);
	_lineCount++;
}

void LayerGame::addEndLineBlock()
{
	Block * b = Block::create(winSize,Color3B::GREEN,"You Win!",50,Color3B::RED);
	b->setAnchorPoint(Point(0,0));
	b->setPosition(Point(0,winSize.height));
	this->addChild(b);
	b->setLineIndex(4);
	_lineCount++;


	LabelBMFont * bm = LabelBMFont::create("Again","fonts/arial-unicode-26.fnt");
	LabelBMFont * bm1 = LabelBMFont::create("Exit","fonts/arial-unicode-26.fnt");
	MenuItem * again = MenuItemLabel::create(bm);
	MenuItem * ext = MenuItemLabel::create(bm1);
	again->setTarget(this,menu_selector(LayerGame::tryAgainCallback));
	ext->setTarget(this,menu_selector(LayerGame::exitCallback));
	Menu * menu = Menu::create(again,ext,NULL);
	b->addChild(menu);
	menu->setPosition(Point::ZERO);
	again->setPosition(Point(again->getBoundingBox().size.width/2,
					   winSize.height-again->getBoundingBox().size.height/2));
	ext->setPosition(Point(winSize.width-ext->getBoundingBox().size.width/2,
					 winSize.height-ext->getBoundingBox().size.height/2));
	
}

void LayerGame::addNormalLineBlocks(int LineIndex)
{
	Size normalBlockSize = Size(winSize.width/4,winSize.height/4);
	int idx = rand()%4;
	for(int i = 0; i < 4; i++)
	{
		Block * b = Block::create(normalBlockSize,
								  i == idx ? Color3B::BLACK : Color3B::WHITE,
								  "",
								  30,
								  Color3B::WHITE);
		b->setLineIndex(LineIndex);
		b->setPosition(Point(i*winSize.width/4,LineIndex*winSize.height/4));
		this->addChild(b);
	}
	_lineCount++;
}

bool LayerGame::onTouchBegan(Touch *touch, Event *unused_event)
{

	for (auto obj : Block::getBlockVector())
	{
		Block * b = (Block *)obj;
		if (b->boundingBox().containsPoint(touch->getLocation()) &&
			b->getLineIndex() == 1)//必须从第一行开始点
		{
			if (b->getColor() == Color3B::BLACK)
			{
				SimpleAudioEngine::getInstance()->playEffect("onclick.wav");
				this->startTimer();
				b->setColor(Color3B::GRAY);
				this->moveDown();
			}
			else if (b->getColor() == Color3B::GREEN )
			{
				SimpleAudioEngine::getInstance()->playEffect("gamewin.wav");
				this->stopTimer();
				this->moveDown();
			}
			else if (b->getColor() == Color3B::WHITE)
			{
				SimpleAudioEngine::getInstance()->playEffect("wrong.wav");
				Scene * scene = LayerFailed::scene();
				Director::getInstance()->replaceScene(scene);
			}
			break;
		}
	}
	return false;
}

void LayerGame::moveDown()
{
	if (this->getLineCount() < 20)
	{
		this->addNormalLineBlocks(4);
	}
	else if (!showEnd)
	{
		this->addEndLineBlock();
		showEnd = true;
	}
	//在mmoveDown()的同时，在第四行处加入一个新行
	//this->addNormalLineBlocks(4);
	for (auto obj : Block::getBlockVector())
	{
		Block * b = (Block *)obj;
		b->moveDownAndCleanUp();
	}
}

void LayerGame::startTimer()
{
	if (!isRunning)
	{
	
		this->scheduleUpdate();
		startTime = clock();
		isRunning = true;
	}
}

void LayerGame::stopTimer()
{
	if (isRunning)
	{
		this->unscheduleUpdate();
	}
}
void LayerGame::update(float dt)
{
	long offset = clock() - startTime;
	String * str = String::createWithFormat("%g",(double)offset/1000);
	ttf->setString(str->getCString());
}

void LayerGame::tryAgainCallback(Ref * sender)
{
	Scene * scene = LayerGame::scene();
	Director::getInstance()->replaceScene(scene);
}
void LayerGame::exitCallback(Ref * sender)
{
	exit(1);
}
