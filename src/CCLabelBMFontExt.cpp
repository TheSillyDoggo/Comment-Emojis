#include "CCLabelBMFontExt.hpp"

std::pair<std::string, std::string> _Emoji(const std::string &name) {
    auto spr = std::string(""_spr);
    return {name, spr + (name + std::string(".png"))};
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
    _Emoji("potbor"),
    _Emoji("dabmeup"),
    _Emoji("fireinthehole"),
    _Emoji("finger"),
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

LabelPart::LabelPart(LabelPartType type, std::string ext) {
    this->type = type;
    this->extra = std::move(ext);
}

const char* LabelPart::getFileNameForEmoji()
{
    if (type == LabelPartType::Text)
        return "";

    for (auto emoji : emojis) {
        if (geode::utils::string::toLower(emoji.first) == geode::utils::string::toLower(extra))
            return emoji.second.c_str();
    }

    return "";
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
    return string;
}

void CCLabelBMFontExt::setFntFile(const char* fntFile)
{
    font = fntFile;
    updateLabel();
}

const char* CCLabelBMFontExt::getFntFile()
{
    return font;
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

    CCSize size = CCSizeMake(0, 0);
    bool inEmoji = false;
    std::string cur = "";
    std::vector<LabelPart> parts = {};
    float h = getOriginalLabel("l", font)->getContentHeight();
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

    for (auto part : parts)
    {
        if (part.type == LabelPartType::Text)
        {
            auto lbl = getOriginalLabel(part.extra.c_str(), font);
            lbl->setAnchorPoint(ccp(0, 0));
            lbl->setColor(colour);
            lbl->setOpacity(opacity);

            if (!lbl)
                return;

            lbl->setPosition(ccp(size.width, 0));
            objNode->addChild(lbl);

            size.width += lbl->getContentWidth();
            size.height = std::max<float>(size.height, lbl->getContentHeight());
        }
        else if (part.type == LabelPartType::Emoji)
        {
            auto spr = CCSprite::createWithSpriteFrameName(part.getFileNameForEmoji());

            if (!spr)
                return;

            spr->setPosition(ccp(size.width + x / 2, 0));
            spr->setAnchorPoint(ccp(0, 0));
            spr->setScale(h / spr->getContentHeight());
            spr->setOpacity(opacity);
            objNode->addChild(spr);

            size.width += spr->getScaledContentSize().width + x;
            size.height = std::max<float>(size.height, spr->getScaledContentSize().height);
        }
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