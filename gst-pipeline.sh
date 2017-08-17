gst-launch-1.0 v4l2src device=/dev/video0 ! videoconvert ! videoscale ! video/x-raw, width=1280, height=720 ! theoraenc ! oggmux ! tcpserversink host=127.0.0.1 port=8080
