#include "pipeline.h"
#include <gstreamer-1.0/gst/gst.h>

int main(int argc, char **argv){
	gst_init(&argv, &argv);
	Pipeline fishcam;
	if(fishcam == NULL){
		ERROR("could not create fishcam\n");
		return -1;
	}
	return 0;
}