

#include "VampTestPlugin.h"


VampTestPlugin::VampTestPlugin(float inputSampleRate) :
    Plugin(inputSampleRate)
    // Also be sure to set your plugin parameters (presumably stored
    // in member variables) to their default values here -- the host
    // will not do that for you
{
}

VampTestPlugin::~VampTestPlugin()
{
}

string
VampTestPlugin::getIdentifier() const
{
    return "vamp-test-plugin";
}

string
VampTestPlugin::getName() const
{
    return "Vamp Test Plugin";
}

string
VampTestPlugin::getDescription() const
{
    return "Test plugin for hosts handling various output types";
}

string
VampTestPlugin::getMaker() const
{
    return "Chris Cannam";
}

int
VampTestPlugin::getPluginVersion() const
{
    return 1;
}

string
VampTestPlugin::getCopyright() const
{
    return "BSD";
}

VampTestPlugin::InputDomain
VampTestPlugin::getInputDomain() const
{
    return TimeDomain;
}

size_t
VampTestPlugin::getPreferredBlockSize() const
{
    return 0;
}

size_t 
VampTestPlugin::getPreferredStepSize() const
{
    return 0;
}

size_t
VampTestPlugin::getMinChannelCount() const
{
    return 1;
}

size_t
VampTestPlugin::getMaxChannelCount() const
{
    return 1;
}

VampTestPlugin::ParameterList
VampTestPlugin::getParameterDescriptors() const
{
    ParameterList list;
    return list;
}

float
VampTestPlugin::getParameter(string identifier) const
{
    return 0;
}

void
VampTestPlugin::setParameter(string identifier, float value) 
{
}

VampTestPlugin::ProgramList
VampTestPlugin::getPrograms() const
{
    ProgramList list;
    return list;
}

string
VampTestPlugin::getCurrentProgram() const
{
    return ""; // no programs
}

void
VampTestPlugin::selectProgram(string name)
{
}

VampTestPlugin::OutputList
VampTestPlugin::getOutputDescriptors() const
{
    OutputList list;

    OutputDescriptor d;

    //!!! review these: extents, units etc

    d.identifier = "instants";
    d.name = "Instants";
    d.description = "Single time points without values";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 0;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::VariableSampleRate;
    d.hasDuration = false;
    list.push_back(d);

    d.identifier = "curve-oss";
    d.name = "Curve: OneSamplePerStep";
    d.description = "A time series with one value per process block";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::OneSamplePerStep;
    d.hasDuration = false;
    list.push_back(d);

    d.identifier = "curve-fsr";
    d.name = "Curve: FixedSampleRate";
    d.description = "A time series with equally-spaced values (independent of process step size)";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::FixedSampleRate;
    d.sampleRate = 2; //!!!
    d.hasDuration = false;
    list.push_back(d);

    d.identifier = "curve-vsr";
    d.name = "Curve: VariableSampleRate";
    d.description = "A variably-spaced series of values";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::VariableSampleRate;
    d.sampleRate = 0;
    d.hasDuration = false;
    list.push_back(d);

    d.identifier = "grid-oss";
    d.name = "Grid: OneSamplePerStep";
    d.description = "A fixed-height grid of values with one column per process block";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::VariableSampleRate;
    d.sampleRate = 0;
    d.hasDuration = false;
    list.push_back(d);

    d.identifier = "grid-fsr";
    d.name = "Grid: FixedSampleRate";
    d.description = "A fixed-height grid of values with equally-spaced columns (independent of process step size)";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::VariableSampleRate;
    d.sampleRate = 0;
    d.hasDuration = false;
    list.push_back(d);


    return list;
}

bool
VampTestPlugin::initialise(size_t channels, size_t stepSize, size_t blockSize)
{
    if (channels < getMinChannelCount() ||
	channels > getMaxChannelCount()) return false;

    // Real initialisation work goes here!

    return true;
}

void
VampTestPlugin::reset()
{
    // Clear buffers, reset stored values, etc
}

VampTestPlugin::FeatureSet
VampTestPlugin::process(const float *const *inputBuffers, Vamp::RealTime timestamp)
{
    // Do actual work!
    return FeatureSet();
}

VampTestPlugin::FeatureSet
VampTestPlugin::getRemainingFeatures()
{
    return FeatureSet();
}

