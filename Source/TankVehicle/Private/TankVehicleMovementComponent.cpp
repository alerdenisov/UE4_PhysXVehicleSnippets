// Fill out your copyright notice in the Description page of Project Settings.

#if WITH_PHYSX
#include "TankVehicleMovementComponent.h"
#include "TankVehiclePrivatePCH.h"

#include "PhysicsPublic.h"
#include "PhysXPublic.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "vehicle/PxVehicleWheels.h"
#include "vehicle/PxVehicleDriveTank.h"

PxVehiclePadSmoothingData PadSmoothingData {
	{
		6.0f,	//rise rate eANALOG_INPUT_ACCEL=0,
		6.0f,	//rise rate eANALOG_INPUT_BRAKE,
		6.0f,	//rise rate eANALOG_INPUT_HANDBRAKE,
		2.5f,	//rise rate eANALOG_INPUT_STEER_LEFT,
		2.5f,	//rise rate eANALOG_INPUT_STEER_RIGHT,
	},
	{
		10.0f,	//fall rate eANALOG_INPUT_ACCEL=0
		10.0f,	//fall rate eANALOG_INPUT_BRAKE_LEFT
		10.0f,	//fall rate eANALOG_INPUT_BRAKE_RIGHT
		5.0f,	//fall rate eANALOG_INPUT_THRUST_LEFT
		5.0f	//fall rate eANALOG_INPUT_THRUST_RIGHT
	}
};


PxVehicleDriveTankRawInputData InputData(PxVehicleDriveTankControlModel::eSPECIAL);

void UTankVehicleMovementComponent::SetLeftTorque(float torgue)
{
    RawLeftTorgue = torgue;
}

void UTankVehicleMovementComponent::SetRightTorque(float torgue)
{
    RawRightTorgue = torgue;
}

void UTankVehicleMovementComponent::SetupVehicleDrive(PxVehicleWheelsSimData* pWheelsSimData)
{
    if (UpdatedPrimitive) {
        PxVehicleDriveSimData driveSimData;
        {
            //Set up the engine to be more powerful but also more damped than the default engine.
            PxVehicleEngineData engineData = driveSimData.getEngineData();
            engineData.mPeakTorque *= 2.0f;
            engineData.mDampingRateZeroThrottleClutchEngaged = 2.0f;
            engineData.mDampingRateZeroThrottleClutchDisengaged = 0.5f;
            engineData.mDampingRateFullThrottle = 0.5f;
            driveSimData.setEngineData(engineData);
        }


        PxVehicleDriveTank* pVehicleDriveTank = PxVehicleDriveTank::allocate(WheelSetups.Num());
        check(pVehicleDriveTank);

        ExecuteOnPxRigidDynamicReadWrite(UpdatedPrimitive->GetBodyInstance(), [&](PxRigidDynamic* pRigidDynamic)
        {
            pVehicleDriveTank->setup(GPhysXSDK, pRigidDynamic, *pWheelsSimData, driveSimData, WheelSetups.Num());
            pVehicleDriveTank->setToRestState();
	        pVehicleDriveTank->mDriveDynData.forceGearChange(PxVehicleGearsData::eFIRST);
	        pVehicleDriveTank->mDriveDynData.setUseAutoGears(true);
	        pVehicleDriveTank->setDriveModel(PxVehicleDriveTankControlModel::eSPECIAL);

            pWheelsSimData->free();
        });

        PVehicle = pVehicleDriveTank;
    }
}


void UTankVehicleMovementComponent::UpdateSimulation(float DeltaTime)
{
	if (PVehicle && UpdatedPrimitive)
	{
//	    UE_LOG(LogTemp, Display, TEXT("Update Simulation 3"));

	    ExecuteOnPxRigidDynamicReadWrite(UpdatedPrimitive->GetBodyInstance(), [&](PxRigidDynamic* pRigidDynamic)
	    {
	        if (fabs(RawLeftTorgue) > DELTA || fabs(RawRightTorgue) > DELTA)
	        {
                InputData.setAnalogAccel(1.0f);
            } else
            {
                InputData.setAnalogAccel(0.0f);
            }

            InputData.setAnalogLeftThrust(FMath::Clamp(RawLeftTorgue, -1.0f, 1.0f));
            InputData.setAnalogRightThrust(FMath::Clamp(RawRightTorgue, -1.0f, 1.0f));
            InputData.setAnalogLeftBrake(0.0f);
            InputData.setAnalogRightBrake(0.0f);

	        // cast vehicle to tank
            PxVehicleDriveTank* PVehicleDriveTank = (PxVehicleDriveTank*)PVehicle;
            PxVehicleDriveTankSmoothAnalogRawInputsAndSetAnalogInputs(PadSmoothingData, InputData, DeltaTime, *PVehicleDriveTank);
	    });
	}
}
#endif