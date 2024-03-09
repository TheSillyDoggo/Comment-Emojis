#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>

#include <iostream>
#include <regex>
#include <string>

using namespace geode::prelude;

std::pair<std::string, std::string> _Emoji(std::string name)
{
    auto spr = std::string(""_spr);

    return std::pair(name, spr + (name + std::string(".png")));
}

std::vector<std::pair<std::string, std::string>> emojis = {
    std::pair("auto", "diffIcon_auto_btn_001.png"),
    std::pair("na", "diffIcon_00_btn_001.png"),
    std::pair("easy", "diffIcon_01_btn_001.png"),
    std::pair("normal", "diffIcon_02_btn_001.png"),
    std::pair("hard", "diffIcon_03_btn_001.png"),
    std::pair("harder", "diffIcon_04_btn_001.png"),
    std::pair("insane", "diffIcon_05_btn_001.png"),
    std::pair("easydemon", "diffIcon_07_btn_001.png"),
    std::pair("mediumdemon", "diffIcon_08_btn_001.png"),
    std::pair("harddemon", "diffIcon_06_btn_001.png"),
    std::pair("insanedemon", "diffIcon_09_btn_001.png"),
    std::pair("extremedemon", "diffIcon_10_btn_001.png"),

    std::pair("star", "GJ_starsIcon_001.png"),

    std::pair("orb", "currencyOrb_001.png"),
    std::pair("orbs", "currencyOrbIcon_001.png"),

    std::pair("diamond", "diamond_small01_001.png"),
    std::pair("diamonds", "currencyDiamondIcon_001.png"),

    std::pair("like", "GJ_likesIcon_001.png"),
    std::pair("dislike", "GJ_dislikesIcon_001.png"_spr), // rob i genuinely hate you for making it this differetn size it is size size different

    std::pair("check", "GJ_completesIcon_001.png"),
    std::pair("cross", "GJ_deleteIcon_001.png"),

    std::pair("locked", "GJLargeLock_001.png"),
    std::pair("lockedgray", "GJ_lockGray_001.png"),
    std::pair("unlocked", "GJ_lock_open_001.png"),

    std::pair("goldcoin", "GJ_coinsIcon_001.png"),
    std::pair("uncollectedusercoin", "GJ_coinsIcon_gray_001.png"),
    _Emoji("usercoinunverified"),
    std::pair("usercoin", "GJ_coinsIcon2_001.png"),
    std::pair("points", "GJ_pointsIcon_001.png"),

    std::pair("mod", "modBadge_01_001.png"),
    std::pair("eldermod", "modBadge_02_001.png"),
    std::pair("leaderboardmod", "modBadge_03_001.png"),

    //other
    _Emoji("amogus"),
    _Emoji("bruh"),
    _Emoji("carlos"),
    _Emoji("clueless"),
    _Emoji("despair"),
    _Emoji("despair2"),
    _Emoji("ned"),
    std::pair("pusab?", "pusab.png"_spr),
    _Emoji("robsmile"),
    _Emoji("sip"),
    _Emoji("splat"),
    _Emoji("teehee"),
    _Emoji("trollface"),
    _Emoji("true"),
    _Emoji("walter"),
    _Emoji("wha"),
    _Emoji("whadahell"),
    _Emoji("youshould"),
    _Emoji("car"),
    _Emoji("zoink"),
    _Emoji("shocked"),
    _Emoji("poppinbottles"),
    _Emoji("party"),
    _Emoji("dabmeup"),
    _Emoji("fireinthehole"),
    _Emoji("xcreatorgoal"),
    _Emoji("soggy"),
    _Emoji("mayo"),
    _Emoji("divine"),
    _Emoji("rattledash"),
    _Emoji("gd"),

    //discord
    _Emoji("100"),
    _Emoji("shushing_face"),
    _Emoji("deaf_person"),
    _Emoji("deaf_man"),
    _Emoji("deaf_woman"),
    _Emoji("bear"),
    _Emoji("broken_heart"),
    _Emoji("cat"),
    _Emoji("dog"),
    _Emoji("fox"),
    _Emoji("gun"),
    _Emoji("face_with_raised_eyebrow"),
    _Emoji("middle_finger"),
    _Emoji("moyai"),
    _Emoji("fire"),
    _Emoji("nerd"),
    _Emoji("radioactive"),
    _Emoji("shocked_face"),
    _Emoji("skull"),
    _Emoji("smiling_imp"),
    _Emoji("speaking_head"),
    _Emoji("sob"),
    _Emoji("eggplant"),
    _Emoji("clown"),
};

#include "EmojiInfoLayer.h"

enum LabelPartType
{
    Text,
    Emoji,
    Username,
    Url,
    Level
};

struct LabelPart
{
    LabelPartType type = LabelPartType::Text;
    std::string extra = "";

