#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>

using namespace geode::prelude;

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
    std::pair("dislike", "GJ_dislikesIcon_001.png"),

    std::pair("check", "GJ_completesIcon_001.png"),
    std::pair("cross", "GJ_deleteIcon_001.png"),

    std::pair("locked", "GJLargeLock_001.png"),
    std::pair("lockedgray", "GJ_lockGray_001.png"),
    std::pair("unlocked", "GJ_lock_open_001.png"),

    std::pair("goldcoin", "GJ_coinsIcon_001.png"),
    std::pair("uncollectedusercoin", "GJ_coinsIcon_gray_001.png"),
    std::pair("usercoin", "GJ_coinsIcon2_001.png"),
    std::pair("points", "GJ_pointsIcon_001.png"),

    std::pair("mod", "modBadge_01_001.png"),
    std::pair("eldermod", "modBadge_02_001.png"),
    std::pair("leaderboardmod", "modBadge_03_001.png"),
};

enum LabelPartType
{
    Text,
    Emoji
};

struct LabelPart
{
    LabelPartType type = LabelPartType::Text;
    std::string extra = "";

    LabelPart(LabelPartType type, std::string ext)
    {
        this->type = type;
        this->extra = geode::utils::string::toLower(ext);
    }

    std::string fileNameForEmoji()
    {
        if (type == LabelPartType::Text)
            return "";

        for (size_t i = 0; i < emojis.size(); i++)
        {
            if (emojis[i].first == extra)
                return emojis[i].second;
        }

        return "";
    }
};

class CCLabelBMFontExt : public CCNode
{
    public:
        std::vector<LabelPart> parts;

        std::string font = "";
        std::string text = "";

        float maxX;

        virtual void updateLabel() // copying types from normal label
        {
            parts.clear();

            std::string s;
            bool inEmoji = false;

            for (size_t i = 0; i < text.size(); i++)
            {
                if (text[i] == ' ')
                {
                    parts.push_back(LabelPart(LabelPartType::Text, s));

                    inEmoji = false;

                    s = " ";

                    continue;
                }

                if (text[i] == ':')
                {
                    parts.push_back(LabelPart(inEmoji ? LabelPartType::Emoji : LabelPartType::Text, s));

                    inEmoji = !inEmoji;

                    s = "";

                    continue; // press start reference no way
                }

                s = s + text[i];
            }

            //if (s != "")
                //parts.push_back(LabelPart(LabelPartType::Text, s));

            float pos = 0;
            float wid = 0;
            int yPos = 0;
            float height = 0;


            float commentHeight = CCLabelBMFont::create("l", font.c_str())->getContentHeight();

            for (size_t i = 0; i < parts.size(); i++)
            {
                auto seg = parts[i];
                log::info("type: {}, extra: {}, filename: {}", seg.type == LabelPartType::Emoji ? "Emoji" : "Text", seg.extra, seg.fileNameForEmoji());

                if (seg.type == LabelPartType::Text)
                {
                    auto lbl = CCLabelBMFont::create(seg.extra.c_str(), font.c_str(), 99999);
                    lbl->setAnchorPoint(ccp(0, 0));
                    lbl->setPosition(ccp(pos, -20 * yPos));
                    this->addChild(lbl);
                    
                    height = std::max<float>(height, lbl->getScaledContentSize().height);
                    pos += lbl->getScaledContentSize().width;
                    wid = std::max<float>(wid, pos);
                }
                else if (seg.type == LabelPartType::Emoji)
                {
                    auto emoji = CCSprite::createWithSpriteFrameName(seg.fileNameForEmoji().c_str());
                    
                    if (!emoji)
                        continue;

                    emoji->setAnchorPoint(ccp(0, 0));
                    emoji->setPosition(ccp(pos + 2, -20 * yPos));
                    this->addChild(emoji);

                    emoji->setScale(commentHeight / emoji->getContentHeight());

                    height = std::max<float>(height, emoji->getScaledContentSize().height);
                    pos += emoji->getScaledContentSize().width + 2 - 0.75f;
                    wid = std::max<float>(wid, pos);
                }

                if (maxX != 0)
                {
                    if (pos > maxX)
                    {
                        wid = std::max<float>(wid, pos);
                        pos = 0;
                        yPos++;
                    }
                }
            }

            this->setContentSize(ccp(wid, height));
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

        void limitLabelWidth(float width, float defaultScale, float minScale)
        {
            this->setScale(clampf(width / this->getContentSize().width, minScale, defaultScale));
        }

        bool init(const char* text, const char* font)
        {
            if (!CCNode::init())
                return false;

            this->setAnchorPoint(ccp(0.5f, 0.5f));

            this->setFont(font, false);
            this->setString(text, false);

            this->updateLabel();

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