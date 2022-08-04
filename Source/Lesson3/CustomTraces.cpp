// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomTraces.h"

bool UCustomTraces::CustomLineTraceByChannel(const UObject* WorldContextObject, FVector Start, FVector End, FHitResult& OutHit)
{
	FCollisionQueryParams TraceParams; 

	//���������� ������-�������� ��� ������
	TraceParams.AddIgnoredActor(Cast<AActor>(WorldContextObject));

	//���������� ������ �� ������� World �������-���������
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	//������������ ����� -> ���������� ��������� � bHit ->true
	bool const bHit = World ? World->LineTraceSingleByChannel(
		OutHit,
		Start,
		End,
		ECC_Visibility,
		TraceParams) : false;

	//������������� ����� ��� �������
	//���� ���� ��������� - ������ ����� 
	if (bHit && OutHit.bBlockingHit)
	{
		//����� �� ������ ������ �� ���������
		::DrawDebugLine(World, Start, OutHit.ImpactPoint,FColor::Cyan, true, 2.5f);
		//����� �� ��������� �� ����� ������
		::DrawDebugLine(World, OutHit.ImpactPoint, End, FColor::Black, true, 2.5f);
		//����� � ����� ���������
		::DrawDebugPoint(World, OutHit.ImpactPoint, 50.0f, FColor::Green, true, 2.5f);
	}
	else
	{
		//���� ��������� ��� - ���� ����� �� ������ �� ����� ������
		::DrawDebugLine(World, Start, End, FColor::Red, true, 2.5f);
	}
	
	
	return bHit;
}

bool UCustomTraces::CustomMultiLineTraceByChannel(const UObject* WorldContextObject, FVector Start, FVector End, TArray<FHitResult>& OutHits)
{

	FCollisionQueryParams TraceParams;

	//���������� ������-�������� ��� ������
	TraceParams.AddIgnoredActor(Cast<AActor>(WorldContextObject));

	//���������� ������ �� ������� World �������-���������
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);

	//������������ ����� -> ���������� ��������� � bHit ->true
	bool const bHit = World ? World->LineTraceMultiByChannel(
		OutHits,
		Start,
		End,
		ECC_Visibility,
		TraceParams) : false;

	//������������� ����� ��� �������
	if (bHit && OutHits.Last().bBlockingHit)
	{
		//������������ ����� �� � ����� ������������
		FVector const BlockingHitPoint = OutHits.Last().ImpactPoint;
		::DrawDebugLine(World, Start, BlockingHitPoint, FColor::Cyan, true, 2.5f);
		::DrawDebugLine(World, BlockingHitPoint, End, FColor::Black, true, 2.5f);
	}
	else
	{
		//���� ������������ �� ���������� - ����� ����.
		::DrawDebugLine(World, Start, End, FColor::Red, true, 2.5f);
	}

	// ������������ ����� ������������
	for (int32 HitIdx = 0; HitIdx < OutHits.Num(); ++HitIdx)
	{
		FHitResult const& Hit = OutHits[HitIdx];
		::DrawDebugPoint(World, Hit.ImpactPoint, 50.0f, (Hit.bBlockingHit ? FColor::Green : FColor::Blue), true, 2.5f);
	}

	return bHit;
}
