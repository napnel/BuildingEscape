#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Actor.h"
#include "Math/UnrealMathUtility.h"
#include "OpenDoor.h"

inline void Debug(const FString& str)
{
	UE_LOG(LogTemp, Warning, TEXT("My Debug function: %s"), *str);
}

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	CurrentYaw = InitialYaw;

	TargetYaw += InitialYaw; 

	if(!PressurePlate)
	{
		Debug(GetOwner()->GetName());
		UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetName());
	}

	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	// UE_LOG(LogTemp, Warning, TEXT("%s"), *GetOwner()->GetActorRotation().ToString());
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Nullptrのときfalse
	if(PressurePlate)
	{
		if (PressurePlate->IsOverlappingActor(ActorThatOpen))
		{
			OpenDoor(DeltaTime);
			OpenDoorTime = GetWorld()->GetTimeSeconds();
		}
		else
		{
			if(GetWorld()->GetTimeSeconds() - OpenDoorTime >= DoorClosedDelayTime)
			{
				CloseDoor(DeltaTime);
			}
		}
	}
	// UE_LOG(LogTemp, Warning, TEXT("%f"), FMath::Lerp(CurrentRotation.Yaw, TargetYaw, 0.025f));
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, TargetYaw, DeltaTime * OpenDoorSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	CurrentYaw = FMath::Lerp(CurrentYaw, InitialYaw, DeltaTime * CloseDoorSpeed);
	FRotator DoorRotation = GetOwner()->GetActorRotation();
	DoorRotation.Yaw = CurrentYaw;
	GetOwner()->SetActorRotation(DoorRotation);
}