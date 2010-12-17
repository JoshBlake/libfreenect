/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2010 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */

#ifndef _MSC_VER
#define _MSC_VER 1600
#endif
#define XN_EXPORTS

#include <initguid.h>
DEFINE_GUID(GUID_CLASS_PSDRV_USB, 0xc3b5f022, 0x5a42, 0x1980, 0x19, 0x09, 0xea, 0x72, 0x09, 0x56, 0x01, 0xb1);
#define USB_DEVICE_EXTRA_PARAM (void*)&GUID_CLASS_PSDRV_USB

#include <stdio.h>
#include <stdlib.h>
#include <XnUSB.h>
#include "freenect_internal.h"	

int fnusb_num_devices(fnusb_ctx *ctx)
{
	/*
	libusb_device **devs; //pointer to pointer of device, used to retrieve a list of devices
	ssize_t cnt = libusb_get_device_list (ctx, &devs); //get the list of devices

	if (cnt < 0)
		return (-1);

	int nr = 0, i = 0;
	struct libusb_device_descriptor desc;
	for (i = 0; i < cnt; ++i)
	{
		int r = libusb_get_device_descriptor (devs[i], &desc);
		if (r < 0)
			continue;
		if (desc.idVendor == VID_MICROSOFT && desc.idProduct == PID_NUI_CAMERA)
			nr++;
	}

	libusb_free_device_list (devs, 1);  // free the list, unref the devices in it
	*/
	int nr = 1;
	return nr;
}

int fnusb_init(fnusb_ctx *ctx, freenect_usb_context *usb_ctx)
{	
	XnStatus status = xnUSBInit();
	xnPrintError(status, "Init");
	if (status != XN_STATUS_OK || status != XN_STATUS_USB_ALREADY_INIT)
	{
		return status;
	}
	/*
	int i;
	
	for (i=0; i < USB_MAX_STREAMS; i++)
	{
		open_streams[i] = NULL;
	}
	*/
	ctx->should_free_ctx = 1;
	return 0;		
}

int fnusb_shutdown(fnusb_ctx *ctx)
{
	xnUSBShutdown();
	return 0;
}

