// Fill out your copyright notice in the Description page of Project Settings.

#include "CairoFunctionLibrary.h"
#include "CairoContext.h"
#include "Engine/Texture2D.h"

UCairoContext *UCairoFunctionLibrary::InitCairoSurface(UObject *WorldContextObject, int Width, int Height)
{
	UCairoContext &Context = *NewObject<UCairoContext>(WorldContextObject);
	Context.Width = Width;
	Context.Height = Height;

	int stride = cairo_format_stride_for_width(CAIRO_FORMAT_ARGB32, Context.Width);

	Context.Size = stride * Context.Height;
	Context.data = (unsigned char *)FMemory::Malloc(Context.Size);
	cairo_surface_t *surface =
	    cairo_image_surface_create_for_data(Context.data, CAIRO_FORMAT_ARGB32, Context.Width, Context.Height, stride);
	Context.ctx = cairo_create(surface);

	Context.bIsInitialized = true;
	Context.Texture = UTexture2D::CreateTransient(Context.Width, Context.Height);
	Context.Texture->MipGenSettings = TextureMipGenSettings::TMGS_NoMipmaps;
	Context.Texture->SRGB = 0;

	return &Context;
}

void UCairoFunctionLibrary::RefreshContextTexture(UCairoContext *Context)
{
	if (Context->Texture == nullptr)
	{
		return;
	}
	FTexture2DMipMap &Mip = Context->Texture->PlatformData->Mips[0];
	void *Data = Mip.BulkData.Lock(LOCK_READ_WRITE);
	FMemory::Memcpy(Data, Context->data, Context->Size);
	Mip.BulkData.Unlock();
	Context->Texture->UpdateResource();
}

void UCairoFunctionLibrary::DestroyContext(UCairoContext *Context)
{
	Context->Cleanup();
}

void UCairoFunctionLibrary::SetSourceRGBA(UCairoContext *Context, const FLinearColor& RGBA)
{
	cairo_set_source_rgba(Context->ctx, RGBA.R, RGBA.G, RGBA.B, RGBA.A);
}

void UCairoFunctionLibrary::SetSourceRGB(UCairoContext *Context, float Red, float Green, float Blue)
{
	cairo_set_source_rgb(Context->ctx, Red, Green, Blue);
}

void UCairoFunctionLibrary::Paint(UCairoContext *Context)
{
	cairo_paint(Context->ctx);
}

void UCairoFunctionLibrary::SetFontSize(UCairoContext *Context, float Size)
{
	cairo_set_font_size(Context->ctx, Size);
}

void UCairoFunctionLibrary::MoveTo(UCairoContext *Context, const FVector2D& Position)
{
	cairo_move_to(Context->ctx, Position.X, Position.Y);
}

void UCairoFunctionLibrary::ShowText(UCairoContext *Context, const FString &Text)
{
	cairo_show_text(Context->ctx, TCHAR_TO_UTF8(*Text));
}

void UCairoFunctionLibrary::LineTo(UCairoContext *Context, const FVector2D& Position)
{
	cairo_line_to(Context->ctx, Position.X, Position.Y);
}

void UCairoFunctionLibrary::Rectangle(UCairoContext *Context, const FVector2D& XY, const FVector2D& Size)
{
	cairo_rectangle(Context->ctx, XY.X, XY.Y, Size.X, Size.Y);
}

void UCairoFunctionLibrary::Arc(UCairoContext *Context, const FVector2D& Center, float Radius, float Angle1,
                                float Angle2)
{
	cairo_arc(Context->ctx, Center.X, Center.Y, Radius, Angle1, Angle2);
}

void UCairoFunctionLibrary::ArcNegative(UCairoContext *Context, const FVector2D& Center,  float Radius,
                                        float Angle1, float Angle2)
{
	cairo_arc_negative(Context->ctx, Center.X, Center.Y, Radius, Angle1, Angle2);
}

void UCairoFunctionLibrary::Fill(UCairoContext *Context)
{
	cairo_fill(Context->ctx);
}

