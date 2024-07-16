#include "EmojiPickPopup.hpp"

bool EmojiPickPopup::setup(CCTextInputNode* input, CCNode* node)
{
    this->input = input;
    this->node = node;

    this->setOpacity(0);
    this->runAction(CCFadeTo::create(0.35f, 100));

    hideNode = CCNode::create();
    hideNode->setPosition(CCDirector::get()->getWinSize() / 2);
    hideNode->setAnchorPoint(ccp(0.5f, 0.5f));
    hideNode->setContentSize(ccp(390, 300));

    inputParent = CCNode::create();
    inputParent->setPosition(CCDirector::get()->getWinSize() * ccp(0.5f, 1) + ccp(0, 60));
    inputParent->runAction(CCSequence::create(CCDelayTime::create(0.02f), CCEaseElasticOut::create(CCMoveTo::create(0.5f, CCDirector::get()->getWinSize() * ccp(0.5f, 1) + ccp(0, -55)), 1.5f), nullptr));

    inputBG = CCScale9Sprite::create("geode.loader/GE_square03.png");
    inputBG->setContentSize(ccp(360, 60) + ccp(20, 20));
    inputParent->addChild(inputBG);

    proxy = CCProxyNode::create();
    proxy->setProxy(node);
    proxy->ignoreAnchorPointForPosition(true);
    inputParent->addChild(proxy, 1);

    if (typeinfo_cast<CCTextInputNode*>(node))
    {
        auto bg = CCScale9Sprite::create("square02_001.png");
        bg->setContentSize(ccp(360, 60));
        bg->setOpacity(100);

        inputParent->addChild(bg);
    }

    m_mainLayer->runAction(CCSequence::create(CCDelayTime::create(0.02f), CCEaseElasticOut::create(CCMoveTo::create(0.5f, ccp(0, -40)), 2), nullptr));
    m_mainLayer->setPositionY(-CCDirector::get()->getWinSize().height);

    m_bgSprite->setVisible(false);
    m_buttonMenu->setVisible(false);

    auto bg = CCScale9Sprite::create("geode.loader/GE_square03.png");
    bg->setPosition(CCDirector::get()->getWinSize() / 2);
    bg->setContentSize(m_bgSprite->getContentSize());

    auto scroll = geode::ScrollLayer::create(ccp(330, 180));
    scroll->setPosition(CCDirector::get()->getWinSize() / 2 - scroll->getContentSize() / 2 + ccp(-6, 0));

    populateScroll(scroll->m_contentLayer);

    scroll->moveToTop();

    auto scrollbar = geode::Scrollbar::create(scroll);
    scrollbar->setPosition(CCDirector::get()->getWinSize() / 2 + ccp(127.5f + 40, 0));

    m_mainLayer->addChild(scroll);
    m_mainLayer->addChild(scrollbar);
    m_mainLayer->addChild(bg, -42069);

    this->addChild(inputParent, 69);
    this->addChild(hideNode);
    return true;
}

void EmojiPickPopup::populateScroll(CCContentLayer* content)
{
    float height = 17.5f;
    float spacer = content->getContentWidth() / 11;
    int x = -1;
    float y = 0;

    auto aemojis = EmojiNode::getEmojis();
    auto bemojis = EmojiNode::getAnimatedEmojis();

    std::vector<std::string> emojis;

    for (auto em : aemojis)
    {
        emojis.push_back(em.first);
    }

    for (auto bm : bemojis)
    {
        emojis.push_back(bm.first);
    }

    for (auto emoji : emojis)
    {
        if (!emoji.starts_with("$$newline$$"))
        {
            auto menu = CCMenu::create();

            auto spr = EmojiNode::createWithKey(emoji);

            if (!spr)
                return;

            x++;

            if ((x - 1) * spacer + spacer * 1.5f > content->getContentWidth())
            {
                y++;
                x = 0;
            }

            menu->setPosition(ccp(x * spacer, y * spacer) + ccp(spacer, spacer) / 2);
            spr->setAnchorPoint(ccp(0.5f, 0.5f));
            spr->setScale(height / spr->getContentHeight());

            auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(EmojiPickPopup::onPickEmoji));
            btn->setID(emoji);

            menu->addChild(btn);
            content->addChild(menu);
        }
        else
        {
            //newline

            auto text = CCLabelBMFont::create(emoji.substr(11).c_str(), "chatFont.fnt");
            text->setColor(ccc3(0, 0, 0));
            text->setOpacity(50);
            text->setAnchorPoint(ccp(0, 0.5f));
            text->setPosition(ccp(10, (y + 1.25f) * spacer));

            auto line = CCLayerColor::create();
            line->setOpacity(50);
            line->ignoreAnchorPointForPosition(false);
            line->setContentSize(ccp((content->getContentWidth() - 25) - text->getScaledContentWidth() - 5, 2));
            line->setPosition(ccp(content->getContentWidth() / 2 + text->getScaledContentWidth() / 2 + 5 / 2, (y + 1.25f) * spacer));

            x = -1;
            y += 1.5f;

            content->addChild(line);
            content->addChild(text);
        }
    }

    content->setContentHeight(spacer * (y + 1));

    for (auto child : CCArrayExt<EmojiNode*>(content->getChildren()))
    {
        child->setPositionY(content->getContentHeight() - child->getPositionY());
    }
}

void EmojiPickPopup::onPickEmoji(CCObject* sender)
{
    input->setString(input->getString() + std::string(":") + as<CCNode*>(sender)->getID() + std::string(":"));
}

EmojiPickPopup* EmojiPickPopup::create(CCTextInputNode* input, CCNode* node)
{
    auto ret = new EmojiPickPopup();
    if (ret && ret->init(360, 200, input, node))
    {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}

void EmojiPickPopup::show()
{
    CCScene::get()->addChild(this, CCScene::get()->getHighestChildZ() + 1);
}

void EmojiPickPopup::hide()
{
    m_mainLayer->runAction(CCSequence::create(CCDelayTime::create(0.02f), CCEaseElasticOut::create(CCMoveTo::create(0.5f, ccp(0, -CCDirector::get()->getWinSize().height)), 2), nullptr));
    inputParent->runAction(CCSequence::create(CCDelayTime::create(0.02f), CCEaseElasticOut::create(CCMoveTo::create(0.5f, CCDirector::get()->getWinSize() * ccp(0.5f, 1) + ccp(0, 60)), 1.5f), nullptr));

    this->runAction(CCFadeTo::create(0.35f, 0));

    this->schedule(schedule_selector(EmojiPickPopup::remove), 0.53f);
}

void EmojiPickPopup::remove(float)
{
    this->onClose(nullptr);
}

void EmojiPickPopup::keyDown(enumKeyCodes code)
{
    if (code == enumKeyCodes::KEY_Escape)
        hide();
}

bool EmojiPickPopup::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (CCLayer::ccTouchBegan(pTouch, pEvent))
    {
        auto v = node->isIgnoreAnchorPointForPosition();
        node->ignoreAnchorPointForPosition(false);

        if (typeinfo_cast<CCTextInputNode*>(node))
            node->setAnchorPoint(ccp(0.5f, 0.12f));

        auto b = node->boundingBox().containsPoint(pTouch->getLocation());

        Loader::get()->queueInMainThread([this, b]{
            input->onClickTrackNode(b);
        });

        node->ignoreAnchorPointForPosition(v);

        if (!hideNode->boundingBox().containsPoint(pTouch->getLocation()))
        {
            hide();
        }

        return true;
    }

    return false;
}

void EmojiPickPopup::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{

}

void EmojiPickPopup::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{

}

void EmojiPickPopup::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{

}
