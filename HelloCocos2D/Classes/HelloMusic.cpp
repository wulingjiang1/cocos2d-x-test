#include "HelloMusic.h"

using namespace cocos2d;
using namespace CocosDenshion;
// android effect only support ogg
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#define EFFECT_FILE        "effect2.ogg"
#else
#define EFFECT_FILE        "effect1.wav"
#endif // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#define MUSIC_FILE        "music.mid"
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_BLACKBERRY)
#define MUSIC_FILE        "background.ogg"
#else
#define MUSIC_FILE        "background.mp3"
#endif // CC_PLATFORM_WIN32

#define LINE_SPACE          40

CCScene* HelloMusic::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloMusic *layer = HelloMusic::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

HelloMusic::HelloMusic()
	: m_pItmeMenu(NULL),
	m_tBeginPos(CCPointZero),
	m_nSoundId(0)
{
}
HelloMusic::~HelloMusic()
{

}

// on "init" you need to initialize your instance
bool HelloMusic::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		std::string testItems[] = {
			"play background music",
			"stop background music",
			"pause background music",
			"resume background music",
			"rewind background music",
			"is background music playing",
			"play effect",
			"play effect repeatly",
			"stop effect",
			"unload effect",
			"add background music volume",
			"sub background music volume",
			"add effects volume",
			"sub effects volume",
			"pause effect",
			"resume effect",
			"pause all effects",
			"resume all effects",
			"stop all effects"
		};

		// add menu items for tests
		m_pItmeMenu = CCMenu::create();

		m_nTestCount = sizeof(testItems) / sizeof(testItems[0]);

		for (int i = 0; i < m_nTestCount; ++i)
		{
			CCLabelTTF* label = CCLabelTTF::create(testItems[i].c_str(), "Arial", 24);       
			CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(HelloMusic::menuCallback));

			m_pItmeMenu->addChild(pMenuItem, i + 10000);
			pMenuItem->setPosition( ccp( 240, (320 - (i + 1) * LINE_SPACE) ));
		}

		m_pItmeMenu->setContentSize(CCSizeMake(480, (m_nTestCount + 1) * LINE_SPACE));
		m_pItmeMenu->setPosition(CCPointZero);
		addChild(m_pItmeMenu);

		setTouchEnabled(true);

		// preload background music and effect
		SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(MUSIC_FILE) );
		SimpleAudioEngine::sharedEngine()->preloadEffect( CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(EFFECT_FILE) );

		// set default volume
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(0.5);
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(0.5);

		bRet = true;
	} while (0);

	return bRet;
}

void HelloMusic::onExit()
{
	CCLayer::onExit();

	SimpleAudioEngine::sharedEngine()->end();
}

void HelloMusic::menuCallback(CCObject* pSender)
{
	// get the userdata, it's the index of the menu item clicked
	CCMenuItem* pMenuItem = (CCMenuItem *)(pSender);
	int nIdx = pMenuItem->getZOrder() - 10000;

	switch(nIdx)
	{
		// play background music
	case 0:

		SimpleAudioEngine::sharedEngine()->playBackgroundMusic(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(MUSIC_FILE)).c_str(), true);
		break;
		// stop background music
	case 1:
		SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
		break;
		// pause background music
	case 2:
		SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
		break;
		// resume background music
	case 3:
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
		break;
		// rewind background music
	case 4:
		SimpleAudioEngine::sharedEngine()->rewindBackgroundMusic();
		break;
		// is background music playing
	case 5:
		if (SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
		{
			CCLOG("background music is playing");
		}
		else
		{
			CCLOG("background music is not playing");
		}
		break;
		// play effect
	case 6:
		m_nSoundId = SimpleAudioEngine::sharedEngine()->playEffect(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(EFFECT_FILE)).c_str());
		break;
		// play effect
	case 7:
		m_nSoundId = SimpleAudioEngine::sharedEngine()->playEffect(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(EFFECT_FILE)).c_str(), true);
		break;
		// stop effect
	case 8:
		SimpleAudioEngine::sharedEngine()->stopEffect(m_nSoundId);
		break;
		// unload effect
	case 9:
		SimpleAudioEngine::sharedEngine()->unloadEffect(std::string(CCFileUtils::sharedFileUtils()->fullPathFromRelativePath(EFFECT_FILE)).c_str());
		break;
		// add bakcground music volume
	case 10:
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() + 0.1f);
		break;
		// sub backgroud music volume
	case 11:
		SimpleAudioEngine::sharedEngine()->setBackgroundMusicVolume(SimpleAudioEngine::sharedEngine()->getBackgroundMusicVolume() - 0.1f);
		break;
		// add effects volume
	case 12:
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() + 0.1f);
		break;
		// sub effects volume
	case 13:
		SimpleAudioEngine::sharedEngine()->setEffectsVolume(SimpleAudioEngine::sharedEngine()->getEffectsVolume() - 0.1f);
		break;
	case 14:
		SimpleAudioEngine::sharedEngine()->pauseEffect(m_nSoundId);
		break;
	case 15:
		SimpleAudioEngine::sharedEngine()->resumeEffect(m_nSoundId);
		break;
	case 16:
		SimpleAudioEngine::sharedEngine()->pauseAllEffects();
		break;
	case 17:
		SimpleAudioEngine::sharedEngine()->resumeAllEffects();
		break;
	case 18:
		SimpleAudioEngine::sharedEngine()->stopAllEffects();
		break;
	}
}

void HelloMusic::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	m_tBeginPos = touch->getLocation();    
}

void HelloMusic::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCSetIterator it = pTouches->begin();
	CCTouch* touch = (CCTouch*)(*it);

	CCPoint touchLocation = touch->getLocation();
	float nMoveY = touchLocation.y - m_tBeginPos.y;

	CCPoint curPos  = m_pItmeMenu->getPosition();
	CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);

	if (nextPos.y < 0.0f)
	{
		m_pItmeMenu->setPosition(CCPointZero);
		return;
	}

	if (nextPos.y > ((m_nTestCount + 1)* LINE_SPACE - 320))
	{
		m_pItmeMenu->setPosition(ccp(0, ((m_nTestCount + 1)* LINE_SPACE - 320)));
		return;
	}

	m_pItmeMenu->setPosition(nextPos);
	m_tBeginPos = touchLocation;
}