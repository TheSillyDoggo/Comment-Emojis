#include <Geode/Geode.hpp>
#include <Geode/modify/CCMenu.hpp>
#include "../EmojiPickPopup.hpp"

using namespace geode::prelude;

class EditLabelPopup : public geode::Popup<> {};

class $modify (EditLabelPopupExt, CCMenu)
{
    struct Fields
    {
        TextInput* input;
    };

    static CCMenu* create()
    {
        auto pRet = CCMenu::create();

        Loader::get()->queueInMainThread([pRet]
        {
            if (pRet->getID() == "Format" && CCScene::get()->getChildByType<EditLabelPopup>(0))
            {
                if (auto menu = pRet)
                {
                    as<EditLabelPopupExt*>(pRet)->m_fields->input = menu->getChildByType<TextInput>(0);
                    as<AnchorLayoutOptions*>(as<EditLabelPopupExt*>(pRet)->m_fields->input->getLayoutOptions())->setOffset(ccp(-15, 0));

                    auto spr = CCSprite::createWithSpriteFrameName("emoji-icon-thicker.png"_spr);
                    spr->setOpacity(100);

                    auto btn = CCMenuItemSpriteExtra::create(spr, pRet, menu_selector(EditLabelPopupExt::onPickEmojis));
                    btn->setID("emojis-btn"_spr);

                    auto menu2 = CCMenu::create();
                    menu2->ignoreAnchorPointForPosition(false);
                    menu2->setContentSize(CCPointZero);
                    menu2->setScale(0.65f);
                    menu2->addChild(btn);

                    menu->addChildAtPosition(menu2, Anchor::Right, ccp(-22, 0));

                    menu->updateLayout();
                }
            }
        });

        return pRet;
    }

    void onPickEmojis(CCObject* sender)
    {
        auto popup = EmojiPickPopup::create(m_fields->input->getInputNode(), m_fields->input);
        popup->show();
        popup->proxy->ignoreAnchorPointForPosition(false);
    }
};