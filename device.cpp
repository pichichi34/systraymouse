#include "device.h"
#include <QDebug>
#include <QString>

Device::Device()
{
devh = NULL;
result=1;
init();
}

int Device::find_lvr_hidusb()
{
    devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    return 0;
}

int Device::interrapt_transfer_out()
{
       int r,transferred;
    r=libusb_interrupt_transfer(devh, ENDPOINT_INT_OUT, massage, PACKET_INT_LEN,&transferred,TIMEOUT);
   // r = libusb_control_transfer(devh,CTRL_OUT,HID_SET_REPORT,(HID_REPORT_TYPE_OUTPUT<<8)|0x00, 0,massage, PACKET_INT_LEN,TIMEOUT);
    if (r < 0) {
        qDebug("Control Out error %d\n"+r);
        return r;
    }
    return 0;
}

void Device::init()
{
    result = libusb_init(NULL);
    if (result < 0) {
       qDebug("Failed to initialise libusb\n");
        exit(1);
    }

    result = find_lvr_hidusb();
    if (result < 0) {
       qDebug("Could not find/open LVR Generic HID device\n");
    }else
        qDebug("Successfully find the LVR Generic HID device\n");
}

void Device::config()
{
     libusb_detach_kernel_driver(devh, INTERFACE_NUMBER);

    result = libusb_claim_interface(devh, INTERFACE_NUMBER);
    if (result < 0) {
    qDebug("libusb_claim_interface error");
    }else
    qDebug("Successfully claimed interface");
}

void Device::close()
{
    libusb_release_interface(devh, INTERFACE_NUMBER);
    libusb_close(devh);
    libusb_exit(NULL);
}

void Device::program(int sens,int delay)
{
    massage[0]=sens;
    massage[1]=delay;
    config();
    interrapt_transfer_out();
    close();
}

