#include <Geode/Geode.hpp>
#include "CCProxyNode.hpp"

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

        static EmojiPickPopup* create(CCTextInputNode* input, CCNode* node);

        void show();
        void hide();
        void remove(float);

        virtual void keyDown(enumKeyCodes code);

        virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
        virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};