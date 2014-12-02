
#ifndef _VAMP_TEST_PLUGIN_H_
#define _VAMP_TEST_PLUGIN_H_

#include <vamp-sdk/Plugin.h>

using std::string;


class VampTestPlugin : public Vamp::Plugin
{
public:
    VampTestPlugin(float inputSampleRate);
    virtual ~VampTestPlugin();

    string getIdentifier() const;
    string getName() const;
    string getDescription() const;
    string getMaker() const;
    int getPluginVersion() const;
    string getCopyright() const;

    InputDomain getInputDomain() const;
    size_t getPreferredBlockSize() const;
    size_t getPreferredStepSize() const;
    size_t getMinChannelCount() const;
    size_t getMaxChannelCount() const;

    ParameterList getParameterDescriptors() const;
    float getParameter(string identifier) const;
    void setParameter(string identifier, float value);

    ProgramList getPrograms() const;
    string getCurrentProgram() const;
    void selectProgram(string name);

    OutputList getOutputDescriptors() const;

    bool initialise(size_t channels, size_t stepSize, size_t blockSize);
    void reset();

    FeatureSet process(const float *const *inputBuffers,
                       Vamp::RealTime timestamp);

    FeatureSet getRemainingFeatures();

protected:
    bool m_produceOutput;
    int m_n;
    std::vector<Vamp::RealTime> m_instants;
    int m_channels;
    int m_stepSize;
    int m_blockSize;
    Vamp::RealTime m_lastTime;
    mutable std::map<std::string, int> m_outputNumbers;

    FeatureSet featuresFrom(Vamp::RealTime, bool);
};



#endif
