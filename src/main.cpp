#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/TextArea.hpp>
#include <Geode/modify/CommentCell.hpp>
#include <Geode/modify/ShareCommentLayer.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

#include "CCLabelBMFontExt.h"

class $modify (CommentCell)
{
	CCLabelBMFontExt* label = nullptr;

	void onUnhide(cocos2d::CCObject* sender)
	{
		#ifdef GEODE_IS_ANDROID
		CommentCell::onUnhide(sender);
		#endif

		//m_fields->label->setString()
	}

	void loadFromComment(GJComment* p0)
	{
		CommentCell::loadFromComment(p0);
		
		if (auto txt = as<CCLayerColor*>(this->getChildren()->objectAtIndex(1))->getChildByID("comment-text-label"))
		{
			txt->setVisible(false);

			auto lbl2 = CCLabelBMFontExt::create(p0->m_commentString.c_str(), "chatFont.fnt");

			if (p0->m_isSpam)
				lbl2->setString("Comment flagged as spam");

			m_fields->label = lbl2;

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

			if (p0->m_isSpam)
				lbl2->setString("Comment flagged as spam");

			m_fields->label = lbl2;

			if (lbl2)
			{
				if (this->m_accountComment)
					lbl2->setPosition(ccp(10, 40));
				else
					lbl2->setPosition(ccp(10, 32.5f));

				lbl2->setAnchorPoint(ccp(0, 0.5f));
				lbl2->setMaxX(310, true);
				if (this->m_accountComment)
					lbl2->limitLabelHeight(50, 1.0f, 0.1f);
				else
					lbl2->limitLabelHeight(45, 1.0f, 0.1f);

				as<CCLayerColor*>(this->getChildren()->objectAtIndex(1))->addChild(lbl2);
			}

			return;
		}
	}
};

class $modify (ShareCommentLayerExt, ShareCommentLayer)
{
	CCMenu* commentMenu = nullptr;
	bool visible = false;
	CCTextInputNode* inp = nullptr;

	void onEmojis(CCObject*)
	{
		m_fields->visible = !m_fields->visible;
		
		auto menu = m_fields->commentMenu;
		menu->stopAllActions();

		#ifdef GEODE_IS_MACOS

		if (m_fields->visible)
		{
			menu->runAction((CCMoveTo::create(0.75f, ccp(CCDirector::get()->getWinSize().width, 0))));
		}
		else
		{
			menu->runAction((CCMoveTo::create(0.75f, ccp(CCDirector::get()->getWinSize().width + menu->getContentSize().width, 0))));
		}

		#else

		if (m_fields->visible)
		{
			menu->runAction(CCEaseInOut::create(CCMoveTo::create(0.75f, ccp(CCDirector::get()->getWinSize().width, 0)), 2));
		}
		else
		{
			menu->runAction(CCEaseInOut::create(CCMoveTo::create(0.75f, ccp(CCDirector::get()->getWinSize().width + menu->getContentSize().width, 0)), 2));
		}

		#endif
	}

	void onSelectEmoji(CCObject* sender)
	{
		auto str = as<CCNode*>(sender)->getID();

		auto inp = m_fields->inp;

		std::stringstream ss;
		ss << inp->getString().c_str();
		ss << ":";
		ss << str;
		ss << ":";

		inp->setString(as<gd::string>(ss.str()));
	}

	bool init(gd::string p0, int p1, CommentType p2, int p3, gd::string p4)
	{
		if (!ShareCommentLayer::init(p0, p1, p2, p3, p4))
			return false;
		
		if (!(std::string(p0) == "Post Update" || std::string(p0) == "Add Comment"))
			return true;

		if (auto l = as<CCLayer*>(this->getChildren()->objectAtIndex(0)))
		{
			if (auto i = getChildOfType<CCTextInputNode>(l, 0))
				m_fields->inp = i;

			if (auto m = as<CCMenu*>(l->getChildren()->objectAtIndex(2)))
			{
				auto spr = CCSprite::createWithSpriteFrameName("emoji-icon-thicker.png"_spr);
				spr->setScale(0.8f);
				spr->setOpacity(150);

				auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(ShareCommentLayerExt::onEmojis));
				btn->setPosition(ccp(178, 38));

				m->addChild(btn);
			}
		}

		auto menu = CCMenu::create();
		menu->setContentSize(ccp(180, 170));
		menu->setAnchorPoint(ccp(1, 0));
		menu->ignoreAnchorPointForPosition(false);
		menu->setPosition(ccp(CCDirector::get()->getWinSize().width + menu->getContentSize().width, 0));

		auto bg = CCScale9Sprite::create("GJ_square05.png");
		bg->setContentSize(menu->getContentSize() * 1.5f);
		bg->setScale(1.0f / 1.5f);
		bg->setAnchorPoint(ccp(0, 0));
		bg->setPosition(ccp(0, 0));
		menu->addChild(bg);

		auto scroll = ScrollLayer::create(menu->getContentSize() + ccp(-20, -20));
		scroll->setPosition(ccp(10, 10));
		menu->addChild(scroll);

		int x = 0;
		int y = 0;

		int rowCount = 8;

		float size = (scroll->getContentWidth() - 10 - 10) / (rowCount - 1);

		auto m = CCMenu::create();
		m->setPosition(ccp(0, 0));
		m->setContentHeight(9999);

		for (size_t i = 0; i < emojis.size(); i++)
		{
			auto spr = CCSprite::createWithSpriteFrameName(emojis[i].second.c_str());

			if (spr)
			{
				spr->setScale(15 / std::max(spr->getContentWidth(), spr->getContentHeight()));

				auto btn = CCMenuItemSpriteExtra::create(spr, this, menu_selector(ShareCommentLayerExt::onSelectEmoji));
				btn->setID(emojis[i].first);

				btn->setPosition(ccp( (size * x) + 10, (size * y) + 10));
				//menu->addChild(btn);
				m->addChild(btn);

				x++;

				if (x > (rowCount - 1))
				{
					x = 0;
					y++;
				}
			}
		}

		scroll->m_contentLayer->addChild(m);
		scroll->m_contentLayer->setContentHeight(size * y + (10 + 10));

		this->addChild(menu);

		m_fields->commentMenu = menu;

		return true;
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