/*
 * Copyright (C) 2016 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "automotive.vehicle@2.0-default-service"
#include <android/log.h>
#include <hidl/HidlTransportSupport.h>

#include <iostream>

#include <vhal_v2_0/DefaultVehicleConnector.h>
#include <vhal_v2_0/DefaultVehicleHal.h>
#include <vhal_v2_0/VehicleHalManager.h>

using ::android::hardware::automotive::vehicle::V2_0::VehicleHalManager;
using ::android::hardware::automotive::vehicle::V2_0::VehiclePropertyStore;
using ::android::hardware::automotive::vehicle::V2_0::impl::DefaultVehicleConnector;
using ::android::hardware::automotive::vehicle::V2_0::impl::DefaultVehicleHal;

int main(int /* argc */, char * /* argv */[]) {
    auto store = std::make_unique<VehiclePropertyStore>();
    auto connector = std::make_unique<DefaultVehicleConnector>();
    auto hal = std::make_unique<DefaultVehicleHal>(store.get(), connector.get());
    auto service = android::sp<VehicleHalManager>::make(hal.get());
    connector->setValuePool(hal->getValuePool());

    android::hardware::configureRpcThreadpool(4, true /* callerWillJoin */);

    ALOGI("Registering as service...");
    android::status_t status = service->registerAsService();

    if (status != android::OK) {
        ALOGE("Unable to register vehicle service (%d)", status);
        return 1;
    }

    ALOGI("Ready");
    ALOGI("(╯°□°）╯︵ ┻━┻ Raspitainment war hier 🎉🥳");
    android::hardware::joinRpcThreadpool();

    return 0;
}
