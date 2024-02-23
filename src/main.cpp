#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/TextArea.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

#include "CCLabelBMFontExt.h"

class $modify (CommentCell)
{
	void loadFromComment(GJComment* p0)
	{
		CommentCell::loadFromComment(p0);

		if (auto txt = as<CCLayerColor*>(this->getChildren()->objectAtIndex(1))->getChildByID("comment-text-label"))
		{
			txt->setVisible(false);

			auto lbl2 = CCLabelBMFontExt::create(p0->m_commentString.c_str(), "chatFont.fnt");

			if (lbl2)
			{
				lbl2->setPosition(txt->getPosition());
				lbl2->setAnchorPoint(txt->getAnchorPoint());
				lbl2->limitLabelWidth(270, 0.7f, 0);

				as<CCLayerColor*>(this->getChildren()->objectAtIndex(1))->addChild(lbl2);
			}

			return;
		}

		if (auto txt = as<TextArea*>(as<CCLayerColor*>(this->getChildren()->objectAtIndex(1))->getChildByID("comment-text-area")))
		{
			txt->setVisible(false);

			auto lbl2 = CCLabelBMFontExt::create(p0->m_commentString.c_str(), "chatFont.fnt");

			if (lbl2)
			{
				lbl2->setPosition(txt->getPosition());
				lbl2->setAnchorPoint(txt->getAnchorPoint());
				lbl2->setMaxX(300);
				//lbl2->limitLabelWidth(270, 0.7f, 0);

				as<CCLayerColor*>(this->getChildren()->objectAtIndex(1))->addChild(lbl2);
			}

			return;
		}
	}
};

/*class $modify (TextArea)
{
	void setString(gd::string p0)
	{
		TextArea::setString(p0);

		if (auto ml = as<MultilineBitmapFont*>(this->getChildren()->objectAtIndex(0)))
		{
			CCArrayExt<CCLabelBMFont*> objects = ml->getChildren();

			for (auto* obj : objects) {
				obj->setVisible(false);

				auto lbl2 = CCLabelBMFontExt::create(obj->getString(), "chatFont.fnt");
				if (lbl2)
				{
					lbl2->setPosition(obj->getPosition());
					lbl2->setAnchorPoint(obj->getAnchorPoint());
					lbl2->setScale(obj->getScale());

					ml->addChild(lbl2);
				}
			}
		}
	}
};*/

/*
CCSprite* img = nullptr;

class $modify(CCLabelBMFont) {

	virtual void draw()
	{
		CCNode::draw();

		//if (typeinfo_cast<CCLabelBMFont*>(this))
		if (true)
		{
			log::info("draw");

			if (img)
				img->draw();
		}
	}

	virtual void updateLabel()
	{
		CCLabelBMFont::updateLabel();

		bool inEmoji = false;
		std::stringstream ss;
		int emojiPos;

		for (size_t i = 0; i < this->getChildrenCount(); i++)
		{
			auto child = reinterpret_cast<CCSprite*>(this->getChildren()->objectAtIndex(i));
			auto chara = this->getString()[i];

			if (chara == " "[0])
				inEmoji = false;

			if (chara == ":"[0])
			{
				if (inEmoji)
				{
					auto emojiName = ss.str();
					auto old = reinterpret_cast<CCSprite*>(this->getChildren()->objectAtIndex(emojiPos));
					
					//auto img = CCSprite::createWithSpriteFrameName("diamond_small01_001.png");
					img = CCSprite::createWithSpriteFrameName("GJ_noteIcon_001.png");
					img->setPosition(old->getPosition());
					img->setTag(i);
					//CCDirector::get()->setNotificationNode(img);
					//img->addChild(CCSprite::createWithSpriteFrameName("label_power_001.png")); // wtf why isn't this working
					//auto img = CCSprite::create("dialogIcon_013.png");
					//img->setPosition(pos);
					//this->getParent()->addChild(img);
					//old->addChild(img);

					//auto layer = CCLayer::create();
					//layer->addChild(img);
					//CCScene::get()->addChild(layer);

					//old->setOpacity(0);

				}
				else
				{
					emojiPos = i;
					ss.clear();
				}

				inEmoji = !inEmoji;
			}
			else
			{
				if (inEmoji)
				{
					ss << chara;
				}
			}
		}
	}
};
*/