#include "ShiftPopup.hpp"

class GroupShiftPopup : public ShiftPopup {
public:
    struct ObjectCollection : public CCObject {
		vector<GameObject*> data;
		ObjectCollection(vector<GameObject*> objs) {
			data = objs;
			this->autorelease();
		}
	};
    void onButtonPress(CCObject* obj) override;
    bool setup() override;
    static GroupShiftPopup* create(vector<GameObject*> objects);
};