void UCairoFunctionLibrary::Stroke(UCairoContext *Context)
{
	cairo_stroke(Context->ctx);
}

void UCairoFunctionLibrary::NewSubPath(UCairoContext *Context)
{
	cairo_new_sub_path(Context->ctx);
}

void UCairoFunctionLibrary::ClosePath(UCairoContext *Context)
{
	cairo_close_path(Context->ctx);
}

void UCairoFunctionLibrary::SelectFontFace(UCairoContext *Context, const FString &Family, EFontSlant Slant,
                                           EFontWeight Weight)
{
	cairo_font_slant_t CairoFontSlant;
	cairo_font_weight_t CairoFontWeight;
	switch (Slant)
	{
	case EFontSlant::FONT_SLANT_ITALIC:
		CairoFontSlant = CAIRO_FONT_SLANT_ITALIC;
		break;
	case EFontSlant::FONT_SLANT_OBLIQUE:
		CairoFontSlant = CAIRO_FONT_SLANT_OBLIQUE;
		break;
	case EFontSlant::FONT_SLANT_NORMAL:
	default:
		CairoFontSlant = CAIRO_FONT_SLANT_NORMAL;
		break;
	}

	switch (Weight)
	{
	case EFontWeight::FONT_FONT_WEIGHT_BOLD:
		CairoFontWeight = CAIRO_FONT_WEIGHT_BOLD;
		break;
	case EFontWeight::FONT_FONT_WEIGHT_NORMAL:
	default:
		CairoFontWeight = CAIRO_FONT_WEIGHT_NORMAL;
		break;
	}
	cairo_select_font_face(Context->ctx, TCHAR_TO_ANSI(*Family), CairoFontSlant, CairoFontWeight);
}

FVector2D UCairoFunctionLibrary::TextExtents(UCairoContext *Context, const FString &Text)
{
	cairo_text_extents_t CairoTextExtents;
	cairo_text_extents(Context->ctx, TCHAR_TO_UTF8(*Text), &CairoTextExtents);
	return FVector2D(CairoTextExtents.width, CairoTextExtents.height);
}

void UCairoFunctionLibrary::SetOperator(UCairoContext *Context, ECairoOperator Operator)
{
	check(false);
}

void UCairoFunctionLibrary::SetTolerance(UCairoContext *Context, float Tolerance)
{
	cairo_set_tolerance(Context->ctx, Tolerance);
}

void UCairoFunctionLibrary::SetAntialias(UCairoContext *Context, ECairoAntialias Antialias)
{
	check(false);
}

void UCairoFunctionLibrary::SetFillRule(UCairoContext *Context, EFillRule FillRule)
{
	check(false);
}

void UCairoFunctionLibrary::SetLineWidth(UCairoContext *Context, float Width)
{
	cairo_set_line_width(Context->ctx, Width);
}

void UCairoFunctionLibrary::SetLineCap(UCairoContext *Context, ELineCap LineCap)
{
	check(false);
}

void UCairoFunctionLibrary::SetLineJoin(UCairoContext *Context, ELineJoin LineJoin)
{
	check(false);
}

void UCairoFunctionLibrary::SetDash(UCairoContext *Context, const TArray<float> &Dashes, int NumDashes, float Offset)
{
	check(false);
}

void UCairoFunctionLibrary::SetMiterLimit(UCairoContext *Context, float Limit)
{
	cairo_set_miter_limit(Context->ctx, Limit);
}

void UCairoFunctionLibrary::Translate(UCairoContext *Context, const FVector2D &Translation)
{
	cairo_translate(Context->ctx, Translation.X, Translation.Y);
}

void UCairoFunctionLibrary::Scale(UCairoContext *Context, const FVector2D &Scale)
{

	cairo_scale(Context->ctx, Scale.X, Scale.Y);
}

void UCairoFunctionLibrary::Rotate(UCairoContext *Context, float Angle)
{
	cairo_rotate(Context->ctx, Angle);
}
