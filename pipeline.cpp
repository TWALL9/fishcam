#include <stdlib.h>
#include <iostream>
#include <glib.h>
#include <pthread.h>
#include <gstreamer-1.0/gst/gst.h>

static gboolean Pipeline::busCall(GstBus *bus, GstMessage *message, gpointer *data){
	GMainLoop *loop = (GMainLoop*)data;

	switch(GST_MESSAGE_TYPE(message)){
		case GST_MESSAGE_EOS:
			g_print("end of stream\n");
			g_main_loop_quit(loop);
			break;

		case GST_MESSAGE_ERROR:{
			gchar *debug;
			GError *error;
			gst_message_parse_error(message, &error, &debug);
			g_free(debug);
			ERROR("%s", error->message);
			g_main_loop_quit(loop);
			break;
		}
			
		default:
			break;
	}
	return TRUE;
}

static void on_pad_added(GstElement *element, GstPad *pad, gpointer *data){
	GstPad *sinkpad;
	GstElement *decoder = (GstElement*)data;

	DEBUG("dynamic pad created, linking now");
	sinkpad = gst_element_get_static_pad(decoder, "sink");
	gst_pad_link(pad, sinkpad);
	gst_object_unref(sinkpad);
}

Pipeline::Pipeline():
	pipeline(NULL)
	{
		GstError* error = NULL;
		pipeline = gst_parse_launch("v4l2src device=/dev/video0  ! video/x-raw,width=640,height=480" 
			"! queue ! omxh264enc  ! h264parse ! mp4mux ! tcpserversink host="127.0.0.1" port=8080", &error);
		if(pipeline == NULL){
			ERROR("error creating pipeline %s", error->message);
			g_error_free(error);
			return NULL;
		}

		gst_element_set_state(pipeline, GST_STATE_PLAYING);

	}

Pipeline::~Pipeline(){
	gst_element_set_state(pipeline, GST_STATE_NULL);
	gst_object_unref(pipeline);
}