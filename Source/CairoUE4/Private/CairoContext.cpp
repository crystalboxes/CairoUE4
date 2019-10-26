// Fill out your copyright notice in the Description page of Project Settings.

#include "CairoContext.h"

#include <cairo/cairo.h>

void UCairoContext::BeginDestroy()
{
	Super::BeginDestroy();
	if (!bIsInitialized)
	{
		return;
	}
	else
	{
		Cleanup();
	}
}

void UCairoContext::Cleanup()
{
	check(ctx);
	check(data);

	cairo_destroy(ctx);
	FMemory::Free(data);
	ctx = nullptr;
	data = nullptr;
	Texture = nullptr;
}
