#include "GamePlayScene.h"

USING_NS_CC;

Scene* GamePlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GamePlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GamePlay::init()
{
    if ( !Layer::init())
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    // Add Background Shape
    Sprite * background = Sprite::create("background.png");
    background->setPosition(cocos2d::Vec2(this->getContentSize().width/2, this->getContentSize().height/2));
    this->addChild(background);
    
    // Position of Pieces
    cocos2d::Vec2 positionPieceTopLeft = cocos2d::Vec2(background->getPositionX() - background->getContentSize().width/4,
                                     background->getPositionY() + background->getContentSize().height/4);
    cocos2d::Vec2 positionPieceTopRight = cocos2d::Vec2(background->getPositionX() + background->getContentSize().width/4,
                                      background->getPositionY() + background->getContentSize().width/4);
    cocos2d::Vec2 positionPieceBottomLeft = cocos2d::Vec2(background->getPositionX() - background->getContentSize().width/4,
                                        background->getPositionY() - background->getContentSize().width/4);
    cocos2d::Vec2 positionPieceBottomRight = cocos2d::Vec2(background->getPositionX() + background->getContentSize().width/4,
                                         background->getPositionY() - background->getContentSize().width/4);
    
    cocos2d::Vec2 positionsArray[4];
    positionsArray[0] = positionPieceTopLeft;
    positionsArray[1] = positionPieceTopRight;
    positionsArray[2] = positionPieceBottomLeft;
    positionsArray[3] = positionPieceBottomRight;
    
    for (int i = 0; i < 4; i++)
    {
        // Add piece
        Piece * piece = Piece::create("piece_0"+std::to_string(i)+".png");
        piece->setTargetPosition(positionsArray[i]);
        this->puzzlePieces.pushBack(piece);
        this->addChild(piece);
        
    }
    
    return true;
}

