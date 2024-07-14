#pragma once

#include <Geode/Geode.hpp>
#include "CCLabelBMFontExt.hpp"

using namespace geode::prelude;

class TextAreaExt : public CCLabelBMFont
{
    public:
        const char* string = "";
        const char* font = "";
        CCTextAlignment alignment;
        CCVerticalTextAlignment verticalAlignment = CCVerticalTextAlignment::kCCVerticalTextAlignmentTop;
        ccColor3B colour = ccc3(255, 255, 255);
        GLubyte opacity = 255;
        CCNode* objNode;

        bool init(const char* string, const char* font);
        static TextAreaExt* create(const char* string, const char* font);

        std::vector<CCLabelBMFontExt*> splitStringIntoLabels(int lineCount);

        ~TextAreaExt();

        virtual void setString(const char *newString);
        virtual void setString(const char *newString, bool needUpdateLabel);

        void setFntFile(const char* fntFile);
        const char* getFntFile();

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

        virtual void setContentSize(const CCSize& contentSize);

        virtual void visit();
        virtual void draw();
};