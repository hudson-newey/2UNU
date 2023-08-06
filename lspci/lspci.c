#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "lspci.h"

#define SYSFS_PCI_PATH "/sys/bus/pci/devices"

void listAllDevices() {
    DIR *dir;
    struct dirent *entry;

    dir = opendir(SYSFS_PCI_PATH);
    if (dir == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') {
            char pciSysPath[128];
            snprintf(pciSysPath, sizeof(pciSysPath), "%s/%s", SYSFS_PCI_PATH, entry->d_name);

            char vendor[128] = "";
            char device[128] = "";

            char pciVendorPath[256];
            snprintf(pciVendorPath, sizeof(pciVendorPath), "%s/%s", pciSysPath, "vendor");
            FILE *vendorFile = fopen(pciVendorPath, "r");
            if (vendorFile != NULL) {
                fscanf(vendorFile, "%s", vendor);
                fclose(vendorFile);
            }

            char pciDevicePath[256];
            snprintf(pciDevicePath, sizeof(pciDevicePath), "%s/%s", pciSysPath, "device");
            FILE *deviceFile = fopen(pciDevicePath, "r");
            if (deviceFile != NULL) {
                fscanf(deviceFile, "%s", device);
                fclose(deviceFile);
            }
            printf("%s %s %s\n", entry->d_name, vendor, device);
        }
    }

    closedir(dir);
}

void printProgramVersion() {
    printf("%s\n", version);
}

void printHelpDocs() {
    printf("%s\n", helpDocs);
}

int main(int argc, const char *argv[]) {
    if (argc > 1) {
        if (strcmp(argv[1], "--version") == 0) {
            printProgramVersion();
            return 0;
        } else if (strcmp(argv[1], "--help") == 0) {
            printHelpDocs();
            return 0;
        }

        return 1;
    }

    listAllDevices();
    return 0;
}
