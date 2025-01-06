#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>

using namespace geode::prelude;

class EmojiNode : public CCSprite
{
    public:
        int currentFrame;
        float progress = 0;
        float rate = 0;
        std::vector<CCSprite*> frames;


        void updateFrame(float);
        virtual void update(float dt);

        bool init(std::string key);
        bool initWithKey(std::string key);
        bool initWithAnimatedSprite(std::string key, float rate);

        static EmojiNode* createWithKey(std::string key);

        static const char* frameForKey(std::string key);
        static std::vector<std::pair<std::string, std::string>> getEmojis();
        static std::vector<std::pair<std::string, float>> getAnimatedEmojis();
};