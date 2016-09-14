/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    Vamp Test Plugin
    Copyright (c) 2013-2016 Queen Mary, University of London

    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
    CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

    Except as contained in this notice, the names of the Centre for
    Digital Music and Queen Mary, University of London shall not be
    used in advertising or otherwise to promote the sale, use or other
    dealings in this Software without prior written authorization.
*/

#include <vamp/vamp.h>
#include <vamp-sdk/PluginAdapter.h>

#include "VampTestPlugin.h"

class Adapter : public Vamp::PluginAdapterBase
{
public:
    Adapter(bool freq) :
        PluginAdapterBase(),
        m_freq(freq) { }

    virtual ~Adapter() { }

protected:
    bool m_freq;

    Vamp::Plugin *createPlugin(float inputSampleRate) {
        return new VampTestPlugin(inputSampleRate, m_freq);
    }
};

static Adapter timeAdapter(false);
static Adapter freqAdapter(true);

const VampPluginDescriptor *
vampGetPluginDescriptor(unsigned int version, unsigned int index)
{
    if (version < 1) return 0;

    // Return a different plugin adaptor's descriptor for each index,
    // and return 0 for the first index after you run out of plugins.
    // (That's how the host finds out how many plugins are in this
    // library.)

    switch (index) {
    case  0: return timeAdapter.getDescriptor();
    case  1: return freqAdapter.getDescriptor();
    default: return 0;
    }
}


