#include "JEM-Modules.hpp"

Plugin *plugin;

void init( rack::Plugin *p )
{
	plugin = p;
	p->slug = "JEM-Modules";
	p->version = TOSTRING( VERSION );
	p->website = "https://github.com/jonmarple/JEM-Modules";

	p->addModel( createModel<VCOWidget>( "JEM-Modules", "VCO", "VCO", OSCILLATOR_TAG ) );
	p->addModel( createModel<VCAWidget>( "JEM-Modules", "VCA", "VCA", AMPLIFIER_TAG ) );
	p->addModel( createModel<TriggerWidget>( "JEM-Modules", "Trigger", "Launch", CONTROLLER_TAG ) );
  p->addModel( createModel<EnvelopeWidget>( "JEM-Modules", "Envelope", "ADSR", ENVELOPE_GENERATOR_TAG ) );
  p->addModel( createModel<SequencerWidget>( "JEM-Modules", "Sequencer", "RUN", SEQUENCER_TAG ) );

}
