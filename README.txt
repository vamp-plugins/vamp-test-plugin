
Vamp Test Plugin
================

This is a test plugin for use by developers who are working on host
applications for Vamp plugins.

Its primary purpose is to help you test that your host is correctly
handling the output sample type and sample rate, as these are quite
easily misinterpreted. (See http://vamp-plugins.org/ for more about
Vamp plugins and http://vapm-plugins.org/guide.pdf for the programming
guide which explains the output sample type and sample rate.)

The plugin does no real work. It simply provides a variety of outputs
with different output descriptors, and returns some test values. See
https://code.soundsoftware.ac.uk/projects/vamp-test-plugin/wiki/Wiki
for documentation of the outputs and features returned.

If you are developing plugins rather than hosts, and you want help in
testing them, look instead at the Vamp Plugin Tester
(https://code.soundsoftware.ac.uk/projects/vamp-plugin-tester).
