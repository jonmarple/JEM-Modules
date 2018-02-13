#include "JEM-Modules.hpp"

struct Sequencer : Module
{
  enum ParamIds
  {
    NUM_PARAMS
  };
  enum InputIds
  {
    NUM_INPUTS
  };
  enum OutputIds
  {
    NUM_OUTPUTS
  };
  enum LightIds
  {
    NUM_LIGHTS
  };

  Sequencer() : Module( NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS ) {}
  void step() override;
};

void Sequencer::step()
{

}

SequencerWidget::SequencerWidget()
{
  Sequencer *module = new Sequencer();
  setModule( module );
  box.size = Vec( 24 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT );

  {
		SVGPanel *panel = new SVGPanel();
		panel->box.size = box.size;
		panel->setBackground( SVG::load( assetPlugin( plugin, "res/Sequencer.svg" ) ) );
		addChild( panel );
	}

	addChild( createScrew<ScrewSilver>( Vec( RACK_GRID_WIDTH, 0 ) ) );
	addChild( createScrew<ScrewSilver>( Vec( box.size.x - 2 * RACK_GRID_WIDTH, 0 ) ) );
	addChild( createScrew<ScrewSilver>( Vec( RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH ) ) );
	addChild( createScrew<ScrewSilver>( Vec( box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH ) ) );

}
