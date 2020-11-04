/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// QSPI SFDP Flash - Block Device example
#include "mbed.h"
#include "BlockDevice.h"

int main()
{
    BlockDevice &block_device = *BlockDevice::get_default_instance();
    int status = block_device.init();
    printf("Init status %d\n", status);
    bd_size_t sector_size_at_address_0 = block_device.get_erase_size(0);
    printf("Sector size %ld\n", status);

    char buffer[] = "ABCD";

    printf("> 4-byte write & read\n");
    status = block_device.erase(0, sector_size_at_address_0);
    printf("Erase status %d\n", status);
    status = block_device.program(buffer, 0, 4);
    printf("Program status %d\n", status);
    memset(buffer, 0, sizeof(buffer));
    status = block_device.read(buffer, 0, 4);
    printf("Read status %d\n", status);
    printf("Buffer %.*s\n", 4, buffer);

    sprintf(buffer, "ABCD");
    printf("> 1-byte write & read\n");
    status = block_device.erase(0, sector_size_at_address_0);
    printf("Erase status %d\n", status);
    status = block_device.program(buffer, 0, 1);
    printf("Program status %d\n", status);
    memset(buffer, 0, sizeof(buffer));
    status = block_device.read(buffer, 0, 1);
    printf("Read status %d\n", status);
    printf("Buffer %.*s\n", 1, buffer);

    status = block_device.deinit();
    printf("Deinit status %d\n", status);
}
