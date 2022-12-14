// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
public:
	ATank();
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void HandleDestruction();
	APlayerController* GetPlayerController() const;
	bool GetTankIsAlive() const;
	void SetTankIsAlive(bool bIsAlive);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USpringArmComponent* m_SpringArmComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UCameraComponent* m_CameraComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "General")
	UMaterialInterface* m_BulletMaterial;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement", meta = (AllowPrivateAccess = true))
	float m_Speed = 0.f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float m_MaxSpeed = 450.5f;
	UPROPERTY(EditAnywhere, Category = "Movement")
	float m_Acceleration = 40.f;
	UPROPERTY(EditAnywhere, Category = "Rotation")
	float m_TurnRate = 40.f;

	float m_TempDirection;

	void Move(float Value);
	void Turn(float Value);

	APlayerController* m_PlayerController;

	bool bAlive = true;
};
