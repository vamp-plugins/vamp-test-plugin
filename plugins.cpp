

#include <vamp/vamp.h>
#include <vamp-sdk/PluginAdapter.h>

#include "VampTestPlugin.h"


static Vamp::PluginAdapter<VampTestPlugin> myPluginAdapter;


const VampPluginDescriptor *
vampGetPluginDescriptor(unsigned int version, unsigned int index)
{
    if (version < 1) return 0;

    // Return a different plugin adaptor's descriptor for each index,
    // and return 0 for the first index after you run out of plugins.
    // (That's how the host finds out how many plugins are in this
    // library.)

    switch (index) {
    case  0: return myPluginAdapter.getDescriptor();
    default: return 0;
    }
}