static void iso_callback(fnusb_isoc_stream *strm, int read);
int fnusb_process_events(fnusb_ctx *ctx)
{
	/*
	int i, j;
	int read, ret;
	uint8_t *buf;
	fnusb_isoc_stream* stream;
	
	for (i=0; i<USB_MAX_STREAMS; i++)
	{
		stream = open_streams[i];
		if (NULL == stream)
			continue;

		for (j=0; j<stream->num_xfers; j++)
		{
			if (stream->dead == 1)
			{
				break;
			}

			read = usb_reap_async_nocancel(stream->xfers[stream->xfer_index].context, 10000);
			if (read != 0)
				printf("read %d/%d bytes from %d,%d: %d\n", read, stream->len, i, j, stream->xfer_index);
			if (read < 0)
			{
				if (read == -22)
				{
					setup_EP_transfer(stream->xfer_index, stream->parent, stream, stream->ep, stream->len);
				}
				else if (read != -116 && read < 0)
				{
					printf("error: %d %s\n", read, usb_strerror());
					usb_cancel_async(stream->xfers[stream->xfer_index].context);
				}
				else
				{
					//got to a stream that wasn't ready, wait till next time
					break;
				}
			}
			else
			{
				if (stream->dead) {
					freenect_context *ctx = stream->parent->parent->parent;
					stream->dead_xfers++;
					printf("EP transfer complete, %d left\n", stream->num_xfers - stream->dead_xfers);
					continue;
				}

				if (read > 0)
				{
					printf("iso %d %d %d\n",  read, i, stream->xfer_index);
					iso_callback(stream, read);	
				}
				buf = (uint8_t*)stream->xfers[stream->xfer_index].buffer;
				
				//printf("pkts: %d  len: %d  buf: %p\n", stream->pkts, stream->len, buf);
				if (buf == 0)
				{
					continue;
				}
				ZeroMemory(buf, stream->pkts * stream->len);
				ret = usb_submit_async(stream->xfers[stream->xfer_index].context, (char*)stream->xfers[stream->xfer_index].buffer, stream->pkts * stream->len);
				if( ret < 0 ){
					printf("error: %d %s\n", ret, usb_strerror());
					usb_cancel_async(stream->xfers[stream->xfer_index].context);
				}

				stream->xfer_index++;
				if (stream->xfer_index >= stream->num_xfers)
				{
					stream->xfer_index = 0;
				}	
			}
		}
	}
	*/
	return 0;
}	
/*
struct usb_device* fnusb_find_device_by_vid_pid(unsigned short vid, unsigned short pid, unsigned int index)
{
	struct usb_bus *busses;
	struct usb_bus *bus;
	int count = 0;

	busses = usb_get_busses();

	for (bus = busses; bus; bus = bus->next) {

		struct usb_device *dev;

		for (dev = bus->devices; dev; dev = dev->next) {

			if (dev->descriptor.idProduct == pid && dev->descriptor.idVendor == vid ) {
				if (count == index)
				{
					return dev;
				}
				count++;
			}
		}
	}
	return NULL;
}
*/
int fnusb_open_subdevices(freenect_device *dev, int index)
{
	XnStatus status;
	XnUSBDeviceSpeed DevSpeed;

	printf("open subdevices 1 camera\n");
	char* path = NULL;//"\\\\?\\usb";
	status = xnUSBOpenDevice(VID_MICROSOFT, PID_NUI_CAMERA, USB_DEVICE_EXTRA_PARAM, path, &dev->usb_cam.dev);
	if (status == XN_STATUS_USB_DEVICE_NOT_FOUND)
	{
		printf("open subdevices 1 can't find camera\n");
		return 1;
	}
	dev->usb_cam.parent = dev;
	xnPrintError(status, "Open Camera");
	status = xnUSBGetDeviceSpeed(dev->usb_cam.dev, &DevSpeed);
	xnPrintError(status, "Get speed");
		printf("dev: %d  cam device: %p\n", DevSpeed, dev->usb_cam.dev);
				printf("Setting interface\n");
	status = xnUSBSetInterface(dev->usb_cam.dev, 0, 0);
	xnPrintError(status, "Set interface");
/*
		printf("open subdevices 2 motor\n");
		
	status = xnUSBOpenDevice(VID_MICROSOFT, PID_NUI_CAMERA, USB_DEVICE_EXTRA_PARAM, path, &dev->usb_motor.dev);
	if (status == XN_STATUS_USB_DEVICE_NOT_FOUND)
	{	printf("open subdevices 2 can't find motor\n");
		return 1;
	}
	xnPrintError(status, "Open Motor");

		printf("open subdevices 3 done\n");
		
				printf("Setting interface\n");
	status = xnUSBSetInterface(dev->usb_motor.dev, 0, 0);
	xnPrintError(status, "Set interface");
*/
	return 0;
}

int fnusb_close_subdevices(freenect_device *dev)
{
	if (dev->usb_cam.dev) {
		xnUSBCloseDevice(dev->usb_cam.dev);
		dev->usb_cam.dev = NULL;
	}
	if (dev->usb_motor.dev) {
		xnUSBCloseDevice(dev->usb_motor.dev);
		dev->usb_motor.dev = NULL;
	}
	return 0;
}


XnBool XN_CALLBACK_TYPE stream_callback(XnUChar* buf, XnUInt32 nBufferSize, void* pCallbackData)
{
	fnusb_isoc_stream *stream = (fnusb_isoc_stream *)pCallbackData;
	if (nBufferSize != 0)
	{
		printf("[%d] received %d\n", stream->ep, nBufferSize);
	}

	
	for (int j=0; j<nBufferSize; j++)
	{
		if (buf[j] == 'R' &&
			buf[j+1] == 'B')
		{
			//printf("RB: %d\n", j);
			stream->cb(stream->parent->parent, &buf[j], stream->len);
		}
	}

	return TRUE;
}

