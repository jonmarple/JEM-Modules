#include "JEM-Modules.hpp"

Plugin *plugin;

void init(rack::Plugin *p) {
	plugin = p;
	p->slug = "JEM-Modules";
	p->version = TOSTRING(VERSION);
	p->website = "https://github.com/jonmarple";

	p->addModel(createModel<VCOWidget>("JEM-Modules", "VCO", "VCO-1", OSCILLATOR_TAG));
	p->addModel(createModel<VCAWidget>("JEM-Modules", "VCA", "VCA-1", AMPLIFIER_TAG));
	p->addModel(createModel<TriggerWidget>("JEM-Modules", "Trigger", "Launch", CONTROLLER_TAG));

}
