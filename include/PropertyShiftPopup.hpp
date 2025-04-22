#include "ShiftPopup.hpp"

class PropertyShiftPopup : public ShiftPopup {
public:
    struct ObjectCollection : public CCObject {
		vector<EffectGameObject*> data;
		ObjectCollection(vector<EffectGameObject*> objs) {
			data = objs;
			this->autorelease();
		}
	};
	int minValue;
	int maxValue;
	function<vector<float>(EffectGameObject*)> getProperty;
    function<void(EffectGameObject*, vector<float>)> setProperty;
	void onButtonPress(CCObject* obj) override;
	bool setup() override;
	static PropertyShiftPopup* create(
		vector<EffectGameObject*> objects,
		function<vector<float>(EffectGameObject*)> getProperty,
		function<void(EffectGameObject*, vector<float>)> setProperty,
		int minValue, int maxValue
	);
	static PropertyShiftPopup* create(
		vector<EffectGameObject*> objects,
		function<vector<float>(EffectGameObject*)> getProperty,
		function<void(EffectGameObject*, vector<float>)> setProperty
	) { return create(objects, getProperty, setProperty, 1, 9999); }
};