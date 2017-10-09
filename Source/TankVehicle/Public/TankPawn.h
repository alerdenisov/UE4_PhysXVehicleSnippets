// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "WheeledVehicle.h"
// #include "TankVehicleMovementComponent.h"
#include "TankPawn.generated.h"


class UTankVehicleMovementComponent;

UCLASS()
class TANKVEHICLE_API ATankPawn : public APawn
{
    GENERATED_UCLASS_BODY()

public:

    /** Name of the MeshComponent. Use this name if you want to prevent creation of the component (with ObjectInitializer.DoNotCreateDefaultSubobject). */
    static FName TankVehicleMeshComponentName;

    /** Name of the VehicleMovement. Use this name if you want to use a different class (with ObjectInitializer.SetDefaultSubobjectClass). */
    static FName TankVehicleMovementComponentName;

    /**  The main skeletal mesh associated with this Vehicle */
    UPROPERTY(Category = "Tank", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class USkeletalMeshComponent* Mesh;

    /** vehicle simulation component */
    UPROPERTY(Category = "Tank", VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
    class UTankVehicleMovementComponent* TankMovement;
};
