#ifndef __LayerGame_H_
#define __LayerGame_H_
#include "cocos2d.h"
class LayerGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene * scene();
	CREATE_FUNC(LayerGame);
	bool init();

	void startGame();
	void addStartLineBlock();
	void addNormalLineBlocks(int LineIndex);
	void addEndLineBlock();

	bool showEnd;
	long startTime;
	bool isRunning;

	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void moveDown();
	CC_SYNTHESIZE(int,_lineCount,LineCount);

	void startTimer();
	void stopTimer();
	void update(float dt);//帧循环定时器的回调函数
	cocos2d::LabelTTF * ttf;

	void tryAgainCallback(cocos2d::Ref * sender);
	void exitCallback(cocos2d::Ref * sender);
	
};



#endif
