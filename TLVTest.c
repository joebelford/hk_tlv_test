
#ifdef __cplusplus
extern "C" {
#endif

#include "HAP.h"
#include "HAPBase.h"
#include "HAP.h"
#include "HAPTLV+Internal.h"
#include "HAPBase.h"
#include <stdlib.h>
#include <unistd.h>
#include "setupEndpointsTLV.h"
#include "StreamingSession.h"

#if __has_feature(nullability)
#pragma clang assume_nonnull begin
#endif

bool isValid1(void* unsused HAP_UNUSED) {
    return true;
}

/* ---------------------------------------------------------------------------------------------*/

typedef struct {
    uint8_t profileID;
    uint8_t level;
    uint8_t packetizationMode;
} videoCodecParamsStruct;

typedef struct {
    uint16_t imageWidth;
    uint16_t imageHeight;
    uint8_t frameRate;
} videoAttributesStruct;

typedef struct {
    uint8_t videoCodecType;
    videoCodecParamsStruct videoCodecParams;
    videoAttributesStruct videoAttributes;
} videoCodecConfigStruct;

typedef struct {
    videoCodecConfigStruct videoCodecConfig;
} supportedVideoConfigStruct;

HAP_RESULT_USE_CHECK
HAPError HandleSupportedVideoRead(
        HAPAccessoryServerRef* server,
        const HAPTLV8CharacteristicReadRequest* request,
        HAPTLVWriterRef* responseWriter,
        void* _Nullable context);

HAP_STRUCT_TLV_SUPPORT(void, SupportedVideoConfigFormat)
HAP_STRUCT_TLV_SUPPORT(void, VideoCodecConfigFormat)
HAP_STRUCT_TLV_SUPPORT(void, VideoCodecParamsFormat)
HAP_STRUCT_TLV_SUPPORT(void, VideoAttributesFormat)

const HAPUInt8TLVFormat videoCodecParamsProfileIDFormat = { .type = kHAPTLVFormatType_UInt8,
                                                            .constraints = { .minimumValue = 0, .maximumValue = 2 },
                                                            .callbacks = { .getDescription = NULL } };
const HAPStructTLVMember videoCodecParamsProfileIDMember = { .valueOffset =
                                                                     HAP_OFFSETOF(videoCodecParamsStruct, profileID),
                                                             .isSetOffset = 0,
                                                             .tlvType = 1,
                                                             .debugDescription = "Video Codec Config Params Profile ID",
                                                             .format = &videoCodecParamsProfileIDFormat,
                                                             .isOptional = false,
                                                             .isFlat = false };

const HAPUInt8TLVFormat videoCodecParamsLevelFormat = { .type = kHAPTLVFormatType_UInt8,
                                                        .constraints = { .minimumValue = 0, .maximumValue = 2 },
                                                        .callbacks = { .getDescription = NULL } };
const HAPStructTLVMember videoCodecParamsLevelMember = { .valueOffset = HAP_OFFSETOF(videoCodecParamsStruct, level),
                                                         .isSetOffset = 0,
                                                         .tlvType = 2,
                                                         .debugDescription = "Video Codec Config Params Level",
                                                         .format = &videoCodecParamsLevelFormat,
                                                         .isOptional = false,
                                                         .isFlat = false };

const HAPUInt8TLVFormat videoCodecParamsPacketizationModeFormat = { .type = kHAPTLVFormatType_UInt8,
                                                                    .constraints = { .minimumValue = 0,
                                                                                     .maximumValue = 2 },
                                                                    .callbacks = { .getDescription = NULL } };

const HAPStructTLVMember videoCodecParamsPacketizationModeMember = {
    .valueOffset = HAP_OFFSETOF(videoCodecParamsStruct, packetizationMode),
    .isSetOffset = 0,
    .tlvType = 3,
    .debugDescription = "Video Codec Config Packetization Mode",
    .format = &videoCodecParamsPacketizationModeFormat,
    .isOptional = false,
    .isFlat = false
};

/* ---------------------------------------------------------------------------------------------*/

const HAPUInt16TLVFormat videoAttributesImageWidthFormat = { .type = kHAPTLVFormatType_UInt16,
                                                             .constraints = { .minimumValue = 0, .maximumValue = 4096 },
                                                             .callbacks = { .getDescription = NULL } };
const HAPStructTLVMember videoAttributesImageWidthMember = { .valueOffset =
                                                                     HAP_OFFSETOF(videoAttributesStruct, imageWidth),
                                                             .isSetOffset = 0,
                                                             .tlvType = 1,
                                                             .debugDescription = "Video Attributes Image Width",
                                                             .format = &videoAttributesImageWidthFormat,
                                                             .isOptional = false,
                                                             .isFlat = false };

const HAPUInt16TLVFormat videoAttributesImageHeightFormat = { .type = kHAPTLVFormatType_UInt16,
                                                              .constraints = { .minimumValue = 0,
                                                                               .maximumValue = 4096 },
                                                              .callbacks = { .getDescription = NULL } };
const HAPStructTLVMember videoAttributesImageHeightMember = { .valueOffset =
                                                                      HAP_OFFSETOF(videoAttributesStruct, imageHeight),
                                                              .isSetOffset = 0,
                                                              .tlvType = 2,
                                                              .debugDescription = "Video Attributes Image Height",
                                                              .format = &videoAttributesImageHeightFormat,
                                                              .isOptional = false,
                                                              .isFlat = false };

const HAPUInt8TLVFormat videoAttributesFrameRateFormat = { .type = kHAPTLVFormatType_UInt8,
                                                           .constraints = { .minimumValue = 0, .maximumValue = 255 },
                                                           .callbacks = { .getDescription = NULL } };
const HAPStructTLVMember videoAttributesFrameRateMember = { .valueOffset =
                                                                    HAP_OFFSETOF(videoAttributesStruct, frameRate),
                                                            .isSetOffset = 0,
                                                            .tlvType = 3,
                                                            .debugDescription = "Video Attributes Frame Rate",
                                                            .format = &videoAttributesFrameRateFormat,
                                                            .isOptional = false,
                                                            .isFlat = false };

const VideoAttributesFormat videoAttributesFormat = {
    .type = kHAPTLVFormatType_Struct,
    .members = (const HAPStructTLVMember* const[]) { &videoAttributesImageWidthMember,
                                                     &videoAttributesImageHeightMember,
                                                     &videoAttributesFrameRateMember,
                                                     NULL },
    .callbacks = { .isValid = isValid1 }
};
const HAPStructTLVMember videoAttributesMember = { .valueOffset = HAP_OFFSETOF(videoCodecConfigStruct, videoAttributes),
                                                   .isSetOffset = 0,
                                                   .tlvType = 3,
                                                   .debugDescription = "Video Attributes",
                                                   .format = &videoAttributesFormat,
                                                   .isOptional = false,
                                                   .isFlat = false };
/* ---------------------------------------------------------------------------------------------*/

const VideoCodecConfigFormat videoCodecParamsFormat = {
    .type = kHAPTLVFormatType_Struct,
    .members = (const HAPStructTLVMember* const[]) { &videoCodecParamsProfileIDMember,
                                                     &videoCodecParamsLevelMember,
                                                     &videoCodecParamsPacketizationModeMember,
                                                     NULL },
    .callbacks = { .isValid = isValid1 }
};
const HAPStructTLVMember videoCodecParamsMember = { .valueOffset =
                                                            HAP_OFFSETOF(videoCodecConfigStruct, videoCodecParams),
                                                    .isSetOffset = 0,
                                                    .tlvType = 2,
                                                    .debugDescription = "Video Codec Parameters",
                                                    .format = &videoCodecParamsFormat,
                                                    .isOptional = false,
                                                    .isFlat = false };

/* ---------------------------------------------------------------------------------------------*/

const HAPUInt8TLVFormat videoCodecTypeFormat = { .type = kHAPTLVFormatType_UInt8,
                                                 .constraints = { .minimumValue = 0, .maximumValue = 1 },
                                                 .callbacks = { .getDescription = NULL } };
const HAPStructTLVMember videoCodecTypeMember = { .valueOffset = HAP_OFFSETOF(videoCodecConfigStruct, videoCodecType),
                                                  .isSetOffset = 0,
                                                  .tlvType = 1,
                                                  .debugDescription = "Video Codec Type",
                                                  .format = &videoCodecTypeFormat,
                                                  .isOptional = false,
                                                  .isFlat = false };

/* ---------------------------------------------------------------------------------------------*/

const VideoCodecConfigFormat videoCodecConfigFormat = {
    .type = kHAPTLVFormatType_Struct,
    .members = (const HAPStructTLVMember* const[]) { &videoCodecTypeMember,
                                                     &videoCodecParamsMember,
                                                     &videoAttributesMember,
                                                     NULL },
    .callbacks = { .isValid = isValid1 }
};

const HAPStructTLVMember videoCodecConfigMember = { .valueOffset =
                                                            HAP_OFFSETOF(supportedVideoConfigStruct, videoCodecConfig),
                                                    .isSetOffset = 0,
                                                    .tlvType = 1,
                                                    .debugDescription = "Video Codec Config",
                                                    .format = &videoCodecConfigFormat,
                                                    .isOptional = false,
                                                    .isFlat = false };

const SupportedVideoConfigFormat supportedVideoConfigFormat = {
    .type = kHAPTLVFormatType_Struct,
    .members = (const HAPStructTLVMember* const[]) { &videoCodecConfigMember, NULL },
    .callbacks = { .isValid = isValid1 }
};

supportedVideoConfigStruct supportedVideoConfigValue = {
    .videoCodecConfig = { .videoCodecType = 0,
                          .videoCodecParams = { .profileID = 1,
                                                .level = 2,
                                                .packetizationMode = 0 }, // TODO - Make enums for profileID, and level
                          .videoAttributes = { .imageWidth = 1920, .imageHeight = 1080, .frameRate = 30 } }
};

/* ---------------------------------------------------------------------------------------------*/

int main() {
    uint8_t setupBytes[121];
    HAPRawBufferCopyBytes(&setupBytes, &setupEndpoints, 121);
    HAPError err;
    HAPTLVReaderRef reader;
    HAPTLVReaderCreateWithOptions(
            &reader,
            &(const HAPTLVReaderOptions) { .bytes = setupBytes,
                                           .numBytes = HAPArrayCount(setupBytes),
                                           .maxBytes = HAPArrayCount(setupBytes) });

    streamingSettings cameraEndpoint;

    err = handleWrite(&reader, &cameraEndpoint);
    HAPAssert(!err);
    streamingSession newSession;

    newSession.dst_ip_address = cameraEndpoint.address.ipAddress;

    const char ipAddr[] = "10.0.1.5";

    in_addr_t ipAddress;

    inet_pton(AF_INET, ipAddr, &ipAddress);

    cameraEndpoint.address.ipAddress = ipAddress;

    newSession.settings = cameraEndpoint;

    newSession.status = kHAPCharacteristicValue_StreamingStatus_Available;

    HAPTLVWriterRef myWriter;
    uint8_t bytes[1024];
    HAPTLVWriterCreate(&myWriter, &bytes, sizeof bytes);
    err = handleRead(&myWriter, &newSession);
    HAPAssert(!err);

    void* actualBytes;
    size_t numActualBytes;

    HAPTLVWriterGetBuffer(&myWriter, &actualBytes, &numActualBytes);

    HAPLogDebug(&kHAPLog_Default, "size of output: %lu", numActualBytes);

    for (size_t i = 0; i < numActualBytes; i++)
    {
        HAPLogDebug(&kHAPLog_Default, "0x%02X", ((uint8_t*)actualBytes)[i]);
    }
    

    // size_t numExpectedBytes = 121;
    // HAPAssert(numActualBytes == numExpectedBytes);
    // HAPAssert(HAPRawBufferAreEqual(actualBytes, &setupEndpoints, numActualBytes));

    /*     HAPTLV sessionId, controllerAddress, videoParams, audioParams;
    sessionId.type = 1;
    controllerAddress.type = 3;
    videoParams.type = 4;
    audioParams.type = 5;
    err = HAPTLVReaderGetAll(
            &reader, (HAPTLV* const[]) { &sessionId, &controllerAddress, &videoParams, &audioParams, NULL });
    HAPAssert(!err);

    controllerAddressStruct myControllerAddress;

    uint8_t addressBuffer[controllerAddress.value.numBytes];
    HAPRawBufferCopyBytes(addressBuffer, &controllerAddress.value.bytes[0], controllerAddress.value.numBytes);

    HAPTLVReaderRef addressReader;
    HAPTLVReaderCreateWithOptions(
            &addressReader,
            &(const HAPTLVReaderOptions) { .bytes = addressBuffer,
                                           .numBytes = controllerAddress.value.numBytes,
                                           .maxBytes = controllerAddress.value.numBytes });

    err = HAPTLVReaderDecode(&addressReader, &controllerAddressFormat, &myControllerAddress);

    HAPLogDebug(&kHAPLog_Default, "IP Address Version: %d\n", myControllerAddress.ipAddrVersion);
        HAPLogDebug(&kHAPLog_Default, "IP Address pointer: %p\n", myControllerAddress.ipAddress);
        HAPLogDebug(&kHAPLog_Default, "IP Address: %s\n", (char*) &myControllerAddress.ipAddress);
    HAPLogDebug(&kHAPLog_Default, "video port: %u\n", myControllerAddress.videoPort);
        HAPLogDebug(&kHAPLog_Default, "audio port: %u\n", myControllerAddress.audioPort); */

    /**
     * @brief Let's encode and see if we have same buffers
     *
     */

    /*     controllerAddressStruct myOutControllerAddress = {
        .audioPort = 65451, .videoPort = 49536, .ipAddrVersion = 0, .ipAddress = "10.0.1.210"
    };

    HAPTLVWriterRef myWriter;
    uint8_t bytes[1024];
    HAPTLVWriterCreate(&myWriter, &bytes, sizeof bytes);

    // err = HAPTLVWriterAppend(&myWriter, &sessionId);
    // HAPAssert(!err);

    // err = HAPTLVWriterAppend(&myWriter, &videoParams);
    // HAPAssert(!err);

    // err = HAPTLVWriterAppend(&myWriter, &audioParams);
    // HAPAssert(!err);

    err = HAPTLVWriterEncode(&myWriter, &controllerAddressFormat, &myOutControllerAddress);
    HAPAssert(!err);

    void* actualBytes;
    size_t numActualBytes;

    HAPTLVWriterGetBuffer(&myWriter, &actualBytes, &numActualBytes);

    uint8_t myBytes[] = {
        0x03, 0x17,       // Controller Address has type 1, 2, 3 4
        0x01, 0x01, 0x00, // IP Address Version
        0x02, 0x0A,       // IP Address  char[] 10.0.1.210
            0x31, 0x30, 0x2E, 0x30, 0x2E, 0x31, 0x2E, 0x32, 0x31, 0x30, 0x03, 0x02, 0x80, 0xC1, // Video RTP Port
       uint16_t 0x04, 0x02, 0xAB, 0xFF,                                                             // Audio RTP Port
       uint16_t
    };

        HAPRawBufferCopyBytes(&myBytes[0], &actualBytes[0], numActualBytes); */

    // size_t numExpectedBytes = 121;
    // HAPAssert(numActualBytes == numExpectedBytes);
    // HAPAssert(HAPRawBufferAreEqual(actualBytes, setupEndpoints, numActualBytes));

    return kHAPError_None;
    // This works to parse
    /*     HAPTLV tlv;
        bool valid = false;

        err = HAPTLVReaderGetNext(&reader, &valid, &tlv);
        HAPAssert(!err);
        HAPAssert(valid);
        HAPLogDebug(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", tlv.type, tlv.value.numBytes);

        return err; */
    /*     HAPError err;

        HAPTLVWriterRef responseWriter;

        // const HAPTLV videoCodecConfigTLV = { .type = 1, .value = { .bytes = outBuffer, .numBytes = outBufferSize } };

        uint8_t bytes[1024];
        HAPTLVWriterCreate(&responseWriter, &bytes, sizeof bytes);

        err = HAPTLVWriterEncode(&responseWriter, &supportedVideoConfigFormat, &supportedVideoConfigValue);

        HAPAssert(!err);

        void* actualBytes;
        size_t numActualBytes;

        HAPTLVWriterGetBuffer(&responseWriter, &actualBytes, &numActualBytes);

        HAPTLVReaderRef reader;
        HAPTLVReaderCreateWithOptions(
                &reader,
                &(const HAPTLVReaderOptions) {
                        .bytes = actualBytes, .numBytes = numActualBytes, .maxBytes = numActualBytes });

        HAPTLV tlv;
        bool valid = false;

        err = HAPTLVReaderGetNext(&reader, &valid, &tlv);
        HAPAssert(!err);
        HAPAssert(valid);
        HAPLogDebug(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", tlv.type, tlv.value.numBytes);

        if (tlv.type == 1) {
            uint8_t buffer[tlv.value.numBytes];
            HAPRawBufferCopyBytes(buffer, &tlv.value.bytes[0], tlv.value.numBytes);
            HAPTLVReaderRef codecReader;
            HAPTLVReaderCreateWithOptions(
                    &codecReader,
                    &(const HAPTLVReaderOptions) { .bytes = buffer, .numBytes = sizeof buffer, .maxBytes = sizeof buffer
       }); HAPTLV typeTLV, paramsTLV, attributesTLV; typeTLV.type = 1; paramsTLV.type = 2; attributesTLV.type = 3; err =
       HAPTLVReaderGetAll(&codecReader, (HAPTLV* const[]) { &typeTLV, &paramsTLV, &attributesTLV, NULL });
            HAPAssert(!err);
            HAPLogDebug(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", typeTLV.type, typeTLV.value.numBytes);
            HAPLogDebug(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", paramsTLV.type, paramsTLV.value.numBytes);
            HAPLogDebug(
                    &kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", attributesTLV.type,
       attributesTLV.value.numBytes);
            // parse attributes
            uint8_t attributesBuffer[attributesTLV.value.numBytes];
            HAPRawBufferCopyBytes(attributesBuffer, &attributesTLV.value.bytes[0], attributesTLV.value.numBytes);
            HAPTLVReaderRef attributesReader;
            HAPTLVReaderCreateWithOptions(
                    &attributesReader,
                    &(const HAPTLVReaderOptions) { .bytes = attributesBuffer,
                                                   .numBytes = sizeof attributesBuffer,
                                                   .maxBytes = sizeof attributesBuffer });
            HAPTLV imageWidth, imageHeight, frameRate;
            imageWidth.type = 1;
            imageHeight.type = 2;
            frameRate.type = 3;
            err = HAPTLVReaderGetAll(&attributesReader, (HAPTLV* const[]) { &imageWidth, &imageHeight, &frameRate, NULL
       }); HAPAssert(!err); uint16_t width = ((const uint16_t*) imageWidth.value.bytes)[0]; uint16_t height = ((const
       uint16_t*) imageHeight.value.bytes)[0]; uint8_t framerate = ((const uint8_t*) frameRate.value.bytes)[0];
            HAPLogDebug(
                    &kHAPLog_Default,
                    "tlv type: %d\ntlv size: %lu\nwidth: %u\n",
                    imageWidth.type,
                    imageWidth.value.numBytes,
                    width);
            HAPLogDebug(
                    &kHAPLog_Default,
                    "tlv type: %d\ntlv size: %lu\nheight: %u\n",
                    imageHeight.type,
                    imageHeight.value.numBytes,
                    height);
            HAPLogDebug(
                    &kHAPLog_Default,
                    "tlv type: %d\ntlv size: %lu\nrate: %u\n",
                    frameRate.type,
                    frameRate.value.numBytes,
                    framerate);
        }
        return err;
        // return kHAPError_None;
     */
    /**
     * @brief This kinda works.  But, at this point, just figure out the HAP_STRUCT stuff.  It feels
     * like there may be problems with arrays of TLV's vice just adding a TLV and letting the writer
     * figure it out.
     *

        const HAPTLV videoCodecTypeTLV = { .type = 1, .value = { .bytes = (uint8_t[]) { 0 }, .numBytes = 1 } };

        const HAPTLV* codecParams[] = {
            &(const HAPTLV) { .type = 1, .value = { .bytes = (uint8_t[]) { 1 }, .numBytes = 1 } }, // profileId
            &(const HAPTLV) { .type = 2, .value = { .bytes = (uint8_t[]) { 2 }, .numBytes = 1 } }, // level
            &(const HAPTLV) { .type = 3, .value = { .bytes = (uint8_t[]) { 0 }, .numBytes = 1 } }, // packetMode
            NULL
        };

        const HAPTLV* attr1080[] = {
            &(const HAPTLV) { .type = 1, .value = { .bytes = (uint16_t[]) { 1920 }, .numBytes = 2 } }, // Width
            &(const HAPTLV) { .type = 2, .value = { .bytes = (uint16_t[]) { 1080 }, .numBytes = 2 } }, // Height
            &(const HAPTLV) { .type = 3, .value = { .bytes = (uint8_t[]) { 30 }, .numBytes = 1 } },    // Framerate
            NULL
        };

        const HAPTLV videoCVOEnabledTLV = { .type = 4, .value = { .bytes = (uint8_t[]) { 0 }, .numBytes = 1 } };

        HAPTLVWriterRef attributesWriter;
        uint8_t bytesAttributes[2048];
        HAPTLVWriterCreate(&attributesWriter, bytesAttributes, sizeof bytesAttributes);

        // Write Codec TLV items.
        for (const HAPTLV* const* tlvItem = attr1080; *tlvItem; tlvItem++) {
            err = HAPTLVWriterAppend(&attributesWriter, *tlvItem);
            HAPAssert(!err);
        }

        // Get buffer.
        void* attributesBytes;
        size_t numAttributesBytes;
        HAPTLVWriterGetBuffer(&attributesWriter, &attributesBytes, &numAttributesBytes);

        const HAPTLV videoCodecAttributesTLV = { .type = 3,
                                                 .value = { .bytes = attributesBytes, .numBytes = numAttributesBytes
     }
     };

        HAPTLVWriterRef paramsWriter;
        uint8_t bytesParams[2048];
        HAPTLVWriterCreate(&paramsWriter, bytesParams, sizeof bytesParams);

        // Write Codec TLV items.
        for (const HAPTLV* const* tlvItem = codecParams; *tlvItem; tlvItem++) {
            err = HAPTLVWriterAppend(&paramsWriter, *tlvItem);
            HAPAssert(!err);
        }

        // Get buffer.
        void* paramsBytes;
        size_t numParamsBytes;
        HAPTLVWriterGetBuffer(&paramsWriter, &paramsBytes, &numParamsBytes);

        const HAPTLV videoCodecParamsTLV = { .type = 2,
                                             .value = { .bytes = paramsBytes, .numBytes = numParamsBytes } }; //
     type 2

        HAPTLVWriterRef configWriter;
        uint8_t bytesConfig[2048];
        HAPTLVWriterCreate(&configWriter, bytesConfig, sizeof bytesConfig);

        // Get buffer.
        void* configBytes;
        size_t numConfigBytes;
        HAPTLVWriterGetBuffer(&configWriter, &configBytes, &numConfigBytes);

        err = HAPTLVWriterAppend(&configWriter, &videoCodecTypeTLV);
        HAPAssert(!err);

        err = HAPTLVWriterAppend(&configWriter, &videoCodecParamsTLV);
        HAPAssert(!err);

        err = HAPTLVWriterAppend(&configWriter, &videoCodecAttributesTLV);
        HAPAssert(!err);

        err = HAPTLVWriterAppend(&configWriter, &videoCVOEnabledTLV);
        HAPAssert(!err);

        // Get buffer.
        void* codecConfigBytes;
        size_t numCodecConfigBytes;
        HAPTLVWriterGetBuffer(&configWriter, &codecConfigBytes, &numCodecConfigBytes);

        const HAPTLV videoCodecConfigTLV = { .type = 1,
                                             .value = { .bytes = codecConfigBytes, .numBytes = numCodecConfigBytes }
     };
        // type videoCodecTypeTLV type 1
        // parameters videoCodecParamsTLV type 2
        // attributes videoCodecAttributesTLV type 3
        // CVO Enabled videoCVOEnabledTLV type 4

        HAPTLVWriterRef responseWriter;

        // const HAPTLV videoCodecConfigTLV = { .type = 1, .value = { .bytes = outBuffer, .numBytes = outBufferSize
     } };

        uint8_t bytes[2048];
        HAPTLVWriterCreate(&responseWriter, bytes, sizeof bytes);

        //---------------------------------------------------------------------------------------------

        err = HAPTLVWriterAppend(&responseWriter, &videoCodecConfigTLV);
        HAPAssert(!err);

        void* actualBytes;
        size_t numActualBytes;
        HAPTLVWriterGetBuffer(&responseWriter, &actualBytes, &numActualBytes);

        HAPTLVReaderRef reader;
        HAPTLVReaderCreateWithOptions(
                &reader,
                &(const HAPTLVReaderOptions) {
                        .bytes = actualBytes, .numBytes = numActualBytes, .maxBytes = numActualBytes });

        HAPTLV tlv;
        bool valid = false;

        err = HAPTLVReaderGetNext(&reader, &valid, &tlv);
        HAPAssert(!err);
        HAPAssert(valid);

        HAPTLV buffer[512];
        HAPRawBufferCopyBytes(buffer, &tlv.value.bytes[0], tlv.value.numBytes);

        if (tlv.type == 1) {
            HAPTLVReaderRef codecReader;
            HAPTLVReaderCreateWithOptions(
                    &codecReader,
                    &(const HAPTLVReaderOptions) {
                            .bytes = &buffer, .numBytes = tlv.value.numBytes, .maxBytes = tlv.value.numBytes });

            bool tlvFound = false;
            HAPTLV jtlv;
            do {
                err = HAPTLVReaderGetNext(&codecReader, &tlvFound, &jtlv);
                HAPAssert(!err);
                if (tlvFound) {
                    HAPTLVReaderRef attributesReader;
                    bool attrTLVfound = false;
                    HAPTLV attrTLV;
                    HAPTLV attrTLVbuffer[512];
                    HAPRawBufferCopyBytes(attrTLVbuffer, &jtlv.value.bytes[0], jtlv.value.numBytes);
                    switch (jtlv.type) {
                        default:
                            break;
                        case 1:
                            HAPLogInfo(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", jtlv.type,
     jtlv.value.numBytes); break; case 2: HAPLogInfo(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", jtlv.type,
     jtlv.value.numBytes); break; case 3: HAPTLVReaderCreateWithOptions( &attributesReader,
                                    &(const HAPTLVReaderOptions) { .bytes = &attrTLVbuffer,
                                                                   .numBytes = jtlv.value.numBytes,
                                                                   .maxBytes = jtlv.value.numBytes });
                            do {
                                err = HAPTLVReaderGetNext(&attributesReader, &attrTLVfound, &attrTLV);
                                HAPAssert(!err);
                                if (attrTLVfound) {
                                    HAPLogInfo(
                                            &kHAPLog_Default,
                                            "tlv type: %d\ntlv size: %lu\n",
                                            jtlv.type,
                                            jtlv.value.numBytes);
                                }

                            } while (attrTLVfound);
                            HAPLogInfo(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", jtlv.type,
     jtlv.value.numBytes); break; case 4: HAPLogInfo(&kHAPLog_Default, "tlv type: %d\ntlv size: %lu\n", jtlv.type,
     jtlv.value.numBytes); break;
                    }
                };
            } while (tlvFound);
            return kHAPError_None;
        };
    */

    /**
     * @brief this works but needs optimized.
     *
        const HAPTLV nestedTLV = { .type = 4, .value = { .bytes = (uint16_t[]) { 1234 }, .numBytes = 2 } };
        const HAPTLV nested2TLV = { .type = 5, .value = { .bytes = (uint16_t[]) { 4321 }, .numBytes = 2 } };

        HAPTLVWriterRef nestedWriter;

        uint8_t nestedBytes[2048];
        HAPTLVWriterCreate(&nestedWriter, nestedBytes, sizeof nestedBytes);

        err = HAPTLVWriterAppend(&nestedWriter, &nestedTLV);
        HAPAssert(!err);

        err = HAPTLVWriterAppend(&nestedWriter, &nested2TLV);
        HAPAssert(!err);

        void* outBuffer;
        size_t outBufferSize;

        HAPTLVWriterGetBuffer(&nestedWriter, &outBuffer, &outBufferSize);

    //---------------------------------------------------------------------------------------------

        HAPTLVWriterRef responseWriter;

        const HAPTLV videoCodecConfigTLV = { .type = 1, .value = { .bytes = outBuffer, .numBytes = outBufferSize }
    };

        uint8_t bytes[2048];
        HAPTLVWriterCreate(&responseWriter, bytes, sizeof bytes);

    //---------------------------------------------------------------------------------------------

        err = HAPTLVWriterAppend(&responseWriter, &videoCodecConfigTLV);
        HAPAssert(!err);

        void* actualBytes;
        size_t numActualBytes;
        HAPTLVWriterGetBuffer(&responseWriter, &actualBytes, &numActualBytes);

        HAPTLVReaderRef reader;
        HAPTLVReaderCreateWithOptions(
                &reader,
                &(const HAPTLVReaderOptions) {
                        .bytes = actualBytes, .numBytes = numActualBytes, .maxBytes = numActualBytes });

        HAPTLV tlv;
        bool valid = false;

        err = HAPTLVReaderGetNext(&reader, &valid, &tlv);
        HAPAssert(!err);
        HAPAssert(valid);

        HAPTLV buffer[512];
        HAPRawBufferCopyBytes(buffer, &tlv.value.bytes[0], tlv.value.numBytes);

        if (tlv.type == 1) {
            HAPTLVReaderRef codecReader;
            HAPTLVReaderCreateWithOptions(
                    &codecReader,
                    &(const HAPTLVReaderOptions) {
                            .bytes = &buffer, .numBytes = tlv.value.numBytes, .maxBytes = tlv.value.numBytes });

            bool tlvFound = false;
            HAPTLV jtlv;
            do {
                err = HAPTLVReaderGetNext(&codecReader, &tlvFound, &jtlv);
                HAPAssert(!err);
                if ((jtlv.type == 4 || jtlv.type == 5) && tlvFound) {
                    uint16_t number[1];
                    HAPRawBufferCopyBytes(number, &jtlv.value.bytes[0], jtlv.value.numBytes);
                    HAPLogInfo(
                            &kHAPLog_Default,
                            "type: %d\nlength: %lu\nvalue: %u\n",
                            jtlv.type,
                            jtlv.value.numBytes,
                            number[0]);
                }
            } while (tlvFound);
            return kHAPError_None;
        };
        */
};
#if __has_feature(nullability)
#pragma clang assume_nonnull end
#endif

#ifdef __cplusplus
}
#endif