    LabelPart(LabelPartType type, std::string ext)
    {
        this->type = type;
        this->extra = ext;
    }

    std::string fileNameForEmoji()
    {
        if (type == LabelPartType::Text)
            return "";

        for (size_t i = 0; i < emojis.size(); i++)
        {
            if (geode::utils::string::toLower(emojis[i].first) == geode::utils::string::toLower(extra))
                return emojis[i].second;
        }

        return "";
    }

    bool isValid()
    {
        return (CCSpriteFrameCache::get()->spriteFrameByName(fileNameForEmoji().c_str()));
    }
};

class CCLabelBMFontExt : public CCMenu
{
    public:
        std::vector<LabelPart> parts;

        std::string font = "";
        std::string text = "";

        float maxX;

        bool isUrl(std::string str) {
            std::regex pattern("^(https?:\\/\\/)?((?:[^\\/:@\\s]+\\.)+)((?:[a-z]{2,})|(?:xn--[a-z0-9\\-]{2,}))(?:\\/\\S*)?$");
    
            return std::regex_match(str, pattern);
        }

        bool isLevel(std::string str)
        {
            std::regex pattern("^[0-9]+$");
    
            return std::regex_match(str, pattern);
        }

        void onEmoji(CCObject* sender)
        {
            #ifndef GEODE_IS_MACOS
            auto str = as<CCNode*>(sender)->getID();

            EmojiInfoLayer::addToScene(str);
            #endif
        }

        void onUsername(CCObject* sender)
        {
            auto str = as<CCNode*>(sender)->getID();

            log::info("username: {}", str);

            auto search = GJSearchObject::create(SearchType::Users, str.c_str());
            auto browser = LevelBrowserLayer::create(search);

            auto scene = CCScene::create();
            scene->addChild(browser);

            CCDirector::get()->pushScene(CCTransitionFade::create(0.5f, scene));

            //usernameForUserID()
        }

        void onLevel(CCObject* sender)
        {
            auto str = as<CCNode*>(sender)->getID();

            log::info("level: {}", str);

            auto search = GJSearchObject::create(SearchType::Search, str.c_str());
            auto browser = LevelBrowserLayer::create(search);

            auto scene = CCScene::create();
            scene->addChild(browser);

            CCDirector::get()->pushScene(CCTransitionFade::create(0.5f, scene));

            //usernameForUserID()
        }

        void onUrl(CCObject* sender)
        {
            auto str = as<CCNode*>(sender)->getID();

            log::info("url: {}", str);

            geode::createQuickPopup(
                "Hold Up!",
                "Links are spooky! Are you sure you want to go to\n<cy>" + str + "</c>?",
                "Cancel", "Yes",
                [str](FLAlertLayer*, bool btn2) {
                    if (btn2) {
                        CCApplication::get()->openURL(str.c_str());
                        //geode::utils::web::openLinkInBrowser(str);
                    }
                }
            );
        }

