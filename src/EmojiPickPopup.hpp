#include <Geode/Geode.hpp>
#include "CCProxyNode.hpp"
#include "EmojiNode.hpp"

using namespace geode::prelude;

class EmojiPickPopup : public geode::Popup<CCTextInputNode*, CCNode*>
{
    public:
        CCTextInputNode* input;
        CCNode* node;
        CCNode* inputParent;
        CCProxyNode* proxy;
        CCScale9Sprite* inputBG;
        CCNode* hideNode;

        bool setup(CCTextInputNode* input, CCNode* node);
        void populateScroll(CCContentLayer* content);

        static EmojiPickPopup* create(CCTextInputNode* input, CCNode* node);

        void onPickEmoji(CCObject* sender);

        void show();
        void hide();
        void remove(float);

        virtual void keyDown(enumKeyCodes code);

        virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};