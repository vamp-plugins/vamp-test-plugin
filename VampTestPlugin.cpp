

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

    int n = 0;

    OutputDescriptor d;

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
    m_outputNumbers[d.identifier] = n++;
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
    m_outputNumbers[d.identifier] = n++;
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
    d.sampleRate = 2;
    d.hasDuration = false;
    m_outputNumbers[d.identifier] = n++;
    list.push_back(d);

    d.identifier = "curve-fsr-timed";
    d.name = "Curve: FixedSampleRate/Timed";
    d.description = "A time series with a fixed sample rate (independent of process step size) but with timestamps on features";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::FixedSampleRate;
    d.sampleRate = 2;
    d.hasDuration = false;
    m_outputNumbers[d.identifier] = n++;
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
    m_outputNumbers[d.identifier] = n++;
    list.push_back(d);

    d.identifier = "grid-oss";
    d.name = "Grid: OneSamplePerStep";
    d.description = "A fixed-height grid of values with one column per process block";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 10;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::OneSamplePerStep;
    d.sampleRate = 0;
    d.hasDuration = false;
    m_outputNumbers[d.identifier] = n++;
    list.push_back(d);

    d.identifier = "grid-fsr";
    d.name = "Grid: FixedSampleRate";
    d.description = "A fixed-height grid of values with equally-spaced columns (independent of process step size)";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 10;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::FixedSampleRate;
    d.sampleRate = 2;
    d.hasDuration = false;
    m_outputNumbers[d.identifier] = n++;
    list.push_back(d);

    d.identifier = "notes-regions";
    d.name = "Notes or Regions";
    d.description = "Variably-spaced features with one value and duration";
    d.unit = "";
    d.hasFixedBinCount = true;
    d.binCount = 1;
    d.hasKnownExtents = false;
    d.isQuantized = false;
    d.sampleType = OutputDescriptor::VariableSampleRate;
    d.sampleRate = 0;
    d.hasDuration = true;
    m_outputNumbers[d.identifier] = n++;
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

static Vamp::Plugin::Feature
timedCurveValue(RealTime r, int i, int n)
{
    std::stringstream s;
    Vamp::Plugin::Feature f;
    f.hasTimestamp = true;
    f.timestamp = r;
    f.hasDuration = false;
    float v = float(i) / float(n);
    f.values.push_back(v);
    s << i+1 << " of " << n << ": " << v << " at " << r.toText();
    f.label = s.str();
    return f;
}

static Vamp::Plugin::Feature
snappedCurveValue(RealTime r, RealTime sn, int i, int n)
{
    std::stringstream s;
    Vamp::Plugin::Feature f;
    f.hasTimestamp = true;
    f.timestamp = r;
    f.hasDuration = false;
    float v = float(i) / float(n);
    f.values.push_back(v);
    s << i+1 << " of " << n << ": " << v << " at " << r.toText() << " snap to " << sn.toText();
    f.label = s.str();
    return f;
}

static Vamp::Plugin::Feature
gridColumn(RealTime r, int i, int n)
{
    std::stringstream s;
    Vamp::Plugin::Feature f;
    f.hasTimestamp = false;
    f.hasDuration = false;
    for (int j = 0; j < 10; ++j) {
	float v = float(j + i + 2) / float(n + 10);
	f.values.push_back(v);
    }
    s << i+1 << " of " << n << " at " << r.toText();
    f.label = s.str();
    return f;
}

static Vamp::Plugin::Feature
noteOrRegion(RealTime r, RealTime d, int i, int n)
{
    std::stringstream s;
    Vamp::Plugin::Feature f;
    f.hasTimestamp = true;
    f.timestamp = r;
    f.hasDuration = true;
    f.duration = d;
    float v = float(i) / float(n);
    f.values.push_back(v);
    s << i+1 << " of " << n << ": " << v << " at " << r.toText() << " dur. " << d.toText();
    f.label = s.str();
    return f;
}

static
float snap(float x, float r)
{
    int n = int(x / r + 0.5);
    return n * r;
}

Vamp::Plugin::FeatureSet
VampTestPlugin::featuresFrom(RealTime timestamp, bool final)
{
    FeatureSet fs;

    RealTime endTime = timestamp + RealTime::frame2RealTime
	(m_stepSize, m_inputSampleRate);

    for (int i = 0; i < (int)m_instants.size(); ++i) {

	if (m_instants[i] >= timestamp && (final || m_instants[i] < endTime)) {
	    fs[m_outputNumbers["instants"]]
		.push_back(instant(m_instants[i], i, m_instants.size()));
	}

	RealTime variCurveTime = m_instants[i] / 2;
	if (variCurveTime >= timestamp && (final || variCurveTime < endTime)) {
	    fs[m_outputNumbers["curve-vsr"]]
		.push_back(timedCurveValue(variCurveTime, i, m_instants.size()));
	}

	RealTime noteTime = (m_instants[i] + m_instants[i]) / 3;
	RealTime noteDuration = RealTime::fromSeconds((i % 2 == 0) ? 1.75 : 0.5);

	if (noteTime >= timestamp && (final || noteTime < endTime)) {
	    fs[m_outputNumbers["notes-regions"]]
		.push_back(noteOrRegion(noteTime, noteDuration, i, m_instants.size()));
	}
    }

    if (!final) {

	if (m_n < 20) {
	    fs[m_outputNumbers["curve-oss"]]
		.push_back(untimedCurveValue(timestamp, m_n, 20));
	}

	if (m_n < 5) {
	    fs[m_outputNumbers["curve-fsr"]]
		.push_back(untimedCurveValue(RealTime::fromSeconds(m_n / 2.0), m_n, 10));

	    float s = (m_n / 4) * 2;
	    if ((m_n % 4) > 0) {
		s += float((m_n % 4) - 1) / 6.0;
	    }
	    fs[m_outputNumbers["curve-fsr-timed"]]
		.push_back(snappedCurveValue(RealTime::fromSeconds(s),
					     RealTime::fromSeconds(snap(s, 0.5)),
					     m_n, 10));
	}

	if (m_n < 20) {
	    fs[m_outputNumbers["grid-oss"]]
		.push_back(gridColumn(timestamp, m_n, 20));
	}

    } else {

	for (int i = (m_n > 5 ? 5 : m_n); i < 10; ++i) {
	    fs[m_outputNumbers["curve-fsr"]]
		.push_back(untimedCurveValue(RealTime::fromSeconds(i / 2.0), i, 10));

	    float s = (i / 4) * 2;
	    if ((i % 4) > 0) {
		s += float((i % 4) - 1) / 6.0;
	    }
	    fs[m_outputNumbers["curve-fsr-timed"]]
		.push_back(snappedCurveValue(RealTime::fromSeconds(s),
					     RealTime::fromSeconds(snap(s, 0.5)),
					     i, 10));
	}

	for (int i = (m_n > 5 ? 5 : m_n); i < 10; ++i) {
	    fs[m_outputNumbers["grid-fsr"]]
		.push_back(gridColumn(RealTime::fromSeconds(i / 2.0), i, 10));
	}
    }

    m_lastTime = endTime;
    m_n = m_n + 1;
    return fs;
}    

VampTestPlugin::FeatureSet
VampTestPlugin::process(const float *const *inputBuffers, RealTime timestamp)
{
    FeatureSet fs = featuresFrom(timestamp, false);
    return fs;
}

VampTestPlugin::FeatureSet
VampTestPlugin::getRemainingFeatures()
{
    FeatureSet fs = featuresFrom(m_lastTime, true);
    return fs;
}

