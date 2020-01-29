
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT
#define GetVariableName(VariableName) # VariableName

inline void DEBUG(const FString& VariableName, const FString& Str)
{
	UE_LOG(LogTemp, Warning, TEXT("%s is %s"), *VariableName, *Str);
}
inline void DEBUG(const FString& Str)
{
	UE_LOG(LogTemp, Warning, TEXT("%s"), *Str);
}

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	// Get players viewpoints
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	DEBUG(GetVariableName(PlayerViewPointLocation), PlayerViewPointLocation.ToString());
	DEBUG(GetVariableName(PlayerViewPointRotation), PlayerViewPointRotation.ToString());
}

