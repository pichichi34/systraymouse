#include "device.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <libusb-1.0/libusb.h>
#include <QDebug>

Device::Device()
{

}

void Device::bad(const char *why) {
    fprintf(stderr,"Fatal error> %s\n",why);
    exit(17);
}


static int Device::find_lvr_hidusb()
{
    devh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
    return devh ? 0 : -EIO;
}


static int Device::test_control_transfer()
{
       int r,i;
       char answer[PACKET_CTRL_LEN];
       char question[PACKET_CTRL_LEN];
       for (i=0;i<PACKET_CTRL_LEN; i++) question[i]=0x20+i;

    r = libusb_control_transfer(devh,CTRL_OUT,HID_SET_REPORT,(HID_REPORT_TYPE_FEATURE<<8)|0x00, 0,question, PACKET_CTRL_LEN,TIMEOUT);
    if (r < 0) {
        fprintf(stderr, "Control Out error %d\n", r);
        return r;
    }
    r = libusb_control_transfer(devh,CTRL_IN,HID_GET_REPORT,(HID_REPORT_TYPE_FEATURE<<8)|0x00,0, answer,PACKET_CTRL_LEN, TIMEOUT);
    if (r < 0) {
        fprintf(stderr, "Control IN error %d\n", r);
        return r;
    }
    for(i = 0;i < PACKET_CTRL_LEN; i++) {
        if(i%8 == 0)
            printf("\n");
        printf("%02x, %02x; ",question[i],answer[i]);
    }
    printf("\n");

    return 0;
}

static int Device::test_control_transfer_in_out()
{
       int r,i;
       char answer[PACKET_INT_LEN];
       char question[PACKET_INT_LEN];
       for (i=0;i<PACKET_INT_LEN; i++) question[i]=0x30+i;
       for (i=1;i<PACKET_INT_LEN; i++) answer[i]=0;

    r = libusb_control_transfer(devh,CTRL_OUT,HID_SET_REPORT,(HID_REPORT_TYPE_OUTPUT<<8)|0x00, 0,question, PACKET_INT_LEN,TIMEOUT);
    if (r < 0) {
        fprintf(stderr, "Control Out error %d\n", r);
        return r;
    }
    r = libusb_control_transfer(devh,CTRL_IN,HID_GET_REPORT,(HID_REPORT_TYPE_INPUT<<8)|0x00, 0, answer,PACKET_INT_LEN, TIMEOUT);
    if (r < 0) {
        fprintf(stderr, "Control IN error %d\n", r);
        return r;
    }
    for(i = 0;i < PACKET_INT_LEN; i++) {
        if(i%8 == 0)
            printf("\n");
        printf("%02x, %02x; ",question[i],answer[i]);
    }
    printf("\n");

    return 0;
}


static int Device::test_interrupt_transfer()
{
       int r,i;
    int transferred;
       char answer[PACKET_INT_LEN];
       char question[PACKET_INT_LEN];
       for (i=0;i<PACKET_INT_LEN; i++) question[i]=0x40+i;

    r = libusb_interrupt_transfer(devh, ENDPOINT_INT_OUT, question, PACKET_INT_LEN,
        &transferred,TIMEOUT);
    if (r < 0) {
        fprintf(stderr, "Interrupt write error %d\n", r);
        return r;
    }
    r = libusb_interrupt_transfer(devh, ENDPOINT_INT_IN, answer,PACKET_INT_LEN,
        &transferred, TIMEOUT);
    if (r < 0) {
        fprintf(stderr, "Interrupt read error %d\n", r);
        return r;
    }
    if (transferred < PACKET_INT_LEN) {
        fprintf(stderr, "Interrupt transfer short read (%d)\n", r);
        return -1;
    }

    for(i = 0;i < PACKET_INT_LEN; i++) {
        if(i%8 == 0)
            printf("\n");
        printf("%02x, %02x; ",question[i],answer[i]);
    }
    printf("\n");

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
#ifdef LINUX
     libusb_detach_kernel_driver(devh, 0);
#endif

    result = libusb_set_configuration(devh, 1);
    if (r < 0) {
        qDebug("libusb_set_configuration error %d\n"+result);
    }else
    qDebug("Successfully set usb configuration 1\n");

    result = libusb_claim_interface(devh, 0);
    if (r < 0) {
    qDebug(stderr, "libusb_claim_interface error %d\n", r);
    }else
    qDebug("Successfully claimed interface\n");

    qDebug("Testing control transfer using loop back test of feature report");
    test_control_transfer();

    qDebug("Testing control transfer using loop back test of input/output report");
    test_control_transfer_in_out();

    qDebug("Testing interrupt transfer using loop back test of input/output report");
    test_interrupt_transfer();

    qDebug("\n");


    return 0;
}

void Device::close()
{
    libusb_release_interface(devh, 0);

    libusb_close(devh);
    libusb_exit(NULL);
}
