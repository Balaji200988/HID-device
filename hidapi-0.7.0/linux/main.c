// This program is aimed at getting the hid device info into an enumerated list of hid_objects

#include <stdio.h>
#include <stdlib.h>

#include "hidapi.h"

#define MOUSE_VENDOR_ID  0x045e
#define MOUSE_PRODUCT_ID 0x07fd

void PrintDeviceInfo(struct hid_device_info *);


int main()
{
	hid_init(); // intialises the hid api
	struct hid_device_info *hid_devices_pointer, *mouse_ptr; // pointers to struct hid_device_info to store the linked list starting addresses returned from hid_enumerate()
	hid_devices_pointer =  hid_enumerate(0x0, 0x0) ; // enumerate all hid devices in laptop
	PrintDeviceInfo(hid_devices_pointer); // prints information about devices, defined in hidExp.c
	mouse_ptr = hid_enumerate(MOUSE_VENDOR_ID, MOUSE_PRODUCT_ID); // gets information about the mouse
	PrintDeviceInfo(mouse_ptr); // prints information about the mouse

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
		usleep(500);
	}
}
