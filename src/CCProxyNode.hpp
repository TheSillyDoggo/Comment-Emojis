#pragma once

#include <Geode/Geode.hpp>
#include <Geode/modify/CCNode.hpp>
#include <Geode/modify/CCLabelBMFont.hpp>

using namespace geode::prelude;

class CCProxyNode : public CCMenu
{
    private:
        CCNode* node;
    public:
        void setProxy(CCNode* proxy);
        CCNode* getProxy();

        virtual bool init();
        virtual void visit(void);
        virtual void draw(void);

        CREATE_FUNC(CCProxyNode);
};