// Copyright Epic Games, Inc. All Rights Reserved.

#include "BCScoder.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>


template <typename T>
std::vector<uint8_t> FBCSencoderModule::encodeUnsignedInt(T value) {
    std::vector<uint8_t> bytes;
    size_t size = sizeof(T);
    for (size_t i = 0; i < size; ++i) {
        bytes.push_back(static_cast<uint8_t>(value >> (i * 8)));
    }
    return bytes;
}


template <typename T>
T FBCSencoderModule::decodeUnsignedInt(const std::vector<uint8_t>& bytes) {
    if (bytes.size() != sizeof(T)) {
        throw std::runtime_error("Incorrect size for decoding unsigned integer.");
    }
    T value = 0;
    for (size_t i = 0; i < bytes.size(); ++i) {
        value |= static_cast<T>(bytes[i]) << (i * 8);
    }
    return value;
}


void runAllTests() {
    FBCSencoderModule encoder;

    //u8
    uint8_t u8Value = 42;
    std::vector<uint8_t> u8Bytes = encoder.encodeUnsignedInt(u8Value);
    uint8_t decodedU8Value = encoder.decodeUnsignedInt<uint8_t>(u8Bytes);
    assert(u8Value == decodedU8Value);

    //u16
    uint16_t u16Value = 12345;
    std::vector<uint8_t> u16Bytes = encoder.encodeUnsignedInt(u16Value);
    uint16_t decodedU16Value = encoder.decodeUnsignedInt<uint16_t>(u16Bytes);
    assert(u16Value == decodedU16Value);

    //u32
    uint32_t u32Value = 1234567890;
    std::vector<uint8_t> u32Bytes = encoder.encodeUnsignedInt(u32Value);
    uint32_t decodedU32Value = encoder.decodeUnsignedInt<uint32_t>(u32Bytes);
    assert(u32Value == decodedU32Value);

    //u64
    uint64_t u64Value = 12345678901234567890ULL;
    std::vector<uint8_t> u64Bytes = encoder.encodeUnsignedInt(u64Value);
    uint64_t decodedU64Value = encoder.decodeUnsignedInt<uint64_t>(u64Bytes);
    assert(u64Value == decodedU64Value);
}

int main() {
    runAllTests();

    return 0;
}