#ifndef DEVICE_H
#define DEVICE_H

#define VENDOR_ID 0x0925
#define PRODUCT_ID 0x7001

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

#define CTRL_IN        LIBUSB_ENDPOINT_IN|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE
#define CTRL_OUT    LIBUSB_ENDPOINT_OUT|LIBUSB_REQUEST_TYPE_CLASS|LIBUSB_RECIPIENT_INTERFACE


class Device
{

    const static int PACKET_CTRL_LEN=2;
    const static int PACKET_INT_LEN=2;
    const static int INTERFACE=0;
    const static int ENDPOINT_INT_IN=0x81; /* endpoint 0x81 address for IN */
    const static int ENDPOINT_INT_OUT=0x01; /* endpoint 1 address for OUT */
    const static int TIMEOUT=5000; /* timeout in ms */
    static int result = 1;
    static struct libusb_device_handle *devh = NULL;
    static int test_interrupt_transfer();
    static int test_control_transfer_in_out();
    static int test_control_transfer();
    void bad(const char *why);
    static int find_lvr_hidusb();



public:
    Device();
    void init();
    void config();
    void close();
};

#endif // DEVICE_H
