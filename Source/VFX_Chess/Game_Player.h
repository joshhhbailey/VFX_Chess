// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "Game_Controller.h"

#include "GameFramework/Pawn.h"
#include "CoreMinimal.h"
#include "Game_Player.generated.h"

UCLASS()
class VFX_CHESS_API AGame_Player : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGame_Player();

private:
	UPROPERTY()
		AGame_Controller* m_gameController;

	UCameraComponent* m_camera;
	USpringArmComponent* m_cameraSpringArm;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
