#include <Geode/Geode.hpp>
#include <Geode/modify/FLAlertLayer.hpp>

using namespace geode::prelude;

class GlobedChatListPopup : public geode::Popup<> {};

class $modify (GlobedChatListPopupExt, FLAlertLayer)
{
    struct Fields {
        InputNode* input;
    };

    virtual void show()
    {
        FLAlertLayer::show();

        if (auto popup = typeinfo_cast<GlobedChatListPopup*>(this))
        {
            if (auto menu = getChildOfType<CCMenu>(popup->m_mainLayer, -1))
            {
                as<AxisLayout*>(menu->getLayout())->setAutoScale(false);
                m_fields->input = getChildOfType<InputNode>(menu, 0);

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

    }
};