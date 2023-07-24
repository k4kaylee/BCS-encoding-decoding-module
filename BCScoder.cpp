// Copyright Epic Games, Inc. All Rights Reserved.

#include "BCScoder.h"
#include <vector>
#include <cstdint>
#include <iostream>
#include <cassert>


#include <vector>
#include <cstdint>
#include <sstream>
#include <iostream>
#include <cassert>
#include "../Private/BCScoderModule.h"





void FBCSencoderModule::encode(BCS_value& value) {
    switch (value.type) {
    case BCS_value::BCS_NUMBER: encodeUnsignedInt(value.data.number); break;
    case BCS_value::BCS_STRING: encodeUTF8String(value.data.string); break;

    }
}

//Encoders

template <typename T>
void FBCSencoderModule::encodeUnsignedInt(T value) {
    size_t size = sizeof(T);
    for (size_t i = 0; i < size; ++i) {
        char byte = static_cast<char>(value >> (i * 8));
        _output.write(&byte, 1);
    }
}

void FBCSencoderModule::encodeUTF8String(const std::string& utf8String) {
    _output.write(utf8String.data(), utf8String.size());
}



// Decoders

template <typename T>
T FBCSdecoderModule::decodeUnsignedInt() {
    char bytes[sizeof(T)];
    _input.read(bytes, sizeof(T));
    T value = 0;
    for (size_t i = 0; i < sizeof(T); ++i) {
        value |= static_cast<T>(bytes[i]) << (i * 8);
    }
    return value;
}

std::string FBCSdecoderModule::decode_string() {
    size_t len = read_uleb128();
    std::string str(len, '\0');
    _input.read(const_cast<char*>(str.data()), len);
    return str;
}

template <typename T, typename F>
std::vector<T> FBCSdecoderModule::decodeArray(F reader) {
    size_t len = read_uleb128();
    std::vector<T> data(len);
    for (size_t i = 0; i < len; i++) {
        data[i] = reader(this);
    }
    return data;
}



// Misc

uint64_t FBCSdecoderModule::read_uleb128() {
    uint64_t result = 0;
    int shift = 0;
    uint8_t byte;
    do {
        _input.read(reinterpret_cast<char*>(&byte), 1);
        uint64_t bits = byte & MASK(7);
        result |= bits << shift;
        shift += 7;
    } while ((byte & BIT(7)) == 0);
    return result;
}


// Unit tests
void runAllTests() {
    /* Under reconstruction */
}



int main() {
    //runAllTests();

    return 0;
}
