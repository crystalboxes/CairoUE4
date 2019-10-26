// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <cairo/cairo.h>
//
#include "CairoContext.generated.h"

/**
 * 
 */
class UTexture2D;

UCLASS()
class CAIROUE4_API UCairoContext : public UObject
{
	GENERATED_BODY()

public:
	cairo_t *ctx = nullptr;
	unsigned char *data = nullptr;

	UPROPERTY(VisibleAnywhere)
	unsigned int Size = 0;

	UPROPERTY(VisibleAnywhere)
	int Width = 0;

	UPROPERTY(VisibleAnywhere)
	int Height = 0;

	UPROPERTY(VisibleAnywhere)
	bool bIsInitialized = false;

	UPROPERTY(VisibleAnywhere)
	UTexture2D *Texture = nullptr;


	virtual void BeginDestroy() override;

	void Cleanup();
};
