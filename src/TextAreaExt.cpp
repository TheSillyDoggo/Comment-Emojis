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
    std::vector<CCLabelBMFontExt*> parts;

    return parts;
}

void TextAreaExt::updateLabel()
{
    if (!objNode || getContentWidth() == 0)
        return;

    this->removeAllChildren();

    auto lbl = CCLabelBMFontExt::create(string, font);
    lbl->setColor(colour);
    lbl->setOpacity(opacity);

    auto lineCount = std::floor<int>((lbl->getScaledContentWidth() / this->getContentWidth()) + 1);

    if (lineCount == 1)
    {
        switch (alignment)
        {
            case CCTextAlignment::kCCTextAlignmentLeft:
                lbl->setAnchorPoint(ccp(0, 0));
                lbl->setPositionX(0);
                break;

            case CCTextAlignment::kCCTextAlignmentCenter:
                lbl->setAnchorPoint(ccp(0.5f, 0));
                lbl->setPositionX(getContentWidth() / 2);
                break;

            case CCTextAlignment::kCCTextAlignmentRight:
                lbl->setAnchorPoint(ccp(1, 0));
                lbl->setPositionX(getContentWidth());
                break;
        };

        switch (verticalAlignment)
        {
            case CCVerticalTextAlignment::kCCVerticalTextAlignmentTop:
                lbl->setAnchorPoint(ccp(lbl->getAnchorPoint().x, 1));
                lbl->setPositionY(this->getContentHeight());
                break;

            case CCVerticalTextAlignment::kCCVerticalTextAlignmentCenter:
                lbl->setAnchorPoint(ccp(lbl->getAnchorPoint().x, 0.5f));
                lbl->setPositionY(this->getContentHeight() / 2);
                break;
        };

        this->addChild(lbl);
        return;
    }

    auto parts = splitStringIntoLabels(lineCount);

    for (auto part : parts)
    {
        part->setColor(colour);
        part->setOpacity(opacity);

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