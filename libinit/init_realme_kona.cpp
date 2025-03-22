/*
 * Copyright (C) 2025 The LineageOS Project
 * SPDX-License-Identifier: Apache-2.0
 */

#include <android-base/logging.h>
#include <android-base/properties.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

using android::base::GetProperty;

/*
 * SetProperty does not allow updating read only properties and as a result
 * does not work for our use case. Write "OverrideProperty" to do practically
 * the same thing as "SetProperty" without this restriction.
 */
void OverrideProperty(const char* name, const char* value) {
    size_t valuelen = strlen(value);

    prop_info* pi = (prop_info*)__system_property_find(name);
    if (pi != nullptr) {
        __system_property_update(pi, value, valuelen);
    } else {
        __system_property_add(name, strlen(name), value, valuelen);
    }
}

/*
 * Only for read-only properties. Properties that can be wrote to more
 * than once should be set in a typical init script (e.g. init.oplus.hw.rc)
 * after the original property has been set.
 */
void vendor_load_properties() {
    auto prjname = std::stoi(GetProperty("ro.boot.prjname", "0"));

    switch (prjname) {
        case 19795: // bladerunner CN
            OverrideProperty("ro.product.product.device", "RMX2071CN");
            OverrideProperty("ro.product.product.model", "RMX2071");
            OverrideProperty("ro.boot.hardware.sku", "bladerunner");
            break;
        case 20607: // bladerunner_48m CN
            OverrideProperty("ro.product.product.device", "RMX2072CN");
            OverrideProperty("ro.product.product.model", "RMX2072");
            OverrideProperty("ro.boot.hardware.sku", "bladerunner_48m");
            break;
        case 19705: // bladerunner Global
            OverrideProperty("ro.product.product.device", "RMX2075L1");
            OverrideProperty("ro.product.product.model", "RMX2075");
            OverrideProperty("ro.boot.hardware.sku", "bladerunner");
            break;
        case 19706: // bladerunner IN
            OverrideProperty("ro.product.product.device", "RMX2076L1");
            OverrideProperty("ro.product.product.model", "RMX2076");
            OverrideProperty("ro.boot.hardware.sku", "bladerunner");
            break;
        case 21615: // rivena CN 真我GT大师探索版
            OverrideProperty("ro.product.product.device", "RE546F");
            OverrideProperty("ro.product.product.model", "RMX3366");
            OverrideProperty("ro.boot.hardware.sku", "rivena");
            break;
        case 21619: // bitra CN
            OverrideProperty("ro.product.product.device", "RE5473");
            OverrideProperty("ro.product.product.model", "RMX3370");
            OverrideProperty("ro.boot.hardware.sku", "bitra");
            break;
        case 136730: // bitra CN (Dragon Ball Edition)
            OverrideProperty("ro.product.product.device", "RE5473");
            OverrideProperty("ro.product.product.model", "RMX3370");
            OverrideProperty("ro.boot.hardware.sku", "bitra");
            break;
        case 136859: // bitra Global
            OverrideProperty("ro.product.product.device", "RE879AL1");
            OverrideProperty("ro.product.product.model", "RMX3370");
            OverrideProperty("ro.boot.hardware.sku", "bitra");
            break;
        case 136858: // bitra IN
            OverrideProperty("ro.product.product.device", "RE879AL1");
            OverrideProperty("ro.product.product.model", "RMX3370");
            OverrideProperty("ro.boot.hardware.sku", "bitra");
            break;
        default:
            LOG(ERROR) << "Unexpected project version: " << prjname;
    }
}