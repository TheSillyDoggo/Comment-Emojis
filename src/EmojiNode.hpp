#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>

using namespace geode::prelude;

class EmojiNode : public CCSprite
{
    public:
        bool initWithKey(std::string key);

        static EmojiNode* createWithKey(std::string key);

        static const char* frameForKey(std::string key);
        static std::vector<std::pair<std::string, std::string>> getEmojis();
};