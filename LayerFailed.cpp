#include "LayerFailed.h"
#include "AppMacros.h"
#include "LayerGame.h"
USING_NS_CC;

Scene * LayerFailed::scene()
{
	Scene * scene = Scene::create();
	LayerFailed * layer = LayerFailed::create();
	scene->addChild(layer);
	return scene;
}

bool LayerFailed::init()
{
	if(!LayerColor::initWithColor(Color4B(142,201,111,255)))
		return false;
	LabelBMFont * failedStr = LabelBMFont::create("You Failed","fonts/arial-unicode-26.fnt");
	failedStr->setPosition(Point(winSize.width/2,winSize.height/2));
	this->addChild(failedStr);

	LabelBMFont * bm = LabelBMFont::create("Again","fonts/arial-unicode-26.fnt");
	LabelBMFont * bm1 = LabelBMFont::create("Exit","fonts/arial-unicode-26.fnt");
	MenuItem * again = MenuItemLabel::create(bm);
	MenuItem * ext = MenuItemLabel::create(bm1);
	again->setTarget(this,menu_selector(LayerFailed::againCallback));
	ext->setTarget(this,menu_selector(LayerFailed::backCallback));
	Menu * menu = Menu::create(again,ext,NULL);
	this->addChild(menu);
	menu->setPosition(Point::ZERO);
	again->setPosition(Point(again->getBoundingBox().size.width/2,
							 again->getBoundingBox().size.height/2));
	ext->setPosition(Point(winSize.width-ext->getBoundingBox().size.width/2,
							ext->getBoundingBox().size.height/2));

	return true;
}

void LayerFailed::againCallback(cocos2d::Ref * ref)
{
	Scene * scene = LayerGame::scene();
	Director::getInstance()->replaceScene(scene);
}
void LayerFailed::backCallback(cocos2d::Ref * ref)
{
	exit(1);
}