static void iso_callback(fnusb_isoc_stream *stream, int read)
{
	/*
	int j;
	
	if (stream->dead == 1)
		return;
	
	uint8_t *buf = (uint8_t*)stream->xfers[stream->xfer_index].buffer;

	for (j=0; j<read; j++)
	{
		if (buf[j] == 'R' &&
			buf[j+1] == 'B')
		{
			//printf("RB: %d\n", j);
			stream->cb(stream->parent->parent, &buf[j], stream->len);
		}
	}
	*/
/*
	for (int i=0; i<stream->pkts; i++) {
		stream->cb(stream->parent->parent, buf, stream->len);
		
		buf += stream->len;
	}*/
	
}

void setup_EP_transfer(int i, fnusb_dev *dev, fnusb_isoc_stream *strm, int ep, int len)
{
	/*
	if (strm->xfers[i].buffer != NULL)
	{
		free(strm->xfers[i].buffer);
		strm->xfers[i].buffer = NULL;
	}
	strm->xfers[i].context = NULL;
	strm->xfers[i].buffer = (uint8_t*)malloc(sizeof(uint8_t) * strm->len * strm->pkts);
	ZeroMemory(strm->xfers[i].buffer, strm->pkts * strm->len);

	usb_isochronous_setup_async(dev->dev, &strm->xfers[i].context, ep, len);
	int ret = usb_submit_async(strm->xfers[i].context, (char*)strm->xfers[i].buffer, strm->pkts * strm->len);
	if (ret < 0)
		printf("Failed to submit xfer %d: %d\n", i, ret);
		*/
}

int fnusb_start_iso(fnusb_dev *dev, fnusb_isoc_stream *stream, fnusb_iso_cb cb, int ep, int num_xfers, int pkts, int len)
{
	XnStatus status = XN_STATUS_OK;
	stream->parent = dev;
	stream->cb = cb;
	stream->num_xfers = num_xfers;
	stream->pkts = pkts;
	stream->ep = ep;
	stream->len = len;
	stream->dead = 0;
//	return 0;
	printf("start iso %d: 1 open endpoint %p %p\n", ep, dev, dev->parent);
	status = xnUSBOpenEndPoint(dev->dev, ep, XN_USB_EP_ISOCHRONOUS, XN_USB_DIRECTION_IN, &stream->ep_handle);
	if (status != XN_STATUS_OK)
	{
		xnPrintError(status, "Can't open ep");
		printf("dev: %p\n", dev->dev);
		return status;
	}
	printf("start iso %d: 2 shutdown read thread\n", ep);
	xnUSBShutdownReadThread(stream->ep_handle);
	printf("start iso %d: 3 init read thread\n", ep);
	status = xnUSBInitReadThread(stream->ep_handle, len*80, NUM_XFERS, READ_TIMEOUT, stream_callback, stream);
	if (status != XN_STATUS_OK)
	{
		xnPrintError(status, "Can't init read thread");
		return status;
	}
	printf("start iso %d: 4 done\n", ep);
	return 0;

}

int fnusb_stop_iso(fnusb_dev *dev, fnusb_isoc_stream *stream)
{
	stream->dead = 1;

	xnUSBShutdownReadThread(stream->ep_handle);
	return 0;
}

int fnusb_control(fnusb_dev *dev, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint8_t *data, uint16_t wLength)
{
	for (int i=0; i<10; i++)
	{
	XnStatus status = XN_STATUS_OK;
	printf("Control type=%04x request=%04x value=%04x index=%04x data=_ len=%d\n", bmRequestType, bRequest, wValue, wIndex, wLength);
	if (bmRequestType == 0x40)
	{
		status = xnUSBSendControl(dev->dev, XN_USB_CONTROL_TYPE_VENDOR, bRequest, wValue, wIndex, (unsigned char*)data, wLength, 0);
		xnPrintError(status, "Sent control");
		if (status == XN_STATUS_OK)
		{
			Sleep(100);
			return 0;
		}
	}
	else if (bmRequestType == 0xC0)
	{
		unsigned int bytesReceived = 0;
		status = xnUSBReceiveControl(dev->dev, XN_USB_CONTROL_TYPE_VENDOR, bRequest, wValue, wIndex, (unsigned char*)data, wLength, &bytesReceived, 0);
		xnPrintError(status, "Received control");
		if (status == XN_STATUS_OK)
			return bytesReceived;
	}
	printf("sleeping: %d/5\n", i);
	Sleep(100);
	}
}
