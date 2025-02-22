#ifndef CLEM_HOST_DISK_UTILS_HPP
#define CLEM_HOST_DISK_UTILS_HPP

#include <string_view>
#include "cinek/buffertypes.hpp"
#include "clem_woz.h"

namespace ClemensDiskUtilities {

size_t calculateNibRequiredMemory(ClemensDriveType driveType);

struct ClemensWOZDisk* parseWOZ(struct ClemensWOZDisk* woz, cinek::ConstRange<uint8_t>& image);

std::string_view getDriveName(ClemensDriveType driveType);

ClemensDriveType getDriveType(std::string_view driveName);

struct ClemensWOZDisk* createWOZ(struct ClemensWOZDisk* woz, const struct ClemensNibbleDisk* nib);

} // end namespace

#endif
