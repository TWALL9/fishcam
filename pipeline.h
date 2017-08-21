#include <gstreamer-1.0/gst/gst.h>

#define PRINT_DEBUG

#define ERROR(FMT, ...)  printf("%s:%d:\t%s\terror: " FMT "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
// enable below to print debug information
#ifdef PRINT_DEBUG
#define DEBUG(FMT, ...)  printf("%s:%d:\t%s\tdebug: " FMT "\n", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define DEBUG(FMT, ...)
#endif

class Pipeline{
public:
	Pipeline();
	~Pipeline();
private:
	static void on_pad_added(GstElement *element, GstPad *pad, gpointer *data);
	static gboolean busCall(GstBus *bus, GstMessage *message, gpointer *data);
	GstElement *pipeline;
};