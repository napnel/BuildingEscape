
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "CollisionQueryParams.h"
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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Find PhysicsHandle"));
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if(!InputComponent)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Find InputComponent"));
	}
	else
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
}

void UGrabber::Grab()
{
	DEBUG("Grab Function is executed");
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
	// DEBUG(GetVariableName(PlayerViewPointLocation), PlayerViewPointLocation.ToString());
	// DEBUG(GetVariableName(PlayerViewPointRotation), PlayerViewPointRotation.ToString());

	//プレイヤーが見ている方向からReachの分だけ線を見えるようにする。
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0.f, 5.f);

	//LineTraceEnd内に入るオブジェクトの情報を取得する。
	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, PlayerViewPointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);
	AActor* HitActor = Hit.GetActor();
	if(HitActor)
	{
		DEBUG(Hit.GetActor()->GetName());
	}
}

