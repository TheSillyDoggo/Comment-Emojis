#include <Geode/Geode.hpp>

using namespace geode::prelude;

class EmojiPickPopup : public geode::Popup<> {
    public:
        bool setup() override {
            m_bgSprite->setVisible(false);
            auto bg = CCScale9Sprite::create("GJ_square05.png");
            bg->setPosition(CCDirector::get()->getWinSize() / 2);
            bg->setContentSize(m_bgSprite->getContentSize());

            auto scroll = geode::ScrollLayer::create(ccp(240, 205));
            scroll->setPosition(CCDirector::get()->getWinSize() / 2 - scroll->getContentSize() / 2);

            auto scrollbar = geode::Scrollbar::create(scroll);
            scrollbar->setPosition(CCDirector::get()->getWinSize() / 2 + ccp(127.5f, 0));

            m_mainLayer->addChild(scroll);
            m_mainLayer->addChild(scrollbar);
            m_mainLayer->addChild(bg, -42069);
            return true;
        }

        static EmojiPickPopup* create() {
            auto ret = new EmojiPickPopup();
            if (ret && ret->init(280.f, 230.f)) {
                ret->autorelease();
                return ret;
            }
            CC_SAFE_DELETE(ret);
            return nullptr;
        }

        void show()
        {
            CCScene::get()->addChild(this, CCScene::get()->getHighestChildZ() + 1);
        }
};