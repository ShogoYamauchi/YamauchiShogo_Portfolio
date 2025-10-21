//--------------------------------------------------------------------
// �t�@�C�����FLineControllerComponent.h
// �T�v�@�@�@�F���`��A�N�^�[���g�����߂̃R���|�[�l���g�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/15	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LineControllerComponent.generated.h"

// �O���錾
class APredictionLine;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class PROTOTYPE_API ULineControllerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	ULineControllerComponent();
	// �Q�[���I�����A�܂��͔j�����ɌĂ΂�鏈��
	void EndPlay(const EEndPlayReason::Type EndPlayReason);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Line")
	TSubclassOf<AActor> LineActorsClass;	// �\�����̃A�N�^�[�N���X 
	UPROPERTY()
	APredictionLine* _pPredictionLineActor;	// �����������`�悷��A�N�^�[

	UFUNCTION(BlueprintCallable, Category = "Line")
	void SpawnAndInitializeLineActor(); 	// ���`��A�N�^�[���X�|�[�����ď�����
	UFUNCTION(BlueprintCallable, Category = "Line")
	void UpdateLineActor(FVector& Start, FVector& End);		// �����X�V����
	UFUNCTION()
	void DestroyPredictionLineActor();	// ���̃A�N�^�[����������֐�
	UFUNCTION()
	void HidePredictionLineActor();	// �\�������\���ɂ���֐�
	UFUNCTION()
	void DisplayPredictionLineActor();	// �\������\���ɂ���֐�

private:
	UPROPERTY(EditAnywhere)
	FVector _lineOffset;	// �\�����̈ʒu�̃I�t�Z�b�g
	UPROPERTY(EditAnywhere)
	bool _predictionLineFlag;	// �\�������o�����ǂ����̃t���O
};
