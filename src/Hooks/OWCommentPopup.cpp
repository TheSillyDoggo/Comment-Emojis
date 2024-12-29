#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include "../EmojiPickPopup.hpp"

using namespace geode::prelude;

class CommentPopup : public geode::Popup<> {};

class $modify (CommentPopupExt, FLAlertLayer)
{
    struct Fields {
        CCTextInputNode* inp = nullptr;
    };

    virtual void show()
    {
        FLAlertLayer::show();
        if (typeinfo_cast<CommentPopup*>(this) && this->getID() == "firee.object-workshop/CommentPopup")
        {
            if (auto menu = m_mainLayer->getChildByType<CCMenu>(0))
            {
                m_fields->inp = menu->getChildByType<CCTextInputNode>(0);
                auto spr = CCSprite::createWithSpriteFrameName("emoji-icon-thicker.png"_spr);
                spr->setScale(0.8f);
                spr->setOpacity(100);

                auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(CommentPopupExt::onEmojis));
                menu->addChildAtPosition(btn, Anchor::BottomRight, {-25, 25});
            }
        }
    }

    void onEmojis(CCObject*)
    {
        if (m_fields->inp)
        {
            m_fields->inp->onClickTrackNode(false);
            EmojiPickPopup::create(m_fields->inp, m_fields->inp)->show();
        }
    }

};
