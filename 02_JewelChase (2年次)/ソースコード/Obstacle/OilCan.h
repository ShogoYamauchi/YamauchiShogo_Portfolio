//--------------------------------------------------------------------
// �t�@�C�����FOilCan.h
// �T�v�@�@�@�F�I�C���ʃN���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/01/30	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "prototype/Obstacle/Obstacle.h"
#include "OilCan.generated.h"

UCLASS()
class PROTOTYPE_API AOilCan : public AObstacle
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
	AOilCan();
	// ���t���[������
	virtual void Tick(float DeltaTime) override;

	// �����̃R���W������ON�ɂ���֐�
	UFUNCTION(BlueprintCallable)
	void TurnOnExplosionCollision();

private:
	UPROPERTY(EditAnywhere)
	class UCapsuleComponent* _pCapsuleComponent;		// �J�v�Z���R���|�[�l���g
	UPROPERTY()
	class USphereComponent* _pSphereComponent; // �J�v�Z���R���|�[�l���g
};
