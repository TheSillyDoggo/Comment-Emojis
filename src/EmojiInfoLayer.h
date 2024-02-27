#ifndef GEODE_IS_MACOS

#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/ui/TextInput.hpp>

using namespace geode::prelude;

#include "CCLabelBMFontExt.h"

class EmojiInfoLayer : public CCLayerColor
{
    public:
        
        virtual void keyBackClicked()
        {
            onClose(nullptr);
        }

        void onClose(CCObject*)
        {
            CCTouchDispatcher::get()->removeDelegate(this);

            this->removeFromParent();
        }

        bool init(std::string emoji)
        {
            if (!CCLayerColor::init())
                return false;

            this->setKeypadEnabled(true);

            auto panel = CCScale9Sprite::create("GJ_square01.png");
            panel->setContentSize(ccp(240, 250));
            this->addChildAtPosition(panel, Anchor::Center);

            auto title = CCLabelBMFont::create((std::string(":") + emoji + std::string(":")).c_str(), "bigFont.fnt");
            title->setScale(0.65f);
            this->addChildAtPosition(title, Anchor::Center, ccp(0, 70 + 38));

            std::string ss;

            for (size_t i = 0; i < emojis.size(); i++)
            {
                if (emojis[i].first == emoji)
                {
                    ss = emojis[i].second;
                    break;
                }
            }

            auto spr = CCSprite::createWithSpriteFrameName(ss.c_str());
            spr->setScale(2);
            this->addChildAtPosition(spr, Anchor::Center);

            auto menu = CCMenu::create();

            auto ok = CCMenuItemSpriteExtra::create(ButtonSprite::create("OK"), this, menu_selector(EmojiInfoLayer::onClose));
            menu->addChildAtPosition(ok, Anchor::Center, ccp(0, -63 - 39));

            this->addChild(menu);

            this->runAction(CCFadeTo::create(0.5f, 125));
            this->ignoreAnchorPointForPosition(true);

            CCTouchDispatcher::get()->addTargetedDelegate(this, -169, true);
            CCTouchDispatcher::get()->addTargetedDelegate(menu, -170, true);

            return true;
        }

        static EmojiInfoLayer* create(std::string emoji)
        {
            EmojiInfoLayer* pRet = new EmojiInfoLayer();
            if (pRet && pRet->init(emoji)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                return nullptr;
            }
        }

        static void addToScene(std::string emoji)
        {
            auto pRet = EmojiInfoLayer::create(emoji);

            CCScene::get()->addChild(pRet, CCScene::get()->getHighestChildZ() + 1);
        }
};

#endif