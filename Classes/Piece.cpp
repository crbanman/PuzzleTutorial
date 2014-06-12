//
//  Piece.cpp
//  PuzzleTutorial
//
//  Created by Cody Banman on 2014-06-12.
//
//

#include "Piece.h"

Piece* Piece::create(const std::string &filename)
{
    Piece *pRet = new Piece();
    if (pRet && pRet->init(filename))
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = NULL;
    }
    return pRet;
    
}

bool Piece::init(const std::string &filename)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    
    listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(Piece::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Piece::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Piece::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    
    return true;
}

	
void Piece::setTargetPosition(cocos2d::Vec2 targetPosition)
{
    this->_targetPosition = targetPosition;
}

void Piece::setActived(bool active)
{
    _actived = active;
    Action *scale;
    if (_actived)
    {
        scale = ScaleTo::create(0.2, 1.1);
    }
    else
    {
        scale = ScaleTo::create(0.2, 1);
    }
    this->runAction(scale);
}


bool Piece::currentLocationSuccess()
{
    cocos2d::Vec2 currentPosition = this->getPosition();
    int deltaX, deltaY;
    deltaX = _targetPosition.x - currentPosition.x;
    deltaY = _targetPosition.y - currentPosition.y;
    
        // Current pice is inside the desired range.
    if ((abs(deltaX) < LOCATION_ACCURACY)&&(abs(deltaY) < LOCATION_ACCURACY))
    {
        Action* moveToTagetPosition = MoveTo::create(0.2, _targetPosition);
        this->runAction(moveToTagetPosition);
        std::cout << "piece is now in the correct place";
        return true;
    }
    return false;
}

bool Piece::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (this->getBoundingBox().containsPoint(touch->getLocation()))
    {
        this->listener->setSwallowTouches(true);
        this->setActived(true);
    }
    else
    {
        this->listener->setSwallowTouches(false);
    }
    
    return true;
}

void Piece::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    this->setActived(false);
    this->currentLocationSuccess();
}

void Piece::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    if (this->_actived)
    {
        this->setPosition(cocos2d::Vec2(this->getPositionX()+touch->getDelta().x,
                                        this->getPositionY()+touch->getDelta().y));
    }
}




