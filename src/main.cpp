#include <Geode/modify/GJItemIcon.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

bool calledAlready = false;
bool moreIcons = false;

class $modify(MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;

		if (calledAlready) return true;
		calledAlready = true;
		moreIcons = Loader::get()->isModLoaded("hiimjustin000.more_icons");

		return true;
	}
};

class $modify(MyGJItemIcon, GJItemIcon) {
	struct Fields {
		UnlockType unlockType = UnlockType::Cube;
	};
	void scaleGracefully(float dt) {
		if (!moreIcons) return;
		if (!m_player) return;
		if (!this->getParent() || !this->getParent()->getUserObject("hiimjustin000.more_icons/name")) return;
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
		if (futureScale < originalScale) this->setScale(originalScale * futureScale);
	}
	bool init(UnlockType p0, int p1, cocos2d::ccColor3B p2, cocos2d::ccColor3B p3, bool p4, bool p5, bool p6, cocos2d::ccColor3B p7) {
		if (!GJItemIcon::init(p0, p1, p2, p3, p4, p5, p6, p7)) return false;
		if (!moreIcons) return true;
		m_fields->unlockType = p0;
		this->scheduleOnce(schedule_selector(MyGJItemIcon::scaleGracefully), .009f);
		return true;
	}
};