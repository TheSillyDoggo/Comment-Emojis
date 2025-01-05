#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>
#include "EmojiNode.hpp"

#include <iostream>
#include <regex>
#include <string>
#include <utility>

using namespace geode::prelude;

//#define _Emoji(id) std::pair(id, std::string(""_spr) + id + std::string(".png"))

enum LabelPartType {
    Text,
    Emoji,
    Username,
    Url,
    Level
};

struct LabelPart {
    LabelPartType type = LabelPartType::Text;
    std::string extra;
    CCNode* node;

    LabelPart(LabelPartType type, std::string ext);

    const char* getFileNameForEmoji();
    static std::string stringFromVector(std::vector<LabelPart> parts);

    bool isValidEmoji();
};

class CCLabelBMFontExt : public CCLabelBMFont {
    public:
        std::string string = "";
        std::string font = "";
        CCTextAlignment alignment;
        ccColor3B colour = ccc3(255, 255, 255);
        GLubyte opacity = 255;
        CCNode* objNode;
        std::vector<LabelPart> parts;

        virtual void setString(const char *newString);
        virtual void setString(const char *newString, bool needUpdateLabel);

        virtual void updateLabel();
    
        virtual const char* getString(void);
        virtual void setCString(const char *label);
        virtual void setAnchorPoint(const CCPoint& var);
        virtual void setAlignment(CCTextAlignment alignment);
        virtual void setWidth(float width);
        virtual void setLineBreakWithoutSpace(bool breakWithoutSpace);
        virtual void setScale(float scale);
        virtual void setScaleX(float scaleX);
        virtual void setScaleY(float scaleY);

        virtual bool isOpacityModifyRGB();
        virtual void setOpacityModifyRGB(bool isOpacityModifyRGB);
        virtual GLubyte getOpacity();
        virtual GLubyte getDisplayedOpacity();
        virtual void setOpacity(GLubyte opacity);
        virtual void updateDisplayedOpacity(GLubyte parentOpacity);
        virtual bool isCascadeOpacityEnabled();
        virtual void setCascadeOpacityEnabled(bool cascadeOpacityEnabled);
        virtual const ccColor3B& getColor(void);
        virtual const ccColor3B& getDisplayedColor();
        virtual void setColor(const ccColor3B& color);
        virtual void updateDisplayedColor(const ccColor3B& parentColor);
        virtual bool isCascadeColorEnabled();
        virtual void setCascadeColorEnabled(bool cascadeColorEnabled);

        virtual void addChild(CCNode* child);
        virtual void addChild(CCNode* child, int zOrder);
        virtual void addChild(CCNode* child, int zOrder, int tag);

        virtual void removeChild(CCNode* child, bool cleanup);
        virtual void removeAllChildrenWithCleanup(bool cleanup);
        virtual void sortAllChildren();

        virtual void visit();
        virtual void draw();
    
        void setFntFile(const char* fntFile);
        const char* getFntFile();
    
        void limitLabelWidth(float width, float defaultScale, float minScale);

        ~CCLabelBMFontExt();

        CCLabelBMFont* getOriginalLabel(const char* string, const char* font);

        bool init(const char *text, const char *font);

        static CCLabelBMFontExt *create(const char *text, const char *font);
};
