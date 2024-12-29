#include <Geode/Geode.hpp>
#include <Geode/modify/CommentCell.hpp>
#include "../CCLabelBMFontExt.hpp"
#include "../TextAreaExt.hpp"

using namespace geode::prelude;

class $modify (CommentCell) {
    struct Fields {
        CCLabelBMFontExt* label;
        TextAreaExt* area;
    };

    void loadFromComment(GJComment* comment)
    {
        CommentCell::loadFromComment(comment);

        if (auto panel = this->getChildByType<CCLayer>(1))
        {
            if (auto txt = panel->getChildByID("comment-text-label"))
            {
                txt->setVisible(false);

                auto lbl = CCLabelBMFontExt::create(comment->m_isSpam ? "Comment flagged as spam" : comment->m_commentString.c_str(), "chatFont.fnt");

                m_fields->label = lbl;

                if (lbl)
                {
                    lbl->setID("comment-text-label"_spr);
                    lbl->setPosition(txt->getPosition());
                    lbl->setAnchorPoint(txt->getAnchorPoint());
                    lbl->limitLabelWidth(270, 0.7f, 0);
                    lbl->setColor(as<CCLabelBMFont*>(txt)->getColor());

                    panel->addChild(lbl);
                }
            }

            if (auto txt = panel->getChildByID("comment-text-area"))
            {
                txt->setVisible(false);

                auto area = TextAreaExt::create(comment->m_isSpam ? "Comment flagged as spam" : comment->m_commentString.c_str(), "chatFont.fnt");

                m_fields->area = area;

                if (area)
                {
                    area->setID("comment-text-area"_spr);
                    area->verticalAlignment = CCVerticalTextAlignment::kCCVerticalTextAlignmentCenter;
                    area->setPosition(txt->getPosition() + ccp(0, -16.5f / 2 - 8));
                    area->setAnchorPoint(ccp(0, 0.5f));
                    area->setContentSize(ccp(320, 40));
                    area->setLineHeight(23 / 0.65f);
                    area->setColor(as<TextArea*>(txt)->getColor());

                    panel->addChild(area);
                }
            }


            if (!m_accountComment && comment->m_accountID == 16778880)
            {
                if (!getChildByID("username-label"))
                    return;
                
                auto badge = CCSprite::createWithSpriteFrameName("geode-icon.png"_spr);
                badge->setScale(0.38f);
                badge->setPosition(panel->getChildByID("username-label")->getPosition() + ccp(panel->getChildByID("username-label")->getScaledContentWidth(), 0) + ccp(8.125f, -1));

                panel->addChild(badge);
            }
        }
    }
};