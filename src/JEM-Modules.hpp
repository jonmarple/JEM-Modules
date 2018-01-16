#include "rack.hpp"

using namespace rack;

extern Plugin *plugin;

////////////////////
// module widgets //
////////////////////

struct VCOWidget : ModuleWidget {
	VCOWidget();
};

struct VCAWidget : ModuleWidget {
	VCAWidget();
};

struct TriggerWidget : ModuleWidget {
	TriggerWidget();
};
