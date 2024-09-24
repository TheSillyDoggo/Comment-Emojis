#include <Geode/Geode.hpp>
#include <Geode/modify/CCScale9Sprite.hpp>
#include "../TextAreaExt.hpp"
#include <Geode/utils/web.hpp>

using namespace geode::prelude;

class OWCommentCell : public CCScale9Sprite {};

float calculateScale(int length, int minLength, int maxLength, float minScale, float maxScale) {
    if (length <= minLength) {
        return minScale;
    } else if (length >= maxLength) {
        return maxScale;
    } else {
        float scale = minScale - ((length - minLength) * (minScale - maxScale) / (maxLength - minLength));
        return scale;
    }
}

class $modify (CCScale9Sprite)
{
    virtual bool init()
    {
        if (!CCScale9Sprite::init())
            return false;

        if (auto cell = typeinfo_cast<OWCommentCell*>(this))
        {
            Loader::get()->queueInMainThread([cell, this]{
                if (this->getID() == "firee.object-workshop/comment/cell")
                {
                    if (auto txt = typeinfo_cast<TextArea*>(this->getChildByIDRecursive("firee.object-workshop/comment/area")))
                    {
                        if (auto label = typeinfo_cast<CCLabelBMFont*>(this->getChildByIDRecursive("firee.object-workshop/comment/content")))
                        {
                            txt->setVisible(false);

                            auto area = TextAreaExt::create(label->getString(), "chatFont.fnt");

                            if (area)
                            {
                                area->setID("comment-text-area"_spr);
                                area->verticalAlignment = CCVerticalTextAlignment::kCCVerticalTextAlignmentCenter;
                                area->setPosition(txt->getPosition() + ccp(0, -9));
                                area->setAnchorPoint(ccp(0, 0.5f));
                                area->setContentSize(txt->getContentSize());
                                area->setScale(calculateScale(strlen(label->getString()), 16, 100, 0.65F, 0.5F));
                                area->setLineHeight(calculateScale(strlen(label->getString()), 16, 100, 40.F, 25.F));
                                area->setColor(label->getColor());

                                this->addChild(area);
                            }
                        }
                    }
                }
            });
        }

        return true;
    }
};
