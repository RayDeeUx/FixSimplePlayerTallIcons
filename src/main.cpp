#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;
namespace perms = geode::utils::permission;

class $modify(MyMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) return false;
		log::info("dankmeme01 custom test mod");
		bool state = perms::getPermissionStatus(perms::Permission::RecordAudio);
		log::debug("Initial state: {}", state);
		perms::requestPermission(perms::Permission::RecordAudio, [](bool granted) {
			log::debug("Was granted: {}", granted);
		});
		return true;
	}
};