// This program is aimed at getting the hid device info into an enumerated list of hid_objects

#include <stdio.h>
#include <stdlib.h>

#include "hidapi.h"

#define TAIDOC_VENDOR_ID 10c4
#define TAIDOC_PRODUCT_ID ea80 

void PrintDeviceInfo(struct hid_device_info *);


int main()
{
	hid_init(); // intialises the hid api
	struct hid_device_info *hid_devices_pointer, *mouse_ptr; // pointers to struct hid_device_info to store the linked list starting addresses returned from hid_enumerate()
	hid_device *handle; 

	hid_devices_pointer =  hid_enumerate(0x0, 0x0) ; // enumerate all hid devices in laptop
	PrintDeviceInfo(hid_devices_pointer); // prints information about devices, defined in main.c
	
	mouse_ptr = hid_enumerate(TAIDOC_VENDOR_ID,TAIDOC_PRODUCT_ID); // gets information about the mouse
	PrintDeviceInfo(mouse_ptr); // prints information about the mouse
	
	handle = hid_open_path(mouse_ptr->path);
	if (handle == NULL)
	{
		printf("Opening device failed!\n");
		return 1;
	}		
	#define MAX_STR 255
	int result;
	wchar_t wstr[MAX_STR];

	result = hid_get_manufacturer_string(handle, wstr, MAX_STR);
	printf("Manufacturer: %ls\n", wstr);	
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

