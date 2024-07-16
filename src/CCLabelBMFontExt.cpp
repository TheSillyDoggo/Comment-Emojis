#include "CCLabelBMFontExt.hpp"

LabelPart::LabelPart(LabelPartType type, std::string ext) {
    this->type = type;
    this->extra = std::move(ext);
}

const char* LabelPart::getFileNameForEmoji()
{
    if (type == LabelPartType::Text)
        return "";

    return EmojiNode::frameForKey(extra);
}

std::string LabelPart::stringFromVector(std::vector<LabelPart> parts)
{
    std::string ss = "";

    for (auto part : parts)
    {
        if (part.type == LabelPartType::Text)
            ss += std::string(part.extra);

        if (part.type == LabelPartType::Emoji)
        {
            ss += ":";
            ss += std::string(part.extra);
            ss += ":";
        }
    }

    return ss;
}

bool LabelPart::isValidEmoji()
{
    return CCSpriteFrameCache::get()->m_pSpriteFrames->objectForKey(getFileNameForEmoji());
}



bool CCLabelBMFontExt::init(const char *text, const char *font) {
    if (!CCLabelBMFont::init())
        return false;

    objNode = CCNode::create();
    objNode->retain();
    this->addChild(objNode);

    this->setAnchorPoint(ccp(0.5f, 0.5f));
    this->ignoreAnchorPointForPosition(false);

    this->setString(text, false);
    this->setFntFile(font); // updates label

    return true;
}

CCLabelBMFontExt* CCLabelBMFontExt::create(const char *text, const char *font) {
    auto *pRet = new CCLabelBMFontExt();

    if (pRet && pRet->init(text, font))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}

void CCLabelBMFontExt::setString(const char *newString)
{
    setString(newString, true);
}

void CCLabelBMFontExt::setString(const char *newString, bool needUpdateLabel)
{
    string = newString;

    if (needUpdateLabel)
        updateLabel();
}

const char* CCLabelBMFontExt::getString()
{
    return string.c_str();
}

void CCLabelBMFontExt::setFntFile(const char* fntFile)
{
    font = fntFile;
    updateLabel();
}

const char* CCLabelBMFontExt::getFntFile()
{
    return font.c_str();
}

void CCLabelBMFontExt::setCString(const char *label)
{

}

void CCLabelBMFontExt::setAnchorPoint(const CCPoint& var)
{
    CCNode::setAnchorPoint(var);
}

void CCLabelBMFontExt::setAlignment(CCTextAlignment alignment)
{
    this->alignment = alignment;
    updateLabel();
}

void CCLabelBMFontExt::setWidth(float width)
{

}

void CCLabelBMFontExt::setLineBreakWithoutSpace(bool breakWithoutSpace)
{

}

void CCLabelBMFontExt::setScale(float scale)
{
    CCNode::setScale(scale);
}

void CCLabelBMFontExt::setScaleX(float scaleX)
{
    CCNode::setScaleX(scaleX);
}

void CCLabelBMFontExt::setScaleY(float scaleY)
{
    CCNode::setScaleY(scaleY);
}

bool CCLabelBMFontExt::isOpacityModifyRGB() { return false; }

void CCLabelBMFontExt::setOpacityModifyRGB(bool isOpacityModifyRGB) {}

GLubyte CCLabelBMFontExt::getOpacity()
{
    return opacity;
}

GLubyte CCLabelBMFontExt::getDisplayedOpacity()
{
    return opacity;
}

void CCLabelBMFontExt::setOpacity(GLubyte opacity)
{
    this->opacity = opacity;
    updateLabel();
}

void CCLabelBMFontExt::updateDisplayedOpacity(GLubyte parentOpacity)
{
    updateLabel();
}

bool CCLabelBMFontExt::isCascadeOpacityEnabled() { return false; }

void CCLabelBMFontExt::setCascadeOpacityEnabled(bool cascadeOpacityEnabled) {}

const ccColor3B& CCLabelBMFontExt::getColor(void)
{
    return colour;
}

const ccColor3B& CCLabelBMFontExt::getDisplayedColor()
{
    return colour;
}

void CCLabelBMFontExt::setColor(const ccColor3B& color)
{
    colour = color;
    updateLabel();
}

void CCLabelBMFontExt::updateDisplayedColor(const ccColor3B& parentColor)
{
    updateLabel();
}

bool CCLabelBMFontExt::isCascadeColorEnabled() { return false; }

void CCLabelBMFontExt::setCascadeColorEnabled(bool cascadeColorEnabled) {}

