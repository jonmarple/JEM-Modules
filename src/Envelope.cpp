#include "JEM-Modules.hpp"

struct Envelope : Module {
  enum ParamIds {
    ATTACK_PARAM,
    DECAY_PARAM,
    SUSTAIN_PARAM,
    RELEASE_PARAM,
    NUM_PARAMS
  };
  enum InputIds {
    IN_INPUT,
    TRIGGER_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    OUT_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds {
    ATTACK_LIGHT,
    DECAY_LIGHT,
    SUSTAIN_LIGHT,
    RELEASE_LIGHT,
    NUM_LIGHTS
  };
  Envelope() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {}
  void step() override;
};

void Envelope::step() {

  lights[ATTACK_LIGHT].value = 1.0;
  lights[DECAY_LIGHT].value = 1.0;
  lights[SUSTAIN_LIGHT].value = 1.0;
  lights[RELEASE_LIGHT].value = 1.0;

}

EnvelopeWidget::EnvelopeWidget() {
	Envelope *module = new Envelope();
	setModule(module);
	box.size = Vec(6 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT);

	{
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground(SVG::load(assetPlugin(plugin, "res/Envelope.svg")));
		addChild(panel);
	}

	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
	addChild(createScrew<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
	addChild(createScrew<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

	addParam(createParam<RoundBlackKnob>(Vec(10, 75), module, Envelope::ATTACK_PARAM, -3.0, 3.0, 0.0));
	addParam(createParam<RoundBlackKnob>(Vec(10, 135), module, Envelope::DECAY_PARAM, -3.0, 3.0, 0.0));
	addParam(createParam<RoundBlackKnob>(Vec(10, 195), module, Envelope::SUSTAIN_PARAM, -3.0, 3.0, 0.0));
	addParam(createParam<RoundBlackKnob>(Vec(10, 255), module, Envelope::RELEASE_PARAM, -3.0, 3.0, 0.0));

	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 67), module, Envelope::ATTACK_LIGHT));
	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 127), module, Envelope::DECAY_LIGHT));
	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 187), module, Envelope::SUSTAIN_LIGHT));
	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 247), module, Envelope::RELEASE_LIGHT));

}
