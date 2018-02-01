#include "JEM-Modules.hpp"

struct VCA : Module {
  enum ParamIds {
  		LEVEL_PARAM,
  		NUM_PARAMS
  	};
  	enum InputIds {
  		EXP_INPUT,
  		IN_INPUT,
  		NUM_INPUTS
  	};
  	enum OutputIds {
  		OUT_OUTPUT,
  		NUM_OUTPUTS
  	};
  	VCA() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {}
  	void step() override;
};

static void stepChannel(Input &in, Param &level, Input &exp, Output &out) {
	float v = in.value * level.value;
	const float expBase = 50.0;
	if(exp.active)
		v *= rescalef(powf(expBase, clampf(exp.value / 10.0, 0.0, 1.0)), 1.0, expBase, 0.0, 1.0);
	out.value = v;
}

void VCA::step() {
	stepChannel(inputs[IN_INPUT], params[LEVEL_PARAM], inputs[EXP_INPUT], outputs[OUT_OUTPUT]);
}

VCAWidget::VCAWidget() {
  VCA *module = new VCA();
  setModule(module);
  box.size = Vec(15*6, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/VCA.svg")));
		addChild(panel);
	}

  addChild(createScrew<ScrewSilver>(Vec(15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));

  addParam(createParam<RoundBlackKnob>(Vec(26, 87), module, VCA::LEVEL_PARAM, 0.0, 1.0, 0.5));

	addInput(createInput<PJ301MPort>(Vec(33, 157), module, VCA::EXP_INPUT));
	addInput(createInput<PJ301MPort>(Vec(33, 216), module, VCA::IN_INPUT));

	addOutput(createOutput<PJ301MPort>(Vec(33, 275), module, VCA::OUT_OUTPUT));
}
