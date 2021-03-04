// Fill out your copyright notice in the Description page of Project Settings.


#include "Piece.h"
#include "GameFramework/Character.h"

// Sets default values
APiece::APiece()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh
	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PieceMesh"));
	RootComponent = m_mesh;

	// Set mesh shape
	static ConstructorHelpers::FObjectFinder<UStaticMesh> staticMesh(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	if (staticMesh.Succeeded())
	{
		m_mesh->SetStaticMesh(staticMesh.Object);
		m_mesh->SetRelativeScale3D({1.0f, 1.0f, 1.0f });

		// Get mesh dimensions
		SetDimensions(staticMesh.Object->GetBounds().GetBox().GetSize());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to set static mesh!"));
	}

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Piece_Light.Piece_Light'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Piece light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Piece_Dark.Piece_Dark'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Piece dark material does not exist!"));
	}

	// Set selected material
	static ConstructorHelpers::FObjectFinder<UMaterial> selectedMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Piece_Selected.Piece_Selected'"));
	if (selectedMaterial.Object != NULL)
	{
		m_selectedMaterial = (UMaterial*)selectedMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Selected material does not exist!"));
	}

	static ConstructorHelpers::FObjectFinder<UMaterial> invisibleMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Piece_Invisible.Piece_Invisible'"));
	if (invisibleMaterial.Object != NULL)
	{
		m_invisibleMaterial = (UMaterial*)invisibleMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Piece dark material does not exist!"));
	}
	m_mesh->SetMaterial(0, m_invisibleMaterial);

	// Set collision properties
	m_mesh->SetCollisionObjectType(ECollisionChannel::ECC_WorldStatic);
	m_mesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
}

// Called when the game starts or when spawned
/*void APiece::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APiece::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/


void APiece::UpdateMaterial()
{	
	// Early return
	if (m_skeletalMesh == nullptr)
	{
		return;
	}

	UMaterial* resultMaterial;
	// Get correct material
	if (m_isSelected)
	{
		resultMaterial = m_selectedMaterial; 
	}
	else if (m_isWhite)
	{
		resultMaterial = m_lightMaterial; 
	}
	else 
	{
		resultMaterial = m_darkMaterial; 
	}
	// Apply material
	m_skeletalMesh->SetMaterial(0, resultMaterial);
}

void APiece::SetBlack()
{ 
	m_isWhite = false;
	UpdateMaterial();
}

void APiece::SelectPiece()
{
	m_isSelected = true;
	UpdateMaterial();
}

void APiece::DeselectPiece()
{	
	m_isSelected= false;
	UpdateMaterial();
}

void APiece::SpawnBlueprint(FVector _dimensions)
{
	FRotator spawnRotator;
	float xPos = (GetSquareID() % 8) * _dimensions.X;
	float yPos = (GetSquareID() / 8) * _dimensions.Y;
	if (m_isWhite)
  {
		spawnRotator = {0.0f, 90.0f, 0.0f};
  }
	else
  {
		spawnRotator = {0.0f, -90.0f, 0.0f};
  }
	m_spawnedBlueprint = GetWorld()->SpawnActor<AActor>(m_pieceBlueprint, { xPos, yPos, 50.0f }, spawnRotator);
	m_character = Cast<ACharacter>(m_spawnedBlueprint);
	m_skeletalMesh = m_character->GetMesh();
	UpdateMaterial();
}

std::vector<std::vector<int>> APiece::CalculateMoves()
{
	UE_LOG(LogTemp, Warning, TEXT("Calculate Moves: Make call to specific piece."));
	return m_availableMoves;
}

void APiece::MovePiece(int _id, FVector _dimensions)
{
	UE_LOG(LogTemp, Warning, TEXT("Move Piece: Make call to specific piece."));
}

bool APiece::GetFirstMove()
{
	UE_LOG(LogTemp, Warning, TEXT("Get First Move: Make call to specific piece."));
	return m_firstMove;
}