        virtual void updateLabel() // copying types from normal label
        {
            parts.clear();

            std::string s;
            bool inEmoji = false;

            for (size_t i = 0; i < text.size(); i++)
            {
                if (text[i] == ' ')
                {
                    s = s + " ";

                    parts.push_back(LabelPart(isLevel(s) ? LabelPartType::Level : (isUrl(s) ? LabelPartType::Url : (s.starts_with("@") ? LabelPartType::Username : LabelPartType::Text)), s));

                    inEmoji = false;

                    s = "";

                    continue;
                }

                if (text[i] == ':')
                {
                    if (inEmoji)
                    {
                        auto part = LabelPart(LabelPartType::Emoji, s);
                        
                        if (!part.isValid())
                        {
                            part.type = LabelPartType::Text;
                            s = ":" + s + ":";
                            part.extra = s;
                        }
                        else
                        {
                            
                        }
                        
                        parts.push_back(part);
                    }
                    else
                        parts.push_back(LabelPart(inEmoji ? LabelPartType::Emoji : (isLevel(s) ? LabelPartType::Level : (isUrl(s) ? LabelPartType::Url : (s.starts_with("@") ? LabelPartType::Username : LabelPartType::Text))), s));

                    inEmoji = !inEmoji;

                    s = "";

                    continue; // press start reference no way
                }

                s = s + text[i];
            }

            if (s != "")
            {
                if (inEmoji)
                    s = ":" + s;

                parts.push_back(LabelPart(isLevel(s) ? LabelPartType::Level : (isUrl(s) ? LabelPartType::Url : (s.starts_with("@") ? LabelPartType::Username : LabelPartType::Text)), s));
            }

            float pos = 0;
            float wid = 0;
            int yPos = 0;
            float height = 0;

            float commentHeight = CCLabelBMFont::create("l", font.c_str())->getContentHeight();

            this->removeAllChildren();

            for (size_t i = 0; i < parts.size(); i++)
            {
                auto seg = parts[i];
                //log::info("type: {}, extra: {}, filename: {}", seg.type == LabelPartType::Emoji ? "Emoji" : "Text", seg.extra, seg.fileNameForEmoji());

                if (seg.type == LabelPartType::Text)
                {
                    auto lbl = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl->setAnchorPoint(ccp(0, 0));
                    lbl->setPosition(ccp(pos, -20 * yPos));
                    this->addChild(lbl);
                    
                    height = std::max<float>(height, lbl->getScaledContentSize().height);
                    pos += lbl->getScaledContentSize().width;
                    wid = std::max<float>(wid, pos);

                    if (maxX != 0)
                    {
                        if (pos > maxX)
                        {
                            wid = std::max<float>(wid, pos);
                            pos = 0;
                            yPos++;

                            lbl->setPosition(ccp(pos, -20 * yPos));
                            pos += lbl->getScaledContentSize().width + 2 - 0.75f;
                        }
                    }
                }
                else if (seg.type == LabelPartType::Emoji)
                {
                    auto emoji = CCSprite::createWithSpriteFrameName(seg.fileNameForEmoji().c_str());
                    
                    if (!emoji)
                        continue;

                    emoji->setScale(commentHeight / emoji->getContentHeight());

                    auto emojiBtn = CCMenuItemSpriteExtra::create(emoji, this, menu_selector(CCLabelBMFontExt::onEmoji));
                    emojiBtn->setID(seg.extra);

                    emojiBtn->setPosition(ccp(pos + 2, -20 * yPos) + (emojiBtn->getScaledContentSize() / 2));
                    this->addChild(emojiBtn);

                    #ifdef GEODE_IS_MACOS
                    emojiBtn->setEnabled(false);
                    #endif

                    height = std::max<float>(height, emoji->getScaledContentSize().height);
                    pos += emojiBtn->getScaledContentSize().width + 2 - 0.75f;
                    wid = std::max<float>(wid, pos);

                    if (maxX != 0)
                    {
                        if (pos > maxX)
                        {
                            wid = std::max<float>(wid, pos);
                            pos = 0;
                            yPos++;

                            emojiBtn->setPosition(ccp(pos + 2, -20 * yPos) + (emojiBtn->getScaledContentSize() / 2));
                            pos += emojiBtn->getScaledContentSize().width + 2 - 0.75f;
                        }
                    }
                }
                else if (seg.type == LabelPartType::Username)
                {
                    auto n = CCNode::create();
                    
                    auto lbl = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl->setColor(ccc3(127, 244, 244));
                    lbl->setAnchorPoint(ccp(0, 0));
                    
                    n->addChild(lbl);
                    n->setContentSize(lbl->getContentSize());

                    auto n2 = CCNode::create();
                    
                    auto lbl2 = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl2->setOpacity(150);
                    lbl2->setAnchorPoint(ccp(0, 0));

                    n2->addChild(lbl2);
                    n2->setContentSize(lbl2->getContentSize());

                    auto btn = CCMenuItemSprite::create(n, n2, this, menu_selector(CCLabelBMFontExt::onUsername));
                    btn->setID(seg.extra.substr(1));
                    btn->setPosition(ccp(pos, -20 * yPos));
                    btn->setAnchorPoint(ccp(0, 0));
                    
                    this->addChild(btn);
                    
                    height = std::max<float>(height, lbl->getScaledContentSize().height);
                    pos += lbl->getScaledContentSize().width;
                    wid = std::max<float>(wid, pos);

                    if (maxX != 0)
                    {
                        if (pos > maxX)
                        {
                            wid = std::max<float>(wid, pos);
                            pos = 0;
                            yPos++;

                            lbl->setPosition(ccp(pos, -20 * yPos));
                            pos += lbl->getScaledContentSize().width + 2 - 0.75f;
                        }
                    }
                }
                else if (seg.type == LabelPartType::Url)
                {
                    auto n = CCNode::create();
                    
                    auto lbl = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl->setColor(ccc3(127, 244, 244));
                    lbl->setAnchorPoint(ccp(0, 0));

                    auto line = CCLayerColor::create();
                    line->setColor(lbl->getColor());
                    line->setOpacity(255);
                    line->ignoreAnchorPointForPosition(false);
                    line->setAnchorPoint(ccp(0, 0));
                    line->setPosition(ccp(0, -1));
                    line->setContentWidth(lbl->getContentWidth());
                    line->setContentHeight(1);

                    n->addChild(line);
                    n->addChild(lbl);
                    n->setContentSize(lbl->getContentSize());

                    auto n2 = CCNode::create();
                    
                    auto lbl2 = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl2->setOpacity(150);
                    lbl2->setAnchorPoint(ccp(0, 0));

                    auto line2 = CCLayerColor::create();
                    line2->setColor(lbl2->getColor());
                    line2->setOpacity(150);
                    line2->ignoreAnchorPointForPosition(false);
                    line2->setAnchorPoint(ccp(0, 0));
                    line2->setPosition(ccp(0, -1));
                    line2->setContentWidth(lbl->getContentWidth());
                    line2->setContentHeight(1);

                    n2->addChild(line2);
                    n2->addChild(lbl2);
                    n2->setContentSize(lbl2->getContentSize());

                    auto btn = CCMenuItemSprite::create(n, n2, this, menu_selector(CCLabelBMFontExt::onUrl));
                    btn->setID(seg.extra);
                    btn->setPosition(ccp(pos, -20 * yPos));
                    btn->setAnchorPoint(ccp(0, 0));
                    
                    this->addChild(btn);
                    
                    height = std::max<float>(height, lbl->getScaledContentSize().height);
                    pos += lbl->getScaledContentSize().width;
                    wid = std::max<float>(wid, pos);

                    if (maxX != 0)
                    {
                        if (pos > maxX)
                        {
                            wid = std::max<float>(wid, pos);
                            pos = 0;
                            yPos++;

                            lbl->setPosition(ccp(pos, -20 * yPos));
                            pos += lbl->getScaledContentSize().width + 2 - 0.75f;
                        }
                    }
                }
                else if (seg.type == LabelPartType::Level)
                {
                    auto n = CCNode::create();
                    
                    auto lbl = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl->setColor(ccc3(127, 244, 244));
                    lbl->setAnchorPoint(ccp(0, 0));
                    
                    n->addChild(lbl);
                    n->setContentSize(lbl->getContentSize());

                    auto n2 = CCNode::create();
                    
                    auto lbl2 = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl2->setOpacity(150);
                    lbl2->setAnchorPoint(ccp(0, 0));

                    n2->addChild(lbl2);
                    n2->setContentSize(lbl2->getContentSize());

                    auto btn = CCMenuItemSprite::create(n, n2, this, menu_selector(CCLabelBMFontExt::onLevel));
                    btn->setID(seg.extra);
                    btn->setPosition(ccp(pos, -20 * yPos));
                    btn->setAnchorPoint(ccp(0, 0));
                    
                    this->addChild(btn);
                    
                    height = std::max<float>(height, lbl->getScaledContentSize().height);
                    pos += lbl->getScaledContentSize().width;
                    wid = std::max<float>(wid, pos);

                    if (maxX != 0)
                    {
                        if (pos > maxX)
                        {
                            wid = std::max<float>(wid, pos);
                            pos = 0;
                            yPos++;

                            lbl->setPosition(ccp(pos, -20 * yPos));
                            pos += lbl->getScaledContentSize().width + 2 - 0.75f;
                        }
                    }
                }
            }

            CCArrayExt<CCNode*> objects = this->getChildren();

            for (auto* obj : objects) {
                obj->setPositionY(obj->getPositionY() + (20 * yPos));
            }

            this->setContentSize(ccp(wid, /*height*/20 * (yPos + 1)));
        }

