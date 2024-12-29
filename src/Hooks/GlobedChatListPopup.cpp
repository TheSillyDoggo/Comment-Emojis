#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>
#include "../EmojiPickPopup.hpp"

using namespace geode::prelude;

class GlobedChatListPopup : public geode::Popup<> {};

class $modify (GlobedChatListPopupExt, FLAlertLayer)
{
    struct Fields {
        TextInput* input;
    };

    virtual void show()
    {
        FLAlertLayer::show();

        if (auto popup = typeinfo_cast<GlobedChatListPopup*>(this))
        {
            if (auto menu = popup->m_mainLayer->getChildByType<CCMenu>(-1))
            {
                as<AxisLayout*>(menu->getLayout())->setAutoScale(false);
                m_fields->input = menu->getChildByType<TextInput>(0);

                auto spr = CCSprite::createWithSpriteFrameName("emoji-icon-thicker.png"_spr);
                spr->setOpacity(100);

                auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(GlobedChatListPopupExt::onPickEmojis));
                btn->setID("emojis-btn"_spr);

                menu->addChild(btn);
                menu->setScale(0.892f);
                menu->updateLayout();
            }
        }
    }

    void onPickEmojis(CCObject* sender)
    {
        EmojiPickPopup::create(m_fields->input->getInputNode(), m_fields->input)->show();
    }
};