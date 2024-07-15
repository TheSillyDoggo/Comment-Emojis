#include "CCProxyNode.hpp"

bool CCProxyNode::init()
{
    if (!CCMenu::init())
        return false;

    this->ignoreAnchorPointForPosition(false);
    this->setPosition(ccp(0, 0));

    return true;
}

void CCProxyNode::setProxy(CCNode* proxy)
{
    node = proxy;
    this->setContentSize(node->getContentSize());
}

CCNode* CCProxyNode::getProxy()
{
    return node;
}

void CCProxyNode::visit(void)
{
    if (node)
    {
        this->setContentSize(node->getContentSize());

        CCNode::visit();
    }
}

void CCProxyNode::draw(void)
{
    auto pos = node->getPosition();
    node->setPosition(node->isIgnoreAnchorPointForPosition() ? CCSizeMake(0, 0) : node->getContentSize() * node->getAnchorPoint());

    node->visit();

    node->setPosition(pos);
}