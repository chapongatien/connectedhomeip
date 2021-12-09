/*
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *    Copyright (c) 2018 Nest Labs, Inc.
 *    All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */
/* this file behaves like a config.h, comes first */
#include <platform/internal/CHIPDeviceLayerInternal.h>

#include <inet/TCPEndPointImpl.h>
#include <inet/UDPEndPointImpl.h>
#include <platform/internal/BLEManager.h>
#include <system/SystemLayerImpl.h>

namespace chip {
namespace DeviceLayer {

chip::Inet::EndPointManager<Inet::UDPEndPoint> * UDPEndPointManager()
{
    static chip::Inet::UDPEndPointManagerImpl gUDPEndPointManager;
    return &gUDPEndPointManager;
}

#if INET_CONFIG_ENABLE_TCP_ENDPOINT
chip::Inet::EndPointManager<Inet::TCPEndPoint> * TCPEndPointManager()
{
#if INET_CONFIG_ENABLE_TCP_ENDPOINT
    static chip::Inet::TCPEndPointManagerImpl gTCPEndPointManager;
    return &gTCPEndPointManager;
#else  // INET_CONFIG_ENABLE_TCP_ENDPOINT
    return nullptr;
#endif // INET_CONFIG_ENABLE_TCP_ENDPOINT
}
#endif // INET_CONFIG_ENABLE_TCP_ENDPOINT

chip::System::LayerImpl * gMockedSystemLayer = nullptr;

void SetSystemLayerForTesting(System::LayerImpl * layer)
{
    gMockedSystemLayer = layer;
}

chip::System::LayerImpl & SystemLayerImpl()
{
    if (gMockedSystemLayer != nullptr)
        return *gMockedSystemLayer;

    static chip::System::LayerImpl gSystemLayerImpl;
    return gSystemLayerImpl;
}

chip::System::Layer & SystemLayer()
{
    return SystemLayerImpl();
}

#if CHIP_SYSTEM_CONFIG_USE_SOCKETS
chip::System::LayerSockets & SystemLayerSockets()
{
    return SystemLayerImpl();
}
#endif // CHIP_SYSTEM_CONFIG_USE_SOCKETS

namespace Internal {
const char * const TAG = "CHIP[DL]";
} // namespace Internal

} // namespace DeviceLayer
} // namespace chip
