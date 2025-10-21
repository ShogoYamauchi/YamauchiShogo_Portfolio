//--------------------------------------------------------------------
// �t�@�C�����FpredectionLine.h
// �T�v�@�@�@�F�\������Actor�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/15	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PredictionLine.generated.h"

// �O���錾
class USplineComponent;
class USplineMeshComponent;

UCLASS()
class PROTOTYPE_API APredictionLine : public AActor
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	APredictionLine();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UStaticMesh* LineStaticMesh;	// UE���ŃX�^�e�B�b�N���b�V���ݒ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spline")
	UMaterialInterface* LineMaterial;	// UE���Ń}�e���A���ݒ�

	// �����X�V����֐�
	UFUNCTION(BlueprintCallable, Category = "Line")
	void UpdateLine(const FVector& StartPoint, const FVector& EndPoint);

private:
	UPROPERTY(VisibleAnywhere, Category = "Components")
	USplineComponent* _pSplineComponent;	// �X�v���C���R���|�[�l���g
	UPROPERTY()
	USplineMeshComponent* _pSplineMeshComponent;  // �X�v���C�����b�V���R���|�[�l���g���i�[����|�C���^

	FVector _splineStartPoint;	// Spline�̎n�_
	FVector _splineEndPoint;		// Spline�̏I�_
};
