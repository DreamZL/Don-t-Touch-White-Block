#ifndef __LayerFailed_H_
#define __LayerFailed_H_

#include "cocos2d.h"
class LayerFailed : public cocos2d::LayerColor
{
public:
	CREATE_FUNC(LayerFailed);
	static cocos2d::Scene * scene();
	bool init();

	void againCallback(cocos2d::Ref * ref);
	void backCallback(cocos2d::Ref * ref);
};

#endif
