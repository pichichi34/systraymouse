#ifndef DEVICE_H
#define DEVICE_H

#include <libusb-1.0/libusb.h>

#define VENDOR_ID 0x0483
#define PRODUCT_ID 0x5758

// HID Class-Specific Requests values. See section 7.2 of the HID specifications
#define HID_GET_REPORT                0x01
#define HID_GET_IDLE                  0x02
#define HID_GET_PROTOCOL              0x03
#define HID_SET_REPORT                0x09
#define HID_SET_IDLE                  0x0A
#define HID_SET_PROTOCOL              0x0B
#define HID_REPORT_TYPE_INPUT         0x01
#define HID_REPORT_TYPE_OUTPUT        0x02
#define HID_REPORT_TYPE_FEATURE       0x03

//#define CTRL_IN        LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE
#define CTRL_OUT    LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE

class Device
{
    const static int INTERFACE_NUMBER = 0;
    const static int PACKET_CTRL_LEN=2;
    const static int PACKET_INT_LEN=2;
    const static int INTERFACE=0;
    const static int ENDPOINT_INT_OUT=0x01; /* endpoint 1 address for OUT */
    const static int TIMEOUT=1000; /* timeout in ms */
    int result;
    struct libusb_device_handle *devh;
    unsigned char massage[PACKET_INT_LEN];
    int interrapt_transfer_out();
    int find_lvr_hidusb();
    void config();
    void close();
    void init();

public:
    Device();
    void program(int,int);
};

#endif // DEVICE_H

