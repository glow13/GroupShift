#include "ShiftPopup.hpp"

class GroupShiftPopup : public ShiftPopup {
public:
    struct ObjectCollection : public CCObject {
		std::vector<GameObject*> data;
		ObjectCollection(std::vector<GameObject*> objs) {
			data = objs;
			this->autorelease();
		}
	};
    void onButtonPress(CCObject* obj) override;
    bool init(FLAlertLayer*);
    static GroupShiftPopup* create(std::vector<GameObject*> objects, FLAlertLayer* popup);
};