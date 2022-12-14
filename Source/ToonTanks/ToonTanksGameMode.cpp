// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"

#include "Tank.h"
#include "ToonTanksPlayerController.h"
#include "Tower.h"
#include "Kismet/GameplayStatics.h"

void AToonTanksGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	HandleGameStart();
}

void AToonTanksGameMode::HandleGameStart()
{
	m_TowerCount = FindTotalTowerCount();
	m_Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	m_ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this,0));

	StartGame();
	
	if(m_ToonTanksPlayerController)
	{
		m_ToonTanksPlayerController->SetPlayerEnabledState(false);
		FTimerHandle playerEnableTimerHandle;
		FTimerDelegate playerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			m_ToonTanksPlayerController,
			&AToonTanksPlayerController::SetPlayerEnabledState,
			true);
		GetWorldTimerManager().SetTimer(playerEnableTimerHandle,
										 playerEnableTimerDelegate,
									m_startDelay,
									false);
	}
}

void AToonTanksGameMode::ActorDied(AActor* deadActor)
{
	if(deadActor == m_Tank)
	{
		m_Tank->HandleDestruction();
		if(m_ToonTanksPlayerController)
		{
			m_ToonTanksPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if(ATower* destroyedTower = Cast<ATower>(deadActor))
	{
		destroyedTower->HandleDestruction();
		m_TowerCount--;
		if(m_TowerCount == 0)
			GameOver(true);
	}
}

uint32_t AToonTanksGameMode::FindTotalTowerCount()
{
	TArray<AActor*> Towers;
	UGameplayStatics::GetAllActorsOfClass(this, ATower::StaticClass(), Towers);
	return Towers.Num();
}


