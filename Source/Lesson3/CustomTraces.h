// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
//Добавьте эти библиотеки
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"
#include "Engine/EngineTypes.h"
#include "Math/Color.h"

#include "CustomTraces.generated.h"

UCLASS()
class LESSON3_API UCustomTraces : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

//Объявление функции
	UFUNCTION(BlueprintCallable, Category = "CustomTrace", meta = (WorldContext = "WorldContextObject", DisplayName = "CustomLineTraceByChannel"))
	static bool CustomLineTraceByChannel(const UObject* WorldContextObject, FVector Start, FVector End, FHitResult& OutHit);


	UFUNCTION(BlueprintCallable, Category = "CustomTrace", meta = (WorldContext = "WorldContextObject", DisplayName = "CustomMultiLineTraceByChannel"))
	static bool CustomMultiLineTraceByChannel(const UObject* WorldContextObject, FVector Start, FVector End, TArray<FHitResult>& OutHits);
};