        virtual void setFont(const char *newString, bool update = true)
        {
            font = std::string(newString);

            if (update)
                updateLabel();
        }

        virtual void setString(const char *newString, bool update = true)
        {
            text = std::string(newString);

            if (update)
                updateLabel();
        }

        virtual void setMaxX(float max, bool update = true)
        {
            maxX = max;

            if (update)
                updateLabel();
        }

        float clampf(float v, float min, float max)
        {
            if (v < min)
                v = min;

            if (v > max)
                v = max;

            return v;
        }

        void limitLabelWidth(float width, float defaultScale, float minScale)
        {
            this->setScale(clampf(width / this->getContentSize().width, minScale, defaultScale));
        }

        void limitLabelHeight(float height, float defaultScale, float minScale, bool alignScale = true)
        {
            this->setScale(clampf(height / this->getContentSize().height, minScale, defaultScale));

            if (alignScale)
                setMaxX(this->maxX / this->getScale());

            log::info("f: {}", height / this->getContentSize().height);
        }

        bool init(const char* text, const char* font)
        {
            if (!CCMenu::init())
                return false;

            this->setAnchorPoint(ccp(0.5f, 0.5f));
            this->ignoreAnchorPointForPosition(false);

            this->setFont(font, false);
            this->setString(text, false);

            this->updateLabel();

            handleTouchPriority(this);

            return true;
        }

        static CCLabelBMFontExt* create(const char* text, const char* font)
        {
            CCLabelBMFontExt* pRet = new CCLabelBMFontExt();
            if (pRet && pRet->init(text, font)) {
                pRet->autorelease();
                return pRet;
            } else {
                delete pRet;
                return nullptr;
            }
        }
};
