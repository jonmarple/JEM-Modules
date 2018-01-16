#include "JEM-Modules.hpp"

struct Trigger : Module {
  enum ParamIds {
    LAUNCH_PARAM,
    LOCK_PARAM,
    NUM_PARAMS
  };
  enum InputIds {
    NUM_INPUTS
  };
  enum OutputIds {
    OUT1_OUTPUT,
    OUT2_OUTPUT,
    OUT3_OUTPUT,
    OUT4_OUTPUT,
    NUM_OUTPUTS
  };

  bool gateOn, launchReleased;

  Trigger() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS) {
    reset();
  }
  void step() override;
  void reset() override {
    gateOn = false;
    launchReleased = true;
    for (int i = 0; i < NUM_OUTPUTS; i++) {
      outputs[i].value = 0.0;
    }
  }
};

void Trigger::step() {
  if (params[LOCK_PARAM].value == 0) {
    if (params[LAUNCH_PARAM].value > 0 && gateOn == false && launchReleased == true) {
      gateOn = true;
      launchReleased = false;
      for (int i = 0; i < NUM_OUTPUTS; i++) {
        outputs[i].value = 1.0;
      }
    }
    else if (params[LAUNCH_PARAM].value > 0 && gateOn == true && launchReleased == true) {
      gateOn = false;
      launchReleased = false;
      for (int i = 0; i < NUM_OUTPUTS; i++) {
        outputs[i].value = 0.0;
      }
    }
    if (params[LAUNCH_PARAM].value == 0){
        launchReleased = true;
    }
  }
  else {
    gateOn = false;
    launchReleased = true;
    for (int i = 0; i < NUM_OUTPUTS; i++) {
      outputs[i].value = params[LAUNCH_PARAM].value;
    }
  }
}

TriggerWidget::TriggerWidget() {
  Trigger *module = new Trigger();
  setModule(module);
  box.size = Vec(15*6, 380);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Trigger.svg")));
		addChild(panel);
	}

  addChild(createScrew<ScrewSilver>(Vec(15, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 0)));
	addChild(createScrew<ScrewSilver>(Vec(15, 365)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x-30, 365)));

  addParam(createParam<LEDButton>(Vec(45, 100), module, Trigger::LAUNCH_PARAM, 0.0, 1.0, 0.0));
  addParam(createParam<CKSS>(Vec(20, 100), module, Trigger::LOCK_PARAM, 0.0, 1.0, 1.0));

	addOutput(createOutput<PJ301MPort>(Vec(40, 160), module, Trigger::OUT1_OUTPUT));
  addOutput(createOutput<PJ301MPort>(Vec(40, 200), module, Trigger::OUT2_OUTPUT));
  addOutput(createOutput<PJ301MPort>(Vec(40, 240), module, Trigger::OUT3_OUTPUT));
  addOutput(createOutput<PJ301MPort>(Vec(40, 280), module, Trigger::OUT4_OUTPUT));
}
