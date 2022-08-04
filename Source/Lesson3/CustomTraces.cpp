// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTraces.h"

bool UCustomTraces::CustomLineTraceByChannel(const UObject* WorldContextObject, FVector Start, FVector End, FHitResult& OutHit)
{
	FCollisionQueryParams TraceParams; 

	//Игнорируем объект-владелец при трейсе
	TraceParams.AddIgnoredActor(Cast<AActor>(WorldContextObject));

	//Запоминаем ссылку на текущий World объекта-владельца
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	//Осуществляем трейс -> записываем результат в bHit ->true
	bool const bHit = World ? World->LineTraceSingleByChannel(
		OutHit,
		Start,
		End,
		ECC_Visibility,
		TraceParams) : false;

	//Визуализируем трейс для отладки
	//Если есть попадание - рисуем линии 
	if (bHit && OutHit.bBlockingHit)
	{
		//Линия от старта трейса до попадания
		::DrawDebugLine(World, Start, OutHit.ImpactPoint,FColor::Cyan, true, 2.5f);
		//Линия от попадания до конца трейса
		::DrawDebugLine(World, OutHit.ImpactPoint, End, FColor::Black, true, 2.5f);
		//Точка в месте попадания
		::DrawDebugPoint(World, OutHit.ImpactPoint, 50.0f, FColor::Green, true, 2.5f);
	}
	else
	{
		//Если попадания нет - одна линия от старта до конца трейса
		::DrawDebugLine(World, Start, End, FColor::Red, true, 2.5f);
	}
	
	
	return bHit;
}

bool UCustomTraces::CustomMultiLineTraceByChannel(const UObject* WorldContextObject, FVector Start, FVector End, TArray<FHitResult>& OutHits)
{

	FCollisionQueryParams TraceParams;

	//Игнорируем объект-владелец при трейсе
	TraceParams.AddIgnoredActor(Cast<AActor>(WorldContextObject));

	//Запоминаем ссылку на текущий World объекта-владельца
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	//Осуществляем трейс -> записываем результат в bHit ->true
	bool const bHit = World ? World->LineTraceMultiByChannel(
		OutHits,
		Start,
		End,
		ECC_Visibility,
		TraceParams) : false;

	//Визуализируем трейс для отладки
	if (bHit && OutHits.Last().bBlockingHit)
	{
		//Отрисовываем линии до и после столкновения
		FVector const BlockingHitPoint = OutHits.Last().ImpactPoint;
		::DrawDebugLine(World, Start, BlockingHitPoint, FColor::Cyan, true, 2.5f);
		::DrawDebugLine(World, BlockingHitPoint, End, FColor::Black, true, 2.5f);
	}
	else
	{
		//Если столкновения не обнаружена - линия одна.
		::DrawDebugLine(World, Start, End, FColor::Red, true, 2.5f);
	}

	// Отрисовываем точки столкновения
	for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
	{
		FHitResult const& Hit = OutHits[HitIdx];
		::DrawDebugPoint(World, Hit.ImpactPoint, 50.0f, (Hit.bBlockingHit ? FColor::Green : FColor::Blue), true, 2.5f);
	}

	return bHit;
}
