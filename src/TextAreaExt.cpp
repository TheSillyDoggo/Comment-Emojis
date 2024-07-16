#include "TextAreaExt.hpp"

bool TextAreaExt::init(const char* string, const char* font)
{
    if (!CCLabelBMFont::init())
        return false;

    objNode = CCNode::create();
    objNode->retain();

    this->setString(string, false);
    this->setFntFile(font);

    return true;
}

TextAreaExt* TextAreaExt::create(const char* string, const char* font)
{
    auto pRet = new TextAreaExt();

    if (pRet && pRet->init(string, font))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}

std::vector<CCLabelBMFontExt*> TextAreaExt::splitStringIntoLabels(int lineCount)
{
    std::vector<CCLabelBMFontExt*> lbls;
    std::vector<LabelPart> ps;

    auto lbl = CCLabelBMFontExt::create(string, font);
    float x = 0;

    if (lineCount == 1)
    {
        lbls.push_back(lbl);
    }
    else
    {
        for (auto part : lbl->parts)
        {
            x += part.node->getScaledContentWidth();
            ps.push_back(part);

            if (x + part.node->getScaledContentWidth() > this->getContentWidth())
            {
                x = 0;

                auto str = LabelPart::stringFromVector(ps);

                auto l = CCLabelBMFontExt::create(str.c_str(), font);
                lbls.push_back(l);

                ps.clear();
            }
        }

        if (!ps.empty())
        {
            auto str = LabelPart::stringFromVector(ps);

            auto l = CCLabelBMFontExt::create(str.c_str(), font);
            lbls.push_back(l);
        }
    }

    return lbls;
}

void TextAreaExt::setLineHeight(float lineHeight)
{
    this->lineHeight = lineHeight;
    updateLabel();
}

float TextAreaExt::getLineHeight()
{
    return lineHeight;
}

void TextAreaExt::updateLabel()
{
    if (!objNode || getContentWidth() == 0)
        return;

    this->removeAllChildren();

    auto lbl = CCLabelBMFontExt::create(string, font);
    lbl->setColor(colour);
    lbl->setOpacity(opacity);

    auto lineCount = std::floor<int>((lbl->getScaledContentWidth() / this->getContentWidth()) + 1) + 1;
    
    if (lineCount < 1)
        lineCount = 1;

    auto parts = splitStringIntoLabels(lineCount);

    float y = 0;
    int count = parts.size();

    for (auto part : parts)
    {
        part->setColor(colour);
        part->setOpacity(opacity);

        switch (alignment)
        {
            case CCTextAlignment::kCCTextAlignmentLeft:
                part->setAnchorPoint(ccp(0, 0));
                part->setPositionX(0);
                break;

            case CCTextAlignment::kCCTextAlignmentCenter:
                part->setAnchorPoint(ccp(0.5f, 0));
                part->setPositionX(getContentWidth() / 2);
                break;

            case CCTextAlignment::kCCTextAlignmentRight:
                part->setAnchorPoint(ccp(1, 0));
                part->setPositionX(getContentWidth());
                break;
        };

        switch (verticalAlignment)
        {
            case CCVerticalTextAlignment::kCCVerticalTextAlignmentTop:
                part->setAnchorPoint(ccp(part->getAnchorPoint().x, 1));
                part->setPositionY(this->getContentHeight() - y);
                y += lineHeight;
                break;

            case CCVerticalTextAlignment::kCCVerticalTextAlignmentCenter:
                part->setAnchorPoint(ccp(part->getAnchorPoint().x, 0.5f));
                part->setPositionY((((count * lineHeight) / 2) / 2) - y);
                part->setPositionY(part->getPositionY() + this->getContentHeight() / 2);
                y += lineHeight / 2;
                break;

            case CCVerticalTextAlignment::kCCVerticalTextAlignmentBottom:
                part->setAnchorPoint(ccp(part->getAnchorPoint().x, 0));
                part->setPositionY(y);
                y += lineHeight;
                break;
        };

        this->addChild(part);
    }
}

void TextAreaExt::setString(const char *newString)
{
    this->setString(newString, true);
}

void TextAreaExt::setString(const char *newString, bool needUpdateLabel)
{
    this->string = newString;

    if (needUpdateLabel)
        updateLabel();
}

const char* TextAreaExt::getString(void)
{
    return string;
}

void TextAreaExt::setFntFile(const char* fntFile)
{
    this->font = fntFile;
}

const char* TextAreaExt::getFntFile() { return font; }

void TextAreaExt::setCString(const char *label) { }

void TextAreaExt::setAnchorPoint(const CCPoint& var) { CCNode::setAnchorPoint(var); }

void TextAreaExt::setAlignment(CCTextAlignment alignment)
{
    this->alignment = alignment;
    updateLabel();
}

void TextAreaExt::setWidth(float width) { }

void TextAreaExt::setLineBreakWithoutSpace(bool breakWithoutSpace) { }

void TextAreaExt::setScale(float scale) { CCNode::setScale(scale); }
void TextAreaExt::setScaleX(float scaleX) { CCNode::setScaleX(scaleX); }
void TextAreaExt::setScaleY(float scaleY) { CCNode::setScaleY(scaleY); }

bool TextAreaExt::isOpacityModifyRGB() { return false; }
void TextAreaExt::setOpacityModifyRGB(bool isOpacityModifyRGB) { }

GLubyte TextAreaExt::getOpacity() { return opacity; }
GLubyte TextAreaExt::getDisplayedOpacity() { return opacity; }

void TextAreaExt::setOpacity(GLubyte opacity)
{
    this->opacity = opacity;
    updateLabel();
}

void TextAreaExt::updateDisplayedOpacity(GLubyte parentOpacity)
{
    this->opacity = parentOpacity;
    updateLabel();
}

bool TextAreaExt::isCascadeOpacityEnabled() { return false; }

void TextAreaExt::setCascadeOpacityEnabled(bool cascadeOpacityEnabled) { }

const ccColor3B& TextAreaExt::getColor(void) { return colour; }
const ccColor3B& TextAreaExt::getDisplayedColor() { return colour; }

void TextAreaExt::setColor(const ccColor3B& color)
{
    this->colour = color;
    updateLabel();
}

void TextAreaExt::updateDisplayedColor(const ccColor3B& parentColor)
{
    this->colour = parentColor;
    updateLabel();
}

bool TextAreaExt::isCascadeColorEnabled() { return false; }
void TextAreaExt::setCascadeColorEnabled(bool cascadeColorEnabled) { }

void TextAreaExt::addChild(CCNode* child) { CCNode::addChild(child); }
void TextAreaExt::addChild(CCNode* child, int zOrder) { CCNode::addChild(child, zOrder); }
void TextAreaExt::addChild(CCNode* child, int zOrder, int tag) { CCNode::addChild(child, zOrder, tag); }

void TextAreaExt::removeChild(CCNode* child, bool cleanup) { CCNode::removeChild(child, cleanup); }
void TextAreaExt::removeAllChildrenWithCleanup(bool cleanup) { CCNode::removeAllChildrenWithCleanup(cleanup); }
void TextAreaExt::sortAllChildren() { CCNode::sortAllChildren(); }

void TextAreaExt::setContentSize(const CCSize& contentSize)
{
    CCNode::setContentSize(contentSize);
    updateLabel();
}

void TextAreaExt::visit() { CCNode::visit(); }
void TextAreaExt::draw() { CCNode::draw(); }

TextAreaExt::~TextAreaExt()
{
    objNode->release();
}