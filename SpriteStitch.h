#pragma once

#include "cocos2d.h"
#include "SpriteStitch.h"

USING_NS_CC;
using namespace std;

class SpriteStitch : public cocos2d::Node
{
private:
	SpriteStitch(const string& stitchFolder, bool hasAlpha);
public:
	static SpriteStitch* createFromFolder(const string& stitchFolder, bool hasAlpha);
	static Sprite* createETCASprite(const string& file, const string& alphaFile);
};
