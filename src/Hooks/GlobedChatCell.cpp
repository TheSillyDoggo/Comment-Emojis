#include <Geode/Geode.hpp>
#include <Geode/modify/CCLayerColor.hpp>
#include "../CCLabelBMFontExt.hpp"

using namespace geode::prelude;

class GlobedChatCell : public CCLayerColor { };

class $modify (CCLayerColor)
{
    virtual bool init()
    {
        if (!CCLayerColor::init())
            return false;

        if (typeinfo_cast<GlobedChatCell*>(this))
        {
            Loader::get()->queueInMainThread([this]{
                if (auto text = this->getChildByID("message-text"))
                {
                    auto ext = CCLabelBMFontExt::create(as<CCLabelBMFont*>(text)->getString(), "chatFont.fnt");
                    ext->setAnchorPoint(text->getAnchorPoint());
                    ext->setPosition(text->getPosition());
                    ext->limitLabelWidth(260.0f, 0.8f, 0.0f);
                    ext->setColor(as<CCLabelBMFont*>(text)->getColor());
                    ext->setID("message-text"_spr);

                    text->setVisible(false);
                    this->addChild(ext);
                }
            });
        }

        return true;
    }
};