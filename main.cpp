#include <gst/gst.h>

int main(int argc, char *argv[])
{
    GstElement *pipeline, *bin;
    GstElement *source, *filter, *sink;

    // init gstreamer
    gst_init(&argc, &argv);

    // create pipeline
    pipeline = gst_pipeline_new("my-pipeline");

    // create bin
    bin = gst_bin_new("mi-bin");

    // create elements
    source = gst_element_factory_make("fakesrc", "source");
    filter = gst_element_factory_make("identity", "filter");
    sink = gst_element_factory_make("fakesink", "sink");

    // add elements to bin
    gst_bin_add_many(GST_BIN(bin), source, filter, sink, NULL);

    // add bin to pipeline
    gst_bin_add(GST_BIN(pipeline), bin);

    // link
    if (!gst_element_link_many(source, filter, sink, NULL)) {
        g_warning("Failed to link elements");
    }

    // only need to unref pipeline, children will release, too.
    gst_object_unref (GST_OBJECT(pipeline));
    return 0;
}
