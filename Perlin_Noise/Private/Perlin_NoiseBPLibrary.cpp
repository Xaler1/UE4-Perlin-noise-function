// Copyright Epic Games, Inc. All Rights Reserved.

#include "Perlin_NoiseBPLibrary.h"
#include "Perlin_Noise.h"
#include "stdlib.h"
#include "time.h"

int p[512];

UPerlin_NoiseBPLibrary::UPerlin_NoiseBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	srand(time(NULL));
	for (int i = 0; i < 512; i++) {
		p[i] = rand() % 256 + 1;
	}
}

float Interpolate(float a, float b, float x);
float LinearInterpolate(float a, float b, float x);
float Fade(float t);
float Gradient(int hash, float X);
float Gradient(int hash, float X, float Y);
float Gradient(int hash, float X, float Y, float Z);
float Random();


float UPerlin_NoiseBPLibrary::OneD_Perlin_Noise(float X, float wavelength = 1, float amplitude = 1)
{
	if (wavelength == 0) {
		wavelength = 1;
	}
	X /= wavelength;
	int a = int(floor(X)) & 0xff;
	X -= floor(X);
	return Interpolate(Gradient(p[a], X), Gradient(p[a + 1], X - 1), Fade(X)) * amplitude;
}

float UPerlin_NoiseBPLibrary::TwoD_Perlin_Noise(float X, float Y, float wavelength = 1, float amplitude = 1)
{
	if (wavelength == 0) {
		wavelength = 1;
	}
	X /= wavelength;
	Y /= wavelength;
	int a = int(floor(X)) & 0xff;
	int b = int(floor(Y)) & 0xff;
	X -= floor(X);
	Y -= floor(Y);
	int A = int((p[a] + b)) & 0xff;
	int B = int((p[a + 1] + b)) & 0xff;
	return Interpolate(Interpolate(Gradient(p[A], X, Y), Gradient(p[B], X - 1, Y), Fade(X)),
					   Interpolate(Gradient(p[A+1], X, Y - 1), Gradient(p[B + 1], X - 1, Y - 1), Fade(X)), Fade(Y)) * amplitude;
}

float UPerlin_NoiseBPLibrary::ThreeD_Perlin_Noise(float X, float Y, float Z, float wavelength = 1, float amplitude = 1)
{
	if (wavelength == 0) {
		wavelength = 1;
	}
	X /= wavelength;
	Y /= wavelength;
	Z /= wavelength;
	int a = int(floor(X)) & 0xff;
	int b = int(floor(Y)) & 0xff;
	int c = int(floor(Z)) & 0xff;
	X -= floor(X);
	Y -= floor(Y);
	Z -= floor(Z);
	float u = Fade(X);
	float v = Fade(Y);
	float w = Fade(Z);
	int A = int(p[a] + b) & 0xff;
	int B = int(p[a + 1] + b) & 0xff;
	int AA = int(p[A] + c) & 0xff;
	int BA = int(p[B] + c) & 0xff;
	int AB = int(p[A + 1] + c) & 0xff;
	int BB = int(p[B + 1] + c) & 0xff;
	return Interpolate(Interpolate(Interpolate(Gradient(p[AA], X, Y, Z), Gradient(p[BA], X - 1, Y, Z), u),
								   Interpolate(Gradient(p[AB], X, Y - 1, Z), Gradient(p[BB], X - 1, Y - 1, Z), u), v), 
					   Interpolate(Interpolate(Gradient(p[AA + 1], X, Y, Z - 1), Gradient(p[BA + 1], X - 1, Y, Z - 1), u),
								   Interpolate(Gradient(p[AB + 1], X, Y - 1, Z - 1), Gradient(p[BB + 1], X - 1, Y - 1, Z - 1), u), v), w) * amplitude;
}

void UPerlin_NoiseBPLibrary::SetSeed(int seed) {
	srand(seed);
	for (int i = 0; i < 512; i++) {
		p[i] = rand() % 256 + 1;
	}
}

float Random() {
	long M = 429496796;
	long A = 1664525;
	int C = 1;
	long Z = floor(rand() * M);
	Z = (A * Z + C) % M;
	return Z/M;
}

float Interpolate(float a, float b, float x) {
	float t = x * PI;
	float f = (1 - cos(t)) * 0.5;
	return a * (1 - f) + b * f;
}

float LinearInterpolate(float a, float b, float x) {
	return a + x * (b - a);
}

float Fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float Gradient(int hash, float X) {
	return (hash & 1) == 0 ? X : -X;
}

float Gradient(int hash, float X, float Y) {
	return ((hash & 1) == 0 ? X : -X) + ((hash & 2) == 0 ? Y : -Y);
}

float Gradient(int hash, float X, float Y, float Z) {
	int h = hash & 15;
	float u = h < 8 ? X : Y;
	float v = h < 4 ? Y : (h == 12 || h == 14 ? X : Z);
	return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
