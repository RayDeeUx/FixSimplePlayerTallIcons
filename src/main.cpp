#include <Geode/modify/GJItemIcon.hpp>

using namespace geode::prelude;

bool enabled = true;
bool moreIconsOnly = true;

$on_mod(Loaded) {
	enabled = Mod::get()->getSettingValue<bool>("enabled");
	listenForSettingChanges<bool>("enabled", [](bool enabledNew) {
		enabled = enabledNew;
	});
	moreIconsOnly = Mod::get()->getSettingValue<bool>("moreIconsOnly");
	listenForSettingChanges<bool>("moreIconsOnly", [](bool moreIconsOnlyNew) {
		moreIconsOnly = moreIconsOnlyNew;
	});
}

using namespace geode::prelude;

class $modify(MyGJItemIcon, GJItemIcon) {
	struct Fields {
		UnlockType unlockType = UnlockType::Cube;
	};
	void scaleGracefully(float dt) {
		if (!enabled) return;
		if (!m_player) return;
		const bool isNotFromMoreIcons = !this->getParent() || !this->getParent()->getUserObject("hiimjustin000.more_icons/name");
		if (moreIconsOnly && isNotFromMoreIcons) return;
		auto simplePlayerChildSprite = m_player->getChildByType<CCSprite>(0);
		if (!simplePlayerChildSprite || simplePlayerChildSprite->getChildrenCount() < 4) return;
		const float originalScale = this->scaleForType(m_fields->unlockType);
		float futureScale = originalScale;
		if (this->getContentHeight() > simplePlayerChildSprite->getContentHeight()) {
			futureScale = simplePlayerChildSprite->getContentHeight() / this->getContentHeight();
		} else if (this->getContentHeight() < simplePlayerChildSprite->getContentHeight()) {
			futureScale = this->getContentHeight() / simplePlayerChildSprite->getContentHeight();
		}
		if (originalScale == futureScale) {
			if (this->getContentWidth() > simplePlayerChildSprite->getContentWidth()) {
				futureScale = simplePlayerChildSprite->getContentWidth() / this->getContentWidth();
			} else if (this->getContentWidth() < simplePlayerChildSprite->getContentWidth()) {
				futureScale = this->getContentWidth() / simplePlayerChildSprite->getContentWidth();
			}
		}
		if ((originalScale * futureScale) < originalScale) {
			if (isNotFromMoreIcons) this->setScale(futureScale);
			else this->setScale(originalScale * futureScale);
		}
	}
	bool init(UnlockType p0, int p1, cocos2d::ccColor3B p2, cocos2d::ccColor3B p3, bool p4, bool p5, bool p6, cocos2d::ccColor3B p7) {
		if (!GJItemIcon::init(p0, p1, p2, p3, p4, p5, p6, p7)) return false;
		m_fields->unlockType = p0;
		this->scheduleOnce(schedule_selector(MyGJItemIcon::scaleGracefully), .001f);
		return true;
	}
};