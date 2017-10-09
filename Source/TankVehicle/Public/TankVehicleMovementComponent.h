// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicleMovementComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "TankVehicleMovementComponent.generated.h"

#ifndef WITH_PHYSX
#define WITH_PHYSX 1
#endif
/**
    From the NVidia PhysX api:
    With eSTANDARD the legal range of left and right thrust is (0,1).
    With eSPECIAL the legal range of left and right thrust is (-1,1).
*/
UENUM()
enum EDriveTankControlModel
{
    Standard = 0,
    Special
};

/**
 * Wrapper class over NVidia's PhysX PxVehicleDriveTank for Unreal Engine
 */
UCLASS()
class TANKVEHICLE_API UTankVehicleMovementComponent : public UWheeledVehicleMovementComponent
{
    GENERATED_BODY()

public:
    /**Set the brake torque to be applied to a specific wheel*/
    UFUNCTION(BlueprintCallable, Category = Vehicle)
    void SetLeftTorque(float torgue);

    /**Set the drive torque to be applied to a specific wheel*/
    UFUNCTION(BlueprintCallable, Category = Vehicle)
    void SetRightTorque(float torgue);

protected:
    float RawLeftTorgue;
    float RawRightTorgue;

    virtual void UpdateSimulation(float DeltaTime) override;
    /** Allocate and setup the PhysX vehicle */
    virtual void SetupVehicleDrive(physx::PxVehicleWheelsSimData* pWheelsSimData) override;
};
