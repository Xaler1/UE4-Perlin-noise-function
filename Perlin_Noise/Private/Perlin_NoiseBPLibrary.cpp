// Copyright Epic Games, Inc. All Rights Reserved.

#include "Perlin_NoiseBPLibrary.h"
#include "Perlin_Noise.h"
#include "stdlib.h"
#include "time.h"

float coefs[11];

UPerlin_NoiseBPLibrary::UPerlin_NoiseBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
	srand(time(NULL));
	for (int i = 0; i < 11; i++) {
		coefs[i] = rand() * 1000;
	}
}

float Interpolate(float a, float b, float x);
float Fade(float t);
float dotGradient(int X, float x, int Y = 0, float y = 0, int Z = 0, float z = 0, int W = 0, float w = 0);
FVector4 Random(int X, int Y, int Z, int W);


float UPerlin_NoiseBPLibrary::OneD_Perlin_Noise(float x, float wavelength = 1, float amplitude = 1)
{
	x /= wavelength;
	int xL = floor(x);
	int xU = xL + 1;

	float dx = Fade(x - xL);
	return Interpolate(dotGradient(xL, x), dotGradient(xU, x), dx) * amplitude;
}

float UPerlin_NoiseBPLibrary::TwoD_Perlin_Noise(float x, float y, float wavelength = 1, float amplitude = 1)
{
	x /= wavelength;
	y /= wavelength;
	int xL = floor(x);
	int xU = xL + 1;
	int yL = floor(y);
	int yU = yL + 1;

	float dx = Fade(x - xL);
	float dy = Fade(y - yL);

	return Interpolate(Interpolate(dotGradient(xL, x, yL, y), dotGradient(xU, x, yL, y), dx),
		Interpolate(dotGradient(xL, x, yU, y), dotGradient(xU, x, yU, y), dx), dy) * amplitude;
}

float UPerlin_NoiseBPLibrary::ThreeD_Perlin_Noise(float x, float y, float z, float wavelength = 1, float amplitude = 1)
{
	x /= wavelength;
	y /= wavelength;
	z /= wavelength;
	int xL = floor(x);
	int xU = xL + 1;
	int yL = floor(y);
	int yU = yL + 1;
	int zL = floor(z);
	int zU = zL + 1;

	float dx = Fade(x - xL);
	float dy = Fade(y - yL);
	float dz = Fade(z - zL);

	return Interpolate(Interpolate(Interpolate(dotGradient(xL, x, yL, y, zL, z), dotGradient(xU, x, yL, y, zL, z), dx),
								   Interpolate(dotGradient(xL, x, yU, y, zL, z), dotGradient(xU, x, yU, y, zL, z), dx), dy),
					   Interpolate(Interpolate(dotGradient(xL, x, yL, y, zU, z), dotGradient(xU, x, yL, y, zU, z), dx),
								   Interpolate(dotGradient(xL, x, yU, y, zU, z), dotGradient(xU, x, yU, y, zU, z), dx), dy), dz) * amplitude;
}

float UPerlin_NoiseBPLibrary::FourD_Perlin_Noise(float x, float y, float z, float w, float wavelength = 1, float amplitude = 1) {
	x /= wavelength;
	y /= wavelength;
	z /= wavelength;
	w /= wavelength;
	int xL = floor(x);
	int xU = xL + 1;
	int yL = floor(y);
	int yU = yL + 1;
	int zL = floor(z);
	int zU = zL + 1;
	int wL = floor(w);
	int wU = wL + 1;

	float dx = Fade(x - xL);
	float dy = Fade(y - yL);
	float dz = Fade(z - zL);
	float dw = Fade(w - wL);

	return Interpolate(Interpolate(Interpolate(Interpolate(dotGradient(xL, x, yL, y, zL, z, wL, w), dotGradient(xU, x, yL, y, zL, z, wL, w), dx),
		Interpolate(dotGradient(xL, x, yU, y, zL, z, wL, w), dotGradient(xU, x, yU, y, zL, z, wL, w), dx), dy),
		Interpolate(Interpolate(dotGradient(xL, x, yL, y, zU, z, wL, w), dotGradient(xU, x, yL, y, zU, z, wL, w), dx),
			Interpolate(dotGradient(xL, x, yU, y, zU, z, wL, w), dotGradient(xU, x, yU, y, zU, z, wL, w), dx), dy), dz),
		Interpolate(Interpolate(Interpolate(dotGradient(xL, x, yL, y, zL, z, wU, w), dotGradient(xU, x, yL, y, zL, z, wU, w), dx),
			Interpolate(dotGradient(xL, x, yU, y, zL, z, wU, w), dotGradient(xU, x, yU, y, zL, z, wU, w), dx), dy),
			Interpolate(Interpolate(dotGradient(xL, x, yL, y, zU, z, wU, w), dotGradient(xU, x, yL, y, zU, z, wU, w), dx),
				Interpolate(dotGradient(xL, x, yU, y, zU, z, wU, w), dotGradient(xU, x, yU, y, zU, z, wU, w), dx), dy), dz), dw) * amplitude;
}

void UPerlin_NoiseBPLibrary::SetSeed(int seed) {
	srand(seed);
	for (int i = 0; i < 11; i++) {
		coefs[i] = rand() * 1000;
	}
}

FVector4 Random(int X, int Y, int Z, int W) {
	float seed = coefs[0] * sin(coefs[1] * X + coefs[2] * Y + coefs[3] * Z + coefs[4] * W + coefs[5]) * tan(coefs[6] * X + coefs[7] * Y + coefs[8] * Z + coefs[9] * W + coefs[10]);
	srand(seed);
	FVector4 random_vector = FVector4(rand(), rand(), rand(), rand());
	return random_vector / random_vector.Size();
}

float Interpolate(float a, float b, float x) {
	float t = x * PI;
	float f = (1 - cos(t)) * 0.5;
	return a * (1 - f) + b * f;
}

float Fade(float t) {
	return t * t * t * (t * (t * 6 - 15) + 10);
}

float dotGradient(int X, float x, int Y, float y, int Z, float z, int W, float w) {
	FVector4 random_vector = Random(X, Y, Z, W);
	float dx = x - X;
	float dy = y - Y;
	float dz = z - Z;
	float dw = w - W;
	return dx * random_vector.X + dy * random_vector.Y + dz * random_vector.Z + dw * random_vector.W;
}
