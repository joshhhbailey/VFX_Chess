///
///  @file Piece_King.cpp
///  @brief King movement logic
/// 
#include "Piece_King.h"

APiece_King::APiece_King()
{
	// Set blueprint
	static ConstructorHelpers::FObjectFinder<UClass> kingBlueprint(TEXT("Class'/Game/VFX_Chess/Assets/Characters/King/King_BP.King_BP_C'"));
	if (kingBlueprint.Succeeded())
	{
		m_pieceBlueprint = kingBlueprint.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("King BP does not exist!"));
	}

	// Set light material
	static ConstructorHelpers::FObjectFinder<UMaterial> lightMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/King/kingWhite_MAT.kingWhite_MAT'"));
	if (lightMaterial.Object != NULL)
	{
		m_lightMaterial = (UMaterial*)lightMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("King light material does not exist!"));
	}

	// Set dark material
	static ConstructorHelpers::FObjectFinder<UMaterial> darkMaterial(TEXT("Material'/Game/VFX_Chess/Assets/Materials/Pieces/King/kingBlack_MAT.kingBlack_MAT'"));
	if (darkMaterial.Object != NULL)
	{
		m_darkMaterial = (UMaterial*)darkMaterial.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("King dark material does not exist!"));
	}
}

std::vector<std::vector<int>> APiece_King::CalculateMoves()
{
	// Clear previous moves
	m_U.clear();
	m_R.clear();
	m_D.clear();
	m_L.clear();
	m_UL.clear();
	m_UR.clear();
	m_DL.clear();
	m_DR.clear();
	m_availableMoves.clear();

	if (GetSquareID() < 56)	// Piece not on top edge
	{
		m_U.push_back(GetSquareID() + 8);
	}

	if (GetSquareID() % 8 != 0)	// Piece not at right edge
	{
		m_R.push_back(GetSquareID() - 1);
	}

	if (GetSquareID() > 7)		// Piece not on bottom edge
	{
		m_D.push_back(GetSquareID() - 8);
	}

	if (GetSquareID() % 8 != 7)	// Piece not on left edge
	{
		m_L.push_back(GetSquareID() + 1);
	}

	// Diagonals
	if (GetSquareID() % 8 != 7 && GetSquareID() < 56)	// Piece not on left or top edge
	{
		m_UL.push_back(GetSquareID() + 9);
	}

	if (GetSquareID() < 56 && GetSquareID() % 8 != 0)	// Piece not on top or right edge
	{
		m_UR.push_back(GetSquareID() + 7);
	}

	if (GetSquareID() % 8 != 0 && GetSquareID() > 7)	// Piece not on right or bottom edge
	{
		m_DR.push_back(GetSquareID() - 9);
	}

	if (GetSquareID() > 7 && GetSquareID() % 8 != 7)	// Piece not on bottom or left edge
	{
		m_DL.push_back(GetSquareID() - 7);
	}

	// Return new available moves
	m_availableMoves.push_back(m_U);
	m_availableMoves.push_back(m_R);
	m_availableMoves.push_back(m_D);
	m_availableMoves.push_back(m_L);
	m_availableMoves.push_back(m_UL);
	m_availableMoves.push_back(m_UR);
	m_availableMoves.push_back(m_DL);
	m_availableMoves.push_back(m_DR);
	return m_availableMoves;
}

void APiece_King::UpdateMaterial()
{
	// Early return
	if (m_skeletalMesh == nullptr)
	{
		return;
	}

	UMaterial* resultMaterial;
	// Get correct material
	if (GetIsSelected())
	{
		resultMaterial = m_selectedMaterial;
	}
	else if (GetIsWhite())
	{
		resultMaterial = m_lightMaterial;
	}
	else
	{
		resultMaterial = m_darkMaterial;
	}
	// Apply material
	for (int materialSlotIndex = 0; materialSlotIndex < m_skeletalMesh->GetNumMaterials(); materialSlotIndex++)
	{
		m_skeletalMesh->SetMaterial(materialSlotIndex, resultMaterial);
	}
}