#include "JEM-Modules.hpp"
#include "dsp/digital.hpp"

struct Envelope : Module {
  enum ParamIds {
    ATTACK_PARAM,
    DECAY_PARAM,
    SUSTAIN_PARAM,
    RELEASE_PARAM,
    NUM_PARAMS
  };
  enum InputIds {
    GATE_INPUT,
    NUM_INPUTS
  };
  enum OutputIds {
    ENVELOPE_OUTPUT,
    NUM_OUTPUTS
  };
  enum LightIds {
    ATTACK_LIGHT,
    DECAY_LIGHT,
    SUSTAIN_LIGHT,
    RELEASE_LIGHT,
    NUM_LIGHTS
  };
  float envelope = 0.0;
  bool decaying = false;
  SchmittTrigger trigger;

  Envelope() : Module(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS) {
    trigger.setThresholds(0.0, 1.0);
  }
  void step() override;
};

void Envelope::step() {
  // Parameter levels
	float attack = clampf(params[ATTACK_PARAM].value, 0.0, 1.0);
	float decay = clampf(params[DECAY_PARAM].value, 0.0, 1.0);
	float sustain = clampf(params[SUSTAIN_PARAM].value, 0.0, 1.0);
	float release = clampf(params[RELEASE_PARAM].value, 0.0, 1.0);

  bool gated = inputs[GATE_INPUT].value >= 1.0;

  const float base = 20000.0;
  const float maxTime = 10.0;

  if(gated) {
    if(decaying) {
      if(decay < 1e-4) {
        envelope = sustain;
      }
      else {
        envelope += powf(base, 1 - decay) / maxTime * (sustain - envelope) / engineGetSampleRate();
      }
    }
    else {
      if(attack < 1e-4) {
				envelope = 1.0;
			}
			else {
				envelope += powf(base, 1 - attack) / maxTime * (1.01 - envelope) / engineGetSampleRate();
			}
			if(envelope >= 1.0) {
				envelope = 1.0;
				decaying = true;
			}
    }
  }
  else {
    if(release <  1e-4) {
      envelope = 0.0;
    }
    else {
      envelope += powf(base, 1 - release) / maxTime * (0.0 - envelope) / engineGetSampleRate();
    }
    decaying = false;
  }

  bool sustaining = nearf(envelope, sustain, 1e-3);
  bool resting = nearf(envelope, 0.0, 1e-3);

  outputs[ENVELOPE_OUTPUT].value = 10.0 * envelope;

  lights[ATTACK_LIGHT].value = (gated && !decaying) ? 1.0 : 0.0;
	lights[DECAY_LIGHT].value = (gated && decaying && !sustaining) ? 1.0 : 0.0;
	lights[SUSTAIN_LIGHT].value = (gated && decaying && sustaining) ? 1.0 : 0.0;
	lights[RELEASE_LIGHT].value = (!gated && !resting) ? 1.0 : 0.0;
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

  addInput(createInput<PJ301MPort>(Vec(11, 320), module, Envelope::GATE_INPUT));

  addOutput(createOutput<PJ301MPort>(Vec(55, 320), module, Envelope::ENVELOPE_OUTPUT));

	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 67), module, Envelope::ATTACK_LIGHT));
	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 127), module, Envelope::DECAY_LIGHT));
	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 187), module, Envelope::SUSTAIN_LIGHT));
	addChild(createLight<SmallLight<BlueLight>>(Vec(45, 247), module, Envelope::RELEASE_LIGHT));

}
