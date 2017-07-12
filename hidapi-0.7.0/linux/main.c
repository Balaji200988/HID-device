// This program is aimed at getting the hid device info into an enumerated list of hid_objects

#include <stdio.h>
#include <stdlib.h>

#include "hidapi.h"

#define MOUSE_VENDOR_ID  0x045e
#define MOUSE_PRODUCT_ID 0x07fd

void PrintDeviceInfo(struct hid_device_info *);


int main()
{
	unsigned char buf[65];
	hid_init(); // intialises the hid api
	struct hid_device_info *hid_devices_pointer, *mouse_ptr; // pointers to struct hid_device_info to store the linked list starting addresses returned from hid_enumerate()
	hid_device *handle; 

	hid_devices_pointer =  hid_enumerate(0x0, 0x0) ; // enumerate all hid devices in laptop
//	PrintDeviceInfo(hid_devices_pointer); // prints information about devices, defined in main.c
	
	mouse_ptr = hid_enumerate(MOUSE_VENDOR_ID, MOUSE_PRODUCT_ID); // gets information about the mouse
//	PrintDeviceInfo(mouse_ptr); // prints information about the mouse
	
	handle = hid_open(mouse_ptr->vendor_id, mouse_ptr->product_id, mouse_ptr->serial_number);
	if (handle == NULL)
	{
		printf("Opening device failed!\n");
		return 1;
	}else
	{
		printf("Opened device at %s\n", mouse_ptr->path);
	}		
	#define MAX_STR 255
	int result;
	wchar_t wstr[MAX_STR];

	result = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer: %ls\n", wstr);	
	
	//hid_set_nonblocking(handle, 1);
		
	result = hid_read_timeout(handle, buf, 65, 20000);
	if (result < 0) printf("Unable to read\n");
//	for (int i = 0; i < result; i++)
//	{
//		printf("buf[%d]: %d\n", i, buf[i]);
//	}	
	printf("Number of bytes read = %d", result);	
	hid_free_enumeration(hid_devices_pointer); // free the memory
	hid_free_enumeration(mouse_ptr); // free the memory
	
	hid_exit(); // clean up 
	return 0; // return
}

void PrintDeviceInfo(struct hid_device_info *temp)
{
	while(temp)
	{
		printf ("Device Found\n type: %04hx %04hx\n path: %s\n serial_number: %ls",
			temp->vendor_id, temp->product_id, temp->path, temp->serial_number);
		printf("\n");
		printf("Manufacturer: %ls\n", temp->manufacturer_string);
		printf("Product     : %ls\n\n", temp->product_string);
		temp = temp->next;// go to the next object in the linked list
	}
}
