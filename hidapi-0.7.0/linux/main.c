// This program is aimed at getting the hid device info into an enumerated list of hid_objects

#include <stdio.h>
#include <stdlib.h>

#include "hidapi.h"

#define MOUSE_VENDOR_ID  0x045e
#define MOUSE_PRODUCT_ID 0x07fd

#define MAX_STR_LEN      255
void PrintDeviceInfo(struct hid_device_info *);


int main()
{
	wchar_t wstr[MAX_STR_LEN];
	int result;
	hid_init(); // intialises the hid api
	hid_device *DeviceHandle;
	DeviceHandle = hid_open(MOUSE_VENDOR_ID, MOUSE_PRODUCT_ID, NULL);
	if (DeviceHandle == NULL)
	{
		printf("Failed to open device\n");
		return 1;
	}
	result = hid_get_product_string(DeviceHandle, wstr, MAX_STR_LEN);
	if (result < 0)
	{	
		printf("Failed to get product string\n");
		return 1;
	}
	printf("Manufacturer: %ls \n", wstr);
	hid_exit(); // clean up 
	return 0; // return
}

