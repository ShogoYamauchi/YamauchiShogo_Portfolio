//--------------------------------------------------------------------
// �t�@�C�����FObstacle.h
// �T�v�@�@�@�F��Q���̊��N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/01/30	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class PROTOTYPE_API AObstacle : public AActor
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

	// �I�[�o�[���b�v�ɐݒ肷��R���W�����R���|�[�l���g���i�[���邽�߂̔z��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimitiveComponent* _CollisionComponentsToOverlap;

	// �I�[�o�[���b�v�C�x���g
	UFUNCTION()
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// �R���X�g���N�^
	AObstacle();
	// ���t���[������
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int Hp;			// �̗�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int Score;		// �_��

private:

};
