/*
 * gst-launch-1.0  filesrc location=jellyfish-3-mbps-hd-h264.mkv ! matroskademux ! h264parse ! vtdec ! autovideosink
 */

#include <gst/gst.h>
#include <glib.h>

static void on_pad_added(GstElement *element, GstPad *pad, gpointer data)
{
    GstPad *sinkpad;
    GstElement *queue = (GstElement *)data;
    g_print("Dynamic pad created, linking demuxer/queue\n");
    sinkpad = gst_element_get_static_pad(queue, "sink");
    gst_pad_link(pad, sinkpad);
    gst_object_unref(sinkpad);
}

int main(int argc, char *argv[])
{
    GMainLoop *loop;
    GstElement *pipeline, *source, *demux, *h264_queue, *parser, *decoder, *raw_queue, *sink;
    GstBus *bus;

    gst_init(&argc, &argv);
    loop = g_main_loop_new(NULL, FALSE);

    if (argc != 2) {
        g_printerr("Usage: %s <H264 video filename>\n", argv[0]);
        return -1;
    }

    pipeline = gst_pipeline_new("h264-player");
    source = gst_element_factory_make("filesrc", "file-source");
    demux = gst_element_factory_make("matroskademux", "demuxer");
    h264_queue = gst_element_factory_make("queue", "hqueue");
    parser = gst_element_factory_make("h264parse", "hparser");
    decoder = gst_element_factory_make("vtdec", "vdecoder");
    raw_queue = gst_element_factory_make("queue", "rqueue");
    sink = gst_element_factory_make("autovideosink", "vsink");

    if (!pipeline || !source || !demux || !h264_queue || !parser || !decoder || !raw_queue || !sink) {
        g_printerr("One element could not be created. Exiting....\n");
        return -1;
    }

    g_object_set(G_OBJECT(source), "location", argv[1]);
    gst_bin_add_many(GST_BIN(pipeline),
            source, demux, h264_queue, parser, decoder, raw_queue, sink, NULL);
    // dont link demux and queue, because demux's output with various meta, need use pad to activate
    gst_element_link_many(source, demux, NULL);
    gst_element_link_many(h264_queue, parser, decoder, raw_queue, sink, NULL);
    g_signal_connect(demux, "pad-added", G_CALLBACK(on_pad_added), h264_queue);
    g_printerr("Now playing %s\n", argv[1]);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
    g_main_loop_run(loop);

    g_printerr("Done, stopping playback\n");
    gst_element_set_state(pipeline, GST_STATE_NULL);

    gst_object_unref(GST_OBJECT(pipeline));
    g_main_loop_unref(loop);
    return 0;
}
