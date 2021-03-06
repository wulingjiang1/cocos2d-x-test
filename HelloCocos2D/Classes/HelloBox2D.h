#ifndef _HELLOBOX2D_H_
#define _HELLOBOX2D_H_
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "GLES-Render.h"
using namespace cocos2d;

class HelloBox2D : public cocos2d::CCLayer
{
private:
	CCTexture2D* m_pSpriteTexture;    // weak ref
	b2World* world;
	GLESDebugDraw* m_debugDraw;
public:
	HelloBox2D();
	~HelloBox2D();
	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCallback(CCObject* pSender);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloBox2D);

	void initPhysics();
	virtual void draw();

	void addNewSpriteAtPosition(CCPoint p);
	void update(float dt);
	virtual void ccTouchesEnded(CCSet* touches, CCEvent* event);
};



#endif