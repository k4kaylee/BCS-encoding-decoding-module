// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <cstdint>

class FBCSencoderModule : public IModuleInterface {
public:

	//Unsigned integers u8, u16, u32, u64
	template <typename T>
	std::vector<uint8_t> encodeUnsignedInt(T value);

	template <typename T>
	T decodeUnsignedInt(const std::vector<uint8_t>& bytes);
};