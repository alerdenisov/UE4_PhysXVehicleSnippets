// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPawn.h"
#include "Engine/CollisionProfile.h"

FName ATankPawn::TankVehicleMeshComponentName(TEXT("TankMesh"));
FName ATankPawn::TankVehicleMovementComponentName(TEXT("TankMovement"));

// Sets default values
ATankPawn::ATankPawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TankVehicleMeshComponentName);
    Mesh->SetCollisionProfileName(UCollisionProfile::Vehicle_ProfileName);
    Mesh->BodyInstance.bSimulatePhysics = true;

    RootComponent = Mesh;
    TankMovement = CreateDefaultSubobject<UTankVehicleMovementComponent>(TankVehicleMovementComponentName);
}

