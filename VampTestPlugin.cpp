

#include "VampTestPlugin.h"

#include <sstream>

using std::stringstream;

using Vamp::RealTime;

VampTestPlugin::VampTestPlugin(float inputSampleRate) :
    Plugin(inputSampleRate),
    m_n(0),
    m_stepSize(0),
    m_blockSize(0)
{
    for (int i = 0; i < 10; ++i) {
	m_instants.push_back(RealTime::fromSeconds(1.5 * i));
    }
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

    // 0 -> instants
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

    // 1 -> curve-oss
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

    // 2 -> curve-fsr
    d.identifier = "curve-fsr";
    d.name = "Curve: FixedSampleRate";
    d.description = "A time series with equally-spaced values (independent of process step size)";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::FixedSampleRate;
    d.sampleRate = 2;
    d.hasDuration = false;
    list.push_back(d);

    // 3 -> curve-vsr
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

    // 4 -> grid-oss
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

    // 5 -> grid-fsr
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

    m_stepSize = stepSize;
    m_blockSize = blockSize;

    return true;
}

void
VampTestPlugin::reset()
{
    m_n = 0;
}

static Vamp::Plugin::Feature
instant(RealTime r, int i, int n)
{
    std::stringstream s;
    Vamp::Plugin::Feature f;
    f.hasTimestamp = true;
    f.timestamp = r;
    f.hasDuration = false;
    s << i+1 << " of " << n << " at " << r.toText();
    f.label = s.str();
    return f;
}

static Vamp::Plugin::Feature
untimedCurveValue(RealTime r, int i, int n)
{
    std::stringstream s;
    Vamp::Plugin::Feature f;
    f.hasTimestamp = false;
    f.hasDuration = false;
    float v = float(i) / float(n);
    f.values.push_back(v);
    s << i+1 << " of " << n << ": " << v << " at " << r.toText();
    f.label = s.str();
    return f;
}

VampTestPlugin::FeatureSet
VampTestPlugin::process(const float *const *inputBuffers, RealTime timestamp)
{
    FeatureSet fs;

    RealTime endTime = timestamp + RealTime::frame2RealTime
	(m_stepSize, m_inputSampleRate);

    for (int i = 0; i < (int)m_instants.size(); ++i) {
	if (m_instants[i] >= timestamp && m_instants[i] < endTime) {
	    // instants output
	    fs[0].push_back(instant(m_instants[i], i, m_instants.size()));
	}
    }

    if (m_n < 20) {
	// curve-oss output
	fs[1].push_back(untimedCurveValue(timestamp, m_n, 20));
    }

    if (m_n < 5) {
        // curve-fsr output
        fs[2].push_back(untimedCurveValue(RealTime::fromSeconds(m_n / 2.0), m_n, 10));
    }

    m_lastTime = endTime;
    m_n = m_n + 1;
    return fs;
}

VampTestPlugin::FeatureSet
VampTestPlugin::getRemainingFeatures()
{
    FeatureSet fs;

    for (int i = 0; i < (int)m_instants.size(); ++i) {
	if (m_instants[i] >= m_lastTime) {
	    fs[0].push_back(instant(m_instants[i], i, m_instants.size()));
	}
    }

    for (int i = (m_n > 5 ? 5 : m_n); i < 10; ++i) {
        // curve-fsr output
        fs[2].push_back(untimedCurveValue(RealTime::fromSeconds(i / 2.0), i, 10));
    }

    return fs;
}

