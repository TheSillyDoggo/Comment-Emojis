#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/TextArea.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/ShareCommentLayer.hpp>
#include <Geode/modify/GJMessagePopup.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>
#include "EmojiPickPopup.h"

using namespace geode::prelude;

#include "CCLabelBMFontExt.hpp"
#include "TextAreaExt.hpp"

class $modify (ShareCommentLayerExt, ShareCommentLayer)
{
    struct Fields {
        bool isComment = false;
        CCTextInputNode *inp = nullptr;
    };

    void onEmojis(CCObject *) {
        EmojiPickPopup::create()->show();
    }

    bool init(gd::string p0, int p1, CommentType p2, int p3, gd::string p4) {
        if (!ShareCommentLayer::init(p0, p1, p2, p3, p4))
            return false;

        if (!(std::string(p0) == "Post Update" || std::string(p0) == "Add Comment"))
            return true;

        if (auto l = as<CCLayer *>(this->getChildren()->objectAtIndex(0))) {
            if (auto i = getChildOfType<CCTextInputNode>(l, 0))
                m_fields->inp = i;

            if (auto m = typeinfo_cast<CCMenu*>(l->getChildren()->objectAtIndex(2))) {
                auto spr = CCSprite::createWithSpriteFrameName("emoji-icon-thicker.png"_spr);
                spr->setScale(0.8f);
                spr->setOpacity(150);

                auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(ShareCommentLayerExt::onEmojis));
                btn->setPosition(ccp(178, 38));

                m->addChild(btn);
            }
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

class $modify(MenuLayer)
{
    bool init()
    {
        MenuLayer::init();

        auto area = TextAreaExt::create("hang up that computer call, come over here and kiss me on my hot mouth. im feeling freaky", "chatFont.fnt");
        area->setPosition(CCDirector::get()->getWinSize() / 2);
        area->setContentSize(ccp(200, 60));
        area->setAnchorPoint(ccp(0.5f, 0.5f));
        area->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);

        this->addChild(area, 420);

        return true;
    }
};