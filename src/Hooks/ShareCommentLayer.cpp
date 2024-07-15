#include <Geode/Geode.hpp>
#include <Geode/modify/ShareCommentLayer.hpp>
#include "../EmojiPickPopup.hpp"

using namespace geode::prelude;

class $modify (ShareCommentLayerExt, ShareCommentLayer)
{
    struct Fields {
        bool isComment = false;
        CCTextInputNode* inp = nullptr;
    };

    void onEmojis(CCObject *) {
        if (m_fields->inp)
        {
            m_fields->inp->onClickTrackNode(false);
            EmojiPickPopup::create(m_fields->inp, m_fields->inp)->show();
        }
    }

    bool init(gd::string title, int charLimit, CommentType type, int ID, gd::string desc)
    {
        if (!ShareCommentLayer::init(title, charLimit, type, ID, desc))
            return false;

        if (type == CommentType::FriendRequest)
            return true;

        m_fields->inp = getChildOfType<CCTextInputNode>(m_mainLayer, 0);

        if (auto menu = getChildOfType<CCMenu>(m_mainLayer, 0))
        {
            auto spr = CCSprite::createWithSpriteFrameName("emoji-icon-thicker.png"_spr);
            spr->setScale(0.8f);
            spr->setOpacity(100);

            auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(ShareCommentLayerExt::onEmojis));
            btn->setPosition(ccp(178, 38));

            menu->addChild(btn);
        }

        m_fields->isComment = true;

        return true;
    }

    virtual void textChanged(CCTextInputNode* textInput)
    {
        ShareCommentLayer::textChanged(textInput);

        if (m_fields->isComment)
        {
            
        }
    }
};