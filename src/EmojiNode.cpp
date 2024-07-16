#include "EmojiNode.hpp"

bool EmojiNode::initWithKey(std::string key)
{
    if (!CCSprite::initWithSpriteFrameName(frameForKey(key)))
        return false;

    

    return true;
}

EmojiNode* EmojiNode::createWithKey(std::string key)
{
    auto pRet = new EmojiNode();

    if (pRet && pRet->initWithKey(key))
    {
        pRet->autorelease();
        return pRet;
    }

    CC_SAFE_DELETE(pRet);
    return nullptr;
}

const char* EmojiNode::frameForKey(std::string key)
{
    for (auto emoji : EmojiNode::getEmojis()) {
        if (!emoji.first.starts_with("$$newline$$") && geode::utils::string::toLower(emoji.first) == geode::utils::string::toLower(key))
            return emoji.second.c_str();
    }

    return "";
}



std::pair<std::string, std::string> _Emoji(const std::string &name) {
    auto spr = std::string(""_spr);
    return {name, spr + (name + std::string(".png"))};
}
std::vector<std::pair<std::string, std::string>> emojis = {
    std::pair("auto", "diffIcon_auto_btn_001.png"),
    std::pair("na", "diffIcon_00_btn_001.png"),
    std::pair("easy", "diffIcon_01_btn_001.png"),
    std::pair("normal", "diffIcon_02_btn_001.png"),
    _Emoji("casual"),
    std::pair("hard", "diffIcon_03_btn_001.png"),
    std::pair("harder", "diffIcon_04_btn_001.png"),
    _Emoji("tough"),
    std::pair("insane", "diffIcon_05_btn_001.png"),
    _Emoji("creul"),
    std::pair("easydemon", "diffIcon_07_btn_001.png"),
    std::pair("mediumdemon", "diffIcon_08_btn_001.png"),
    std::pair("harddemon", "diffIcon_06_btn_001.png"),
    std::pair("insanedemon", "diffIcon_09_btn_001.png"),
    std::pair("extremedemon", "diffIcon_10_btn_001.png"),

    std::pair("star", "GJ_starsIcon_001.png"),

    std::pair("orb", "currencyOrb_001.png"),
    std::pair("orbs", "currencyOrbIcon_001.png"),

    std::pair("diamond", "diamond_small01_001.png"),
    std::pair("diamonds", "currencyDiamondIcon_001.png"),

    std::pair("like", "GJ_likesIcon_001.png"),
    std::pair("dislike", "GJ_dislikesIcon_001.png"_spr), // rob i genuinely hate you for making it this differetn size it is size size different

    std::pair("check", "GJ_completesIcon_001.png"),
    std::pair("cross", "GJ_deleteIcon_001.png"),

    std::pair("locked", "GJLargeLock_001.png"),
    std::pair("lockedgray", "GJ_lockGray_001.png"),
    std::pair("unlocked", "GJ_lock_open_001.png"),

    std::pair("goldcoin", "GJ_coinsIcon_001.png"),
    std::pair("uncollectedusercoin", "GJ_coinsIcon_gray_001.png"),
    _Emoji("usercoinunverified"),
    std::pair("usercoin", "GJ_coinsIcon2_001.png"),
    std::pair("points", "GJ_pointsIcon_001.png"),

    std::pair("mod", "modBadge_01_001.png"),
    std::pair("eldermod", "modBadge_02_001.png"),
    std::pair("leaderboardmod", "modBadge_03_001.png"),

    std::pair("$$newline$$", "$$newline$$"),

    //discord
    _Emoji("100"),
    _Emoji("shushing_face"),
    _Emoji("deaf_person"),
    _Emoji("deaf_man"),
    _Emoji("deaf_woman"),
    _Emoji("bear"),
    _Emoji("broken_heart"),
    _Emoji("cat"),
    _Emoji("dog"),
    _Emoji("fox"),
    _Emoji("gun"),
    _Emoji("face_with_raised_eyebrow"),
    _Emoji("middle_finger"),
    _Emoji("moyai"),
    _Emoji("fire"),
    _Emoji("nerd"),
    _Emoji("radioactive"),
    _Emoji("shocked_face"),
    _Emoji("skull"),
    _Emoji("smiling_imp"),
    _Emoji("speaking_head"),
    _Emoji("sob"),
    _Emoji("eggplant"),
    _Emoji("clown"),

    std::pair("$$newline$$", "$$newline$$"),

    //other
    _Emoji("amogus"),
    _Emoji("bruh"),
    _Emoji("carlos"),
    _Emoji("clueless"),
    _Emoji("despair"),
    _Emoji("despair2"),
    _Emoji("ned"),
    std::pair("pusab?", "pusab.png"_spr),
    _Emoji("robsmile"),
    _Emoji("sip"),
    _Emoji("splat"),
    _Emoji("teehee"),
    _Emoji("trollface"),
    _Emoji("true"),
    _Emoji("walter"),
    _Emoji("wha"),
    _Emoji("whadahell"),
    _Emoji("youshould"),
    _Emoji("car"),
    _Emoji("zoink"),
    _Emoji("shocked"),
    _Emoji("poppinbottles"),
    _Emoji("party"),
    _Emoji("potbor"),
    _Emoji("dabmeup"),
    _Emoji("fireinthehole"),
    _Emoji("finger"),
    _Emoji("soggy"),
    _Emoji("mayo"),
    _Emoji("divine"),
    _Emoji("rattledash"),
    _Emoji("gd"),
    std::pair("geode", "geode-icon.png"_spr),
    _Emoji("boar"),

    // cat collection, thank you c# discord. i wuv you <3
    std::pair("$$newline$$", "$$newline$$"),

    _Emoji("catbless"),
    _Emoji("catcash"),
    _Emoji("catcomf"),
    _Emoji("catcool"),
    _Emoji("catcop"),
    _Emoji("catcorn"),
    _Emoji("catderp"),
    _Emoji("catfacepalm"),
    _Emoji("catfine"),
    _Emoji("catgasm"),
    _Emoji("catgasp"),
    _Emoji("catgift"),
    _Emoji("catgrump"),
    _Emoji("catgun"),
    _Emoji("cathammer"),
    _Emoji("cathi"),
    _Emoji("cathype"),
    _Emoji("catlaugh"),
    _Emoji("catlick"),
    _Emoji("catloser"),
    _Emoji("catlost"),
    _Emoji("catlove"),
    _Emoji("catlul"),
    _Emoji("catlurk"),
    _Emoji("catmusik"),
    _Emoji("catok"),
    _Emoji("catpat"),
    _Emoji("catpls"),
    _Emoji("catpog"),
    _Emoji("catpout"),
    _Emoji("catree"),
    _Emoji("catshrug"),
    _Emoji("catshy"),
    _Emoji("catsimp"),
    _Emoji("catsip"),
    _Emoji("catsleep"),
    _Emoji("catsmart"),
    _Emoji("catsweat"),
    _Emoji("catthinking"),
};

std::vector<std::pair<std::string, std::string>> EmojiNode::getEmojis()
{
    return emojis;
}