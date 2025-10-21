//--------------------------------------------------------------------
// �t�@�C�����FTrashCan.h
// �T�v�@�@�@�F�S�~���N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/02/12 �N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "prototype/Obstacle/Obstacle.h"
#include "TrashCan.generated.h"

// �O���錾
class UBoxComponent;

// �h���b�v������A�C�e����enum�^�Ő��䂷��
UENUM()
enum class DropItems : uint8
{
	Jewel_Blue,		// �W���G��
	Jewel_Red,		// �ԃW���G��
	Jewel_Yellow,	// ���W���G��
	Jewel_Purple,	// ���W���G��

	HpItem,			// �̗͉�
	Magnet,			// �}�O�l�b�g
};

UCLASS()
class PROTOTYPE_API ATrashCan : public AObstacle
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

	// �I�[�o�[���b�v�C�x���g
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

public:
	// �R���X�g���N�^
	ATrashCan();

	UPROPERTY(EditAnywhere, Category = "Drop Items")
	TSubclassOf<class AActor> _pDropItems[6];		// �h���b�v����A�C�e���� BP ���w�肷��

	UPROPERTY()
	DropItems DropItemValue;		// �h���b�v�A�C�e�����Ǘ����� Enmu �^�ϐ�

	UFUNCTION(BlueprintCallable)
	void SpawnDropItem();		// �A�C�e�����h���b�v������֐�


private:

	UPROPERTY(EditAnywhere)
	class UBoxComponent* _pBoxComponent;	 // �{�b�N�X�R���|�[�l���g
};
