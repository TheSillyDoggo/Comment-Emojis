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

namespace QOLModExt
{
    class CommentEmojisOverrideLabelCreatePrivateEventPleaseDoNotUseOrIWillTouchYou : public Event
    {
        public:
            std::function<CCLabelBMFont*()> function;

            CommentEmojisOverrideLabelCreatePrivateEventPleaseDoNotUseOrIWillTouchYou(std::function<CCLabelBMFont*()> function)
            {
                this->function = function;
            }
    };
};

$execute
{
    auto e = QOLModExt::CommentEmojisOverrideLabelCreatePrivateEventPleaseDoNotUseOrIWillTouchYou([]
    {
        return CCLabelBMFontExt::create("L", "bigFont.fnt");
    });
    e.post();
};