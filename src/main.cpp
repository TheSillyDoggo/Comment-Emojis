#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <Geode/modify/TextArea.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/ShareCommentLayer.hpp>
#include <Geode/modify/GJMessagePopup.hpp>
#include <Geode/modify/CCKeyboardDispatcher.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>
#include "EmojiPickPopup.hpp"

using namespace geode::prelude;

#include "CCLabelBMFontExt.hpp"
#include "TextAreaExt.hpp"

class $modify(MenuLayer)
{
    bool init()
    {
        MenuLayer::init();

        auto area = TextAreaExt::create("femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy femboy ", "chatFont.fnt");
        area->setPosition(CCDirector::get()->getWinSize() / 2);
        area->setContentSize(ccp(200, 60));
        area->setAnchorPoint(ccp(0.5f, 0.5f));
        area->setAlignment(CCTextAlignment::kCCTextAlignmentCenter);

        this->addChild(area, 420);

        return true;
    }
};