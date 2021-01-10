// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Perlin_NoiseBPLibrary.generated.h"

/* 
*	Function library class.
*	Each function in it is expected to be static and represents blueprint node that can be called in any blueprint.
*
*	When declaring function you can define metadata for the node. Key function specifiers will be BlueprintPure and BlueprintCallable.
*	BlueprintPure - means the function does not affect the owning object in any way and thus creates a node without Exec pins.
*	BlueprintCallable - makes a function which can be executed in Blueprints - Thus it has Exec pins.
*	DisplayName - full name of the node, shown when you mouse over the node and in the blueprint drop down menu.
*				Its lets you name the node using characters not allowed in C++ function names.
*	CompactNodeTitle - the word(s) that appear on the node.
*	Keywords -	the list of keywords that helps you to find node when you search for it using Blueprint drop-down menu. 
*				Good example is "Print String" node which you can find also by using keyword "log".
*	Category -	the category your node will be under in the Blueprint drop-down menu.
*
*	For more info on custom blueprint nodes visit documentation:
*	https://wiki.unrealengine.com/Custom_Blueprint_Node_Creation
*/
UCLASS()
class UPerlin_NoiseBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_UCLASS_BODY()

	UFUNCTION(BlueprintPure, meta = (DisplayName = "1D Perlin Noise", Keywords = "One 1D Perlin_Noise perlin noise Perlin Noise", 
		ToolTip = "Sample 1D perlin noise at the given X coordinate"), Category = "Perlin_Noise")
	static float OneD_Perlin_Noise(const float x, const float scale = 1, const float amplitude = 1);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "2D Perlin Noise", Keywords = "Two 2D Perlin_Noise perlin noise Perlin Noise",
		ToolTip = "Sample 2D perlin noise at the given X,Y coordinate"), Category = "Perlin_Noise")
	static float TwoD_Perlin_Noise(const float x, const float y, const float scale = 1, const float amplitude = 1);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "3D Perlin Noise", Keywords = "Three 3D Perlin_Noise perlin noise Perlin Noise", 
		ToolTip = "Sample 3D perlin noise at the given X,Y,Z coordinate"), Category = "Perlin_Noise")
	static float ThreeD_Perlin_Noise(const float x, const float y, const float z, const float scale = 1, const float amplitude = 1);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "4D Perlin Noise", Keywords = "Four 4D Perlin_Noise perlin noise Perlin Noise", 
		ToolTip = "Sample 4D perlin noise at the given X,Y,Z,W coordinate"), Category = "Perlin_Noise")
	static float FourD_Perlin_Noise(const float x, const float y, const float z, const float w, const float scale = 1, const float amplitude = 1);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "1D Perlin Fractal", Keywords = "One 1D Perlin_Noise perlin noise fractal",
		ToolTip = "Sample 1D fractal perlin noise at the given X coordinate", AdvancedDisplay = 4), Category = "Perlin_Noise")
	static float OneD_Perlin_Fractal(const float x, const int levels, float scale = 1, float amplitude = 1, const float ScaleFade = 2, const float AmpFade = 2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "2D Perlin Fractal", Keywords = "Two 2D Perlin_Noise perlin noise fractal", 
		ToolTip = "Sample 2D fractal perlin noise at the given X,Y coordinate", AdvancedDisplay = 5), Category = "Perlin_Noise")
	static float TwoD_Perlin_Fractal(const float x, const float y, const int levels, float scale = 1, float amplitude = 1, const float ScaleFade = 2, const float AmpFade = 2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "3D Perlin Fractal", Keywords = "Three 3D Perlin_Noise perlin noise fractal", 
		ToolTip = "Sample 3D fractal perlin noise at the given X,Y,Z coordinate", AdvancedDisplay = 6), Category = "Perlin_Noise")
	static float ThreeD_Perlin_Fractal(const float x, const float y, const float z, const int levels, float scale = 1, float amplitude = 1, const float ScaleFade = 2, const float AmpFade = 2);

	UFUNCTION(BlueprintPure, meta = (DisplayName = "4D Perlin Fractal", Keywords = "Four 4D Perlin_Noise perlin noise fractal", 
		ToolTip = "Sample 4D fractal perlin noise at the given X,Y,Z,W coordinate", AdvancedDisplay = 7), Category = "Perlin_Noise")
	static float FourD_Perlin_Fractal(const float x, const float y, const float z, const float w, const int levels, float scale = 1, float amplitude = 1, const float ScaleFade = 2, const float AmpFade = 2);

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Set Noise Seed", Keywords = "Set_Seed seed set seed"), Category = "Perlin_Noise")
	static void SetSeed(int seed);
};
