#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "RulesScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	auto bg = Sprite::create("bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	auto closeItem = MenuItemImage::create(
		"quit.png",
		"quit.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	auto startItem = MenuItemImage::create(
		"newGame_normal.png",
		"newGame_selected.png",
		CC_CALLBACK_1(HelloWorld::menuStartScene, this));

	auto rulesItem = MenuItemImage::create(
		"Rules.png",
		"Rules.png",
		CC_CALLBACK_1(HelloWorld::menuRulesScene, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x,y));
  		closeItem->setScale(0.5);
    }

	startItem->setAnchorPoint(Vec2(0.5, 0.5));
	rulesItem->setAnchorPoint(Vec2(0.5, 0.5));
	startItem->setPosition(Vec2(visibleSize.width / 2, 2 * visibleSize.height / 3));
	startItem->setScale(0.5);
	rulesItem->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	rulesItem->setScale(0.5);


    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, startItem, rulesItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label

    auto label = Label::createWithTTF("BombingAdventure","fonts/Marker Felt.ttf", 42);
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
	// add the label as a child to this layer
    this->addChild(label, 1);

	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("music&effect/HelloMusic.mp3", true);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void HelloWorld::menuStartScene(cocos2d::Ref * pSender)
{
	Director::getInstance()->replaceScene(CCTransitionMoveInR::create(0.4f, GameScene::createScene()));
}

void HelloWorld::menuRulesScene(cocos2d::Ref * pSender)
{
	Director::getInstance()->pushScene(RulesScene::createScene());
}