void CCLabelBMFontExt::limitLabelWidth(float width, float defaultScale, float minScale)
{
    this->setScale(clampf(width / this->getContentWidth(), minScale, defaultScale));
}

CCLabelBMFont* CCLabelBMFontExt::getOriginalLabel(const char* string, const char* font)
{
    auto l = new CCLabelBMFont();

    if (l && l->initWithString(string, font, kCCLabelAutomaticWidth, kCCTextAlignmentLeft, CCPointZero))
    {
        l->autorelease();
        return l;
    }

    CC_SAFE_DELETE(l);

    return nullptr;
}

void CCLabelBMFontExt::updateLabel()
{
    if (!objNode)
        return;

    objNode->removeAllChildrenWithCleanup(true);

    parts.clear();

    CCSize size = CCSizeMake(0, 0);
    bool inEmoji = false;
    std::string cur = "";
    float h = getOriginalLabel("l", font.c_str())->getContentHeight();
    float x = 2;

    for (auto ch : utils::string::split(string))
    {
        if (ch == ':')
        {
            if (inEmoji)
            {
                inEmoji = false;

                auto part = LabelPart(LabelPartType::Emoji, cur);
                
                if (!part.isValidEmoji())
                {
                    part.type = LabelPartType::Text;
                    part.extra = ":" + part.extra + ":";
                }
                
                parts.push_back(part);
                cur.clear();

            }
            else
            {
                auto part = LabelPart(LabelPartType::Text, cur);
                
                parts.push_back(part);
                cur.clear();

                inEmoji = true;
            }
        }
        else if (ch == ' ')
        {
            if (inEmoji)
            {
                cur = ":" + cur;
                inEmoji = false;
            }

            cur = cur + " ";

            auto part = LabelPart(LabelPartType::Text, cur);
            parts.push_back(part);
            cur.clear();
        }
        else
        {
            cur += ch;
        }
    }

    //log::info("end data: cur: {}, inEmoji: {}", cur, inEmoji);

    if (cur.empty() && inEmoji)
    {
        parts.push_back(LabelPart(LabelPartType::Text, ":"));

        inEmoji = false;
    }

    if (!cur.empty())
    {
        if (inEmoji)
            cur = ":" + cur;

        parts.push_back(LabelPart(LabelPartType::Text, cur));
    }

    int i = 0;

    for (auto part : parts)
    {
        if (part.type == LabelPartType::Text)
        {
            auto lbl = getOriginalLabel(part.extra.c_str(), font.c_str());
            lbl->setAnchorPoint(ccp(0, 0));
            lbl->setColor(colour);
            lbl->setOpacity(opacity);

            if (!lbl)
                return;

            lbl->setPosition(ccp(size.width, 0));
            objNode->addChild(lbl);

            parts[i].node = lbl;
            size.width += lbl->getContentWidth();
            size.height = std::max<float>(size.height, lbl->getContentHeight());
        }
        else if (part.type == LabelPartType::Emoji)
        {
            auto spr = EmojiNode::createWithKey(part.extra);

            if (!spr)
                return;

            spr->setPosition(ccp(size.width + x / 2, 0));
            spr->setAnchorPoint(ccp(0, 0));
            spr->setScale(h / spr->getContentHeight());
            spr->setOpacity(opacity);
            objNode->addChild(spr);

            parts[i].node = spr;
            size.width += spr->getScaledContentSize().width + x;
            size.height = std::max<float>(size.height, spr->getScaledContentSize().height);
        }

        i++;
    }

    this->setContentSize(size);
}

void CCLabelBMFontExt::addChild(CCNode* child)
{
    CCNode::addChild(child);
}

void CCLabelBMFontExt::addChild(CCNode* child, int zOrder)
{
    CCNode::addChild(child, zOrder);
}

void CCLabelBMFontExt::addChild(CCNode* child, int zOrder, int tag)
{
    CCNode::addChild(child, zOrder, tag);
}

void CCLabelBMFontExt::removeChild(CCNode* child, bool cleanup)
{
    CCNode::removeChild(child, cleanup);
}

void CCLabelBMFontExt::removeAllChildrenWithCleanup(bool cleanup)
{
    CCNode::removeAllChildrenWithCleanup(cleanup);
}

void CCLabelBMFontExt::sortAllChildren()
{
    CCNode::sortAllChildren();
}

void CCLabelBMFontExt::visit() { CCNode::visit(); }

void CCLabelBMFontExt::draw() { CCNode::draw(); }

CCLabelBMFontExt::~CCLabelBMFontExt()
{
    objNode->release();
}