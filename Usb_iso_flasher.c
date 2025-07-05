#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main() {
    int iso_burner();
    printf("Welcome to the Usb-iso-flash for linux\n");
    printf("1. Start\n");
    printf("2. Exit\n");
    int menuinput;
    scanf("%d", &menuinput);
    switch (menuinput) {
        case 1:
            iso_burner();
            break;
    
        case 2:
            return 0;
            break;

        default:
            printf("Wrong input! Enter only '1' or '2'\n");
            break;
    }
    return 0;
}


int iso_burner() {
    char iso_path[256];
    char usb_path[256];
    char command[512];

    printf("\nEnter the path of the ISO file to flash on a USB:\n");
    scanf("%s", iso_path);

    
    
    struct stat buffer;
    if (stat(iso_path, &buffer) == 0) {
        printf("Select the USB device (Path) where you want to flash the ISO:\n");
        printf("WARNING: Flashing will erase all data on the selected USB device!\n");
        system("lsblk");  
        scanf("%s", usb_path);
        
        char confirm;
        printf("Are you sure you want to flash the ISO to %s? This will erase all data on the device. (y/n): ", usb_path);
        scanf(" %c", &confirm); 

        if (confirm == 'y' || confirm == 'Y') {
            snprintf(command, sizeof(command),
                    "sudo dd if=%s of=%s bs=4M status=progress conv=fsync",
                    iso_path, usb_path);

            printf("Running command: %s\n", command);
            system(command);
            printf("ISO flashing process completed!\n");
        } else {
            printf("Flashing canceled.\n");
        }

    } else {
        printf("Invalid ISO path or file does not exist\n");
    }

    return 0;
}
